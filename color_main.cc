#include <iostream>
#include <string.h>
#include <unistd.h>
#include "Rng.h"

using namespace std;


//this function parses out a letter and allows for colors
string color_parse_letter(char * v,int * offset) {
	if (v[*offset] != '%') {
		string ret_val = "";
		ret_val += v[*offset];
		return ret_val;
	}
	//incriment the offset once here so we dont have to do it a ton of times in the switch statement
	*offset+=1;
	switch (v[*offset])
	{
		case 'R':
			return "\033[1;31m";
		case 'r':
			return "\033[0;31m";
		case 'U':
			return "\033[1;34m";
		case 'u':
			return "\033[0;34m";
		case 'B':
			return "\033[1;30m";
		case 'b':
			return "\033[0;30m";
		case 'G':
			return "\033[1;32m";
		case 'g':
			return "\033[0;32m";
		case 'Y':
			return "\033[1;33m";
		case 'y':
			return "\033[0;33m";
		case 'M':
			return "\033[1;35m";
		case 'm':
			return "\033[0;35m";
		case 'C':
			return "\033[1;36m";
		case 'c':
			return "\033[0;36m";
		case 'W':
			return "\033[1;37m";
		case 'w':
			return "\033[0;37m";		
		case 'V':	
			return "\033[0;0m";
		default:
			//false alarm no need to change offset
			*offset-=1;
			return "%";
	}
}
string parse_no_color(char * v,int * offset) {
	if (v[*offset] != '%') {
		string ret_val = "";
		ret_val += v[*offset];
		return ret_val;
	}
	//incriment the offset once here so we dont have to do it a ton of times in the switch statement
	*offset+=1;
	switch (v[*offset])
	{
		case 'R':
			return "";
		case 'r':
			return "";
		case 'U':
			return "";
		case 'u':
			return "";
		case 'B':
			return "";
		case 'b':
			return "";
		case 'G':
			return "";
		case 'g':
			return "";
		case 'Y':
			return "";
		case 'y':
			return "";
		case 'M':
			return "";
		case 'm':
			return "";
		case 'C':
			return "";
		case 'c':
			return "";
		case 'W':
			return "";
		case 'w':
			return "";		
		case 'V':	
			return "";
		default:
			//false alarm no need to change offset
			*offset-=1;
			return "%";
	}
}
//this function parses out a string and fills it with ANSI color codes
string parse(int argc,char ** argv,string (*p)(char *,int*) = &color_parse_letter)
{
	string ret_val = "";
	for (int i = 1;i<argc;i++)
	{
		int j = 0;
		while (argv[i][j] != '\x00')
		{
			ret_val += (*p)(argv[i],&j);
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
	if (argc < 2) {
		//technicaly this is valid behavior as we just print nothing
		exit(0);
	}
	//set up our constants
	Rng dice = Rng();
	string key = "/_=+-*/abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,()[]!?#;\"\'\\*<>{}"; 	
	
	string found = "";
	string parsed = parse(argc,argv,&parse_no_color);
	string before = "";
	int sleep_time = 60000/parsed.length();	
	for (int i = 0;i<parsed.length();i++)
	{
		before += key[dice.Range(0,key.length()-1)];
		cout << before << '\r';
		flush(cout);
		usleep(sleep_time);
	}
	for (int i = 0;i<parsed.length();i++)
	{
		found=rand_string(parsed,key,i,&dice);
		cout << found + "\r";
		flush(cout);
		found[i]=parsed[i];
		usleep(sleep_time);
	}
	cout << "\r";
	flush(cout);
	string s = parse(argc,argv); 
	cout << s << endl;
	return 0;
}
