/** @file stack.h */
#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <new>
using namespace std;


class Stack{
    typedef struct sN{ // structure of each element in stack
        char value ;
        struct sN *next ; // next element

    }stackNode;
    
    public:
        Stack(){
            topPtr = NULL ;
            stack = NULL ;
        } // constructor with initialization
        bool isEmpty() const; // decide whether stack is empty
        void push(const char inValue); // add one element into stack
        void getTop( char& outValue ); // get the top of stack without removal
        char getTop() ;
        void pop(); // remove the top of stack
        void pop( char& outValue ); // get the top of stack and remove it
        void p(){
            int count = 0 ;
            cout << endl ;
            for( sN *temp = stack ; temp!=NULL ; temp = temp->next, count++ ){
                cout <<"...."<< temp->value << " " ;
            }
        }
        ~Stack(); // destructor
    private:
        stackNode *topPtr ; // only one data member
        stackNode *stack ;

}; // end Stack class


    //Stack::Stack():topPtr(NULL){}
bool Stack::isEmpty() const{
    if( stack==NULL )
        return true ;
    
    return false ;
}

void Stack::push(const char inValue){
    try{
        if( stack == NULL ){
            topPtr = new stackNode ;
            topPtr->value = inValue ;
            topPtr->next = NULL ;
            stack = topPtr ;
        }
        else{
            stackNode *temp ;
            for( temp = stack ; temp!=NULL ; temp = temp->next ){
                if( temp->next == NULL ){
                    temp->next = new stackNode ;
                    temp = temp->next ;
                    temp->value = inValue ;
                    temp->next = NULL ;
                    topPtr = temp ; // reset topPtr become the newest one
                    
                    
                    break ;
                }
            }


        }
    }
    catch( bad_alloc& ba ){
        cerr << endl << "bad_alloc on stack caught:"<< ba.what() << endl ;
    }
}

void Stack::getTop( char& outValue ){
    for( sN *temp = stack ; temp!=NULL ; temp = temp->next ){
        outValue = temp->value ;
    }
}

char Stack::getTop(){
    char outValue ;
    for( sN *temp = stack ; temp!=NULL ; temp = temp->next ){
        outValue = temp->value ;
    }
    return outValue ;
}



void Stack::pop(){
    stackNode *t = stack ;
    if(stack==NULL)
        return ;
    if( stack->next == NULL){
        delete topPtr ;
        stack = NULL ;
        topPtr = NULL ;
    }
    else if( stack->next->next == NULL ){
        delete topPtr ;
        stack->next = NULL ;
        topPtr = stack ;
    }
    else{
        for( stackNode *temp = stack ; temp!=NULL ; temp = temp->next ){
            if(temp->next == NULL){
                delete temp ;
                temp = NULL ;
                t->next = NULL ;
                topPtr = t ;
                temp = t ;
                break ;
            }
            else{
                t = temp ;
            }
        }

    }
    
}

void Stack::pop( char& outValue ){
    stackNode *t = stack ;
    if(stack==NULL)
        return ;
    if( stack->next == NULL){
        outValue = topPtr->value ;
        delete topPtr ;
        stack = NULL ;
        topPtr = NULL ;
    }
    else if( stack->next->next == NULL ){
        outValue = topPtr->value ;
        delete topPtr ;
        stack->next = NULL ;
        topPtr = stack ;
    }
    else{
        for( stackNode *temp = stack ; temp!=NULL ; temp = temp->next ){
            
            if(temp->next == NULL){
                outValue = temp->value ;
                delete temp ;
                temp = NULL ;
                t->next = NULL ;
                topPtr = t ;
                temp = t ;
                //break ;
            }
            else{
                t = temp ;
            }
        }

    }
}

Stack::~Stack(){
    while(!isEmpty())
        pop();
}
