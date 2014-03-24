
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef POPUP_WINDOW_GUARD
#define POPUP_WINDOW_GUARD 1
#include "std_lib_facilities_3.h"
#include "GUI.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Popup_window : Graph_lib::Window {
	Popup_window(Point xy, int w, int h, const string& title );
	bool wait_for_button(); // simple event loop
	int year(){return y;}
	int month(){return m;}
	string get_filename(){return filename;}
	bool fexists(string filename);
	bool is_button_pushed(){return button_pushed;}
private:
	Button next_button;     // the "next" button
	bool button_pushed;
	In_box year_input;
	In_box month_input;
	In_box filename_input;
	Out_box error_output;
	Image splash;
	Image appt_text;
	void get_info();
	static void cb_next(Address, Address); // callback for next_button
	void next();            // action to be done when next_button is pressed
	int y;
	int m;
	string filename;
};

//------------------------------------------------------------------------------

#endif
