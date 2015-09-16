#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <fstream>

#include "board.h"

// ================================================================
// ================================================================
// This function is called if there was an error with the command line arguments
bool usage(const std::string &executable_name) {
  std::cerr << "Usage: " << executable_name << " <puzzle_file>" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#>" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -all_solutions" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -visualize_accessibility" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#> -all_solutions" << std::endl;
  std::cerr << "       " << executable_name << " <puzzle_file> -max_moves <#> -visualize_accessibility" << std::endl;
  exit(0);
}


// ================================================================
// ================================================================
// load a Ricochet Robots puzzle from the input file
Board load(const std::string &executable, const std::string &filename) {

  // open the file for reading
  std::ifstream istr (filename.c_str());
  if (!istr) {
    std::cerr << "ERROR: could not open " << filename << " for reading" << std::endl;
    usage(executable);
  }

  // read in the board dimensions and create an empty board
  // (all outer edges are automatically set to be walls
  int rows,cols;
  istr >> rows >> cols;
  Board answer(rows,cols);

  // read in the other characteristics of the puzzle board
  std::string token;
  while (istr >> token) {
    if (token == "robot") {
      char a;
      int r,c;
      istr >> a >> r >> c;
      answer.placeRobot(Position(r,c),a);
    } else if (token == "vertical_wall") {
      int i;
      double j;
      istr >> i >> j;
      answer.addVerticalWall(i,j);
    } else if (token == "horizontal_wall") {
      double i;
      int j;
      istr >> i >> j;
      answer.addHorizontalWall(i,j);
    } else if (token == "goal") {
      std::string which_robot;
      int r,c;
      istr >> which_robot >> r >> c;
      answer.setGoal(which_robot,Position(r,c));
    } else {
      std::cerr << "ERROR: unknown token in the input file " << token << std::endl;
      exit(0);
    }
  }

  // return the initialized board
  return answer;
}

// ================================================================
// ================================================================

int main(int argc, char* argv[]) {

  // There must be at least one command line argument, the input puzzle file
  if (argc < 2) {
    usage(argv[0]);
  }

  // By default, the maximum number of moves is unlimited
  int max_moves = -1;

  // By default, output one solution using the minimum number of moves
  bool all_solutions = false;

  // By default, do not visualize the accessibility
  bool visualize_accessibility = false;

  // Read in the other command line arguments
  for (int arg = 2; arg < argc; arg++) {
    if (argv[arg] == std::string("-all_solutions")) {
      // find all solutions to the puzzle that use the fewest number of moves
      all_solutions = true;
    } else if (argv[arg] == std::string("-max_moves")) {
      // the next command line arg is an integer, a cap on the  # of moves
      arg++;
      assert (arg < argc);
      max_moves = atoi(argv[arg]);
      assert (max_moves > 0);
    } else if (argv[arg] == std::string("-visualize_accessibility")) {
      // As a first step towards solving the whole problem, with this
      // option, let's visualize where the robots can move and how many
      // steps it takes to get there
      visualize_accessibility = true;
    } else {
      std::cout << "unknown command line argument" << argv[arg] << std::endl;
      usage(argv[0]);
    }
  }

  // Load the puzzle board from the input file
  Board board = load(argv[0],argv[1]);

  //
  //
  // YOUR CODE STARTS HERE //Indeed it does...
  //
  //

	for (int i = 0; i < board.getRows()+1; i++) //First we set up the size of the visualization vector
	{
		for (int j = 0; j < board.getCols()+1; j++) //Don't worry we get to the recursion later... 
		{
			int tmp = -1;
			board.t.push_back(tmp); //Yes my visualization vector is a public variable... but this is the second time I've written the program from scratch
		}
		board.viz.push_back(board.t); //And my last late day... so spare a little mercy
	}
	for(unsigned int i = 0; i < board.numRobots(); i++) //Then we add the robots to a vector
	{
		Position P = board.getRobotPositions()[i];
		int y = P.row;
		int x = P.col;
		board.viz[y][x] = 0;
	}
	std::vector<std::string> path; //This vector keeps track of an individual robot path
	board.mm = max_moves; //This tells the rest of my functions what the max number of moves are
	std::vector<Position> pos = board.getRobotPositions(); //This vector of positions tells my functions where the robots are... 
	board.single = board.getRobotPositions(); //This does the same thing but only for a single output run
	board.trackMoves(0, pos, 0, path); //And here we send the positions and a fresh path vector off to neverland
	max_moves = board.mm; //Once neverland finishes processing... we have to see how many moves it took

if (visualize_accessibility == true) //If we are just visualizing it
{
	for (int i = 1; i < board.getRows()+1; i++)
	{
		for (int j = 1; j < board.getCols()+1; j++)  //Then we loop through and display the visualize vector
		{
			if(board.viz[i][j] != -1)
			{
				std::cout<<board.viz[i][j]<< " "; //trackMoves is how this vector got populated (see board.cpp)
			}
			else
			{
				std::cout<<"."<<" "; //Because my vector is ints not chars... we have to change the -1's to periods
			}
		}
		std::cout << std::endl;
	}
return 0; //Then we are done
}
else if (all_solutions == true) //If all solutions are true
{
	board.print(); //We print the initial board
	if (board.paths.size() == 0) //paths is a vector of vectors of strings... each string representing a move
	{
	if (max_moves == -1)
	{
		std::cout<<"no solutions found"<<std::endl; //If max moves wasn't specified and we get tossed out
		return 0; 
	}
	std::cout<<"no solutions with " << max_moves << " or fewer moves"<<std::endl; //Otherwise we specify the number of moves that resulted in no paths
	return 0;
	}
	else
	{
		std::cout<<board.paths.size()<<" different "<< board.paths[0].size() << " move solutions:"<<std::endl; //Otherwise... we say how many moves there are
	}
	std::cout<<std::endl;
	for (int i = 0; i < board.paths.size(); i++)
	{
		for (int j = 0; j < board.paths[i].size(); j++)
		{
			std::cout<<board.paths[i][j]<<std::endl; //then we output all of the paths
		}
		std::cout<<"robot " << board.paths[i][board.paths[i].size()-1][6] << " reaches the goal after " << board.paths[0].size() << " moves"<< std::endl; //Looking at the last path
		std::cout<<std::endl;															//to determine which robot reached the goal... by parsing the string of the path
	}
}
else
{
	board.print();  //This one is the most tricky
	std::string x; //This is a temporary string
	if (board.paths.size() == 0)
	{
		if (max_moves == -1)
		{
			std::cout<<"no solutions found"<<std::endl; //Once again for no solutions we do the same thing
			return 0;
		}		
		std::cout<<"no solutions with " << max_moves << " or fewer moves"<<std::endl; 
		return 0;
	}
	for (int j = 0; j < board.paths[0].size(); j++)
	{
		if (j != 0)
		{
			board.print(); //Then we print the initial board
		}
		std::cout<<board.paths[0][j]<<std::endl; //So this gets kinda weird... but essentially
		x = board.paths[0][j]; //I only returned strings of directions from my program earlier
		std::string direction; //So I have to parse each string and figure out what it means
		int z = board.whichRobot(x[6]);
		if (x[14] == 'e')
		{
			direction = "east";
		}
		if (x[14] == 'w')
		{
			direction = "west";
		}
		if (x[14] == 's')
		{
			direction = "south";
		}
		if (x[14] == 'n')
		{
			direction = "north";
		}
		std::vector<std::string> tempath;
		board.mm = -2; //-2 is a number of max moves that wont be tested normally
		board.moveRobot(z, direction, 0, board.single, 0, tempath); //my moving function recognizes this and moves the robot without recursing over and over
		board.setspot(board.single[z], ' '); //In my board.cpp I set the position of the robot character
		board.single[z].col = board.tempos.col; //Using this we can continue to output the correct position
		board.single[z].row = board.tempos.row;
	}
	board.print();
	std::cout<<"robot " << x[6] << " reaches the goal after " << board.paths[0].size() << " moves"<< std::endl;
	
}



}

// ================================================================
// ================================================================
