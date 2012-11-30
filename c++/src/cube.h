#ifndef __CUBE_h_INCLUDE__
#define __CUBE_h_INCLUDE__

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "poly.h"
	//#include "CCell.h"

class cell {
private:
	double e;
	point4 x;
		//	CCell *oCell;
public:
	inline cell(){e=0.; /*oCell=NULL;*/}
	inline cell(point4& p){x=p; e=0.;}
	inline ~cell(){/*noop*/}
	
	inline double getE() const {return e;}
	inline void setE(const double mE){e=mE;}
	inline point4 getX() const {return x;}
	inline void setX(const point4& mX){x=mX;}
		//	void setCell(CCell* oC);
		//	inline CCell* getCCell() {return oCell;}
	
	friend std::ostream& operator<< (std::ostream &outS, const cell &c);
};

class tetra4{
private:
	cell* cells[2][4];
	poly4 mPoly;
	static double fosE;
	
public:
	tetra4();
	tetra4(tetra4& t);
	~tetra4();
	
	void setCell(int i, int j, cell* c_ptr);
	inline void setFosE(double e) {fosE=e;}
	void findSurf(cell* c1, cell* c2);
	void makeCells();
	void findSurfacePoints();
	bool hasSurface();
	bool isValid() const;
	point4 getVolumeVector(point4 &center);
	point4 pointAboveFOS();
	
	friend std::ostream& operator<< (std::ostream &outS, const tetra4 &t);
};

class cube4{
private:
	cell* cells[2][2][2][2];
	tetra4 tetras[6];
	static double fosE;
	
public:
	cube4();
	cube4(cube4& c);
	~cube4();
	
	void setCell(int i, int j, int k, int m, cell* c_ptr);
	bool isValid();
	bool hasSurface();
	void findSurf(cell* c1, cell* c2);
	void findSurfacePoints();
	void makeCells();
	void makeTetras();
	point4 getVolumeVector(point4 &rCenter);
	
		//	void setCells(CCell* oCells[16]);
	bool freeze(double foPoint[4], double surfVec[4]);
	inline void setFosE(double e) {fosE=e; tetra4 t; t.setFosE(e);}
};

#endif // __CUBE_h_INCLUDE__