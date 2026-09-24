#include <iostream>

using namespace std;

bool isSorted(int arr[], int n);

bool isSorted(int arr[], int n)
{

    if (n <= 1)
    {
        return true;

    } else if(arr[n-2] > arr[n-1]) {
        return false;

    } else {

        return isSorted(arr, n - 1);
    }

}

int main()
{

    int test1[] = { 1,2,3 };
    int test2[] = { 2,1,3 };

    cout << isSorted(test1, 3) << endl; // Outputs 1 for true
    cout << isSorted(test2, 3) << endl; // Outputs 0 for false

    return 0;
}
