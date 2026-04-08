#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {5, 2, 8, 1, 9, 3};
    int n = arr.size();
    
    // 冒泡排序核心代码（只有4行）
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
    
    // 输出结果
    for (int num : arr)
        cout << num << " ";
    
    return 0;
}