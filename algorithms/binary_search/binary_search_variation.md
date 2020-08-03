# 学习数据结构与算法的一些笔记--*二分查找的变体问题*

基础的二分查找中，数组中的数据连续有序且无重复。当数组中有重复的数据时，将会有一系列的变体问题。但是核心思想没有改变：**通过比较mid和目标值的关系，来确定目标值所在的区间。**

# 变体一：查找第一个值等于给定值的元素
```cpp
class solution{
public:
    int binartSearch(vector<int> nums, int val){
        int low = 0, high = nums.size() -1;
        while(low<=high)
        {
            int mid = low + ((high - low)>>1);
            if(nums[mid] == val)
            {
                /*如果 mid 等于 0，那这第一个元素，那它肯定是我们要找的；
                如果 mid 不等于 0，但前一个元素不等于 value，
                那也说明 a[mid]就是第一个值等于给定值的元素。*/
                if(mid == 0 || nums[mid-1] != val)
                {
                    return mid;
                }
                high = mid -1;
            }
            else if(nums[mid] > val)
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

# 变体二：查找最后一个值等于给定值的元素
```cpp
class solution{
public:
    int binartSearch(vector<int> nums, int val){
        int low = 0, high = nums.size() -1;
        while(low<=high)
        {
            int mid = low + ((high - low)>>1);
            if(nums[mid] == val)
            {
                /*如果 mid 是最后一个元素，那它肯定是我们要找的；
                如果 mid 不是最后，但后一个元素不等于 value，
                那也说明 a[mid]就是最后一个值等于给定值的元素。*/
                if(mid == nums.size()-1 || nums[mid+1] != val)
                {
                    return mid;
                }
                low = mid + 1;
            }
            else if(nums[mid] > val)
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

# 变体三：查找第一个大于等于给定值的元素
```cpp
class solution{
public:
    int binartSearch(vector<int> nums, int val){
        int low = 0, high = nums.size() -1;
        while(low<=high)
        {
            int mid = low + ((high - low)>>1);
            if(nums[mid] >= val)
            {
                /*如果 mid 是第一个元素，那它肯定是我们要找的；
                如果 mid 不是第一个，但前一个元素小于 value，
                那也说明 a[mid]就是第一个值大于等于给定值的元素。*/
                if(mid == 0 || nums[mid-1] < val)
                {
                    return mid;
                }
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

# 变体四：查找最后一个小于等于给定值的元素
```cpp
class solution{
public:
    int binartSearch(vector<int> nums, int val){
        int low = 0, high = nums.size() -1;
        while(low<=high)
        {
            int mid = low + ((high - low)>>1);
            if(nums[mid] <= val)
            {
                /*如果 mid 是最后一个元素，那它肯定是我们要找的；
                如果 mid 不是最后一个，但后一个元素大于 value，
                那也说明 a[mid]就是最后一个值小于等于给定值的元素。*/
                if(mid == nums.size()-1 || nums[mid+1] > val)
                {
                    return mid;
                }
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }   
        }
        return -1;
    }
};
```