#ifndef __CPOINT_h_INCLUDE
#define __CPOINT_h_INCLUDE

#include <iostream>
#include <cmath>

class point {
private:
	double x[3];
	static int sortIndex;
public:
	point();
	point(const point &p);
	point(double mX, double y, double z);
	~point();
	
	point& operator=  (point const& p);
	point& operator+= (point const& p);
	point& operator*= (const double &s);
	point& operator/= (const double &s);
	double operator() (const int i) const;
	point cross(const point &p);
	void makeUnit();
	double getX(const int i) const;
	void setX(const int i, const double v);
	static void setSortIndex(const int i);
	inline double mag() const {return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);}
	bool isZero();
	
	friend bool operator== (const point &p1, const point &p2);
	friend bool operator!= (const point &p1, const point &p2);
	friend bool operator<  (const point &p1, const point &p2);
	friend point operator+ (const point &p1, const point &p2);
	friend point operator- (const point &p1, const point &p2);
	friend point operator- (const point &p);
	friend double operator* (const point &p1, const point &p2);
	friend point operator* (const double &s, const point &p);
	friend point operator* (const point &p, const double &s);
	friend point operator/ (const point &p, const double &s);

	
	friend std::ostream& operator<< (std::ostream &outS, const point &p);
};

class point4 {
private:
	double x[4];
	static int sortIndex;
public:
	point4();
	point4(const point4 &p);
	point4(double t, double mX, double y, double z);
	~point4();
	
	point4& operator=  (point4 const& p);
	point4& operator+= (point4 const& p);
	point4& operator-= (point4 const& p);
	point4& operator*= (const double &s);
	point4& operator/= (const double &s);
	double operator() (const int i) const;
	
	point4 cross(const point4 &p1, const point4 &p2);
	void makeUnit();
	double getX(const int i) const;
	void setX(const int i, const double v);
	inline void makeZero(){x[0]=0.;x[1]=0.;x[2]=0.;x[3]=0.;}
	static void setSortIndex(const int i);
	inline double mag() const {return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]+x[3]*x[3]);}
	inline void lower() {x[1]=-x[1];x[2]=-x[2];x[3]=-x[3];}
	inline void raise() {lower();}
	bool isZero();
	void jiggle();
	
	friend bool operator== (const point4 &p1, const point4 &p2);
	friend bool operator!= (const point4 &p1, const point4 &p2);
	friend bool operator<  (const point4 &p1, const point4 &p2);
	friend point4 operator+ (const point4 &p1, const point4 &p2);
	friend point4 operator- (const point4 &p1, const point4 &p2);
	friend point4 operator- (const point4 &p);
	friend double operator* (const point4 &p1, const point4 &p2);
	friend point4 operator* (const double &s, const point4 &p);
	friend point4 operator* (const point4 &p, const double &s);
	friend point4 operator/ (const point4 &p, const double &s);
	
	friend std::ostream& operator<< (std::ostream &outS, const point4 &p);
};
#endif