# 学习数据结构与算法的一些笔记--*队列（概念和特点）*

## 一、先入先出
支持两个操作：入队enqueue()，放一个数据到队尾；出队dequeue()，从队头取一个元素。所以，和栈一样，队列也是一种操作受限的线性表。

## 二、队列的实现
### 1.数组实现（顺序队列）
```cpp
// 用数组实现的队列
class ArrayQueue {
// 数组：items，数组大小：n
private:
    vector<int> items;
    int size = 0;
    // head表示队头下标，tail表示队尾下标
    int head = 0;
    int tail = 0;

public:
    // 申请一个大小为capacity的数组
    ArrayQueue(int capacity) {
        items = new vector<int>[capacity];
        size = capacity;
    }

    // 入队
    bool enqueue(int item) {
        // 如果tail == n 表示队列已经满了。此时若队列前方为空，可进行数据搬移
        if (tail == n)
        {
            if(head == 0)
            {
                return false;
            }
            //搬移
            for(int i = head;i<tail;i++)
            {
                items[i-head] = item[i];
            }
            tail -= head;
            head = 0 
        }
        items[tail] = item;
        ++tail;
        return true;
        }

    // 出队
    int dequeue() {
        // 如果head == tail 表示队列为空
        if (head == tail) return NULL;
        // 为了让其他语言的同学看的更加明确，把--操作放到单独一行来写了
        int ret = items[head];
        ++head;
        return ret;
    }
}
```

### 2.链表实现（链式队列）
```cpp
struct ListNode {
      int val;  //当前结点的值
      ListNode *next;  //指向下一个结点的指针
      ListNode(int x) : val(x), next(NULL) {}  //初始化当前结点值为x,指针为空
}

// 用链表实现的队列
class ListNodeQueue{
// 数组：items，数组大小：n
private:
    int size = 0;
    // head表示队头，tail表示队尾
    struct ListNode* head = NULL;
    struct ListNode* tail = NULL;

public:
    // 构造函数
    ArrayQueue() {}

    // 入队
    bool enqueue(int item) {
        struct ListNode* new_node;
        new_node->val = item;
        // 若队列为空，则将第一个入队的结点作为头尾结点（否则tail=NULL）
        if(size == 0)
        {
            head = new_node;
            tail = head;
        }
        else
        {
            tail->next = new_node;
            tail = tail->next;
        }
        size++;
        return true;
        }

    // 出队
    int dequeue() {
        // 如果size == 0 表示队列为空
        if (size == 0) return NULL;
        int ret = head->val;
        head = head->next;
        size--;
        return ret;
    }
}

```
### 3.循环队列（基于数组）
```cpp
class MyCircularQueue {
private:
    vector<int> data;
    int head;
    int tail;
    int size;
    
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k): size(k), head(-1), tail(-1) {
        data.resize(k);
    }// 构造函数的作用是对成员变量进行初始化，而不是定义成员变量
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if(isFull())
        {
            return false;
        }
        if(isEmpty())
        {
            head = 0;
        }
        tail = (tail+1)%size;// 循环队列，必须考虑head/tail在最末尾的情况
        data[tail] = value;
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if(isEmpty())
        {
            return false;
        }
        if(head == tail)
        {
            head = -1;
            tail = -1;
            return true;
        } 
        head = (head+1)%size; // 循环队列，必须考虑head/tail在最末尾的情况
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        if(isEmpty())
        {
            return -1;
        }
        return data[head];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        if(isEmpty())
        {
            return -1;
        }
        return data[tail];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        if(head == -1 && tail == -1)
        {
            return true;
        }
        return false;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        if((tail+1)%size == head)
        {
            return true;
        }
        return false;
    }
};

```

## 三、队列的应用
* ### 阻塞队列
* 在队列的基础上增加阻塞操作，就成了阻塞队列。
* 阻塞队列就是在队列为空的时候，从队头取数据会被阻塞，因为此时还没有数据可取，直到队列中有了数据才能返回；如果队列已经满了，那么插入数据的操作就会被阻塞，直到队列中有空闲位置后再插入数据，然后在返回。
* 从上面的定义可以看出这就是一个“生产者-消费者模型”。这种基于阻塞队列实现的“生产者-消费者模型”可以有效地协调生产和消费的速度。当“生产者”生产数据的速度过快，“消费者”来不及消费时，存储数据的队列很快就会满了，这时生产者就阻塞等待，直到“消费者”消费了数据，“生产者”才会被唤醒继续生产。不仅如此，基于阻塞队列，我们还可以通过协调“生产者”和“消费者”的个数，来提高数据处理效率，比如配置几个消费者，来应对一个生产者。
* ### 并发队列
* 在多线程的情况下，会有多个线程同时操作队列，这时就会存在线程安全问题。能够有效解决线程安全问题的队列就称为并发队列。
* 并发队列简单的实现就是在enqueue()、dequeue()方法上加锁，但是锁粒度大并发度会比较低，同一时刻仅允许一个存或取操作。
* 实际上，基于数组的循环队列利用CAS原子操作，可以实现非常高效的并发队列。这也是循环队列比链式队列应用更加广泛的原因。
* ### 线程池资源枯竭时的处理
* 在资源有限的场景，当没有空闲资源时，基本上都可以通过“队列”这种数据结构来实现请求排队。