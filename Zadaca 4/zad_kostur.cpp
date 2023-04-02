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
};


class DynamicQueue {
protected:
    CSLL container;
public:
    DynamicQueue();
    DynamicQueue(const DynamicQueue& q);
    ~DynamicQueue();

    bool empty() const;

    void enqueue(double x);
    double dequeue();

    void print() const;
};

