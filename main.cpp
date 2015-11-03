#include "mydata.h"

int main()
{
	string WORKDIR;
	fileHandle(WORKDIR);	std::ifstream objFileIn;
	//objFileIn.open(WORKDIR, std::ios::in);
	NameRefvol namevol;
	storeNameRefvol(WORKDIR , namevol);

	deformFunction(WORKDIR, namevol);

	return 1;
} 

