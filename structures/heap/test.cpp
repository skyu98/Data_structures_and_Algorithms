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
        tree[p] = tree[q];
        tree[q] = tmp;
    }

public:
    heap(int n) : capacity(n), count(0) {
        tree = vector<int> (capacity+1, 0);
        tree[0] = -1;       
    }

    int insert(int val){
        if(count >= capacity) return -1;
        ++count;

        int idx = count;
        tree[idx] = val;

        while(idx / 2 > 0  && tree[idx] > tree[idx / 2])// 自下往上堆化
        {
            // cout << idx <<"is" <<tree[idx] << endl;
            // cout << idx / 2 << "is" << tree[idx / 2] << endl;
            swap(idx, idx / 2);
            idx /= 2;
        }
        return idx;
    }

    int removeTop(){
        if(count < 1) return -1;
        tree[1] = tree[count];
        --count;

        heapify(tree, count, 1);
        return 0;
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
        int save = count;
        while(count > 1)
        {
            swap(count, 1);
            --count;
            heapify(tree, count, 1);
        }
        count = save;
    }

    int get(int idx){
        if(idx > count) return -1;
        return tree[idx];
    }
};

int main()
{
    int size = 5;

    heap h(size);
    h.insert(7);
    h.insert(8);
    h.insert(6);
    h.insert(3);
    h.insert(4);

    for(int i=1;i<=size;++i)
    {
        cout << h.get(i)<< endl;
    }
	cout<<"remove the top num :"<< h.get(1)<<endl;
    h.removeTop();

    for(int i=1;i<=size-1;++i)
    {
        cout << h.get(i)<< endl;
    }
    
	h.sort();

    cout <<"after sort"<< endl;

    for(int i=1;i<=size-1;++i)
    {
        cout << h.get(i)<< endl;
    }

    
    return 0;
}
