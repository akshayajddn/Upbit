#include "master.h"


fstream is;

void iprint(unsigned char x)
{
	bitset<8> y(x);
	is << y<<" ";
}	

void iprint(int x)
{
	is<<"["<<x<<"]";
}

void iprint(string str)
{
	is<<str<<" ";
}



void insert0(string filename)
{
	 char ch;int llen,len;int I;
    unsigned char word=0;
    int size =sizeof(word)*8;
	
	word =0;
            is.open(filename.c_str());
          
            is.seekp(0, std::ios_base::end);
            len = is.tellp();
           
            I=2;
            is.seekp(-I, ios_base::end);
            is>>ch;
            while(ch!='['&&I<=len)
            {
                ++I;
                is.seekp(-I, ios_base::end);
                is>>ch;
            }
            
            is>>llen;
			
			 if(llen == size -1)//full prev word
                {
                    word =  pow(2, size-1);
					I = llen>9?4:3;
					is.seekp(-I, ios_base::end);
					iprint(word);
					iprint(1);
                    
                }
				else if(llen+1==size-1)//literal word
				{
					I = llen>9?5+size:4+size;
                    is.seekp(-I, ios_base::end);
                    for(int i=0;i<size;i++)
                    {
                        is>>ch;
                        if(ch=='1')
                        word = (word<<1)+1;
                        else
                        word =word<<1;
                    }
					if(word==pow(2,size-1))//now a 0 fill
					{
							unsigned char prevword;
							I = llen>9?5+size*2+1:4+size*2+1;
							is.seekp(-I, ios_base::end);
								for(int i=0;i<size;i++)
								{
								is>>ch;
								if(ch=='1')
								prevword = (prevword<<1)+1;
								else
								prevword =prevword<<1;
								}
							//cout<<(int)prevword<<" "<<pow(2,size-2)-1<<endl;
							if(prevword<pow(2,size-2)-1)//prevword is 0 fill and scope to add
							{
								I = llen>9?5+size*2+1:4+size*2+1;
								is.seekp(-I, ios_base::end);
								prevword=prevword+1;
								iprint(prevword);
								iprint(size-1);
								long int length = is.tellg(); 
								truncate(filename.c_str(),length);
								
								
							}
							else
							{
								I = llen>9?5+size:4+size;
								is.seekp(-I, ios_base::end);
								word = 1;
								iprint(word);
								iprint(size-1);
							}
					}
					else
					{
						word=(word<<1);
						is.seekp(-I, ios_base::end);
						unsigned char Y= pow(2, size-1);
						word = word|Y;
						iprint(word);
						iprint(llen+1);
					}
                    
				}
                else//prevword is literal word and not full
                {
					I = llen>9?5+size:4+size;
                    is.seekp(-I, ios_base::end);
                    for(int i=0;i<size;i++)
                       {
                         is>>ch;
						 if(ch=='1')
							word = (word<<1)+1;
						 else
							word =word<<1;
						}
					word=(word<<1);
					unsigned char Y= pow(2, size-1);
					word = word|Y;
                    is.seekp(-I, ios_base::end);
					iprint(word);
                    iprint(llen+1);
                }
				
				if(is.is_open()) is.close();
}

void insert1(string filename)
{
	//cout<<filename<<endl;
	
	 char ch;int llen,len;int I;
    unsigned char word=0;
    int size =sizeof(word)*8;
	
	word =0;
            is.open(filename.c_str());
          
            is.seekp(0, std::ios_base::end);
            len = is.tellp();
           
            I=2;
            is.seekp(-I, ios_base::end);
            is>>ch;
            while(ch!='['&&I<=len)
            {
                ++I;
                is.seekp(-I, ios_base::end);
                is>>ch;
            }
            
            is>>llen;
			
     if(llen == size -1)//full prevword - literal or fill
                            {
                                word =  pow(2, size-1)+1;
                                I = llen>9?4:3;
                                is.seekp(-I, ios_base::end);
                                iprint(word);
                                iprint(1);
                                
                            }
                            else//incomplete prevword->literal
                            {
                                I = llen>9?5+size:4+size;
                                is.seekp(-I, ios_base::end);
                                for(int i=0;i<size;i++)
                                {
                                    is>>ch;
                                    if(ch=='1')
                                        word = (word<<1)+1;
                                    else
                                        word =word<<1;
                                }
								word=(word<<1)+1;
                                unsigned char Y = pow(2,size-1);
                                word = word|Y;
								if(word==pow(2,size)-1)//1fill as literal
								{
									unsigned char prevword;
									I = llen>9?5+size*2+1:4+size*2+1;
									is.seekp(-I, ios_base::end);
										for(int i=0;i<size;i++)
										{
										is>>ch;
										if(ch=='1')
											prevword = (prevword<<1)+1;
										else
											prevword =prevword<<1;
										}
										//cout<<(int)prevword<<endl;
									if(prevword>=pow(2,size-2)&&prevword<pow(2,size-1)-1)
										//prev word is 1 fill word with scope to add
									{
										I = llen>9?5+size*2+1:4+size*2+1;
										is.seekp(-I, ios_base::end);
										prevword=prevword+1;
										iprint(prevword);
										iprint(size-1);
										long int length = is.tellg(); 
										truncate(filename.c_str(),length);
									}
									else//prevword is either not 1fill or no scope to add
									{
									I = llen>9?5+size:4+size;
									is.seekp(-I, ios_base::end);
									word = pow(2,size-2)+1;
									iprint(word);
									iprint(size-1);
									}
								}
                                else//not 7 consecutive insertions
								{
								is.seekp(-I, ios_base::end);
                                iprint(word);
                                iprint(llen+1);
								}
                            }			
			
			
			if(is.is_open()) is.close();
}

void newinsert(string wahfolder,std::map<string,string> mymap)
{
	
    vector<string> cols = listFile("./"+wahfolder);
	std::map<string,string>::iterator it;
	for(int i = 0; i < cols.size(); i++)
	{
		vector<string> bvs = listFile("./"+wahfolder+"/"+cols[i]+"/vbv");
		
		it = mymap.find(cols[i]);
		if (it != mymap.end())//entry present
		{
			string newval = mymap.find(cols[i])->second;
			
			string col1 = cols[i]+'_'+newval+ ".txt";
			//col1 = "./"+wahfolder+"/"+col+"/vbv/"+col1;
			for(int j = 0; j < bvs.size(); j++)
			{
				if(bvs[j].compare(col1)==0)//newval column
					insert1("./"+wahfolder+"/"+cols[i]+"/vbv/"+bvs[j]);
				else
					insert0("./"+wahfolder+"/"+cols[i]+"/vbv/"+bvs[j]);
			}
			
		}
		else//entry absent
		{
			for(int j = 0; j < bvs.size(); j++)
			{
				insert0("./"+wahfolder+"/"+cols[i]+"/vbv/"+bvs[j]);
			}
		}
				
		bvs = listFile("./"+wahfolder+"/"+cols[i]+"/ubv");
		for(int j = 0; j < bvs.size(); j++)
			insert0("./"+wahfolder+"/"+cols[i]+"/ubv/"+bvs[j]);
			
	}
}

