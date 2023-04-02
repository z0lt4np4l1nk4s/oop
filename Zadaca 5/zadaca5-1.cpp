#include <iostream>
#include <list>

using namespace std;

double sum(const list<double>& L)
{
    double s = 0;
    for(auto l: L) s += l;
    return s;
}

double prod(const list<double>& L)
{
    if(L.empty()) return 1;
    double s = 1;
    for(auto l: L) s *= l;
    return s;
}

double min(const list<double>& L)
{
    if(L.empty()) throw out_of_range("min(const list<double>& L) - No elements");
    double min = L.front();
    for(auto l: L) if(l < min) min = l;
    return min;
}

double max(const list<double>& L)
{
    if(L.empty()) throw out_of_range("max(const list<double>& L) - No elements");
    double max = L.front();
    for(auto l: L) if(l > max) max = l;
    return max;
}

int main()
{
    list<double> L{ 14.4, 3.2, 12.1, 28.34, 25.12, 23.166, 3.5 };
    for(auto l: L) cout << l << " ";
    cout << endl;
    cout << "sum: " << sum(L) << endl;
    cout << "prod: " << prod(L) << endl;
    cout << "min: " << min(L) << endl;
    cout << "max: " << max(L) << endl;
}