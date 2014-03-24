#include "Calendar_window.h"

using namespace Graph_lib;

Calendar_window::Calendar_window(Point xy, int w, int h, const string& title, int _yy, int _mm, string _filename) :
	Window(xy,w,h,title),
	button_pushed(false),
	filename(_filename),
	date_text(Point(100,15),200,20,""),
	add_appt_button(Point(455,15), 40, 20, "Add", cb_add_appt),
	add_rep_appt_button(Point(500,15), 90, 20, "Add Yearly", cb_add_rep_appt),
	add_appt_data(Point(350,15), 100, 20,"Appointment:"),
	search(Point(650,15), 80, 20,"Search:"),
	search_appt_button(Point(735,15), 60, 20, "Search", cb_search_appt),
	next_month_button(Point(50,15), 30, 20, "-->", cb_next_month),
	prev_month_button(Point(10,15), 30, 20, "<--", cb_prev_month)
{	
	//set the background color of the window
	color(maroon);
	appts = fileIO::read_file(filename);
	d.change_date(_yy,_mm,1);
	
	init_vector_objects();
	init_weekdays();
	attach(next_month_button);
	attach(prev_month_button);
	attach(date_text);
	attach(add_appt_data);
	attach(add_appt_button);
	attach(add_rep_appt_button);
	attach(search);
	attach(search_appt_button);
	search.labelcolor(white);
	search_appt_button.color(white);
	add_appt_button.color(white);
	add_appt_data.labelcolor(white);
	add_rep_appt_button.color(white);
	prev_month_button.color(white);
	next_month_button.color(white);
	date_text.set_box(FL_NO_BOX);
	date_text.textcolor(white);
	draw_month();
	
}

//======================================
//call this to show the window on the screen
//======================================
bool Calendar_window::show_window()
{
	gui_main();
}

//=============================================================================
//=============================================================================
//===============================Callback functions============================
//=============================================================================
//=============================================================================


void Calendar_window::cb_search_appt(Address, Address pw)
{
	reference_to<Calendar_window>(pw).search_appt(); 
}
void Calendar_window::search_appt()
{
	sort_appts(appts);
	string s = search.get_string();
	Chrono::Date fd = fileIO::search_appointments(appts,s);
	if(fd.year() == 0){
		if(d.month() <= fd.month() && d.day() <= fd.day()){
			d = Chrono::Date(d.year(),fd.month(),fd.day());
		}
		else
			d = Chrono::Date(d.year()+1,fd.month(),fd.day());
	}
	else
		d = fd;
	for(int i=0; i<42; ++i){
		show_all_boxes(i);
	}
	
	draw_month();
	redraw();
	
}

//===========================================
//Callback functions for add appt button
//===========================================
void Calendar_window::cb_add_appt(Address, Address pw)
{  
    reference_to<Calendar_window>(pw).add_appt();    
}
void Calendar_window::add_appt()
{
	string s = add_appt_data.get_string();
	if (s != ""){
		fileIO::Appt a(d,s);
		fileIO::add_appointment(appts, a);
		fileIO::write_file(appts,filename);
		display_appt();
	}
	
}

//===========================================
//Callback functions for add appt repeating button
//===========================================
void Calendar_window::cb_add_rep_appt(Address, Address pw)
{  
    reference_to<Calendar_window>(pw).add_rep_appt();    
}
void Calendar_window::add_rep_appt()
{
	string s = add_appt_data.get_string();
	Chrono::Date dc(d.month(),d.day());
	if (s != ""){
		fileIO::Appt a(dc,s);
		fileIO::add_appointment(appts, a);
		fileIO::write_file(appts,filename);
		display_appt();
	}
	
}

//===========================================
//Callback functions for next/prev month button
//===========================================
void Calendar_window::cb_next_month(Address, Address pw)
{
	reference_to<Calendar_window>(pw).clear_month();  
	reference_to<Calendar_window>(pw).draw_next_month();  
}

void Calendar_window::cb_prev_month(Address, Address pw)
{  
	reference_to<Calendar_window>(pw).clear_month();  
	reference_to<Calendar_window>(pw).draw_prev_month();  
}

//======================================
//do all necessary actions to show next month on screen
//======================================
void Calendar_window::draw_next_month()
{
	clear_month();
	clear_appt();
	d.Chrono::Date::add_month(1);
	int start= month_start_day((d.year()), ((int)d.month()));
	for(int i=0; i<labels.size(); ++i){ //run for each column
		show_all_boxes(i);
		if(i>=(start) && i<(start+days_in_month(d.year(), d.month()))){
			stringstream ss;
			ss<<i+1-(start);
			labels[i].put(ss.str());
		}
		else
			hide_boxes(i);
	}
	set_pressed_date();
	display_appt();
	update_date_text();
	redraw();
}

//======================================
//do all necessary actions to show prev month on screen
//======================================
void Calendar_window::draw_prev_month()
{
	clear_month();
	clear_appt();
	d.Chrono::Date::sub_month(1);
	int start= month_start_day((d.year()), ((int)d.month()));
	for(int i=0; i<labels.size(); ++i){ //run for each column
		show_all_boxes(i);
		if(i>=(start) && i<(start+days_in_month(d.year(), d.month()))){
			stringstream ss;
			ss<<i+1-(start);
			labels[i].put(ss.str());
		}
		else
			hide_boxes(i);
	}
	set_pressed_date();
	display_appt();
	update_date_text();
	redraw();
}




//======================================
//callback function for when a date is clicked
//======================================
void Calendar_window::cb_cal(Address, Address pw)
{  
    reference_to<Calendar_window>(pw).cal();  
}

//--------------------------------------
//do all necessary actions to show month on screen
//--------------------------------------
void Calendar_window::cal() //run when any day is clicked
{
	
	//set the state of each button to off
	for(int i=0; i<dates.size(); ++i){
		dates[i].set(0);
	}
	//set the color of each label to default
	for(int j=0; j<labels.size(); ++j){
			labels[j].color(maroon);
			labels[j].textcolor(white);
			}
	//set clicked day to on
	reference_to<Button>(this).set(1);
	  
	//set the color of the label that was clicked
	labels[get_pressed()].color(white);
	labels[get_pressed()].textcolor(maroon);
	
	int yy = d.year();
	int mm = d.month();
	int selection = get_pressed()+1;
	int startday = month_start_day(yy,mm);
	
	d.change_date(yy,mm,selection-startday);
	update_date_text();
	//redraw the objects
	redraw();
}


//=============================================================================
//=============================================================================
//===============================Helper functions==============================
//=============================================================================
//=============================================================================



//======================================
//update current date being shown
//======================================
void Calendar_window::update_date_text(){
	stringstream ss;
	ss<<mnth[d.month()-1]<<" "<<d.day()<<", "<<d.year();
	stringstream sss;
	sss<<"";
	date_text.put(sss.str());
	date_text.put(ss.str());
}

//======================================
//actions to properly create the vector objects
//======================================
void Calendar_window::init_vector_objects(){
	for(int j=0; j<6; ++j){ //run for each column
		for(int i=0; i<7; ++i){ //run for a row of 7
			
			//create buttons for each day of the month
			dates.push_back(new Button(Point((i*x)+xxx,(j*y)+65),xx,y,"",cb_cal));
			
			//create day label for each day
			labels.push_back(new Out_box(Point((i*x)+xxx,(j*y)+65),xx,20,""));
			
			//create text boxes for each day to hold appts
			out_text1.push_back(new Out_box(Point((i*x)+xxx,(j*y)+85),xx,15,""));
			out_text2.push_back(new Out_box(Point((i*x)+xxx,(j*y)+100),xx,15,""));
			out_text3.push_back(new Out_box(Point((i*x)+xxx,(j*y)+115),xx,15,""));
			out_text4.push_back(new Out_box(Point((i*x)+xxx,(j*y)+130),xx,15,""));
			
			
			//attach appts text boxes to window
			//and set color and text size
			attach(out_text1[out_text1.size()-1]);
			attach(out_text2[out_text2.size()-1]);
			attach(out_text3[out_text3.size()-1]);
			attach(out_text4[out_text4.size()-1]);
			out_text1[out_text1.size()-1].color(white);
			out_text2[out_text2.size()-1].color(white);
			out_text3[out_text3.size()-1].color(white);
			out_text4[out_text4.size()-1].color(white);
			out_text1[out_text1.size()-1].textsize(10);
			out_text2[out_text2.size()-1].textsize(10);
			out_text3[out_text3.size()-1].textsize(10);
			out_text4[out_text4.size()-1].textsize(10);
			
			//attach day labels to window
			attach(labels[labels.size()-1]);
			
			//attach buttons to window
			attach(dates[dates.size()-1]);
			labels[labels.size()-1].color(maroon);
			labels[labels.size()-1].textcolor(white);
			
			//set the box style of buttons to be invisible
			dates[dates.size()-1].set_box(FL_NO_BOX);
			
			
		}
	}
}

//======================================
//actions to properly create weekday labels
//======================================
void Calendar_window::init_weekdays(){
	for(int i=0; i<7; ++i){
		weekdays.push_back(new Out_box(Point((i*x)+xxx,30),120,40,""));
		attach(weekdays[weekdays.size()-1]);
		weekdays[i].set_box(FL_NO_BOX);
		stringstream ss;
		ss<<wkdy[i];
		weekdays[i].put(ss.str());
		weekdays[i].textcolor(white);
	}
}
//======================================
//display appointments for current month
//======================================
void Calendar_window::display_appt(){
	clear_appt();
	int mm = d.month();
	int yy = d.year();
	int startday = month_start_day(yy,mm);
	int daysinmonth = days_in_month(yy,Chrono::Date::Month(mm));
	for (int i=0; i<days_in_month(yy,Chrono::Date::Month(mm)); ++i)
	{
		if(full_moon(yy,mm,i+1))
			out_text1[startday+i].put("Full Moon");
	}
	for (int i=0; i<appts.size(); ++i){
		if ((mm==appts[i].get_date().month() && yy==appts[i].get_date().year()) || (mm==appts[i].get_date().month() && appts[i].get_date().year()==0)){
			//int selection = get_pressed()+1;
			int dd = appts[i].get_date().day();
			int j=dd+startday-1;
			stringstream ss;
			ss<<appts[i].get_appointment();
			if(out_text1[j].contents().compare("")==0){ out_text1[j].put(ss.str());}
			else if(out_text2[j].contents().compare("")==0){ out_text2[j].put(ss.str());}
			else if(out_text3[j].contents().compare("")==0){ out_text3[j].put(ss.str());}
			else if(out_text4[j].contents().compare("")==0){ out_text4[j].put(ss.str());}
		}
	}
	redraw();
}

//======================================
//clear text boxes showing appointments
//======================================
void Calendar_window::clear_appt(){
	for(int i=0; i<labels.size(); ++i){ //run for each column
		stringstream ss;
		ss<<"";
		out_text1[i].put(ss.str());
		out_text2[i].put(ss.str());
		out_text3[i].put(ss.str());
		out_text4[i].put(ss.str());
	}
}

//======================================
//return index of currently pressed button
//======================================
int Calendar_window::get_pressed()
{
	for(int i=0; i<dates.size(); ++i){
		if(dates[i].get()==1){
			return i;
		}
	}
}

//======================================
//change the selected button to the current date
//======================================
void Calendar_window::set_pressed_date(){
	int dd = d.day();
	int startday = month_start_day(d.year(),d.month());
	int k=dd+startday-1;
	//set the state of each button to off
	for(int i=0; i<dates.size(); ++i){
		dates[i].set(0);
	}
	//set the color of each label to default
	for(int j=0; j<labels.size(); ++j){
		labels[j].color(maroon);
		labels[j].textcolor(white);
	}
	dates[k].set(1);
	labels[k].color(white);
	labels[k].textcolor(maroon);	
}

//======================================
//clear the number labels on the screen
//======================================
void Calendar_window::clear_month()
{
	for(int i=0; i<labels.size(); ++i){ //run for each column
		stringstream ss;
		ss<<"";
		labels[i].put(ss.str());
	}
}

//======================================
//do all necessary actions to show month on screen
//======================================
void Calendar_window::draw_month()
{
	clear_month();
	//clear_appt();
	int start= month_start_day((d.year()), ((int)d.month()));
	for(int i=0; i<labels.size(); ++i){ //run for each column
		if(i>=(start) && i<(start+days_in_month(d.year(), d.month()))){
			stringstream ss;
			ss<<i+1-(start);
			labels[i].put(ss.str());
		}
		else
			hide_boxes(i);
	}
	set_pressed_date();
	display_appt();
	update_date_text();
	redraw();
}

//======================================
//hide all objects not belonging to a date in the current month
//======================================
void Calendar_window::hide_boxes(int index){
	dates[index].hide();
	labels[index].hide();
	out_text1[index].hide();
	out_text2[index].hide();
	out_text3[index].hide();
	out_text4[index].hide();
}

//======================================
//show all objects previously hidden
//======================================
void Calendar_window::show_all_boxes(int index){
	dates[index].show();
	labels[index].show();
	out_text1[index].show();
	out_text2[index].show();
	out_text3[index].show();
	out_text4[index].show();
}

//======================================
//use ctime to find the start weekday of each month
//======================================
int Calendar_window::month_start_day(int yr, int mth){
	time_t rawtime;
	struct tm * timeinfo;
	
	/* get current timeinfo and modify it to the user's choice */
	time ( &rawtime );
		timeinfo = localtime ( &rawtime );
	timeinfo->tm_year = yr - 1900;
	timeinfo->tm_mon = mth - 1;
	timeinfo->tm_mday = 1;

	/* call mktime: timeinfo->tm_wday will be set */
	mktime ( timeinfo );
	int asdf =timeinfo->tm_wday;
	return asdf;
}

//======================================
//return true when theres a full moon
//======================================
bool Calendar_window::full_moon(int yy, int mm, int dd){
	double c;
	double e;
	double de; //days elapsed
	int b;
	double p;
  
	c = 365.25*yy;
	e = 30.6*mm;
	de = c + e + dd - 694039.09; // find the total days elapsed
	b = de/29.53; // 29.53 is the amount of days in every moon cycle
	p = (de/29.53 - b);
	p = p*29.53 - 29.53/2;
 
	if(p < .5 && p > -.5)
		return true; 
	else 
		return false;
}




//------------------------------------------------------------------------------
