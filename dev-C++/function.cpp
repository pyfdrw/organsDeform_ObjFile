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
	//objgeo.point[0] 与 objgeo.pointnormal[0]无意义
	//objgeo.face[0] 有意义
	objgeo.facecount = Fcount;
	objgeo.pointcount = Vcount;
	objgeo.vncount = VNcount;
	objgeo.point = new Point[Vcount + 1];
	objgeo.pointnormal = new Point[VNcount + 1];
	objgeo.face = new Face[Fcount + 1];

	filein.clear();  // 文件读取到结束时 使用seek是无效的，必须先clear
	//filein.close();
	filein.seekg(0L,std::ifstream::beg);    // 文件定重新向到文件开头
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

	std::stringstream ss; // 用于类型转换
	string filename;      // 用于存储文件名(整数转换成字符串)
	string objfilepath;   // 读取的objfile的具体路径
	float movelength[200];  // 存储器官偏移的长度
	ObjGeo objgeo; 
	int filetmp;
	for (int i = 0; i < namevol.organcount; i++) { //namevol中存储了器官数目，器官编号也存储在数组中了，
		filename.clear();
		ss.clear();
		ss << *(namevol.name + i);
		ss >> filename;
		objfilepath = WORKDIR + filename + ".obj";
		std::cout << filename + ".obj    " << std::endl;
		filetmp = storeGeo(objfilepath, objgeo);
		if (1 == filetmp) {      //file not found
			continue;
		}// 存储几何
		movelength[i] = organDeform(objgeo, *(namevol.vol + i)); // 偏移网格，偏移长度记录在movelength中

		geoOutput(OUTPUTDIR + filename + ".obj", objgeo);

		objgeo.freeObjGeo();

	}

	// 输出movelength[]到OUTPUTDIR + "movelength.txt"中
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

	float adddirection = 1;  //记录使平移增加的方向，外扩增加为1，内缩增加为-1
	objgeo += 0.05;
	float voltmp = fabs(objgeo.geoVolCal());
	if (voltmp >= vol) {
		adddirection = 0.5;
	} else {
		adddirection = -0.5;
	}
	objgeo += -0.05;

	float movemax = adddirection;
	float movemin = -adddirection;  //最多平移的距离,movemax体积增大最大平移距离，movemin体积缩小最大平移距离
	float movenow = 0;

	if (vol >= singlevol) { //应该缩小体积
		movemax = 0;
		movenow = movemin / 2;
		while ((movemax - movemin) > 0.00001) { //防止死循环
			objgeo += movenow;
			float voltmp = fabs(objgeo.geoVolCal());
			if (fabs(voltmp - singlevol) / singlevol < 0.001) { //相对误差小于0.1%
				break;
			} else if (voltmp >= singlevol) { //movenow不够长
				objgeo += -movenow;
				movemax = movenow;
				movenow = (movenow + movemin) / 2;

			} else if (voltmp < singlevol) { //movenow太长
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
	} else { //应该增大体积
		movenow = movemax / 2;
		movemin = 0;
		while ((movemax - movemin) > 0.00001) {
			objgeo += movenow;
			float voltmp = fabs(objgeo.geoVolCal());
			if (fabs(voltmp - singlevol) / singlevol < 0.001) { //相对误差小于0.1%
				break;
			} else if (voltmp >= singlevol) { //movenow太长
				objgeo += -movenow;
				movemax = movenow;
				movenow = (movenow + movemin) / 2;
			} else if (voltmp < singlevol) { //movenow不够长
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
	for (int i = 1; i <= objgeo.pointcount; i++) {         // 顶点输出
		fileout << "v " << std::setprecision(13) << std::setw(20) << std::right
		        << (objgeo.point + i)->getcoorX() << ' '
		        << (objgeo.point + i)->getcoorY() << ' '
		        << (objgeo.point + i)->getcoorZ() << std::endl;      // 浮点数以小数后13位的精度输出
	}

	for (int i = 1; i <= objgeo.vncount; i++) {         // 顶点法方向输出
		fileout << "vn " << std::setprecision(13) << std::setw(20) << std::right
		        << (objgeo.pointnormal + i)->getcoorX() << ' '
		        << (objgeo.pointnormal + i)->getcoorY() << ' '
		        << (objgeo.pointnormal + i)->getcoorZ() << std::endl;      // 浮点数以小数后13位的精度输出
	}

	for (int i = 0; i < objgeo.facecount; i++) {         // 面输出
		fileout << "f " << std::setprecision(13) << std::right
		        << (objgeo.face + i)->getpointAindex() << "//" << (objgeo.face + i)->getpointAindex() << ' '
		        << (objgeo.face + i)->getpointBindex() << "//" << (objgeo.face + i)->getpointBindex() << ' '
		        << (objgeo.face + i)->getpointCindex() << "//" << (objgeo.face + i)->getpointCindex() << ' '
		        << std::endl;      // 浮点数以小数后13位的精度输出
	}

	//fileout.clear();
	delete[]outfilepathchartmp;
	fileout.close();
}
