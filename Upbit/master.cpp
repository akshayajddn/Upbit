#include "master.h"

std::map<string,int> NumberOfUpdates;
int NoOfUbvs_GOE_T;
int multiprocessing;

string setup(string inputfolder)
{
  string wahfolder = wah(inputfolder);
  initializeUBs(wahfolder);
  createfps(wahfolder);
  return wahfolder;
}


void runqueries(string folder, string queryfile)
{
	fstream fout;
	string latencyfile;
	if(multiprocessing==1)
		latencyfile = "latencies_multi.txt";
	else
		latencyfile = "latencies_upbit.txt";
	fout.open(latencyfile.c_str(),ios::in | ios::out | ios::trunc);
	//time_t start,end;
	//std::chrono::time_point<std::chrono::system_clock> start,end;
	//std::chrono::duration<double> elapsed;
	struct timeval start, end;
	double elapsed;
	
	ifstream read;
    read.open(queryfile.c_str()); 
	string line;
	while (std::getline(read, line))
	{
		istringstream readline(line);
		char query;
		string colname;
		int val,row;
		readline>>query;
		
		std::map<string,string> mymap;
		
		//start = std::chrono::system_clock::now();
		gettimeofday(&start, NULL);
		switch(query)
		{
			case 'i':
						readline>>colname;
						readline>>val;
						mymap.insert ( std::pair<string,string>(colname,ToString(val)));
						while(readline>>colname)
						{
							readline>>val;
							mymap.insert ( std::pair<string,string>(colname,ToString(val)));
						}
						newinsert(folder,mymap);
						break;
			case 'd':
						readline>>row;
						newdelete(folder,row);
						break;
			case 'r':
						readline>>colname;
						readline>>row;
						newread(folder+"/"+colname,row);
						if(multiprocessing == 1 && NoOfUbvs_GOE_T>NumberOfUpdates.size()/2)
							mergeall(folder);
						break;
			case 'u':
						readline>>colname;
						readline>>row;
						readline>>val;
						newupdate(folder,colname, row,ToString(val));
						break;
			default:
						break;
		}
		gettimeofday(&end, NULL);
		//end = std::chrono::system_clock::now();
		//elapsed = end - start;
		elapsed = ((end.tv_sec - start.tv_sec) * 1000) 
					+ (end.tv_usec / 1000 - start.tv_usec / 1000);
		fout<<query<<" "<<elapsed<<endl;
	}
	fout.close();
}

int main(int argc, char **argv)
{
	string inputfolder,wahfolder,queryfile;
    //cout<<"hi";
	cout<<"give folder name of uncompressed files"<<endl;
    cin>>inputfolder;
	cout<<"give name of query file"<<endl;
    cin>>queryfile;
	//inputfolder = "sample_new";
	//queryfile = "queries.txt";
	wahfolder = setup(inputfolder);
    //system("rm -rf sample_wah/C0");
    //system("cp -r C0/ sample_wah/");
    //
	multiprocessing=1; 
	//156 with upbit, 84 with multi
	struct timeval start, end;
	gettimeofday(&start, NULL);
	runqueries(wahfolder,queryfile);
	gettimeofday(&end, NULL);
	double elapsed = ((end.tv_sec - start.tv_sec) * 1000) 
        + (end.tv_usec / 1000 - start.tv_usec / 1000);
	cout<<elapsed<<endl;
    
	//wahfolder = "file1_wah";
	
	/*std::map<string,string> mymap;
	mymap.insert ( std::pair<string,string>("c1",ToString(10)));
	mymap.insert ( std::pair<string,string>("c2",ToString(20)));
	newinsert("file1_wah",mymap);
	
	cout<<newread("file1_wah/c1",1)<<endl;
	newupdate("file1_wah","c1", 1,"10");
	newupdate("file1_wah","c2", 1,"10");
	cout<<newread("file1_wah/c1",1)<<endl;
	
	
	cout<<newread("file1_wah/c1",1)<<endl;
	cout<<newread("file1_wah/c1",1)<<endl;
	*/
	/*
   for(map<string,int>::iterator it = NumberOfUpdates.begin(); it != NumberOfUpdates.end(); ++it) {
		cout << it->first << " " <<it->second<<"\n";
	}
	
	
	
	for(map<string,int>::iterator it = NumberOfUpdates.begin(); it != NumberOfUpdates.end(); ++it) {
		cout << it->first << " " <<it->second<<"\n";
	}
	mergeall(wahfolder);
	for(map<string,int>::iterator it = NumberOfUpdates.begin(); it != NumberOfUpdates.end(); ++it) {
		cout << it->first << " " <<it->second<<"\n";
	}*/
	/* std::map<string,string> mymap;
	mymap.insert ( std::pair<string,string>("c1",ToString(10)));
	mymap.insert ( std::pair<string,string>("c2",ToString(20)));
	newinsert("file1_wah",mymap);*/
	
	//cout<<newread("file1_wah/c1",1);
	//initializeUBs("file1_wah");
	//newupdate("file1_wah","c1", 1,"10");
	//newdelete("file1_wah",1);
	//cout<<newread("file1_wah/c1",2);
	//merge("file1_wah/c1/vbv/c1_10.txt","file1_wah/c1/ubv/c1_10u.txt");
  
        
}

 




