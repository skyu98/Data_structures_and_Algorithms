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