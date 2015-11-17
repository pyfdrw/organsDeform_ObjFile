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
	Point(float coorX, float coorY, float coorZ);
	float getcoorX();
	float getcoorY();
	float getcoorZ();
	void setcoorX(float coorX);
	void setcoorY(float coorY);
	void setcoorZ(float coorZ);
	Point& operator-(Point &B);
	Point& operator+(Point &B);
	Point& operator/(float divisor);
	Point& operator*(float multiplier);
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
	int vnRebuild();
	//void geoVertexMove(float length); //沿着点发方向平移lenth
	ObjGeo& operator+=(float length);
	ObjGeo& operator+(float length);    //仅支持objgeoCOPY+length，表示沿着点发方向平移lenth，不支持交换律
	ObjGeo& operator*(float factornow); //统一缩放因子缩放，仅按照Z方向缩放
	/*ObjGeo operator=(ObjGeo &objgeoCOPY);*/
	void freeObjGeo();
	Point& centerpointCal();
	void dirMove(Point direction);   //几何按照direction方向平移
	//~ObjGeo();
};


void fileHandle(string &path);
void storeNameRefvol(string WORKDIR, NameRefvol &namevol);
int storeGeo(std::string objfilepath, ObjGeo& objgeo);
void deformFunction(string WORKDIR , NameRefvol namevol);
float organDeform(ObjGeo &objgeo, float singlevol);
float correctmoveminFind(ObjGeo &objgeo);   //几何向内缩放的时候可能出现体积为负数的情况，需要计算最大的缩放距离
float organDeformUniformScle(ObjGeo &objgeo, float singlevol);

void geoOutput(string outfilepath, ObjGeo& objgeo);
void NameRefvolEdit(NameRefvol &namerefvol);
Point &vectorCross(Point &A, Point &B);   //向量叉乘
float vectorDot(Point &A, Point &B);      //向量点乘

# endif
