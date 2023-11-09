#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct node
{
    char data;
    node *leftChild;
    node *rightChild;
    node(char data)
        : data(data), leftChild(nullptr), rightChild(nullptr) {}
    static node* create()
    {
        char data;
        cin >> data;
        if(data == '0')
        {
            return 0;
        }
        node* newnode = new node(data);
        newnode->leftChild = create();
        newnode->rightChild = create();
        return newnode;
    }
    static node* create(char*,char*,char*)
    {
        
    }
};

struct binary_tree
{
    node *root;
    void preorder();
    void inorder();
    void postorder();
    void preorder2();
    void create()
    {
        root = node::create();
    }
    binary_tree(){}
    binary_tree(char*,char*);
};


void binary_tree::preorder()
{
    stack<node *> sta;
    sta.push(root);
    while (!sta.empty())
    {
        node *nownode = sta.top();
        if (nownode != nullptr)
        {
            cout << nownode->data << " ";
            sta.pop();
            sta.push(nownode->rightChild);
            sta.push(nownode->leftChild); // 后进先出
        }
        else
        {
            sta.pop();
        }
    }
    cout << endl;
}
void binary_tree::preorder2()
{
    stack<node *> sta;
    sta.push(root);
    while (!sta.empty())
    {
        node *nownode = sta.top();
        sta.pop();
        while (nownode != nullptr)
        {
            cout << nownode->data << " ";
            sta.push(nownode->rightChild);
            nownode = nownode->leftChild;
        }
    }
}
void preorder(node *nownode)
{
    if (nownode == nullptr)
    {
        return;
    }
    cout << nownode->data << " ";
    preorder(nownode->leftChild);
    preorder(nownode->rightChild);
}

void inorder(node *nownode)
{
    if (nownode == nullptr)
    {
        return;
    }
    inorder(nownode->leftChild);
    cout << nownode->data << " ";
    inorder(nownode->rightChild);
}

void binary_tree::inorder()
{
    stack<node *> sta;
    node *nownode = root;
    while (1)
    {
        while (nownode != nullptr)
        {
            sta.push(nownode);
            nownode = nownode->leftChild; // 沿左侧通路依次入栈
        }
        if (sta.empty())
        {
            return;
        }
        nownode = sta.top();
        sta.pop();
        cout << nownode->data << " ";
        nownode = nownode->rightChild; // 访问一个节点后,访问其右子树
    }
}

void postorder(node *nownode)
{
    if (nownode == nullptr)
    {
        return;
    }
    postorder(nownode->leftChild);
    postorder(nownode->rightChild);
    cout << nownode->data << " ";
}

int main()
{
    binary_tree tree;
    tree.root = new node('A');

    tree.root->leftChild = new node('B');
    tree.root->rightChild = new node('E');

    tree.root->leftChild->rightChild = new node('C');

    tree.root->leftChild->rightChild->leftChild = new node('D');

    tree.root->rightChild->leftChild = new node('F');

    // inorder(tree.root);
    tree.inorder();

    tree.create();
    tree.preorder();
    tree.inorder();
    return 0;
}