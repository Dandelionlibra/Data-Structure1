/** @file Linkedlist.h */
#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <new>
using namespace std;


class Linkedlist{
    typedef struct qN{
        string value ;
        struct qN *next ; // next element
    }listNode;
    
    public:
        Linkedlist(){ // constructor with initialization
            head = NULL ;
            tail = NULL ;
            list = NULL ;
        }
        
        Linkedlist(const Linkedlist& copy){

            for( listNode *temp = copy.head ; temp != NULL ; temp = temp->next ){
                this->ins(temp->value); // put current version to copy version
            }
        }
        bool isEmpty() const ; // decide whether list is empty
        void ins(const string inValue) ; // append one value into list
        void getHead( string& outValue) ; // get the head of list without removal
        void del() ; // remove the head of list
        void del( string& outValue ) ; // get the head of list and remove it
        void clearUp() ; //clear up the rntire list
        void p(){
            int count = 0 ;
            cout <<"Postfix expression: " ;
            if( !isEmpty() ){
                cout << head->value ;
            }
            
            for( listNode *temp = head->next ; !isEmpty()&&temp!=NULL ; temp = temp->next, count++ ){
                cout << ", " << temp->value ;
            }
            cout << endl ;
        }
        ~Linkedlist() ; // destructor
    private:
        listNode *head, *tail ; // only two data members
        listNode *list ;
};


bool Linkedlist::isEmpty() const{
    if( list == NULL )
        return true ;
    return false ;
}

void Linkedlist::ins(const string inValue){
    try{
        if( head == NULL ){
            head = new listNode() ;
            head->value = inValue ;
            head->next = NULL ;
            tail = head ;
            list = head ;
        }
        else{
            for( listNode *temp = head ; temp!=NULL ; temp = temp->next ){
                if(temp->next == NULL){
                    temp->next = new listNode() ;
                    temp = temp->next ;
                    temp->value = inValue ;
                    temp->next = NULL ;
                    tail = temp ;
                    //break ;
                }
            }
        }
    }
    catch (std::bad_alloc& ba){
        std::cerr << endl << "bad_alloc on stack caught:"<< ba.what()<< endl ;
    }
}

void Linkedlist::getHead( string& outValue) {
    if(!isEmpty())
        outValue = head->value ;
}

void Linkedlist::del() {
    if(!isEmpty()){
        list=head ;
        if(list->next != NULL){
            list = list->next ;
            delete head ;
            head = list ;
        }
        else{
            delete list ;
            list = NULL ;
            head = NULL ;
            tail = NULL ;
        }
    }
}

void Linkedlist::del( string& outValue ) {
    outValue="";
    if(!isEmpty()){
        outValue = head->value ;
        if(list->next != NULL){
            list = list->next ;
            delete head ;
            head = list ;
        }
        else{
            delete list ;
            list = NULL ;
            head = NULL ;
            tail = NULL ;
        }
    }
}

void Linkedlist::clearUp() {
    while( list != NULL ){
        del() ;
    }
}

Linkedlist::~Linkedlist() {
    clearUp();
}