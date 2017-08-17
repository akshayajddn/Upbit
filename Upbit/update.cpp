#include "master.h"

fstream uinfile;
fstream uoutfile;
int size = 8;

int uprint(unsigned char c)
{
	bitset<8> y(c);
	uoutfile << y << " ";
	return 0;
}

int getWordType(int endpos, int validbits, int k)
{
    int i,count = 0;
    int remainingruns;
    unsigned char msbit,whichbit,bit;
    int ignorebits;
    int newk;
    
    uinfile >> msbit;
    while(uinfile.tellg() < endpos)
    {
        if(msbit == '1')
        {
        	if(k > count+7)
        	{
        	    count += 7;
        	    uinfile.ignore(8,' ');
        	}
        	else
        	{
        		uinfile.seekg(-1,uinfile.cur);
                return 0;
        	}
        }

        else
        {
        	int runs = 0;
        	int tempk=k;
        	uinfile >> whichbit;
        	for(i = 1;i<=6;i++)
        	{
        		uinfile >> bit;
        		runs += pow(2,6-i) * (bit-48);
        	}
        	tempk = tempk - count;
        	count += (7*runs);
        	if(k <= count)
        	{
        		remainingruns = (runs - tempk/7 - 1);
        		if(k%7 == 0)
        		{
        			remainingruns += 1;
        		}
                uinfile.seekg(-8, uinfile.cur);
                return remainingruns;
        	}	
        }
        uinfile >> msbit;
    }

    if(uinfile.tellg() == endpos+1)
    {
        if(validbits != size-1)
        {
            if ((count + validbits) < k )
            {
                cout << "Row underflow!!";
                return -2;
            }

            else
            {
                ignorebits = size-1-validbits;
                newk = k - count;
                newk = newk-1;
                uinfile.ignore(ignorebits+newk,' ');
           
                uinfile >> bit;
                uoutfile.close();
                uinfile.seekg(-1,ios_base::cur);

                int x = (bit - 48)^1;
                uinfile << x;

                uinfile.close();
                return -1;
            }

        }

        else
        {
            if(count < k)
            {
                cout << "Row underflow!!";
                return -2;
            }
        }
    }
    return 0;
    
}



unsigned char AdjustWithPrevWord(unsigned char prevword, unsigned char word)
{
	if(prevword<=pow(2,size-1)-1)// prevword is fill word
	{	 
		if(word==1)//current word is 0 fill
		{
			if(prevword<pow(2,size-2)-1)//prevword is 0 fill and there is scope to add
				prevword = prevword+1;
		    else//prevword is 1 fill
		    {
				uprint(prevword);
				prevword= 1;
		  	}
		}
	    else//current word is 1 fill i.e. it is 65
	    {
		 	if(prevword>pow(2,size-2) && prevword<pow(2,size-1)-1)// prev word is 1 fill and there is scope to add(already checked above)
		    	prevword = prevword+1;
		  	else//prevword is 0 fill
		  	{
				uprint(prevword);
				prevword = pow(2,size-2)+1;
		  	}
	  	}
    }
    else //prevword is literal word
    {
    	uprint(prevword);
		if(word==1)//current word is 0 fill
			prevword = 1;
	  	else//current word is 1 fill
	    	prevword= pow(2,size-2)+1;
  	}
  	return prevword;
}


unsigned char AdjustNextFill(unsigned char prevword, unsigned char word)
{
	unsigned char diff;
	if(prevword<pow(2,size-1)-1)// prevword is fill word and there is scope to add
	{ 	 
		if(word<pow(2,size-2))//current word is 0 fill
	    {
	    	if(prevword<pow(2,size-2)-1)//prevword is 0 fill and there is scope to add
	    	{
	    		diff = pow(2,size-2)-1 - prevword;
	    		if(word > diff)
	    		{
	    			prevword += diff;
	    			word -= diff;
	    			uprint(prevword);
	    			prevword = word;
	    		}
	    		else
	    		{
	    			/*diminish that word*/
	    			prevword += word;
	    		}
	    	}
		  	else//prevword is 1 fill or a 0 fill which has no scope to add
		  	{
				uprint(prevword);
			  	prevword = word;
		  	}
	  	}
	  	else//current word is 1 fill
	  	{	
			if(prevword>pow(2,size-2))// prev word is 1 fill and there is scope to add(already checked above)
		    {
		    	diff = pow(2,size-1)-1 - prevword;
	    		if(word-pow(2,size-2) > diff)
	    		{
	    			prevword += diff;
	    			word -= diff;
	    			uprint(prevword);
	    			prevword = word;
	    		}
	    		else
	    		{
	    			/*diminish that word*/
	    			prevword = prevword + (word - pow(2,size-2));
	    		}
		    }
		  	else//prevword is 0 fill
		  	{
				uprint(prevword);
			  	prevword = word;
		  	}
	  	}
    }

    else /*previous word is a literal word or a fully exhausted fill word*/
    {
    	uprint(prevword);
    	prevword = word;
    }
    return prevword;
}



unsigned char AdjustNextWord(unsigned char prevword, int endpos)
{
    unsigned char msbit,bit;
    unsigned char word;

	uinfile >> msbit;
	while(uinfile.tellg() < endpos)
	{
	  	if(msbit == '1')
	  	{
	  		uinfile.seekg(-1,uinfile.cur);
	  		uprint(prevword);	
	  		break;
	  	}
	  	/*form the fill word*/
	  	word = 0;
	  	for(int i = 1;i<=7;i++)
	  	{
	  		uinfile >> bit;
	  		word += pow(2,size-1-i) * (bit-48);
	  	}
  		prevword = AdjustNextFill(prevword,word);
  		uinfile >> msbit; 	
    }
    return prevword;
}





int flipbit(string UBfilename,int k)
{
	std::size_t found = UBfilename.find_last_of("/");
	NumberOfUpdates[UBfilename.substr(found+1)] += 1;
    int i,j,pos;
    int flag = 0;
    char remainingruns = 0;
    unsigned char newruns = 0;
    unsigned char prevword = 0,word = 0;
    unsigned char whichbit,msbit,bit;
    int validbits,endpos;
    //string outputfilename = foldername + "output1.txt";

    //cin >> k;
    
    uinfile.open(UBfilename.c_str());
    //system("rm output1.txt");
    uoutfile.open("output1.txt",ios::in | ios::out | ios::trunc);

    /*uinfile.seekg(-2,ios_base::end);
    uinfile >> bit;
    validbits = bit - 48;*/
	int I=2;char ch;
	int len;
	uinfile.seekp(0,std::ios_base::end);
	len = uinfile.tellp();
	uinfile.seekp(-I, ios_base::end);
    uinfile>>ch;
           while(ch!='['&&I<=len)
            {
				++I;
                uinfile.seekp(-I, ios_base::end);
                uinfile>>ch;
            }
            
    uinfile>>validbits;
	
	
    if(validbits == size-1)
    {
        uinfile.seekg(-2,ios_base::cur);
    }
    else
    {
        uinfile.seekg(-11,ios_base::cur);
    }
    //cout << validbits;
    endpos = uinfile.tellg();
    uinfile.seekg(ios_base::beg);

    remainingruns = getWordType(endpos,validbits,k);
    
    if(remainingruns == -2 || remainingruns == -1)
    {
        return 0;
    }

    if(uinfile.tellg() != 0)
    {
    	uinfile.seekg(-size-1,ios_base::cur);
    	flag = 1;	
    }
  
    int end = uinfile.tellg();
    uinfile.seekg(ios_base::beg);
    char *s = new char[end+1];
    memset(s,'\0',end+1);
    uinfile.read(s,end);
    uoutfile << s;
	
    /*monster code*/
    //uinfile >> bit;
    

    if(flag == 1)
    {
    	for(i=1;i<=8;i++)
    	{
        	uinfile >> bit;
        	prevword += pow(2,8-i) * (bit-48);
    	}
    }

    else
    {
    	prevword = 0;
    }
    
    
    uinfile >> msbit;

    if(msbit == '1')
    {
        //word = pow(2,size-1);
        /*position to modify in the literal word*/
        word = 0;
        if(k%(size-1) == 0)
        {
        	pos = size-1;
        }
        else
        {
        	pos = k%(size-1);
        }
        
        //uinfile.ignore(1,' ');

        for(i=1;i<pos;i++)
        {
            uinfile >> bit;
            word += pow(2,size-1-i) * (bit-48);
        }
        uinfile >> bit;
        word += pow(2,size-1-i)*((bit-48) ^ 1);
        i++;

        for(j = i;j<=size-1;j++)
        {
            uinfile >> bit;
            word += pow(2,size-1-j) * (bit-48);
        }
        /*if word remains literal*/
        if(word != 0 && word != pow(2,size-1)-1)
        {
        	word = word | (1 << (size-1));
        	if(prevword != 0)
        	{
        		uprint(prevword);
        	}
        	uprint(word);
            /*copy the rest of the file into the output file*/
        }

        /*if word becomes fill*/
        else
        {
        	if(word == pow(2,size-1)-1)
        	{
        		word = 1;
        		word = word | (1 << (size-2));	
        	}
        	else
        	{
        		word = 1;
        	}
        	
        	if(prevword == 0)
        	{
        		prevword = word;
        	}
        	else
        	{
        		prevword = AdjustWithPrevWord(prevword,word);
        	}
        	prevword = AdjustNextWord(prevword,endpos);
        }
    }
    
    else/*a fill occurred*/
    {
    	
    	uinfile >> whichbit;
    	for(i = 1;i<=size-2;i++)
    	{
    		uinfile >> bit;
    		word += pow(2,size-2-i) * (bit-48);
    	}
    	
    	newruns = word - remainingruns - 1;
    	//newruns = newruns | ((whichbit-48)<<(size-2));

    	if(prevword != 0)
    	{
    		uprint(prevword);
    	}

    	if(newruns != 0)
    	{
    		newruns = newruns | ((whichbit-48)<<(size-2));
    		uprint(newruns);	
    	}
    	
    	/*creating a literal word*/
    	word = pow(2,size-1);
    	if(k%(size-1) == 0)
        {
        	pos = size-1;
        }
        else
        {
        	pos = k%(size-1);
        }
    	for(i = 1;i< pos;i++)
    	{
    		word += pow(2,size-1-i) * (whichbit-48);
    	}
    	word += pow(2,size-1-i)*((whichbit-48) ^ 1);
    	i++;

    	for(int j = i;j<=size-1;j++)
    	{
    		word += pow(2,size-1-j) * (whichbit-48);	
    	}

    	uprint(word);
    	
    	prevword = remainingruns;
    	prevword = prevword | ((whichbit-48) << (size-2));
		
		if(prevword != 0 && prevword != pow(2,size-2))
		{
			prevword = AdjustNextWord(prevword,endpos);	
		}
    }

    
    if(uinfile.tellg() == endpos+1)
    {
        uinfile.seekg(-1,ios_base::cur);
    	uprint(prevword);
    }
    
    
    /*if a literal word, or a different fill occured*/
    /*copy the whole content*/
    int begin = uinfile.tellg();
    uinfile.seekg(0,uinfile.end);
    end = uinfile.tellg();
    uinfile.seekg(begin);
    char *s1 = new char[end-begin+1];
    memset(s1,'\0',end-begin+1);
    uinfile.read(s1,end - begin + 1);
    
	if(s1[0] == ' ')
	{
		uoutfile << s1+1;	
	}
	else
	{
		uoutfile << s1;
	}
    
    uinfile.close();
    uoutfile.close();

    rename("output1.txt",UBfilename.c_str());
	
	if(multiprocessing==1 && NumberOfUpdates[UBfilename.substr(found+1)]==THRESHOLD)
	{
		NoOfUbvs_GOE_T +=1;
	}
	
	if((multiprocessing==0 && NumberOfUpdates[UBfilename.substr(found+1)]==THRESHOLD)||
		(multiprocessing==1 && NumberOfUpdates[UBfilename.substr(found+1)]==SEC_THRESHOLD_MULTIPLIER*THRESHOLD))
	{
		string ubfile = UBfilename;
		std::size_t found_col  = UBfilename.find("/ubv");
		string colfolder = UBfilename.substr(0,found_col);
		UBfilename = UBfilename.substr(found+1);
		found = UBfilename.find("u.txt");
		string vbfile = UBfilename.substr(0,found)+".txt";
		merge(colfolder+"/vbv/"+vbfile,ubfile);
		initializeUB(colfolder,UBfilename.substr(0,found)+".txt");
		if(multiprocessing==1)NoOfUbvs_GOE_T -= 1;
	}
	
	

    return 0;
}




void newupdate(string wahfolder,string colname, int row, string newval)
{
	string colfolder = "./"+ wahfolder+"/"+colname;
	string oldval = newread(colfolder,row);
	if(oldval.compare("-1")!=0)
		flipbit(colfolder+"/ubv/"+colname+"_"+oldval+"u.txt",row);

	flipbit(colfolder+"/ubv/"+colname+"_"+newval+"u.txt",row);
}


