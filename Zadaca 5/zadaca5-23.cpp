#include <iostream>
#include <vector>

using namespace std;

struct Node {
	double value;
	Node* next;

	Node();
	Node(double value);
	Node(const Node& n);
	~Node();

    //swap premješta sadržaj između dva čvora
    void swap(Node& n);

	void print() const;
};

Node::Node():value{0}, next{nullptr}{}

Node::Node(double value) : value{value}, next{nullptr}{}

Node::Node(const Node& node): value{node.value}, next{node.next} {}

Node::~Node(){}

void Node::swap(Node& node)
{
    double temp = node.value;
    node.value = value;
    value = temp;
}

void Node::print() const
{
    cout << value << " at " << this << ", Next at " << next << endl;
} 

class CSLL {
protected:
	Node* head;
public:
	CSLL();
	CSLL(const CSLL& c);
	~CSLL();

	bool empty() const;

	void prepend(double value);
	void append(double value);

	double removeFromHead();

	void sort();

	void print() const;

    void reverse();
    double avg();
    Node* min();
    Node* max();
    void deleteAboveAverage();
};

CSLL::CSLL() : head{nullptr}{}

CSLL::CSLL(const CSLL& c)
{
    if(c.head == nullptr) return;
    head = new Node(c.head->value);
    Node* n = head;
    Node* tmp = c.head->next;
    while(tmp != c.head)
    {
        n->next = new Node{tmp->value};
        n = n->next;
        tmp = tmp->next;
    }
    n->next = head;
}

CSLL::~CSLL()
{
    Node* n = head->next;
    while(n != head)
    {
        Node* tmp = n;
        n = n->next;
        delete tmp;
    }
    delete head;
}

bool CSLL::empty() const 
{
    return head == nullptr; 
}

void CSLL::prepend(double value)
{
    if(empty())
    {
        Node* node = new Node(value);
        node->next = node;
        head = node;
        return;
    }
    Node* node = new Node{*head};
    head->value = value;
    head->next = node;
}

void CSLL::append(double value)
{
    Node* node = new Node{value};
    if(empty())
    {
        node->next = node;
        head = node;
    }
    else
    {
        node->next = head;
        Node* lastNode = head;
        while(lastNode->next != head)
        {
            lastNode = lastNode->next;
        }
        lastNode->next = node;
    }
}

double CSLL::removeFromHead()
{
    if(empty()) throw out_of_range("CSLL::removeFromHead() - No elements");
    double val = head->value;
    Node* newHead;
    if(head == head->next) newHead = nullptr;
    else 
    {
        newHead = head->next;
        Node* node = newHead->next;
        while(node->next != head)
        {
            node = node->next;
        }
        node->next = newHead;
    }
    delete head;
    head = newHead;
    return val;
}

void CSLL::sort()
{
    if(empty()) return;
    Node* firstNode = head;
    do
    {
        Node* min = firstNode;
        Node* currentNode = firstNode->next;
        while(currentNode != head)
        {
            if(currentNode->value < min->value) min = currentNode;
            currentNode = currentNode->next; 
        }
        if(min->value < firstNode->value) firstNode->swap(*min); 
        firstNode = firstNode->next;
    } while (firstNode != head);    
}

void CSLL::print() const
{
    if(head == nullptr)
    {
        cout << "No elements" << endl;
        return;
    }
    Node* node = head;
    cout << endl << "Elements: " << endl;
    do
    {
        cout << "Address: " << node << " value: " << node->value << "; next: " << node->next << " " << endl;
        node = node->next;
    } while (node != head);
    cout << endl;    
}

void CSLL::reverse()
{
    if(head == nullptr) return;
    Node* curr = head;
    Node* prev = head;
    while(prev->next != head) prev = prev->next;
    Node* next;
    do
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while (curr != head);
    head = prev;
}

double CSLL::avg()
{
    if(empty()) return 0;
    int s = 0, c = 0;
    Node* curr = head;
    do
    {
        s += curr->value;
        c++;
        curr = curr->next;
    } while (curr != head);
    return s / c;
}

Node* CSLL::min()
{
    if(empty()) return nullptr;
    Node* min = head;
    Node* curr = head;
    do
    {
        if(curr->value < min->value) min = curr;
        curr = curr->next;
    } while (curr != head);
    return min;
}

Node* CSLL::max()
{
    if(empty()) return nullptr;
    Node* max = head;
    Node* curr = head;
    do
    {
        if(curr->value > max->value) max = curr;
        curr = curr->next;
    } while (curr != head);
    return max;
}

void CSLL::deleteAboveAverage()
{
    if(empty()) return;
    double average = avg();
    while(head->value > average) removeFromHead();
    Node* prev = head;
    Node* curr = head->next;
    do
    {
        if(curr->value > average)
        {
            Node* temp = curr;
            prev->next = curr->next;
            curr = curr->next;
            delete temp;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    } while (curr != head);
}

int main()
{
    CSLL* l = new CSLL{}; 

    cout << "2. zadatak" << endl;

    vector<double> V = { 59.9, 13.7, 10.0, 98.44, 16.7, 20.269, 1.5 };
    for(const double& d : V) l->append(d);
    l->print();
    l->sort();
    l->reverse();
    l->print();

    cout << endl << "3. zadatak" << endl;

    cout << "Avg: " << l->avg() << endl;
    Node* min = l->min();
    cout << "Min: " << min << ", " << min->value << endl;
    Node* max = l->min();
    cout << "Max: " << max << ", " << max->value << endl;
    l->deleteAboveAverage();
    cout << endl << "Removed above average elements" << endl << "Updated list:";
    l->print();
    delete l;
    return 0;
}