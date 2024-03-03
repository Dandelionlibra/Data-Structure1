#ifndef _JobQueue_HPP
#define _JobQueue_HPP
#include "JobList.hpp"
#include <iostream> // cout, endl
#include <fstream> // open, is_open
#include <string> // string
#include <vector> // vector
#include <cstdlib> // atoi, system
#include <iomanip> // setw, setprecision
#include <ctime> // clock, CLOCKS_PER_SEC
using namespace std;

template <typename T>
class JobQueue{
    struct jobQ{
        int OID; // order identifier
        int arrival; // arrival time
        int duration; // job duration
        int timeout; // expire time
        jobQ *next;
    };
    //T *cA; // circular array
    jobQ *qFront, *qBack, *tmp; // head & tail of queue
    int qSize, qMax; // current size & max size of queue

    //int next(int idx){} // move to the next position in queue

public:
    int avail; // the time when CPU is available
    JobQueue():qFront(nullptr), qBack(nullptr), qSize(0), qMax(0), avail(0){} // construtor of no-space queue
    JobQueue<T>(int maxS):qFront(nullptr), qSize(0), avail(0){ // construtor of an empty queue

    } // end construtor

    int length() const{ // get the current queue length
        return qSize;
    }

    bool isEmpty() const{ // check whether it is empty
        return qFront == nullptr;
    }

    bool isFull() const{ // check whether it is full
        if ( qSize == qMax ){
            return true ;
        }
        return false ;
    }

    void enQueue(jobType &job){ // append a new element
         try{
            if ( isEmpty() ) {
                qFront = new jobQ();
                qFront->OID = job.OID;
                qFront->arrival = job.arrival;
                qFront->duration = job.duration;
                qFront->timeout = job.timeout;
                qFront->next = qFront;
                qBack = qFront;
            } // end if 
            else{
                qBack->next = new jobQ();
                qBack = qBack->next;
                qBack->OID = job.OID;
                qBack->arrival = job.arrival;
                qBack->duration = job.duration;
                qBack->timeout = job.timeout;
                qBack->next = qFront;
            } // end else
        } // end try
        catch(std::bad_alloc& ba){ // unable to allocate space
            std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
        } // end catch
    }

    void getFront(jobType &job){ // get the first element
        job.OID = qFront->OID;
        job.arrival = qFront->arrival;
        job.duration = qFront->duration;
        job.timeout = qFront->timeout;
    }

    void deQueue(){ // drop the first element
        tmp = qFront;
        if( !isEmpty() ){
            qBack->next = qFront->next;
            qFront = qFront->next;
            tmp->next = nullptr;
            delete tmp;
        } // end if
    }

    void deQueue(jobType &job){ // get & drop the first element
        job.OID = qFront->OID;
        job.arrival = qFront->arrival;
        job.duration = qFront->duration;
        job.timeout = qFront->timeout;
        tmp = qFront;
        if( !isEmpty() ){
            qBack->next = qFront->next;
            qFront = qFront->next;
            tmp->next = nullptr;
            delete tmp;
        } // end if
    }

    void clearQ(){ // clean up
        while (!isEmpty())
            deQueue();
    }
    ~JobQueue(){ // destrutor
        clearQ() ;
    } // end destrutor
    
}; // end JobQueue
#endif //_JobQueue_HPP