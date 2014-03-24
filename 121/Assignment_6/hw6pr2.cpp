#include "std_lib_facilities_3.h"
#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
struct Parallelogram : Closed_polyline {
	Parallelogram(Point tl, Point tr, Point bl)
	{
		Point br(bl.x + (tr.x - tl.x), tr.y + (bl.y - tl.y)); //Calculate position of fourth point
		
		add(tl);
		add(tr);
		add(br);
		add(bl);
	}
	
	void draw_lines() const;
	
};

void Parallelogram::draw_lines() const
{
	Closed_polyline::draw_lines();
}

}

void draw_parallelogram() {
	Simple_window win(Point(150,150),425, 425,"Parallelogram");
	
	Point tl(100,50); //tl
	Point tr(300,50); //tr
	Point bl(150,150); //bl
	Color c = Color::red;
	Line_style ls = Line_style(Line_style::solid, 4);
	
	//Parallelogram One
	Parallelogram one(tl, tr, bl);
	one.set_style(ls);
	one.set_fill_color(c);
	win.attach(one);
	
	//Parallelogram Two
	Parallelogram two(bl, Point(350, 150), Point(75, 350));
	two.set_style(ls));
	two.set_fill_color(Color::blue);
	win.attach(two);
	
	//Parallelogram Three
	Parallelogram three(bl, Point(75,350), tl);
	three.set_style(ls);
	three.set_fill_color(Color::magenta);
	win.attach(three);
	
	win.wait_for_button();
	return;
}

int main()
try {
	draw_parallelogram();
	
	return 0;
}
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}
