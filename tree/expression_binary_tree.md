# 表达式二叉树

将表达式拆解开,运算符为节点,两个操作数为子树,即可构成表达式树

- 表达式树的叶节点为操作数,其余节点为运算符
- 表达式树的中根序列为中缀表达式
- 表达式树的后根序列为后缀表达式

## 表达式树的构建

### 关于c++处理数字字符混合的情况
当cin获取到一个非整形字符的时候，cin >> i 会返回false，并且会对cin对象做一个错误标记
只有使用 cin.clear() 清除错误标记后才能继续从缓冲区读取数据

[参考连接](https://blog.csdn.net/qq_41191055/article/details/115349012)

```c++
while (1)
{
    if (cin >> i)
    {
        // 获取到整型值
        ivec.push_back(i);
    }
    else
    {
        // 需要先清除错误标记
        cin.clear();
        // cin.get()会获取缓冲区中的第一个字符，注意，空格和回车也会读取。
        char t = cin.get();
        if (t == ' ')
        {
            // 如果获取到了空格，则跳过，获取下一个字符
            t = cin.get();
        }
        // 此时t已经是我们想要的字符了
        cvec.push_back(t);
    }
}


```

### 后缀表达式构建



### 中缀表达式构建


