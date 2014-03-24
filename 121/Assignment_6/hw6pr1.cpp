#include "std_lib_facilities_3.h"
#include "Simple_window.h"
#include "Graph.h"

void draw_board( ) {
	Simple_window win(Point(150,150),470,400,"Checkers");
	Color moss_green(fl_rgb_color(85,136,34));
	Color lemon_chiffon(fl_rgb_color(255,238,187));
	
	Vector_ref<Rectangle> board;
	Vector_ref<Ellipse> bottom;
	Vector_ref<Ellipse> top;
	Vector_ref<Ellipse> ring;
	
	
//Draw the board
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {
			board.push_back(new Rectangle(Point(i*50, j*50), 50, 50));
			if(i%2 == 0 && j%2 == 0 || i%2 != 0 && j%2 != 0) {
				board[board.size()-1].set_fill_color(moss_green);
			}
			if(i%2 != 0 && j%2 ==0 || i%2 == 0 && j%2 != 0) {
				board[board.size()-1].set_fill_color(lemon_chiffon);
			}
			win.attach(board[board.size()-1]);
		}
	}
	
//Draw the checker pieces	
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {
			if(i%2==0 && j%2==0 || i%2!=0 && j%2!=0) {
			
				if(j < 3) { //Draw red pieces for top three rows
					bottom.push_back(new Ellipse(Point(i*50 + 25, j*50 + 25), 6, 3));
					bottom[bottom.size()-1].set_style(Line_style(Line_style::solid, 25));
					bottom[bottom.size()-1].set_color(Color::black);
					win.attach(bottom[bottom.size()-1]);
					
					top.push_back(new Ellipse(Point(i*50 + 25, j*50 + 20), 5, 2));
					top[top.size()-1].set_style(Line_style(Line_style::solid, 25));
					top[top.size()-1].set_color(Color::red);
					win.attach(top[top.size()-1]);
					
					ring.push_back(new Ellipse(Point(i*50 + 25, j*50 + 20), 18, 14)) ;
					ring[ring.size()-1].set_style(Line_style(Line_style::solid, 1));
					ring[ring.size()-1].set_color(Color::black);
					win.attach(ring[ring.size()-1]);
				}
				if(j > 4) { //Draw white pieces for bottom three rows
					bottom.push_back(new Ellipse(Point(i*50 + 25, j*50 + 25), 6, 3));
					bottom[bottom.size()-1].set_style(Line_style(Line_style::solid, 25));
					bottom[bottom.size()-1].set_color(Color::black);
					win.attach(bottom[bottom.size()-1]);
					
					top.push_back(new Ellipse(Point(i*50 + 25, j*50 + 20), 5, 2));
					top[top.size()-1].set_style(Line_style(Line_style::solid, 25));
					top[top.size()-1].set_color(Color::white);
					win.attach(top[top.size()-1]);
					
					ring.push_back(new Ellipse(Point(i*50 + 25, j*50 + 20), 18, 14)) ;
					ring[ring.size()-1].set_style(Line_style(Line_style::solid, 1));
					ring[ring.size()-1].set_color(Color::black);
					win.attach(ring[ring.size()-1]);
				}
			}
		}
	}
	
	win.wait_for_button();
	return;
}

int main()
try {
	draw_board();
	
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
