# ifndef MYDATA_H

// read .obj file
#include <iostream>
#include <cstdlib>

#include <sstream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cmath>
// std
using std::string;

class NameRefvol
{
public:
	NameRefvol();
	unsigned int organcount;
	int *name;
	float *vol;
};


class Face
{
private:
	unsigned int pointAindex_;
	unsigned int pointBindex_;
	unsigned int pointCindex_;
public:
	//unsigned int count;
	Face();
	unsigned int getpointAindex();
	unsigned int getpointBindex();
	unsigned int getpointCindex();
	void setpointAindex(unsigned int pointAindex);
	void setpointBindex(unsigned int pointBindex);
	void setpointCindex(unsigned int pointCindex);
};

class Point
{
private:
	float coorX_;
	float coorY_;
	float coorZ_;
public:
	//unsigned int count;
	Point();
	float getcoorX();
	float getcoorY();
	float getcoorZ();
	void setcoorX(float coorX);
	void setcoorY(float coorY);
	void setcoorZ(float coorZ);
};

class ObjGeo
{
public:
	Face* face;
	Point* pointnormal;
	Point* point;
	unsigned int facecount;
	unsigned int pointcount;
	unsigned int vncount;
	ObjGeo();
	ObjGeo(ObjGeo &objgeoCOPY);  //拷贝构造函数
	double geoVolCal();
	//void geoVertexMove(float length); //沿着点发方向平移lenth
	ObjGeo& operator+=(float length);
	ObjGeo& operator+(float length);  //仅支持objgeoCOPY+length，表示沿着点发方向平移lenth，不支持交换律
	/*ObjGeo operator=(ObjGeo &objgeoCOPY);*/
	void freeObjGeo();
	//~ObjGeo();
};


void fileHandle(string &path);
void storeNameRefvol(string WORKDIR, NameRefvol &namevol);
int storeGeo(std::string objfilepath, ObjGeo& objgeo);
void deformFunction(string WORKDIR , NameRefvol namevol);
float organDeform(ObjGeo &objgeo, float singlevol);
void geoOutput(string outfilepath, ObjGeo& objgeo);
void NameRefvolEdit(NameRefvol &namerefvol);

# endif
