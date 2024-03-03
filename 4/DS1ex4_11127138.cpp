// 11127132 羅海綺
// 11127138 林雨臻
#include <cstdlib>  // atoi, system
#include <fstream>  // open, is_open
#include <iomanip>  // setw, setprecision
#include <iostream> // cout, endl, fixed
#include <string>   // string
#include <vector>   // vector
using namespace std;

struct schoolType {
    string sname; // school name
    string dname; // department name
    string type;  // day or night
    string level; // graduate or undergraduate
    int nstud;    // num of students
    int nprof;    // num of professors
    int ngrad;    // num of graduates
};

template <typename T>
class BSTree {
    struct nodeType {
        T key;            // search key
        int idx;          // data index
        nodeType *lchild; // left child
        nodeType *rchild; // right child
    };
    nodeType *root, *tmp = root; // root node of BST
    int visit;                   // number of visited nodes
    

    void insertNode(nodeType *&node, T value) { // insert a node by recursion
        if (node == nullptr) {
            node = new nodeType();
            node->key = value;
            node->idx = visit;
            node->lchild = nullptr;
            node->rchild = nullptr;
            visit++;
        } else {
            if (value < node->key) // if key bigger than value
                insertNode(node->lchild, value);
            else
                insertNode(node->rchild, value);
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

    void findNode(nodeType *&subtree, int goal) { // check the right nodes
        if (subtree == nullptr)
            return;
        else if (goal <= subtree->key) {
            output.push_back(subtree->idx);
            findNode(subtree->lchild, goal);
            findNode(subtree->rchild, goal);
        } else
            findNode(subtree->rchild, goal);
    } // end findNode

    void findNode(nodeType *&subtree, string goal) { // check the right nodes
        if (subtree == nullptr)
            return;
        else if (goal <= subtree->key) {
            if (goal == subtree->key) output.push_back(subtree->idx);

            findNode(subtree->lchild, goal);
            findNode(subtree->rchild, goal);
        } else
            findNode(subtree->rchild, goal);
    } // end findNode

    nodeType *deleteNode(nodeType *node, T search) { // delete a given node
        if (node == nullptr) // current node is null, return
            return nullptr;

        if (search < node->key) { // find the node which need to del in left subtree
            node->lchild = deleteNode(node->lchild, search);
        } 
        else if (search > node->key) { // find the node which need to del in right subtree
            node->rchild = deleteNode(node->rchild, search);
        } 
        else { // already find
            if (node->lchild == nullptr) { // Case 2: only right subtree
                nodeType *temp = node->rchild;
                delete node;
                return temp;
            } else if (node->rchild == nullptr) { // Case 2: only left subtree
                nodeType *temp = node->lchild;
                delete node;
                return temp;
            } else { // Case 3: have two subtree
                     // find the smallest node in left subtree
                nodeType *min = node->rchild;
                while (min->lchild != nullptr)
                    min = min->lchild;

                node->idx = min->idx; // replace the current node to the min
                node->key = min->key;
                // delete the smallest node in right subtree
                node->rchild = deleteNode(node->rchild, min->key); 
            }
        }

        return node;
    } // end deleteNode

    nodeType *delG(nodeType *node, T search, string school, vector<schoolType> allRidx) { // delete a given node
        if (node == nullptr) // current node is null, return
            return nullptr;

        if (search < node->key) { // find the node which need to del in left subtree
            node->lchild = delG(node->lchild, search, school, allRidx);
        } 
        else if (search > node->key) { // find the node which need to del in right subtree
            node->rchild = delG(node->rchild, search, school, allRidx);
        }
        else if (allRidx.at(node->idx).sname != school){ // check the school name is correct
            node->rchild = delG(node->rchild, search, school, allRidx);
        }
        else { // already find
            if (node->lchild == nullptr) { // Case 2: only right subtree
                nodeType *temp = node->rchild;
                delete node;
                return temp;
            } else if (node->rchild == nullptr) { // Case 2: only left subtree
                nodeType *temp = node->lchild;
                delete node;
                return temp;
            } else { // Case 3: have two subtree
                     // find the smallest node in left subtree
                nodeType *min = node->rchild;
                while (min->lchild != nullptr)
                    min = min->lchild;

                node->idx = min->idx; // replace the current node to the min
                node->key = min->key;
                // delete the smallest node in right subtree
                node->rchild = delG(node->rchild, min->key, allRidx.at(node->idx).sname, allRidx); 
            }
        }

        return node;
    } // end delG

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

    void add(T value) { // insert a node into BST on any type
        tmp = root;
        insertNode(root, value);
    } //  end add

    void showH(int n) const { // show the tree of graduates height
        nodeType *node = root;
        int num = getH(node, 0);
        cout << "Tree height {Number of graduates} = " << num << '\n';
        node = nullptr;
    } // end showH

    void showH(string name) const { // show the tree of school name height
        nodeType *node = root;
        int num = getH(node, 0);
        cout << "Tree height {School name} = " << num << '\n';
        node = nullptr;
    } // end showH

    void findMatch(T goal) { // find the nodes match the goal
        findNode(root, goal);
    } // end findMatch

    void findDel(T goal) { // find the nodes match the goal
        root = deleteNode(root, goal);
    } // end findMatch

    void deleteGra( int graduate, string school, vector<schoolType> allRidx ){
        root = delG(root, graduate, school, allRidx);
    } // end deleteGra

    void clearUp() { // cut off the entire tree
        clearBST(root);
        visit = 0;
        root = nullptr; // have to initail!!!!
    } // end clearUp

    ~BSTree() { clearUp(); } // destructor
};  // end BSTree

class SchoolList {
    vector<schoolType> allR, records;
    vector<schoolType> allRidx;
    string fileID;
    BSTree<int> graduate;
    BSTree<string> name;
    bool fileexist = false ;
    void reset() { // initial set up
        fileexist = false;
        this->allR.clear();
        this->allRidx.clear();
        this->fileID.clear();
        this->graduate.clearUp();
        this->name.clearUp(); // "this" can be moved
    } // end reset

   public:
   
    SchoolList() { reset(); }  // construtor
    ~SchoolList() { reset(); } // destrutor

    bool fileExist(){
        return fileexist;
    }

    bool isEmpty() { // examine whether it is empty or not
        if (allR.size() == 0)
            return true;
        else
            return false;
    } // end isEmpty

    void createTree() { // create two trees
        for (int i = 0; i < allR.size(); i++) {
            graduate.add(allR.at(i).ngrad);
            name.add(allR.at(i).sname);
        }
    } // end createTree

    void printHeight() { // print the tree height
        name.showH("0");
        graduate.showH(0);
    } // end printHeight

    void printOutput(vector<int> o) { // print the result
        cout << "Search results:\n";
        for (int i = 0; i < o.size(); i++) {
            cout << "[" << i + 1 << "]"
                 << "\t" << allRidx.at(o[i]).sname << "\t" << allRidx.at(o[i]).dname << "\t" << allRidx.at(o[i]).type
                 << "\t" << allRidx.at(o[i]).level << "\t" << allRidx.at(o[i]).nstud << "\t" << allRidx.at(o[i]).nprof
                 << "\t" << allRidx.at(o[i]).ngrad << '\n';
        }
    } // end printOutput

    void printDelOutput(vector<schoolType> o) { // print the result
        cout << "Deleted records:\n";
        for (int i = 0; i < o.size(); i++) {
            cout << "[" << i + 1 << "]"
                 << "\t" << o.at(i).sname << "\t" << o.at(i).dname << "\t" << o.at(i).type
                 << "\t" << o.at(i).level << "\t" << o.at(i).nstud << "\t" << o.at(i).nprof
                 << "\t" << o.at(i).ngrad << '\n';
        }
    } // end printOutput

    void findG(string dec) { // find the graduates which amount bigger than input
        if (!(dec[0] <= '9' && dec[0] >= '0')) {
            cout << "### the input string " << dec << " is not a decimal number! ###\n";
            return;
        } else {
            graduate.findMatch(atoi(dec.c_str()));
            if (graduate.output.size() == 0)
                cout << "There is no match!\n";
            else
                printOutput(graduate.output);
        }

        graduate.output.clear(); // clear the vector
    } // end findG

    void findS(string school) { // find the school which is same as input
        name.findMatch(school);
        if (name.output.size() == 0)
            cout << "There is no match!\n";
        else
            printOutput(name.output);

        name.output.clear(); // clear the vector
    } // end findS

    void deleteS(string school) { // find the school which is same as input
        for( int i = 0; i < allR.size(); i++ ){
            if( school == allR.at(i).sname ){
                name.findDel(school);
                graduate.deleteGra(allR.at(i).ngrad, allR.at(i).sname, allRidx);
                records.push_back(allR.at(i));
                allR.erase( allR.begin()+i );
                i--;
            }
        } // end for

        if ( records.size() == 0)
            cout << "There is no match!\n";
        else
            printDelOutput(records);
        
        printHeight();
        records.clear(); // clear the vector
    } // end deleteS

    bool readFile() { // declaration: read all from a inputfile
        fstream inFile;
        string fileName;

        this->reset();
        cout << "\nInput a file number: ";
        cin >> this->fileID;
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
            inFile.getline(cstr, 255, '\n'); // skip the 2nd header line
            inFile.getline(cstr, 255, '\n'); // skip the list of column names
            while (inFile.getline(cstr, 255, '\n')) {
                schoolType oneR; // one data record
                string buf, cut; // transform c-string into c++ string

                fNo = 0;
                pre = 0;
                buf.assign(cstr);
                do {
                    pos = buf.find_first_of('\t', pre);
                    cut = buf.substr(pre, pos - pre);
                    switch (++fNo) {
                        case 2:
                            oneR.sname = cut; // get the school name
                            break;
                        case 4:
                            oneR.dname = cut; // get the department name
                            break;
                        case 5:
                            oneR.type = cut; // get either day or night
                            break;
                        case 6:
                            oneR.level = cut; // get graduate or undergraduate
                            break;
                        case 7:
                            cut = sortinput(cut);
                            oneR.nstud = atoi(cut.c_str()); // get the number of students
                            break;
                        case 8:
                            cut = sortinput(cut);
                            oneR.nprof = atoi(cut.c_str()); // get the number of professors
                            break;
                        case 9:
                            cut = sortinput(cut);
                            oneR.ngrad = atoi(cut.c_str()); // get the number of graduates
                            break;
                        default:
                            break;
                    }                              // end switch
                    pre = ++pos;                   // move to the next field
                } while ((pos > 0) && (fNo < 10)); // continue if there are still fields to be read
                this->allR.push_back(oneR);        // save one record into the school list
                this->allRidx.push_back(oneR);
            } // end outer-while
            inFile.close();

        } // end else

        if (!this->allR.size()) {
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

        // cout << a << endl;
        //system("pause");
        return a;
    }
};    // end class SchoolList

int main() {
    SchoolList slist;
    int command = -1;
    bool isEnd = false;
    string fileName, input;
    while (!isEnd) {
        cout << "\n*** University Graduate Information System ***";
        cout << "\n* 0. Quit                                    *";
        cout << "\n* 1. Create Two Binary Search Trees          *";
        cout << "\n* 2. Search by Number of Graduates           *";
        cout << "\n* 3. Search by School Name                   *";
        cout << "\n* 4. Removal by School Name                  *";
        cout << "\n**********************************************";
        cout << "\nInput a command(0, 1-4): ";
        cin >> command;
        switch (command) {
            case 0:
                isEnd = true;
                break;
            case 1:
                if (slist.readFile()) { // if file exist
                    slist.createTree();
                    slist.printHeight();
                }
                break;
            case 2:
                if (slist.fileExist() == false)
                    cout << "\nPlease choose command 1 first!\n";
                else {
                    cout << "Input the number of graduates: ";
                    cin >> input;
                    slist.findG(input);
                }
                break;
            case 3:
                if (slist.fileExist() == false)
                    cout << "\nPlease choose command 1 first!\n";
                else {
                    cout << "Input a school name: ";
                    cin >> input;
                    slist.findS(input);
                }
                break;
            case 4:
                if (slist.fileExist() == false)
                    cout << "\nPlease choose command 1 first!\n";
                else {
                    cout << "Input a school name: ";
                    cin >> input;
                    slist.deleteS(input);
                }
                break;
            default:
                cout << "\nCommand does not exist!\n";
        } // end switch case
    } // end while
} // end main()