//11127132, 羅海綺
//11127138, 林雨臻
#include "JobList.hpp"
#include "JobQueue.hpp"
#include "AnsList.hpp"
#include "Simulation.hpp"

int main(){
    string command = "0" ;
    string fileName ;
    while( true ){
        JobList job_list ; // task 1
        
		cout << endl << "**** Simulate FIFO Queues by SQF *****" ;
		cout << endl << "* 0. Quit                            *" ;
		cout << endl << "* 1. Sort a file                     *" ;
		cout << endl << "* 2. Simulate one FIFO queue         *" ;
		cout << endl << "**************************************" ;
		cout << endl << "Input a command(0, 1, 2): " ;
        cin >> command ;
		if ( command.compare( "0" ) == 0 )
			break ;
        else if( command.compare( "1" ) == 0 || command.compare( "2" ) == 0 ) {
            if( command.compare( "1" ) == 0 ){
                cout << endl << "Input a file number: " ;
                cin >> fileName ;
                if ( job_list.getAll( fileName ) ){
                    job_list.Test();
                    std::cout << endl << "See sorted" << fileName <<".txt" << endl ;
                }

            }
            else{
                if ( fileName.size() == 0 ){
                    cout << endl << "Input a file number: " ;
                    cin >> fileName ;
                    //### sorted304.txt does not exist! ###
                }
                if( job_list.opensortedfile(fileName) ){
                    Simulation job_simulation( job_list, 1 ) ;
                    //AnsList a ;
                    //a.showAll(fileName) ;
                    std::cout << endl << "See output" << fileName <<".txt" << endl ;
                }
            }

        }

        else
			cout<< endl << "Command does not exist!" << endl ;
    }

} // main()

