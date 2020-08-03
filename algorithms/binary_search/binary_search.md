# 学习数据结构与算法的一些笔记--*基础二分查找*

# 一、二分查找
二分查找针对的是一个有序的数据集合，查找思想有点类似分治思想。每次都通过跟区间的中间元素对比，将待查找的区间缩小为之前的一半，直到找到要查找的元素，或者区间被缩小为 0。
![search](search.jpg)
* 时间复杂度：每次缩短一半，复杂度为$O(logN)$.

# 二、二分查找的实现
## 迭代实现
```cpp
class solution{
public:
    int binarySearch(vector<int> nums, int val){
        int low = 0, high = nums.size()-1;
        // 1. 循环退出条件注意是 low<=high，而不是 low < high;
        // 因为如果val是low和high中的某一个，那么就会因为两者相等时退出循环而找不到目标值
        while(low <= high)
        {
            /*2.如果 low 和 high 比较大的话，两者之和可能会溢出。
            我们可以将这里的除以 2 操作转化成位运算 low+((high-low)>>1)。
            因为相比除法运算来说，计算机处理位运算要快得多。*/ 
            int mid = low + ((high - low)>>1);
            if(nums[mid] == val) return mid;
            // 3.如果直接写成 low=mid 或者 high=mid，就可能会发生死循环。
            if(nums[mid] > val)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            } 
        }
        return -1;
    }
};
```
## 递归实现
```cpp
class solution{
public:
    int _search(vector<int> nums, int low, int high, int val){
        if(low>high) return -1;

        int mid = low + ((high - low)>>1);
        if(nums[mid] == val) return mid;
        if(nums[mid] < val) return _search(nums, low, mid-1, val);
        else return _search(nums, mid+1, high, val);
    }

    int binarySearch(vector<int> nums, int val){
        return _search(nums, 0, nums.size()-1, val);
    }
};
```
# 三、二分查找应用场景的局限性
**首先，二分查找只能用在数据是通过顺序表来存储的数据结构上。**
如果你的数据是通过其他数据结构存储的，则无法应用二分查找。主要原因是二分查找算法需要按照下标随机访问元素。数组按照下标随机访问数据的时间复杂度是 O(1)，而链表随机访问的时间复杂度是 O(n)。所以，如果数据使用链表存储，二分查找的时间复杂就会变得很高。

**其次，二分查找针对的是有序数据。**
二分查找对这一点的要求比较苛刻，数据必须是有序的。如果数据没有序，我们需要先排序。前面章节里我们讲到，排序的时间复杂度最低是 O(nlogn)。所以，如果我们针对的是一组静态的数据，没有频繁地插入、删除，我们可以进行一次排序，多次二分查找。这样排序的成本可被均摊，二分查找的边际成本就会比较低。但是，如果我们的数据集合有频繁的插入和删除操作，要想用二分查找，要么每次插入、删除操作之后保证数据仍然有序，要么在每次二分查找之前都先进行排序。针对这种动态数据集合，无论哪种方法，维护有序的成本都是很高的。所以，二分查找只能用在插入、删除操作不频繁，一次排序多次查找的场景中。针对动态变化的数据集合，二分查找将不再适用.

**再次，数据量太小不适合二分查找。**
如果要处理的数据量很小，完全没有必要用二分查找，顺序遍历就足够了。只有数据量比较大的时候，二分查找的优势才会比较明显。不过，这里有一个例外。如果数据之间的比较操作非常耗时，不管数据量大小，都推荐使用二分查找。比如，数组中存储的都是长度超过 300 的字符串，如此长的两个字符串之间比对大小，就会非常耗时。我们需要尽可能地减少比较次数，而比较次数的减少会大大提高性能，这个时候二分查找就比顺序遍历更有优势。

**最后，数据量太大也不适合二分查找。**
二分查找的底层需要依赖数组这种数据结构，而数组为了支持随机访问的特性，要求内存空间连续，对内存的要求比较苛刻。

# 四、课后思考
## 1.如何编程实现“求一个数的平方根”？要求精确到小数点后 6 位。
```cpp
class solution{
public:
    double sqrt(double x){
        if(x < 0) return -1;
        if(x == 1 || x == 0) return x;
        double low, high, precision = 0.000001;
        if(x > 1) 
        {
            low  = 1;
            high = x;
        }
        else
        {
            low = x;
            high = 1;
        }

        while(low <= high )
        {
            double mid = low + ((high - low)>>1);
            if(abs(mid - x/mid) <= precision) return mid;
            if(mid < x/mid)
            {
                high = mid;
            }
            else low = mid;
        }
        return -1;
    }
};

```

## 2、如果数据使用链表存储，查找的时间复杂度是多少？
双链表：$O(n/2 + n/4 + ... + 1) = O(n)$ 
单链表：$O(n + n/2 + n/4 + ... + 1) = O(2n) = O(n)$ 。单链表还需遍历一次找到尾部。但是在遍历过程中就已经能找到目标值了。