//11127132, 羅海綺
//11127138, 林雨臻
//#include "JobList.hpp"
//#include "JobQueue.hpp"
//#include "AnsList.hpp"
//#include "Simulation.hpp"
#include <iostream> // cout, endl
#include <fstream> // open, is_open
#include <string> // string
#include <string.h>
#include <vector> // vector
#include <cstdlib> // atoi, system
#include <iomanip> // setw, setprecision
#include <ctime> // clock, CLOCKS_PER_SEC
//#include <exception>
using namespace std;

struct jobType{
    string OID; // order identifier
    int arrival; // arrival time
    int duration; // job duration
    int timeout; // expire time
};
struct abortType{
    string OID ; // currentTime
    int Abort ;
    int Delay ;
};
struct doneType{
    string OID; // duration
    int Departure ;
    int Delay ;
};
struct jobQ{
    jobType j;
    jobQ *next;
};

class JobList{
    string fileID; // file identifier
    vector<jobType> aList; // list of jobs with four columns
    vector<abortType> abortJobs; // list of aborted jobs with three columns
    vector<doneType> doneJobs;
    double avgDelay; // average delay
    double successRate; // percentage of done jobs

    void reset(){ //definition: initial set up
        vector<jobType>().swap(aList) ;
        vector<abortType>().swap(abortJobs) ;
        vector<doneType>().swap(doneJobs) ;
    } // end reset
    void showJob(){ // declaration: display a job on screen //
        int i = 1 ;
        cout << endl << "\tOID\tArrival\tDuration\tTimeOut" << endl;
        while( i-1<aList.size() ){
            string n = "(" + to_string(i) + ")" ;
            cout << std::left << setw(8) << n << setw(8) << aList[i-1].OID << setw(8) << aList[i-1].arrival << setw(8) << aList[i-1].duration << setw(8) << aList[i-1].timeout << endl;
            //aList.erase(aList.begin());
            i++;
        }
    }
    void sortByArrival(){ // declaration: sort all by arrival time
        jobType swap;
        int n = aList.size(), tmp, id;
        sort = clock() ;
        for (int interval = n/2 ; interval>0 ; interval = interval/2) {
            for (int i = interval ; i < n ; i++) {
                tmp = aList[i].arrival;
                id = stoi(aList[i].OID);
                for (int j = i; j >= interval && aList[j-interval].arrival >= tmp; j = j-interval) {
                    if(aList[j-interval].arrival > tmp){
                        swap = aList[j];
                        aList[j] = aList[j-interval];
                        aList[j-interval] = swap;
                    } // end if

                    if(aList[j-interval].arrival == tmp){
                        if(stoi(aList[j-interval].OID) > id ){
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
    void putAll(){ // declaration: write all as file
        string fileout = "sorted"+fileID+".txt" ;
        ofstream sortedout( fileout.c_str() ) ;

        int i = 1 ;
        write = clock();
        sortedout << "OID\tArrival\tDuration\tTimeOut\n" ;

        while( i-1<aList.size() ){
            string n = "(" + to_string(i) + ")" ;
            sortedout << aList[i-1].OID << '\t' << aList[i-1].arrival << '\t' << aList[i-1].duration << '\t' << aList[i-1].timeout << '\n' ;
            //aList.erase(aList.begin());
            i++;
        }

        write = clock() - write;
        sortedout.close() ;
    }
    void showTime(){ // declaration: output time on screen
        cout << endl << "Reading data: " << read << " clocks " << "(" << fixed << setprecision(2) << double(read) << " ms)" << endl;
        cout << "Sorting data: " << sort << " clocks " << "(" << fixed << setprecision(2) << double(sort) << " ms)" << endl;
        cout << "Writing data: " << write << " clocks " << "(" << fixed << setprecision(2) << double(write) << " ms)" << endl;
        //std::cout << endl << "See sorted" << fileID <<".txt" << endl ;
    }

    //***********************************/
    //The above are private methods
    //***********************************/
    void showAbortJobs(){ // declaration: display abort jobs on screen
        cout << endl << "\t[Abort List]" << endl;
        cout << "\tOID\tAbort\tDelay" << endl;
        int i = 1 ;
        while( i-1<abortJobs.size() ){
            string n = "[" + to_string(i) + "]" ;
            cout << n << "\t" << abortJobs[i-1].OID << "\t" << abortJobs[i-1].Abort << "\t" << abortJobs[i-1].Delay << endl;
            i++;
        }
    }
    void showDoneJobs(){ // declaration: display done jobs on screen
        cout << endl << "\t[Done List]" << endl;
        cout << "\tOID\tDeparture\tDelay" << endl;
        int i = 1 ;
        while( i-1<doneJobs.size() ){
            string n = "[" + to_string(i) + "]" ;
            cout << n << "\t" << doneJobs[i-1].OID << "\t" << doneJobs[i-1].Departure << "\t"
            << doneJobs[i-1].Delay << endl;
            i++;
        }
    }
    void computeStat(){ // declaration: compute the statistics
        avgDelay=0,successRate=0 ;
        cout<< "abortJobs.size: " <<abortJobs.size()<< "   doneJobs.size: " <<doneJobs.size()<<endl;

        for( int i = 0 ; i < abortJobs.size() ; i++){
            avgDelay = avgDelay + abortJobs[i].Delay ;
        }
        for( int i = 0 ; i < doneJobs.size() ; i++){
            avgDelay = doneJobs[i].Delay + avgDelay ;
        }
        cout<< "avgDelay: " << avgDelay <<endl;
        if( abortJobs.size()+doneJobs.size()!=0 ){
            avgDelay = avgDelay / (abortJobs.size()+doneJobs.size()) ;
            successRate = 100*double(doneJobs.size()) / (abortJobs.size()+doneJobs.size()) ;
        }
    }
    void showStat(){ // declaration: display statistics on screen
        cout << "[Average Delay]\t" << setprecision(2) << avgDelay <<" ms" << endl ;
        cout << "[Success Rate]\t" << setprecision(2) << successRate <<" %" << endl ;
    }

public:
    int read ,sort ,write ;
    JobList(): avgDelay(0.0), successRate(0.0){ reset(); } // constructor for initialization
    ~JobList(){ reset(); } // destructor for initialization
    string getfileID (){
        return fileID ;
    }
    int getlengh(){
        return aList.size();
    }
    bool isEmpty() { // check whether it is empty or not
        return aList.empty();
    }
    //***************************************************/
    //The above are primitive methods publicly available
    //***************************************************/
    bool getAll(string fileName){ // declaration: read all from a inputfile
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
            if (!input.fail())
                aList.push_back( job );
        } // end while

        input.close() ;
        return true ;
    }
    //bool getSorted(); // declaration: read all from a file and sort them
    void s(){
        showJob();
    }
    void Test(){
        //jobType j;
        showJob();
        sortByArrival();
        putAll();
        showTime();
    }
    int nextJob(){ // declaration: get the next job
        jobType next;
        nextJobCheck(next) ;
        return next.timeout;
    }
    void nextJobCheck(jobType & nextjob){ // declaration: take a look at the next job
        nextjob = aList[0];
    }
    void nextJob(jobType & nextjob){ // declaration: get & remove the next job
        nextJobCheck(nextjob) ;
        aList.erase(aList.begin());
    }
    //*************************************/
    void showAll(){ // declaration: display all on screen
        showAbortJobs() ;
        showDoneJobs() ;
        computeStat() ;
        showStat() ;
    }

    void addAbortJob(jobType& job, int cur, bool isFull, bool proccess){ // declaration: add one aborted job
        abortType abort;
        abort.OID = job.OID ;
        cout << "in addAbortJob!!!!!\nOID:" << job.OID << " Arrival:" << job.arrival << " Duration:" << job.duration << " TimeOut:" << job.timeout << endl ;
        
        
        if( isFull ){
            abort.Abort = job.arrival ;
            abort.Delay = 0;
        }
        else if ( proccess ){
            abort.Abort = job.timeout ;
            abort.Delay = abort.Abort - job.arrival ;
        }
        else {
            abort.Abort = cur ;
            abort.Delay = abort.Abort - job.arrival ;
        }
        abortJobs.push_back( abort );
    }
    void addDoneJob(jobType& job, int cur){ // declaration: add one done job
        doneType done;
        done.OID = job.OID ;
        cout << "in addDoneJob!!!!!\nOID:" << job.OID << " Arrival:" << job.arrival << " Duration:" << job.duration << " TimeOut:" << job.timeout << endl ;

        done.Departure = job.duration + cur ;
        done.Delay = cur - job.arrival ;
        doneJobs.push_back( done ) ;
    }
    void putAll(int a){ // declaration: write all as a file
        string fileout = "output"+fileID+".txt" ;
        ofstream sortedout( fileout.c_str() ) ;
        computeStat() ;
        showStat() ;

        if(!sortedout){
            cout << "### Cannot create output"<< fileID <<".txt ###" ;
            //throw exception ;
        }
        sortedout << "\t[Abort Jobs]\n" ;
        sortedout << "\tOID\tAbort\tDelay" << endl;
        for( int i = 1 ; i-1<abortJobs.size() ; i++ ){
            string n = "[" + to_string(i) + "]" ;
            sortedout << n << "\t" << abortJobs[i-1].OID << "\t" << abortJobs[i-1].Abort << "\t" << abortJobs[i-1].Delay << endl ;
        }

        sortedout << "\n\t[Jobs Done]\n" ;
        sortedout << "\tOID\tDeparture\tDelay" << endl;
        for( int i = 1 ; i-1<doneJobs.size() ; i++ ){
            string n = "[" + to_string(i) + "]" ;
            sortedout << n << "\t" << doneJobs[i-1].OID << "\t" << doneJobs[i-1].Departure << "\t" << doneJobs[i-1].Delay << endl ;
        }

        sortedout << "[Average Delay]\t" << setprecision(2) << double(avgDelay) << " ms" << endl ;
        sortedout << "[Success Rate]\t" << setprecision(2) << double(successRate) << " %" << endl ;
        sortedout.close() ;
    }

}; // end JobList

class JobQueue{
    jobQ *qFront, *qBack, *tmp; // head & tail of queue
    int qSize, qMax; // current size & max size of queue
public:
    int avail; // the time when CPU is available
    JobQueue():qFront(nullptr), qBack(nullptr), qSize(0), qMax(0), avail(3){} // construtor of no-space queue
    JobQueue(int maxS):qFront(nullptr), qBack(nullptr), qSize(0), qMax(maxS), avail(0){} // construtor of an empty queue
    

    int length() const{ // get the current queue length
        return qSize;
    }
    bool isEmpty() const{ // check whether it is empty
        return qFront == nullptr ;
    }
    bool isFull() const{ // check whether it is full
        cout << " qsize:" << qSize << " qmax:" << qMax << endl ;
        return qSize == qMax ;
    }
    void enQueue(jobType job){ // append a new element
        try{
            if ( isEmpty() ) {
                qFront = new jobQ();
                qFront->j = job ;
                //qFront->OID = job.OID;
                //qFront->arrival = job.arrival;
                //qFront->duration = job.duration;
                //qFront->timeout = job.timeout;
                qFront->next = qFront;
                qBack = qFront;
            } // end if 
            else{
                qBack->next = new jobQ();
                qBack = qBack->next;
                qBack->next = qFront;
                qBack->j = job ;
                //qBack->OID = job.OID;
                //qBack->arrival = job.arrival;
                //qBack->duration = job.duration;
                //qBack->timeout = job.timeout;
            } // end else
            qSize++ ;
        } // end try
        catch(std::bad_alloc& ba){ // unable to allocate space
            std::cerr << endl << "bad_alloc on queue caught: " << ba.what() << endl;
        } // end catch
    }
    void getFront(jobType &job){ // get the first element
        job = qFront->j;
    }
    void deQueue(){ // drop the first element
        cout<< "!!!!!!!!!!!!!deQueue!!!!!!!!!!!!!!!!" << endl ;
        if( !isEmpty() && qFront==qBack ){
            delete qFront ;
            qFront = nullptr;
            qBack = nullptr ;
            tmp = nullptr ;
        }
        else if( !isEmpty() ){
            tmp = qFront;
            qFront = qFront->next;
            qBack->next = qFront->next;
            tmp->next = nullptr;
            delete tmp;
            tmp = NULL;
            qSize--;
        } // end if
        
    }
    void deQueue(jobType &job){ // get & drop the first element
        cout<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl ;
        if( !isEmpty() ){
            cout<< "!isempty" << endl ;
            job = qFront->j ;
            tmp = qFront;
            if( qFront == qBack ){
                delete qFront ;
                qFront = NULL ;
                qBack = NULL ;
            }
            qBack->next = qFront->next;
            qFront = qFront->next;
            tmp->next = nullptr;
            delete tmp;
            tmp = NULL;
        } // end if
        qSize--;
    }
    void show(){
        tmp = qFront;
        cout<< "\nshow in queue!!!! " <<endl ;
        if (!isEmpty()){
            do{
                cout<<"O:"<<tmp->j.OID<<" A:"<<tmp->j.arrival<<" D:"<<tmp->j.duration<<" T:"<<tmp->j.timeout<<" "<<endl ;
                tmp = tmp->next;
            }while ( tmp!=qBack );
            if( tmp==qBack ){
                cout<<"O:"<<tmp->j.OID<<" A:"<<tmp->j.arrival<<" D:"<<tmp->j.duration<<" T:"<<tmp->j.timeout<<" "<<endl ;
            }
        }
    }
    void clearQ(){ // clean up
        while (!isEmpty())
            deQueue();
    }
    ~JobQueue(){ // destrutor
        clearQ() ;
    } // end destrutor
    
}; // end JobQueue

void Simulation ( JobList job_list, int cpu ){
    jobType tJob, qJob ; // temp
    int max = 3 ;
    string curOID ;
    vector<JobQueue> queue(max, JobQueue(3)) ;
    int curtime = 0 ;
    bool proccess = false ;
    for( int i=1 ; i<cpu ; i++ ){ // create not only one queue
        JobQueue q(max);
        queue.push_back(q);
    }

    job_list.nextJob(tJob) ;
    curtime = tJob.arrival ;
    cout << "OID:" << tJob.OID << " Arrival:" << tJob.arrival << " Duration:" << tJob.duration << " TimeOut:" << tJob.timeout << endl ;
    if( tJob.arrival+tJob.duration <= tJob.timeout )
        job_list.addDoneJob(tJob, curtime) ;
    else
        job_list.addAbortJob(tJob, curtime, queue[0].isFull(), true ) ;
    curtime += tJob.duration ;
    cout << "1.curtime:" << curtime << "OID:" << tJob.OID << " Arrival:" << tJob.arrival << " Duration:" << tJob.duration << " TimeOut:" << tJob.timeout << endl ;
    job_list.showAll();


    
    while( !job_list.isEmpty() ){
        //cout << "Press Enter to continue" << std::endl;
        //cin.ignore(1000000000, '\n');
        cout << "curtime: (" << curtime << ")\n\n" ;
        job_list.nextJobCheck(tJob) ;
        while( !job_list.isEmpty() && tJob.arrival < curtime ){
            cout << "Press Enter to continue..." << endl;
            cin.ignore(1000000000, '\n');
            if( !queue[0].isFull() ){
                cout << "N\n\n";
                job_list.nextJob(tJob) ;
                queue[0].enQueue(tJob) ;
            }
            else{ // when quene isfull but a task is arrive
                cout << "T\n\n";
                job_list.nextJob(tJob) ;
                job_list.addAbortJob(tJob, curtime, queue[0].isFull(), false ) ;
            }
            queue[0].show() ;
            job_list.showAll();
            job_list.s() ;
            if ( !job_list.isEmpty() )
                job_list.nextJobCheck(tJob) ;
            cout << "Press Enter to continue..." << endl;
            cin.ignore(1000000000, '\n');
        }

        queue[0].getFront(qJob) ;
        curOID = qJob.OID ;
        cout << "2.curtime:" << curtime << "OID:" << qJob.OID << " Arrival:" << qJob.arrival << " Duration:" << qJob.duration << " TimeOut:" << qJob.timeout << endl ;
        bool overdue = true ;
        while ( overdue && !queue[0].isEmpty() ){
            queue[0].getFront(qJob) ;
            if( curtime > qJob.timeout ){
                queue[0].deQueue() ;
                job_list.addAbortJob(qJob, curtime, queue[0].isFull(), curOID.compare(qJob.OID) == 0) ;
            }
            else{
                overdue = false ;
            }
        }
        bool done = true ;
        cout << "3.curtime:" << curtime << "OID:" << qJob.OID << " Arrival:" << qJob.arrival << " Duration:" << qJob.duration << " TimeOut:" << qJob.timeout << endl ;

        while( done ){
            queue[0].getFront(qJob) ;
            int a = qJob.arrival+qJob.duration ;
            if( curtime == a ){
                queue[0].deQueue() ;
                job_list.addDoneJob(qJob, curtime) ;
            }
            else{
                done = false ;
            }
        }
        curtime+=1;
    }
    
    while( !queue[0].isEmpty() ){ // finish the remains in queue
        queue[0].getFront(qJob) ;
        
        bool overdue = true ;
        while ( overdue && !queue[0].isEmpty() ){
            cout << "4.curtime:" << curtime << " OID:" << qJob.OID << " Arrival:" << qJob.arrival << " Duration:" << qJob.duration << " TimeOut:" << qJob.timeout << endl << endl ;

            queue[0].getFront(qJob) ;
            if( curtime > qJob.timeout ){
                queue[0].deQueue() ;
                job_list.addAbortJob(qJob, curtime, queue[0].isFull(), true) ;
            }
            else{
                overdue = false ;
            }
        }/*
        bool done = true ;
        while( done ){
            queue[0].getFront(qJob) ;
            int a = qJob.arrival+qJob.duration ;
            if( curtime == a ){
                queue[0].deQueue() ;
                job_list.addDoneJob(qJob, curtime) ;
            }
            else{
                done = false ;
            }
        }*/
        curtime+=1;
    } // end if




    job_list.putAll(1);
    cout << "END !!!!!!!!!" << endl;
    job_list.showAll();
    //job_list.s() ;
}

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
                    cout << endl << "See sorted" << fileName <<".txt" << endl ;
                }
                //job_list.s() ;
                //cout << endl ;
            }
            else{
                if ( fileName.size() == 0 ){
                    cout << endl << "Input a file number: " ;
                    cin >> fileName ;
                    //### sorted304.txt does not exist! ###
                }
                if( job_list.opensortedfile(fileName) ){
                    Simulation ( job_list, 1 ) ;
                    //jobType j ;
                    //job_list.nextJob(j) ;
                    //cout << j.OID <<" " << j.arrival << endl ;

                    //job_list.s() ;
                    std::cout << endl << "See output" << fileName <<".txt" << endl ;
                }
            }
        }
        else
			cout<< endl << "Command does not exist!" << endl ;
    }

} // main()