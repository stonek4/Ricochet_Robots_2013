#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdlib.h> 
#include "board.h"


// ==================================================================
// ==================================================================
// Implementation of the Position class


// allows a position to be output to a stream
std::ostream& operator<<(std::ostream &ostr, const Position &p) {
  ostr << '(' << p.row << "," << p.col << ')';
  return ostr;
}


// equality and inequality comparision of positions
bool operator==(const Position &a, const Position &b) {
  return (a.row == b.row && a.col == b.col);
}
bool operator!=(const Position &a, const Position &b) {
  return !(a==b);
}


// ==================================================================
// ==================================================================
// Implementation of the Board class


// ===================
// CONSTRUCTOR
// ===================

Board::Board(int r, int c) { 
  // initialize the dimensions
  rows = r; 
  cols = c; 

  // allocate space for the contents of each grid cell
  board = std::vector<std::vector<char> >(rows,std::vector<char>(cols,' '));

  // allocate space for booleans indicating the presense of each wall
  // by default, these are false == no wall
  // (note that there must be an extra column of vertical walls
  //  and an extra row of horizontal walls)
  vertical_walls = std::vector<std::vector<bool> >(rows,std::vector<bool>(cols+1,false));
  horizontal_walls = std::vector<std::vector<bool> >(rows+1,std::vector<bool>(cols,false));

  // initialize the outermost edges of the grid to have walls
  for (int i = 0; i < rows; i++) {
    vertical_walls[i][0] = vertical_walls[i][cols] = true;
  }
  for (int i = 0; i < cols; i++) {
    horizontal_walls[0][i] = horizontal_walls[rows][i] = true;
  }
}


// ===================
// ACCESSORS related to board geometry
// ===================

// Query the existance of a horizontal wall
bool Board::getHorizontalWall(double r, int c) const {
  // verify that the requested wall is valid
  // the row coordinate must be a half unit
  assert (fabs((r - floor(r))-0.5) < 0.005);
  assert (r >= 0.4 && r <= rows+0.6);
  assert (c >= 1 && c <= cols);
  // subtract one and round down because the corner is (0,0) not (1,1)
  return horizontal_walls[floor(r)][c-1];
}

// Query the existance of a vertical wall
bool Board::getVerticalWall(int r, double c) const {
  // verify that the requested wall is valid
  // the column coordinate must be a half unit
  assert (fabs((c - floor(c))-0.5) < 0.005);
  assert (r >= 1 && r <= rows);
  assert (c >= 0.4 && c <= cols+0.6);
  // subtract one and round down because the corner is (0,0) not (1,1)
  return vertical_walls[r-1][floor(c)];
}


// ===================
// MODIFIERS related to board geometry
// ===================

// Add an interior horizontal wall
void Board::addHorizontalWall(double r, int c) {
  // verify that the requested wall is valid
  // the row coordinate must be a half unit
  assert (fabs((r - floor(r))-0.5) < 0.005);
  assert (r >= 0 && r <= rows);
  assert (c >= 1 && c <= cols);
  // verify that the wall does not already exist
  assert (horizontal_walls[floor(r)][c-1] == false);
  // subtract one and round down because the corner is (0,0) not (1,1)
  horizontal_walls[floor(r)][c-1] = true;
}

// Add an interior vertical wall
void Board::addVerticalWall(int r, double c) {
  // verify that the requested wall is valid
  // the column coordinate must be a half unit
  assert (fabs((c - floor(c))-0.5) < 0.005);
  assert (r >= 1 && r <= rows);
  assert (c >= 0 && c <= cols);
  // verify that the wall does not already exist
  assert (vertical_walls[r-1][floor(c)] == false);
  // subtract one and round down because the corner is (0,0) not (1,1)
  vertical_walls[r-1][floor(c)] = true;
}


// ===================
// PRIVATE HELPER FUNCTIONS related to board geometry
// ===================

char Board::getspot(const Position &p) const {
  // verify that the requested coordinate is valid
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);
  // subtract one from each coordinate because the corner is (0,0) not (1,1)
  return board[p.row-1][p.col-1];
}

void Board::setspot(const Position &p, char a) {
  // verify that the requested coordinate is valid
  assert (p.row >= 1 && p.row <=  rows);
  assert (p.col >= 1 && p.col <= cols);
  // subtract one from each coordinate because the corner is (0,0) not (1,1)
  board[p.row-1][p.col-1] = a;
}



// ===================
// ACCESSORS related to robots
// ===================

// Given a robot name, find the id of that robot
int Board::whichRobot(char a) const {
  for (unsigned int i = 0; i < robots.size(); i++) {
    if (robots[i] == a) {
      return i;
    }
  }
  std::cerr << "ERROR: Robot " << a << " does not exist" << std::endl;
  exit(0);
}


// ===================
// MODIFIERS related to robots
// ===================

// for initial placement of a new robot
void Board::placeRobot(const Position &p, char a) {

  // check that input data is reasonable
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);
  // make sure we don't already have a robot at that location
  assert (getspot(p) == ' ');
  // we may not start with a robot at the goal location
  assert (p != goal);

  // robots must be represented by a capital letter
  assert (a >= 'A' && a <= 'Z');

  // make sure we don't already have a robot with the same name
  for (unsigned int i = 0; i < robots.size(); i++) {
    assert (robots[i] != a);
  }

  // add the robot and its position to the vectors of robots
  robots.push_back(a);
  robot_positions.push_back(p);

  // mark the robot on the board
  setspot(p,a);
}
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ My Code Starts HERE $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
void Board::trackMoves(int i, std::vector<Position> pos, int c, std::vector<std::string> path)  //Ok... so my recursion is a little weird but its not that hard to understand.
{																							//Think of it as a three step process... we add robot moves to the vectors and check for... 
	c++;																					//...completion.  Then if we are not complete, we send that information to a function that...
	if (mm == -1)																			//...cycles through all the moves and all the robots.  And lastly we have function that moves...
	{																						//...the robots and calls the first function to add the moves to the vectors again.
		mm = 14;
	}
	int h = path.size()/2;
	bool check = false;
	for (int j = 0; j < path.size()/2; j++)
	{
		if (path[j] != path[j+h])
		{
			check = true;
		}
	}	
	if (check = false && path.size() > 7)
	{
		return;
	}
	if (c == 1) //If it is the first time running through we don't need to add anything
	{
		cycleMoves(pos, c, path); //Just send it straight to the cycle
		return;
	}
	if (pos.empty() == false) //Otherwise we check if the vector of robot positions returned is empty (this is how I check if the robot got moved)
	{
		if ((c-1) < viz[pos[i].row][pos[i].col] || viz[pos[i].row][pos[i].col] == -1) //If it was, and if it reached the spot it moved it in less moves than any other robot
		{																		//Or it is the first robot to reach that spot
			viz[pos[i].row][pos[i].col] = (c-1); //Then we add it to the visualization vector
		}
	}
	else //Otherwise that path is dead
	{
		return;
	}
	for (int j = 0; j < numRobots(); j++)
	{
		if (pos[j].col == getGoal().col && pos[j].row == getGoal().row) //Here we check if a robot has reached the goal
		{ 
			if (goal_robot == -1 || i == goal_robot)  //and if the robot that reached the goal matters, and if so... if its correct
			{
				if ((c-1) < mm) //If those are true... and the robot reached the goal in a number of moves less than any other path before
				{
					mm = (c-1); 
					paths.clear(); //We clear the path
				}
				paths.push_back(path);	//But no matter what we add the new path to the paths 
			}
		}
	}
	if (c > mm && mm != -1) //Here we check for completion
	{
		return;
	}
	else if (c == 14)
	{
		return;
	}
	else
	{
		cycleMoves(pos, c, path); //If we aren't complete we go to step 2
	}
}

void Board::cycleMoves(std::vector<Position> pos, int c, std::vector<std::string> path)
{
  for (int i = 0; i < numRobots(); i++) //Step 2 is simple... just keep sending robots through the spin cycle aka the moveRobot function
  {
	moveRobot(i, "north", 0, pos, c, path);
	moveRobot(i, "south", 0, pos, c, path);
	moveRobot(i, "east", 0, pos, c, path);
	moveRobot(i, "west", 0, pos, c, path);
  }
}

void Board::moveRobot(int i, const std::string &direction, int m, std::vector<Position> pos,  int c, std::vector<std::string> path) {
if (direction == "north") //If we are moving a robot north
{
	for (int j = 0; j < pos.size(); j++) //For every robot
	{
		if (pos[i].row-1 == pos[j].row && pos[i].col == pos[j].col) //We have to make sure that no robots are above the one being moved
		{
			if (m == 0) //If there is and we didn't move at all
			{
				return; //We can't move and return
			}
			if (mm == -2) //If we are just trying to set the map for display (in a one requested path scenario) then we set the path and return
			{
				tempos.col = pos[i].col;
				tempos.row = pos[i].row;
				setspot(tempos, getRobot(i));
				return;
			}
			std::string z = "robot x moves north"; //But usually if a robot is above, then we have reached a new destination
			z[6] = getRobot(i); //We add the robot moved to the magic z string
			path.push_back(z); //And pushback that string into the path
			trackMoves(i, pos, c, path); //Then return to track moves!
			return;
		}
	}
	if (getHorizontalWall(double(pos[i].row - .5), pos[i].col) == true) //If there wasn't another robot above... there could still be a wall
	{
			if (m == 0)
			{
				return;
			}
			if (mm == -2)
			{
				tempos.col = pos[i].col;
				tempos.row = pos[i].row;
				setspot(tempos, getRobot(i));
				return;
			}
		
			std::string z = "robot x moves north"; //Same deal... just if there is a wall there
			z[6] = getRobot(i);
			path.push_back(z);
			trackMoves(i, pos, c, path);
			return;
	}
	else
	{
		pos[i].row--; //Otherwise we can move the robot
		moveRobot(i, direction, 1, pos, c, path); //And we recurse by sending the robot through the move again
	}
}

if (direction == "south") //Same thing happens for the other directions... you can scroll down but there's nothing else down there to see
{
	for (int j = 0; j < pos.size(); j++)
	{
		if (1+pos[i].row == pos[j].row && pos[i].col == pos[j].col)
		{
						if (m == 0)
			{
				return;
			}
			if (mm == -2)
			{
				tempos.col = pos[i].col;
				tempos.row = pos[i].row;
				setspot(tempos, getRobot(i));
				return;
			}

			std::string z = "robot x moves south";
			z[6] = getRobot(i);
			path.push_back(z);
			trackMoves(i, pos, c, path);
			return;
		}
	}
	if (getHorizontalWall(double(pos[i].row + .5), pos[i].col) == true)
	{
						if (m == 0)
			{
				return;
			}
			if (mm == -2)
			{
				tempos.col = pos[i].col;
				tempos.row = pos[i].row;
				setspot(tempos, getRobot(i));
				return;
			}

			std::string z = "robot x moves south";
			z[6] = getRobot(i);
			path.push_back(z);
			trackMoves(i, pos, c, path);
			return;
	}
	else
	{
		pos[i].row++;
		moveRobot(i, direction, 1, pos, c, path);
	}
}

if (direction == "east")
{
	for (int j = 0; j < pos.size(); j++)
	{
		if (1+pos[i].col == pos[j].col && pos[i].row == pos[j].row)
		{
			if (m == 0)
			{
				return;
			}
			if (mm == -2)
			{
				tempos.col = pos[i].col;
				tempos.row = pos[i].row;
				setspot(tempos, getRobot(i));
				return;
			}

			std::string z = "robot x moves east";
			z[6] = getRobot(i);
			path.push_back(z);
			trackMoves(i, pos, c, path);
			return;
		}
	}
	if (getVerticalWall(pos[i].row, double(pos[i].col + .5)) == true)
	{
			if (m == 0)
			{
				return;
			}
			if (mm == -2)
			{
				tempos.col = pos[i].col;
				tempos.row = pos[i].row;
				setspot(tempos, getRobot(i));
				return;
			}

			std::string z = "robot x moves east";
			z[6] = getRobot(i);
			path.push_back(z);
			trackMoves(i, pos, c, path);
			return;
	}
	else
	{
		pos[i].col++;
		moveRobot(i, direction, 1, pos, c, path);
	}
}

if (direction == "west")
{
	for (int j = 0; j < pos.size(); j++)
	{
		if (pos[i].col-1 == pos[j].col && pos[i].row == pos[j].row)
		{
						if (m == 0)
			{
				return;
			}
			if (mm == -2)
			{
				tempos.col = pos[i].col;
				tempos.row = pos[i].row;
				setspot(tempos, getRobot(i));
				return;
			}

			std::string z = "robot x moves west";
			z[6] = getRobot(i);
			path.push_back(z);
			trackMoves(i, pos, c, path);
			return;
		}
	}
	if (getVerticalWall(pos[i].row, double(pos[i].col - .5)) == true)
	{
						if (m == 0)
			{
				return;
			}
			if (mm == -2)
			{
				tempos.col = pos[i].col;
				tempos.row = pos[i].row;
				setspot(tempos, getRobot(i));
				return;
			}

			std::string z = "robot x moves west";
			z[6] = getRobot(i);
			path.push_back(z);
			trackMoves(i, pos, c, path);
			return;
	}
	else
	{
		pos[i].col--;
		moveRobot(i, direction, 1, pos, c, path);
	}
}

}


// ===================
// MODIFIER related to the puzzle goal
// ===================

void Board::setGoal(const std::string &gr, const Position &p) {
  // check that input data is reasonable
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);


  // set the goal position
  goal = p;
  // set which robot must reach the goal
  if (gr == "any") {
    goal_robot = -1;
  } else {
    // otherwise it must be a single character, the name of a valid robot
    assert (gr.size() == 1);
    goal_robot = whichRobot(gr[0]);
  }
}


// ==================================================================
// PRINT THE BOARD
// ==================================================================

void Board::print() {

  // print the column headings
  std::cout << " ";
  for (int j = 1; j <= cols; j++) {
    std::cout << std::setw(4) << j;
  }
  std::cout << "\n";
  
  // for each row
  for (int i = 0; i <= rows; i++) {

    // don't print row 0 (it doesnt exist, the first real row is row 1)
    if (i > 0) {
      
      // note that each grid rows is printed as 3 rows of text, plus the separator
      // the first and third rows are blank except for vertical walls
      // the middle row has the row heading, the robot positions, and the goal
      std::string first = "  ";
      std::string middle;
      for (int j = 0; j <= cols; j++) {
        if (j > 0) { 
          first += "   "; 
          // determine if a robot is current located in this cell, or
          // if this is the goal
          Position p(i,j);
          char c = getspot(p);
          if (c == ' ' && p == getGoal()) {
            // if this is a goal that any robot can reach:
            if (goal_robot == -1) c = '?';
            // if this goal must be reached by a particular robot use
            // the lowercase version of the robot name to indicate
            // which robot needs to reach the goal:
            else c = tolower(getRobot(goal_robot));
          }
          // put a little space around the information so it's easier to read
          middle += " ";
          middle += c;
          middle += " ";
        }
        // the vertical walls
        if (getVerticalWall(i,j+0.5)) {
          first += "|";
          middle += "|";
        } else {
          first += " ";
          middle += " ";
        }
      }

      // output the three rows
      std::cout << first << std::endl;
      std::cout << std::setw(2) << i << middle << std::endl;
      std::cout << first << std::endl;
    }

    // print the horizontal walls between rows
    std::cout << "  +";
    for (double j = 1; j <= cols; j++) {
      (getHorizontalWall(i+0.5,j)) ? std::cout << "---" : std::cout << "   ";
      std::cout << "+";
    }
    std::cout << "\n";
  }
}

// ==================================================================
// ==================================================================
