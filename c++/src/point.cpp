#include <iostream>
#include <fstream>
#include "point.h"

point::point(){
	x[0] = 0.; 
	x[1] = 0.; 
	x[2] = 0.;
}

point::point(const point& p){
	x[0] = p.x[0];
	x[1] = p.x[1];
	x[2] = p.x[2];
}

point::point(double mX, double y, double z){
	x[0] = mX;
	x[1] = y;
	x[2] = z;
}

point::~point(){
	// noop
}

double point::operator() (int i) const {
	if (i<0 || i>2){
		std::cout << "Invalid Access to point::(" << i << ") "  << *this << std::endl;
		exit(1);
	}
	return x[i];
}

point& point::operator= (const point &p){
	if (this == &p)
		return *this;
	
	x[0] = p.x[0];
	x[1] = p.x[1];
	x[2] = p.x[2];
	return *this;
}

point& point::operator+= (const point &p){
	x[0] += p.x[0];
	x[1] += p.x[1];
	x[2] += p.x[2];
	return *this;
}

point& point::operator*= (const double &s){
	x[0] = s*x[0];
	x[1] = s*x[1];
	x[2] = s*x[2];
	return *this;
}

point& point::operator/= (const double &s){
	if (s==0.){
		std::cout << "Divide by zero at " << *this << std::endl;
		exit(1);
	}
	
	x[0] = x[0]/s;
	x[1] = x[1]/s;
	x[2] = x[2]/s;
	
	return *this;
}

point point::cross(const point& p){
	return point(x[1]*p.x[2]-x[2]*p.x[1],
				 x[2]*p.x[0]-x[0]*p.x[2],
				 x[0]*p.x[1]-x[1]*p.x[0]);
}

void point::makeUnit(){
	if (!isZero()) *this /= mag();
}

bool point::isZero(){
	for (int i=0;i<3;i++)
		if (fabs(x[i]) > 1E-20) 
			return false;
	return true;
}

double point::getX(const int i) const{
	if (i<0 || i>2){
		std::cout << "Invalid Access point::getX("<<i<<") " << *this << std::endl;
		exit(1);
	}
	return x[i];
}

void point::setX(const int i, const double v) {
	if (i<0 || i>2) {
		std::cout << "Invalid Access point::setX("<<i<<","<<v<<") " << *this << std::endl;
		exit(1);
	}
	x[i] = v;
}

void point::setSortIndex(const int i) {
	if (i<0 || i>2){
		std::cout << "Invalid Index point::setSortIndex("<<i<<") " << std::endl;
		exit(1);
	}
	sortIndex = i;
}

bool operator== (const point &p1, const point &p2){
	return p1.x[0]==p2.x[0] && p1.x[1]==p2.x[1] && p1.x[2]==p2.x[2];
}

bool operator!= (const point &p1, const point &p2){
	return p1.x[0]!=p2.x[0] || p1.x[1]!=p2.x[1] || p1.x[2]!=p2.x[2];
}	

bool operator<  (const point &p1, const point &p2){
	return p1(point::sortIndex) < p2(point::sortIndex);
}

point operator+ (const point &p1, const point &p2){
	return point(p1.x[0]+p2.x[0],p1.x[1]+p2.x[1],p1.x[2]+p2.x[2]);
}

point operator- (const point &p1, const point &p2){
	return point(p1.x[0]-p2.x[0],p1.x[1]-p2.x[1],p1.x[2]-p2.x[2]);
}

point operator- (const point &p){
	return point(-p(0),-p(1),-p(2));
}

double operator* (const point &p1, const point &p2){
	return (p1.x[0]*p2.x[0]+p1.x[1]*p2.x[1]+p1.x[2]*p2.x[2]);
}

point operator* (const double &s, const point &p){
	return point(s*p.x[0],s*p.x[1],s*p.x[2]);
}

point operator* (const point &p, const double &s){
	return point(s*p.x[0],s*p.x[1],s*p.x[2]);
}

point operator/ (const point &p, const double &s){
	if (s==0.){
		std::cout << "Divide by zero at " << p << std::endl;
		exit(1);
	}
		
	return point(p.x[0]/s,p.x[1]/s,p.x[2]/s);
}

std::ostream& operator<< (std::ostream &outS, const point &p) {
	outS << "(" << p.x[0] << ", " << p.x[1] << ", " << p.x[2] << ")";
	return outS;
}

int point::sortIndex=0;

point4::point4(){
	x[0] = 0.; x[1] = 0.; x[2] = 0.; x[3] = 0.;
}

point4::point4(const point4& p){
	x[0] = p.x[0]; x[1] = p.x[1]; x[2] = p.x[2]; x[3] = p.x[3];
}

point4::point4(double t, double mX, double y, double z){
	x[0] = t;
	x[1] = mX;
	x[2] = y;
	x[3] = z;
}

point4::~point4(){
		// noop
}

double point4::operator() (int i) const {
	if (i<0 || i>3) {
		std::cout << "Invalid Access to point::(" << i << ") "  << *this << std::endl;
		exit(1);
	}
	return x[i];
}

point4& point4::operator= (const point4 &p){
	if (this == &p)
		return *this;
	
	x[0] = p.x[0];
	x[1] = p.x[1];
	x[2] = p.x[2];
	x[3] = p.x[3];
	return *this;
}

point4& point4::operator+= (const point4 &p){
	x[0] += p.x[0];
	x[1] += p.x[1];
	x[2] += p.x[2];
	x[3] += p.x[3];
	return *this;
}

point4& point4::operator-= (const point4 &p){
	x[0] -= p.x[0];
	x[1] -= p.x[1];
	x[2] -= p.x[2];
	x[3] -= p.x[3];
	return *this;
}

point4& point4::operator*= (const double &s){
	x[0] = s*x[0];
	x[1] = s*x[1];
	x[2] = s*x[2];
	x[3] = s*x[3];
	return *this;
}

point4& point4::operator/= (const double &s){
	if (s==0.){
		std::cout << "point4::operator/= : Divide by zero at " << *this << std::endl;
		exit(1);
	}
	
	x[0] = x[0]/s;
	x[1] = x[1]/s;
	x[2] = x[2]/s;
	x[3] = x[3]/s;
	
	return *this;
}

point4 point4::cross(const point4& p1, const point4& p2){
	/*
	std::cout << *this << std::endl << p1 << std::endl << p2 << std::endl << std::endl;
	
	std::cout << "cross[0] = "<< x[1]*(p1(2)*p2(3)-p1(3)*p2(2)) << " " 
	<< x[2]*(p1(3)*p2(1)-p1(1)*p2(3)) << " " << x[3]*(p1(1)*p2(2)-p1(2)*p2(1)) << std::endl;
	
	std::cout << "cross[1] = "<< x[2]*(p1(3)*p2(0)-p1(0)*p2(3)) << " " 
	<< x[3]*(p1(0)*p2(2)-p1(2)*p2(0)) << " " << x[0]*(p1(2)*p2(3)-p1(3)*p2(2)) << std::endl;
	
	std::cout << "cross[2] = "<< x[3]*(p1(0)*p2(1)-p1(1)*p2(0)) << " " 
	<< x[0]*(p1(1)*p2(3)-p1(3)*p2(1)) << " " << x[1]*(p1(3)*p2(0)-p1(0)*p2(3)) << std::endl;
	
	std::cout << "cross[3] = "<< x[0]*(p1(1)*p2(2)-p1(2)*p2(1)) << " " 
	<< x[1]*(p1(2)*p2(0)-p1(0)*p2(2)) << " " << x[2]*(p1(0)*p2(1)-p1(1)*p2(0)) << std::endl;
	*/
	
	return point4( x[1]*(p1(2)*p2(3)-p1(3)*p2(2))
				  +x[2]*(p1(3)*p2(1)-p1(1)*p2(3))
				  +x[3]*(p1(1)*p2(2)-p1(2)*p2(1)),
		   
				  -x[0]*(p1(2)*p2(3)-p1(3)*p2(2))
				  -x[2]*(p1(3)*p2(0)-p1(0)*p2(3))
				  -x[3]*(p1(0)*p2(2)-p1(2)*p2(0)),
		   
				   x[0]*(p1(1)*p2(3)-p1(3)*p2(1))
				  +x[1]*(p1(3)*p2(0)-p1(0)*p2(3))
				  +x[3]*(p1(0)*p2(1)-p1(1)*p2(0)),
				  
				  -x[0]*(p1(1)*p2(2)-p1(2)*p2(1))
				  -x[1]*(p1(2)*p2(0)-p1(0)*p2(2))
				  -x[2]*(p1(0)*p2(1)-p1(1)*p2(0)) );
}

void point4::makeUnit(){
		//std::cout << "makeUnit : " << *this << " /= " << mag() << std::endl;
	if (!isZero())
		*this /= mag();
}

double point4::getX(const int i) const{
	if (i<0 || i>3){
		std::cout << "Invalid Access point4::getX("<<i<<") " << *this << std::endl;
		exit(1);
	}
	return x[i];
}

void point4::setX(const int i, const double v){
	if (i<0 || i>3){
		std::cout << "Invalid Access point4::setX("<<i<<") " << *this << std::endl;
		exit(1);
	}
	x[i]=v;
}

void point4::setSortIndex(const int i) {
	if (i<0 || i>3){
		std::cout << "Invalid Index point::setSortIndex("<<i<<") " << std::endl;
		exit(1);
	}
	sortIndex = i;
}

bool point4::isZero(){
	for (int i=0;i<4;i++)
		if (fabs(x[i]) > 1E-20) 
			return false;
	return true;
}

void point4::jiggle(){
	for (int i=0;i<4;i++) 
		x[i] += (1.E-10)*((double)rand()/((double)RAND_MAX));
}

bool operator== (const point4 &p1, const point4 &p2){
	return p1.x[0]==p2.x[0] && p1.x[1]==p2.x[1] && p1.x[2]==p2.x[2] && p1.x[3]==p2.x[3];
}

bool operator!= (const point4 &p1, const point4 &p2){
	return p1.x[0]!=p2.x[0] || p1.x[1]!=p2.x[1] || p1.x[2]!=p2.x[2] || p1.x[3]!=p2.x[3];
}	

bool operator<  (const point4 &p1, const point4 &p2){
	return p1(point4::sortIndex) < p2(point4::sortIndex);
}

point4 operator+ (const point4 &p1, const point4 &p2){
	return point4(p1.x[0]+p2.x[0],p1.x[1]+p2.x[1],p1.x[2]+p2.x[2],p1.x[3]+p2.x[3]);
}

point4 operator- (const point4 &p1, const point4 &p2){
	return point4(p1.x[0]-p2.x[0],p1.x[1]-p2.x[1],p1.x[2]-p2.x[2],p1.x[3]-p2.x[3]);
}

point4 operator- (const point4 &p){
	return point4(-p(0),-p(1),-p(2),-p(3));
}

double operator* (const point4 &p1, const point4 &p2){
	return p1.x[0]*p2.x[0]+p1.x[1]*p2.x[1]+p1.x[2]*p2.x[2]+p1.x[3]*p2.x[3];
}

point4 operator* (const double &s, const point4 &p){
	return point4(s*p.x[0],s*p.x[1],s*p.x[2],s*p.x[3]);
}

point4 operator* (const point4 &p, const double &s){
	return point4(s*p.x[0],s*p.x[1],s*p.x[2],s*p.x[3]);
}

point4 operator/ (const point4 &p, const double &s){
	if (s==0.){
		std::cout << "point4::operator/ : Divide by zero at " << p << std::endl;
		exit(1);
	}
	
	return point4(p.x[0]/s,p.x[1]/s,p.x[2]/s,p.x[3]/s);
}

std::ostream& operator<< (std::ostream &outS, const point4 &p) {
	outS << "(" << p.x[0] << ", " << p.x[1] << ", " << p.x[2] << ", " << p.x[3] << ")";
	return outS;
}

int point4::sortIndex=0;