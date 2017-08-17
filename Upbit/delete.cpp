#include "master.h"

void newdelete(string wahfolder,int row)
{
	string colfolder;
	vector<string> cols = listFile("./"+wahfolder);
	for(int i = 0; i < cols.size(); i++)
	{
		colfolder = "./"+ wahfolder+"/"+cols[i];
		string oldval = newread(colfolder,row);
		if(oldval.compare("-1")!=0)
			flipbit(colfolder+"/ubv/"+cols[i]+"_"+oldval+"u.txt",row);
	}
}

