#include "edge.h"

	// edge class does not handle the memory
	// associated with the points it contains
	// as such default constructor will not 
	// fill the point pointer array
edge::edge(){
	p[0] = NULL;
	p[1] = NULL;
		//	v = p[1] - p[0];
	inSurf = false;
}

edge::edge(edge &e){
	p[0] = e.p[0]; 
	p[1] = e.p[1];
	v = e.v;
	inSurf = e.inSurf;
	
}

edge::edge(point &p1, point &p2){
	p[0] = &p1;
	p[1] = &p2;
	v = *p[1] - *p[0];
	inSurf = false;
}

edge::edge(point* p1, point* p2){
	p[0] = p1;
	p[1] = p2;
	v = *p[1] - *p[0];
	inSurf = false;
}

edge::~edge(){
	// noop
}

edge& edge::operator= (edge const& e){
	if (this == &e)
		return *this;
	
		//p[0] = &e(0);
		//p[1] = &e(1);
	p[0] = e.p[0]; 
	p[1] = e.p[1];
	v = e.v;
	inSurf = e.inSurf;
	return *this;
}

point& edge::operator() (int i) const{
	if (i!=0 && i!=1){
		std::cout << "Invalid Access to edge::(" << i << ") "  << *this << std::endl;
		exit(1);
	}
	return *p[i];
}

bool edge::mark() {
	if (inSurf)
		return false;
	inSurf = true;	
	return true;
}

bool edge::unmark() {
	if (!inSurf) return false;
	
	std::cout << "edge::unmark() : " << *this << std::endl;
	inSurf = false;
	return true;
}

bool operator== (const edge &e1, const edge &e2){
	return (e1(0)==e2(0) && e1(1)==e2(1)) || (e1(0)==e2(1) && e1(1)==e2(0));
}

std::ostream& operator<< (std::ostream &outS, const edge &e){
	outS << "[" << e(0) << ", " << e(1) << "] ";// << e.inSurf;
	return outS;
}