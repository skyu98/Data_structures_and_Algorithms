# 学习数据结构与算法的一些笔记--*二叉搜索树（概念和特点）*

## 一、二叉搜索树的特点
二叉查找树要求，在树中的任意一个节点，其左子树中的每个节点的值，都要小于这个节点的值，而右子树节点的值都大于这个节点的值。
这样的特殊结构，使其支持快速查找一个数据，还支持快速插入、删除一个数据。

## 二、查找操作
先取根节点，如果它等于要查找的数据，那就返回。如果要查找的数据比根节点的值小，就在左子树中递归查找；如果要查找的数据比根节点的值大，就在右子树中递归查找。
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// recursion
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(!root ||root->val == val ) return root;
        if(root->val > val) return searchBST(root->left, val);
        if(root->val < val) return searchBST(root->right, val);
        return nullptr;
    }
};
```

```cpp
 // iteration
class Solution{
public:
    TreeNode* Find(TreeNode* root, int target){
        TreeNode* tmp = root;
        while(tmp! = NULL)
        {
            if(tmp->val==target)
            {
                return tmp;
            }
            else if(tmp->val < target)
            {
                tmp = tmp->right;
            }
            else
            {
                tmp = tmp->left;
            }
        }
        return NULL;
    }
};
```

## 二、 插入操作
二叉查找树的插入过程有点类似查找操作。
新插入的数据一般都是在叶子节点上，只需要从根节点开始，依次比较要插入的数据和节点的大小关系。如果要插入的数据比节点的数据大，并且节点的右子树为空，就将新数据直接插到右子节点的位置；如果不为空，就再递归遍历右子树，查找插入位置。同理，如果要插入的数据比节点数值小，并且节点的左子树为空，就将新数据插入到左子节点的位置；如果不为空，就再递归遍历左子树，查找插入位置。
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 // recursion
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root) return ( new TreeNode(val));

        if(root->val < val) 
        {
            root->right = insertIntoBST(root->right, val);
        }
        else
        {
            root->left = insertIntoBST(root->left, val);
        }
        return root;
    }
};
 ```
 ```cpp
 // iteration
class Solution{
public:
    // 假设插入的值不与已有的值重复
    TreeNode* Insert(TreeNode* root, int data){
        if(root == NULL)
        {
            TreeNode* root = new TreeNode(data);
            return root; 
        }

        TreeNode* tmp = root;
        while(tmp!=NULL) // while(True)
        {
            if(data > tmp->val)
            {
                if(tmp->right == NULL)
                {
                    tmp->right = TreeNode(data);
                    return root;
                }
                tmp = tmp->right;
            }
            else
            {
                if(tmp->left == NULL)
                {
                    tmp->left = TreeNode(data);
                    return root;
                }
                tmp = tmp->left;
            }
        }
    }
}；
```

## 三、删除操作
二叉查找树的查找、插入操作都比较简单易懂，但是它的删除操作就比较复杂了。
针对要删除节点的子节点个数的不同，我们需要分三种情况来处理。

* 第一种情况是，如果要删除的节点没有子节点，我们只需要直接将父节点中，指向要删除节点的指针置为null。比如图中的删除节点55。

* 第二种情况是，如果要删除的节点只有一个子节点（只有左子节点或者右子节点），我们只需要更新父节点中，指向要删除节点的指针，让它指向要删除节点的子节点就可以了。比如图中的删除节点13。

* 第三种情况是，如果要删除的节点有两个子节点，这就比较复杂了。我们需要找到这个节点的右子树中的最小节点，把它替换到要删除的节点上。然后再删除掉这个最小节点，因为最小节点肯定没有左子节点（如果有左子结点，那就不是最小节点了），所以，我们可以应用上面两条规则来删除这个最小节点。比如图中的删除节点18。

![delete](./tree_delete.jpg "delete")

## 迭代

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution{
public:
    int* Delete(TreeNode* root, int target){

        TreeNode* cur = root, *pre=NULL;
        while(cur! = NULL && cur->val != target)
        {
            pre = cur;
            if(cur->val < target)
            {
                cur = cur->right;
            }
            else
            {
                cur = cur->left;
            }
        }
        if(cur == NULL) return -1;

        if(cur->left != NULL && cur->right != NULL)
        {
            TreeNode* min = cur->right, *pre_min = cur;
            while(min->left!=NULL)
            {
                pre_min = min;
                min = min->left;
            }
            cur->val = min->val;
            // 接下来删除min节点
            // 由于min节点一定只有一个或没有子节点，因此可以将min作为cur，
            // 直接使用之后的逻辑进行删除操作
            cur = min;
            pre = pre_min;
        }

        TreeNode* single_child = NULL;
        if(cur->left != NULL) single_child = cur->left;
        else if(cur->right != NULL) single_child = cur->right;

        if(pre == NULL) root = single_child;
        else if(pre->left == cur) pre->left = single_child;
        else pre->right = single_child;
        return 0;
    }
};
```
## 递归
在这里，将找其右子树中的最小节点，抽象为找其中序遍历中的**后继节点**；
```cpp
int successor(TreeNode* root) {
  root = root->right;
  while (root->left != NULL) root = root->left;
  return root->val;
} 
```
**如果没有右子树，则其后继节点在其上方，为了避免回溯，则利用其前驱节点代替后继结点**
将找其左子树中的最大节点，抽象为找其中序遍历中的**前驱节点**；
```cpp
int predecessor(TreeNode* root) {
  root = root->left;
  while (root->right != NULL) root = root->right;
  return root->val;
} 
```
```cpp
class Solution {
public:
    int successor(TreeNode* root) {
        root = root->right;
        while (root->left != NULL) root = root->left;
        return root->val;
    }    
    
    int predecessor(TreeNode* root) {
        root = root->left;
        while (root->right != NULL) root = root->right;
        return root->val;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root) return root;
        
        // delete from left subtree
        if(key < root->val)
        {
            root->left = deleteNode(root->left, key);
        }
        // delete from right subtree
        else if(key > root->val)
        {
            root->right = deleteNode(root->right, key);
        }
        // root is the target
        else
        {   
            // if it's a leaf
            if(!root->left && !root->right) root = NULL;
            // it's not a leaf and has a right child
            else if(root->right)
            {   
                // find it's successor and use it to replace
                root->val = successor(root);
                // delete the successor
                root->right = deleteNode(root->right, root->val);
            }
            // it's not a leaf, has no right child, and has a left child
            else if(root->left)
            {
                // find it's predecessor and use it to replace
                root->val = predecessor(root);
                // delete the predecessor
                root->left = deleteNode(root->left, root->val)
            } 
        }
        return root;    
    }
};
```

## 四、其他操作
* 除了插入、删除、查找操作之外，二叉查找树中还可以支持快速地查找最大节点和最小节点、前驱节点和后继节点。

* 二叉查找树除了支持上面几个操作之外，还有一个重要的特性，就是中序遍历二叉查找树，可以输出有序的数据序列，时间复杂度是 O(n)，非常高效。因此，二叉查找树也叫作二叉排序树。

## 五、支持重复数据的二叉查找树
前面默认树中节点存储的都是数字。在实际的软件开发中，二叉查找树中存储的，是一个包含很多字段的对象。利用对象的某个字段作为键值（key）来构建二叉查找树，把对象中的其他字段叫作卫星数据。
前面二叉查找树的操作，针对的都是不存在键值相同的情况。如果存储的两个对象键值相同，有两种解决方法。
* 第一种方法比较容易。二叉查找树中每一个节点不仅会存储一个数据，因此我们通过链表和支持动态扩容的数组等数据结构，把值相同的数据都存储在同一个节点上。

* 第二种方法比较不好理解，不过更加优雅。每个节点仍然只存储一个数据。在查找插入位置的过程中，如果碰到一个节点的值，与要插入数据的值相同，就将这个要插入的数据放到这个节点的右子树，把这个新插入的数据当作大于这个节点的值来处理。
当要查找数据的时候，遇到值相同的节点，并不停止查找操作，而是继续在右子树中查找，直到遇到叶子节点，才停止。这样就可以把键值等于要查找值的所有节点都找出来。对于删除操作，也需要先查找到每个要删除的节点，然后再按删除操作的方法，依次删除。

## 六、二叉查找树的时间复杂度分析
* 极度不平衡：退化为链表，复杂度为O(n);
* 极度平衡：即完全二叉树（或满二叉树），**时间复杂度跟树的高度成正比，也就是 O(height)。** 假设最大层数是L，那么：
```cpp
n >= 1+2+4+8+...+2^(L-2)+1
n <= 1+2+4+8+...+2^(L-2)+2^(L-1)
```
L的范围是[log2(n+1), log2n+1]。因此，平衡二叉查找树的高度接近logn，操作的时间复杂度也比较稳定，是O(logn)。

## 七、思考：如何求给定二叉树的高度？
#### 1.思路：
```cpp
height(root) = max(height(root->left), height(root->right)) + 1
```
```cpp
class Solution{
public:
    int height(TreeNode* root){
        if(tree == NULL) return 0;
        return max(height(root->left), height(root->right)) + 1;
    }
};
```
#### 2.思路：高度等于最大深度+1
```cpp
depth(Node->child) = depth(Node) + 1 
```
```cpp
class Solution{
public:
    int res = 0;
    void passDepth(TreeNode* r, int depth){
        if(r == NULL) return;
        // 如果是根节点，判断是否是最深的根节点
        if(!r->left && !r->right)
        {
            res = max(res, depth);
        }
        // 继续传递
        passDepth(r->left, depth+1);
        passDeprh(r->right, depth+1);
    }

    int height(TreeNode* root){
        if(root==NULL) return 0;
        solve(root, 1); // 根节点深度为0
        return res;
    }
};
```
#### 3.思路：层次遍历整个树，每一层count++
```cpp
class Solution{
public:
    int height(TreeNode* root){
        if(root == NULL) return 0;
        
        int height = 0;
        queue<TreeNode*> q;

        q.push(root);
        while(!q.empty())
        {
            height++;
            int size = q.size();
            for(int i=0;i<size;i++)
            {
                TreeNode* cur = q.front();
                q.pop();
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
        }
        return height;
    }
};
```