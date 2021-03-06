# 学习算法的一些笔记--*贪心算法*

贪心算法的核心就是：**取当前可取得的最优解。**
每次选择当前情况下，在对限制值同等贡献量的情况下，对期望值贡献最大的数据。

## 具体例子

### 455. Assign Cookies
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。对每个孩子 i ，都有一个胃口值 $g_i$ ，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j ，都有一个尺寸$ s_j $。如果$ s_j >= g_i $，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

注意：

你可以假设胃口值为正。
一个小朋友最多只能拥有一块饼干。

#### 思路：
对于一个孩子来说，如果小的糖果可以满足，我们就没必要用更大的糖果，这样更大的就可以留给其他对糖果大小需求更大的孩子。另一方面，对糖果大小需求小的孩子更容易被满足，所以，我们可以从需求小的孩子开始分配糖果。因为满足一个需求大的孩子跟满足一个需求小的孩子，对我们期望值的贡献是一样的。

我们每次从剩下的孩子中，找出对糖果大小需求最小的，然后发给他剩下的糖果中能满足他的最小的糖果，这样得到的分配方案，也就是满足的孩子个数最多的方案。
```cpp
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        if(s.empty() || g.empty()) return 0;

        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int count = 0, cookie_idx = 0;
        for(int i = 0;i<g.size();++i)
        {
            int low = cookie_idx, high = s.size()-1;
            if(low > high) return count;
           
            while(low < high)
            {
                int mid = low + ((high - low)>> 1);
                if(s[mid] < g[i]) 
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid;
                }
            }
            if(s[low] < g[i]) return count;
            else
            {
                cookie_idx = low + 1;
                ++count;
            } 
        }
        return count;
    }
};
```
时间复杂度：O(nlogn)
空间复杂度：O(1)

### 322. Coin Change
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

#### 思路：
在生活中，我们肯定是先用面值最大的来支付，如果不够，就继续用更小一点面值的，以此类推，最后剩下的用 1 元来补齐。在贡献相同期望值（纸币数目）的情况下，我们希望多贡献点金额，这样就可以让纸币数更少，这就是一种贪心算法的解决思路。

需要注意的是，这里贪心算法找到的解不一定是最优解，比如：用100， 99， 1的硬币凑396,贪心算法会用三个100和96个1元，实际上只需要4个99。

后面会提到，此题应该用动态规划来解。

### 402. Remove K Digits
给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。

注意:
* num 的长度小于 10002 且 ≥ k。
* num 不会包含任何前导零。

示例 1 :
>输入: num = "1432219", k = 3
输出: "1219"
解释: 移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219。

示例 2 :
>输入: num = "10200", k = 1
输出: "200"
解释: 移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。

示例 3 :
>输入: num = "10", k = 2
输出: "0"
解释: 从原数字移除所有的数字，剩余为空就是0。

#### 思路：
我们可以总结上述删除一个数字的规则，如下：
给定一个数字序列$ [D_1D_2D_3…D_n]$，如果数字$ D_2$小于其左邻居$ D_1$，则我们应该删除左邻居$D_1$，以获得最小结果。

算法：

上述的规则使得我们通过一个接一个的删除数字，逐步的接近最优解。

这个问题可以用贪心算法来解决。上述规则阐明了我们如何接近最终答案的基本逻辑。一旦我们从序列中删除一个数字，剩下的数字就形成了一个新的问题，我们可以继续使用这个规则。

我们会注意到，在某些情况下，规则对任意数字都不适用，即单调递增序列。在这种情况下，我们只需要删除末尾的数字来获得最小数。

```cpp
class Solution {
public:
    string removeKdigits(string num, int k) {
        stack<char> s;
        for(int i = 0;i<num.size();++i)
        {
            while(!s.empty() && k > 0 && num[i] < s.top())
            {
                s.pop();
                --k;
            }
            s.push(num[i]);
        }
        
        while(k>0)
        {
            --k;
            s.pop();
        }

        string res;
        while(!s.empty())
        {
            res += s.top();
            s.pop();
        }

        reverse(res.begin(), res.end());

        while (!res.empty() && res[0] == '0') {
            res.erase(res.begin());
        }

        return res.size() == 0 ? "0" : res;
    }
};
```
时间复杂度：O(n)
空间复杂度：O(n)

