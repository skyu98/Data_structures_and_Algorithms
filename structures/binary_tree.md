# 学习数据结构与算法的一些笔记--*树（概念和特点）*

## 一、树
1.树的常用概念
* 根节点、叶子节点、父节点、子节点、兄弟节点，还有节点的高度、深度以及层数，树的高度。

2.概念解释
* 节点的高度：节点到叶子节点的最长路径所包含的边数
* 节点的深度：根节点到节点的路径所包含的边数
* 节点的层数：节点的深度+1（根节点的层数是1）
* 树的高度：等于根节点的高度
## 二、二叉树
1.概念
①什么是二叉树？
* 每个节点最多只有2个子节点的树，这两个节点分别是左子节点和右子节点。

②什么是满二叉树？
* 除了叶子节点外，每个节点都有左右两个子节点，这种二叉树叫做满二叉树。

③什么是完全二叉树？
* 与满二叉树的前n个节点一一对应的二叉树叫做完全二叉树（叶子节点都在最底下两层，最后一层叶子节都靠左排列，并且除了最后一层，其他层的节点个数都要达到最大）。


2.完全二叉树的存储
①链式存储
* 每个节点由3个字段，其中一个存储数据，另外两个是指向左右子节点的指针。这种存储方式比较常用，大部分二叉树代码都是通过这种方式实现的。

②顺序存储
* 用数组来存储，对于完全二叉树，如果节点X存储在数组中的下标为i，那么它的左子节点的存储下标为2*i，右子节点的下标为2*i+1，反过来，下标i/2位置存储的就是该节点的父节点。注意，根节点存储在下标为1的位置。完全二叉树用数组来存储是最省内存的方式。

3.二叉树的遍历
①前序遍历：
* 对于树中的任意节点来说，先打印这个节点，然后再打印它的左子树，最后打印它的右子树。
```cpp
前序遍历的递推公式：
preOrder(r) = print r->preOrder(r->left)->preOrder(r->right);

class Solution{
public:
    vector<int> res;

    void preOrder(Node* root, vector<int> res)
    {
        if(root == NULL) return;
        res.push_back(root->val);
        preOrder(root->left);
        preOrder(root->right);
    }
};
```
②中序遍历：
* 对于树中的任意节点来说，先打印它的左子树，然后再打印它的本身，最后打印它的右子树。
```cpp
中序遍历的递推公式：
inOrder(r) = inOrder(r->left)->print(r)->inOrder(r->right);

class Solution{
public:
    vector<int> res;

    void inOrder(Node* root, vector<int> res)
    {
        if(root == NULL) return;
        inOrder(root->left);
        res.push_back(root->val);
        inOrder(root->right);
    }
};
```
③后序遍历：
* 对于树中的任意节点来说，先打印它的左子树，然后再打印它的右子树，最后打印它本身。
```cpp
后序遍历的递推公式：
postOrder(r) = postOrder(r->left)->postOrder(r->right)->print r

class Solution{
public:
    vector<int> res;

    void postOrder(Node* root, vector<int> res)
    {
        if(root == NULL) return;
        postOrder(root->left);
        postOrder(root->right);
        res.push_back(root->val);
    }
};
```
* 时间复杂度：3种遍历方式中，每个节点最多会被访问2次，所以时间复杂度是O(n)。

三、思考
1.给定一组数据，比如1，3，5，6，9，10.你来算算，可以构建出多少种不同的二叉树？

2.如何用循环实现二叉树的遍历？
* 采用队列来辅助实现广度优先遍历：
```cpp
class Solution{
public:
    int BFS(Node* root){
        if(root == NULL) return -1;

        queue<Node*> q;
        unordered_map<Node, int> visited; // 在树结构中没有必要，因为可以确定不存在环

        q.push(root);
        visited[Node] = 1;

        while(!q.empty())
        {
            int size= q.size();
            for(int i=0;i<size;i++)
            {
                int cur = q.front();
                q.pop()
                std::cout << cur->val << endl; 
                if(cur->left != NULL && visited[cur->left] != 1)
                {
                    q.push(cur->left); 
                    visited[cur->left] = 1;
                }
                if(cur->right != NULL && visited[cur->right] != 1)
                {
                    q.push(cur->right); 
                    visited[cur->right] = 1;
                }
            }
        }
        return 0;
    } 
};
```