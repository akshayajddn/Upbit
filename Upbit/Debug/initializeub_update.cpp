#include <iostream>
#include <fstream>
#include <bitset>
#include <math.h>
#include <cstdio>
#include <sstream>
#include <string>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <sys/stat.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;
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
void initializeUB(string colfolder,string VB)
{
// example: 
//colfolder:"./file1_wah/c1" 
//VB:"c1_10.txt"
	int found = VB.find(".");
    writ.open(("./"+colfolder+"/ubv/"+VB.substr(0,found)+"u"+".txt").c_str(), ios::out | ios::trunc);
  	//cout<<"./"+colfolder+"/vbv/"+VB<<endl;
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


int main(int argc, char *argv[])
{

	initializeUB(argv[1],argv[2]);
	return 0;
}


