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
	double temp;

	squares(bool twest, bool tnorth, bool teast, bool tsouth)
	{
		west = twest;
		north = tnorth;
		east = teast;
		south = tsouth;
		topprob = 1;
		temp = 0;
	}

	squares(double obstacle)
	{
		topprob = obstacle;
		west = true;
		north = true;
		east = true;
		south = true;
		topprob = 0;
		temp = 0;
	}

};

class sense
{
public:
	//obstacle
	bool west, north, east, south;
	sense(bool twest, bool tnorth, bool teast, bool tsouth)
	{
		west = twest;
		north = tnorth;
		east = teast;
		south = tsouth;
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

	void firstsenseupdate(sense first)
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (arr[i][j].topprob != 0)
				{
					if (first.west == true)
					{
						if (arr[i][j].west == true)
						{
							arr[i][j].topprob *= .8;
						}
						else
						{
							arr[i][j].topprob *= .15;
						}
					}
					else
					{
						if (arr[i][j].west == true)
						{
							arr[i][j].topprob *= .2;
						}
						else
						{
							arr[i][j].topprob *= .85;
						}
					}

					if (first.north == true)
					{
						if (arr[i][j].north == true)
						{
							arr[i][j].topprob *= .8;
						}
						else
						{
							arr[i][j].topprob *= .15;
						}
					}
					else
					{
						if (arr[i][j].north == true)
						{
							arr[i][j].topprob *= .2;
						}
						else
						{
							arr[i][j].topprob *= .85;
						}
					}

					if (first.east == true)
					{
						if (arr[i][j].east == true)
						{
							arr[i][j].topprob *= .8;
						}
						else
						{
							arr[i][j].topprob *= .15;
						}
					}
					else
					{
						if (arr[i][j].east == true)
						{
							arr[i][j].topprob *= .2;
						}
						else
						{
							arr[i][j].topprob *= .85;
						}
					}

					if (first.south == true)
					{
						if (arr[i][j].south == true)
						{
							arr[i][j].topprob *= .8;
						}
						else
						{
							arr[i][j].topprob *= .15;
						}
					}
					else
					{
						if (arr[i][j].south == true)
						{
							arr[i][j].topprob *= .2;
						}
						else
						{
							arr[i][j].topprob *= .85;
						}
					}

				}
			}
		}
	}

	void finalsenseupdate()
	{
	


		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (arr[i][j].topprob != 0)
				{
					arr[i][j].topprob = arr[i][j].topprob / (currentbottom);
				}
			}
		}
	}

	void firstmovementupdate(int dir)
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{



				if (dir == 1)
				{

					if (i > 0)
					{
						if (arr[i - 1][j].topprob != 0)
						{
							arr[i][j].temp += arr[i - 1][j].topprob * .1;  // left
						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;
						}

					}
					else
					{
						arr[i][j].temp += arr[i][j].topprob * .1;
					}

					if (i < 6)
					{

						if (arr[i + 1][j].topprob != 0)
						{
							arr[i][j].temp += arr[i + 1][j].topprob * .8;  // right
						}

					}

					if (j > 0)
					{
						if (arr[i][j - 1].topprob != 0)
						{
							arr[i][j].temp += arr[i][j - 1].topprob * .1;  // top
						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;
						}


					}
					else
					{
						arr[i][j].temp += arr[i][j].topprob * .1;
					}

					if (j < 7)
					{
						if (arr[i][j + 1].topprob != 0)
						{
							arr[i][j].temp += arr[i][j + 1].topprob * .1;  // bottom
						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;
						}


					}
					else
					{
						arr[i][j].temp += arr[i][j].topprob * .1;
					}


				}
					// 1 west 2 north 3 east 4 south

				//done
				if (dir == 1)
					{

						if (i > 0)
						{
							if (arr[i - 1][j].topprob != 0)
							{
								  // left
							}
							else
							{
								arr[i][j].temp += arr[i][j].topprob * .1;
							}

						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;
						}

						if (i < 6)
						{

							if (arr[i + 1][j].topprob != 0)
							{
								arr[i][j].temp += arr[i + 1][j].topprob * .8;  // right
							}
						
						}

						if (j > 0)
						{
							if (arr[i ][j-1].topprob != 0)
							{
								arr[i][j].temp += arr[i][j - 1].topprob * .1;  // top
							}
							else
							{
								arr[i][j].temp += arr[i][j].topprob * .1;
							}

							
						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;
						}

						if (j < 7)
						{
							if (arr[i][j + 1].topprob != 0)
							{
								arr[i][j].temp += arr[i][j + 1].topprob * .1;  // bottom
							}
							else
							{
								arr[i][j].temp += arr[i][j].topprob * .1;
							}


						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;
						}


					}

				if (dir == 2)
				{

					if (i > 0)
					{
						if (arr[i - 1][j].topprob != 0)
						{
							arr[i][j].temp += arr[i - 1][j].topprob * .1;  // left
						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;
						}

					}
					else
					{
						arr[i][j].temp += arr[i][j].topprob * .1;
					}

					if (i < 6)
					{

						if (arr[i + 1][j].topprob != 0)
						{
							arr[i][j].temp += arr[i + 1][j].topprob * .8;  // right
						}

					}

					if (j > 0)
					{
						if (arr[i][j - 1].topprob != 0)
						{
							arr[i][j].temp += arr[i][j - 1].topprob * .1;  // top
						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;
						}


					}
					else
					{
						arr[i][j].temp += arr[i][j].topprob * .1;
					}

					if (j < 7)
					{
						if (arr[i][j + 1].topprob != 0)
						{
							arr[i][j].temp += arr[i][j + 1].topprob * .1;  // bottom
						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;
						}


					}
					else
					{
						arr[i][j].temp += arr[i][j].topprob * .1;
					}


				}


				


					if (first.east == true)
					{

					}


					if (first.south == true)
					{

					}


				
			}
		}
	}

};

int main()
{
	map test;
	test.calculatebottom();
	test.printmap();


	sense first(false,false,false,false);
	cout << endl << endl << endl;
	test.firstsenseupdate(first);
	
	test.finalsenseupdate();
	test.calculatebottom();


	test.printmap();

	


}