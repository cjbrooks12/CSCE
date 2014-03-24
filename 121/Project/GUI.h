
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef GUI_GUARD
#define GUI_GUARD

#include "Window.h"
#include "Graph.h"

namespace Graph_lib {

//------------------------------------------------------------------------------

    typedef void* Address;    // Address is a synonym for void*
    typedef void(*Callback)(Address, Address);    // FLTK's required function type for all callbacks

//------------------------------------------------------------------------------

    template<class W> W& reference_to(Address pw)
    // treat an address as a reference to a W
    {
        return *static_cast<W*>(pw);
    }

//------------------------------------------------------------------------------

    class Widget {
    // Widget is a handle to an Fl_widget - it is *not* an Fl_widget
    // We try to keep our interface classes at arm's length from FLTK
    public:
        Widget(Point xy, int w, int h, const string& s, Callback cb)
            : loc(xy), width(w), height(h), label(s), do_it(cb)
        {}
        virtual void move(int dx,int dy) { hide(); pw->position(loc.x+=dx, loc.y+=dy); show(); }
        virtual void hide() { pw->hide(); }
        virtual void show() { pw->show(); }
        
        //I added these functions to access the built in fltk functions
	//=============================================================
	virtual void set(int x) { reference_to<Widget>(pw).set(x); }
	virtual char get() { reference_to<Widget>(pw).get(); }
	virtual void color(Fl_Color col) { reference_to<Widget>(pw).color(col); }
	virtual void textcolor(Fl_Color col) { reference_to<Widget>(pw).textcolor(col); }
	virtual void labelcolor(Fl_Color col) { reference_to<Widget>(pw).labelcolor(col); }
	virtual void selection_color(Fl_Color scol) { reference_to<Widget>(pw).selection_color(scol); }
	//=============================================================

        virtual void attach(Window&) = 0;

        Point loc;
        int width;
        int height;
        string label;
        Callback do_it;

        virtual ~Widget() { }

    protected:
        Window* own;    // every Widget belongs to a Window
        Fl_Widget* pw;  // connection to the FLTK Widget
    private:
        Widget& operator=(const Widget&); // don't copy Widgets
        Widget(const Widget&);
    };

//------------------------------------------------------------------------------

    struct Button : Widget {
        Button(Point xy, int w, int h, const string& label, Callback cb)
            : Widget(xy,w,h,label,cb)
        {}
	
        void attach(Window&);
        
        //my Button functions that access the built in fltk functions
	//=============================================================
	void color(Fl_Color);
	void selection_color(Fl_Color);
	void set(int);
	char get();
	void set_box(Fl_Boxtype);
	//=============================================================
    };

//------------------------------------------------------------------------------

    struct In_box : Widget {
        In_box(Point xy, int w, int h, const string& s)
            :Widget(xy,w,h,s,0) { }
        int get_int();
        string get_string();
	
        void attach(Window& win);
        void labelcolor(Fl_Color);
    };

//------------------------------------------------------------------------------

    struct Out_box : Widget {
        Out_box(Point xy, int w, int h, const string& s)
            :Widget(xy,w,h,s,0) { }
        void put(int);
        void put(const string&);
        void attach(Window& win);
        
        //my outbox functions that access the built in fltk functions
	//=============================================================
	void set_box(Fl_Boxtype);
	void deactivate();
	void color(Fl_Color);
	void textcolor(Fl_Color);
	void textsize(int size);
	string contents();
	
	//=============================================================
    };
	
//------------------------------------------------------------------------------

    struct Menu : Widget {
        enum Kind { horizontal, vertical };
        Menu(Point xy, int w, int h, Kind kk, const string& label)
            : Widget(xy,w,h,label,0), k(kk), offset(0)
        {}

        Vector_ref<Button> selection;
        Kind k;
        int offset;
        int attach(Button& b);      // Menu does not delete &b
        int attach(Button* p);      // Menu deletes p

        void show()                 // show all buttons
        {
            for (unsigned int i = 0; i<selection.size(); ++i)
                selection[i].show();
        }
        void hide()                 // hide all buttons
        {
            for (unsigned int i = 0; i<selection.size(); ++i) 
                selection[i].hide(); 
        }
        void move(int dx, int dy)   // move all buttons
        {
            for (unsigned int i = 0; i<selection.size(); ++i) 
                selection[i].move(dx,dy);
        }

        void attach(Window& win)    // attach all buttons
        {
            for (int i=0; i<selection.size(); ++i) win.attach(selection[i]);
            own = &win;
        }

    };

//------------------------------------------------------------------------------

} // of namespace Graph_lib

#endif // GUI_GUARD
