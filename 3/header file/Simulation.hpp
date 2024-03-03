#ifndef _Simulation_HPP
#define _Simulation_HPP
#include "JobList.hpp"
#include "JobQueue.hpp"
#include "AnsList.hpp"

class Simulation {
    JobList jobs; // a list of jobs
    AnsList answers; // a set of answers
    //JobQueue<jobType> **allQ; // a set of queues
    JobQueue<jobType> allQ; // a set of queues
    int qNum; // number of queues
    //***********************************/
    //The above are private data members
    //***********************************/

    void delQ(int CPUAmount){ // declaration: delete an old job from a queue
        allQ.deQueue() ;
    }
    void updateQ(int CPUAmount, int i){ // declaration: update each queue
        jobType next ;
        jobs.nextJob(next) ;
        allQ.enQueue(next) ;
    }
    void finishQ(){ // declaration: finish the remaining jobs in queues

    }

public:
    Simulation(JobList aList, int N): jobs(aList), qNum(N){ // copy constructor
        string a ;
        cout <<endl << "The simulation is running..." << endl ;
        /*while( !jobs.isEmpty() ){
            updateQ(1, 2) ;
            delQ(1) ;
        }*/

        finishQ() ;

        answers.showAll(a) ;
        answers.putAll( aList.getfileID(), a ) ;
    } // end constructor

    ~Simulation(){ // end destructor

    } // end destructor

    void SQF(); // declaration: shortest queue first
}; //end Simulation

#endif // _Simulation_HPP





