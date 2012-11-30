#include "poly.h"

poly::poly(){
	points.reserve(4);
	surface.reserve(4);
}

poly::~poly(){
	points.clear();
	surface.clear();
}

point poly::makePoint(){
	return point(((double)rand()/((double)RAND_MAX)),
				 ((double)rand()/((double)RAND_MAX)),
				 ((double)rand()/((double)RAND_MAX)));
}

void poly::makePoints(int i){
	for (int j=0;j<i;j++)
		points.push_back(makePoint());
}

bool poly::isSurfaceOpen(){
	for (int i=0;i<surface.size();i++)
		for (int j=0;j<3;j++)
			if (!surface[i].getEdge_ptr(j)->isMarked()) 
				return true;

	return false;
}

bool poly::markEdges(){
	for (int i=0;i<3;i++){
		edge* mE = surface.back().getEdge_ptr(i);
		for (int j=0;j<surface.size()-1;j++){
			int status = surface[j].markEdge(*mE);
			if (status == 0)
				mE->mark();
			if (status == 2)
				return false;
		}
	}
	return true;
}

void poly::unmarkEdges(){
	for (int i=0;i<3;i++){
		edge* mE = surface.back().getEdge_ptr(i);
		
		for (int j=0;j<surface.size()-1;j++)
			if(surface[j].unmarkEdge(*mE))
				mE->unmark();
	}
}

bool poly::giftwrap(){
	
	if (surface.size() != 0) 
		surface.clear();
	
		// sort by x coordinate
	sortPoints(0);
		// first points is minimum x
	point p1 = points[0]; point* p1_ptr = &points[0];
	
		// 2nd point is found by 2d giftwrap in xy plane
	double maxDot = -1.;
	point p2; point* p2_ptr;
	for (int i=1;i<points.size();i++){
		point delta = points[i] - p1;
		delta.setX(2,0.);
		delta.makeUnit();
		double dDot = delta * point(0,1,0);
		
		std::cout << delta << " * " << points[i] << " : " << dDot << std::endl;
		if (maxDot < dDot){
			maxDot = dDot;
			p2 = points[i];
			p2_ptr = &points[i];
		}
		else if (dDot == maxDot)
			if ( (points[i] - p1).mag() < p2.mag()){
				maxDot = dDot;
				p2 = points[i];
				p2_ptr = &points[i];
			}
	}
	
	std::cout << p1 << "   " << p2 << std::endl;
	
		// project into plane defined by edge
		// between the first two points
	point dp = p2 - p1;
	dp.makeUnit();
		// origin in projected space
	point p0 = p1 - dp * (dp*p1);
	
	std::vector<point> pp;
	for (int i=1;i<points.size();i++)
		if (points[i] != p2)
			pp.push_back(points[i] - dp * (dp*points[i]) - p0);
	
		// find all possible pairs of points
	std::vector<point> ppairs1;
	std::vector<point> ppairs2;
	for (int i=0;i<pp.size();i++)
		for (int j=i+1;j<pp.size();j++){
			ppairs1.push_back(pp[i]);
			ppairs2.push_back(pp[j]);
		}
	
	pp.clear();

		// find the two points in this space 
		// with the largest opening angle
	point pp1, pp2;
	double minDot = 2.;
	for (int i=0;i<ppairs1.size();i++){
		double dDot = (ppairs1[i]*ppairs2[i])/(ppairs1[i].mag()*ppairs2[i].mag());
		if (dDot < minDot){
			minDot = dDot;
			pp1 = ppairs1[i];
			pp2 = ppairs2[i];
		}
		else if (dDot == minDot)
			if ( (ppairs1[i]-ppairs2[i]).mag() < (pp1-pp2).mag()){
				minDot = dDot;
				pp1 = ppairs1[i];
				pp2 = ppairs2[i];
			}
	}
	
	ppairs1.clear();
	ppairs2.clear();
	
		// find the poitns in original space
		// that match the points at large angles
		// these are the first two triangles
	for (int i=0;i<points.size();i++){
		point mPP = points[i] - dp*(dp*points[i]) - p0;
		if (mPP==pp1 || mPP==pp2)
			surface.push_back(tri(*p1_ptr,*p2_ptr,points[i]));
	}
	
	if (!markEdges())
		return false;
	
		//	for (int j=0;j<surface.size();j++)
		//		std::cout << "surface["<<j<< "] : " << surface[j] << std::endl;
		//	std::cout << std::endl;
	
	while (isSurfaceOpen()){
		edge mE;
		point mP;
		
		for (int i=0;i<surface.size();i++){
			
			if (!surface[i].getUnconnected(mE, mP))
				continue;
			
			dp = mE(1) - mE(0);
			dp.makeUnit();
			p0 = mE(1) - dp*(dp*mE(1));
			point mPP = mP - dp*(dp*mP) - p0;
			mPP = -mPP/(mPP.mag());
			
			std::vector<point> ppoints;
			for (int j=0;j<points.size();j++){
				if (surface[i].hasPoint(points[j]))
					continue;
				ppoints.push_back(points[j] - dp *(dp*points[j]) - p0);
			}
			
			double maxDot = -2.;
			point nPP;
				// find most colinear
			for (int j=0;j<ppoints.size();j++){
				double dDot = (ppoints[j]*mPP)/ppoints[j].mag();
				if (dDot > maxDot){
					maxDot = dDot;
					nPP = ppoints[j];
				}
					// if there are planar points, take the closest one
				else if (dDot == maxDot)
					if ( ppoints[j].mag() < nPP.mag()){
						maxDot = dDot;
						nPP = ppoints[j];
					}
			}
			ppoints.clear();

			for (int j=0;j<points.size();j++)
				if (nPP == points[j] - dp*(dp*points[j]) - p0)
					surface.push_back(tri(mE(0),mE(1),points[j]));

				//			for (int j=0;j<surface.size();j++)
				//				std::cout << "surface["<<j<< "] : " << surface[j] << std::endl;
				//			std::cout << std::endl;
			
			if (!markEdges()) {
				return false;
				
					//unmarkEdges();
					//surface.pop_back();
				
					//for (int j=0;j<surface.size();j++)
					//std::cout << "surface["<<j<< "] : " << surface[j] << std::endl;
					//std::cout << std::endl;
					//continue;
			}
			break;
				
		}
	}
	
	calcCenter();
	fixN();
	
	return true;
}

double poly::getConvexVolume(){
	if (surface.size() == 0)
		return -1.;
	
	double temp=0.;
	for (int i=0;i<surface.size();i++)
		temp += surface[i].calcVolume(center);
	return temp/6.;
}

bool poly::calcCenter(){
	if (points.size() == 0)
		return false;
	
	center = point(0.,0.,0.);
	for (int i=0;i<points.size();i++){
		center += points[i];
	}
	
	center /= double(points.size());
	return true;
}

bool poly::fixN(){
	if (surface.size() == 0)
		return false;
	
	for (int i=0;i<surface.size();i++)
		surface[i].fixN(center);
	
	return true;
}

void poly::sortPoints(int i){
	point::setSortIndex(i);
	std::sort(points.begin(), points.end());
}

std::ostream& operator<< (std::ostream &outS, const poly &p) {
	for (int i=0;i<p.points.size();i++)
		outS << p.points[i] << std::endl;
	if (p.surface.size() > 0)
		for (int i=0;i<p.surface.size();i++)
			outS << p.surface[i] << std::endl;
	return outS;
}

poly4::poly4(){
	points4.reserve(4);
		//	surf4.reserve(4);
	center4 = point4(0.,0.,0.,0.);
}

poly4::~poly4(){
	points4.clear();
		//	surf4.clear();
}

void poly4::makePoints3() {
	if (points4.size() == 0){
		std::cout << "Error: poly4::makePoints3 called with empty points4. " << std::endl;
		exit(1);
	}
	
	if (projVec.isZero()){
		std::cout << "poly4::makePoints3() requires a projection vector" <<std::endl;
		exit(1);
	}
		
		//	std::cout << "projVec = " << projVec << std::endl;
	
	basis[0] = point4(1.,0.,0.,0.);
	basis[0] -= (basis[0]*projVec) * projVec;
	if (basis[0].isZero()){
		basis[0] = point4(0.,1.,0.,0.);
		basis[0] -= (basis[0]*projVec) * projVec;
		if (basis[0].isZero()){
			std::cout << " problem with isZero()??? " << std::endl;
			exit(1);
		}
	}
	basis[0].makeUnit();
	
	basis[1] = point4(0.,0.,1.,0.);
		//	std::cout << (basis[1]*projVec)* projVec << " " <<  (basis[1]*basis[0])*basis[0] << std::endl;
	basis[1] -= (basis[1]*projVec) * projVec;
		//	std::cout << basis[1] << " : " << basis[1]*basis[0] << " " << basis[1]*projVec << std::endl;
	basis[1] -= (basis[1]*basis[0])*basis[0];
	
	if (basis[1].isZero()){
		basis[1] = point4(0.,0.,0.,1.);
		basis[1] -= (basis[1]*projVec)* projVec;
		basis[1] -= (basis[1]*basis[0])*basis[0];
		if (basis[1].isZero()){
				// std::cout << " problem with isZero()??? " << std::endl;
			exit(1);
		}
	}
	basis[1].makeUnit();
		//	std::cout << basis[1]*basis[0] << " " << basis[1]*projVec << std::endl;
	
	basis[2] = projVec.cross(basis[0],basis[1]);
	basis[2].makeUnit();
	
		//	std::cout << "basis : " << basis[0] << " " << basis[1] << " " << basis[2] << std::endl;
	
		// check orthogonality??
	
	for (int i=0;i<points4.size();i++) 
		points.push_back( point(basis[0]*points4[i],basis[1]*points4[i],basis[2]*points4[i]));

		//	for (int i=0;i<points.size();i++)
		//		std::cout << "p["<< i << "] : " << points[i] << std::endl;
}

void poly4::jigglePoints() {
	for (int i=0;i<points4.size();i++)
		points4[i].jiggle();
	points.clear();
}

void poly4::calcCenter4() {
	int mSize = points4.size();
	
	if (mSize == 0){
		std::cout << "Error : poly::calcCenter4() called with empty points4 " << std::endl;
		exit(1);
	}
	
	center4 = point4(0.,0.,0.,0.);
	for (int i=0;i<mSize;i++){
		center4 += points4[i];
	}
	center4 /= double(mSize);
		//	std::cout << "center = " << center4 << std::endl;
}

point4 poly4::getVolumeVector() {
	assert(points.size() == points4.size());
	
	point4 mVV;
	
	for (int i=0;i<surface.size();i++) {
		point4* mP4[3];
		for (int j=0;j<3;j++){
			point* mP_ptr = surface[i].getPoint_ptr(j);
			for (int k=0;k<points4.size();k++){
				point p(basis[0]*points4[k],basis[1]*points4[k],basis[2]*points4[k]);
				if (p == *mP_ptr){
					mP4[j] = &points4[k];
					break;
				}
				if (k == points4.size()){
					std::cout << "missing point " << *mP_ptr << std::endl;
					exit(1);
				}
			}
		}
		
		tri4 t(mP4[0],mP4[1],mP4[2]);
			//		std::cout << "adding volume vector:" << std::endl;
			//		std::cout << *mP4[0] << std::endl << *mP4[1] << std::endl << *mP4[2] << std::endl << std::endl;
			//		std::cout << t.getVolumeVector(center4,projVec) << std::endl;
		mVV += t.getVolumeVector(center4,projVec);
	}

	return mVV;
}