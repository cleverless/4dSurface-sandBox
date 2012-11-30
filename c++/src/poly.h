#ifndef __INCLUDE_POLYHEDRON_h__
#define __INCLUDE_POLYHEDRON_h__

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "point.h"
#include "tri.h"

class poly{
protected:
	std::vector<point> points;
	std::vector<tri> surface;
	point center;
public:
	poly();
	~poly();
	
	point makePoint();
	void makePoints(int i);
	inline void pushPoint(double x, double y, double z) {points.push_back(point(x,y,z));}
	inline void makePoints(int i, int j){makePoints(std::min(i,j) + (rand()%((1+std::max(i,j)-std::min(i,j)))));}
	std::vector<point> getPoints(){return points;}
	std::vector<tri> getSurface(){return surface;}
	
	bool isSurfaceOpen();
	bool markEdges();
	void unmarkEdges();
	bool giftwrap();
	
	double getConvexVolume();
	bool calcCenter();
	bool fixN();
	
	void sortPoints(int i);
	
	friend std::ostream& operator<< (std::ostream &outS, const poly &p);	
};

class poly4 : public poly {
protected:
	std::vector<point4> points4;
	point4 center4;
	point4 projVec;
	point4 basis[3];
public:
	poly4();
	~poly4();
	
	inline void addPoint(point4 p) {points4.push_back(p); /*std::cout << "adding: "<< p << std::endl;*/}
	inline int size(){return points4.size();}
	inline void setNormal(point4 &p) {projVec = p; projVec.makeUnit();}
	
	void jigglePoints();
	void makePoints3();
	void calcCenter4();
	inline point4 getCenter4(){return center4;}
	
	point4 getVolumeVector();
};

#endif //__INCLUDE_POLYHEDRON_h__