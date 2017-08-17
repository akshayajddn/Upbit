#include "master.h"


string newread(string colfolder, int row)
{
	FILE *in;
	char buff[512];


	if(!(in = popen(("python rowbit.py "+colfolder+" "+ToString(row)).c_str(), "r")))
	{
		pclose(in);
		return "-1";
	}

	while(fgets(buff, sizeof(buff), in)!=NULL){
		string str(buff);
		str = str.substr (0,str.length()-1); 
		pclose(in);
		return str;
	}
	//pclose(in);
}

