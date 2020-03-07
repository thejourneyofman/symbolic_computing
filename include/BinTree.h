#ifndef BINTREE_H
#define BINTREE_H

#include <memory>
#include <map>

using namespace std;

template <typename T>
struct BTNode
{
    BTNode<T> *left;
    BTNode<T> *right;
    BTNode<T> *parent;
    T key;
    T value;
};

template <class T>
class BinTree
{
public:
    // Constrctor
    explicit BinTree() : m_pTree(nullptr) {
    }

    BinTree(BinTree<T>&& other){
        m_pTree = move(other.m_pTree);
        *other.m_pTree = nullptr;
    }

    // Destructor
    ~BinTree()
    {
        releaseTree(m_pTree);
        m_pTree = nullptr;
    }

    void is_operator(std::function<bool(const T)> ip){
        IsOperator = ip;
    }

    void is_unitsymbol(std::function<bool(const T)> iu) {
        isUnitSymbol = iu;
    }

    // Add TWO nodes to the binary tree from one connection
    // which concludes a unit and an input, where input can be
    // another output of unit.
    BTNode<T>* addNodes(T unit, T input)
    {
        // Create a unit node
        BTNode<T> *unitNode = new BTNode<T>;
        unitNode->key = unit;
        unitNode->parent = nullptr;
        unitNode->left = nullptr;
        unitNode->right = nullptr;

        // Create an input node
        BTNode<T> *inputNode = new BTNode<T>;
        inputNode->key = input;
        inputNode->parent = nullptr;
        inputNode->left = nullptr;
        inputNode->right = nullptr;

        // In case that tree is empty
        if ( m_pTree == nullptr )
        {
            // if there are no ALUs (one input connected to result), add the only input to the tree.
            if ( strcmp(unit, "result") == 0 ) {
                m_pTree = inputNode;
            } else { // add the unit and input nodes to the tree and return
                m_pTree = unitNode;
                unitNode->left = inputNode;
                inputNode->parent = unitNode;
            }
            return m_pTree;
        }

        // Do nothing if the connection concludes the "result"
        if ( strcmp(unit, "result") == 0 ) {
            return m_pTree;
        }

        // Find if the unit is in the tree
        BTNode<T> * uNode = findNode(m_pTree, unit);
        // If the unit is not in the tree and its input is in the tree,
        // apend it to the tree. Note that all those reserved inputs
        // stored in the isolatedMap will be appended to the tree too.
        if ( uNode == nullptr ) {
            if ( isUnitSymbol(input) ) {
                BTNode<T> * iNode = findNode(m_pTree, input);
                unitNode->left = iNode;
                iNode->parent = unitNode;
                auto iter = isolatedMap.find(unit);
                if ( iter != isolatedMap.end() ) {
                    unitNode->right = iter->second;
                    iter->second->parent = unitNode;
                    isolatedMap.erase(iter);
                }
                m_pTree = unitNode;
            } else { // Otherwise, store it to the isolatedMap.
                // If unit is already in the isolatedMap, merge all children to one node.
                auto iter = isolatedMap.find(unit);
                if ( iter != isolatedMap.end() ) {
                    BTNode<T> *temp = new BTNode<T>;
                    temp->key = unit;
                    temp->parent = nullptr;
                    temp->left = iter->second;
                    temp->right = inputNode;
                    iter->second = temp;
                } else { // Otherwise, simply insert it to the isolatedMap.
                    isolatedMap.insert(pair<string, BTNode<T> *>(string(unit), inputNode));
                }
            }
        } else {
            // If unit is already in the tree, update its children.
            if ( isUnitSymbol(input) ) {
                auto iter = isolatedMap.find(input);
                if ( iter != isolatedMap.end() ) {
                    inputNode = iter->second;
                }

            }
            uNode->right =  inputNode;
            inputNode->parent = uNode;
        }

        return m_pTree;
    }

    // Recursively find the node and if it exists in the tree,
    // return its node point.
    BTNode<T> *findNode(BTNode<T> * &Node, const T ch){
        if( Node == nullptr ){
            return nullptr;
        }
        else if( strcmp(Node->key, ch) == 0) {
            return Node;
        }
        else{
            BTNode<T> *p;
            p = findNode(Node->left, ch);
            if( p != nullptr ){
                return p;
            }
            else{
                return findNode(Node->right, ch);
            }
        }
    }

    // Recursively traverse the tree in order and
    // update the "value" for each node.
    void inOrderTraverse(BTNode<T> * pNode)
    {
        if ( pNode != nullptr )
        {

            // Traverse its left child
            inOrderTraverse(pNode->left);

            // Update the "value" field of each node
            if ( strcmp(pNode->key, "-1") == 0 ) {
                pNode->value = pNode->key;
            } else if ( isUnitSymbol(pNode->key) ) {
                pNode->value = new char[strlen(m_pUnitMap[pNode->key].c_str()) + 1];
                strcpy(pNode->value, m_pUnitMap[pNode->key].c_str());
            } else {
                pNode->value = new char[strlen(m_pInputMap[pNode->key].c_str()) + 1];
                strcpy(pNode->value, m_pInputMap[pNode->key].c_str());
            }

            // Traverse its right child
            inOrderTraverse(pNode->right);
        }
    }

    // Destroy the tree and releaes all its nodes.
    void releaseTree(BTNode<T> * pNode)
    {
        if (pNode != nullptr)
        {
            releaseTree(pNode->left);
            releaseTree(pNode->right);
            free(pNode);
        }
    }

    // Process the calulation of the arithmetic logics.
    // Recursively processing in DLR.
    double calculate(const BTNode<T> * pNode)
    {
        double x, y, result;
        if ( IsOperator(pNode->value) )
        {
            x = calculate(pNode->left);
            y = calculate(pNode->right);
            char op = *(T) pNode->value;
            switch(op){
                case '+':
                    result = x + y;
                    break;
                case '*':
                    result = x * y;
                    break;
                case '-':
                    result = x - y;
                    break;
                case '/':
                    try {
                        if( y == 0 )
                            throw "division by zero error.";
                        result = x / y;
                    } catch (const char* msg) {
                        std::cerr << msg << std::endl;
                    }
                    break;
            }
            return result;
        }
        result = atof(pNode->value);
        return result;
    }

    // Return the root node.
    BTNode<T> *getRootNode() {
        return m_pTree;
    }

    // Update the input map and return its size.
    int updateInputMap(const string a, const string b) {
        if ( m_pInputMap.find(a) != m_pInputMap.end() ) {
            m_pInputMap[a] = b;
        } else {

            m_pInputMap.insert(pair<string, string>(a, b));
        }
        return m_pInputMap.size();
    }

    // Return the unit map.
    map<string, string> getUnitMap(){
        return m_pUnitMap;
    }

    // Update the unit map.
    void updateUnitMap(const string a, const string b) {
        if ( m_pUnitMap.find(a) != m_pUnitMap.end() ) {
            m_pUnitMap[a] = b;
        } else {
            m_pUnitMap.insert(pair<string, string>(a, b));
        }
    }


private:
    BTNode<T> *m_pTree;
    map<string, BTNode<T> *> isolatedMap;
    map<string, string> m_pUnitMap;
    map<string, string> m_pInputMap;
    std::function<bool(const T)> IsOperator;
    std::function<bool(const T)> isUnitSymbol;

};

#endif // BINTREE_H
