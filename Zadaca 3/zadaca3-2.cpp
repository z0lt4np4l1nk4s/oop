#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

struct Student {
    int scores[5];

    Student();

    void fillScores(int(& arr)[5]);
    int calculateTotalScore() const;
    void print() const;
};

Student::Student() 
{
    for(int i = 0; i < 5; i++) scores[i] = 0;
}

void Student::fillScores(int(& arr)[5])
{
    for(int i = 0; i < 5; i++) scores[i] = arr[i];
}

int Student::calculateTotalScore() const
{
    return accumulate(begin(scores), end(scores), 0);
}

void Student::print() const
{
    cout << "Scores: ";
    for(int i = 0; i < 5; i++) scores[i];
    cout << endl;
}

int main()
{
    ifstream file("data.txt");
    string text;
    getline(file, text);
    int n = stoi(text);
    Student* students = new Student[n];
    for(int i = 0; i < n; i++)
    {
        getline(file, text);
        int arr[5] { 0 };
        int l = 0, r = 1, c = 0;
        while(r <= text.size())
        {
            if(text[r] == ' ' || r == text.size())
            {
                string str = text.substr(l, r-l);
                r+=2;
                l = r-1;
                arr[c++] = stoi(str);
            }
            else r++;
        }
        students[i].fillScores(arr);
    }
    file.close();
    if(n <= 0) return 0;
    int markovScore = students[0].calculateTotalScore();
    auto pred = [&](const Student& student)
    {
        return student.calculateTotalScore() >= markovScore;
    };
    cout << count_if(students + 1, students + n, pred);
    delete [] students;
    return 0;
}