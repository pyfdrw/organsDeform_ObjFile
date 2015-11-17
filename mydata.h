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
	ObjGeo(ObjGeo &objgeoCOPY);  //�������캯��
	double geoVolCal();
	int vnRebuild();
	//void geoVertexMove(float length); //���ŵ㷢����ƽ��lenth
	ObjGeo& operator+=(float length);
	ObjGeo& operator+(float length);    //��֧��objgeoCOPY+length����ʾ���ŵ㷢����ƽ��lenth����֧�ֽ�����
	ObjGeo& operator*(float factornow); //ͳһ�����������ţ�������Z��������
	/*ObjGeo operator=(ObjGeo &objgeoCOPY);*/
	void freeObjGeo();
	Point& centerpointCal();
	void dirMove(Point direction);   //���ΰ���direction����ƽ��
	//~ObjGeo();
};


void fileHandle(string &path);
void storeNameRefvol(string WORKDIR, NameRefvol &namevol);
int storeGeo(std::string objfilepath, ObjGeo& objgeo);
void deformFunction(string WORKDIR , NameRefvol namevol);
float organDeform(ObjGeo &objgeo, float singlevol);
float correctmoveminFind(ObjGeo &objgeo);   //�����������ŵ�ʱ����ܳ������Ϊ�������������Ҫ�����������ž���
float organDeformUniformScle(ObjGeo &objgeo, float singlevol);

void geoOutput(string outfilepath, ObjGeo& objgeo);
void NameRefvolEdit(NameRefvol &namerefvol);
Point &vectorCross(Point &A, Point &B);   //�������
float vectorDot(Point &A, Point &B);      //�������

# endif
