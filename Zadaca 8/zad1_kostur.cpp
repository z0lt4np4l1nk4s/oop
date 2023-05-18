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
