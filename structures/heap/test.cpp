#include<vector>

using namespace std;

class heap{
private:
    vector<int> tree;
    int capacity;
    int count;

    void swap(vector<int> v, int p, int q){
        int tmp = v[p];
        v[p] = v[q];
        v[q] = tmp;
    }

public:
    heap(int n) : capacity(n), count(0) {
        vector<int> tree (capacity + 1);
    }

    int insert(int val){
        if(count >= capacity) return -1;
        ++count;

        tree.push_back(val);
        int idx = count;
        while(idx / 2 > 0  && tree[idx] > tree[idx / 2])// 自下往上堆化
        {
            swap(tree, idx, idx / 2);
            idx /= 2;
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
            swap(tree, idx, maxPos);
            idx = maxPos;
        }
    }
};