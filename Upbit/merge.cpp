#include "master.h"

ofstream outfile;
void mprint(unsigned char x)
{
	bitset<8> y(x);
	outfile << y <<" ";
}


unsigned char wah_compression(unsigned char prevword, unsigned char c, int size)
{
	if(prevword<=pow(2,size-1)-1)// prevword is fill word and there is scope to add
	{	 
		if(c==0)//current word is 0 fill
		{
			if(prevword<pow(2,size-2)-1)//prevword is 0 fill and there is scope to add
				prevword = prevword+1;
			else//prevword is 1 fill
			{
				mprint(prevword);
				prevword= 1;
			}
		}
		else//current word is 1 fill
		{
			if(prevword>=pow(2,size-2) && prevword<pow(2,size-1)-1)// prev word is 1 fill and there is scope to add(already checked above)
				prevword = prevword+1;
			else//prevword is 0 fill
			{
				mprint(prevword);
				prevword = pow(2,size-2)+1;
			}
		}
	}
	else //prevword is literal word(already got mprinted)
	{
		if(c==pow(2,size-1)-1)//current word is 1 fill
		    prevword = pow(2,size-2)+1;
		else//current word is 0 fill
		    prevword= 1;
	}	

	return prevword;
}


int merge(string VBfilename, string UBfilename)
{
	int i,size = 8;
	unsigned char msbit1,msbit2;
	unsigned char bit1,bit2;
	unsigned char whichbit1,whichbit2;
	unsigned char a=0,b=0,c=0;
	unsigned char prevword = 0;

	int endpos1,endpos2;

	ifstream inp1(VBfilename.c_str());
	ifstream inp2(UBfilename.c_str());
	
	std::size_t found = UBfilename.find_last_of("/");
	string tempfilename = "temp_"+ UBfilename.substr(found+1);
	
	
	outfile.open(tempfilename.c_str());

	int runs1 = 0,runs2 = 0;
	
	int validbits;
	/*
	inp1.seekg(-2,ios_base::end);
	inp1 >> bit1;
	
	validbits = bit1 - 48;*/
	
	int I=2;char ch;
	int len;
	inp1.seekg(0,std::ios_base::end);
	len = inp1.tellg();
	inp1.seekg(-I, ios_base::end);
    inp1>>ch;
           while(ch!='['&&I<=len)
            {
				++I;
                inp1.seekg(-I, ios_base::end);
                inp1>>ch;
            }
            
    inp1>>validbits;
	endpos1 = inp1.tellg();

	/*inp2.seekg(-2,ios_base::end);
	inp2 >> bit2;*/
	I=2;
	inp2.seekg(0,std::ios_base::end);
	len = inp2.tellg();
	inp2.seekg(-I, ios_base::end);
    inp2>>ch;
           while(ch!='['&&I<=len)
            {
				++I;
                inp2.seekg(-I, ios_base::end);
                inp2>>ch;
            }
            
    inp2>>validbits;
	
	endpos2 = inp2.tellg();

	if(validbits != size-1)
	{
		inp1.seekg(-11,ios_base::cur);	
		inp2.seekg(-11,ios_base::cur);
	}
	
	else
	{
		inp1.seekg(-2,ios_base::cur);
		inp2.seekg(-2,ios_base::cur);
	}

	endpos1 = inp1.tellg();
	endpos2 = inp2.tellg();
	inp1.seekg(ios_base::beg);
	inp2.seekg(ios_base::beg);
	

	while(true)
	{	
		if(runs1 == 0)
		{
			a = 0;
			inp1 >> msbit1;
			if(inp1.tellg() == endpos1+1)
				break;

			if(msbit1 == '1')
			{
				for(i = 1;i<=size-1;i++)
				{
					inp1 >> bit1;
					a += pow(2,size-1-i) * (bit1 - 48);
				}
			}

			else if(msbit1 == '0')
			{
				inp1 >> whichbit1;
				for(i = 1;i<=size-2;i++)
	        	{
	        		inp1 >> bit1;
	        		runs1 += pow(2,size-2-i) * (bit1-48);
	        	}

	        	if(whichbit1 == '1')
	        	{
	        		a = pow(2,size-1)-1;
	        	}

	        	else
	        	{
	        		a = 0;
	        	}
			}	
		    //inp1 >> bit1;
		}

			
		if(runs2 == 0)
		{
			b = 0;
			inp2 >> msbit2;
			if(inp2.tellg() == endpos2+1)
				break;

			if(msbit2 == '1')
			{
				for(i = 1;i<=size-1;i++)
				{
					inp2 >> bit2;
					b += pow(2,size-1-i) * (bit2 - 48);
				}
			}

			else if(msbit2 == '0')
			{
				inp2 >> whichbit2;
				for(i = 1;i<=size-2;i++)
	        	{
	        		inp2 >> bit2;
	        		runs2 += pow(2,size-2-i) * (bit2-48);
	        	}

	        	if(whichbit2 == '1')
	        	{
	        		b = pow(2,size-1)-1;
	        	}
	        	else
	        	{
	        		b = 0;
	        	}
			}
			//inp2 >> bit2;
		}

		if(runs1 != 0)
		{
			runs1--;
		}

		if(runs2 != 0)
		{
			runs2--;
		}

		c = a ^ b;


		//resultant word is a literal word
		if(c != 0 && c != (pow(2,size-1) - 1))
		{
			//check if the prevword was a fill word
			//if fill then it has to be mprinted
			if(prevword<pow(2,size-1)-1 && prevword > 0)
			{
				mprint(prevword);
			}
			c = c | (1 << (size-1));
			prevword = c;
			mprint(prevword);
		}
		
		else
		{
			//resultant word is a fill word
			prevword = wah_compression(prevword,c,size);
		}
	}
    
	if(validbits != size-1)
	{
		inp2 >> bit2;
		a = 0,b = 0;

		for(i = size-2;i>=0;i--)
		{
			inp1 >> bit1;
			a += pow(2,i) * (bit1 - 48);

			inp2 >> bit2;
			b += pow(2,i) * (bit2 - 48);
		}
		
		c = a ^ b;
		c = c | (1 << (size-1));

		if(prevword<pow(2,size-1) && prevword > 0)
		{
			mprint(prevword);
		}
		mprint(c);		
	}

	else
	{
		if(c != 0 && c != (pow(2,size-1) - 1))
		{
			if(prevword<pow(2,size-1) && prevword > 0)
			{
				mprint(prevword);
			}
			c = c | (1 << (size-1));
			mprint(c);
		}
		else
		{
			if(prevword<pow(2,size-1) && prevword > 0)
			{
				mprint(prevword);
			}
		}
	}
	outfile << "[" << validbits << "]"; 
	inp1.close();
	inp2.close();	
	outfile.close();
	rename(tempfilename.c_str(),VBfilename.c_str());

	return 0;
}

void mergeall(string wahfolder)
{
	//with multiprocessing
    
    //cout<<"Parallelly merging"<<endl;
    
	vector<string> cols = listFile("./"+wahfolder);
	for(int i = 0; i < cols.size(); i++)
	{
		string colfolder = "./"+wahfolder+"/"+cols[i];
		system(("python merge.py "+colfolder).c_str());
	}
	
	for(map<string,int>::iterator it = NumberOfUpdates.begin(); it != NumberOfUpdates.end(); ++it) {
		NumberOfUpdates[it->first] = 0;
	}
	NoOfUbvs_GOE_T = 0;
}

/*vector<string> cols = listFile("./"+wahfolder);
	std::map<string,string>::iterator it;
	for(int i = 0; i < cols.size(); i++)
	{
		string colfolder = "./"+wahfolder+"/"+cols[i];
		vector<string> vbs = listFile(colfolder+"/vbv");
		for(int j=0;j<vbs.size();j++)
		{
			int found = vbs[i].find(".");
			string ub = vbs[i].substr(0,found)+"u"+".txt";
			merge(colfolder+"/vbv/"+vbs[i],colfolder+"/ubv/"+ub);
		}		
	}*/