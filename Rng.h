#include <cstdlib>
#include <ctime>
#include <iostream>
//an Rng class for c++ that allows the roling of arbitrary dice
using namespace std;
class Rng
{
private:
long StartTime = time(0);

public:
Rng();
//returns a random number between str and end, INCLUDING str and end
//returns -1 on error
int Range(int str=1, int end=6) 
{
	if((end-str) >= 1)
	{
		this -> StartTime += 1;
		srand(this -> StartTime);
		return ((rand() % ((end-str) + 1)) + str);
	}
	else
	{
		return -1;
	}
}
//returns true Perc percent of the times it is called
bool Percent(int Perc)
{
	if (Perc >= 100)
	{
		return true;
	}
	else if (Perc <= 0)
	{
		return false;
	}
	else if (Range(0,100) <= Perc)
	{
		return true;
	}
	else
	{
	//if you manage to get down here, you rolled an i :P
	return false;
	}
}
};
Rng::Rng() {}
