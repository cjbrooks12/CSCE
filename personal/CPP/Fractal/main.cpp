/*
Fractal generator outline
* 	Start with a window. Divide it into a grid using for loops, so that each
* 		pixel will be plotted. Test that each pixel is plotted in the window
* 		by iterating through and plotting a point with a given color in each
* 		pixel. Try making the color change slightly with every so many pixels
* 		so that I can be sure each one has been plotted correctly.
*
* 	Make a class that create a fractal recursion possible out of a point, along
* 		with a color. It will have two parts: a point(plotted from FLTK) and a
* 		color. Make a function that will create a point at the top corner of the
* 		window, then pass it through a single math function. Take this and plot
* 		it, then pass the result through the math function again. Do this a
* 		specified number of times. In the same steps, pass the color variable to
* 		a function that will run it through a math function to determine the
* 		color at a specific point. after each iteration, plot the point with
* 		the color calculated color value. Then start at the next pixel in the
* 		image and do the same process. Repeat until every starting pixel in the
* 		window has been calculated. Make it so that any time a pixel would be
* 		plotted over top another previousy plotted one, use the new value. Also
* 		find out how to use the older value, and see if there is any kind of
* 		happy medium between the two to yield best results.
*
* 	Make a function to apply to the position of each pixel, and another for the
* 		color of the pixel.
*
* 	The above is all for an IFS fractal. Also implement a time-escape fractal,
* 		and see if it matter whether the numbers are plotted re vs im, or if
* 		simple x vs y will suffice. Use same general principles, but plot a
* 		point only once, then iterate to find if it diverges. If it diverges,
* 		the number of iterations it took to diverge will determine its color. Do
* 		this for every point on the grid. Then do the entire thing again with
* 		the resultant points; this will refine the fractal. Keep doing this a
* 		specified number of times.
*
* 	Include support for plugins. Make them compiled .dll files, so that it is
* 		compatible with Apophysis plugins.
*
*
*/

#include "fractal.cpp"

int main()
try {

	int width = 9;
	int height = 5;

	Vector<Position> pos_vec;
	Position p, y;
	for(int j=0; j<height; j++) {
		for(int i=0; i<width; i++) {
			p.set_position(i,j);
			y = cal_pos(p);

			pos_vec.push_back(y);
		}
	}
	for(int j=0; j<height; j++) {
		for(int i=0; i<width; i++) {
			cout << pos_vec[(width * j) + i];
		}
		cout << endl;
	}
	return 0;
}
catch(exception& e){
	cerr << "error: " << e.what() << endl;
}
catch(...) {
	cerr << "something went wrong\n";
}
