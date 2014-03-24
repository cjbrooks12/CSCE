
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Group.H>
#include "GUI.h"

namespace Graph_lib {

//------------------------------------------------------------------------------
//void Widget::add(Fl_Widget& wid) { 
//reference_to<Widget>(pw).add(wid);
//}

void Button::attach(Window& win)
{
	pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
	//pw->color(c);
	//pw->selection_color(c_p);
	//reference_to<Fl_Button>(pw).value(state);
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
	own = &win;
}

//my Button functions that access the built in fltk functions
//=============================================================
void Button::set(int l)
{
	reference_to<Fl_Button>(pw).value(l);
}
char Button::get()
{
	reference_to<Fl_Button>(pw).value();
}
void Button::color(Fl_Color col)
{
	reference_to<Fl_Button>(pw).color(col);
}
void Button::selection_color(Fl_Color scol)
{
	reference_to<Fl_Button>(pw).selection_color(scol);
}
void Button::set_box(Fl_Boxtype f)
{
	reference_to<Fl_Button>(pw).box(f);
}
//=============================================================
//------------------------------------------------------------------------------

int In_box::get_int()
{
    Fl_Input& pi = reference_to<Fl_Input>(pw);
    // return atoi(pi.value());
    const char* p = pi.value();
    if (!isdigit(p[0])) return -999999;
    return atoi(p);
}

//------------------------------------------------------------------------------

string In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	return string(pi.value());
}

//------------------------------------------------------------------------------

void In_box::attach(Window& win)
{
    pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
    own = &win;
}

void In_box::labelcolor(Fl_Color c)
{
	reference_to<Fl_Input>(pw).labelcolor(c);
}
//------------------------------------------------------------------------------

void Out_box::put(const string& s)
{
    reference_to<Fl_Output>(pw).value(s.c_str());
}

//------------------------------------------------------------------------------

void Out_box::attach(Window& win)
{
    pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
    own = &win;
}

//------------------------------------------------------------------------------
//my outbox functions that access the built in fltk functions
//=============================================================
string Out_box::contents()
{
	return (string)(reference_to<Fl_Output>(pw).value());
}
void Out_box::textcolor(Fl_Color c)
{
	reference_to<Fl_Output>(pw).textcolor(c);
}

void Out_box::textsize(int size)
{
	reference_to<Fl_Output>(pw).textsize((unsigned char)size);
}
void Out_box::set_box(Fl_Boxtype bx)
{
	reference_to<Fl_Output>(pw).box(bx);
}
void Out_box::deactivate()
{
	pw->deactivate();
}
void Out_box::color(Fl_Color c)
{
	reference_to<Fl_Output>(pw).color(c);
}
//=============================================================
//------------------------------------------------------------------------------

int Menu::attach(Button& b)
{
    b.width = width;
    b.height = height;

    switch(k) {
    case horizontal:
        b.loc = Point(loc.x+offset,loc.y);
        offset+=b.width;
        break;
    case vertical:
        b.loc = Point(loc.x,loc.y+offset);
        offset+=b.height;
        break;
    }
    selection.push_back(b); // b is NOT OWNED: pass by reference
    return int(selection.size()-1);
}

//------------------------------------------------------------------------------

int Menu::attach(Button* p)
{
    Button& b = *p;
    b.width = width;
    b.height = height;

    switch(k) {
    case horizontal:
        b.loc = Point(loc.x+offset,loc.y);
        offset+=b.width;
        break;
    case vertical:
        b.loc = Point(loc.x,loc.y+offset);
        offset+=b.height;
        break;
    }
    selection.push_back(&b); // b is OWNED: pass by pointer
    return int(selection.size()-1);
}

//------------------------------------------------------------------------------

}; // of namespace Graph_lib
