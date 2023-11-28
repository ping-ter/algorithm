#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void selectSort(vector<int> &datas)
{
    int n = datas.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (datas[j] < datas[min])
            {
                min = j;
            }
        }
        swap(datas[i], datas[min]);
    }
}

void siftDown(vector<int> &datas, int root, int n) // 重建堆
{
    int lchild = root * 2 + 1;
    int rchild = root * 2 + 2;
    while (lchild < n)
    {
        int max = root;
        if (datas[lchild] > datas[max])
        {
            max = lchild;
        }
        if (rchild < n && datas[rchild] > datas[max])
        {
            max = rchild;
        }
        if (max == root)
        {
            return;
        }
        swap(datas[max], datas[root]);
        root = max;
        lchild = root * 2 + 1;
        rchild = root * 2 + 2;
    }
}
void heapSort(vector<int> &datas)
{
    int n = datas.size();
    for (int i = 0; i < n / 2; i++)
    {
        siftDown(datas, i, n);
    }
}

int main()//debug
{
    vector<int> arr = {2,3,8,3,42,1,3,5};
    heapSort(arr);
    for_each(arr.begin(),arr.end(),[](int a)
    {
        cout << a << " ";
    });
    return 0;
}