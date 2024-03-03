// 11127132 羅海綺
// 11127138 林雨臻
#include <cstdlib>  // atoi, system
#include <fstream>  // open, is_open
#include <iomanip>  // setw, setprecision
#include <iostream> // cout, endl, fixed
#include <string>   // string
#include <vector>   // vector
#include <math.h>
using namespace std;

struct pokemonType{
    string rawR; // raw data of one record
    int no; // pokemon number
    string name; // pokemon name
    string tp1; // 1st type
    int total; // total sum
    int hp; // health point
    int attack;
    int defense;
};

template <typename T>
class BSTree {
    struct nodeType {
        int key;            // search key
        vector<int> idx;          // data no
        nodeType *lchild; // left child
        nodeType *rchild; // right child
    };
    nodeType *root, *tmp = root; // root node of BST
    int visit;                   // number of visited nodes

    void insertNode(nodeType *&node, pokemonType value) { // insert a node by recursion
        if (node == nullptr) {
            node = new nodeType();
            node->key = value.hp;

            node->idx.push_back(value.no);
            //node->idx = value.no;

            node->lchild = nullptr;
            node->rchild = nullptr;
            
        }
        else {
            if (value.hp < node->key) // if key bigger than value
                insertNode(node->lchild, value);
            else if(value.hp > node->key)
                insertNode(node->rchild, value);
            else if( value.hp == node->key ){
                node->idx.push_back(value.no);
            }

        }
    } // end insertNode

    int getH(nodeType *bst, int total) const { // calculate the tree by recursion
        if (bst == nullptr)
            return 0;
        else {
            int a = getH(bst->lchild, total);
            int b = getH(bst->rchild, total);
            if (a > b) // which is higher
                return a + 1;
            else
                return b + 1;
        }
    } // end getH

    void clearBST(nodeType *&del) { // clear up the entire tree by recursion
        if (del == nullptr) {
            delete del;
            del = nullptr;
        } else {
            clearBST(del->lchild);
            clearBST(del->rchild);
            delete del;
        }
    } // end clearBST

public:
    vector<int> output;
    BSTree() : root(nullptr), visit(0) {} // constructor of an empty tree
    bool isEmpty() {                      // examine whether it is empty or not
        return root == nullptr;
    } // end isEmpty

    void add(pokemonType value) { // insert a node into BST on any type
        tmp = root;
        insertNode(root, value);
    } //  end add

    void showH(int n) const { // show the tree height
        nodeType *node = root;
        int num = getH(node, 0);
        cout << "HP tree height = " << num << '\n';
        node = nullptr;
    } // end showH

    vector<pair<pokemonType,int> > findLeft( vector<pokemonType> pSet ){
        vector<pair<pokemonType,int>> tmp ;
        pair<pokemonType,int> a ;
        for( nodeType *t = root ; t!=nullptr ; t = t->lchild ){
            //cout << "\033[33;1mHP heap height = \033[0m \n";


            for( int i = 0 ; t->lchild==nullptr && i < t->idx.size() ; i++ ){
                a.first.no = t->idx.at(i);
                for( int j = 0 ; j<pSet.size() ; j++ ){
                    if( a.first.no == pSet.at(j).no ){
                        a.first = pSet.at(j) ;
                        a.second = j ;
                    }
                }
                tmp.push_back(a);
            }
        }

        return tmp;
    }

    vector<pair<pokemonType,int> > findRight( vector<pokemonType> pSet ){
        vector<pair<pokemonType,int>> tmp ;
        pair<pokemonType,int> a ;
        for( nodeType *t = root ; t!=nullptr ; t = t->rchild ){
            for( int i = 0 ; t->rchild==nullptr && i < t->idx.size() ; i++ ){
                a.first.no = t->idx.at(i);
                for( int j = 0 ; j<pSet.size() ; j++ ){
                    if( a.first.no == pSet.at(j).no ){
                        a.first = pSet.at(j) ;
                        a.second = j ;
                    }
                }
                tmp.push_back(a);
            }
        }
        

        return tmp;
    }



    void clearUp() { // cut off the entire tree
        clearBST(root);
        visit = 0;
        root = nullptr; // have to initail!!!!
    } // end clearUp

    ~BSTree() { clearUp(); } // destructor
};  // end BSTree


class Heap{
    vector<pokemonType> item;
    pokemonType rootItem;
    int size; // number of heap items

    void clearHeap(){
        size = 0;
        item.clear();
    }
public:
    Heap() : size(0) {} // constructor of an empty tree

    bool heapIsEmpty(){
        return (item.size()==0);
    }

    void heapInsert( vector<pokemonType> pSet ){
        item = pSet; // put new item at the end of heap
        size = item.size();
    }

    void sortInsert(){
        for( int i = item.size()/2 ; i >= 0 ; i-- )
            heapRebuild(i);
    }

    void heapDelete(vector<pokemonType> &item){
        if(heapIsEmpty()){
            cout << "Heap empty\n";
            return;
        }
            
        rootItem = item[0];
        size--;
        item[0]=item[size];
        heapRebuild(0);

    }

    void heapRebuild(int root){
        int child = 2*root + 1; // find the left child of root
        if( child < size ){ // root have child
            int rightChild = child + 1;
            if( (rightChild < size) && (item[rightChild].hp > item[child].hp) ) // root have rightChild
                child = rightChild ; // the index of the larger child
            if( item[root].hp < item[child].hp ){
                pokemonType temp = item[root];
                item[root] = item[child];
                item[child] = temp;
                heapRebuild(child);
            }

        }
    }

    void showheap(){
        cout << left << "\t#\t" << setw(32) << "Name" << "Type 1\t\t" << "HP" << "\t" << "Attack" << "\t" << "Defense\n";
        for( int i = 0 ; i < item.size() ; i++ ){
            cout << right << "[" << setw(2) << i << "]\t" ;
            cout << left << item.at(i).no << "\t" << setw(24) << item.at(i).name << "\t" << setw(16) 
                 << item.at(i).tp1 << item.at(i).hp << "\t" << item.at(i).attack << "\t" << item.at(i).defense << "\n" ;
        }
    }

    void showheight(){
        int tmp = item.size() ;
        int height = 0;
        while( tmp > 0 ){
            tmp = tmp - pow(2, height);
            height++;
        }

       cout << "HP heap height = " << height << "\n";

    }
    
    void showleftmost(){
        int increment = 2 ;
        int idx = 0 ;
        for( int i = 0 ; i < item.size() ; i++ ){
            if( idx + pow(increment,i) < item.size() )
                idx = idx + pow(increment, i) ;
            else
                break;
            
        }

        cout << "Leftmost node:\n" ;
        cout << left << "\t#\t" << setw(32) << "Name" << "Type 1\t\t" << "HP" << "\t" << "Attack" << "\t" << "Defense\n";
        cout << left << "[" << idx << "]\t" << item.at(idx).no << "\t" << setw(32) << item.at(idx).name << setw(16)
             << item.at(idx).tp1 << item.at(idx).hp << "\t" << item.at(idx).attack << "\t" << item.at(idx).defense << "\n" ;


    }
    void showbottom(){
        int idx = item.size()-1;
        cout << "Bottom:\n";
        cout << left << "\t#\t" << setw(32) << "Name" << "Type 1\t\t" << "HP" << "\t" << "Attack" << "\t" << "Defense\n" ;
        cout << right << "[" << idx << "]\t" << left << item.at(idx).no << "\t" << setw(32) << item.at(idx).name << setw(16) 
             << item.at(idx).tp1 << item.at(idx).hp << "\t" << item.at(idx).attack << "\t" << item.at(idx).defense << "\n" ;

    }
    void clearUp() { // cut off the entire tree
        clearHeap();
    } // end clearUp

    ~Heap() { clearUp(); } // destructor
}; // end Heap

class pokemonList{
    vector<pokemonType> pSet; // set of data records
    vector<pair<pokemonType,int> > Leftmost;
    vector<pair<pokemonType,int> > Rightmost;
    string fileID; // number to form a file name
    bool fileexist ;
    bool heapexist;
    BSTree<string> aBST; // a binary search tree
    Heap aHeap;

    void show(int i, vector<pokemonType> p){ // display one record on screen 
        cout << right << "[" << setw(2) <<i+1<< "]\t" << left << p.at(i).no << "\t" << setw(24) << p[i].name << "\t" 
             << setw(16) << p[i].tp1 << p[i].hp << "\t" << p[i].attack << "\t" << p[i].defense << "\n" ;
    }

    public:
    pokemonList(): fileID(""),fileexist(false),heapexist(false){ clearUp(); } // constructor: do nothing
    bool isEmpty(){ // check if there is nothing
        if (pSet.size() == 0)
            return true;
        return false;
    }
    bool fileExist(){
        return fileexist;
    }
    
    bool readFile() { // declaration: read all from a inputfile
        fstream inFile;
        string fileName;

        this->clearUp();
        cout << "\nInput a file number [0: quit]: ";
        cin >> this->fileID;
        if( fileID == "0" )
            return false;

        fileName = "input" + fileID + ".txt";
        inFile.open(fileName.c_str(), fstream::in);
        if (!inFile.is_open()) { // confirm existence or not
            cout << "\n### " << fileName << " does not exist! ###\n";
            return false; // end
        } else {
            fileexist = true;
            char cstr[255];
            int fNo, pre, pos;
            inFile.getline(cstr, 255, '\n'); // skip the 1st header line
            while (inFile.getline(cstr, 255, '\n')) {
                pokemonType oneR; // one data record
                string buf, cut; // transform c-string into c++ string

                fNo = 0;
                pre = 0;
                buf.assign(cstr);
                do {
                    pos = buf.find_first_of('\t', pre);
                    cut = buf.substr(pre, pos - pre);
                    switch (++fNo) {
                        case 1:
                            oneR.no = atoi(cut.c_str()); // get the school name
                            break;
                        case 2:
                            oneR.name = cut; // get the school name
                            break;
                        case 3:
                            oneR.tp1 = cut; // get the department name
                            break;
                        case 5:
                            oneR.total = atoi(cut.c_str()); // get either day or night
                            break;
                        case 6:
                            oneR.hp = atoi(cut.c_str()); // get graduate or undergraduate
                            break;
                        case 7:
                            cut = sortinput(cut);
                            oneR.attack = atoi(cut.c_str()); // get the number of students
                            break;
                        case 8:
                            cut = sortinput(cut);
                            oneR.defense = atoi(cut.c_str()); // get the number of professors
                            break;
                        default:
                            break;
                    }                              // end switch
                    pre = ++pos;                   // move to the next field
                } while ((pos > 0) && (fNo < 10)); // continue if there are still fields to be read
                this->pSet.push_back(oneR);        // save one record into the school list
                //this->allRidx.push_back(oneR);
            } // end outer-while
            inFile.close();

        } // end else

        if (!this->pSet.size()) {
            cout << "\n### Get nothing from the file " << fileName << "!###\n";
            return false;
        } // end if

        return true;
    } // end readFile
    string sortinput(string cut){
        string a = "";
        for( int i = 0 ; i<cut.size() ; i++ ){
            if (cut[i] != '\"' && cut[i] != ',')
                a = a + cut[i];
        }
        return a;
    }
    void showAll(){ // display all the records in screen
        cout << left << "\t#\t" << setw(32) << "Name" << "Type 1\t\t" << "HP" << "\t" << "Attack" << "\t" << "Defense\n";
        for(int i = 0 ; i < pSet.size() ; i++){
            show(i, pSet) ;
        }
    }

    void buildBST(){ // build BST
        for (int i = 0; i < pSet.size(); i++) {
            aBST.add(pSet.at(i));
        }

        Leftmost = aBST.findLeft(pSet);
        Rightmost = aBST.findRight(pSet);

    }
    void buildHeap(){
        if(!heapexist){
            //cout << "\033[31;1mbuildHeap: \033[0m \n";
            aHeap.heapInsert(pSet);
            aHeap.sortInsert();
            heapexist = true;
        }

        //cout << "\033[31;1mshowHeap: \033[0m \n";
        aHeap.showheap();
        aHeap.showheight();
        aHeap.showleftmost();
        aHeap.showbottom();
    }

    void printLeftAndRight(){
        cout << left << "Leftmost node:\n" ;
        for( int i = 0 ; i < Leftmost.size() ; i++ ){
            cout << right << "[" << Leftmost.at(i).second+1<< "]\t" << left << Leftmost.at(i).first.no << "\t" 
                 << setw(32) << Leftmost.at(i).first.name << setw(16) << Leftmost.at(i).first.tp1 << Leftmost.at(i).first.hp 
                 << "\t" << Leftmost.at(i).first.attack << "\t" << Leftmost.at(i).first.defense << "\n" ;
        }

        cout << left << "Rightmost node:\n" ;
        for( int i = 0 ; i < Rightmost.size() ; i++ ){
            cout << right << "[" << Rightmost.at(i).second+1<< "]\t" << left << Rightmost.at(i).first.no << "\t" 
                 << setw(32) << Rightmost.at(i).first.name << setw(16) << Rightmost.at(i).first.tp1 << Rightmost.at(i).first.hp 
                 << "\t" << Rightmost.at(i).first.attack << "\t" << Rightmost.at(i).first.defense << "\n" ;
        }
    
    }
    
    void printHeight() { // print the tree height
        aBST.showH(0);
    } // end printHeight

    void clearUp(){
        fileexist = false;
        heapexist = false;

        fileID.clear();
        pSet.clear();
        Leftmost.clear();
        Rightmost.clear();
        aBST.clearUp();
        aHeap.clearUp();

    } // end clearUp()

    ~pokemonList(){ clearUp(); } // desturctor: destory the object
}; // end pokemonList

int main() {
    pokemonList pokemon;
    int command = -1;
    bool isEnd = false;
    string fileName, input;
    while (!isEnd) {
        cout << "\n***** Pokemon Tree and Heap *****";
        cout << "\n* 0. QUIT                       *";
        cout << "\n* 1. Read a file to build BST   *";
        cout << "\n* 2. Transform it into Max Heap *";
        cout << "\n*********************************";
        cout << "\nInput a choice(0, 1, 2): ";
        cin >> command;
        switch (command) {
            case 0:
                isEnd = true;
                break;
            case 1:
                if (pokemon.readFile()) { // if file exist
                    pokemon.buildBST();
                    
                    pokemon.showAll();
                    pokemon.printHeight();
                    pokemon.printLeftAndRight();
                }
                break;
            case 2:
                if (pokemon.fileExist() == false)
                    cout << "\n----- Execute Mission 1 first! -----\n";
                else {
                    pokemon.buildHeap();
                }
                break;
            
            default:
                cout << "\nCommand does not exist!\n" << endl;
        } // end switch case
    } // end while
} // end main()