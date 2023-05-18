#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned int Node;

template <typename K, typename V>
struct CompleteBinaryTree{

    vector<pair<K, V>> N;
    unsigned int size;

    CompleteBinaryTree(): N{}, size{0u} {}
    CompleteBinaryTree(const vector<pair<K, V>>& L): N{L}, size{L.size()} {}

    Node left(Node i) const { return 2 * i ; }
    Node right(Node i) const { return 2 * i + 1; }
    Node parent(Node i) const { return i / 2; }
    Node root() {return 1;}

    pair<K, V>& element(Node i) { return N[i]; }
    const pair<K, V>& element(Node i) const { return N[i]; }

    //setters
    void updateLeft(Node i, const pair<K, V>& e) { N[left(i)] = e; }
    void updateRight(Node i, const pair<K, V>& e) { N[right(i)] = e; }
    void updateParent(Node i, const pair<K, V>& e) { N[parent(i)] = e; }

    bool isLeaf(Node i) const { return size < left(i); }

    unsigned int getSize() { return size; }
    void setSize(unsigned int newSize) { size = newSize; }
    bool empty() { return size == 0; }

    void preorderPrint(Node) const;
    void postorderPrint(Node) const;

    void swapNodes(Node i, Node j);

    const pair<K, V>& operator[](int) const;
    pair<K, V>& operator[](int);
};

template <typename K, typename V>
void CompleteBinaryTree<K, V>::preorderPrint(Node i) const {
    if (i >= size) {
        return;
    }
    cout << N[i] << "\t";
    preorderPrint(left(i));
    preorderPrint(right(i));
}

template <typename K, typename V>
void CompleteBinaryTree<K, V>::postorderPrint(Node i) const {
    if (i >= size) {
        return;
    }
    postorderPrint(left(i));
    postorderPrint(right(i));
    cout << N[i] << "\t";
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::swapNodes(Node i, Node j) {
    swap(N[i], N[j]);
}

template<typename K, typename V>
const pair<K, V> &CompleteBinaryTree<K, V>::operator[](int i) const {
    return N.at(i);
}

template<typename K, typename V>
pair<K, V> &CompleteBinaryTree<K, V>::operator[](int i) {
    return N.at(i);
}

template <typename K, typename V>
class MinPriorityQueue {
public:
    CompleteBinaryTree<K, V> tree;
    MinPriorityQueue();
    MinPriorityQueue(const MinPriorityQueue&);

    void downHeap(Node i);
    void upHeap(Node i);

    // s obzirom na prosljeđeni vektor, izgrađujemo prioritetni red
    // (pretpostavljamo da je prioritetni red prazan, ili pregazimo
    // sve dosad pohranjene parove)
    void buildMinHeap(const vector<pair<K, V>>& L);

    V minimum();
    V extractMin();
    void decreaseKey(Node i, K key);
    void insert(const pair<K, V>& v);

    // ispis reda
    void print() const;
};

template <typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue() 
{
    //Everything is 1 indexed
    //That is why I need some dummy data
    insert({123, "dummy data"});
    //And to set back the size to 0
    tree.setSize(0);
}

template <typename K, typename V>
MinPriorityQueue<K, V>::MinPriorityQueue(const MinPriorityQueue& Q)
{
    //Adding the dummy data first
    insert({123, "dummy data"});
    //reseting the size
    tree.setSize(0);
    for(int i = 1; i <= Q.tree.size; i++) tree.N.push_back(Q.tree[i]);
    tree.size = Q.tree.size;
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::downHeap(Node i)
{
    Node l = tree.left(i), r = tree.right(i);
    if(l <= tree.size && tree[l] < tree[r])
    {
        tree.swapNodes(i, l);
        downHeap(l);
    }
    else if(r <= tree.size)
    {
        tree.swapNodes(i, r);
        downHeap(r);
    }
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::upHeap(Node i)
{
    if(i <= 1) return;
    Node p = tree.parent(i);
    if(tree[i] < tree[p])
    {
        tree.swapNodes(i, p);
        upHeap(p);
    }
}

// s obzirom na prosljeđeni vektor, izgrađujemo prioritetni red
// (pretpostavljamo da je prioritetni red prazan, ili pregazimo
// sve dosad pohranjene parove)
template <typename K, typename V>
void MinPriorityQueue<K, V>::buildMinHeap(const vector<pair<K, V>>& L)
{
    tree.N.clear();
    for(auto& kvp: L) insert(kvp);
    tree.size = L.size();
}

template <typename K, typename V>
V MinPriorityQueue<K, V>::minimum()
{
    if(tree.size == 0) throw ("V MinPriorityQueue<K, V>::minimum() - No elements");
    return tree[tree.root()].second;
}

template <typename K, typename V>
V MinPriorityQueue<K, V>::extractMin()
{
    if(tree.size == 0) throw ("V MinPriorityQueue<K, V>::extractMin() - No elements");
    V m = tree[tree.root()].second;
    tree.swapNodes(tree.root(), tree.size--);
    tree.N.pop_back();
    downHeap(tree.root());
    return m;
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::decreaseKey(Node i, K key)
{
    if(i == 0 || i > tree.size) return;
    tree[i].first = key;
    upHeap(i);
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::insert(const pair<K, V>& v)
{
    tree.N.push_back(v);
    upHeap(++tree.size);
}

// ispis reda
template <typename K, typename V>
void MinPriorityQueue<K, V>::print() const
{
    //printing using the << operator
    cout << *this;
}

template <typename K, typename V>
ostream &operator<<(ostream &out, const pair<K, V> &p)
{
    cout << "K: " << p.first << ", V: " << p.second << ";\t";
    return out;
}

template <typename K, typename V>
ostream &operator<<(ostream &out, const CompleteBinaryTree<K, V> &tree)
{
    for(int i = 1; i <= tree.size; i++) cout << tree[i];
    return out;
}

template <typename K, typename V>
ostream &operator<<(ostream &out, const MinPriorityQueue<K, V> &Q)
{
    out << Q.tree << endl;
    return out;
}

int main() 
{
    MinPriorityQueue<int, string> Q;
    vector<pair<int, string>> V = {{1, "osoba4"}, {2, "osoba7"}, {7, "osoba5"}, {8, "osoba1"}, {5, "osoba6"}};
    //Q.buildMinHeap(V);
    for(auto& p : V) Q.insert(p);
    Q.print();
    Q.insert({6, "osoba9"});
    Q.print();
    string minVal = Q.extractMin();
    cout << "Minimum value: " << minVal << endl;
    Q.print();
    //In the task it was said to change the key for the element
    //on index 2 (0 indexed) that is why I wrote 3 (1 indexed)
    Q.decreaseKey(3, 4);
    Q.print();
    MinPriorityQueue<int, string> Q1 = {Q};
    Q1.print();
    return 0;
}
