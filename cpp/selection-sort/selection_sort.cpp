#include <iostream>
using namespace std;

// Function prototypes
void swap(int& x, int& y);
void selectionSort(int a[], int startIndex, int endIndex);

// Recursively sort array a.
// startIndex: The index of the starting element in array a where we want sorting to begin.
//             For example, startIndex would be 0 to start at the first element.
// endIndex:   The index of the last element in array a where we want sorting to end.
//             For example, in an array of length 5, this would be 4 to specify the last element.
void selectionSort(int a[], int startIndex, int endIndex)
{
    // Base case or termination condition: quit if start and end are the same.
    // This would specify to sort only a single element, which is already sorted.
    if (startIndex >= endIndex)
        return;

    int indexOfMin = startIndex;
    // Find the minimum element in the inclusive unsorted range.

    for(int i = startIndex; i <= endIndex; i++)
    {
        if (a[indexOfMin] > a[i])
        {
            indexOfMin = i;
        }
    }

    // Once indexOfMin is found, swap the values in the array at indexOfMin and startIndex
    swap(a[indexOfMin], a[startIndex]);  // Move the minimum to the front of the range.

    // Recursively sort the remaining suffix.
    selectionSort(a, startIndex + 1, endIndex);
}

// Swap two integers by reference.

void swap(int &x, int &y)
{
    int spaceHolder = x;
    x = y;
    y = spaceHolder;
}

// Demonstrate sorting two integer arrays.
int main()
{

    int b[10] = { 1000, 20, -1, 0 , 93, 4, 33, 22, 11, 9 };

    cout << "Test 2 numbers : " << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << b[i] << endl;

    }

    selectionSort(b, 0, 9);

    cout << "Test 2 after selection sort : " << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << b[i] << endl;
    }
    int a[5] = { 6, 5, 0, 9, 5 };

    cout << "Test 1 numbers : " << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << a[i] << endl;

    }

    selectionSort(a, 0, 4);

    cout << "Test 1 after selection sort : " << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << a[i] << endl;

    }

    return 0;
}
