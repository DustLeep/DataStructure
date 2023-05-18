#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
using namespace std;

void bubbleSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        int min = i;
        for (int j = i + 1; j < size; ++j)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}
void insertionSort(int arr[], int size)
{
    for (int i = 1; i < size; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}
void selectionsort(int arr[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        int min = i;
        for (int j = i + 1; j < size; ++j)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1, n2 = r - m;
    int *L = new int[n1], *R = new int[n2];
    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; ++i)
        R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}
void mergesort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
void quicksort(int arr[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = arr[l];
        while (i < j)
        {
            while (i < j && arr[j] >= x)
                --j;
            if (i < j)
                arr[i++] = arr[j];
            while (i < j && arr[i] < x)
                ++i;
            if (i < j)
                arr[j--] = arr[i];
        }
        arr[i] = x;
        quicksort(arr, l, i - 1);
        quicksort(arr, i + 1, r);
    }
}
void reverse(int arr[], int size)
{
    for (int i = 0; i < size / 2; ++i)
    {
        swap(arr[i], arr[size - i - 1]);
    }
}
void bak(int arr[], int arr2[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        arr2[i] = arr[i];
    }
}
int main()
{
    // 创建一个长度为1000的​int​数组
    int arr[1000];
    // 用随机数填充数组
    srand(time(NULL));
    for (int i = 0; i < 1000; ++i)
    {
        arr[i] = rand() % 1000;
    }
    // 备份数组
    int arr2[1000];
    bak(arr, arr2, 1000);
    // 分别用冒泡排序、选择排序、插入排序、归并排序、快速排序对数组进行排序，并输出​每种排序算法的运行时间,单位为纳秒
    cout << "随机乱序数组：" << endl;
    auto start = chrono::steady_clock::now();
    bubbleSort(arr, 1000);
    auto end = chrono::steady_clock::now();
    cout << "冒泡排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    bak(arr2, arr, 1000);
    start = chrono::steady_clock::now();
    selectionSort(arr, 1000);
    end = chrono::steady_clock::now();
    cout << "选择排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    bak(arr2, arr, 1000);
    start = chrono::steady_clock::now();
    insertionSort(arr, 1000);
    end = chrono::steady_clock::now();
    cout << "插入排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    bak(arr2, arr, 1000);
    start = chrono::steady_clock::now();
    mergesort(arr, 0, 999);
    end = chrono::steady_clock::now();
    cout << "归并排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    bak(arr2, arr, 1000);
    start = chrono::steady_clock::now();
    quicksort(arr, 0, 999);
    end = chrono::steady_clock::now();
    cout << "快速排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    // 顺序数组
    cout << "顺序数组:" << endl;
    start = chrono::steady_clock::now();
    bubbleSort(arr, 1000);
    end = chrono::steady_clock::now();
    cout << "冒泡排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    start = chrono::steady_clock::now();
    selectionSort(arr, 1000);
    end = chrono::steady_clock::now();
    cout << "选择排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    start = chrono::steady_clock::now();
    insertionSort(arr, 1000);
    end = chrono::steady_clock::now();
    cout << "插入排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    start = chrono::steady_clock::now();
    mergesort(arr, 0, 999);
    end = chrono::steady_clock::now();
    cout << "归并排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    start = chrono::steady_clock::now();
    quicksort(arr, 0, 999);
    end = chrono::steady_clock::now();
    cout << "快速排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    // 反转数组
    reverse(arr, 1000);
    bak(arr, arr2, 1000);
    // 逆序数组
    cout << "逆序数组:" << endl;
    start = chrono::steady_clock::now();
    bubbleSort(arr, 1000);
    end = chrono::steady_clock::now();
    cout << "冒泡排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    bak(arr2, arr, 1000);
    start = chrono::steady_clock::now();
    selectionSort(arr, 1000);
    end = chrono::steady_clock::now();
    cout << "选择排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    bak(arr2, arr, 1000);
    start = chrono::steady_clock::now();
    insertionSort(arr, 1000);
    end = chrono::steady_clock::now();
    cout << "插入排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    bak(arr2, arr, 1000);
    start = chrono::steady_clock::now();
    mergesort(arr, 0, 999);
    end = chrono::steady_clock::now();
    cout << "归并排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    bak(arr2, arr, 1000);
    start = chrono::steady_clock::now();
    quicksort(arr, 0, 999);
    end = chrono::steady_clock::now();
    cout << "快速排序用时：" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;
    return 0;
}