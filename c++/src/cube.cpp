#include "cube.h"

std::ostream& operator<< (std::ostream &outS, const cell &c){
	outS << c.x << " : " << c.e;
	return outS;
}
/*
void cell::setCell(CCell* oC){
	if (oC == NULL){
		std::cout << "cell::setCell passes bogus cell" << std::endl;
		exit(1);
	}
	
	oCell=oC;
	for (int i=0;i<4;i++)
		x.setX(i, oCell->getX(i));
	
	e = oCell->getE();
}
*/
tetra4::tetra4() {
	for (int i=0;i<2;i++)
		for (int m=0;m<4;m++)
			cells[i][m] = NULL;
}

tetra4::tetra4(tetra4& t) {
	for (int i=0;i<2;i++)
		for (int j=0;j<4;j++)
			cells[i][j] = t.cells[i][j];
	
}

tetra4::~tetra4() {
		//noop
}

void tetra4::setCell(int i, int j, cell* c_ptr) {
	if (i<0 || 1<i || j<0 || 3<j){
		std::cout << "Invalid call to tetra4::setCell("<<i<<","<<j<<") " << std::endl;
		exit(1);
	}
	cells[i][j] = c_ptr;
}

void tetra4::makeCells() {
	for (int i=0;i<2;i++)
		for (int j=0;j<4;j++){
			cells[i][j] = new cell();
			
			if (i==0 && j==1)
				cells[i][j]->setE(0.6+1E-10*((double)rand()/((double)RAND_MAX)));
			else 
				cells[i][j]->setE(0.3+1E-10*((double)rand()/((double)RAND_MAX)));
			
			if (j==0) cells[i][j]->setX(point4(double(i),0.,0.,0.));
			if (j==1) cells[i][j]->setX(point4(double(i),1.,0.,0.));
			if (j==2) cells[i][j]->setX(point4(double(i),0.,1.,0.));
			if (j==3) cells[i][j]->setX(point4(double(i),0.,0.,1.));
			
				//std::cout << *cells[i][j] << std::endl;
		}
}

bool tetra4::hasSurface() {
	if (cells[0][0]->getE() < fosE){
		for (int i=0;i<2;i++)
			for (int j=0;j<4;j++)
				if (cells[i][j]->getE() > fosE)
					return true;
	}
	else {
		for (int i=0;i<2;i++)
			for (int j=0;j<4;j++)
				if (cells[i][j]->getE() < fosE)
					return true;
	}
	
	std::cout << "no surf in tetra4: " << std::endl;
	for (int i=0;i<2;i++)
		for (int j=0;j<4;j++)
			std::cout << cells[i][j]->getE() << " ";
	std::cout << std::endl << std::endl;
	
	return false;
}

bool tetra4::isValid() const {
	for (int i=0;i<2;i++)
		for (int j=0;j<4;j++)
			if (cells[i][j] == NULL)
				return false;
	return true;
}

void tetra4::findSurfacePoints() {
		// connections within tetrahedron at each time
	for (int i=0;i<2;i++) 
		for (int k=0;k<3;k++)
			for (int j=k;j<4;j++)
				findSurf(cells[i][j],cells[i][k]);
	
		// time-like connections
	for (int i=0;i<4;i++)
		findSurf(cells[0][i],cells[1][i]);
}

void tetra4::findSurf(cell* c1, cell* c2) {
	if ( (c1->getE() < fosE && c2->getE() > fosE) || (c1->getE() > fosE && c2->getE() < fosE)) 
		mPoly.addPoint( c1->getX() + ((fosE-c1->getE())/(c2->getE()-c1->getE()))*(c2->getX()-c1->getX()));
}

point4 tetra4::getVolumeVector(point4 &center) {
	if (!isValid()){
		std::cout << "tetra4::getVolumeVector() called in non-initialized tetra4" << std::endl;
		exit(1);
	}
	
	findSurfacePoints();
	
	if (mPoly.size() == 0) {
		std::cout << "tetra4::getVolumeVector() called w/o surface" << std::endl;
		exit(1);
	}
	
	mPoly.calcCenter4();
	center = mPoly.getCenter4();
	point4 c = center -  pointAboveFOS();
	mPoly.setNormal(c);
	mPoly.makePoints3();
	
	int jiggles=0;
	while(!mPoly.giftwrap()) {
		mPoly.jigglePoints();
		mPoly.makePoints3();
		jiggles++;
		if (jiggles > 5) {
			std::cout << std::endl << "weird cube??? " << std::endl << mPoly << std::endl << std::endl;
			exit(1);
		}
	}
	
	return mPoly.getVolumeVector();
}

point4 tetra4::pointAboveFOS(){
	point4 p;
	int numPoints=0;
	for (int i=0;i<2;i++)
		for (int j=0;j<4;j++)
			if (cells[i][j]->getE() > fosE){
				numPoints++;
				p += cells[i][j]->getX();
			}
	p /= double(numPoints);
		//	std::cout << "paf = " << p << std::endl;
	return p;
}

std::ostream& operator<< (std::ostream &outS, const tetra4 &t){
	if (t.isValid())
		for (int i=0;i<2;i++) {
			for (int j=0;j<4;j++) 
				outS << *t.cells[i][j] << " | ";
			outS << std::endl;
		}
	else 
		outS << "Unable to stream Invalid Tetra4";
	return outS;
}

double tetra4::fosE;

cube4::cube4() {
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++)
				for (int m=0;m<2;m++)
					cells[i][j][k][m] = NULL;
}

cube4::cube4(cube4& c) {
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++)
				for (int m=0;m<2;m++)
					cells[i][j][k][m] = c.cells[i][j][k][m];
	
}

cube4::~cube4() {
		//noop
}

void cube4::setCell(int i, int j, int k, int m, cell* c_ptr) {
	if ((i==0 || i==1) && (j==0 || j==1) && (k==0 || k==1) && (m==0 || m==1)){
		std::cout << "Invalid call to cube4::setCell("<<i<<","<<j<<","<<k<<","<<m<<") " << std::endl;
		exit(1);
	}
	cells[i][j][k][m] = c_ptr;
}
/*
void cube4::setCells(CCell* oCells[16]) {
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++)
				for (int m=0;m<2;m++) {
					cells[i][j][k][m] = new cell();
					cells[i][j][k][m]->setCell(oCells[8*i+4*j+2*k+m]);
				}
	
}
*/
void cube4::makeCells() {
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++)
				for (int m=0;m<2;m++) {
					cells[i][j][k][m] = new cell();
					
					if (k==0 && j==1)
						cells[i][j][k][m]->setE(0.7+1E-10*((double)rand()/((double)RAND_MAX)));
					else 
						cells[i][j][k][m]->setE(0.3+1E-10*((double)rand()/((double)RAND_MAX)));
						//cells[i][j][k][m]->setE(((double)rand()/((double)RAND_MAX)));
					
					
					cells[i][j][k][m]->setX(point4(double(i),double(j),double(k),double(m)));
					
						//std::cout << *cells[i][j][k][m] << std::endl;
				}
}

void cube4::makeTetras() {
		// set main diagonal
	for (int j=0;j<2;j++) {
		for (int i=0;i<6;i++){
			tetras[i].setCell(j,0,cells[j][0][0][0]);
			tetras[i].setCell(j,3,cells[j][1][1][1]);
		}
		tetras[0].setCell(j,1,cells[j][1][0][0]);
		tetras[0].setCell(j,2,cells[j][1][1][0]);
		
		tetras[1].setCell(j,1,cells[j][1][1][0]);
		tetras[1].setCell(j,2,cells[j][0][1][0]);
		
		tetras[2].setCell(j,1,cells[j][0][1][0]);
		tetras[2].setCell(j,2,cells[j][0][1][1]);
		
		tetras[3].setCell(j,1,cells[j][0][1][1]);
		tetras[3].setCell(j,2,cells[j][0][0][1]);
		
		tetras[4].setCell(j,1,cells[j][0][0][1]);
		tetras[4].setCell(j,2,cells[j][1][0][1]);
		
		tetras[5].setCell(j,1,cells[j][1][0][1]);
		tetras[5].setCell(j,2,cells[j][1][0][0]);
	}
	
	
		//	for (int i=0;i<6;i++)
		//		std::cout << tetras[i] << std::endl;
}

bool cube4::hasSurface() {
	if (cells[0][0][0][0]->getE() < fosE){
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				for (int k=0;k<2;k++)
					for (int m=0;m<2;m++)
						if (cells[i][j][k][m]->getE() > fosE)
							return true;
	}
	else {
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				for (int k=0;k<2;k++)
					for (int m=0;m<2;m++)
						if (cells[i][j][k][m]->getE() < fosE)
							return true;
	}
	return false;
}

bool cube4::isValid() {
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++)
				for (int m=0;m<2;m++)
					if (cells[i][j][k][m] == NULL)
						return false;
	return true;
}

void cube4::findSurfacePoints() {
	/*
		// connections within cube at each time
	for (int i=0;i<2;i++){
		findSurf(cells[i][0][0][0],cells[i][0][0][1]);
		findSurf(cells[i][0][0][0],cells[i][0][1][0]);
		findSurf(cells[i][0][0][0],cells[i][1][0][0]);
		
		findSurf(cells[i][0][0][1],cells[i][0][1][1]);
		findSurf(cells[i][0][0][1],cells[i][1][0][1]);
		
		findSurf(cells[i][0][1][0],cells[i][1][1][0]);
		findSurf(cells[i][0][1][0],cells[i][0][1][1]);
		
		findSurf(cells[i][1][0][0],cells[i][1][1][0]);
		findSurf(cells[i][1][0][0],cells[i][1][0][1]);
		
		findSurf(cells[i][1][1][0],cells[i][1][1][1]);
		findSurf(cells[i][1][0][1],cells[i][1][1][1]);
		findSurf(cells[i][0][1][1],cells[i][1][1][1]);
	}
	
		// time-like connections
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++)
				findSurf(cells[0][i][j][k],cells[1][i][j][k]);
	 */
}

point4 cube4::getVolumeVector(point4 &rCenter) {
	if (!isValid()){
		std::cout << "cube4::getVolumeVector() called in non-initialized cube4" << std::endl;
		exit(1);
	}
	
	rCenter.makeZero();
	makeTetras();
	
	point4 vVec, center;
	int count=0;
	for (int i=0;i<6;i++) {
		if (!tetras[i].hasSurface()) continue;
		point4 v = tetras[i].getVolumeVector(center);
		vVec += v;
		rCenter += center;
		count++;
	}
	if (count == 0) {
		std::cout << "findSurf error - no surface in this cube : "<< fosE << std::endl;
		
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				for (int k=0;k<2;k++)
					for (int m=0;m<2;m++)
						std::cout << cells[i][j][k][m]->getE() << std::endl;
		
		return point4(0.,0.,0.,0.);
	}
	
	
	rCenter /= double(count);
	return vVec;
}

bool cube4::freeze(double foPoint[4], double surfVec[4]) {
	point4 center;
	point4 mFOVec = getVolumeVector(center);
	
	for (int i=0;i<4;i++){
		foPoint[i] = center.getX(i);
		surfVec[i] = mFOVec.getX(i);
	}
	
	if (center.isZero())
		return false;
	return true;
}

double cube4::fosE;