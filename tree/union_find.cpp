#include <iostream>
#include <array>
#include <string>
#include <stack>
using namespace std;
struct union_find
{
    array<char, 256> father;
    array<int, 256> rank;
    // 节点的父亲数组
    union_find()
    {
        fill(father.begin(), father.end(), 0); // 初始化成0
        fill(rank.begin(), rank.end(), 0);     // 初始化成0
    }
    void make_set(char x);
    void union_set(char x, char y);
    char find_set(char x);
};

void union_find::make_set(char x)
{
    father[x] = 0; // 为x构建一个单节点的树
    rank[x] = 0;
}

char union_find::find_set(char x)
{
    char p = x;
    stack<char> sta;
    while (father[p] != 0)
    {
        sta.push(p);
        p = father[p];
    }
    while (!sta.empty())
    {
        father[sta.top()] = p;
        sta.pop();
    }
    return p;
}

void union_find::union_set(char x, char y)
{
    // father[find_set(x)] = find_set(y);
    char fx = find_set(x), fy = find_set(y);
    if (fx == fy)
    {
        return; // 已经在同一集合了,不合并
    }
    if (rank[fx] > rank[fy])
    {
        father[fy] = fx; // 树高没增加,秩不变
    }
    else
    {
        father[fx] = fy;
        if (rank[fx] == rank[fy])
        {
            rank[fy]++; // 如果秩相等,那么根的秩加一
        }
    }
}

int main()
{
    union_find aset;
    string str = "1abexp";
    for (char i : str)
    {
        aset.make_set(i);
    }

    aset.union_set('1', 'a');
    aset.union_set('e', 'x');
    aset.union_set('b', 'p');
    aset.union_set('p', 'x');

    for (char i : str)
    {
        cout << i << " in " << aset.find_set(i) << "  father: " << aset.father[i] << endl;
    }
    return 0;
}
