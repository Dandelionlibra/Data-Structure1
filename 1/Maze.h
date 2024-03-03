/** @file Maze.h */
#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
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

/*
enum Pattern {
	E, //empty
	O, //obstacle
	G, //goal
	V, //visited
	R  //route
};*/

class Maze{
	public:
		Maze() ;
		//Maze( const Maze& aMaze ) ; // copy aMaze to vMaze
		bool load( string fileName, Modes inmode ) ;
		// bool findGoals( Maze vMaze ) ;
		bool findGoals( int currenty, int currentx) ;
		// void show() ;
		void show( bool success ) ;
		void clean() ;

	private:
		Modes mode ; // self mode
		Direction direction = Right ; // record the directon of mouse
		int x, y ; // width, high
		// int currentx = 0, currenty = 0 ; // record the current point while pass the maze
		int gamount = 1 ; // initial let the amount of g which need to be found is 1
		int findg = 0 ; // record the goal that we already found
		vector<vector<char> > pattern; //(x, vector<char> (y, 0))
		vector<vector<char> > patternV;
		vector<vector<char> > patternR;
		vector<pair<int,int> > temproute; // temple
		vector<vector<pair<int,int> > > pass; // (0,1),(0,2)...
		bool setModeAndG = false ; // already setting mode or not
		//bool Back = false ;
};

/*
Maze::Maze() {
	pattern = vector<vector<char>>(x, vector<char>(y, '0')) ;
	
	for ( int i = 0 ; i < pattern.size() ; i++ ) {
		for ( int j = 0 ; j < pattern[i].size() ; j++ ){
			pattern[i][j]= '0' ;
		}
	}
}*/

Maze::Maze() {
}
/*
Maze::Maze( const Maze& aMaze ) {
	x = aMaze.x ;
	y = aMaze.y ;
	mode = aMaze.mode ;
	pattern = aMaze.pattern ;
}*/


bool Maze::load( string fileName, Modes inmode ) {
	fileName = "input"+fileName+".txt" ;
	ifstream input( fileName.c_str() ); // c_str()將String物件轉換成C語言形式的字串常數。
	
	if( !input ) { // confirm existence or not
		cout << fileName << " doesn't exist!";
		return false ; // end
	}
	
	input >> x >> y ; // in >> a >> b ;// std::cout << a << " " << b ;

	pattern = vector<vector< char > >(y, vector<char>(x, '0')) ;
	for ( int i = 0 ; i < y ; i++ ){ //pattern.size()
		for ( int j = 0 ; j < x ; j++ ){ //pattern[i].size()
			input >> pattern[i][j] ;
		}
	}
	patternV = pattern ;
	patternR = pattern ;

	mode = inmode ;	
	if ( mode == oneG )
		setModeAndG = true ;

	if( !setModeAndG ) {
		cout << "Number of G (goals):" ;
		cin >> gamount ;
		setModeAndG = true ;
	}

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






/*
bool Maze::findGoals( int currentx, int currenty) {

	if ( findg == gamount )
		return true ;
	temproute.push_back( make_pair(currentx,currenty) ) ; // store temp pass

	//temproute[0].first
	//temproute[0].second
	//temproute.back().first
	//temproute.size()

	patternV[ currentx ][ currenty ] = 'V' ;
	int trydirection = 0 ;
	if ( pattern[ currentx ][ currenty ] == 'G' ){
		findg++;
		pass.push_back(temproute) ; // pass.push_back( make_pair(temproute.first,temproute.second) ) ; copy the total route
	}
	

	// decide move to which place, according to the counterclockwise principle
	while( trydirection != 4 ){
		int tempx, tempy ;

		if( direction == Right ) {
			if ( (currentx+1 < x) && (patternV[ currentx+1 ][ currenty ] != 'O') && (patternV[ currentx+1 ][ currenty ] != 'V') ) {
				tempx = currentx + 1 ;
				tempy = currenty ;
				findGoals( tempx, tempy ) ;
			}
			direction = Down ;
		}
		else if( direction == Down ) {
			if ( (currenty+1 < y) && (patternV[ currentx ][ currenty+1 ] != 'O') && (patternV[ currentx ][ currenty+1 ] != 'V') ) {
				tempx = currentx ;
				tempy = currenty + 1 ;
				findGoals( tempx, tempy ) ;
			}
			direction = Left ;
		}
		else if( direction == Left ) {
			if ( (currentx-1 >= 0) && (patternV[ currentx-1 ][ currenty ] != 'O') && (patternV[ currentx-1 ][ currenty ] != 'V') ) {
				tempx = currentx - 1 ;
				tempy = currenty ;
				findGoals( tempx, tempy ) ;
			}
			direction = Up ;
		}
		else if( direction == Up ) {
			if ( (currenty-1 >= 0) && (patternV[ currentx ][ currenty-1 ] != 'O') && (patternV[ currentx ][ currenty-1 ] != 'V') ) {
				tempx = currentx ;
				tempy = currenty - 1 ;
				findGoals( tempx, tempy ) ;
			}
			direction = Right ;
		}
		trydirection++ ;
*/
		/*
		if( direction == Right ) {
			if ( (currentx+1 < x) && (patternV[ currentx+1 ][ currenty ] != 'O') && (patternV[ currentx+1 ][ currenty ] != 'V') ) {
				currentx = currentx + 1 ;
				if ( patternV[ currentx ][ currenty ] == 'G' )
					findg++ ;
				patternV[ currentx ][ currenty ] = 'V' ;
			}
			else{
				direction = Down ;
				trydirection++ ;
			}
		}
		if( direction == Down ) {
			if ( (currenty+1 < y) && (patternV[ currentx ][ currenty+1 ] != 'O') && (patternV[ currentx ][ currenty+1 ] != 'V') ) {
				currenty = currenty + 1 ;
				if ( patternV[ currentx ][ currenty ] == 'G' )
					findg++ ;
				patternV[ currentx ][ currenty ] = 'V' ;
			}
			else{
				direction = Left ;
				trydirection++ ;
			}
		}
		if( direction == Left ) {
			if ( (currentx-1 >= 0) && (patternV[ currentx-1 ][ currenty ] != 'O') && (patternV[ currentx-1 ][ currenty ] != 'V') ) {
				currentx = currentx - 1 ;
				if ( patternV[ currentx ][ currenty ] == 'G' )
					findg++ ;
				patternV[ currentx ][ currenty ] = 'V' ;
			}
			else{
				direction = Up ;
				trydirection++ ;
			}
		}
		if( direction == Up ) {
			if ( (currenty-1 >= 0) && (patternV[ currentx ][ currenty-1 ] != 'O') && (patternV[ currentx ][ currenty-1 ] != 'V') ) {
				currenty = currenty - 1 ;
				if ( patternV[ currentx ][ currenty ] == 'G' )
					findg++ ;
				patternV[ currentx ][ currenty ] = 'V' ;
			}
			else{
				direction = Right ;
				trydirection++ ;
			}
		}
		

		//findGoals( tempx, tempy ) ;
	} // end while



	temproute.pop_back() ; // pop out illegal route

	if ( findg == gamount )
		return true ;

	return false ; // findg != gamount

	// return findGoals( currentx, currenty ) ;
}
*/


/*
bool Maze::findGoals( Maze vMaze ) { // clockwise
	int posx = currentx ;
	int posy = currenty ;
	int trydirection = 0 ;
	Back = false ;
	if ( mode == oneG ) {
		

	}
	else if( mode == moreG ) {
		// set the amount of g, when mode != oneG
		if( !setModeAndG ) {
			cout << "Number of G (goals):" ;
			cin >> gamount ;
			setModeAndG = true ;
		}
	}

	// decide move to which place, according to the counterclockwise principle
	while( trydirection != 4 ){
		if( vMaze.direction == Right ) {
			if ( (vMaze.currentx+1 < vMaze.x) && (vMaze.pattern[ vMaze.currentx+1 ][ vMaze.currenty ] != 'O') && (vMaze.pattern[ vMaze.currentx+1 ][ vMaze.currenty ] != 'V') ) {
				vMaze.currentx = vMaze.currentx + 1 ;
				if ( vMaze.pattern[ vMaze.currentx ][ vMaze.currenty ] == 'G' )
					findg++ ;
				vMaze.pattern[ vMaze.currentx ][ vMaze.currenty ] = 'V' ;
			}
			else{
				vMaze.direction = Down ;
				trydirection++ ;
			}
		}
		if( vMaze.direction == Down ) {
			if ( (vMaze.currenty+1 < vMaze.y) && (vMaze.pattern[ vMaze.currentx ][ vMaze.currenty+1 ] != 'O') && (vMaze.pattern[ vMaze.currentx ][ vMaze.currenty+1 ] != 'V') ) {
				vMaze.currenty = vMaze.currenty + 1 ;
				if ( vMaze.pattern[ vMaze.currentx ][ vMaze.currenty ] == 'G' )
					findg++ ;
				vMaze.pattern[ vMaze.currentx ][ vMaze.currenty ] = 'V' ;
			}
			else{
				vMaze.direction = Left ;
				trydirection++ ;
			}
		}
		if( vMaze.direction == Left ) {
			if ( (vMaze.currentx-1 >= 0) && (vMaze.pattern[ vMaze.currentx-1 ][ vMaze.currenty ] != 'O') && (vMaze.pattern[ vMaze.currentx-1 ][ vMaze.currenty ] != 'V') ) {
				vMaze.currentx = vMaze.currentx - 1 ;
				if ( vMaze.pattern[ vMaze.currentx ][ vMaze.currenty ] == 'G' )
					findg++ ;
				vMaze.pattern[ vMaze.currentx ][ vMaze.currenty ] = 'V' ;
			}
			else{
				vMaze.direction = Up ;
				trydirection++ ;
			}
		}
		if( vMaze.direction == Up ) {
			if ( (vMaze.currenty-1 >= 0) && (vMaze.pattern[ vMaze.currentx ][ vMaze.currenty-1 ] != 'O') && (vMaze.pattern[ vMaze.currentx ][ vMaze.currenty-1 ] != 'V') ) {
				vMaze.currenty = vMaze.currenty - 1 ;
				if ( vMaze.pattern[ vMaze.currentx ][ vMaze.currenty ] == 'G' )
					findg++ ;
				vMaze.pattern[ vMaze.currentx ][ vMaze.currenty ] = 'V' ;
			}
			else{
				vMaze.direction = Right ;
				trydirection++ ;
			}
		}
	} // end while


	if( trydirection == 4 )
		Back = true ;
	

	if ( Back ) {
		currentx = posx ;
		currenty = posy ;
		Back = false ;
	}

	if ( findg == gamount )
		return true ;
	else if ( ( currentx == 0 && currenty == 0 ) && ( findg != gamount ) )
		return false ;
	return findGoals( vMaze ) ;
}
*/
void Maze::clean() {
	pattern.clear() ;
	pattern.clear() ;
	patternR.clear() ;
	cout <<"vec.size(): " << pattern.size() << endl;
    cout <<"vec.capasity(): " << pattern.capacity() << endl;
	cout <<"temproute.size(): " << temproute.size() << endl;
    cout <<"pass.capasity(): " << pass.capacity() << endl;
	vector<vector<char> >().swap(pattern);
	vector<vector<char> >().swap(patternV);
	vector<vector<char> >().swap(patternR);
	vector<pair<int,int> >().swap(temproute); // temple
	vector<vector<pair<int,int> > >().swap(pass); // (0,1),(0,2)...

	cout <<"vec.size(): " << pattern.size() << endl;
    cout <<"vec.capasity(): " << pattern.capacity() << endl;

}
