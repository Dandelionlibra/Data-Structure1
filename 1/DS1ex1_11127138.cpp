//11127138, 林雨臻
#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <math.h>
//#include "Maze.h"
using namespace std;


enum Modes {
	oneG,
	moreG
};
enum Direction {
	Right,
	Down,
	Left,
	Up,
	//Back
};



class Maze{
	public:
		Maze() ;
		bool load( string fileName, Modes inmode ) ;
		bool findGoals( int currenty, int currentx) ;
		void show( bool success ) ;
		void clean() ;

	private:
		Modes mode ; // self mode
		Direction direction = Right ; // record the directon of mouse
		int x, y ; // width, high
		// int currentx = 0, currenty = 0 ; //
		int gamount = 0 ; // initial let the amount of g which need to be found is 1
		int findg = 0 ; // record the goal that we already found
		vector<vector<char> > pattern; //(x, vector<char> (y, 0))
		vector<vector<char> > patternV;
		vector<vector<char> > patternR;
		vector<pair<int,int> > temproute; // record the temple point while pass the maze
		vector<vector<pair<int,int> > > pass; // (0,1),(0,2)...
		bool setModeAndG = false ; // already setting mode or not
};


Maze::Maze() {
}

bool Maze::load( string fileName, Modes inmode ) {
	fileName = "input"+fileName+".txt" ;
	ifstream input( fileName ); // c_str()將String物件轉換成C語言形式的字串常數。

	if( !input ) { // confirm existence or not
		cout << fileName << " doesn't exist!";
		return false ; // end
	}

	input >> x >> y ; // in >> a >> b ;// std::cout << a << " " << b ;
	//cout << x <<" " << y <<endl ;
	if ( x == 0 || y == 0 ) {
    	cout << "Input maze format error!" <<endl ;
    	return false ;
	}

	pattern = vector<vector<char>>(y, vector<char>(x, '0')) ;
	for ( int i = 0 ; i < y ; i++ ){ //pattern.size()
		for ( int j = 0 ; j < x ; j++ ){ //pattern[i].size()

            if (input.eof()){
                cout << "Input maze format error!" <<endl ;
                return false ;
            }
			input >> pattern[i][j] ;
			// cout << pattern[i][j] << endl ;
			if ( pattern[i][j] != 'E' && pattern[i][j] != 'O' && pattern[i][j] != 'G' ) {
                cout << "Input maze format error!" <<endl ;
                return false ;
            }


		}/*
		for( int j = 0 ; j < x ; j++ ){
            cout << pattern[i][j] << " " ;

		}
		cout << endl ;*/

	}

	patternV = pattern ;
	patternR = pattern ;

	mode = inmode ;
	if ( mode == oneG ){
        gamount = 1 ;
        setModeAndG = true ;
	}


	while( setModeAndG == false && gamount == 0  ){
		gamount = 0 ;
		bool errorchar = false ;
		if( setModeAndG == false ) {
			string a ;
			cout << "Number of G (goals):" ;
			cin >> a ;

			for ( int i = 0 ; !errorchar &&i < a.length() ; i++ ){
				if ( a[i] == '0' ){
					gamount = gamount + 0*pow(10,a.length()-i-1) ;// gamount = gamount + 0*10 ;
					setModeAndG = true ;
                }
				else if ( a[i] == '1' ){
					gamount = gamount + 1*pow(10,a.length()-i-1) ;//gamount = gamount + 1*10 ;
					setModeAndG = true ;
                }
				else if ( a[i] == '2' ){
					gamount = gamount + 2*pow(10,a.length()-i-1) ;//gamount = gamount + 2*10 ;
					setModeAndG = true ;
                }
				else if ( a[i] == '3' ){
					gamount = gamount + 3*pow(10,a.length()-i-1) ;//gamount = gamount + 3*10 ;
					setModeAndG = true ;
                }
				else if ( a[i] == '4' ){
					gamount = gamount + 4*pow(10,a.length()-i-1) ;//gamount = gamount + 4*10 ;
					setModeAndG = true ;
                }
				else if ( a[i] == '5' ){
					gamount = gamount + 5*pow(10,a.length()-i-1) ;//gamount = gamount + 5*10 ;
					setModeAndG = true ;
                }
				else if ( a[i] == '6' ){
					gamount = gamount + 6*pow(10,a.length()-i-1) ;//gamount = gamount + 6*10 ;
					setModeAndG = true ;
                }
				else if ( a[i] == '7' ){
					gamount = gamount + 7*pow(10,a.length()-i-1) ;//gamount = gamount + 7*10 ;
					setModeAndG = true ;
                }
				else if ( a[i] == '8' ){
					gamount = gamount + 8*pow(10,a.length()-i-1) ;//gamount = gamount + 8*10 ;
					setModeAndG = true ;
                }
				else if ( a[i] == '9' ){
					gamount = gamount + 9*pow(10,a.length()-i-1) ;//gamount = gamount + 9*10 ;
					setModeAndG = true ;
                }
				else {
                    errorchar = true ;
					setModeAndG = false ;
					gamount = 0 ;
				}
			}
			if ( gamount <= 0 || gamount > 100 ){
                cout << "illegal input!" << endl ;
                cout << "### The number must be in [1,100] ###/" << endl ;
                cout << endl ;
                gamount = 0 ;
                setModeAndG = false ;
            }
		}
	}
    // cout << gamount << endl ;
	input.close() ;
	return true ;
}


void Maze::show( bool success ) {
	for ( int i = 0 ; i < y ; i++ ){
		for ( int j = 0 ; j < x ; j++ ) {
			if ( pattern[i][j] == 'G' )
				cout << pattern[i][j] ;
			else
				cout << patternV[i][j] ;
		}

		cout << endl ;
	}
	cout << endl ;


	for ( int i = 0 ; i < pass.size() ; i++ ){
		for( int j = 0 ; j < pass[i].size() ; j++ ){
			patternR[pass[i][j].first][pass[i][j].second] = 'R' ;
		}
	}

	for ( int i = 0 ; success && i < y ; i++ ){
		for ( int j = 0 ; j < x ; j++ ){
			if ( pattern[i][j] == 'G' )
				cout << pattern[i][j] ;
			else
				cout << patternR[i][j] ;
		}

		cout << endl ;
	}

}


bool Maze::findGoals( int currenty, int currentx) {
	if ( findg == gamount )
		return true ;


	temproute.push_back( make_pair(currenty,currentx) ) ; // store temp pass

	//temproute[0].first ;
	//temproute[0].second
	//temproute.back().first
	//temproute.size()

	patternV[ currenty ][ currentx ] = 'V' ;
	int trydirection = 0 ;
	if ( pattern[ currenty ][ currentx ] == 'G' ){
		findg++;
		pass.push_back(temproute) ; // pass.push_back( make_pair(temproute.first,temproute.second) ) ; copy the total route
	}


	// decide move to which place, according to the counterclockwise principle
	while( trydirection != 4 ){
		int tempy, tempx ;

		if( direction == Right ) {
			if ( (currentx+1 < x) && (patternV[ currenty ][ currentx+1 ] != 'O') && (patternV[ currenty ][ currentx+1 ] != 'V') ) {
				tempx = currentx + 1 ;
				tempy = currenty ;
				findGoals( tempy, tempx ) ;
			}
			direction = Down ;
		}
		else if( direction == Down ) {
			if ( (currenty+1 < y) && (patternV[ currenty+1 ][ currentx ] != 'O') && (patternV[ currenty+1 ][ currentx ] != 'V') ) {
				tempx = currentx ;
				tempy = currenty + 1 ;
				findGoals( tempy, tempx ) ;
			}
			direction = Left ;
		}
		else if( direction == Left ) {
			if ( (currentx-1 >= 0) && (patternV[ currenty ][ currentx-1 ] != 'O') && (patternV[ currenty ][ currentx-1 ] != 'V') ) {
				tempx = currentx - 1 ;
				tempy = currenty ;
				findGoals( tempy, tempx ) ;
			}
			direction = Up ;
		}
		else if( direction == Up ) {
			if ( (currenty-1 >= 0) && (patternV[ currenty-1 ][ currentx ] != 'O') && (patternV[ currenty-1 ][ currentx ] != 'V') ) {
				tempx = currentx ;
				tempy = currenty - 1 ;
				findGoals( tempy, tempx ) ;
			}
			direction = Right ;
		}
		trydirection++ ;

	} // end while



	temproute.pop_back() ; // pop out illegal route

	if ( findg == gamount )
		return true ;

	return false ; // findg != gamount

}


void Maze::clean() {
	vector<vector<char> >().swap(pattern); // clean the size and capacity
	vector<vector<char> >().swap(patternV);
	vector<vector<char> >().swap(patternR);
	vector<pair<int,int> >().swap(temproute);
	vector<vector<pair<int,int> > >().swap(pass);
}


int main() {
	string command = "0" ;

	while(true) {
		Maze aMaze ;
		string fileName ;
		Modes mode = oneG ;

		cout<< endl << "*** Path Finding ***" ;
		cout<< endl << "* 0. Quit          *" ;
		cout<< endl << "* 1. One goal      *" ;
		cout<< endl << "* 2. More goals    *" ;
		cout<< endl << "********************" ;
		cout<< endl << "Input a command(0, 1, 2): " ;

		std::cin>> command ;
		if ( command.compare( "0" ) == 0 )
			break ;
		else if( command.compare( "1" ) == 0 || command.compare( "2" ) == 0 ) {
			if( command.compare( "2" ) == 0 )
				mode = moreG ;
			cout<< endl << "Input a file number (e.g., 101,102,...):" ;
			std::cin>> fileName;
			if ( aMaze.load( fileName, mode ) ) {
				bool success = aMaze.findGoals( 0, 0 ) ;
				aMaze.show( success ) ;
				mode = oneG ; // resetting the mode to one
			}
			aMaze.clean() ; // clear up all of the vector
		}

		else
			cout<< endl << "Command does not exist!" << endl ;
	} // end while

	return 0 ;
}










