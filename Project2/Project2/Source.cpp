#include <iostream>;
#include <string>;
#include <cmath>;


using namespace std;

class squares//for each section of the map
{
public:
	
	bool west, north, east, south;
	double topprob;
	double temp;

	squares(bool twest, bool tnorth, bool teast, bool tsouth)
	{
		west = twest;
		north = tnorth;
		east = teast;
		south = tsouth;
		topprob = .0263;
		temp = 0;
	}

	squares(double obstacle) // for the obstacle spaces
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

class sense // holds the 4 boolean values for whats around the robot
{
public:
	
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
	double currentbottom; // used in the normalization of the spaces as the bottom value(all the other values added toegether)
	squares arr[6][7] = {
	{squares(true, true, false, false),squares(false, true, false, true),squares(false, true, false, false),squares(false, true, false, false),squares(false, true, false, true),squares(false, true, false, false),squares(false, true, true, false)},
	{squares(true, false, true, false),squares(0),squares(true, false, false, false),squares(false, false, true, false),squares(0),squares(true, false, false, false),squares(false, false, true, false)},
	{squares(true, false, false, false),squares(false, true, false, true),squares(false, false, false, false),squares(false, false, false, false),squares(false, true, false, true),squares(false, false, false, false),squares(false, false, true, false)},
	{squares(true, false, true, false),squares(0),squares(true, false, false, false),squares(false, false, true, false),squares(0),squares(true, false, false, false),squares(false, false, true, false)},
	{squares(true, false, false, false),squares(false, true, false, false),squares(false, false, false, false),squares(false, false, false, false),squares(false, true, false, false),squares(false, false, false, false),squares(false, false, true, false)},
	{squares(true, false, false, true),squares(false, false, false, true),squares(false, false, false, true),squares(false, false, false, true),squares(false, false, false, true),squares(false, false, false, true),squares(false, false, true, true)},
	};//the map filled with the spaces and their neighbor values

	
	void calculatebottom() // adds the probability of each square so we can normalize them
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
	

	void printmap()//prints the map... should i have put this comment? only time will tell, let me know in the feedback if i shouldnt have
	{
		
			
		
		cout.precision(3); // rounds the values to 3 places
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (arr[i][j].topprob == 0)
				{
					cout << "####" << "   ";//obstackles
					
				}
				else
				{
					cout << (arr[i][j].topprob) * 100 << "   ";//proababilities
					
				}
			}
			cout << endl;

		}

		cout << endl << endl << endl;

	}

	void firstsenseupdate(sense first) //first half of the sensing calculates the first value for each square based off the sensing info and its neighbors values, will be normalized later
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (arr[i][j].topprob != 0)
				{
					if (first.west == true) // if the west space has an obstacle in the sensing
					{
						if (arr[i][j].west == true)//if this square has an obstacle to the west
						{
							arr[i][j].topprob *= .8;
						}
						else// if it doesnt 
						{
							arr[i][j].topprob *= .15;
						}
					}
					else//if the sensing says the space to the west is open
					{
						if (arr[i][j].west == true)//if the west space actually has an obstacle
						{
							arr[i][j].topprob *= .2;
						}
						else//if the space is open to the west
						{
							arr[i][j].topprob *= .85;
						}
					}

					if (first.north == true)//same for north
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

					if (first.east == true)//same for east
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

					if (first.south == true)//you guessed it! for south
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

	void finalsenseupdate()//uses the values calculated in firstsensorupdate and the current bottom to normalize all the values
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

	void firstmovementupdate(int dir)//updates the probabilities based off which way we tried to move
	{

		


		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{

					// 1 west 2 north 3 east 4 south im only gonna explain from west cause the others are all basically the same but from different directions
				if (dir == 1) //from the west
				{

					if (i > 0) // if were not at thetop
					{
						if (arr[i - 1][j].topprob != 0)//if the space above us is open
						{

							arr[i][j].temp += arr[i-1][j].topprob * .1; 

						}
						else//if theres an obstacle
						{
							arr[i][j].temp += arr[i][j].topprob * .1;
						}


					}
					else// were at top of the map
					{
						arr[i][j].temp += arr[i][j].topprob * .1;
					}

					if (i < 5)// if were not at bottom of map
					{

						if (arr[i + 1][j].topprob != 0) // if the space below us is open
						{
							arr[i][j].temp += arr[i + 1][j].topprob * .1;

						}
						else // the space is an obstacle
						{
							arr[i][j].temp += arr[i][j].topprob * .1;

						}

					}
					else//were at bottom
					{
						arr[i][j].temp += arr[i][j].topprob * .1;

					}

					if (j > 0)//if were not at left wall
					{
						if (arr[i][j - 1].topprob != 0)//do nothing because we cant bounce off anything if its open
						{
							

						}
						else// theres an obstacle we can bounce off
						{
							arr[i][j].temp += arr[i][j].topprob * .8;

						}


					}
					else//were at the left wall of the map
					{
						arr[i][j].temp += arr[i][j].topprob * .8;


					}

					if (j < 6)// if were not at right wall
					{
						if (arr[i][j + 1].topprob != 0)// the space to the left of us is open 
						{
							arr[i][j].temp += arr[i][j + 1].topprob * .8;
						}
						else//noone can move into our square because the space is an obstacle and theres no chance we go backwards
						{
					

						}


					}
					else//at right wall so nothing can move west to enter our space and we cant move backwards to bounce off the wall
					{
						

					}


				}

				if (dir == 2)
				{

					if (i > 0) // 0 = top
					{
						if (arr[i - 1][j].topprob != 0)
						{
							 
							
						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .8;
						}


					}
					else// not top
					{
						arr[i][j].temp += arr[i][j].topprob * .8;
					}

					if (i < 5)// not at bottom
					{

						if (arr[i + 1][j].topprob != 0)
						{
							arr[i][j].temp += arr[i + 1][j].topprob * .8;  
							
						}
						else
						{
							
						}

					}
					else//at bottom
					{
						
					}

					if (j > 0)//not at left wall
					{
						if (arr[i][j - 1].topprob != 0)
						{
							arr[i][j].temp += arr[i][j-1].topprob * .1;

						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;

						}


					}
					else//at left wall
					{
						arr[i][j].temp += arr[i][j].topprob * .1;
						

					}

					if (j < 6)// not at right wall
					{
						if (arr[i][j + 1].topprob != 0)
						{
							arr[i][j].temp += arr[i][j + 1].topprob * .1; 
						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;

						}


					}
					else//at right wall 
					{
						arr[i][j].temp += arr[i][j].topprob * .1;

					}


				}

				if (dir == 3)
				{

					if (i > 0) // 0 = top
					{
						if (arr[i - 1][j].topprob != 0)
						{

							arr[i][j].temp += arr[i-1][j].topprob * .1;

						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;
						}


					}
					else// not top
					{
						arr[i][j].temp += arr[i][j].topprob * .1;
					}

					if (i < 5)// not at bottom
					{

						if (arr[i + 1][j].topprob != 0)
						{
							arr[i][j].temp += arr[i + 1][j].topprob * .1;

						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;

						}

					}
					else//at bottom
					{
						arr[i][j].temp += arr[i][j].topprob * .1;

					}

					if (j > 0)//not at left wall
					{
						if (arr[i][j - 1].topprob != 0)
						{
							arr[i][j].temp += arr[i][j - 1].topprob * .8;

						}
						else
						{
							

						}


					}
					else//at left wall
					{
						


					}

					if (j < 6)// not at right wall
					{
						if (arr[i][j + 1].topprob != 0)
						{
							
						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .8;

						}


					}
					else//at right wall 
					{
						arr[i][j].temp += arr[i][j].topprob * .8;

					}


				}

				if (dir == 4)
				{

					if (i > 0) // 0 = top
					{
						if (arr[i - 1][j].topprob != 0)
						{

							arr[i][j].temp += arr[i-1][j].topprob * .8;

						}
						else
						{
							
						}


					}
					else// not top
					{
						
					}

					if (i < 5)// not at bottom
					{

						if (arr[i + 1][j].topprob != 0)
						{
							

						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .8;

						}

					}
					else//at bottom
					{
						arr[i][j].temp += arr[i][j].topprob * .8;

					}

					if (j > 0)//not at left wall
					{
						if (arr[i][j - 1].topprob != 0)
						{
							arr[i][j].temp += arr[i][j - 1].topprob * .1;

						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;

						}


					}
					else//at left wall
					{
						arr[i][j].temp += arr[i][j].topprob * .1;


					}

					if (j < 6)// not at right wall
					{
						if (arr[i][j + 1].topprob != 0)
						{
							arr[i][j].temp += arr[i][j + 1].topprob * .1;
						}
						else
						{
							arr[i][j].temp += arr[i][j].topprob * .1;

						}


					}
					else//at right wall 
					{
						arr[i][j].temp += arr[i][j].topprob * .1;

					}


				}


			}
		}
	}

	void finalmovementupdate()//update the probability of each space from a temporary storage to the main probability and reset the temperary storage
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (arr[i][j].topprob == 0)
				{
					
				}
				else
				{
					arr[i][j].topprob = arr[i][j].temp;
					arr[i][j].temp = 0;
				}

			}
			
		}
	}
};

int main()
{
	map test;
	sense first(false, false, false, false);
	sense second(true, false, false, false);
	sense third(false, false, false, false);
	sense fourth(false, true, false, true);
	sense fifth(true, false, false, false);
	// ^ these are self explanatory right?

	test.calculatebottom();

	cout << "Inital probabilities" << endl;

	test.printmap();

	test.firstsenseupdate(first);//for sensing this is the order because you get the values updated
	test.calculatebottom();// then you get all the updated values added together 
	test.finalsenseupdate();// then you use that to normalize them

	
	cout << "After sensing (0,0,0,0)" << endl;

	test.printmap();
	


	test.firstmovementupdate(2);

	test.finalmovementupdate();


	cout << "After moving north" << endl;

	test.printmap();


	
	test.firstsenseupdate(second);
	test.calculatebottom();

	test.finalsenseupdate();
	cout << "After sensing (1,0,0,0)" << endl;

	test.printmap();

	

	test.firstmovementupdate(2);

	test.finalmovementupdate();
	cout << "After moving north" << endl;

	test.printmap();



	test.firstsenseupdate(third);
	test.calculatebottom();

	test.finalsenseupdate();
	cout << "After sensing (0,0,0,0)" << endl;

	test.printmap();



	test.firstmovementupdate(1);

	test.finalmovementupdate();
	cout << "After moving west" << endl;

	test.printmap();



	test.firstsenseupdate(fourth);
	test.calculatebottom();

	test.finalsenseupdate();
	cout << "After sensing (0,1,0,1)" << endl;

	test.printmap();



	test.firstmovementupdate(1);

	test.finalmovementupdate();
	cout << "After moving west" << endl;

	test.printmap();



	test.firstsenseupdate(fifth);
	test.calculatebottom();

	test.finalsenseupdate();	
	cout << "After sensing (1,0,0,0)" << endl;

	test.printmap();

	//hi


}