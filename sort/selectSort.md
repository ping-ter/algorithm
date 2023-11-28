# 选择排序

简单排序的思想是从序列中挑选元素,放到它应该在的位置

## 简单选择排序

简单选择排序即每次从未排序序列中选择一个最小的元素,放入有序序列的末尾,最终使得整个序列变成有序序列

算法实现很简单:

```c++
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
```

## 堆排序