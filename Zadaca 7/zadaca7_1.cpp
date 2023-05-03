#include <iostream>
#include <list>
#include <queue>
using namespace std;

class Node;

using NodeList = list<Node*>;
using Elem = int;

class Node
{
protected:
    Elem _elt;
    Node* _left;
    Node* _right;
    Node* _par;
public:
    Node(Elem e): _elt(e), _left(nullptr), _right(nullptr), _par(nullptr){}
    Node(Elem e, Node* left, Node* right, Node* parent): _elt(e), _left(left), _right(right), _par(parent){}
    // setters
    void setLeft(Node *left)  { _left = left; }
    void setRight(Node *right) { _right = right; }
    void setParent(Node *par) { _par = par; }
    void setElement(Elem e) { _elt = e; }
    // getters
    Elem element() const { return _elt; }
    Node * left() const { return _left; }
    Node * right() const { return _right; }
    Node * parent() const  { return _par; }
    // predicates
    bool isRoot() const { return _par == nullptr; } // return True if root
    bool isLeaf() const { return (_left == nullptr) && (_right == nullptr); }  // return True if leaf
};

class BinaryTree
{
private:
    Node* _root;
    unsigned int _size;

    Node* copyTree(Node* node);
public:
    BinaryTree():_root(nullptr), _size(0){}
    BinaryTree(const BinaryTree&);
    Node* root() const { return _root; }
    unsigned size() const { return _size ; }

    bool addRoot(Elem e); // add root to the empty tree
    bool expandLeaves(Node *, Elem, Elem); // add leaves to leaf node

    void postorderPrint(Node*); // print nodes in postorder manner
    void preorderPrint(Node*); // print nodes in preorder manner

    void preorderTree(Node*, NodeList&); // save node pointer to NodeList in preorder fashion

    BinaryTree& operator=(const BinaryTree&);
    NodeList BFS(Node*);

    ~BinaryTree(); // delete tree, i.e. delete all nodes
};

void BinaryTree::preorderTree(Node* n, NodeList& L){

    if (n == nullptr)
        return;
    L.push_back(n);
    preorderTree(n->left(), L);
    preorderTree(n->right(), L);
}

BinaryTree::~BinaryTree()
{
    // collect all nodes in list of nodes
    NodeList L = BFS(root());
    // delete them one by one
    for (auto n: L) delete n;
}
void BinaryTree::postorderPrint(Node *n){
    if (n == nullptr) return;
    postorderPrint(n->left());
    postorderPrint(n->right());
    cout << n->element() << " " ;
}

void BinaryTree::preorderPrint(Node *n)
{
    if (n == nullptr)
        return;
    cout << n->element() << " " ;
    preorderPrint(n->left());
    preorderPrint(n->right());
}
bool BinaryTree::addRoot(Elem e)
{
    if (_root != nullptr) return false;
    else
    {
        _root = new Node(e);
        _size = 1;
        return true;
    }
}

bool BinaryTree::expandLeaves(Node *n, Elem e1, Elem e2)
{
    if (n == nullptr || n->left() != nullptr && n->right() != nullptr) return false;
    Node* n1 = new Node(e1);
    Node* n2 = new Node (e2);
    n->setLeft(n1);
    n1->setParent(n);
    n->setRight(n2);
    n2->setParent(n);
    _size += 2;
    return true;
}

unsigned depth(const BinaryTree& T, const Node& n)
{
    if (n.isRoot())
        return 0;
    else
        return 1 + depth(T, *n.parent() );

}

unsigned height(const BinaryTree& T, const Node& n)
{
    if (n.isLeaf())
        return 0;
    else
        return 1 + max(height(T, *n.left()), height(T, *n.right()));
}

Node* BinaryTree::copyTree(Node* node)
{
    if(node == nullptr) return nullptr;
    return new Node(node->element(), copyTree(node->left()), copyTree(node->right()), node);
}

BinaryTree::BinaryTree(const BinaryTree& tree)
{
    _root = copyTree(tree.root());
    _size = tree.size();
}

BinaryTree& BinaryTree::operator=(const BinaryTree& tree)
{
    for(auto& n : BFS(_root)) delete n;
    _root = copyTree(tree.root());
    _size = tree.size();
    return *this;
}

NodeList BinaryTree::BFS(Node* node)
{
    NodeList L;
    queue<Node*> Q;
    Q.push(node);
    while (!Q.empty())
    {
        Node* n = Q.front();
        Q.pop();
        if(n == nullptr) continue;
        L.push_back(n);
        Q.push(n->left());
        Q.push(n->right());
    }
    return L;
}

int main() {
    Elem e = 1;
    Node n(e);

    BinaryTree T;
    T.addRoot(1);
    T.expandLeaves(T.root(), 2, 3);
    T.expandLeaves(T.root()->left(), 4, 5);

    BinaryTree T2{T};

    BinaryTree T3;
    T3.addRoot(10);
    T3 = T2;
    T3.expandLeaves(T3.root()->right(), 6, 7);

    NodeList L = T3.BFS(T3.root());

    for(auto& N : L) cout << N->element() << " ";
    cout << endl << endl;

    for(auto& N : T2.BFS(T2.root())) N->setElement(N->element() + 1);
    T2.preorderPrint(T2.root()); cout << endl << endl;
    T.preorderPrint(T.root());

    return 0;
}