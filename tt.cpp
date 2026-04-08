#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// 基础版本的快速排序（Lomuto分区方案）
template<typename T>
int partitionLomuto(std::vector<T>& arr, int low, int high) {
    // 选择最后一个元素作为基准
    T pivot = arr[high];
    int i = low - 1;  // 小于基准的元素的边界
    
    for (int j = low; j < high; j++) {
        // 如果当前元素小于等于基准
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    
    // 将基准放到正确的位置
    std::swap(arr[i + 1], arr[high]);
    return i + 1;  // 返回基准的最终位置
}

// Hoare分区方案（通常比Lomuto更快）
template<typename T>
int partitionHoare(std::vector<T>& arr, int low, int high) {
    // 选择中间元素作为基准（避免最坏情况）
    T pivot = arr[low + (high - low) / 2];
    int i = low - 1;
    int j = high + 1;
    
    while (true) {
        // 从左向右找到第一个大于等于基准的元素
        do {
            i++;
        } while (arr[i] < pivot);
        
        // 从右向左找到第一个小于等于基准的元素
        do {
            j--;
        } while (arr[j] > pivot);
        
        // 如果指针相遇或交叉，返回j
        if (i >= j) {
            return j;
        }
        
        // 交换这两个元素
        std::swap(arr[i], arr[j]);
    }
}

// 三路快速排序分区（处理大量重复元素）
template<typename T>
std::pair<int, int> partitionThreeWay(std::vector<T>& arr, int low, int high) {
    // 选择中间元素作为基准
    T pivot = arr[low + (high - low) / 2];
    int lt = low;      // arr[low..lt-1] < pivot
    int gt = high;     // arr[gt+1..high] > pivot
    int i = low;       // arr[lt..i-1] == pivot
    
    while (i <= gt) {
        if (arr[i] < pivot) {
            std::swap(arr[lt], arr[i]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            std::swap(arr[i], arr[gt]);
            gt--;
        } else {
            i++;
        }
    }
    
    return {lt, gt};  // 返回等于基准的元素的边界
}

// 插入排序（用于小数组优化）
template<typename T>
void insertionSort(std::vector<T>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        T key = arr[i];
        int j = i - 1;
        
        // 将arr[i]插入到已排序的arr[low..i-1]中
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 优化的快速排序主函数
template<typename T>
void quickSortOptimized(std::vector<T>& arr, int low, int high) {
    // 小数组使用插入排序（通常16-32个元素）
    const int INSERTION_SORT_THRESHOLD = 16;
    
    if (high - low + 1 <= INSERTION_SORT_THRESHOLD) {
        insertionSort(arr, low, high);
        return;
    }
    
    // 使用三数取中法选择基准（避免最坏情况）
    int mid = low + (high - low) / 2;
    
    // 对low、mid、high三个位置的元素进行排序
    if (arr[mid] < arr[low]) std::swap(arr[mid], arr[low]);
    if (arr[high] < arr[low]) std::swap(arr[high], arr[low]);
    if (arr[high] < arr[mid]) std::swap(arr[high], arr[mid]);
    
    // 将中位数放到high-1位置
    std::swap(arr[mid], arr[high - 1]);
    T pivot = arr[high - 1];
    
    // Hoare分区
    int i = low;
    int j = high - 1;
    
    while (true) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        
        if (i >= j) break;
        std::swap(arr[i], arr[j]);
    }
    
    // 将基准放回正确位置
    std::swap(arr[i], arr[high - 1]);
    
    // 递归排序左右两部分
    quickSortOptimized(arr, low, i - 1);
    quickSortOptimized(arr, i + 1, high);
}

// 基础快速排序（递归版本）
template<typename T>
void quickSortRecursive(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        // 使用Hoare分区
        int pivotIndex = partitionHoare(arr, low, high);
        
        // 递归排序左右两部分
        quickSortRecursive(arr, low, pivotIndex);
        quickSortRecursive(arr, pivotIndex + 1, high);
    }
}

// 迭代版本的快速排序（使用栈避免递归深度过大）
template<typename T>
void quickSortIterative(std::vector<T>& arr, int low, int high) {
    // 使用栈来模拟递归
    std::vector<std::pair<int, int>> stack;
    stack.push_back({low, high});
    
    while (!stack.empty()) {
        auto [l, h] = stack.back();
        stack.pop_back();
        
        if (l < h) {
            int pivotIndex = partitionHoare(arr, l, h);
            
            // 将左右子数组压入栈中
            stack.push_back({l, pivotIndex});
            stack.push_back({pivotIndex + 1, h});
        }
    }
}

// 三路快速排序（处理大量重复元素）
template<typename T>
void quickSortThreeWay(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        auto [lt, gt] = partitionThreeWay(arr, low, high);
        quickSortThreeWay(arr, low, lt - 1);
        quickSortThreeWay(arr, gt + 1, high);
    }
}

// 测试函数
void testQuickSort() {
    std::cout << "=== 快速排序测试 ===\n";
    
    // 测试1：随机数组
    std::vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90, 88, 76, 45};
    std::cout << "原始数组: ";
    for (int num : arr1) std::cout << num << " ";
    std::cout << "\n";
    
    quickSortOptimized(arr1, 0, arr1.size() - 1);
    std::cout << "排序后: ";
    for (int num : arr1) std::cout << num << " ";
    std::cout << "\n\n";
    
    // 测试2：大量重复元素的数组
    std::vector<int> arr2 = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9};
    std::cout << "有重复元素的数组: ";
    for (int num : arr2) std::cout << num << " ";
    std::cout << "\n";
    
    quickSortThreeWay(arr2, 0, arr2.size() - 1);
    std::cout << "三路快排后: ";
    for (int num : arr2) std::cout << num << " ";
    std::cout << "\n\n";
    
    // 测试3：性能测试
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);
    
    std::vector<int> largeArr(10000);
    for (int& num : largeArr) {
        num = dis(gen);
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    quickSortOptimized(largeArr, 0, largeArr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "排序10000个随机数用时: " << duration.count() << " 微秒\n";
    
    // 验证排序是否正确
    bool isSorted = std::is_sorted(largeArr.begin(), largeArr.end());
    std::cout << "排序验证: " << (isSorted ? "✓ 正确" : "✗ 错误") << "\n";
}

// 快速排序的模板函数（最简接口）
template<typename T>
void quickSort(std::vector<T>& arr) {
    if (arr.empty()) return;
    quickSortOptimized(arr, 0, arr.size() - 1);
}

// 主函数
int main() {
    testQuickSort();
    
    // 使用示例
    std::cout << "\n=== 使用示例 ===\n";
    
    std::vector<double> numbers = {3.14, 2.71, 1.41, 1.73, 0.58, 4.67, 2.23};
    std::cout << "排序前: ";
    for (double num : numbers) std::cout << num << " ";
    std::cout << "\n";
    
    quickSort(numbers);
    
    std::cout << "排序后: ";
    for (double num : numbers) std::cout << num << " ";
    std::cout << "\n";
    
    return 0;
}