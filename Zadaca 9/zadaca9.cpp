#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node* parent, * left, * right;

    Node() : parent{nullptr}, left{nullptr}, right{nullptr} {}
    Node(K key, V value) : key{key}, value{value}, parent{nullptr}, left{nullptr}, right{nullptr} {}
    Node(K key, V value, Node<K, V>* parent) : key{key}, value{value}, parent{parent}, left{nullptr}, right{nullptr} {}

    void print() const;
};

template <typename K, typename V>
void Node<K, V>::print() const
{
    cout << "Node at: " << this << "; parent at: " << parent << "; left at: " << left << "; right at: " << right << endl;
    cout << "Key: " << key << "; value: " << value << endl;
}

template <typename K, typename V>
struct BST {
    Node<K, V>* root;

    BST() : root{nullptr} {}
    // copy konstruktor (pripaziti na shallow-copy)
    BST(const BST& bst);
    ~BST();

    // pretrazuj podstablo s korijenom x dok ne pronadeš čvor
    // vrijednoscu key (u suprotnom vrati nullptr)
    Node<K, V>* search(Node<K, V>* x, K key);

    // vrati pokazivač na čvor koji ima minimalnu vrijednost
    // kljuca u podstablu čiji je korijen x
    Node<K, V>* minimum(Node<K, V>* x);

    // vrati pokazivač na čvor koji ima maksimalnu vrijednost
    // kljuca u podstablu čiji je korijen x
    Node<K, V>* maximum(Node<K, V>* x);

    // vrati sljedbenika čvora x po vrijednosti key unutar stabla
    Node<K, V>* successor(Node<K, V>* x);

    // vrati prethodnika čvora x po vrijednosti key unutar stabla
    Node<K, V>* predecessor(Node<K, V>* x);

    // unesi novi čvor brinuvši se o definiciji binary search tree-a
    void insert(const K& key, const V& value);


    // zamijeni podstabla s korijenima u i v
    void transplant(Node<K, V>* u, Node<K, V>* v);

    // obriši čvor x brinuvši se o definiciji binary search tree-a
    void remove(Node<K, V>* x);

    // napravi inorder obilazak, vrijednosti redom pohrani
    // u vektor nodes
    void inorderWalk(Node<K, V>* x, vector<Node<K, V>*>& nodes) const;

    // copy pridruživanje (pripaziti na shallow-copy)
    BST& operator=(const BST& bst);

    void print() const;
    vector<Node<K, V>*> BFS(Node<K, V>* node);
    Node<K, V>* copyTree(Node<K, V>* oldNode, Node<K, V>* parent);
};

// copy konstruktor (pripaziti na shallow-copy)
template <typename K, typename V>
BST<K, V>::BST(const BST<K, V>& bst)
{
    root = copyTree(bst.root, nullptr);
}

template <typename K, typename V>
BST<K, V>::~BST()
{
    for(auto& node : BFS(root)) delete node;
    root = nullptr;
}

// pretrazuj podstablo s korijenom x dok ne pronadeš čvor
// vrijednoscu key (u suprotnom vrati nullptr)
template <typename K, typename V>
Node<K, V>* BST<K, V>::search(Node<K, V>* x, K key)
{
    if(x == nullptr || key == x->key) return x;
    if(key < x->key) return search(x->left, key);
    return search(x->right, key);
}

// vrati pokazivač na čvor koji ima minimalnu vrijednost
// kljuca u podstablu čiji je korijen x
template <typename K, typename V>
Node<K, V>* BST<K, V>::minimum(Node<K, V>* x)
{
    if(x == nullptr || x->left == nullptr) return x;
    return minimum(x->left);
}

// vrati pokazivač na čvor koji ima maksimalnu vrijednost
// kljuca u podstablu čiji je korijen x
template <typename K, typename V>
Node<K, V>* BST<K, V>::maximum(Node<K, V>* x)
{
    if(x == nullptr || x->right == nullptr) return x;
    return maximum(x->right);
}

// vrati sljedbenika čvora x po vrijednosti key unutar stabla
template <typename K, typename V>
Node<K, V>* BST<K, V>::successor(Node<K, V>* x)
{
    if(x == nullptr) return nullptr;
    x = x->right;
    while(x->left != nullptr) x = x->left;
    return x;
}

// vrati prethodnika čvora x po vrijednosti key unutar stabla
template <typename K, typename V>
Node<K, V>* BST<K, V>::predecessor(Node<K, V>* x)
{
    if(x == nullptr) return nullptr;
    x = x->left;
    while(x->right != nullptr) x = x->right;
    return x;
}

// unesi novi čvor brinuvši se o definiciji binary search tree-a
template <typename K, typename V>
void BST<K, V>::insert(const K& key, const V& value)
{
    if(root == nullptr) 
    {
        root = new Node(key, value);
        return;
    }
    Node<K, V>* node = root;
    while(true)
    {
        if(key < node->key)
        {
            if(node->left == nullptr)
            {
                node->left = new Node<K, V>(key, value, node);
                return;
            }
            else node = node->left;
        }
        else
        {
            if(node->right == nullptr)
            {
                node->right = new Node<K, V>(key, value, node);
                return;
            }
            else node = node->right;
        }
    }
}

// zamijeni podstabla s korijenima u i v
template <typename K, typename V>
void BST<K, V>::transplant(Node<K, V>* u, Node<K, V>* v)
{
    if (u->parent == nullptr) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

// obriši čvor x brinuvši se o definiciji binary search tree-a
template <typename K, typename V>
void BST<K, V>::remove(Node<K, V>* x)
{
    if (x == nullptr) return;
    if (x->left == nullptr) transplant(x, x->right);
    else if (x->right == nullptr) transplant(x, x->left);
    else 
    {
        Node<K, V>* node = minimum(x->right);
        if (node->parent != x) 
        {
            transplant(node, node->right);
            node->right = x->right;
            node->right->parent = node;
        }
        transplant(x, node);
        node->left = x->left;
        node->left->parent = node;
    }
    delete x;
}

// napravi inorder obilazak, vrijednosti redom pohrani
// u vektor nodes
template <typename K, typename V>
void BST<K, V>::inorderWalk(Node<K, V>* x, vector<Node<K, V>*>& nodes) const
{
    if(x == nullptr) return;
    inorderWalk(x->left, nodes);
    nodes.push_back(x);
    inorderWalk(x->right, nodes);
}

// copy pridruživanje (pripaziti na shallow-copy)
template <typename K, typename V>
BST<K, V>& BST<K, V>::operator=(const BST<K, V>& bst)
{
    this->~BST();
    root = copyTree(bst.root, nullptr);
    return *this;
}

template <typename K, typename V>
void BST<K, V>::print() const
{
    cout << "-------------------------------------------------------" << endl;
    cout << "Binary search tree with root at: " << root << endl;
    if(root == nullptr) cout << "No nodes!" << endl;
    else 
    {
        cout << "Nodes:" << endl;
        vector<Node<K, V>*> nodes;
        inorderWalk(root, nodes);
        for(auto& node : nodes) node->print();
    }
    cout << "-------------------------------------------------------" << endl;
}

template <typename K, typename V>
Node<K, V>* BST<K, V>::copyTree(Node<K, V>* oldNode, Node<K, V>* parent)
{
    if(oldNode == nullptr) return nullptr;
    Node<K, V>* newNode = new Node<K, V>(oldNode->key, oldNode->value, parent);
    newNode->left = copyTree(oldNode->left, newNode);
    newNode->right = copyTree(oldNode->right, newNode);
    return newNode;
}

template <typename K, typename V>
vector<Node<K, V>*> BST<K, V>::BFS(Node<K, V>* node)
{
    vector<Node<K, V>*> nodes;
    queue<Node<K, V>*> Q;
    Q.push(node);
    while(!Q.empty())
    {
        Node<K, V>* N = Q.front();
        Q.pop();
        if(N == nullptr) continue;
        nodes.push_back(N);
        Q.push(N->left);
        Q.push(N->right);
    }
    return nodes;
}

int main() {
    BST<int, string> bst;
    bst.insert(20, "Korisnik1");
    bst.insert(25, "Korisnik2");
    bst.insert(15, "Korisnik3");
    bst.insert(17, "Korisnik4");
    bst.print();
    bst.remove(bst.root);
    bst.print();
    return 0;
}