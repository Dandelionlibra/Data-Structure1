#ifndef _JobList_HPP
#define _JobList_HPP
#include <iostream> // cout, endl
#include <fstream> // open, is_open
#include <string> // string
#include <vector> // vector
#include <cstdlib> // atoi, system
#include <iomanip> // setw, setprecision
#include <ctime> // clock, CLOCKS_PER_SEC
using namespace std;

struct jobType{
    int OID; // order identifier
    int arrival; // arrival time
    int duration; // job duration
    int timeout; // expire time
};

class JobList{
    vector<jobType> aList; // list of jobs with four columns
    string fileID; // file identifier
    //***********************************/
    //The above are private data members
    //***********************************/

    void reset(){ //definition: initial set up
        vector<jobType>().swap(aList) ;
    } // end reset
    void showJob(jobType & j); // declaration: display a job on screen //
    void sortByArrival(); // declaration: sort all by arrival time
    void putAll(); // declaration: write all as file
    void showTime(); // declaration: output time on screen
    void nextJobCheck(jobType & nextjob){ // declaration: take a look at the next job
        nextjob = aList[0];
    } // get the next job without removal
    //***********************************/
    //The above are private methods
    //***********************************/

public:
    int read ,sort ,write ;
    JobList(){ reset(); } // constructor for initialization
    ~JobList(){ reset(); } // destructor for initialization
    bool isEmpty(); // check whether it is empty or not
    //***************************************************/
    //The above are primitive methods publicly available
    //***************************************************/

    bool getAll(string fileName); // declaration: read all from a inputfile
    string getfileID (){
        return fileID ;
    }
    int getlengh(){
        return aList.size();
    }
    bool opensortedfile(string fileName){// declaration: read all from a sortedfile
        fileID = fileName ;
        string filein = "sorted" + fileName + ".txt" ;
        string tmp ;
        struct jobType job ;

        ifstream input(filein.c_str()) ;
        if( !input ) { // confirm existence or not
            cout << endl << "### " << filein << " does not exist! ###" << endl;
            return false ;
        }
        input >> tmp >> tmp >> tmp >> tmp; // read the name of column
        while(!input.eof()){
            input >> job.OID >> job.arrival >> job.duration >> job.timeout ;
            aList.push_back( job );
        } // end while

        input.close() ;
        return true ;
    }
    bool getSorted(); // declaration: read all from a file and sort them
    void Test(){
        jobType j;
        showJob( j );
        sortByArrival();
        putAll();
        showTime();
    }
    void nextJob(jobType & nextjob){ // declaration: get & remove the next job
        nextJobCheck(nextjob) ;
        aList.erase(aList.begin());
    }
}; // end JobList




bool JobList::getAll(string fileName){// declaration: read all from a file
    struct jobType job ;
    string tmp, filein = "input"+fileName+".txt" ;
    fileID = fileName ;
    ifstream input( filein.c_str() ); // c_str()將String物件轉換成C語言形式的字串常數。
    if( !input ) { // confirm existence or not
        cout << endl << "### " << filein << " does not exist! ###" << endl;
        return false ; // end
    }

    read = clock() ;
    input >> tmp >> tmp >> tmp >> tmp; // read the name of column
    while(!input.eof()){
        input >> job.OID >> job.arrival >> job.duration >> job.timeout ;
        if (!input.fail()) // ensue when .txt show up lots of \n will not read the last one into vector
            aList.push_back( job );
    } // end while


    read = clock() - read ;
    input.close() ;

    return true ;
}

void JobList::sortByArrival(){ // declaration: sort all by arrival time
    jobType swap;
    int n = aList.size(), tmp, id;
    sort = clock() ;
    for (int interval = n/2 ; interval>0 ; interval = interval/2) {
        for (int i = interval ; i < n ; i++) {
            tmp = aList[i].arrival;
            id = aList[i].OID;
            for (int j = i; j >= interval && aList[j-interval].arrival >= tmp; j = j-interval) {
                if(aList[j-interval].arrival > tmp){
                    swap = aList[j];
                    aList[j] = aList[j-interval];
                    aList[j-interval] = swap;
                } // end if

                if(aList[j-interval].arrival == tmp){
                    if(aList[j-interval].OID > id ){
                        swap = aList[j];
                        aList[j] = aList[j-interval];
                        aList[j-interval] = swap;
                    } // end if
                } // end if
            } // end for
        } // end for
    } // end for

    sort = clock() - sort;
} // end sortByArrival

void JobList::putAll(){ // declaration: write all as file
    string fileout = "sorted"+fileID+".txt" ;
    ofstream sortedout( fileout.c_str() ) ;

    int i = 1 ;
    write = clock();
    sortedout << "OID" << '\t' << "Arrival" << '\t' << "Duration" << '\t' << "TimeOut" << '\n' ;
    //cout << "        " << std::left << setw(8) << "OID" << setw(8) << "Arrival" << setw(16) << "Duration" << setw(8) << "TimeOut" << endl;

    while( i-1<aList.size() ){
        string n = "(" + to_string(i) + ")" ;
        //cout << std::left << setw(8) << n << setw(8) << aList[i-1].OID << setw(8) << aList[i-1].arrival << setw(8) << aList[i-1].duration << setw(8) << aList[i-1].timeout << endl;
        sortedout << aList[i-1].OID << '\t' << aList[i-1].arrival << '\t' << aList[i-1].duration << '\t' << aList[i-1].timeout << '\n' ;
        //aList.erase(aList.begin());
        i++;
    }

    write = clock() - write;
    sortedout.close() ;
}

void JobList::showJob(jobType & j){
    int i = 1 ;
    cout << endl << "\tOID\tArrival\tDuration\tTimeOut" << endl;
    while( i-1<aList.size() ){
        string n = "(" + to_string(i) + ")" ;
        cout << std::left << setw(8) << n << setw(8) << aList[i-1].OID << setw(8) << aList[i-1].arrival << setw(8) << aList[i-1].duration << setw(8) << aList[i-1].timeout << endl;
        //aList.erase(aList.begin());
        i++;
    }
}

void JobList::showTime(){ // declaration: output time on screen
    std::cout << endl << "Reading data: " << read << " clocks " << "(" << fixed << setprecision(2) << double(read) << " ms)" << endl;
    std::cout << "Sorting data: " << sort << " clocks " << "(" << fixed << setprecision(2) << double(sort) << " ms)" << endl;
    std::cout << "Writing data: " << write << " clocks " << "(" << fixed << setprecision(2) << double(write) << " ms)" << endl;
    //std::cout << endl << "See sorted" << fileID <<".txt" << endl ;
}

bool JobList::isEmpty() {
    return aList.empty();
}



#endif //_JobList_HPP
