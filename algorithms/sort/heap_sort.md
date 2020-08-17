# 学习数据结构与算法的一些笔记--*堆排序（O（nlogn）时间复杂度*

借助于堆这种数据结构实现的排序算法，就叫做堆排序。
堆排序的时间复杂度非常稳定，是 O(nlogn)，并且还是原地排序算法。
我们可以把堆排序的过程大致分解成两个大的步骤，**建堆**和**排序**。

## 1.建堆
我们首先将数组原地建成一个堆。所谓“原地”就是，不借助另一个数组，就在原数组上操作。
建堆的过程，有两种思路。

### 思路一：不断插入新元素，从下到上堆化
第一种是借助在堆中插入一个元素的思路。尽管数组中包含 n 个数据，但是可以假设，起初堆中只包含一个数据，就是下标为 1 的数据。然后，调用插入操作，将下标从 2 到 n 的数据依次插入到堆中。
```cpp
private:
    void swap(vector<int> v, int p, int q){
        int tmp = v[p];
        v[p] = v[q];
        v[q] = tmp;
    }

public:
    void insert(vector<int>& nums, int idx){
        while((idx - 1) / 2 >= 0  && nums[idx] > nums[(idx-1) / 2])// 自下往上堆化
        {
            swap(tree, idx, (idx -1)/ 2);
            idx = (idx -1)/ 2;
        }
    }

    void buildHeap(vector<int> nums){
        if(nums.size()<=1) return; 
        for(int i = 1;i<nums.size();++i)
        {   
            insert(nums, i);
        }
    }
};
```

### 思路二：从最后一个非叶子节点开始，从上到下堆化
第二种实现思路，跟第一种截然相反，第二种实现思路，是从后往前处理数组，并且每个数据都是从上往下堆化。
```cpp
private:
    void swap(vector<int>& v, int p, int q){
        int tmp = v[p];
        v[p] = v[q];
        v[q] = tmp;
    }

public:
    void buildHeap(vector<int> nums){
        if(nums.size()<=1) return; 
        for(int i = (nums.size()-2)/2;i>=0;--i)
        {   
            heapify(nums, nums.size(), i);
        }
    }

    void heapify(vector<int>& nums, int n, int idx){
        while(1)
        {
            int maxPos = idx;
            if( (2* idx +1) <= n-1 && nums[maxPos] < nums[2*idx + 1]) maxPos = 2*idx + 1;
            if( (2* idx + 2) <= n-1 && num[maxPos] < nums[2*idx + 2]) maxPos = 2*idx + 2;
            if( maxPos == idx) break;
            swap(nums, idx, maxPos);
            idx = maxPos;
        }
    }
```
在这段代码中，我们对下标从$(n-2)/2$​开始到 1 的数据进行堆化，下标是$n/2$ 到$ n-1 $的节点是叶子节点，我们不需要堆化。

### 建堆的时间复杂度
表面上，由于我们堆化一次是$O(logn)$，总共对n/2个节点进行堆化，所以总的复杂度是O(nlogn)；
但是实际上，需要堆化的节点从倒数第二层开始。每个节点堆化的过程中，需要比较和交换的节点个数，跟这个节点的高度 k 成正比。所以，假设根节点的高度是h，那么：

$$T = 1*h + 2^1 * (h-1) + ... + 2^{h-1} * 1$$
$$2T = 2*h + 2^2 * (h-1) + ... + 2^h * 1$$

所以，两式相减：

$$T = -h + 2^1 + 2^2 + ... + 2^h = 2^{h+1} - h -2$$

由于$h=log_2{n}$，得到$T = 2n - log_2n -2$，所以时间复杂度为O(n)。

