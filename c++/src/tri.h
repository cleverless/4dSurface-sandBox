#ifndef __CTRI_h_INCLUDE__
#define __CTRI_h_INCLUDE__

#include <cmath>
#include <iostream>

#include "point.h"
#include "edge.h"

class tri{
private:
	point* p[3]; // pointers to points
	edge* e[3];  // edge opposing point p
	point n;     // cell normal - direction arbitrary until fixN() call
	point c;     // cell center
public:
	tri();
	tri(const tri& t);
	tri(point& p1, point& p2, point& p3);
	tri(point* p1, point* p2, point* p3);
	~tri();
	
	tri& operator= (tri const& t);
	friend bool operator== (const tri& t1, const tri& t2);
	
	inline void invalidEdge(const edge& e){std::cout << "Invalid edge passed to tri::tri() : " << e; exit(1);}
	bool hasPoint(const point& oP) const;
	bool hasEdge(const edge& oE) const;
	point* getPoint_ptr(const int i);
	edge* getEdge_ptr(const int i);
	int markEdge(const edge& oE);
	bool unmarkEdge(const edge& oE);
	bool getUnconnected(edge &oE, point &oP);
	bool fixN(const point& center);
	double calcVolume(const point& oP);
	bool isInside(const point& oP);
	
	friend std::ostream& operator<< (std::ostream &outS, const tri& t);
};

	// triangle in 4-space
	// used by poly4 to calculate volumes
class tri4 {
private:
	point4* p4[3];
	void isValid() const;
public:
	tri4();
	tri4(const tri4& t4);
	tri4(point4* p1, point4* p2, point4* p3);
	~tri4();
	
	tri4& operator= (tri4 const& t4);
	
	bool hasPoint(const point4& oP) const;
	void setPoint(int i, point4* p_ptr);
	point4 getVolumeVector(const point4& center, const point4& projVec);
	point4 getCenter();
	
	friend bool operator== (const tri4& t1, const tri4& t2);
	friend std::ostream& operator<< (std::ostream &outS, const tri4& t);
};

#endif // __CTRI_h_INCLUDE__