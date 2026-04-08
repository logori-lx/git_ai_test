#include <iostream>
#include <vector>
using namespace std;

void qsort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    
    int i = l, j = r, p = a[l];
    
    while (i < j) {
        while (i < j && a[j] >= p) j--;
        if (i < j) a[i++] = a[j];
        
        while (i < j && a[i] < p) i++;
        if (i < j) a[j--] = a[i];
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