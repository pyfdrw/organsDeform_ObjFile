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

// Store ObjGeo but use C based language
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
		std::cout << filename + ".obj    " << std::endl;
		filetmp = storeGeo(objfilepath, objgeo);
		if (1 == filetmp) {      //file not found
			continue;
		}// �洢����
		movelength[i] = organDeform(objgeo, *(namevol.vol + i)); // ƫ������ƫ�Ƴ��ȼ�¼��movelength��

		geoOutput(OUTPUTDIR + filename + ".obj", objgeo);

		objgeo.freeObjGeo();

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
	float vol = fabs(objgeo.geoVolCal());

	float adddirection = 1;  //��¼ʹƽ�����ӵķ�����������Ϊ1����������Ϊ-1
	objgeo += 0.05;
	float voltmp = fabs(objgeo.geoVolCal());
	if (voltmp >= vol) {
		adddirection = 0.5;
	} else {
		adddirection = -0.5;
	}
	objgeo += -0.05;

	float movemax = adddirection;
	float movemin = -adddirection;  //���ƽ�Ƶľ���,movemax����������ƽ�ƾ��룬movemin�����С���ƽ�ƾ���
	float movenow = 0;

	if (vol >= singlevol) { //Ӧ����С���
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
			//printf("%s", "Waring ");
			std::cout << "Waring " << std::endl;
		}

		return movenow;
	}
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
		fileout << "v " << std::setprecision(13) << std::setw(20) << std::right
		        << (objgeo.point + i)->getcoorX() << ' '
		        << (objgeo.point + i)->getcoorY() << ' '
		        << (objgeo.point + i)->getcoorZ() << std::endl;      // ��������С����13λ�ľ������
	}

	for (int i = 1; i <= objgeo.vncount; i++) {         // ���㷨�������
		fileout << "vn " << std::setprecision(13) << std::setw(20) << std::right
		        << (objgeo.pointnormal + i)->getcoorX() << ' '
		        << (objgeo.pointnormal + i)->getcoorY() << ' '
		        << (objgeo.pointnormal + i)->getcoorZ() << std::endl;      // ��������С����13λ�ľ������
	}

	for (int i = 0; i < objgeo.facecount; i++) {         // �����
		fileout << "f " << std::setprecision(13) << std::right
		        << (objgeo.face + i)->getpointAindex() << "//" << (objgeo.face + i)->getpointAindex() << ' '
		        << (objgeo.face + i)->getpointBindex() << "//" << (objgeo.face + i)->getpointBindex() << ' '
		        << (objgeo.face + i)->getpointCindex() << "//" << (objgeo.face + i)->getpointCindex() << ' '
		        << std::endl;      // ��������С����13λ�ľ������
	}

	//fileout.clear();
	delete[]outfilepathchartmp;
	fileout.close();
}
