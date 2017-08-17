#ifndef HEADER_H
#define HEADER_H

#define THRESHOLD 5
#define SEC_THRESHOLD_MULTIPLIER 1.75

#include <stdio.h>
#include <iostream>  
#include <fstream>   
#include <math.h>
#include <bitset>
#include <sstream>
#include <string>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <sys/stat.h>
#include <sys/time.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <map>
#include <time.h>  

using namespace std;

extern int size;
extern ifstream infile;
extern ofstream outfile;
extern fstream is;
extern fstream uinfile;
extern fstream uoutfile;
extern ofstream writ;
extern std::map<string,int> NumberOfUpdates;
extern int NoOfUbvs_GOE_T;
extern int multiprocessing;

template <typename T>
  string ToString ( T Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }



//merge
void mprint(unsigned char x);
unsigned char wah_compression(unsigned char prevword, unsigned char c, int size);
int merge(string UBfilename, string VBfilename);
void mergeall(string wahfolder);

//insert
void iprint(unsigned char x);
void iprint(int x);
void iprint(string str);
void insert0(string filename);
void insert1(string filename);
void newinsert(string wahfolder,std::map<string,string> mymap);

//update
int uprint(unsigned char);
int getWordType(int endpos, int validbits, int k);
unsigned char AdjustWithPrevWord(unsigned char prevword, unsigned char word);
unsigned char AdjustNextFill(unsigned char prevword, unsigned char word);
unsigned char AdjustNextWord(unsigned char prevword, int endpos);
int flipbit(string UBfilename,int k);
void newupdate(string wahfolder,string colname, int row, string newval);

//read
string newread(string colfolder, int row);

//delete
void newdelete(string wahfolder,int row);

//wah
void print(unsigned char x);
void print(int x);
void print(string str);
vector<string> listFile(string foldername);
void compress(string outputfolder,string inputfolder,string colfilename);
string wah(string inputfolder);
void initializeUB(string wahfolder,string VB);
void initializeUBs(string wahfolder);
void createfps(string wahfolder);

//wah
//int getKthbit(string filename,int k);

//master
string setup(string inputfolder);
void runqueries(string folder, string queryfile);

//other files (in Debug folder)
//fp.py
//rowbit.py
//merge_update.cpp
//initializeub_update.cpp
//merge.py


//input files (in Debug folder)
// _un folder
//queries.txt


#endif