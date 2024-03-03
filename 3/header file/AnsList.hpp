#ifndef _AnsList_HPP
#define _AnsList_HPP
#include <iostream> // cout, endl
#include <fstream> // open, is_open
#include <string> // string
#include <vector> // vector
#include <cstdlib> // atoi, system
#include <iomanip> // setw, setprecision
#include <ctime> // clock, CLOCKS_PER_SEC
#include <exception>
using namespace std;

class AnsList{
    struct abortType{
        int OID ; // currentTime
        int Abort ;
        int Delay ;
        int Arrival ;
        int Duration ;
        int TimeOut ;
    };
    struct doneType{
        int OID; // duration
        int Departure ;
        int Delay ;
        int Arrival ;
        int Duration ;
        int TimeOut ;
    };
    vector<abortType> abortJobs; // list of aborted jobs with three columns
    vector<doneType> doneJobs; // list of done jobs with three columns
    float avgDelay; // average delay
    float successRate; // percentage of done jobs

    void showAbortJobs(string){ // declaration: display abort jobs on screen
        cout << endl << "\t[Abort List]" << endl;
        cout << endl << "\tOID\tAbort\tDelay" << endl;
        int i = 1 ;
        while( i-1<abortJobs.size() ){
            string n = "[" + to_string(i) + "]" ;
            cout << "\t" << n << "\t" << abortJobs[i-1].OID << "\t" << abortJobs[i-1].Abort << "\t" << abortJobs[i-1].Delay << endl;
            i++;
        }
    }
    void showDoneJobs(string){ // declaration: display done jobs on screen
        cout << endl << "\t[Done List]" << endl;
        cout << endl << "\tOID\tDeparture\tDelay" << endl;
        int i = 1 ;
        while( i-1<doneJobs.size() ){
            string n = "[" + to_string(i) + "]" ;
            cout << n << "\t" << doneJobs[i-1].OID << "\t" << doneJobs[i-1].Departure << "\t"
            << doneJobs[i-1].Delay << endl;
            i++;
        }
    }
    void computeStat(){ // declaration: compute the statistics
        avgDelay = 0.0 ;
        for( int i = 0 ; i < abortJobs.size() ; i++){
            avgDelay = abortJobs[i].Delay + avgDelay ;
        }
        for( int i = 0 ; i < doneJobs.size() ; i++){
            avgDelay = doneJobs[i].Delay + avgDelay ;
        }
        avgDelay = avgDelay / ( abortJobs.size() + doneJobs.size() ) ;
        successRate = (abortJobs.size()+doneJobs.size()) / doneJobs.size() ;
    }
    void showStat(){ // declaration: display statistics on screen
        cout << "[Average Delay]" << "\t" << avgDelay <<" ms" << endl ;
        cout << "[Success Rate]" << "\t" << successRate <<" %" << endl ;
    }
public:
    AnsList(): avgDelay(0.0), successRate(0.0){} // constructor for initialization
    ~AnsList(){ // destructor for initialization

    }
    void showAll(string){ // declaration: display all on screen
        string  a ;
        showAbortJobs(a) ;
        showDoneJobs(a) ;
        showStat() ;
    }
    void addAbortJob(int OID, int Arrival, int Duration, int TimeOut){ // declaration: add one aborted job
        struct abortType abort ;
        abort.OID = OID ;
        abort.Abort = Arrival + Duration ;
        abort.Delay = 0 ;
        abortJobs.push_back( abort );
    }
    void addDoneJob(int OID, int Arrival, int Duration, int TimeOut){ // declaration: add one done job
        struct doneType done ;
        done.OID = OID ;
        done.Departure = Arrival + Duration ;
        done.Delay = 0 ;
        doneJobs.push_back( done ) ;
    }
    void putAll(string fileID, string ){ // declaration: write all as a file
            string fileout = "output"+fileID+".txt" ;    
        try{
            ofstream sortedout( fileout.c_str() ) ;
            if(!sortedout){
                //throw FileException("### Cannot create output") ;
            }
            sortedout << "\t[Abort Jobs]\n" ;
            sortedout << "\tOID\tAbort\tDelay" << endl;
            for( int i = 1 ; i-1<abortJobs.size() ; i++ ){
                string n = "[" + to_string(i) + "]" ;
                sortedout << n << "\t" << abortJobs[i-1].OID << "\t" << abortJobs[i-1].Abort << "\t" << abortJobs[i-1].Delay << endl ;
            }

            sortedout << "\n\t[Jobs Done]\n" ;
            sortedout << "\tOID\tDeparture\tDelay" << endl;
            for( int i = 1 ; i-1<abortJobs.size() ; i++ ){
                string n = "[" + to_string(i) + "]" ;
                sortedout << n << "\t" << abortJobs[i-1].OID << "\t" << abortJobs[i-1].Abort << "\t" << abortJobs[i-1].Delay << endl ;
            }

            sortedout << "[Average Delay]\t" << avgDelay << " ms" << endl ;
            sortedout << "[Success Rate]\t" << successRate << " %" << endl ;
            sortedout.close() ;
        }
        catch(exception & FileException){

        }
    }

}; // end AnsList


#endif //_AnsList_HPP