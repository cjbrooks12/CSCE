//#include "std_lib_facilities_3.h"
#include "Calendar_window.h"
#include "Popup_window.h"

int main(){
	Popup_window popup(Point(0,0),800,600,"splash");
	popup.wait_for_button();
	int year = popup.year();
	int month = popup.month();
	string filename = popup.get_filename();
	if(popup.is_button_pushed()==true){
		Calendar_window win1(Point(0,0),800,600,"splash",year,month,filename);
		win1.show_window();
	}
	}
