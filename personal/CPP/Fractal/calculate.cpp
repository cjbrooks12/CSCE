using namespace fractal;

namespace fractal {

	Position cal_pos(Position p) {
		int x, y;

		x = 2*p.x();
		y = 2*p.y();

		p.set_position(x,y);

		return p;
	}

	Color cal_color(Color c) {
		return c;
	}

	Density cal_den(Density d) {
		return d;
	}
}
