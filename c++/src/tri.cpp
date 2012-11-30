#include "tri.h"

tri::tri(){
	for (int i=0;i<3;i++){
		p[i] = NULL;
		e[i] = NULL;
	}
}

tri::tri(const tri& t){
	for (int i=0;i<3;i++){
		p[i] = t.p[i];
		e[i] = new edge(*t.e[i]);
	}

	n = t.n;
	c = t.c;
}

tri::tri(point& p1, point& p2, point& p3){
	p[0] = &p1;
	p[1] = &p2;
	p[2] = &p3;
	
	e[0] = new edge(p[1],p[2]);
	e[1] = new edge(p[2],p[0]);
	e[2] = new edge(p[0],p[1]);
	
	n = e[2]->getV().cross( -e[1]->getV());
	
	c = (*p[0]+*p[1]+*p[2])/3.;
}

tri::tri(point* p1, point* p2, point* p3){
	p[0] = p1;
	p[1] = p2;
	p[2] = p3;
	
	e[0] = new edge(p[1],p[2]);
	e[1] = new edge(p[2],p[0]);
	e[2] = new edge(p[0],p[1]);
	
	n = e[2]->getV().cross( -e[1]->getV());
	c = (*p[0]+*p[1]+*p[2])/3.;
}

tri::~tri(){
	delete e[0];
	delete e[1];
	delete e[2];
}

tri& tri::operator= (tri const& t){
		// tri do not own their points
	p[0] = t.p[0];
	p[1] = t.p[1];
	p[2] = t.p[2];
	
		// tri own their edges
	e[0] = new edge(*t.e[0]);
	e[1] = new edge(*t.e[1]);
	e[2] = new edge(*t.e[2]);
	
	n = t.n;
	c = t.c;
}

bool tri::hasPoint(const point& oP) const{
	return *p[0] == oP || *p[1] == oP || *p[2] == oP;
}

bool tri::hasEdge(const edge& oE) const{
	return *e[0] == oE || *e[1] == oE || *e[2] == oE;
}

point* tri::getPoint_ptr(const int i) {
	if (i<0 || i>2) {
		std::cout << "Bad Index tri::getPoint_ptr(" << i << ")" << std::endl;
		exit(1);
	}
	return p[i];
}

edge* tri::getEdge_ptr(const int i){
	if (i<0 || i>2) {
		std::cout << "Bad Index tri::getEgde_ptr(" << i << ")" << std::endl;
		exit(1);
	}
	return e[i];
}

int tri::markEdge(edge const& oE){
	for (int i=0;i<3;i++)
		if (*e[i] == oE){
			if (!e[i]->mark())
				return 2;
			return 0;
		}
	return 1;
}

bool tri::unmarkEdge(edge const& oE){
	for (int i=0;i<3;i++)
		if (*e[i] == oE){
			if (!e[i]->unmark())
				return true;
		}
	return false;
}

bool tri::getUnconnected(edge &oE, point &oP){
	for (int i=0;i<3;i++)
		if (!e[i]->isMarked()){
			oE = *e[i];
			oP = *p[i];
			return true;
		}
	
	return false;
}

bool tri::fixN(const point& center){
	if (n * (c - center) < 0.){
		n = -n;
		return true;
	}
	return false;
}

double tri::calcVolume(const point& oP){
	return fabs( (*p[0]-oP) * (*p[1]-oP).cross(*p[2]-oP));
}

bool tri::isInside(const point& oP){
	if ( (oP - c) * n < 0.)
		return true;
	return false;
}

bool operator== (const tri& t1, const tri& t2){
	return t1.hasPoint(*t2.p[0]) && t1.hasPoint(*t2.p[1]) && t1.hasPoint(*t2.p[2]);
}

std::ostream& operator<< (std::ostream &outS, const tri &t) {
	outS << "{" << *t.p[0] << ", " << *t.p[1] << ", " << *t.p[2] << "} (" 
	<< t.e[0]->isMarked() << "," << t.e[0]->isMarked() << "," << t.e[2]->isMarked() << ")";
	return outS;
}

tri4::tri4(){
	for (int i=0;i<3;i++)
		p4[i] = NULL;
}

tri4::tri4(const tri4& t){
	for (int i=0;i<3;i++)
		p4[i] = t.p4[i];
}

tri4::tri4(point4* p1, point4* p2, point4* p3){
	p4[0] = p1;
	p4[1] = p2;
	p4[2] = p3;
}

tri4::~tri4(){
		// noop
}

tri4& tri4::operator= (tri4 const& t){
		// tri do not own their points
	p4[0] = t.p4[0];
	p4[1] = t.p4[1];
	p4[2] = t.p4[2];
}

void tri4::isValid() const {
	if (p4[0]==NULL || p4[1]==NULL || p4[2]==NULL) {
		std::cout << " tri4::isValid() failure " << *this << std::endl;
		exit(1);
	}		
}

bool tri4::hasPoint(const point4& oP) const{
	isValid();
	return *p4[0] == oP || *p4[1] == oP || *p4[2] == oP;
}

void tri4::setPoint(int i, point4* p_ptr) {
	if (i<0 || i>2) 
		p4[i]=p_ptr; 
	else {
		std::cout << "Invalid Index ("<<i<<") to tri4::setPoint() " << std::endl;
		exit(1);
	} 
}

point4 tri4::getVolumeVector(const point4& center, const point4& projVec) {
	isValid();
	point4 vVec = (*p4[0]-center).cross((*p4[1]-center),(*p4[2]-center))/6.;
	
		//	std::cout << getCenter() << std::endl << center << std::endl << projVec * vVec << std::endl;
	if (projVec * vVec < 0.)
		return -vVec;
	return vVec;
}

point4 tri4::getCenter() {
	return (*p4[0] + *p4[1] + *p4[2])/3.;
}

bool operator== (const tri4& t1, const tri4& t2){
	t1.isValid();
	t2.isValid();
	return t1.hasPoint(*t2.p4[0]) && t1.hasPoint(*t2.p4[1]) && t1.hasPoint(*t2.p4[2]);
}

std::ostream& operator<< (std::ostream &outS, const tri4 &t) {
	outS << "{" << *t.p4[0] << ", " << *t.p4[1] << ", " << *t.p4[2] << "}";
	return outS;
}