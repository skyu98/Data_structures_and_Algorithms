#include<iostream>
#include<vector>


using namespace std;

class heap{
private:
    vector<int> tree;
    int capacity;
    int count;

    void swap(int p, int q){
        int tmp = tree[p];
        // cout << tmp << ","<< p << endl;
        tree[p] = tree[q];
        tree[q] = tmp;
    }

public:
    heap(int n) : capacity(n), count(0) {
        vector<int> tree;
        tree.push_back(-1);
    }

    int insert(int val){
        if(count >= capacity) return -1;
        ++count;

        tree.push_back(val);
        
        int idx = count;
        
        while(idx / 2 > 0  && tree[idx] > tree[idx / 2])// 自下往上堆化
        {
            swap(idx, idx / 2);
            idx /= 2;
        }
        
        for(int i =0;i<tree.size();++i)
        {
            cout<< i << ","<< tree[i]<<endl;
        }
        return idx;
    }

    int removeTop(){
        if(count < 1) return -1;
        tree[1] = tree[count];
        --count;

        heapify(tree, count, 1);
    }

    // 从上往下堆化
    void heapify(vector<int> tree, int count, int idx){
        while(1)
        {
            int maxPos = idx;
            if( 2* idx <= count && tree[maxPos] < tree[2*idx]) maxPos = 2*idx;
            if( 2* idx + 1 <= count && tree[maxPos] < tree[2*idx + 1]) maxPos = 2*idx + 1;
            if( maxPos == idx) break;
            swap(idx, maxPos);
            idx = maxPos;
        }
    }

    void sort(){
        while(count > 1)
        {
            swap(count, 1);
            --count;
            heapify(tree, count, 1);
        }
    }

    int get(int idx){
        if(idx > count) return -1;
        return tree[idx];
    }
};

int main()
{
    int capacity = 2;

    heap h = heap(capacity);
    h.insert(7);
    h.insert(8);
    //h.insert(6);
    //h.insert(3);
    //h.insert(4);

    for(int i=1;i<=capacity;++i)
    {
        cout << h.get(i)<< endl;
    }

    // h.sort();

    // cout <<"after sort"<< endl;

    // for(int i=1;i<=capacity;++i)
    // {
    //     cout << h.get(i+1)<< endl;
    // }

    // h.removeTop();

    // cout << h.get(1)<< endl;
    
    return 0;
}