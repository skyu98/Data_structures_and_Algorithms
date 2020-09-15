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
时间复杂度：$O(n*target)$。每种状态计算一次。
空间复杂度：$O(n*target)$。储存每种状态。


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
时间复杂度：$O(n*target)$。每种状态计算一次。
空间复杂度：$O(n*target)$。储存每种状态。

**这说明，带备忘录的回溯算法，其效率和动态规划相同。**


### 518.Coin Change 2(完全背包问题)
给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。 

>示例 1:
输入: amount = 5, coins = [1, 2, 5]
输出: 4
解释: 有四种方式可以凑成总金额:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1

>示例 2:
输入: amount = 3, coins = [2]
输出: 0
解释: 只用面额2的硬币不能凑成总金额3。

>示例 3:
输入: amount = 10, coins = [10] 
输出: 1
 

>注意:你可以假设：
0 <= amount (总金额) <= 5000
1 <= coin (硬币面额) <= 5000
硬币种类不超过 500 种
结果符合 32 位符号整数

#### 思路：
完全背包问题和经典0-1背包问题的唯一区别是：完全背包每个物品是无限的，而不是只有一个。
这里状态dp[i][j]的含义为：只用前i个硬币，对于amount = j，能刚好凑出amount的方式总数。
那么base case为：
```cpp
dp[0][j % coins[0] == 0] = 1;
dp[...][0] = 1;
```
状态转移方程为：
```cpp
if(j > coins[i]) dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]];
else dp[i][j] = dp[i-1][j];
```
```cpp
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        if(amount == 0) return 1;
        if(coins.size() == 0) return amount == 0;
        if(coins[0] > amount) return 0;
        

        vector<vector<int>> dp(coins.size(), vector<int>(amount + 1, 0));

        // base case 
        for(int i = 0;i<coins.size();++i)
        {
            dp[i][0] = 1;
        }
        for(int j = 0;j<=amount;++j)
        {
            if(j % coins[0] == 0)
            dp[0][j] = 1;
        }
        
        for(int i=1;i<coins.size();++i)
        {
            for(int j=0;j <=amount;++j)
            {
                if(j >= coins[i]) dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]];
                else dp[i][j] = dp[i-1][j];
            }
        }

        return dp[coins.size()-1][amount];
    }
};
```
时间复杂度：$O(N * amount)$；每个状态考虑一次，每次会考虑n种硬币；
空间复杂度：$O(N * amount)$；需要一个数组来储存信息。

### 72. Edit Distance
给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

* 插入一个字符
* 删除一个字符
* 替换一个字符
 
>示例 1：
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')

>示例 2：
输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')

#### 思路：
```cpp
D[i][j-1] 为 A 的前 i 个字符和 B 的前 j - 1 个字符编辑距离的子问题。即对于 B 的第 j 个字符，我们在 A 的末尾添加了一个相同的字符，那么 D[i][j] 最小可以为 D[i][j-1] + 1；

D[i-1][j] 为 A 的前 i - 1 个字符和 B 的前 j 个字符编辑距离的子问题。即对于 A 的第 i 个字符，我们在 B 的末尾添加了一个相同的字符，那么 D[i][j] 最小可以为 D[i-1][j] + 1；

D[i-1][j-1] 为 A 前 i - 1 个字符和 B 的前 j - 1 个字符编辑距离的子问题。即对于 B 的第 j 个字符，我们修改 A 的第 i 个字符使它们相同，那么 D[i][j] 最小可以为 D[i-1][j-1] + 1。特别地，如果 A 的第 i 个字符和 B 的第 j 个字符原本就相同，那么我们实际上不需要进行修改操作。在这种情况下，D[i][j] 最小可以为 D[i-1][j-1]。
```

```cpp
那么我们可以写出如下的状态转移方程：
if(word1[i] == word2[j]) dp[i][j] = dp[i - 1][j - 1];
else
{
    dp[i][j] = min(1 + dp[i - 1][j - 1], 1 + dp[i - 1][j], 1 + dp[i][j - 1]);
}

```

具体代码如下：

```cpp
class Solution {
public:
    int _min(int a, int b, int c) {
        return min(a, min(b, c));
    }

    int minDistance(string word1, string word2) {
        if(word1 == word2) return 0;
        if(word1 == "") return word2.size();
        if(word2 == "") return word1.size();

        int len_1 = word1.size(), len_2 = word2.size();

        vector<vector<int>> dp(len_1, vector<int>(len_2)); 

        for(int i = 0;i<len_1;++i)
        {
            if(word1[i] == word2[0]) dp[i][0] = i;
            else if(i == 0) dp[i][0] = 1;
            else dp[i][0] = dp[i - 1][0] + 1;
        }
        
        for(int j = 0;j<len_2;++j)
        {
            if(word2[j] == word1[0]) dp[0][j] = j;
            else if(j == 0) dp[0][j] = 1;
            else dp[0][j] = dp[0][j - 1] + 1;
        }
        
        for(int i = 1;i<len_1;++i)
        {
            for(int j = 1;j<len_2;++j)
            {
                if(word1[i] == word2[j]) dp[i][j] = dp[i - 1][j - 1];
                else
                {
                    dp[i][j] = _min(1 + dp[i - 1][j - 1], 1 + dp[i - 1][j], 1 + dp[i][j - 1]);
                }
            }
        }
        return dp[len_1 - 1][len_2 - 1];
    }
};
```
时间复杂度 ：O(mn)，其中 m 为 word1 的长度，n 为 word2 的长度。

空间复杂度 ：O(mn)，我们需要大小为O(mn)的数组来记录状态值。