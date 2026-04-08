#include <iostream>
#include <vector>
using namespace std;

void qsort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    
    int p = a[l], i = l, j = r;
    
    while (i < j) {
        while (i < j && a[j] >= p) j--;
        a[i] = a[j];
        while (i < j && a[i] <= p) i++;
        a[j] = a[i];
    }
    
    a[i] = p;
    qsort(a, l, i - 1);
    qsort(a, i + 1, r);
}

int main() {
    vector<int> arr = {5, 2, 8, 1, 9, 3};
    qsort(arr, 0, arr.size() - 1);
    
    for (int x : arr) cout << x << " ";
    
    return 0;
}
// write a unittest for the qsort function
#include <cassert>

void test_qsort() {
    // Test case 1: Regular case
    vector<int> arr1 = {5, 2, 8, 1, 9, 3};
    qsort(arr1, 0, arr1.size() - 1);
    assert(arr1 == vector<int>({1, 2, 3, 5, 8, 9}));

    // Test case 2: Already sorted
    vector<int> arr2 = {1, 2, 3, 4, 5};
    qsort(arr2, 0, arr2.size() - 1);
    assert(arr2 == vector<int>({1, 2, 3, 4, 5}));

    // Test case 3: Reverse sorted
    vector<int> arr3 = {5, 4, 3, 2, 1};
    qsort(arr3, 0, arr3.size() - 1);
    assert(arr3 == vector<int>({1, 2, 3, 4, 5}));

    // Test case 4: All elements are the same
    vector<int> arr4 = {1, 1, 1, 1, 1};
    qsort(arr4, 0, arr4.size() - 1);
    assert(arr4 == vector<int>({1, 1, 1, 1, 1}));

    // Test case 5: Single element
    vector<int> arr5 = {42};
    qsort(arr5, 0, arr5.size() - 1);
    assert(arr5 == vector<int>({42}));

    // Test case    6: Empty array
    vector<int> arr6 = {};
    qsort(arr6, 0, arr6.size() - 1);
    assert(arr6 == vector<int>({}));
}