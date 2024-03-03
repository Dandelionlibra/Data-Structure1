//11127138, 林雨臻
#include <stdio.h>
#include <string> // string class
#include <cstdlib> // system, atoi
#include <iostream>
#include <new>
#define MAX_LEN 255 // maximum string length
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


bool isExp(string& infix); // check the validity of each symbol
bool isBalanced(const string infix); // check the validity of balanced parenthesis
bool isLegal(const string infix); // check whether it is a legal expression
void str2list(Linkedlist& infixList, const string infix); // parse a string into a linked list
void infix2postfix(Linkedlist& infixList, Linkedlist& postfix); // transform infix into postfix
string delspace(const string infix);

string delspace(const string infix){
	string infixnonspace = "" ;
	for( int i = 0 ; i<infix.size() ; i++ ){
		if( infix[i] != ' ' ){
			infixnonspace = infixnonspace + infix[i] ;
		}
	}
	return infixnonspace ;
}
bool isBalanced(const string infix){
	Stack parentheses ;
	int parenthesesOfLeftFirst = 1 ;
	for( int i = 0 ; i<infix.size() ; i++ ){
		if( infix[i] == '(' ){
			parentheses.push( infix[i] ) ;
		}
		else if ( infix[i] == ')' ){
			if( parentheses.isEmpty() ){
				cout << "Error 2: there is one extra close parenthesis." << endl ;
				return false ;
			}
			parentheses.pop() ;
		}

	}

	if( !parentheses.isEmpty() ) {// there still have extra parenthesis in the stack
		cout << "Error 2: there is one extra open parenthesis." << endl ;
		parentheses.~Stack() ;
		return false ;
	}
	return true ;
}
bool isLegal(const string infix){
	bool operators = true ;
	bool operand = true ;
	bool parentheses = true ;
	char infixchar = infix[0] ;

	if( infix.size() == 0 ){
		cout << "Error 3: there is one extra operator." << endl ;
        return false ;
	}
    if( infixchar == '+' || infixchar == '-' || infixchar == '*' || infixchar == '/' || infixchar == ')' ){
		cout << "Error 3: there is one extra operator." << endl ;
        return false ;
    }
    else if ( infix[infix.size()-1] == '+' || infix[infix.size()-1] == '-' || infix[infix.size()-1] == '*' || infix[infix.size()-1] == '/' ){
		cout << "Error 3: there is one extra operator." << endl ;
        return false ;
    }



	for( int i = 1 ; i<infix.size() ; i++ ) {
		if( infix.size() == 0 ){
			cout << "Error 3: there is one extra operator." << endl ;
		}
		if( ( infixchar == '+' || infixchar == '-' || infixchar == '*' || infixchar == '/') && ( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') ){
			cout << "Error 3: there is one extra operator." << endl ;
			return false ;
		}
		if( ( infixchar == '+' || infixchar == '-' || infixchar == '*' || infixchar == '/') && ( infix[i] == ')' ) ){ // (45-)
			cout << "Error 3: it is not infix in the parentheses." << endl ;
			return false ;
		}
		if( ( infixchar == '(' ) && ( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') ){ // (+64)
			cout << "Error 3: it is not infix in the parentheses." << endl ;
			return false ;
		}
		if( infixchar == '(' && infix[i] == ')' ){ // ()
			cout << "Error 3: it is not infix in the parentheses." << endl ;
			return false ;
		}
		if( !( infixchar == '(' || infixchar == '+' || infixchar == '-' || infixchar == '*' || infixchar == '/') && ( infix[i] == '(' ) ){ // -45(45)
			cout << "Error 3: there is one extra operand." << endl ;
			return false ;
		}
		if( ( infixchar == ')' ) && !( infix[i] == ')' || infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') ){ // (64)45+
			cout << "Error 3: there is one extra operand." << endl ;
			return false ;
		}

		if( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' ){
			operators = false ;
		}

		infixchar = infix[i] ;
	}

	return true ;
}
bool isExp(string& infix){
	for( int i = 0 ; i<infix.size(); i++ ){
		if( infix[i]!='0' && infix[i]!='1' && infix[i]!='2' && infix[i]!='3' && infix[i]!='4' && infix[i]!='5' && infix[i]!='6' && infix[i]!='7' && infix[i]!='8' && infix[i]!='9' ){
			if( infix[i]!=' ' && infix[i]!='/' &&  infix[i]!='+' && infix[i]!='-' && infix[i]!='*' && infix[i]!='(' && infix[i]!=')' ){
				cout<< "Error 1: "<< infix[i] <<" is not a legitimate character."<<endl ;
				return false ;
			}
		}
	}
	return true ;
}
void str2list(Linkedlist& infixList, const string infix){
	bool endnum = false ;
	string cur = "" ;
	for( int i = 0 ; i<infix.size() ; i++ ){
		if( endnum ){
			infixList.ins( cur ) ;
			cur = "" ;
			endnum = false ;
		}
		if ( infix[i] != '0' && infix[i] != '1' && infix[i] != '2' && infix[i] != '3' && infix[i] != '4' && infix[i] != '5' && infix[i] != '6' && infix[i] != '7' && infix[i] != '8' && infix[i] != '9' ){
			cur = cur + infix[i] ;
			infixList.ins( cur ) ;
			cur = "" ;
		}
		else{
			cur = cur + infix[i] ;
			if( i+1 < infix.size() ){
				if ( infix[i+1] != '0' && infix[i+1] != '1' && infix[i+1] != '2' && infix[i+1] != '3' && infix[i+1] != '4' && infix[i+1] != '5' && infix[i+1] != '6' && infix[i+1] != '7' && infix[i+1] != '8' && infix[i+1] != '9' )
					endnum = true ;
			}
			else if ( i+1 == infix.size() ){
				endnum = false ;
				infixList.ins( cur ) ;
				cur = "" ;
			}
		}

	}
}
void infix2postfix(Linkedlist& infixList, Linkedlist& postfix){
	Stack operatorsBox ;
    string firsttemp = "" ;
	string temp ;
    char operatortemp;

	int list[50] = {0} ;
	list['+'] = 1, list['-'] = 1, list['*'] = 2, list['/'] = 2 ;

    infixList.del(firsttemp);
    while( firsttemp.compare("(")==0 ){
        operatorsBox.push('(');
        infixList.del(firsttemp);
    }
    postfix.ins(firsttemp);

    do{
        infixList.del(temp);

        if( temp.compare(")")==0 ){
            operatorsBox.getTop(operatortemp) ;
            while( !operatorsBox.isEmpty() && operatortemp!='(' ){
                string operator_str ;
                operatorsBox.pop(operatortemp) ;
                operator_str.append(1, operatortemp) ; // turn char to string
                postfix.ins(operator_str) ;
                operatorsBox.getTop(operatortemp) ;
            }
            operatorsBox.pop() ;
        }

        else if( temp[0] == '0' || temp[0] == '1' || temp[0] == '2' || temp[0] == '3' || temp[0] == '4' || temp[0] == '5' || temp[0] == '6' || temp[0] == '7' || temp[0] == '8' || temp[0] == '9' ){
            postfix.ins(temp) ;
        }
        else if( temp.compare("+")==0 || temp.compare("-")==0 || temp.compare("*")==0 || temp.compare("/")==0 || temp.compare("(")==0 ){
            char te ;
            string te_str ;
            operatorsBox.getTop( te ) ;
            te_str.append(1, te) ;

			while( !operatorsBox.isEmpty() && temp[0]!='(' && list[temp[0]]<=list[te] ){
                postfix.ins(te_str) ;
                operatorsBox.pop() ;
            	operatorsBox.getTop( te ) ;
				te_str = "";
            	te_str.append(1, te) ;
			}
			operatorsBox.push(temp[0]);

        }

        
        firsttemp = temp ;
    }
	while( !infixList.isEmpty() ) ;

    while( !operatorsBox.isEmpty() ) {
        char t ;
        string t_str ;
        operatorsBox.pop(t) ;
        t_str.append(1, t) ;
        if( t!='(' ){
            postfix.ins(t_str) ;
        }
    }/*
    string a ="" ;
    postfix.getHead( a ) ;
    if( a.compare("(") == 0 ){
        postfix.del() ;
    }*/

}


int main() {
	int command = 0 ;

	do {
        string infixS ;
		cout<< endl << "* Arithmetic Expression Evaluator *" ;
		cout<< endl << "* 0. QUIT                         *" ;
		cout<< endl << "* 1. Infix2postfix Transformation *" ;
		//cout<< endl << "* 2. Infix2prefix Transformation  *" ;
		cout<< endl << "***********************************" ;
		cout<< endl << "Input a choice(0, 1): " ;

		cin>> command ;
		cin.ignore(MAX_LEN,'\n');
		switch(command){
			case 0 : break ;
			case 1 : cout << endl << "Input an infix expression: " ;
				getline(cin, infixS) ;
				infixS = delspace(infixS) ;

				if ( isExp(infixS) && isBalanced(infixS) && isLegal(infixS) ) {
					cout << "It is a legitimate infix expression." << endl ;
					Linkedlist infixList ;
                    Linkedlist postfix ;
                    str2list(infixList, infixS) ;
                    infix2postfix(infixList, postfix) ;
                    postfix.p() ;
				}

				break ;
			default : cout << endl << "Command does not exist!" << endl ;
		}

	}while( command != 0 ) ;

	system("pause") ;
	return 0 ;
}

