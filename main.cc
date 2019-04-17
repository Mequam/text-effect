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
int main(int argc,char ** argv)
{
	//set up our constants
	Rng dice = Rng();
	string key = " //	_=+-*/abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,()[]!?#;\"\'\\*<>{}"; 	
	string found = "";
	string parsed = parse(argc,argv);
	for (int i = 0;i<parsed.length();i++)
	{
		for (int j = 0; j < 200;j++)
		{
			if (i != parsed.length()-1)
			{
				cout << '\r' << found << key[dice.Range(0,key.length()-1)];
			}
			else
			{
				cout << '\r' << found;
			}
			usleep(100);
		}
		found+=parsed[i];
	}
	cout << endl;

return 1;
}
