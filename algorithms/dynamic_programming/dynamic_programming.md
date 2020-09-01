# 学习算法的一些笔记--*动态规划*

动态规划的处理思想，和回溯法类似：**枚举所有的解，找到满足期望的解。**
其技巧是在于**如何有规律地枚举所有可能的解，避免遗漏；*并且能够利用DP Table优化穷举过程***。

## 适用场景
动态规划适合解决的问题的模型为**多阶段决策最优解模型。**
一般是用动态规划来解决最优问题。而解决问题的过程，需要经历多个决策阶段。每个决策阶段都对应着一组状态。然后我们寻找一组决策序列，经过这组决策序列，能够产生最终期望求解的最优值。

每个阶段，根据不同的情况和选择，会达到多种不同的状态，对应到递归树中，就是有很多不同的节点。我们把每一层重复的状态（节点）合并，只记录不同的状态，然后基于上一层的状态集合，来推导下一层的状态集合。

之所以可以这样求解，是因为动态规划的三个特征：
* 1. 最优子结构:
    我们可以通过子问题的最优解，推导出问题的最优解。如果我们把最优子结构，对应到我们前面定义的动态规划问题模型上，那我们也可以理解为，后面阶段的状态可以通过前面阶段的状态推导出来。

* 2. 无后效性:
    无后效性有两层含义：
        * 第一层含义是，在推导后面阶段的状态的时候，我们只关心前面阶段的状态值，不关心这个状态是怎么一步一步推导出来的。
        * 第二层含义是，某阶段状态一旦确定，就不受之后阶段的决策影响。

* 3. 重复子问题：
    不同的决策序列，到达某个相同的阶段时，可能会产生重复的状态。如果暴力穷举的话效率会极其低下，所以需要「备忘录」或者「DP table」来优化穷举过程，避免不必要的计算。

## 具体例子

### 322. Coin Change
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

>示例 1:
输入: coins = [1, 2, 5], amount = 11
输出: 3 
解释: 11 = 5 + 5 + 1

>示例 2:
输入: coins = [2], amount = 3
输出: -1

>说明:
你可以认为每种硬币的数量是无限的。

#### 思路：
首先，我们明确该问题满足动态规划的特征；
接下来，我们需要定义状态；此题中，状态dp[i]的意义应该为：amount为i时的最少硬币个数；那么base case为：dp[0] = 0;
接下来，我们需要分析，如何根据最优子结构，写出递归公式，也就是所谓的状态转移方程。
假设凑出amount金额的最少硬币个数为dp[amount]，那么显然:

```cpp
dp[amount] = min(1 + dp[amount - coins[0]], 1 + dp[amount - coins[1]], ... ,1 + dp[amount - coins[n-1]])
```

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        // base case
        dp[0] = 0;

        for(int i =0;i<dp.size();++i)
        {
            // 尝试解决每种硬币的子问题
            for(auto coin : coins)
            {
                // 子问题无解，直接跳过
                if(i - coin < 0) continue;
                // 状态转移方程
                dp[i] = min(dp[i], 1 + dp[i - coin]);
            }
        }

        return dp[amount] == amount + 1 ? -1 : dp[amount]; 
    }
};
```

时间复杂度：$O(N * amount)$；每个状态考虑一次，每次会考虑n种硬币；
空间复杂度：$O(amount)$；需要一个数组来储存信息。

### 416. Partition Equal Subset Sum(经典问题：0-1背包)
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
之前的回溯算法中，我们是使用排序，从大到小处理来节省算力。现在使用：
* 1.回溯+备忘录
* 2.动态规划

#### 1.回溯+备忘录
```cpp
class Solution {
public:
    vector<vector<int>> memo;

    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(auto i : nums)
        {
            sum += i;
        }
        
        if(sum % 2 != 0) return false;

        int target = sum / 2, idx = 0, cur = 0;

        memo = vector<vector<int>>(nums.size(), vector<int>(target + 1, -1));

        return solve(nums, idx, cur, target);
    }

    bool solve(vector<int>& nums, int idx, int cur, int target){
        if(cur == target) return true;   

        if(idx > nums.size() - 1) return false;

        if(memo[idx][cur] != -1) return memo[idx][cur];

        if(nums[idx] + cur <= target)
        {
            memo[idx][cur] = solve(nums, idx+1, cur + nums[idx], target) || solve(nums, idx+1, cur, target);
        }
        else
        {
            memo[idx][cur] = solve(nums, idx+1, cur, target);
        }
        
        return memo[idx][cur];
    }
};
```
#### 2.动态规划
这里状态dp[i][j]的含义为：对于前i(索引)个物品，能不能有某种选择，把容量为j的背包刚刚好装满。
那么base case为：
```cpp
dp[...][0] = 0;
dp[0][j==nums[0]] = 1;
```
状态转移方程为：
```cpp
if(j < nums[i]) dp[i][j] = dp[i-1][j];
else dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]];
```
具体代码如下：
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

        int target = sum / 2, idx = 0, cur = 0;

        vector<vector<int>>dp (nums.size(), vector<int>(target + 1, 0));

        if(nums[0] <= target) dp[0][nums[0]] = 1;
  
        for(int i = 1;i<nums.size();++i)
        {
            for(int j = 0;j<=target;++j)
            {

                if(j < nums[i]) dp[i][j] = dp[i-1][j];
                
                else dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]];
            }
        }
        return dp[nums.size()-1][target];
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