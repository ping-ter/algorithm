#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
using namespace std;

namespace Mat_graph
{
    struct node
    {
        char data;
        node(char data)
            : data(data) {}
    };
    struct graph
    {
        vector<node> nodes;
        vector<vector<int>> adjMat;
        bool direct; // 是否为有向图
        graph(int nodes_count, const vector<node> &nodes, bool direct)
            : nodes(nodes), adjMat(nodes_count, vector<int>(nodes_count, 0)), direct(direct) {}

        void addEdge(int i, int j, int weight) // 权图
        {
            adjMat[i][j] = weight;
            if (!direct)
            {
                adjMat[j][i] = weight;
            }
        }
        void addEdge(int i, int j) // 非权图
        {
            adjMat[i][j] = 1;
            if (!direct)
            {
                adjMat[j][i] = 1;
            }
        }
        void print()
        {
            for (int i = 0; i < nodes.size(); i++)
            {
                for (int j = 0; j < nodes.size(); j++)
                {
                    cout << adjMat[i][j] << " ";
                }
                cout << endl;
            }
        }
        void BFS()
        {
            queue<int> que;
            int n = nodes.size();
            vector<int> v_travelsaled(n, 0);

            que.push(0);
            while (!que.empty())
            {
                int index = que.front();
                que.pop();
                if (v_travelsaled[index] == 1)
                {
                    continue;
                }
                v_travelsaled[index] = 1;
                cout << nodes[index].data << " ";
                for (int i = 0; i < n; i++) // 对于无向图,这里可以优化
                {
                    if (adjMat[index][i] != 0 && v_travelsaled[i] == 0)
                    {
                        que.push(i);
                    }
                }
            }
            cout << endl;
        }

        void DFS()
        {
            stack<int> sta;
            int n = nodes.size();
            vector<int> v_traversaled(n, 0);
            sta.push(0);
            while (!sta.empty())
            {
                int index = sta.top();
                sta.pop();
                if (v_traversaled[index] == 1)
                {
                    continue;
                }
                v_traversaled[index] = 1;
                cout << nodes[index].data << " ";
                for (int i = 0; i < n; i++)
                {
                    if (adjMat[index][i] != 0 && v_traversaled[i] == 0)
                    {
                        sta.push(i);
                    }
                }
            }
            cout << endl;
        }
    };

};

namespace List_graph
{
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
                         { cout << nodes[now.index].data << " "
                                << "w:" << now.weight << "  "; });
                cout << endl;
            }
        }
        void BFS()
        {
            queue<int> que;
            if (nodes.empty())
            {
                return;
            }
            vector<int> v_traversal(nodes.size(), 0); // 用来记录已经遍历过的图
            que.push(0);
            while (!que.empty())
            {
                int index = que.front();
                que.pop();
                if (v_traversal[index] == 1)
                {
                    continue;
                }
                v_traversal[index] = 1;
                cout << nodes[index].data << " ";
                for_each(nodes[index].link.begin(), nodes[index].link.end(),
                         [&](linknode now)
                         {
                             que.push(now.index);
                         });
            }
            cout << endl;
        }

        void DFS()
        {
            vector<int> v_travelsal(nodes.size(), 0);
            DFS_in(v_travelsal, 0);
            cout << endl;
        }

        void DFS_in(vector<int> &v_travelsal, int index)
        {
            if (v_travelsal[index] == 1)
            {
                return;
            }
            v_travelsal[index] = 1;
            cout << nodes[index].data << " ";
            for_each(nodes[index].link.begin(), nodes[index].link.end(), [&](linknode &now)
                     { DFS_in(v_travelsal, now.index); });
        }

        void DFS_noRecursion()
        {
            stack<int> sta;
            sta.push(0);
            vector<int> v_travelsal(nodes.size(), 0);

            while (!sta.empty())
            {
                int index = sta.top();
                sta.pop();
                if (v_travelsal[index] == 1)
                {
                    continue;
                    ;
                }
                v_travelsal[index] = 1;
                cout << nodes[index].data << " ";

                for_each(nodes[index].link.begin(), nodes[index].link.end(), [&](linknode &now)
                         { sta.push(now.index); });
            }
            cout << endl;
        }
        void Dijkstra(int index);
        void Dijkstra_better(int index);
    };
    void graph::Dijkstra(int index)
    {
        int n = nodes.size();
        const int INF = 0x3f3f3f3f;
        vector<int> dist(n, INF);
        vector<int> pre(n, -1);
        vector<int> S(n, 0);
        dist[index] = 0;

        auto check = [&]()
        {
            cout << "|index|";
            for (int i = 0; i < n; i++)
            {
                cout << i << "|";
            }
            cout << endl;
            cout << "|:---:|";
            for (int i = 0; i < n; i++)
            {
                cout << ":---:|";
            }
            cout << endl;
            cout << "|pre|";
            for (int i = 0; i < n; i++)
            {
                cout << pre[i] << "|";
            }
            cout << endl;
            cout << "|dist|";
            for (int i = 0; i < n; i++)
            {
                if (dist[i] != INF)
                {
                    cout << dist[i] << "|";
                }
                else
                {
                    cout << "INF|";
                }
            }
            cout << endl;
            cout << "|S|";
            for (int i = 0; i < n; i++)
            {
                cout << S[i] << "|";
            }
            cout << endl
                 << endl;
        }; // 打印算法执行过程

        auto findMin = [&]() -> int
        {
            int min_index = -1;
            int min = INF;
            for (int i = 0; i < n; i++)
            {
                if (S[i] == 0 && dist[i] < min)
                {
                    min_index = i;
                    min = dist[i];
                }
            }
            return min_index;
        };

        for (int i = 0; i < n; i++)
        {
            int now = findMin();
            if (now == -1)
            {
                return; // 图不连通,剩下的点源点都不可及,结束算法
            }
            S[now] = 1;
            for_each(nodes[now].link.begin(), nodes[now].link.end(), [&](linknode &a)
                     {
                if(S[a.index] == 0 && dist[now] + a.weight < dist[a.index])
                {
                    dist[a.index] = dist[now] + a.weight;
                    pre[a.index] = now;
                } }); // 只需要更新邻接的点
            check();
        }
    }
};

int main()
{
    using namespace List_graph;
    graph myfirst_graph(5, {'1', '2', '3', '4', '5'}, true);
    myfirst_graph.addEdge(0, 1, 3);
    myfirst_graph.addEdge(0, 4, 30);
    myfirst_graph.addEdge(1, 2, 25);
    myfirst_graph.addEdge(1, 3, 8);
    myfirst_graph.addEdge(2, 4, 10);
    myfirst_graph.addEdge(3, 2, 4);
    myfirst_graph.addEdge(3, 4, 12);

    myfirst_graph.print();
    myfirst_graph.Dijkstra(0);
    return 0;
}
