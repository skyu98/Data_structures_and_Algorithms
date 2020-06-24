# 学习数据结构与算法的一些笔记--*数组和链表*

# P1：数组

## 1.连续分配的一段内存空间--->*随机访问*
内存的连续性，让数组的按下标访问能在O(1)的复杂度下完成。给定数组名a和需要访问的下标i：
```c
a[i]_address = base_address + i * data_type_size;
```

## 2.低效删除/插入操作
数组为了保持内存数据的连续性，插入和删除时会搬动剩下的结点，这会导致插入、删除这两个操作比较低效---O(n)时间复杂度。

----

# P2：链表

## 1.高效的插入删除
链表分配的空间不是连续的，天然具有动态扩容的优势。
在链表中插入或者删除一个数据，并不需要为了保持内存的连续性而搬移结点，因为存储空间本身就不是连续的。
针对链表的插入和删除操作，只需要考虑相邻结点的指针改变，所以对应的时间复杂度是 O(1)。

## 2.链表的局限性
链表中的数据并非连续存储的，要想随机访问，无法根据首地址和下标直接计算出对应的内存地址。
需要根据指针一个结点一个结点地依次遍历，直到找到相应的结点。链表随机访问需要 O(n) 的时间复杂度。
因为在删除/插入结点时，需要知道当前结点的前一个结点，这需要从头遍历，这导致其整个删除/插入过程用时为O(n)。

## 3.双向链表
双向链表用额外的两个空间来存储后继结点和前驱结点的地址。虽然两个指针比较浪费存储空间，但可以支持双向遍历，这样也带来了双向链表操作的灵活性。
由于能立即找到其前驱结点，插入/删除的时间复杂度减少为O(1)。

## 4.经典问题

* 注意边界条件

### 1.单链表反转(C/C++)
#### 1.思路：遍历链表，不断把下一个移到前面作为新的头节点。
```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == NULL) return NULL;
        ListNode *p = head, *q=head;
        while(p->next != NULL)
        {
            q = p->next;
            p->next = q->next;
            q->next = head;
            head = q;
        }
        return head;
    }
};
```
#### 2.思路：直接从头节点开始反转顺序，需要额外一个temp来记录上一个结点（即反转后的下一个结点）。
```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == NULL) return NULL;
        ListNode *p = head, *q=head, *temp = NULL;
        while(p!= NULL)
        {
            q = p;
            p = p->next;
            q->next = temp;
            temp = q;
        }
        return q;
    }
};
```
---

### 2.链表中环的检测
#### 思路：快慢指针，慢的每走一步，快的走两步；如果有环存在，两者必定相遇；否则快指针会跑的末尾。
```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *fast = head, *slow = head;
        while(slow && fast && fast->next)//没有环时，单数个结点时fast->next=NULL;偶数时fast==NULL
        {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast)
            {
                return true;
            }
        }
        return false;
    }
};
```

---

### 3.两个有序的链表合并
#### 思路：用一个新空链表，通过对比l1，l2中结点值的大小，将其有序地串联起来。
```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *p = l1, *q = l2;
        // res是新的链表地址，需要用new来申请空间
        ListNode *res = new ListNode; 
        res->next = NULL;
        ListNode *cur = res;
        
        while(p!=NULL && q!=NULL)
        {
            if(p->val < q->val)
            {
                cur->next = p;
                p = p->next;
                cur = cur->next;
                cur->next = NULL;
            }
            else
            {
                cur->next = q;
                q = q->next;
                cur = cur->next;
                cur->next = NULL;
            }
        }
        //此时可能会出现某一链表串联完时，另一链表还有结点未访问；只需将剩下的接上即可。
        if(p!=NULL)
        {
            cur->next = p;
        }
        if(q!=NULL)
        {
            cur->next = q;
        }
        res = res->next;
        return res;
    }
};
```

---

### 4.删除链表倒数第 n 个结点
#### 1.思路：两次遍历，第一次获取结点个数；第二次删除。
```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head == NULL) return NULL;
        int len = 0;
        ListNode *p = head;  
        
        while(p!=NULL)
        {
            len++;
            p = p->next;
        }
        // 如果是删除头节点，则直接返回第二个结点即可。
        if(n == len)
        {
            return head->next;
        }
        // 其他情况，找到被删除位置的前驱结点进行删除操作。
        p = head;
        for(int i=0;i<len-n-1;i++)
        {
            p = p->next;
        }
        p->next = p->next->next;
        return head;
    }
};
```

#### 2.思路：遍历一次，通过判断当前结点的下n个结点是否为NULL，来确定是否为目标位置。
```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head == NULL) return NULL;
        
        ListNode *p = head, *q = head, *tmp = head;  
        
        while(p->next!=NULL) //此处也可以是while(p!=NULL)，
                            //因为n>=1，程序总会在p停在最后一个结点之前找到目标结点的前一个结点。
        {   
            q = p;
            for(int i =0;i<n;i++)
            {
                q = q->next;
            }
            if(q == NULL)
            {   
                break;
            }
            tmp = p; // tmp为被删除结点的前驱结点
            p = p->next;
        }
        // 如果是删除头节点，则直接返回第二个结点即可。
        if(p == head)
        {
            return head->next;
        }
        // 其他情况，在被删除位置的前驱结点进行删除操作。
        tmp->next = p->next;
        return head;
    }
};
```

### 5.链表的中间结点
#### 思路：快慢指针寻找中点
```cpp
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *fast = head, *slow = head;
        while(fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
            return slow;
    }
};
```