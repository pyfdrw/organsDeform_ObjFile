#include "mydata.h"

// Other functions
void fileHandle(string &path) {
	char *tmp = new char[500];
	std::cout << "Please input OBJ files location" << std::endl;
	std::cout << "Make sure AIMVOL.txt exist !" << std::endl;
	std::cin >> tmp;
	path = tmp;
	if (path.at(path.length() - 1) != '\\' || path.at(path.length() - 1) != '/') {
		if (path.find('/') > path.length()) {
			path.append("\\");
		} else {
			path.append("/");
		}
	}

}

void storeNameRefvol(string WORKDIR, NameRefvol &namevol) {
	string namevolpath = WORKDIR + "AIMVOL.txt";
	std::ifstream volfilein;
	char* namevolpathchartmp = new char[500];
	std::stringstream sstmp;
	sstmp << namevolpath;
	sstmp >> namevolpathchartmp;
	sstmp.clear();

	volfilein.open(namevolpathchartmp, std::ifstream::in);

	if (true == volfilein.fail()) {
		std::cout << "\"AIMVOL.txt\" is not exist !" << std::endl;
		std::exit(0);
	}

	char* linetmp = new char[300];

	while (true != volfilein.eof()) {
		volfilein.getline(linetmp, 300);
		if (strlen(linetmp) < 2) {
			continue;
		}
		sscanf(linetmp, "%d %f", (namevol.name + namevol.organcount), (namevol.vol + namevol.organcount));
		namevol.organcount++;
	}

	delete[]namevolpathchartmp;
	volfilein.clear();
	volfilein.close();
}

//�����������ٵı��βο������Ҫ������������������Զ�������Щ����
void NameRefvolEdit(NameRefvol &namerefvol)
{
	float *vol = new float[500];
	for (int i = 0; i < 500; i++) 
		*(vol + i) = 0;

	for (int i = 0; i < namerefvol.organcount; i++)
	{
		*(vol + *(namerefvol.name + i)) = *(namerefvol.vol + i);
	}

	// ������������֯��������ο�������¼���
	for (int i = 0; i < 500; i++)
	{
		if (13 == i)
			*(vol + 13) = *(vol + 13) + *(vol + 14) + *(vol + 15);
		else if (16 == i)
			*(vol + 16) = *(vol + 16) + *(vol + 17) + *(vol + 18);
		else if (19 == i)
			*(vol + 19) = *(vol + 19) + *(vol + 20) + *(vol + 21);
		else if (22 == i)
			*(vol + 22) = *(vol + 22) + *(vol + 23);
		else if (24 == i)
			*(vol + 24) = *(vol + 24) + *(vol + 25);
		else if (26 == i)
			*(vol + 26) = *(vol + 26) + *(vol + 27);
		else if (28 == i)
			*(vol + 28) = *(vol + 28) + *(vol + 29) + *(vol + 30);
		else if (31 == i)
			*(vol + 31) = *(vol + 31) + *(vol + 32) + *(vol + 33);
		else if (34 == i)
			*(vol + 34) = *(vol + 34) + *(vol + 35) + *(vol + 36);
		else if (37 == i)
			*(vol + 37) = *(vol + 37) + *(vol + 38);
		else if (39 == i)
			*(vol + 39) = *(vol + 39) + *(vol + 40);
		else if (41 == i)
			*(vol + 41) = *(vol + 41) + *(vol + 42);
		else if (43 == i)
			*(vol + 43) = *(vol + 43) + *(vol + 44);
		else if (45 == i)
			*(vol + 45) = *(vol + 45) + *(vol + 46);
		else if (47 == i)
			*(vol + 47) = *(vol + 47) + *(vol + 48);
		else if (49 == i)
			*(vol + 49) = *(vol + 49) + *(vol + 50);
		else if (51 == i)
			*(vol + 51) = *(vol + 51) + *(vol + 52);
		else if (53 == i)
			*(vol + 53) = *(vol + 53) + *(vol + 54);
		else if (55 == i)
			*(vol + 55) = *(vol + 55) + *(vol + 56);
		else if (70 == i)
			*(vol + 70) = *(vol + 70) + *(vol + 71);
		else if (72 == i)
			*(vol + 72) = *(vol + 72) + *(vol + 73);
		else if (74 == i)
		{
			*(vol + 74) = 0;
		}
		else if (75 == i)
			*(vol + 75) = *(vol + 75) + *(vol + 74);
		else if (76 == i)
			*(vol + 76) = *(vol + 76) + *(vol + 77);
		else if (78 == i)
			*(vol + 78) = *(vol + 78) + *(vol + 79);
		else if (80 == i)
			*(vol + 80) = *(vol + 80) + *(vol + 81);
		else if (82 == i)
			*(vol + 82) = *(vol + 82) + *(vol + 83);
		else if (84 == i)
			*(vol + 84) = *(vol + 84) + *(vol + 85);
		else if (87 == i)
			*(vol + 87) = *(vol + 87) + *(vol + 88);
		else if (89 == i)
			*(vol + 89) = *(vol + 89) + *(vol + 90);
		else if (92 == i)
			*(vol + 92) = *(vol + 92) + *(vol + 93);
		else if (137 == i)
			*(vol + 137) = *(vol + 137) + *(vol + 138);
	}

	namerefvol.organcount = 0;
	for (int i = 0; i < 500; i++)
	{
		if (0 != *(vol + i))
		{
			*(namerefvol.name + namerefvol.organcount) = i;
			*(namerefvol.vol + namerefvol.organcount) = *(vol + i);

			namerefvol.organcount++;
		}
	}

	delete[]vol;
}

// Store ObjGeo
int storeGeo(std::string objfilepath, ObjGeo& objgeo) {
	std::ifstream filein;
	char* objfilepathchartmp = new char[500];
	std::stringstream sstmp;
	sstmp << objfilepath;
	sstmp >> objfilepathchartmp;
	sstmp.clear();

	filein.open(objfilepathchartmp, std::ifstream::in);
	if (true == filein.fail()) {
		std::cout << objfilepath << "not exist" << std::endl;
		return 1;
	}

	char* linetmp = new char[300];
	int Vcount = 0, Fcount = 0, VNcount = 0;
	while (true != filein.eof()) {
		filein.getline(linetmp, 300);
		if (0 == strlen(linetmp) || 1 == strlen(linetmp))
			continue;
		if ('v' == *linetmp && ' ' == *(linetmp + 1)) {
			Vcount++;
		} else if ('v' == *linetmp && 'n' == *(linetmp + 1)) {
			VNcount++;
		} else if ('f' == *linetmp && ' ' == *(linetmp + 1)) {
			Fcount++;
		}
	}

	//malloc enough space
	//objgeo.point[0] �� objgeo.pointnormal[0]������
	//objgeo.face[0] ������
	objgeo.facecount = Fcount;
	objgeo.pointcount = Vcount;
	objgeo.vncount = VNcount;
	objgeo.point = new Point[Vcount + 1];
	objgeo.pointnormal = new Point[VNcount + 1];
	objgeo.face = new Face[Fcount + 1];

	filein.clear();  // �ļ���ȡ������ʱ ʹ��seek����Ч�ģ�������clear
	//filein.close();
	filein.seekg(0L,std::ifstream::beg);    // �ļ����������ļ���ͷ
	//filein.open(objfilepath, std::ifstream::in);
	
	int tellgg = filein.tellg();
	int pointtmp = 0;
	int pointnormaltmp = 0;
	int facetmp = 0;
	while (true != filein.eof()) {
		filein.getline(linetmp, 300);
		if ('v' == *linetmp && ' ' == *(linetmp + 1)) {
			float coorX, coorY, coorZ;
			sscanf(linetmp, "%*s %f%f%f", &coorX, &coorY, &coorZ);
			(objgeo.point + pointtmp + 1)->setcoorX(coorX);
			(objgeo.point + pointtmp + 1)->setcoorY(coorY);
			(objgeo.point + pointtmp + 1)->setcoorZ(coorZ);
			pointtmp++;
		} else if ('v' == *linetmp && 'n' == *(linetmp + 1)) {
			float coorX, coorY, coorZ;
			sscanf(linetmp, "%*s %f%f%f", &coorX, &coorY, &coorZ);
			(objgeo.pointnormal + pointnormaltmp + 1)->setcoorX(coorX);
			(objgeo.pointnormal + pointnormaltmp + 1)->setcoorY(coorY);
			(objgeo.pointnormal + pointnormaltmp + 1)->setcoorZ(coorZ);
			pointnormaltmp++;
		} else if ('f' == *linetmp && ' ' == *(linetmp + 1)) {
			int facetmp1, facetmp2, facetmp3;
			sscanf(linetmp, "%*s %d//%*d %d//%*d %d//%*d", &facetmp1, &facetmp2, &facetmp3);
			(objgeo.face + facetmp)->setpointAindex(facetmp1);
			(objgeo.face + facetmp)->setpointBindex(facetmp2);
			(objgeo.face + facetmp)->setpointCindex(facetmp3);
			facetmp++;
		}
	}

	delete[]objfilepathchartmp;
	filein.close();
	return 0;
}

void deformFunction(string WORKDIR , NameRefvol namevol) {
	std::cout << "move path in ...\\deform\\" << std::endl;
	string OUTPUTDIR = WORKDIR + "deform";
	if (OUTPUTDIR.at(OUTPUTDIR.length() - 1) != '\\' || OUTPUTDIR.at(OUTPUTDIR.length() - 1) != '/') {
		if (OUTPUTDIR.find('/') > OUTPUTDIR.length()) {
			OUTPUTDIR.append("\\");
		} else {
			OUTPUTDIR.append("/");
		}
	}

	std::stringstream ss; // ��������ת��
	string filename;      // ���ڴ洢�ļ���(����ת�����ַ���)
	string objfilepath;   // ��ȡ��objfile�ľ���·��
	float movelength[200];  // �洢����ƫ�Ƶĳ���
	ObjGeo objgeo; 
	int filetmp;
	for (int i = 0; i < namevol.organcount; i++) { //namevol�д洢��������Ŀ�����ٱ��Ҳ�洢���������ˣ�
		filename.clear();
		ss.clear();
		ss << *(namevol.name + i);
		ss >> filename;
		objfilepath = WORKDIR + filename + ".obj";
		std::cout << filename + ".obj    "; //<< std::endl;
		filetmp = storeGeo(objfilepath, objgeo);
		if (1 == filetmp) {      //file not found
			continue;
		}// �洢����
		movelength[i] = organDeform(objgeo, *(namevol.vol + i)); // ƫ������ƫ�Ƴ��ȼ�¼��movelength��

		geoOutput(OUTPUTDIR + filename + ".obj", objgeo);

		objgeo.freeObjGeo();
		std::cout << std::endl;

	}

	// ���movelength[]��OUTPUTDIR + "movelength.txt"��
	std::ofstream movelengthfile;
	char* movelengthfilechartmp = new char[500];
	std::stringstream sstmp;
	sstmp << OUTPUTDIR + "movelength.txt";
	sstmp >> movelengthfilechartmp;
	sstmp.clear();

	movelengthfile.open(movelengthfilechartmp,std::ifstream::out);
	if (true == movelengthfile.fail()) {
		std::cout << "Can't create or open " << OUTPUTDIR + "movelength.txt" << std::endl;
	}
	movelengthfile << "move length for every organ\n" << std::endl;
	movelengthfile << "Organ          movelength\n" << std::endl;
	for (int i = 0; i < namevol.organcount; i++) {
		movelengthfile << std::setw(5) << std::right << *(namevol.name + i) << "          " << std::left << movelength[i] << '\n';
	}

	delete[]movelengthfilechartmp;
	movelengthfile.clear();
	movelengthfile.close();
}

float organDeform(ObjGeo &objgeo, float singlevol) {
	//float vol = fabs(objgeo.geoVolCal());
	float vol = (objgeo.geoVolCal());
	std::cout << "Initial vol = " << vol;
	// �������ŵĳ��Ȳ�Ӧ������ѡȡ��������Χ�п�򳤻�ߵ���Сֵ�ĸ�����Ϊ���������������
	float minx = 100000; float maxx = -100000;
	float miny = 100000; float maxy = -100000;
	float minz = 100000; float maxz = -100000;
	float minans = 0;
	for (int i = 0; i < objgeo.pointcount; i++)
	{
		minx = minx > (objgeo.point + i)->getcoorX() ? (objgeo.point + i)->getcoorX() : minx;
		maxx = maxx < (objgeo.point + i)->getcoorX() ? (objgeo.point + i)->getcoorX() : maxx;

		miny = miny > (objgeo.point + i)->getcoorY() ? (objgeo.point + i)->getcoorY() : miny;
		maxy = maxy < (objgeo.point + i)->getcoorY() ? (objgeo.point + i)->getcoorY() : maxy;

		minz = minz > (objgeo.point + i)->getcoorZ() ? (objgeo.point + i)->getcoorZ() : minz;
		maxz = maxz < (objgeo.point + i)->getcoorZ() ? (objgeo.point + i)->getcoorZ() : maxz;
	}

	minans = (maxx - minx) < (maxy - miny) ? (maxx - minx) : (maxy - miny);
	minans = minans < (maxz - minz) ? minans : (maxz - minz);
	// std::cout << minans;

	float adddirection = 1;  //��¼ʹƽ�����ӵķ�����������Ϊ1����������Ϊ-1
	objgeo += 0.0001;
	float voltmp = (objgeo.geoVolCal());
	if (voltmp >= vol) {
		adddirection = 0.5;
	} else {
		adddirection = -(0.3 < minans ? 0.3 : minans);
	}
	objgeo += -0.05;

	//std::cout << "max move length " << std::setw(5) << std::right << adddirection << "   ";

	float movemax = adddirection;
	float movemin = -adddirection;  //���ƽ�Ƶľ���,movemax����������ƽ�ƾ��룬movemin�����С���ƽ�ƾ���
	float movenow = 0;

	if (vol >= singlevol) { //Ӧ����С���, ע��������ָ��������

		//find correct movemin
		movemin = correctmoveminFind(objgeo);
		std::cout << '\n' << "movemin = " << movemin << std::endl;
		movemax = 0;
		movenow = movemin / 2;
		while ((movemax - movemin) > 0.00001) { //��ֹ��ѭ��
			objgeo += movenow;
			float voltmp = fabs(objgeo.geoVolCal());
			if (fabs(voltmp - singlevol) / singlevol < 0.001) { //������С��0.1%
				break;
			} else if (voltmp >= singlevol) { //movenow������
				objgeo += -movenow;
				movemax = movenow;
				movenow = (movenow + movemin) / 2;

			} else if (voltmp < singlevol) { //movenow̫��
				objgeo += -movenow;
				movemin = movenow;
				movenow = (movenow + movemax) / 2;
			}
		}

		if ((movemax - movemin) <= 0.00001) {
			objgeo += movenow;
			printf("%s", "Waring ");
		}

		if (movenow < -0.2)
		{
			printf("%s", "too huge reduce length!, Try to deform using uniform scale factor\n");
			//objgeo += -movenow; //��ԭ
			//movenow = organDeformUniformScle(objgeo, singlevol);
			//std::cout << movenow << "===";
			//movenow = -100;    //-100 ����ͳһ�ߴ������
		}

		return movenow;
	} else { //Ӧ���������
		movenow = movemax / 2;
		movemin = 0;
		while ((movemax - movemin) > 0.00001) {
			objgeo += movenow;
			float voltmp = fabs(objgeo.geoVolCal());
			if (fabs(voltmp - singlevol) / singlevol < 0.001) { //������С��0.1%
				break;
			} else if (voltmp >= singlevol) { //movenow̫��
				objgeo += -movenow;
				movemax = movenow;
				movenow = (movenow + movemin) / 2;
			} else if (voltmp < singlevol) { //movenow������
				objgeo += -movenow;
				movemin = movenow;
				movenow = (movenow + movemax) / 2;
			}
		}

		if ((movemax - movemin) <= 0.00001) {
			objgeo += movenow;
			printf("%s", "Waring ");
			//std::cout << "Waring " << std::endl;
		}

		return movenow;
	}
}

float correctmoveminFind(ObjGeo &objgeo)
{
	//ObjGeo objgeotmp = objgeo;

	float kmin = - 0.5;
	float kmax = 0;
	float know = - 0.25;
	
	while ((kmax - kmin) > 0.0001)
	{
		objgeo += know;
		if (objgeo.geoVolCal() > 0)
		{
			objgeo += -know;
			kmax = know;
			know = (kmax + kmin) / 2;
		}
		else
		{
			objgeo += -know;
			kmin = know;
			know = (kmax + kmin) / 2;
		}
	}

	//objgeotmp.freeObjGeo();
	return kmax;
}

float organDeformUniformScle(ObjGeo &objgeo, float singlevol)
{
	Point centrepointbef(0, 0, 0);
	Point centrepointaft(0, 0, 0);
	centrepointbef = objgeo.centerpointCal();

	float factormax = 5;
	float factormin = 0.00001;
	float factornow = 1;
	float voltmp = 0;
	voltmp = fabs(objgeo.geoVolCal());
	while (abs((voltmp - singlevol) / singlevol) > 0.0001)
	{
		if (voltmp > singlevol) // ��������̫����
		{
			objgeo = objgeo * (1.0 / factornow);
			factormax = factornow;
			factornow = (factormax + factormin) / 2;
		}
		else
		{
			objgeo = objgeo * (1.0 / factornow);
			factormin = factornow;
			factornow = (factormax + factormin) / 2;
		}
		objgeo = objgeo * factornow;
		voltmp = fabs(objgeo.geoVolCal());
	} 
	
	objgeo.vnRebuild();
	centrepointaft = objgeo.centerpointCal();
	objgeo.dirMove(centrepointaft - centrepointbef);  //���ĵ㱣��һ��

	return factornow;
}

void geoOutput(string outfilepath, ObjGeo& objgeo) {
	std::ofstream fileout;
	char* outfilepathchartmp = new char[500];
	std::stringstream sstmp;
	sstmp << outfilepath;
	sstmp >> outfilepathchartmp;
	sstmp.clear();

	fileout.open(outfilepathchartmp, std::ofstream::out);
	if (true == fileout.fail()) {
		std::cout << "Errors, Can't create or open " << outfilepath << std::endl;
	}

	fileout << "#Rhino\n" << std::endl;
	for (int i = 1; i <= objgeo.pointcount; i++) {         // �������
		fileout << "v " << std::setprecision(13) << std::setw(20) << std::left
		        << (objgeo.point + i)->getcoorX() << ' ' << std::setw(20) << std::left
		        << (objgeo.point + i)->getcoorY() << ' ' << std::setw(20) << std::left
		        << (objgeo.point + i)->getcoorZ() << std::endl;      // ��������С����13λ�ľ������
	}

	for (int i = 1; i <= objgeo.vncount; i++) {           // ���㷨�������
		fileout << "vn " << std::setprecision(13) << std::setw(20) << std::left
		        << (objgeo.pointnormal + i)->getcoorX() << ' ' << std::setw(20) << std::left
		        << (objgeo.pointnormal + i)->getcoorY() << ' ' << std::setw(20) << std::left
		        << (objgeo.pointnormal + i)->getcoorZ() << std::endl;      // ��������С����13λ�ľ������
	}

	for (int i = 0; i < objgeo.facecount; i++) {          // �����
		fileout << "f " << std::left
		        << (objgeo.face + i)->getpointAindex() << "//" << (objgeo.face + i)->getpointAindex() << ' '
		        << (objgeo.face + i)->getpointBindex() << "//" << (objgeo.face + i)->getpointBindex() << ' '
		        << (objgeo.face + i)->getpointCindex() << "//" << (objgeo.face + i)->getpointCindex() << ' '
		        << std::endl;      // ��������С����13λ�ľ������
	}

	//fileout.clear();
	delete[]outfilepathchartmp;
	fileout.close();
}

Point &vectorCross(Point &A, Point &B)
{
	Point C; //c = A x B
	C.setcoorX(A.getcoorY() * B.getcoorZ() - A.getcoorZ() * B.getcoorY());
	C.setcoorY(A.getcoorZ() * B.getcoorX() - A.getcoorX() * B.getcoorZ());
	C.setcoorZ(A.getcoorX() * B.getcoorY() - A.getcoorY() * B.getcoorX());

	return C;
}

float vectorDot(Point &A, Point &B)
{
	float dotans = 0;
	dotans = A.getcoorX() * B.getcoorX() +
		A.getcoorY() * B.getcoorY() +
		A.getcoorZ() * B.getcoorZ();

	return dotans;
}