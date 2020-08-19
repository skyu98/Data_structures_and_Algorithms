# 学习算法的一些笔记--*分治算法*

分治算法的核心就是：**将原问题划分成 n 个规模较小，并且结构与原问题相似的子问题，递归地解决这些子问题，然后再合并其结果，就得到原问题的解。**

**分治算法是一种处理问题的思想，递归是一种编程技巧。**
实际上，分治算法一般都比较适合用递归来实现。分治算法的递归实现中，每一层递归都会涉及这样三个操作：
* 分解：将原问题分解成一系列子问题；
* 解决：递归地求解各个子问题，若子问题足够小，则直接求解；
* 合并：将子问题的结果合并成原问题。

分治算法能解决的问题，一般需要满足下面这几个条件：
* 原问题与分解成的小问题具有相同的模式；
* 原问题分解成的子问题可以独立求解，子问题之间没有相关性，这是分治算法跟动态规划的明显区别；
* 具有分解终止条件，也就是说，当问题足够小时，可以直接求解；
* 可以将子问题合并成原问题，而这个合并操作的复杂度不能太高，否则就起不到减小算法总体复杂度的效果了。

## 具体例子
### 剑指 Offer 51. 数组中的逆序对

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

示例 1:
>输入: [7,5,6,4]
输出: 5

#### 思路：
我们可以将数组分成前后两半 A1 和 A2，分别计算 A1 和 A2 的逆序对个数 K1 和 K2，然后再计算 A1 与 A2 之间的逆序对个数 K3。那数组 A 的逆序对个数就等于 K1+K2+K3。
如何快速计算出两个子问题 A1 与 A2 之间的逆序对个数呢？这里就要借助归并排序算法了：
归并排序中有一个非常关键的操作，就是将两个有序的小数组，合并成一个有序的数组。实际上，在这个合并的过程中，我们就可以计算这两个小数组的逆序对个数了。每次合并操作，我们都计算逆序对个数，把这些计算出来的逆序对个数求和，就是这个数组的逆序对个数了。
```cpp
class Solution {
public:
    int num;

    int reversePairs(vector<int>& nums) {
        num = 0;
        int len = nums.size();
        mergeCounting(nums, 0, len-1);
        return num;
    }

    void mergeCounting(vector<int>& nums, int p, int r){
        if(p>=r) return;
        int q = (p + r) / 2;
        mergeCounting(nums, p, q);
        mergeCounting(nums, q+1, r);
        merge(nums, p, q, r);
    }

    void merge(vector<int>& nums, int p, int q, int r){
        int idx_1 = p, idx_2 = q+1, idx = 0;
        vector<int> tmp(r - p +1);
        
        while(idx_1 <= q && idx_2 <= r)
        {
            if(nums[idx_1] <= nums[idx_2])
            {
                tmp[idx++] = nums[idx_1++];
            }
            else
            {
                num += (q - idx_1 + 1);
                tmp[idx++] = nums[idx_2++]; 
            }
        }

        while(idx_1 <= q)
        {
            tmp[idx++] = nums[idx_1++];
        }
        while(idx_2 <= r)
        {
            tmp[idx++] = nums[idx_2++];
        }

        for(int i =0;i<(r-p +1);++i)
        {
            nums[p + i] = tmp[i];
        }
    }
};
```
时间复杂度：O(nlogn)
空间复杂度：O(n)

### 315. Count of Smaller Numbers After Self
给定一个整数数组 nums，按要求返回一个新数组 counts。数组 counts 有该性质： ```counts[i]``` 的值是 ```nums[i]``` 右侧小于 ```nums[i]``` 的元素的数量。

示例：
>输入：nums = [5,2,6,1]
输出：[2,1,1,0] 

#### 思路：
总体思路和上一题一样，使用分治的思想：将一个数组分为A1，A2，那么
对于nums[i]，在整个数组中其逆序对的个数，等于A1中```counts[i1]``` + A2中```counts[i2]```。
需要注意的是:
* 1.因为这里进行了排序，每个元素的位置会改变，所以需要保存其最开始的下标，来存储其对应的逆序对个数。**这里不能用散列表，因为我们需要对每个数进行操作，我们希望这个下标是它的属性，否则在有重复元素的情况下会造成错误。**
* 2.这里判断的是针对每个元素的逆序对，所以我们是在移动右指针时计算。因为在右指针之前的元素，都是小于左指针的，所以这些是左指针对应的逆序对。

```cpp
class Solution {
public:
    vector<int> res;
    vector<pair<int, int>> numAndIndex;

    vector<int> countSmaller(vector<int>& nums) {
        int len = nums.size();
        res = vector<int>(len);
        for(int i=0;i<len;++i)
        {
            numAndIndex.push_back(make_pair(nums[i], i));
        }
        mergeCounting(numAndIndex, 0, len-1);
        return res;
    }

    void mergeCounting(vector<pair<int, int>>& numAndIndex, int p, int r){
        if(p>=r) return;
        int q = (p + r) / 2;
        mergeCounting(numAndIndex, p, q);
        mergeCounting(numAndIndex, q+1, r);
        merge(numAndIndex, p, q, r);
    }

    void merge(vector<pair<int, int>>& numAndIndex, int p, int q, int r){
        int idx_1 = p, idx_2 = q+1, idx = 0;
       vector<pair<int, int>>tmp(r - p +1);
        
        while(idx_1 <= q && idx_2 <= r)
        {
            if(numAndIndex[idx_1].first <= numAndIndex[idx_2].first)
            {
                
                int pos = numAndIndex[idx_1].second;
                res[pos] += (idx_2 - q - 1);
                tmp[idx++] = numAndIndex[idx_1++];
            }
            else
            {
                tmp[idx++] = numAndIndex[idx_2++]; 
            }
        }

        
        while(idx_1 <= q)
        {
            int pos = numAndIndex[idx_1].second;
            res[pos] += (idx_2 - q - 1);
            tmp[idx++] = numAndIndex[idx_1++];
        }
        while(idx_2 <= r)
        {
            tmp[idx++] = numAndIndex[idx_2++]; 
        }

        for(int i =0;i<(r-p+1);++i)
        {
            numAndIndex[p + i] = tmp[i];
        }
    }
};
```
时间复杂度：O(nlogn)
空间复杂度：O(n)

### 最近点对问题
在二维平面上的n个点中，如何快速的找出最近的一对点，就是最近点对问题。