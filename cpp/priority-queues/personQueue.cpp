#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Person
{
public:
    Person();
    Person(string name, int priority);
    ~Person();
    string name;
    int priority;
};

// Prototype to overload the < operator for Person
bool operator<(const Person &lhs, const Person &rhs);

Person::Person() : name(""), priority(100)
{
}

Person::Person(string name, int priority) : name(name), priority(priority)
{
}

Person::~Person()
{
}

bool operator<(const Person &lhs, const Person &rhs)
{
    return lhs.priority < rhs.priority; // Larger numeric priority is served first.
}

int main()
{
    priority_queue<Person> pq;
    pq.push(Person("Intern", 2));
    pq.push(Person("Developer", 8));
    pq.push(Person("CEO", 1000));
    pq.push(Person("Waterboy", 3));
    pq.push(Person("Manager", 12));
    pq.push(Person("Vice President", 100));
    while (!pq.empty())
    {
        cout << pq.top().name << " " << pq.top().priority << endl;
        pq.pop();
    }
    return 0;
    return 0;
}
