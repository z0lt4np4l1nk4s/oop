#include <iostream>
#include <list>
#include <utility>

using namespace std;

template <typename K, typename V>
struct MinPriorityQueue {
    list<pair<K, V>> container;
    void insert(const pair<K, V>& el);
    V extractMin();

    // pronalazimo element s kljucem key, te ga postavljamo
    // na odgovarajuće mjesto s obzirom na njegov novi kljuc
    // newKey
    void decreaseKey(const K& key, const K& newKey);
    // ispis prioritetnog reda	
    void print() const;
};

template <typename K, typename V>
void MinPriorityQueue<K, V>::insert(const pair<K, V>& el)
{
    for(auto it = container.begin(); it != container.end(); it++)
    {
        if(it->first >= el.first) 
        {
            container.insert(it, el);
            return;
        }
        
    }
    container.push_back(el);
}

template <typename K, typename V>
V MinPriorityQueue<K, V>::extractMin()
{
    V value = container.front().second;
    container.pop_front();
    return value;
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::decreaseKey(const K& key, const K& newKey)
{
    auto it = container.begin();
    V value;
    for(; it != container.end(); it++)
    {
        if(it->first == key) 
        {
            value = it->second;   
            it->first = newKey;
            break;
        }
    }
    if(it == container.end()) return;
    container.erase(it);
    insert({newKey, value});
}

template <typename K, typename V>
void MinPriorityQueue<K, V>::print() const
{
    for(auto it = container.begin(); it != container.end(); it++)
    {
        cout << "K: " << it->first << ", V: " << it->second << ";\t";
    }
    cout << endl;
}

int main()
{
    MinPriorityQueue<int, string> Q;
    Q.insert({1, "osoba4"});
    Q.insert({2, "osoba7"}); 
    Q.insert({7, "osoba5"});
    Q.insert({8, "osoba1"});
    Q.insert({5, "osoba6"});
    Q.print();
    Q.insert({6, "osoba9"});
    Q.print();
    string minValue = Q.extractMin();
    cout << "Minimum element: " << minValue << endl;
    Q.print();
    Q.decreaseKey(6, 4);
    Q.print();
    return 0;
}