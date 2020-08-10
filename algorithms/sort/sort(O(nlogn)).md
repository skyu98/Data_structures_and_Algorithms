# 学习数据结构与算法的一些笔记--*排序（O（nlogn）时间复杂度）*

继续上一部分的排序算法，此篇学习的是归并排序和快速排序。

## 一、归并排序
归并排序使用的就是**分治思想**。
要排序一个数组，先把数组从中间分成前后两部分，然后对前后两部分分别排序，再将排好序的两部分合并在一起，整个数组就有序了。
分治算法一般都是用递归来实现的。**分治是一种解决问题的处理思想，递归是一种编程技巧。**

### 归并排序的递归伪代码
```cpp
// 递推公式
merge_sort(p...r) = merge(merge_sort(p...q), merge_sort(q+1...r)); // q = (p + r)/2

// 终止条件
p >= r;
```
### 归并排序C++实现
```cpp
class Solution{
public:
    void merge_sort(int* a, int start, int end){
        if(start>=end) return;

        int mid = (start + end)/2;
        merge_sort(a, start, mid);
        merge_sort(a, mid+1, end);
        merge(a, start, mid, end);
    }

    void merge(int* a, int start, int mid, int end){
        int len = end - start + 1;
        int* tmp = new int[len];

        int i=start, j=mid + 1, k=0;
        while(i<=mid && j<=end)
        {
            if(a[i]<=a[j])
            {
                tmp[k] = a[i];
                i++;
            }
            else
            {
                tmp[k] = a[j];
                j++;
            }
            k++;
        }

        int rest_start = (i <= mid) ? i : j;
        int rest_end = (i <= mid) ? mid : end;
        while(rest_start <= rest_end)
        {
            tmp[k] = a[rest_start];
            k++；
            rest_start++;
        }

        for(i=0;i<len;i++)
        {
            a[start+i] = tmp[i];
        }

        delete tmp;
    }

    int* MergeSort(int* a, int n){
        if(n<=1) return a;
        merge_sort(a, 0, n-1);
        return a;
    }
}；
```
* #### 稳定性：归并排序是稳定的排序算法。
在归并排序中，merge()时，只要把相同的元素按原有的顺序放入tmp[]，该方法就是稳定的。
* #### 空间复杂度：归并排序不是原地排序算法。(O(n))
* #### 时间复杂度：
```cpp
T(1) = C；   n=1时，只需要常量级的执行时间，所以表示为C。

T(n) = 2*T(n/2) + n
     = 2*(2*T(n/4) + n/2) + n = 4*T(n/4) + 2*n
     = 4*(2*T(n/8) + n/4) + 2*n = 8*T(n/8) + 3*n
     = 8*(2*T(n/16) + n/8) + 3*n = 16*T(n/16) + 4*n
     ......
     = 2^k * T(n/2^k) + k * n
     ......
```
当 T(n/2^k)=T(1) 时，也就是 n/2^k=1，我们得到 k=log2n 。我们将 k 值代入上面的公式，得到 T(n)=Cn+nlog2n。所以快速排序的时间复杂度是 O(nlogn)。

## 二、快速排序
如果要排序数组中下标从p到r之间的一组数据：
* 1.选择p到r之间的任意一个数据作为pivot（分区点）；
* 2.遍历p到r之间的数据，将小于pivot的放到左边，将大于pivot的放到右边，将pivot放到中间；
* 3.递归排序下标从p到q-1之间的数据和下标从q+1到r之间的数据，直到区间缩小为1。

### 快速排序的递归伪代码
```cpp
// 递推公式
quick_sort(p...r) = quick_sort(p...q-1) + quick_sort(q...r)); // q is pivot

// 终止条件
p >= r;
```
### 快速排序C++实现
```cpp
class Solution{
public:
    int partition(int* a, int start, int end){
        int pivot = a[end], i = start;

        for(int j=start;j<end;j++)
        {
            if(a[j] < pivot)
            {
                int tmp = a[j];
                a[j] = a[i];
                a[i] = tmp;
                i++;
            }
        }
        int tmp = pivot;
        a[end] = a[i];
        a[i] = tmp;

        return i;
    }

    void quick_sort(int* a, int start, int end){
        if(start>=end) return;

        q = partition(a, start, end);
        quick_sort(a, start, q-1);
        quick_sort(a, q, end); 
    }

    int* QuickSort(int* a, int n){
        if(n <= 1) return a;

        quick_sort(a, 0, n-1);
        return a;
    }
};
```
* #### 稳定性：快速排序不是稳定的排序算法。
在快速排序中，partition()时，由于涉及到交换操作，相同的元素可能不会按原有的顺序存放，因此该方法不是稳定的。
* #### 空间复杂度：快速排序是原地排序算法。
* #### 时间复杂度：
1. 最好情况：如果每次分区操作，都能正好**把数组分成大小接近相等的两个小区间**，那么：
```cpp
T(1) = C；   n=1时，只需要常量级的执行时间，所以表示为C。

T(n) = 2*T(n/2) + n
     = 2*(2*T(n/4) + n/2) + n = 4*T(n/4) + 2*n
     = 4*(2*T(n/8) + n/4) + 2*n = 8*T(n/8) + 3*n
     = 8*(2*T(n/16) + n/8) + 3*n = 16*T(n/16) + 4*n
     ......
     = 2^k * T(n/2^k) + k * n
     ......
```
当 T(n/2^k)=T(1) 时，也就是 n/2^k=1，我们得到 k=log2n 。我们将 k 值代入上面的公式，得到 T(n)=Cn+nlog2n。所以归并排序的时间复杂度是 O(nlogn)。

2. 最坏情况：当初始数组已经有序时，那么每次获得的两个分区都是不均衡的，需要进行大约 n 次分区操作，每次分区平均要扫描大约 n/2 个元素。这种情况下，快排的时间复杂度就从 O(nlogn) 退化成了 O(n^2)。

3:平均情况：结论：T(n) 在大部分情况下的时间复杂度都可以做到 O(nlogn)，只有在极端情况下，才会退化到 O(n2)。