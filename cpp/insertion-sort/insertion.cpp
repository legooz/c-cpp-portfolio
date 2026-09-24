#include <iostream>
using namespace std;

void insertionSort(int n, int a[])
{
    for (int j = 1; j < n; j++)
    {
      int key = a[j];
      int i = j - 1;
      while ((i >=0) && (a[i]>key))
      {
          a[i+1] = a[i];
           i--;
      }
      a[i+1]=key;
    }
}

int main()
{
  int a[] = {5, 3, 8, 2, 10, 7};
  insertionSort(6, a);
  for (int i = 0; i < 6; i++)
     cout << a[i] << endl;
  return 0;
    return 0;
}
