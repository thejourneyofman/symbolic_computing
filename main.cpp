#include <iostream>
#include <cstring>

#include "mytensorflow.h"
#include "tf_parser.h"
#include "BinTree.h"

using namespace std;

// Predefine four arithmetic symbols to meet four operations.
// "+" : add
// "*" : mul
// "-" : min
// "/" : div
char const * OPERATOR[] = { "+", "*", "-", "/" };

int inputNum;
shared_ptr<BinTree<char *>> tree = make_shared<BinTree<char *>>();

// callback implementation of add_callback.
void getAdd(string a)
{
    if (tree == nullptr)
    try {
        throw "tree is empty";
    }
    catch (...){
         cout << "We caught an exception: ";
    }
    BinTree<char *>* ptr = tree.get();
    ptr->updateUnitMap(a, OPERATOR[0]);
}

// callback implementation of mul_callback.
void getMul(string a)
{
    if (tree == nullptr)
    try {
        throw "tree is empty";
    }
    catch (...){
         cout << "We caught an exception: ";
    }
    BinTree<char *>* ptr = tree.get();
    ptr->updateUnitMap(a, OPERATOR[1]);
}

// callback implementation of min_callback.
void getMin(string a)
{
    if (tree == nullptr)
    try {
        throw "tree is empty";
    }
    catch (...){
         cout << "We caught an exception: ";
    }
    BinTree<char *>* ptr = tree.get();
    ptr->updateUnitMap(a, OPERATOR[2]);
}

// callback implementation of div_callback.
void getDiv(string a)
{
    if (tree == nullptr)
    try {
        throw "tree is empty";
    }
    catch (...){
         cout << "We caught an exception: ";
    }
    BinTree<char *>* ptr = tree.get();
    ptr->updateUnitMap(a, OPERATOR[3]);
}

// callback implementation of input_callback.
void getInputs(int a)
{
    inputNum = a;
}

// callback implementation of connection_callback.
void getConnections(string a, string b, string c, string d)
{
    char * ops = new char[strlen(c.c_str())+1];
    strcpy(ops, c.c_str());
    char * nums = new char[strlen((a+b).c_str())+1];
    // input is OR NOT an output of anther unit
    if ( a == "input" ) {
        strcpy(nums, (a+b).c_str());
    } else {
        strcpy(nums, a.c_str()); // it is an output of another unit, only keep the unit name
    }

    if (tree == nullptr)
    try {
        throw "tree is empty";
    }
    catch (...){
         cout << "We caught an exception: ";
    }
    BinTree<char *>* ptr = tree.get();

    map<string, string> treeUnitMap = ptr->getUnitMap();
    ptr->addNodes(ops, nums);

}

// callback implementation of value_callback.
void getValues(string a, string b, string c)
{
    if (tree == nullptr)
    try {
        throw "tree is empty";
    }
    catch (...){
         cout << "We caught an exception: ";
    }
    BinTree<char *>* ptr = tree.get();

    int map_size = ptr->updateInputMap(a + b, c);
    if (map_size == inputNum) {
        BTNode<char *> *pNode = ptr->getRootNode();
        ptr->inOrderTraverse(pNode);
        cout << ptr->calculate(pNode) <<endl;
    }
}

// Return if key is an operator symbol defined in OPERATOR.
function<bool(const char*)> IsOperator = [](const char* key)
{
    for ( const auto& op:OPERATOR )
    {
        if ( strcmp(key, op) == 0 )
        {
            return true;
        }
    }

    return false;
};

// Return if key is an operator name defined in unit names.
function<bool(const char*)> isUnitSymbol = [](const char* key) {
    if ( strstr(key, "input") == nullptr ) {
         return true;
    } else {
        return false;
    }
};

// main
int main()
{
    tree->is_operator(IsOperator);
    tree->is_unitsymbol(isUnitSymbol);

    mytensorflow mytf;
    mytf.add_register("a");
    mytf.min_register("b");
    mytf.div_register("c");
    mytf.variable("input_0");
    mytf.variable("input_1");
    mytf.variable("input_2");
    mytf.variable("input_3");
    mytf.tensor("input_0", "a_0");
    mytf.tensor("input_1", "a_1");
    mytf.tensor("input_2", "b_0");
    mytf.tensor("input_3", "b_1");
    mytf.tensor("a", "c_0");
    mytf.tensor("b", "c_1");
    mytf.tensor("c", "result");

    mytf.constant("3.5","input_0");
    mytf.constant("5.5","input_1");
    mytf.constant("7.5","input_2");
    mytf.constant("9.5","input_3");
    mytf.constant("12.5","input_0");

    tf_parser tp(mytf);
    tp.add_callback(getAdd);
    tp.mul_callback(getMul);
    tp.min_callback(getMin);
    tp.div_callback(getDiv);
    tp.input_callback(getInputs);
    tp.connection_callback(getConnections);
    tp.value_callback(getValues);
    tp.run();

    return 0;
}
