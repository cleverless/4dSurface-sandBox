#include <iostream>
#include <vector>
	//#include <random>
#include <ctime>
#include "point.h"
#include "cube.h"

int main(int argc, const char * argv []) {
	srand(time(0));
	
		//	cube4 c;
		//	c.makeCells();
		//	std::cout << "mVV = " << c.getVolumeVector() << std::endl;
	poly p;
	p.pushPoint(0.330426, 3.9808, -3.40833);
	p.pushPoint(0.332253, 4.00442, -3.40498);
	p.pushPoint(0.329124, 3.99671, -3.31795);
	p.pushPoint(0.47175, 4.0034, -3.22532);
	p.pushPoint(0.474044, 3.97272, -3.40263);
	p.pushPoint(0.471899, 4.00514, -3.22594);
	p.pushPoint(0.477381, 4.01864, -3.39641);
	p.pushPoint(0.464567, 4.0041, -3.22447);
	
	p.sortPoints(0);
	std::cout << p << std::endl;
	
	p.giftwrap();
	std::cout << p << std::endl;
	
	return 0;
}