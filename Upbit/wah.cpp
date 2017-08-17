#include "master.h"


//1st bit is 1 for literal word and 0 for fill word

ofstream writ;

void print(unsigned char x)
{
	bitset<8> y(x);
	writ << y<<" ";
}

void print(int x)
{
	writ<<"["<<x<<"]";
}

void print(string str)
{
	writ<<str<<" ";
}

vector<string> listFile(string foldername){
	vector<string> columns;
        DIR *pDIR;
        struct dirent *entry;
        if( (pDIR=opendir(foldername.c_str())) ){
                while((entry = readdir(pDIR))){
                        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
                        columns.push_back(entry->d_name);
                }
                closedir(pDIR);
        }
	return columns;
}

void compress(string outputfolder,string inputfolder,string colfilename)
{
    
  string infilename = "./"+inputfolder+"/"+colfilename;
  ifstream read;
  read.open(infilename.c_str());   

  int found = colfilename.find(".");
  string colfolder =outputfolder+"/"+colfilename.substr(0,found);
  mkdir(colfolder.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  mkdir((colfolder+"/vbv").c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  mkdir((colfolder+"/ubv").c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  string line;
  while (std::getline(read, line))
  {
	  //
  unsigned char prevword,word=0;
  int prev;
  int c;
  int count=0,flag=0;
  int size = sizeof(prevword)*8;
  prevword=pow(2,size-1);
	  //
  istringstream readline(line);
  string col_val;
  readline>>col_val;
  col_val = col_val.substr(1,col_val.length()-2);
  writ.open((colfolder+"/vbv/"+colfilename.substr(0,found)+"_"+col_val+".txt").c_str(), ios::out | ios::trunc);
  
  readline>>prev;
  count++;

  while(readline>>c) 
  {
	  count++;
	  if(flag == 2 ||(prev==c&& flag==0))//flag 0 for first two bits of first word,
										 //flag 1 for literal word 
										 //flag 2 for new word
      {//cout<<endl<<"M"<<prev<<c;
		  if(flag==2)flag=0;
		  //if(flag==0&&count>2)flag=2;
		  if(count==size-1)// a fill occured
		  { //cout<<"F";
			  if(prevword<=pow(2,size-1)-1)// prevword is fill word and there is scope to add
			  {	 
				  if(c==0)//current word is 0 fill
				  {
					  if(prevword<pow(2,size-2)-1)//prevword is 0 fill and there is scope to add
						  prevword = prevword+1;
					  else//prevword is 1 fill
					  {
						  print(prevword);
						  prevword= 1;
					  }
				  }
				  else//current word is 1 fill
				  {
					  if(prevword>pow(2,size-2)&&prevword<pow(2,size-1)-1)// prev word is 1 fill and there is scope to add(already checked above)
					    prevword = prevword+1;
					  else//prevword is 0 fill
					  {
						  print(prevword);
						  prevword = pow(2,size-2)+1;
					  }
				  }
			  }
			  else //prevword is literal word(already got printed)
			  {
				  if(c==1)//current word is 1 fill
				    prevword = pow(2,size-2)+1;
				  else//current word is 0 fill
				    prevword= 1;
			  }
			  word = 0;
			  count=0;
			  flag=2;//a new word is going to start
		  }
      }
      else
      {
		  //cout<<"count here:"<<count<<" ";cout<<" Flag"<<flag<<endl;
			  
          //this word is found to be literal word now
		  unsigned char Y= pow(2, size-1);
		  if(flag==0&&count==2)
		  {
			  flag=1;
			  if(prev==0)
				word =Y;
			  else
				word=Y+1;//cout<<"prev "<<prev <<" here1 ";print(word);
		  }
		  else if(flag==0&&count>2)
		  {//cout<<"Y"<<prev<<c<<" ";
			  flag=1;//this is a literal word
			  if(prev==1)
			  {
				  for(int i=0;i<count-1;i++)
					  {
						  word = (word<<1)|Y;
						  word++;  
					  }
			  }
			
			  
				  
		  }
		  
		  word=(word<<1)|Y;//cout<<"H ";print(word);
		  
		  if(c==1)
			word++;		  
		   
		  //cout<<"c "<<c<< " heunsigned char prevword,word=0;re2 ";print(word);
		  
		  if(count==size-1)
		  {
			  if(prevword<pow(2,size-1))
				  print(prevword);
			  print(word);
			  prevword=word;
			  word=0;
			  count =0;
			  flag =2;
		  } 
      }	  
	  prev=c;
  }//while ends
  if(prevword<pow(2,size-1))
	print(prevword);
  if(count>0)
	  {unsigned char Y= pow(2, size-1);
	  if(word==0&&c==1)
	  {
		  word = pow(2,count)-1;
	  }
	  word = word|Y;
	  print(word);}
  else count = size-1;
  print(count);
  count=0;
  writ.close();
  }
  read.close();
  
}

string wah(string inputfolder)
{
  int found = inputfolder.find("_");
  string outputfolder = inputfolder.substr(0,found)+"_wah";
  system(("rm -rf "+outputfolder).c_str());
  mkdir(outputfolder.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  vector<string> colfilenames = listFile("./"+inputfolder);
  for(int i = 0; i < colfilenames.size(); i++)
    compress(outputfolder,inputfolder,colfilenames[i]);
  return outputfolder;
}

void initializeUB(string colfolder,string VB)
{
	int found = VB.find(".");
	string ubv =VB.substr(0,found)+"u"+".txt";
    writ.open(("./"+colfolder+"/ubv/"+ubv).c_str(), ios::out | ios::trunc);
  	//cout<<"./"+colfolder+"/vbv/"+VB<<endl;VB.substr(0,found)+"u"+".txt"
	NumberOfUpdates[ubv]=0;
	ifstream read(("./"+colfolder+"/vbv/"+VB).c_str());
    char bit;
    char msbit;
	unsigned char word = 0,temp;
	int size = sizeof(word)*8;
    int i;
    while(read >> msbit)
    {  
		if(msbit=='[')
			break;
        else if(msbit == '1')
        {
        	if(word+1 < pow(2,size-2))
        	{
        	    word += 1;
        	}
			else
			{
				print(word);
				word=1;
			}
			read.ignore(size,' ');
		}
        else
        {
        	int runs = 0;
        	read >> bit;
        	for(i = 1;i<=size-2;i++)
        	{
        		read >> bit;
        		runs += pow(2,size-2-i) * (bit-'0');
        	}
			if(word+runs < pow(2,size-2))
        	{
				word += runs;
			}
			else
			{
				temp=word;
				word = pow(2,size-2)-1;
				print(word);
				word = temp + runs - word;
			}
        	read.ignore(1,' ');
        }

    }
	int llen;
	read >>llen;
	if(llen==7)
	{
		print(word);
		print(size-1);
	}
	else
	{
		word = word - 1;
		print(word);
		word = pow(2,size-1);
		print(word);
		print(llen);
	}
	writ.close();
    read.close();
}

void initializeUBs(string wahfolder)
{ 
	vector<string> VBs = listFile("./"+wahfolder);
    for(int i = 0; i < VBs.size(); i++)
	{
		vector<string> vbs = listFile("./"+wahfolder+"/"+VBs[i]+"/vbv");
		for(int j = 0; j < vbs.size(); j++)
			initializeUB(wahfolder+"/"+VBs[i],vbs[j]);
	}	
		
		
		//initializeUB(wahfolder,VBs[i]);
	
}

void createfps(string wahfolder)
{
	vector<string> cols = listFile("./"+wahfolder);
	int fencelengh =5;
    for(int i = 0; i < cols.size(); i++)
	{
		system(("python fp.py ./"+wahfolder + "/"+cols[i]+" "+ToString(fencelengh)).c_str());
	}
}








