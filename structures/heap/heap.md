# 学习数据结构与算法的一些笔记--*堆（概念和特点）*

# 一、堆的定义
堆是一种特殊的树。
* 1.堆是一个完全二叉树；
* 2.堆的每个节点的值都必须大于等于（小于等于）其左右节点的值。

前面介绍过，用数组来储存**完全二叉树**是很节省空间的，因为我们不需要存储左右子节点的指针，单纯地通过数组的下标，就可以找到一个节点的左右子节点和父节点。

|nums| *null*|7|6|4|3|2|1|
|--|--|--|--|--|--|--|--|
|index|0|1|2|3|4|5|6|

对于上面的数组，数组中下标为$ i $的节点的左子节点，就是下标为$ i∗2 $的节点，右子节点就是下标为$ i∗2+1 $的节点，父节点就是下标为$ 2i​ $的节点。

# 二、堆的基本操作
对一个堆进行任何的操作，我们都需要保证操作之后堆的两个特性不变。
## 1.插入
往堆中插入一个元素，要保证它还是**完全二叉树**很简单，只需要在数组末尾添加该元素；重点是在于如何通过某种调整，保证其大小关系，这种调整叫做**堆化（heapify）**。

在一个大顶堆中，子节点的值要比父节点小。我们让新插入的节点与父节点对比大小。如果不满足子节点小于等于父节点的大小关系，就互换两个节点。一直重复这个过程，直到父子节点之间满足规定的大小关系。
```cpp
class heap{
private:
    vector<int> tree;
    int capacity;
    int count;

    void swap(vector<int> v, int p, int q){
        int tmp = v[p];
        v[p] = v[q];
        v[q] = tmp;
    }

public:
    heap(int n) : capacity(n), count(0) {
        vector<int> tree (capacity + 1);
    }

    void insert(int val){
        if(count >= capacity) return;
        ++count;

        tree.push_back(val);
        int idx = count;
        while(idx / 2 > 0  && tree[idx] > tree[idx / 2])// 自下往上堆化
        {
            swap(tree, idx, idx / 2);
            idx /= 2;
        }
    }

};
```
## 2.删除*堆顶元素*
假设我们构造的是大顶堆，当删除堆顶元素之后，就需要把第二大的元素放到堆顶，那第二大元素肯定会出现在左右子节点中。然后我们再迭代地删除第二大节点，以此类推，直到叶子节点被删除。不过这种方法，由于其删除的路径不可控，有可能会造成数组空洞，使得最终堆化出来的堆并不满足完全二叉树的特性。

为了避免这种情况出现，还是要使删除路径可控。
因此，我们删除堆顶元素，把最后一个节点放到堆顶，然后利用同样的对比方法，并且重复进行这个过程，直到父子节点之间满足大小关系为止。
这就是从上往下的堆化方法。因为移除的是数组中的最后一个元素，而在堆化的过程中，都是交换操作，不会出现数组中的“空洞”，所以这种方法堆化之后的结果，肯定满足完全二叉树的特性。

```cpp
int removeTop(){
    if(count < 1) return -1;
    tree[1] = tree[count];
    --count;

    heapify(tree, count, 1);
}

void heapify(vector<int> tree, int count, int idx){
    while(1)
    {
        int maxPos = idx;
        if( 2* idx <= count && tree[maxPos] < tree[2*idx]) maxPos = 2*idx;
        if( 2* idx + 1 <= count && tree[maxPos] < tree[2*idx + 1]) maxPos = 2*idx + 1;
        if( maxPos == idx) break;
        swap(tree, idx, maxPos);
        idx = maxPos;
    }
}
```

## 3.插入一个元素和删除堆顶元素的时间复杂度
一个包含 n 个节点的完全二叉树，树的高度不会超过$log_2^​n$。堆化的过程是顺着节点所在路径比较交换的，所以堆化的时间复杂度跟树的高度成正比，也就是$O(logn)$。插入数据和删除堆顶元素的主要逻辑就是堆化，所以，往堆中插入一个元素和删除堆顶元素的时间复杂度都是$ O(logn)$。