# 学习数据结构与算法的一些笔记--*栈和队列（概念和特点）*

# P1 栈

## 1.后入先出

当某个数据集合只涉及在一端插入和删除数据，并且满足后进先出、先进后出的特性，我们就应该首选“栈”这种数据结构。

## 2.栈的实现
### 1.用数组实现顺序栈
```cpp

// 基于数组实现的顺序栈
class ArrayStack {
  private:
    vector<string> items;  // 数组
    int count;       // 栈中元素个数
    int n;           //栈的大小

  public:
  // 初始化数组，申请一个大小为n的数组空间
  ArrayStack(int n) {
    this.items = new vector<string>[n];
    this.n = n;
    this.count = 0;
  }

  // 入栈操作
  bool push(string item) {
    // 数组空间不够了，直接返回false，入栈失败。
    if (count == n) return false;
    // 将item放到下标为count的位置，并且count加一
    items[count] = item;
    ++count;
    return true;
  }
  
  // 出栈操作
  string pop() {
    // 栈为空，则直接返回null
    if (count == 0) return null;
    // 返回下标为count-1的数组元素，并且栈中元素个数count减一
    string tmp = items[count-1];
    --count;
    return tmp;
  }
};
```

### 2.用链表实现链式栈
```cpp
template <class T>
struct NODE
{
    NODE<T>* next;
    T data;
};

template <class T>
class MyStack{
    public:
        MyStack(){
            phead = new NODE<T>;
            if (phead == NULL)
            {
                cout << "Failed to malloc a new node. " << endl;
            }
            else
            {
                phead->data = NULL;
                phead->next = NULL;
            }
        }

        //入栈
        void push(T e){
            NODE<T>* p = new NODE<T>;
            if (p == NULL)
            {
                cout << "Failed to malloc a new node. " << endl;
            }
            else
            {
                p->data = e;
                p->next = phead->next;
                phead->next = p;
            }
        }

        //出栈
        T pop(){
            T e;
            NODE<T>* p = phead->next;
            if(p != NULL)
            {
                phead->next = p->next;
                e = p->data;
                delete p;
                return e;
            }
            else
            {
                cout << "There is no elements in the stack." << endl;
                return NULL;
            }
        }

        //取得栈顶元素
        T top(){
            T e;
            NODE<T>* p = phead->next;
            if (p != NULL)
            {
                e = p->data;
                return e;
            }
            else
            {
                cout << "There is no elements in the stack." << endl;
                return NULL;
            }
        }

        //取得栈中元素个数
        int size(){
            int count(0);
            NODE<T>* p = phead->next;
            while (p != NULL)
            {
                p = p->next;
                count++;
            }
                return count;
        }

        //判断stack是否为空
        bool empty(){
            NODE<T>* p = phead;
            if (p->next == NULL)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    private:
        NODE<T>* phead;
};
```
在入栈和出栈的过程中，只需要一两个临时变量存储空间，所以O(1)级别。我们说空间复杂度的时候，是指除了原本的数据存储空间外，算法运行还需要额外的存储空间。

## 3.栈的应用
* ### 栈在函数调用中的应用
操作系统给每个线程分配了一块独立的内存空间，这块内存被组织成“栈”这种结构，用来存储函数调用时的临时变量。每进入一个函数，就会将其中的临时变量作为栈帧入栈，当被调用函数执行完成，返回之后，将这个函数对应的栈帧出栈。

为什么函数调用要用“栈”来保存临时变量呢？用其他数据结构不行吗？
* 因为函数调用的执行顺序符合后进者先出，先进者后出的特点。比如函数中的局部变量的生命周期的长短是先定义的生命周期长，后定义的生命周期短；还有函数中调用函数也是这样，先开始执行的函数只有等到内部调用的其他函数执行完毕，该函数才能执行结束。
正是由于函数调用的这些特点，根据数据结构是特定应用场景的抽象的原则，我们优先考虑栈结构。

* ### 栈在表达式求值中的应用
逆波兰表达式：
逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。

平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。
该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。

逆波兰表达式主要有以下两个优点：
* 去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。
* 适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中。
```cpp
class Solution {
public:  
    //需要一个将字符转换为对应数字的函数
    int str2int(const string str){
	    int i=0,temp = 0;
	    if (str[0] == '-' || str[0] == '+')  //如果第一个字符是正负号，
	    {                      //则移到下一个字符
		    i++;
	    }
	    while (i < str.size())
	    {
		    if ((str[i] < '0') || (str[i] > '9'))  //如果当前字符不是数字
		    {                       //则退出循环
		        break;
		    }
 
		    temp = temp * 10 + (str[i] - '0'); //如果当前字符是数字则计算数值
		    i++;      //移到下一个字符
	    }
	    if (str[0] == '-')     //如果字符串是以“-”开头，则转换成其相反数
	    {
		    temp = -temp;
	    }
	    return temp;
    }


    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        int size = tokens.size();
        int i,a,b;
        for(i=0;i<size;i++)
        {
            if(tokens[i] ==  "+")
            {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(a+b); 
            }
            else if(tokens[i] == "-")
            {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(b-a); 
            }
            else if(tokens[i]== "*")
            {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(a*b); 
            }
            else if(tokens[i]== "/")
            {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(int(b/a)); 
            }
            else
            {
                cout<< tokens[i]<< '\n' <<endl;
                s.push(str2int(tokens[i]));
            }
            
        }
        return s.top();
    }
};
```

* ### 栈在括号匹配中的应用
#### 思路：遇到左括号，入栈；遇到右括号，判断其与栈顶是否配套，是则栈顶出栈，继续下一括号，否则返回false;当所有的括号都扫描完成之后，如果栈为空，则说明字符串为合法格式；否则，说明未匹配的左括号为非法格式。
```cpp

class Solution {
public:
    bool isValid(string s) {
        // 长度为奇数，不可能有效
        if(s.size() % 2 != 0)
        {
            return false;
        }
        
        stack<char> res;
        int i=0;
        while(i<s.size())
        {
            if(s[i]== '(' || s[i]== '[' ||s[i]== '{')
            {
                res.push(s[i]);
                i++;
            }
            if(s[i]== ')' || s[i]== ']' ||s[i]== '}')
            {
                //到了右括号，栈还是空的无左括号，不可能有效
                if(res.empty()) 
                {
                    return false;
                }
                if(pair(s[i]) == res.top())
                {
                   res.pop(); 
                   i++; 
                }
                else
                {
                    return false;
                }
            }
        }
        return res.empty();
    }
    
    //return语句不能全在if里面，否则会报错
    char pair(char s)
    {
        if(s == ')') return '(';
        if(s == ']') return '[';
        else return '{';
    }
};
```

