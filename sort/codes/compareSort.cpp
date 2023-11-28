#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int> &datas)
{
    int n = datas.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (datas[i] < datas[j])
            {
                int temp = datas[i];
                datas[i] = datas[j];
                datas[j] = temp;
            }
        }
    }
}