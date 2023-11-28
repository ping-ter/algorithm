#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <stack>
using namespace std;
struct linknode
{
    int index;
    int weight; // 权图
    linknode(int index)
        : index(index) {}
    linknode(int index, int weight)
        : index(index), weight(weight) {}
};
struct node
{
    char data;
    list<linknode> link;
    node(char data)
        : data(data) {}
};

struct graph
{
    vector<node> nodes;
    bool direct; // 是否为有向图
    graph(int nodes_count, const vector<node> &nodes, bool direct)
        : nodes(nodes), direct(direct) {}

    void addEdge(int i, int j, int weight) // 权图
    {
        nodes[i].link.push_back(linknode(j, weight));
        if (!direct)
        {
            nodes[j].link.push_back(linknode(i, weight));
        }
    }
    void addEdge(int i, int j) // 非权图
    {
        nodes[i].link.push_back(linknode(j));
        if (!direct)
        {
            nodes[j].link.push_back(linknode(i));
        }
    }
    void print()
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << nodes[i].data << " link: ";
            for_each(nodes[i].link.begin(), nodes[i].link.end(), [&](linknode &now)
                     { cout << nodes[now.index].data << " "; });
            cout << endl;
        }
    }
    void topoOrder() // 拓扑排序
    {
        int n = nodes.size();
        vector<int> inDegree(n, 0); // 记录各点入度
        stack<int> sta;             // 辅助栈
        for_each(nodes.begin(), nodes.end(), [&](node &now)
                 {
            for(linknode& i : now.link)
            {
                inDegree[i.index]++;
            } }); // 统计各点入度

        for (int i = 0; i < n; i++)
        {
            if (inDegree[i] == 0)
            {
                sta.push(i); // 入度为0的点入栈
            }
        }

        while (!sta.empty())
        {
            int index = sta.top();
            sta.pop();
            cout << nodes[index].data << " ";
            for (linknode &i : nodes[index].link)
            {
                inDegree[i.index]--; // 减少入度,模拟删除边的操作
                if (inDegree[i.index] == 0)
                {
                    sta.push(i.index); // 入度为0的点入栈
                }
            }
        }
        cout << endl;
    }
    void dfs_in(vector<int> &traversaled, int index)
    {
        traversaled[index] = 1; // 标记为已访问
        for (linknode &i : nodes[index].link)
        {
            if (traversaled[i.index] == 0)
            {
                dfs_in(traversaled, i.index);
            }
        }
        cout << nodes[index].data << " ";
    }
    void re_topoOrder()
    {
        int n = nodes.size();
        vector<int> traversaled(n, 0);
        dfs_in(traversaled, 0);
        cout << endl;
    }
};

int main()
{
    graph topo(7, {'A', 'B', 'C', 'D', 'E', 'F', 'H'}, true);
    topo.addEdge(0, 1);
    topo.addEdge(0, 2);
    topo.addEdge(1, 3);
    topo.addEdge(2, 5);
    topo.addEdge(1, 4);
    topo.addEdge(1, 5);
    topo.addEdge(4, 6);
    topo.addEdge(5, 6);
    topo.print();
    topo.topoOrder();
    topo.re_topoOrder();
    return 0;
}