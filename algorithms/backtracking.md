# 学习算法的一些笔记--*回溯算法*

回溯的处理思想：**枚举所有的解，找到满足期望的解。**
其技巧是在于**如何有规律地枚举所有可能的解，避免遗漏和重复**。

我们把问题求解的过程分为多个阶段。每个阶段，我们都会面对一个岔路口，有多个选择，我们先随意选一条路走，当发现这条路走不通的时候（不符合期望的解），就回退到上一个岔路口，另选一种走法继续走。

## 具体例子

### 51. N-Queens
给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。

每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

示例:

>输入: 4   
输出: [
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],
>
>["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。

#### 思路：
我们把这个问题划分成 8 个阶段，依次将 8 个棋子放到第一行、第二行、第三行……第八行。在放置的过程中，我们不停地检查当前放法，是否满足要求。如果满足，则跳到下一行继续放置棋子；如果不满足，那就再换一种放法，继续尝试。

```cpp
class Solution {
public:
    vector<vector<string>> output;
    vector<int> result;
    int row, col, size;

    vector<vector<string>> solveNQueens(int n) {
        result = vector<int>(n);
        size = n;
        _solve(0);
        return output;
    }

    void _solve(int row){
        if(row == size)
        {
           printQueen(result);
        }
        for(int col=0;col<size;++col)
        {
            if(isOk(row, col))
            {
                result[row] = col;
                _solve(row + 1);
            }
        }
    }

    bool isOk(int row, int col){
        int left = col-1, right = col+1;
        for(int i = row - 1;i>=0;--i)
        {
            if(result[i] == col) return false;
            if(left >=0 && result[i] == left) return false;
            if(right < size && result[i] == right) return false;
            --left;
            ++right;
        }
        return true;
    }

    void printQueen(vector<int>& result){
        vector<string> tmp;
        string s;
        for(int row=0;row<size;++row)
        {
            s = "";
            for(col=0;col<size;++col)
            {
                if(result[row] == col)
                {
                   s += "Q";
                }
                else
                {
                    s += ".";
                }
            }
            tmp.push_back(s);
        }
        output.push_back(tmp);
    }
};
```
时间复杂度：最坏$O(n^{n+1})$；因为回溯法的本质就是穷举，所以时间复杂度相当高；
空间复杂度：O(n)；需要一个数组来储存放置信息。

### 经典问题：0-1背包
我们有一个背包，背包总的承载重量是 Wkg。现在我们有 n 个物品，每个物品的重量不等，并且不可分割。我们现在期望选择几件物品，装载到背包中。在不超过背包所能装载重量的前提下，如何让背包中物品的总重量最大？

#### 思路：

```cpp
class Solution{
public:
    int max_weight = 0;

    int findMaxWeight(vector<int> items, int capacity){
        int idx = 0, cur_weight = 0;
        solve(items, capacity, idx, cur_weight);
        return max_weight;
    }

    void solve(vector<int>& items, int capacity, int idx, int cur_weight){
        if(cur_weight == capacity || idx == items.size())
        {
            max_weight = cur_weight > max_weight ? cur_weight : max_weight;
        }

        solve(items, capacity, idx + 1, cur_weight);
        if(cur_weight + items[idx] <= w)
        {
            solve(items, capacity, idx+1, cur_weight + items[idx]);
        }
    }
};
```
时间复杂度：最坏O(2^n)
空间复杂度：O(1).

### 416. Partition Equal Subset Sum
给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

>示例 1:
输入: [1, 5, 11, 5]
输出: true
解释: 数组可以分割成 [1, 5, 5] 和 [11].
 
>示例 2:
输入: [1, 2, 3, 5]
输出: false
解释: 数组不能分割成两个元素和相等的子集.

#### 思路：
此题就是比较典型的0-1背包问题。对于每个数字，我们可以选择或者不选择。
需要注意的是，因为我们只需要找到一个数列，使其和为总和的一半，所以我们可以排序后，从最大的数字开始减起，节省一些算力。
```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(auto i : nums)
        {
            sum += i;
        }
        
        if(sum % 2 != 0) return false;

        sort(nums.begin(), nums.end());
        int cur = sum / 2, idx = nums.size() - 1;
        if(nums[idx] > cur) return false;

        return solve(nums, idx, cur);
    }

    bool solve(vector<int>& nums, int idx, int cur){
        if(cur == 0) return true;   

        if(idx < 0) return false;
        
        if(nums[idx] == cur) return true;   

        if(nums[idx] > cur)
        {
            return solve(nums, idx-1, cur);
        }
        else
        {
            return solve(nums, idx-1, cur - nums[idx]) || solve(nums, idx-1, cur);
        }
    }
};
```

### 10. Regular Expression Matching
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素

说明:

s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。

>示例 1:
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。

>示例 2:
输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。

>示例 3:
输入:
s = "ab"
p = ".\*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

>示例 4:
输入:
s = "aab"
p = "c\*a\*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。

>示例 5:
输入:
s = "mississippi"
p = "mis\*is\*p\*."
输出: false

#### 思路：
解题思路
* 1、如果p为空，s为空匹配，s非空不匹配；
* 2、s非空，p == s || p == '.'时第一个字符匹配；
* 3、(p+1) != ''，则递归判断剩下的是否匹配 first_match && isMatch(++s, ++p)
* 4、(p+1) == '*'，则有两种情况匹配：
    * a: *匹配0个字符，s匹配剩下的，即isMatch(s, p+2)
    * b: *匹配1个字符，继续用p匹配剩下的s，即first_match && isMatch(s+1, p)

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        return _match(s.data(), p.data());
    }

    bool _match(char* s, char* p){
        if(!*p) return !*s; // 这里注意，!p代表指针为空，!*p才代表*p == '\0'
        bool first_match = *s && (*s == *p || *p == '.');
        if(*(p+1) == '*')
        {
            return _match(s, p+2) || (first_match && _match(s+1, p));
        }
        else
        {
            return first_match && _match(s+1, p+1);
        }
    }
};
```

## 主要解题框架
``` python
result = []
def backtrack(路径, 选择列表):
    if 满足结束条件:
        result.add(路径)
        return
    
    for 选择 in 选择列表:
        做选择
        backtrack(路径, 选择列表)
        撤销选择
```