#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Node;

using NodeList = list<Node*>;
using Elem = int;

class Node{
protected:
    Elem _elt;
    Node* _par;
    list<Node*> _children;
private:
    Node* copyNode(Node*);
    NodeList getAllChildren(Node* node);
public:
    Node(Elem);
    Node(const Node&);
    list<Node*>& children();
    Node* parent() const;
    Elem element() const;
    void setParent(Node*);
    void prependChild(Node*);
    void appendChild(Node*);
    void removeFirstChild();
    void removeLastChild();
    void setValue(Elem);
    bool isRoot() const;
    bool isLeaf() const;
};

Node* Node::copyNode(Node* node)
{
    if(node == nullptr) return nullptr;
    Node* newNode = new Node{node->element()};
    newNode->setParent(node);
    for(auto& n : node->children())
    {
        newNode->appendChild(new Node{n->element()});
    }
    return newNode;
}

Node::Node(Elem e) : _elt{e}, _par{nullptr} {}

Node::Node(const Node& node)
{
    _elt = node.element();
    _par = node.parent();
    if(_par != nullptr) _par->appendChild(this);
    for(auto& n : node._children) appendChild(new Node(n->element()));
}

list<Node*>& Node::children() { return _children; }

Node* Node::parent() const { return _par; }
    
Elem Node:: element() const { return _elt; }

void Node::setParent(Node* node) { _par = node; }

void Node::prependChild(Node* node ) 
{ 
    node->setParent(this);
    _children.push_front(node); 
}

void Node::appendChild(Node* node) 
{ 
    node->setParent(this);
    _children.push_back(node); 
}

NodeList Node::getAllChildren(Node* node)
{
    NodeList L;
    queue<Node*> Q;
    Q.push(node);
    while(!Q.empty())
    {
        Node* n = Q.front();
        Q.pop();
        if(n == nullptr) continue;
        L.push_back(n);
        for(auto& N : n->children()) Q.push(N);
    }
    return L;
}

void Node::removeFirstChild() 
{
    Node* node = _children.front();
    _children.pop_front(); 
    for(auto& n : getAllChildren(node)) delete n; 
}

void Node::removeLastChild() 
{ 
    Node* node = _children.back();
    _children.pop_back(); 
    for(auto& n : getAllChildren(node)) delete n; 
}

void Node::setValue(Elem e) { _elt = e; }

bool Node::isRoot() const { return _par == nullptr; }
    
bool Node::isLeaf() const { return _children.size() == 0; }

class NAryTree {
protected:
    Node* _root;
private:
    Node* copyTree(Node* node);
public:
    NAryTree();
    NAryTree(const NAryTree&);
    ~NAryTree();
    Node* root() const;
    void addRoot(Elem);
    void appendChild(Node*, Elem);
    void prependChild(Node*, Elem);
    void preorderPrint(Node* ) const;
    void postorderPrint(Node* ) const;
    void preorderNodes(Node*, NodeList&); //radi preorder obilazak i sprema Node-ove u proslijeđeni NodeList
    NodeList BFS(Node*);
    NAryTree& operator=(const NAryTree&);
};

NAryTree::NAryTree() : _root{nullptr} {}

Node* NAryTree::copyTree(Node* node)
{
    if(node == nullptr) return nullptr;
    Node* newNode = new Node{node->element()};
    for(auto& n : node->children())
    {
        Node* child = copyTree(n);
        child->setParent(newNode);
        newNode->appendChild(child);
    }
    return newNode;
}

NAryTree::NAryTree(const NAryTree& tree)
{
    _root = copyTree(tree.root());
}

NAryTree::~NAryTree()
{
    NodeList L = BFS(root());
    for(auto& node : L) delete node;
}

Node* NAryTree::root() const { return _root; };

void NAryTree::addRoot(Elem e)
{
    if(_root != nullptr) return;
    _root = new Node(e);
}

void NAryTree::appendChild(Node* node, Elem e) 
{ 
    Node* newNode = new Node{e};
    node->appendChild(newNode); 
}

void NAryTree::prependChild(Node* node, Elem e) 
{ 
    Node* newNode = new Node{e};
    newNode->setParent(node);
    node->prependChild(newNode); 
}
    
void NAryTree::preorderPrint(Node* node) const 
{
    if(node == nullptr) return;
    cout << node->element() << " ";
    for(auto& n : node->children()) preorderPrint(n);
}

void NAryTree::postorderPrint(Node* node) const
{
    if(node == nullptr) return;
    for(auto& n : node->children()) postorderPrint(n);
    cout << node->element() << " ";
}

void NAryTree::preorderNodes(Node* node, NodeList& nodeList) //radi preorder obilazak i sprema Node-ove u proslijeđeni NodeList
{
    if(node == nullptr) return;
    nodeList.push_back(node);
    for(auto& n : node->children()) preorderNodes(n, nodeList);
}

NodeList NAryTree::BFS(Node* node)
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
        for(auto& N : n->children()) Q.push(N);
    }
    return L;
}
    
NAryTree& NAryTree::operator=(const NAryTree& tree)
{
    _root = copyTree(tree.root());
    return *this;
}

int main()
{
    NAryTree T;
    T.addRoot(5);
    Node* child = new Node(1);
    T.root()->appendChild(child);
    child->appendChild(new Node(11));
    child->appendChild(new Node(14));
    child->prependChild(new Node(10));
    T.root()->appendChild(new Node(2));
    T.root()->appendChild(new Node(3));
    T.root()->appendChild(new Node(4));

    cout << "Preorder: " << endl;
    T.preorderPrint(T.root()); cout << endl << endl;
    cout << "Postorder: " << endl;
    T.postorderPrint(T.root()); cout << endl << endl;

    NAryTree T2 = T;
    for(auto& n : T2.BFS(T2.root())) n->setValue(n->element() + 1);

    for(auto& n : T.BFS(T.root())) cout << n->element() << " ";
    cout << endl << endl;
    for(auto& n : T2.BFS(T2.root())) cout << n->element() << " ";
    cout << endl << endl;

    T.root()->removeLastChild();
    for(auto& n : T.BFS(T.root())) cout << n->element() << " ";
    cout << endl << endl;

    cout << "Is " << T.root()->element() << " root? " << endl << T.root()->isRoot(); 

    return 0;
}