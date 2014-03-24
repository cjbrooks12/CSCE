#ifndef CALENDAR_WINDOW_GUARD
#define CALENDAR_WINDOW_GUARD 1

#include "std_lib_facilities_3.h"
#include "GUI.h"
#include "Graph.h"
#include <vector>
#include <ctime>
#include "fileIO.h"

using namespace Graph_lib;
		
//------------------------------------------------------------------------------

struct Calendar_window : Graph_lib::Window {
    Calendar_window(Point xy, int w, int h, const string& title, int _yy, int _mm, string _filename);
    bool show_window(); // simple event loop
private:
	//=========Colors
	Fl_Color maroon=(fl_rgb_color(80,0,0));
	Fl_Color white=(fl_rgb_color(255,255,255));
	
	//=========vars
	int x = 112;
	int xx = x-5;
	int xxx = 10;
	int y = 90;
	//=========label arrays
	string wkdy[7] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	string mnth[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	bool button_pushed;
	
	//=========vectors to display appointments
	Vector_ref<Out_box> out_text1;
	Vector_ref<Out_box> out_text2;
	Vector_ref<Out_box> out_text3;
	Vector_ref<Out_box> out_text4;
	
	//=========vector to display each day number
	Vector_ref<Out_box> labels;
	
	//=========vector to display each weekday label
	Vector_ref<Out_box> weekdays;
	
	//=========vector of appointments
	vector<fileIO::Appt> appts;
	
	//=========filename of appointments
	string filename;
	
	//=========outbox for current day
	Out_box date_text;
	
	//=========input for appointment
	In_box add_appt_data;
	In_box search;
	
	Chrono::Date d;
	
	//=========appointment button
	Button search_appt_button;
	static void cb_search_appt(Address, Address);
	void search_appt();
	
	//=========appointment button
	Button add_appt_button;
	static void cb_add_appt(Address, Address);
	void add_appt();
	
	//=========repeating appointment button
	Button add_rep_appt_button;
	static void cb_add_rep_appt(Address, Address);
	void add_rep_appt();
	
	//=========vector of date buttons
	Vector_ref<Button> dates;
	static void cb_cal(Address, Address);
	void cal();
	
	//=========previous month button
	Button prev_month_button;
	static void cb_prev_month(Address, Address);
	void draw_prev_month();
	
	//=========next month button
	Button next_month_button;
	static void cb_next_month(Address, Address); // callback for next_button
	void draw_next_month();
	
	//=========helper functions
	void update_date_text();
	void init_vector_objects();
	void init_weekdays();
	//==========================
	void display_appt();
	void clear_appt();
	//==========================
	int get_pressed();
	void set_pressed_date();
	//==========================
	void clear_month();
	void draw_month();
	//==========================
	void hide_boxes(int index);
	void show_all_boxes(int index);
	//==========================
	int month_start_day(int yr, int mth);
	bool full_moon(int dd, int mm, int yy);
	
};
	
	
#endif
