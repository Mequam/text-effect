#include <iostream>
#include <string.h>
#include <unistd.h>
#include "Rng.h"
using namespace std;
string parse(int argc,char ** argv)
{
	string ret_val = "";
	for (int i = 1;i<argc;i++)
	{
		int j = 0;
		while (argv[i][j] != '\x00')
		{
			ret_val += argv[i][j];
			j++;
		}
		ret_val += ' ';
	} 
	return ret_val;
}
string rand_string(string str,string key,int start,Rng* dice)
{
	for (int i = start;i<str.length()-1;i++)
	{
		str[i]=key[dice->Range(0,key.length())];
	}
	return str;

}
int main(int argc,char ** argv)
{
	//set up our constants
	Rng dice = Rng();
	string key = "/_=+-*/abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,()[]!?#;\"\'\\*<>{}"; 	
	string found = "";
	string parsed = parse(argc,argv);
	for (int i = 0;i<200;i++)
	{
		cout << rand_string(parsed,key,0,&dice) << '\r';
		flush(cout);
		usleep(200);
	}
	for (int i = 0;i<parsed.length();i++)
	{
		found=rand_string(parsed,key,i,&dice);
		cout << found + "\r";
		flush(cout);
		found[i]=parsed[i];
		usleep(20000);
	}
	cout << endl;

return 1;
}
