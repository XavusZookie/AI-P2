#include <iostream>;
#include <string>;
#include <cmath>;


using namespace std;

class squares
{
public:
	//obstacle?
	bool west, north, east, south;
	double topprob;


	squares(bool twest, bool tnorth, bool teast, bool tsouth)
	{
		west = twest;
		north = tnorth;
		east = teast;
		south = tsouth;
		topprob = 1;
	}

	squares(double obstacle)
	{
		topprob = obstacle;
	}

};

class map
{
public:
	int width = 7, length = 6;
	double currentbottom;
	squares arr[6][7] = {
	{squares(true, true, false, false),squares(false, true, false, true),squares(false, true, false, false),squares(false, true, false, false),squares(false, true, false, true),squares(false, true, false, false),squares(false, true, true, false)},
	{squares(true, false, true, false),squares(0),squares(true, false, false, false),squares(false, false, true, false),squares(0),squares(true, false, false, false),squares(false, false, true, false)},
	{squares(true, false, false, false),squares(false, true, false, true),squares(false, false, false, false),squares(false, false, false, false),squares(false, true, false, true),squares(false, false, false, false),squares(false, false, true, false)},
	{squares(true, false, true, false),squares(0),squares(true, false, false, false),squares(false, false, true, false),squares(0),squares(true, false, false, false),squares(false, false, true, false)},
	{squares(true, false, false, false),squares(false, true, false, false),squares(false, false, false, false),squares(false, false, false, false),squares(false, true, false, false),squares(false, false, false, false),squares(false, false, true, false)},
	{squares(true, false, false, true),squares(false, false, false, true),squares(false, false, false, true),squares(false, false, false, true),squares(false, false, false, true),squares(false, false, false, true),squares(false, false, true, true)},
	};

	
	void calculatebottom()
	{ 
		currentbottom = 0;

		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				currentbottom += arr[i][j].topprob;
			}
			

		}
		return;
	}
	

	void printmap()
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (arr[i][j].topprob == 0)
				{
					cout << "#########" << "   ";
				}
				else
				cout << arr[i][j].topprob/currentbottom << "   ";
			}
			cout << endl;

		}
	}





};

int main()
{
	map test;
	test.calculatebottom();
	test.printmap();







}