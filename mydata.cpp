#include "mydata.h"

NameRefvol::NameRefvol()
{
	name = new int[500];
	vol = new float[500];
	organcount = 0;
}


//Functions for class "face"
Face::Face()
{
	pointAindex_ = 0;
	pointBindex_ = 0;
	pointCindex_ = 0;
	//count = 0;
}
unsigned int Face::getpointAindex()
{
	return pointAindex_;
}
unsigned int Face::getpointBindex()
{
	return pointBindex_;
}
unsigned int Face::getpointCindex()
{
	return pointCindex_;
}
void Face::setpointAindex(unsigned int pointAindex)
{
	pointAindex_ = pointAindex;
}
void Face::setpointBindex(unsigned int pointBindex)
{
	pointBindex_ = pointBindex;
}
void Face::setpointCindex(unsigned int pointCindex)
{
	pointCindex_ = pointCindex;
}

//Functions for class "Point"
Point::Point()
{
	coorX_ = 0;
	coorY_ = 0;
	coorZ_ = 0;
	//count = 0;
}
float Point::getcoorX()
{
	return coorX_;
}
float Point::getcoorY()
{
	return coorY_;
}
float Point::getcoorZ()
{
	return coorZ_;
}
void Point::setcoorX(float coorX)
{
	coorX_ = coorX;
}
void Point::setcoorY(float coorY)
{
	coorY_ = coorY;
}
void Point::setcoorZ(float coorZ)
{
	coorZ_ = coorZ;
}

ObjGeo::ObjGeo()
{
	face = 0;
	point = 0;
	facecount = 0;
	pointcount = 0;
	vncount = 0;
}

ObjGeo::ObjGeo(ObjGeo &objgeoCOPY)
{
	face = new Face[objgeoCOPY.facecount];
	point = new Point[objgeoCOPY.pointcount];
	pointnormal = new Point[objgeoCOPY.vncount];

	facecount = objgeoCOPY.facecount;
	pointcount = objgeoCOPY.pointcount;
	vncount = objgeoCOPY.vncount;

	for (int i = 1; i <= objgeoCOPY.facecount; i++)
	{
		(face + i)->setpointAindex((objgeoCOPY.face + i)->getpointAindex());
		(face + i)->setpointBindex((objgeoCOPY.face + i)->getpointBindex());
		(face + i)->setpointCindex((objgeoCOPY.face + i)->getpointCindex());
	}

	for (int i = 1; i <= objgeoCOPY.pointcount; i++)
	{
		(point + i)->setcoorX((objgeoCOPY.point + i)->getcoorX());
		(point + i)->setcoorY((objgeoCOPY.point + i)->getcoorY());
		(point + i)->setcoorZ((objgeoCOPY.point + i)->getcoorZ());
	}

	for (int i = 0; i < objgeoCOPY.vncount; i++)
	{
		(pointnormal + i)->setcoorX((objgeoCOPY.pointnormal + i)->getcoorX());
		(pointnormal + i)->setcoorY((objgeoCOPY.pointnormal + i)->getcoorY());
		(pointnormal + i)->setcoorZ((objgeoCOPY.pointnormal + i)->getcoorZ());
	}

}

//ObjGeo ObjGeo::operator=(ObjGeo &objgeoCOPY) //+ 重载，深拷贝
//{
//	if (0 != this->face || 0 != this->point || 0 != this->pointnormal)
//	{
//		delete[]this->face;
//		delete[]this->point;
//		delete[]this->pointnormal;
//	}
//	this->face = new Face[objgeoCOPY.facecount];
//	this->point = new Point[objgeoCOPY.pointcount];
//	this->pointnormal = new Point[objgeoCOPY.vncount];
//
//	facecount = objgeoCOPY.facecount;
//	pointcount = objgeoCOPY.pointcount;
//	vncount = objgeoCOPY.vncount;
//
//	for (int i = 1; i <= objgeoCOPY.facecount; i++)
//	{
//		(this->face + i)->setpointAindex((objgeoCOPY.face + i)->getpointAindex());
//		(this->face + i)->setpointBindex((objgeoCOPY.face + i)->getpointBindex());
//		(this->face + i)->setpointCindex((objgeoCOPY.face + i)->getpointCindex());
//	}
//
//	for (int i = 1; i <= objgeoCOPY.pointcount; i++)
//	{
//		(this->point + i)->setcoorX((objgeoCOPY.point + i)->getcoorX());
//		(this->point + i)->setcoorY((objgeoCOPY.point + i)->getcoorY());
//		(this->point + i)->setcoorZ((objgeoCOPY.point + i)->getcoorZ());
//	}
//
//	for (int i = 0; i < objgeoCOPY.vncount; i++)
//	{
//		(this->pointnormal + i)->setcoorX((objgeoCOPY.pointnormal + i)->getcoorX());
//		(this->pointnormal + i)->setcoorY((objgeoCOPY.pointnormal + i)->getcoorY());
//		(this->pointnormal + i)->setcoorZ((objgeoCOPY.pointnormal + i)->getcoorZ());
//	}
//
//	return *this;
//}

double ObjGeo::geoVolCal()
{
	// 计算质心
	Point geocenter;
	float xx, yy, zz;
	xx = 0, yy = 0, zz = 0;
	for (int i = 0; i < this->facecount; i++)
	{
		xx += (this->point + (this->face + i)->getpointAindex())->getcoorX();
		yy += (this->point + (this->face + i)->getpointAindex())->getcoorY();
		zz += (this->point + (this->face + i)->getpointAindex())->getcoorZ();
		xx += (this->point + (this->face + i)->getpointBindex())->getcoorX();
		yy += (this->point + (this->face + i)->getpointBindex())->getcoorY();
		zz += (this->point + (this->face + i)->getpointBindex())->getcoorZ();
		xx += (this->point + (this->face + i)->getpointCindex())->getcoorX();
		yy += (this->point + (this->face + i)->getpointCindex())->getcoorY();
		zz += (this->point + (this->face + i)->getpointCindex())->getcoorZ();
	}
	xx = xx / (this->facecount * 3);
	yy = yy / (this->facecount * 3);
	zz = zz / (this->facecount * 3);

	// 计算体积
	geocenter.setcoorX(xx);
	geocenter.setcoorY(yy);
	geocenter.setcoorZ(zz);
	float geovol = 0;
	for (int i = 0; i < this->facecount; i++)
	{
		Point A, B, C;
		A.setcoorX((this->point + (this->face + i)->getpointBindex())->getcoorX() - (this->point + (this->face + i)->getpointAindex())->getcoorX());
		A.setcoorY((this->point + (this->face + i)->getpointBindex())->getcoorY() - (this->point + (this->face + i)->getpointAindex())->getcoorY());
		A.setcoorZ((this->point + (this->face + i)->getpointBindex())->getcoorZ() - (this->point + (this->face + i)->getpointAindex())->getcoorZ());
		B.setcoorX((this->point + (this->face + i)->getpointCindex())->getcoorX() - (this->point + (this->face + i)->getpointAindex())->getcoorX());
		B.setcoorY((this->point + (this->face + i)->getpointCindex())->getcoorY() - (this->point + (this->face + i)->getpointAindex())->getcoorY());
		B.setcoorZ((this->point + (this->face + i)->getpointCindex())->getcoorZ() - (this->point + (this->face + i)->getpointAindex())->getcoorZ());
		C.setcoorX(geocenter.getcoorX() - (this->point + (this->face + i)->getpointAindex())->getcoorX());
		C.setcoorY(geocenter.getcoorY() - (this->point + (this->face + i)->getpointAindex())->getcoorY());
		C.setcoorZ(geocenter.getcoorZ() - (this->point + (this->face + i)->getpointAindex())->getcoorZ());

		Point D; //A x B = D
		D.setcoorX(A.getcoorY() * B.getcoorZ() - A.getcoorZ() * B.getcoorY());
		D.setcoorY(A.getcoorZ() * B.getcoorX() - A.getcoorX() * B.getcoorZ());
		D.setcoorZ(A.getcoorX() * B.getcoorY() - A.getcoorY() * B.getcoorX());

		geovol += 1.0 / 6 * (D.getcoorX() * C.getcoorX() + D.getcoorY() * C.getcoorY() + D.getcoorZ() * C.getcoorZ());
	}

	return geovol;
}

//void ObjGeo::geoVertexMove(float length)
//{
//	for (int i = 1; i <= this->pointcount; i++)
//	{
//		(this->point + i)->setcoorX(((this->point + i)->getcoorX() + length * (this->pointnormal + i)->getcoorX()));
//		(this->point + i)->setcoorY(((this->point + i)->getcoorY() + length * (this->pointnormal + i)->getcoorY()));
//		(this->point + i)->setcoorZ(((this->point + i)->getcoorZ() + length * (this->pointnormal + i)->getcoorZ()));
//	}
//}

ObjGeo& ObjGeo::operator+=(float length)
{
	for (int i = 1; i <= this->pointcount; i++)
	{
		(this->point + i)->setcoorX(((this->point + i)->getcoorX() + length * (this->pointnormal + i)->getcoorX()));
		(this->point + i)->setcoorY(((this->point + i)->getcoorY() + length * (this->pointnormal + i)->getcoorY()));
		(this->point + i)->setcoorZ(((this->point + i)->getcoorZ() + length * (this->pointnormal + i)->getcoorZ()));
	}
	
	return *this;
}

ObjGeo& ObjGeo::operator+(float length)
{
	for (int i = 1; i <= this->pointcount; i++)
	{
		(this->point + i)->setcoorX(((this->point + i)->getcoorX() + length * (this->pointnormal + i)->getcoorX()));
		(this->point + i)->setcoorY(((this->point + i)->getcoorY() + length * (this->pointnormal + i)->getcoorY()));
		(this->point + i)->setcoorZ(((this->point + i)->getcoorZ() + length * (this->pointnormal + i)->getcoorZ()));
	}

	return *this;
}

void ObjGeo::freeObjGeo()
{
	delete[]point;
	point = 0;
	delete[]face;
	face = 0;
	delete[]pointnormal;
	pointnormal = 0;
	facecount = 0;
	pointcount = 0;
	vncount = 0;
}

//ObjGeo::~ObjGeo()
//{
//	delete[]point;
//	delete[]face;
//	delete[]pointnormal;
//  facecount = 0;
//  pointcount = 0;
//  vncount = 0;
//}
