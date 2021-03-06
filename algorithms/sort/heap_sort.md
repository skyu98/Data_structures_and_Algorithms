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

## 二、排序
排序需要的是确定的大小关系，在大顶堆中，堆顶元素就是数组中最大的数，所以可以将其和最后的元素交换，再将前n-1个元素堆化；重复这个过程，整个数组就是有序的了。
```cpp
void sort(vector<int>& nums){
    int size = nums.size();
    while(size>1)
    {
        swap(nums, size, 1);
        --size;
        heapify(nums, size ,1);
    }
} 
```
### 时间复杂度
堆排序包括建堆和排序两个操作，建堆过程的时间复杂度是$ O(n)$，排序过程的时间复杂度是$ O(nlogn)$，所以，堆排序整体的时间复杂度是 $O(nlogn)$。

### 空间复杂度
在建堆和排序的过程中，都使用交换操作，所以只有常量级的额外空间，所以复杂度是O(1)。

### 稳定性
由于存在交换操作，有可能改变元素的相对顺序，所以不是稳定的排序方法。

## 三、实际应用场景
### 1.堆的应用一：优先级队列
一个堆就可以看作一个优先级队列。
* 往优先级队列中插入一个元素，就相当于往堆中插入一个元素；
* 从优先级队列中取出优先级最高的元素，就相当于取出堆顶元素。

#### （1）合并有序小文件
**假设我们有 100 个小文件，每个文件的大小是 100MB，每个文件中存储的都是有序的字符串。我们希望将这些 100 个小文件合并成一个有序的大文件。**

整体思路有点像归并排序中的合并函数（几个里面取最小的放进结果）。
我们从这 100 个文件中，各取第一个字符串，放入数组中，然后比较大小，把最小的那个字符串放入合并后的大文件中，并从数组中删除。我们再从这个小文件取下一个字符串，放到数组中，重新比较大小，并且选择最小的放入合并后的大文件，将它从数组中删除。依次类推，直到所有的文件中的数据都放入到大文件为止。这里我们用数组这种数据结构，来存储从小文件中取出来的字符串。每次从数组中取最小字符串，都需要循环遍历整个数组，显然，这不是很高效。
这里就可以用到优先级队列，也可以说是堆。我们将从小文件中取出来的字符串放入到小顶堆中，那堆顶的元素，也就是优先级队列队首的元素，就是最小的字符串。我们将这个字符串放入到大文件中，并将其从堆中删除。然后再从小文件中取出下一个字符串，放入到堆中。循环这个过程，就可以将 100 个小文件中的数据依次放入到大文件中。我们知道，删除堆顶数据和往堆中插入数据的时间复杂度都是 O(logn)，n 表示堆中的数据个数，这里就是 100。

#### (2) 高性能定时器
假设我们有一个定时器，定时器中维护了很多定时任务，每个任务都设定了一个要触发执行的时间点。定时器每过一个很小的单位时间（比如 1 秒），就扫描一遍任务，看是否有任务到达设定的执行时间。如果到达了，就拿出来执行。但是，这样每过 1 秒就扫描一遍任务列表的做法比较低效，主要原因有两点：第一，任务的约定执行时间离当前时间可能还有很久，这样前面很多次扫描其实都是徒劳的；第二，每次都要扫描整个任务列表，如果任务列表很大的话，势必会比较耗时。针对这些问题，我们就可以用优先级队列来解决。我们按照任务设定的执行时间，将这些任务存储在优先级队列中，队列首部（也就是小顶堆的堆顶）存储的是最先执行的任务。这样，定时器就不需要每隔 1 秒就扫描一遍任务列表了。它拿队首任务的执行时间点，与当前时间点相减，得到一个时间间隔 T。这个时间间隔 T 就是，从当前时间开始，需要等待多久，才会有第一个任务需要被执行。这样，定时器就可以设定在 T 秒之后，再来执行任务。从当前时间点到（T-1）秒这段时间里，定时器都不需要做任何事情。当 T 秒时间过去之后，定时器取优先级队列中队首的任务执行。然后再计算新的队首任务的执行时间点与当前时间点的差值，把这个值作为定时器执行下一个任务需要等待的时间。这样，定时器既不用间隔 1 秒就轮询一次，也不用遍历整个任务列表，性能也就提高了。

### 2.堆的应用二：利用堆求 Top K
我把这种求 Top K 的问题抽象成两类。一类是针对静态数据集合，也就是说数据集合事先确定，不会再变。另一类是针对动态数据集合，也就是说数据集合事先并不确定，有数据动态地加入到集合中。针对静态数据，如何在一个包含 n 个数据的数组中，查找前 K 大数据呢？我们可以维护一个大小为 K 的小顶堆，顺序遍历数组，从数组中取出数据与堆顶元素比较。如果比堆顶元素大，我们就把堆顶元素删除，并且将这个元素插入到堆中；如果比堆顶元素小，则不做处理，继续遍历数组。这样等数组中的数据都遍历完之后，堆中的数据就是前 K 大数据了。遍历数组需要 O(n) 的时间复杂度，一次堆化操作需要 O(logK) 的时间复杂度，所以最坏情况下，n 个元素都入堆一次，时间复杂度就是 O(nlogK)。针对动态数据求得 Top K。怎么理解呢？我举一个例子。一个数据集合中有两个操作，一个是添加数据，另一个询问当前的前 K 大数据。如果每次询问前 K 大数据，我们都基于当前的数据重新计算的话，那时间复杂度就是 O(nlogK)，n 表示当前的数据的大小。实际上，我们可以一直都维护一个 K 大小的小顶堆，当有数据被添加到集合中时，我们就拿它与堆顶的元素对比。如果比堆顶元素大，我们就把堆顶元素删除，并且将这个元素插入到堆中；如果比堆顶元素小，则不做处理。这样，无论任何时候需要查询当前的前 K 大数据，我们都可以立刻返回给他。

### 3.堆的应用三：利用堆求中位数
如果数据的个数是奇数，把数据从小到大排列，那第 $(n​+1)/2$ 个数据就是中位数（注意：假设数据是从 0 开始编号的）；如果数据的个数是偶数的话，那处于中间位置的数据有两个，第 $n/2$​​ 个和第 $(n​+1)/2$ 个数据，这个时候，我们可取两个数中靠前的那个，就是第 $n/2$​​ 个数据。对于一组静态数据，中位数是固定的，我们可以先排序，第 $n/2$​ 个数据就是中位数。每次询问中位数的时候，我们直接返回这个固定的值就好了。所以，尽管排序的代价比较大，但是边际成本会很小。
但是，如果我们面对的是动态数据集合，中位数在不停地变动，如果再用先排序的方法，每次询问中位数的时候，都要先进行排序，那效率就不高了。借助堆这种数据结构，我们不用排序，就可以非常高效地实现求中位数操作。
我们需要维护两个堆，一个大顶堆，一个小顶堆。大顶堆中存储前半部分数据，小顶堆中存储后半部分数据，且小顶堆中的数据都大于大顶堆中的数据。也就是说，如果有 n 个数据，n 是偶数，我们从小到大排序，那前 $n/2$​​ 个数据存储在大顶堆中，后 $n/2$​ 个数据存储在小顶堆中。这样，大顶堆中的堆顶元素就是我们要找的中位数。如果 n 是奇数，情况是类似的，大顶堆就存储 $(n​+1)/2$ 个数据，小顶堆中就存储 $n/2$​ 个数据。
我们前面也提到，数据是动态变化的，当新添加一个数据的时候，我们如何调整两个堆，让大顶堆中的堆顶元素继续是中位数呢？如果新加入的数据小于等于大顶堆的堆顶元素，我们就将这个新数据插入到大顶堆；否则，我们就将这个新数据插入到小顶堆。这个时候就有可能出现，两个堆中的数据个数不符合前面约定的情况：如果 n 是偶数，两个堆中的数据个数都是 $n/2$​​；如果 n 是奇数，大顶堆有  $(n​+1)/2$ 个数据，小顶堆有 $n/2$​ 个数据。这个时候，我们可以从一个堆中不停地将堆顶元素移动到另一个堆，通过这样的调整，来让两个堆中的数据满足上面的约定。

### 4.在实际开发中，为什么快速排序要比堆排序性能好？
* 1.堆排序数据访问的方式没有快速排序友好。

对于快速排序来说，数据是顺序访问的。而对于堆排序来说，数据是跳着访问的。 比如，堆排序中，最重要的一个操作就是数据的堆化。比如下面这个例子，对堆顶节点进行堆化，会依次访问数组下标是 1，2，4，8 的元素，而不是像快速排序那样，局部顺序访问，所以，这样对 CPU 缓存是不友好的。

* 2.对于同样的数据，在排序过程中，堆排序算法的数据交换次数要多于快速排序。

我们在讲排序的时候，提过两个概念，有序度和逆序度。对于基于比较的排序算法来说，整个排序过程就是由两个基本的操作组成的，比较和交换（或移动）。快速排序数据交换的次数不会比逆序度多。但是堆排序的第一步是建堆，建堆的过程会打乱数据原有的相对先后顺序，导致原数据的有序度降低。比如，对于一组已经有序的数据来说，经过建堆之后，数据反而变得更无序了。