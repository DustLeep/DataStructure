#include "../../List/list.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../../List/queue.h"

using namespace std;

void print(int arr[], int n)
{
    // 打印数组
    cout << "高度:";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    srand(time(NULL));
    for (int k = 0; k < 10; k++)
    {
        // 初始化队列
        Queue<int> q;
        int n = rand() % 105 + 1;
        int arr[n];
        for (int i = 0; i < n; i++)
        {
            // 初始化数组
            arr[i] = rand() % 106;
        }
        print(arr, n);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            // 当队列不为空且栈顶元素大于当前元素时
            while (!q.empty() && arr[q.front()] > arr[i])
            {
                // 获取栈顶元素
                int h = arr[q.front()];
                // 弹出栈顶元素
                q.dequeue();
                // 获取左边界
                int l = q.empty() ? -1 : q.front();
                // 计算最大面积
                ans = max(ans, h * (i - l - 1));
            }
            // 当前元素入队
            q.enqueue(i);
        }
        while (!q.empty())
        {
            // 获取栈顶元素
            int h = arr[q.front()];
            // 弹出栈顶元素
            q.dequeue();
            // 获取左边界
            int l = q.empty() ? -1 : q.front();
            // 计算最大面积
            ans = max(ans, h * (n - l - 1));
        }
        cout << "最大矩形面积为" << ans << endl
             << endl;
    }
    return 0;
}