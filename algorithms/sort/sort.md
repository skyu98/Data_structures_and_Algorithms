# 学习数据结构与算法的一些笔记--*排序（O（n^2）时间复杂度）*

## 一、排序方法与复杂度归类
（1）几种最经典、最常用的排序方法：冒泡排序、插入排序、选择排序、快速排序、归并排序、计数排序、基数排序、桶排序。
（2）复杂度归类
* 冒泡排序、插入排序、选择排序 O(n^2)
* 快速排序、归并排序 O(nlogn)
* 计数排序、基数排序、桶排序 O(n)

## 二、如何分析一个“排序算法”？
* ### 算法的执行效率
1. 最好、最坏、平均情况时间复杂度。
2. 时间复杂度的系数、常数和低阶。
3. 比较次数，交换（或移动）次数。
* ### 排序算法的稳定性
1. 稳定性概念：如果待排序的序列中存在值相等的元素，经过排序之后，相等元素之间原有的先后顺序不变。
2. 稳定性重要性：可针对对象的多种属性进行有优先级的排序。
3. 举例：给电商交易系统中的“订单”排序，按照金额大小对订单数据排序，对于相同金额的订单以下单时间早晚排序。用稳定排序算法可简洁地解决。先按照下单时间给订单排序，排序完成后用稳定排序算法按照订单金额重新排序。
* ### 排序算法的内存损耗
原地排序算法：特指空间复杂度是O(1)的排序算法。

## 三、冒泡排序
冒泡排序只会操作相邻的两个数据。每次冒泡操作都会对相邻的两个元素进行比较，看是否满足大小关系要求，如果不满足就让它俩互换。
```cpp
// 冒泡排序，a表示数组，n表示数组大小
class Solution{
public:
    void bubbleSort(int* a, int n) {
        if (n <= 1) return;
 
        for (int i = 0; i < n; ++i) 
        {
            // 提前退出冒泡循环的标志位
            bool flag = false;
            for (int j = 0; j < n - i - 1; ++j) 
            {
                if (a[j] > a[j+1]) 
                { // 交换
                    int tmp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = tmp;
                    flag = true;  // 表示有数据交换      
                }
            }
            if (!flag) break;  // 没有数据交换，提前退出
        }
    }
};
```
* #### 稳定性：冒泡排序是稳定的排序算法。
在冒泡排序中，只有交换才可以改变两个元素的前后顺序。为了保证冒泡排序算法的稳定性，当有相邻的两个元素大小相等的时候，我们不做交换，相同大小的数据在排序前后不会改变顺序，所以冒泡排序是稳定的排序算法。
* #### 空间复杂度：冒泡排序是原地排序算法。
* #### 时间复杂度：
1. 最好情况（满有序度）：O(n)。
2. 最坏情况（满逆序度）：O(n^2)。
3. 平均情况：
“有序度”和“逆序度”：对于一个不完全有序的数组，如4，5，6，3，2，1，有序元素对为3个（4，5），（4，6），（5，6），有序度为3，逆序度为12；对于一个完全有序的数组，如1，2，3，4，5，6，有序度就是n*(n-1)/2，也就是15，称作满有序度；逆序度=满有序度-有序度；冒泡排序、插入排序交换（或移动）次数=逆序度。
最好情况下初始有序度为n*(n-1)/2，最坏情况下初始有序度为0，则平均初始有序度为n*(n-1)/4，即交换次数为n*(n-1)/4，因交换次数<比较次数<最坏情况时间复杂度，所以平均时间复杂度为O(n^2)。

## 四、插入排序
插入排序将数组数据分成已排序区间和未排序区间。初始已排序区间只有一个元素，即数组第一个元素。在未排序区间取出一个元素插入到已排序区间的合适位置，直到未排序区间为空。
```cpp
class Solution{
public:
    void insertSort(int* a, int n) {
        if (n <= 1) return;
 
        for (int i = 1; i < n; ++i) 
        {
           int value = a[i];
           for(int j=i-1;j>=0;j--)
           {
               if(a[j]>value)
               {
                   a[j+1] = a[j];
               }
               else break;
           }
           a[j+1] = value;
        }
};
```
* #### 稳定性：插入排序是稳定的排序算法。
* #### 空间复杂度：插入排序是原地排序算法。
* #### 时间复杂度：
1. 最好情况：O(n)。
2. 最坏情况：O(n^2)。
3. 平均情况：O(n^2)（往数组中插入一个数的平均时间复杂度是O(n)，一共重复n次）。


## 五、选择排序
选择排序将数组分成已排序区间和未排序区间。初始已排序区间为空。每次从未排序区间中选出最小的元素插入已排序区间的末尾，直到未排序区间为空。
```cpp
class Solution{
public:
    void selectSort(int* a, int n){
        if (n<=1) return;

        for(int i=0;i<n;i++)
        {   
            min_idx = i;
            for(int j=i;j<n;j++)
            {
                if(a[j]<a[min_idx])
                {
                    min_idx = j;
                }
            }
            int temp = a[min_idx];
            a[min_idx] = a[i];
            a[i] = temp;
        }
    }
};
```
* #### 稳定性：选择排序不是稳定的排序算法。
* #### 空间复杂度：选择排序是原地排序算法。
* #### 时间复杂度：（都是O(n^2)）
1. 最好情况：O(n^2)。
2. 最坏情况：O(n^2)。
3. 平均情况：O(n^2)。


## 六、思考
* 选择排序和插入排序的时间复杂度相同，都是O(n^2)，在实际的软件开发中，为什么我们更倾向于使用插入排序而不是冒泡排序算法呢？
* 答：从代码实现上来看，冒泡排序的数据交换要比插入排序的数据移动要复杂，冒泡排序需要3个赋值操作，而插入排序只需要1个，所以在对相同数组进行排序时，冒泡排序的运行时间理论上要长于插入排序。