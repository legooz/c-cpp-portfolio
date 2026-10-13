#include <iostream>
#include <string>
#include "queue.cpp"
using namespace std;

int main()
{
  Queue<string> q;

    q.enqueue("Bill");
    q.enqueue("Aaron");
    q.enqueue("Zorro");
    q.enqueue("Gobu");
    while (!q.isEmpty())
    {
        string s = q.dequeue();
        cout << s << endl;
    }
  return 0;
}
