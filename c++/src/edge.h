#ifndef __CEDGE_h_INCLUDE__
#define __CEDGE_h_INCLUDE__
#include <iostream>
#include "point.h"

class edge{
private:
	point* p[2]; // pointer to points defining edge
	point v;     // vector from p[0] to p[1]
	bool inSurf; // true is edge is assigned to two tri
public:
	edge();
	edge(edge &e);
	edge(point &p1, point &p2);
	edge(point* p1, point* p2);
	~edge();
	
	edge& operator= (edge const& e);
	point& operator() (const int i) const;
	
	inline bool hasPoint(const point &oP){return *(p[0])==oP || *(p[1])==oP;}
	inline bool hasNoPoint(const point &oP){return *(p[0])!=oP && *(p[1])!=oP;}
	inline point getV(){return v;}
	bool unmark();
	bool mark();
	inline bool isMarked(){return inSurf;}
	
	friend bool operator== (const edge &e1, const edge &e2);
	friend std::ostream& operator<< (std::ostream &outS, const edge &e);
};

#endif // __CEDGE_h_INCLUDE__