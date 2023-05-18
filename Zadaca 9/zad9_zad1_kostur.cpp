#include <iostream>
#include <vector>
using namespace std;

template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node* parent, * left, * right;

    void print() const;
};

template <typename K, typename V>
struct BST {
    Node<K, V>* root;

    BST();
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
};

int main() {



    return 0;
}
