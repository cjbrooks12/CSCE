
#include "Popup_window.h"

using namespace Graph_lib;


//------------------------------------------------------------------------------

Popup_window::Popup_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    splash(Point(0,0),"splashimage.jpg"),
    appt_text(Point(270,500),"enterapptfile.jpg"),
    next_button(Point(520,550), 70, 20, "Next", cb_next),
    year_input(Point(449,450), 50, 20,""),
    month_input(Point(310,450), 50, 20,""),
    filename_input(Point(305,550), 200, 20,""),
    error_output(Point(305,575), 200, 20,""),
    button_pushed(false)
{
	attach(splash);
	splash.set_mask(Point(0,0),800,450);
	attach(appt_text);
	attach(next_button);
	attach(month_input);
	attach(year_input);
	attach(filename_input);
	attach(error_output);
	set_color(fl_rgb_color(80,0,0));
	error_output.set_box(FL_NO_BOX);
	error_output.textcolor(Color::white);
}

//------------------------------------------------------------------------------

bool Popup_window::wait_for_button(){
	Fl::run();
}

//===================================================
//check for file existence
//===================================================
bool Popup_window::fexists(string filename)
{
  ifstream ifile(filename);
  return ifile;
}

//===================================================
//set variable
//===================================================
void Popup_window::get_info(){
	y = year_input.get_int();
	m = month_input.get_int();
	filename = filename_input.get_string();
}

//===================================================
//callback for next button
//===================================================
void Popup_window::cb_next(Address, Address pw)
// call Simple_window::next() for the window located at pw
{  
    reference_to<Popup_window>(pw).next();    
}
void Popup_window::next()
{
	get_info();
	stringstream ss;
	if(fexists(filename) && y>0 && m>0 && m<=12){
		
		
		button_pushed = true;
		hide();
		//Calendar_window win1(Point(0,0),800,600,"shit",y,m,filename);
		//win1.show_window();
	}
	else if(!fexists(filename)){
			ss<<"file not found";
			error_output.put(ss.str());
		}
	else if(m<=0 || m>13 || y<=0){
			ss<<"invalid date";
			error_output.put(ss.str());
			}
			redraw();
}

//------------------------------------------------------------------------------
