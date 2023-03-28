#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class DynamicStack {
private:
    vector<int> container;

public:
    DynamicStack();
    DynamicStack(const DynamicStack& S);
    ~DynamicStack();
    bool empty();
    void push(int);
    int pop();
    void print();
};

DynamicStack::DynamicStack() { container.clear(); }

DynamicStack::DynamicStack(const DynamicStack& stack)
{
    for(int i = 0; i < (int)stack.container.size(); i++) container.push_back(stack.container[i]);
}

DynamicStack::~DynamicStack() { container.clear(); }

bool DynamicStack::empty()
{
    return container.empty();
}

void DynamicStack::push(int x)
{
    container.push_back(x);
}

int DynamicStack::pop()
{
    if(container.size() == 0) throw out_of_range("DynamicStack::pop() - no elements");
    int val = container.back();
    container.pop_back();
    return val;
}

void DynamicStack::print()
{
    cout << endl << "Memory location: " << this << "; Size: " << container.size() << "; Capacity: " << container.capacity() << endl;
    if(container.size() == 0) cout << "No elements...";
    else
    {
        cout << "Elements: " << endl;
        for(int i = 0; i < (int)container.size(); i++) cout << container[i] << " ";
    }
    cout << endl;
}

int main()
{
    DynamicStack* S1 = new DynamicStack;
    for(int i = 1; i <= 10; i++) S1->push(i);
    DynamicStack* S2 = new DynamicStack(*S1);
    while(!S2->empty())
    {
        S2->print();
        cout << "Popped: " << S2->pop() << endl;;
    }
    S2->print(); 
    S1->print();
    delete S1;
    delete S2;
    return 0;
}