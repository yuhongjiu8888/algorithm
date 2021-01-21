算法

1.输入一个链表，反转链表后，输出新链表的表头。
解：
    此题想考察的是：如何调整链表指针，来达到反转链表的目的。
初始化：3个指针
1）pre指针指向已经反转好的链表的最后一个节点，最开始没有反转，所以指向nullptr
2）cur指针指向待反转链表的第一个节点，最开始第一个节点待反转，所以指向head
3）nex指针指向待反转链表的第二个节点，目的是保存链表，因为cur改变指向后，后面的链表则失效了，所以需要保存
接下来，循环执行以下三个操作
1）nex = cur->next, 保存作用
2）cur->next = pre 未反转链表的第一个节点的下个指针指向已反转链表的最后一个节点
3）pre = cur， cur = nex; 指针后移，操作下一个未反转链表的第一个节点
循环条件，当然是cur != nullptr
循环结束后，cur当然为nullptr，所以返回pre，即为反转后的头结点。

class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        ListNode *pre = nullptr;
        ListNode *cur = pHead;
        ListNode *nex = nullptr; // 这里可以指向nullptr，循环里面要重新指向
        while (cur) {
            nex = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nex;
        }
        return pre;
    }
};

2.设计LRU缓存结构，该结构在构造时确定大小，假设大小为K，并有如下两个功能
set(key, value)：将记录(key, value)插入该结构
get(key)：返回key对应的value值
[要求]
set和get方法的时间复杂度为O(1)
某个key的set或get操作一旦发生，认为这个key的记录成了最常使用的。
当缓存的大小超过K时，移除最不经常使用的记录，即set或get最久远的。
若opt=1，接下来两个整数x, y，表示set(x, y)
若opt=2，接下来一个整数x，表示get(x)，若x未出现过或已被移除，则返回-1
对于每个操作2，输出一个答案

#include <unordered_map>
#include <list>
#include <vector>
using namespace std;
struct Node
{
    Node(int k = 0, int v = 0) : key(k), val(v) {}
    int key;
    int val;
};
class Solution
{
public:
    /**
     * lru design
     * @param operators int整型vector<vector<>> the ops
     * @param k int整型 the k
     * @return int整型vector
     */
    vector<int> LRU(vector<vector<int>> &operators, int k)
    {
        // write code here
        cap = k;
        vector<int> ans;
        for (auto &input : operators)
        {
            if (input[0] == 1)
            {
                set(input[1], input[2]);
            }
            else
            {
                ans.push_back(get(input[1]));
            }
        }
        return ans;
    }
    //删除
    int remove(std::list<Node>::iterator &ite)
    {
        int key = ite->key;
        int val = ite->val;
        L.erase(ite);
        H.erase(key);
        return val;
    }
    // 添加
    void add(int key, int val)
    {
        L.push_front(Node(key, val));
        H[key] = L.begin();
        if (L.size() > cap)
        {
            auto last = L.end();
            --last;
            remove(last);
        }
    }
    void set(int x, int y)
    {
        auto ite = H.find(x);
        //已经存在，删除了再添加到头部
        if (ite != H.end())
        {
            remove(ite->second);
        }
        add(x, y);
    }
    int get(int x)
    {
        int val = 0;
        //已经存在，删除了再添加到头部
        auto ite = H.find(x);
        if (ite != H.end())
        {
            val = remove(ite->second);
            add(x, val);
            return val;
        }
        return -1;
    }

private:
    std::list<Node> L;
    std::unordered_map<int, std::list<Node>::iterator> H;
    int cap;
};

3.判断给定的链表中是否有环。如果有环则返回true，否则返回false。
你能给出空间复杂度的解法么？
	快慢指针法

class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode *p = head;
        ListNode *q = head;
        while(p!=nullptr && p->next!=nullptr){
            p = p->next->next;
            q = q->next;
            if(p==q){
                return true;
            }
 
        }
        return false;
    }
};

4.分别按照二叉树先序，中序和后序打印所有的节点。
输入   {1,2,3}
返回值 [[1,2,3],[2,1,3],[2,3,1]]

解：递归方法
class Solution {
public:
    /**
     * 
     * @param root TreeNode类 the root of binary tree
     * @return int整型vector<vector<>>
     */
	//前序遍历
    void preorder(TreeNode* root){
        if(root != nullptr){
            pre.push_back(root -> val);
            preorder(root -> left);
            preorder(root -> right);
        }
    }
 
	//中序遍历
    void inorder(TreeNode* root){
        if(root != nullptr){
            inorder(root -> left);
            in.push_back(root -> val);
            inorder(root -> right);
        }
    }
 
	//后续遍历
    void postorder(TreeNode* root){
        if(root != nullptr){
            postorder(root -> left);
            postorder(root -> right);
            post.push_back(root -> val);
        }
    }
    vector<vector<int> > threeOrders(TreeNode* root) {
        // write code here
        vector<vector<int>> res;
        preorder(root);
        res.push_back(pre);
        inorder(root);
        res.push_back(in);
        postorder(root);
        res.push_back(post);
        return res;
    }
private: 
    vector<int> pre;
    vector<int> in;
    vector<int> post;
};

5.请实现有重复数字的升序数组的二分查找。
输出在数组中第一个大于等于查找值的位置，如果数组中不存在这样的数，则输出数组长度加一。
输入 5,4,[1,2,4,4,5]
返回值 3

class Solution {
public:
    /**
     * 二分查找
     * @param n int整型 数组长度
     * @param v int整型 查找值
     * @param a int整型vector 有序数组
     * @return int整型
     */
    int upper_bound_(int n, int v, vector<int>& a) {
        // write code here
         int left = 0, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (a[mid] < v) left = mid + 1;
            else right = mid;
        }
        return right + 1;
    }
};

6.输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4。
输入  [4,5,1,6,2,7,3,8],4
返回值 [1,2,3,4]

class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> res;
        if (k==0 || k>input.size()) return res;//此处需要判断输入的值是否合理
        sort(input.begin(), input.end());
        for(int i=0;i<k;i++){
            res.push_back(input[i]);
        }
        return res;
    }
};

7.有一个整数数组，请你根据快速排序的思路，找出数组中第K大的数。
给定一个整数数组a,同时给定它的大小n和要找的K(K在1到n之间)，请返回第K大的数，保证答案存在。
输入 [1,3,5,2,2],5,3
返回值 2

class Solution {
public:
    int findKth(vector<int> a, int n, int K) {
        // write code here
        if(K<1 || K>n) return 0;
        
        return quick_sort(a, 0, n - 1, n, K);  
    }
    int quick_sort(vector<int>& a, int start, int end, int n, int k) {
        int base = a[start];
        int i = start;
        int j = end;
        int res = 0;
 
        while (i < j) {
            while (i<j && a[j]>=base) --j;
            while (i<j && a[i]<=base) ++i;
            if (i < j) swap(a[i], a[j]);
        }
        swap(a[start], a[j]);
 
        if (n - j == k) return a[j];
        else if (n - j < k) res = quick_sort(a, start, j-1, n, k);
        else if (n - j > k) res = quick_sort(a, j+1, end, n, k);
        return res;
    }
    
};

8.给定一个二叉树，返回该二叉树层序遍历的结果，（从左到右，一层一层地遍历）
例如：
给定的二叉树是{3,9,20,#,#,15,7},

该二叉树层序遍历的结果是
[
[3],
[9,20],
[15,7]
]
解题思路:https://www.bilibili.com/video/BV1bK41137Fa/
    /**
 * struct TreeNode {
 *    int val;
 *    struct TreeNode *left;
 *    struct TreeNode *right;
 * };
 */

class Solution {
public:
    /**
     *
     * @param root TreeNode类
     * @return int整型vector<vector<>>
     */
    vector<vector<int> > levelOrder(TreeNode* root) {
        vector<vector<int> >res;//用于返回最后的结果
        if(root == NULL) return res;//如果根节点为空就返回结果
        queue<TreeNode *>q;//用于存储每一层的节点
        q.push(root);
        while(!q.empty()){
            vector<int>temp;//用于存储当前遍历这一层的节点
            int n = q.size();
            for(int i = 0;i < n;i ++){
                TreeNode *node = q.front();//取出队列的第一个元素
                q.pop();
                temp.push_back(node->val);//将队头元素保存起来
                if(node->left != NULL) q.push(node->left);//左孩子如果不为空就进队列
                if(node->right != NULL) q.push(node->right);//右孩子如果不为空就进队列
            }
            res.push_back(temp);//将这一层的节点数里面据保存到res
        }
        return res;
    }

};

9.一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。
解：考察知识：递归，记忆化搜索，动态规划和动态规划的空间优化。
class Solution {
public:
    int jumpFloor(int n) {
        if (n == 0 || n == 1) return n;
        int a = 1, b = 1, c;
        for (int i=2; i<=n; ++i) {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
};

10.将两个有序的链表合并为一个新链表，要求新的链表是通过拼接两个链表的节点来生成的，且合并后新链表依然有序。
输入 {1},{2}
返回值 {1,2}

解：
class Solution {
public:
    /**
     * 
     * @param l1 ListNode类 
     * @param l2 ListNode类 
     * @return ListNode类
     */
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // write code here
         if(l1==nullptr||l2==nullptr) return  l1?l1:l2;
        ListNode* q=nullptr;
        ListNode* p1=l1;
        ListNode* p2=l2;
        if(p1->val<=p2->val)//把最小的头结点赋值给q;
        {
            q=p1;
            p1=p1->next;//后移
        }
        else
        {
            q=p2;
            p2=p2->next;
        }
        ListNode *qq=q;//记录头结点
        while(p2&&p1)
        {
            if(p1->val<=p2->val)
            {
                q->next=p1;
                q=p1;//更新位置
                p1=p1->next;
            }
            else//大于
            {
                q->next=p2;
                q=p2;
                p2=p2->next;
 
            }
        }
        if(p1)//剩余的直接连接在后面
            q->next=p1;
        if(p2)
            q->next=p2;
        return qq;
        
    }
};


11.用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
解 ： https://www.nowcoder.com/practice/54275ddae22f475981afa2244dd448c6?tpId=190&tags=&title=&diffculty=0&judgeStatus=0&rp=1

class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int ret = stack2.top();
        stack2.pop();
        return ret;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};

12.给出一个整数数组，请在数组中找出两个加起来等于目标值的数，
你给出的函数twoSum 需要返回这两个数字的下标（index1，index2），需要满足 index1 小于index2.。注意：下标是从1开始的
假设给出的数组中只存在唯一解
例如：
给出的数组为 {20, 70, 110, 150},目标值为90
输出 index1=1, index2=2

输入：[3,2,4],6
返回值  [2,3]

解：
class Solution {
public:
    /**
     * 
     * @param numbers int整型vector 
     * @param target int整型 
     * @return int整型vector
     */
    vector<int> twoSum(vector<int>& numbers, int target) {
        // write code here
        vector<int> res;
        int len = numbers.size();
        for(int i = 0; i<len;i++){
            for(int j = i+1;j<len;j++){
                if(numbers[i]+numbers[j]==target){
                    res.push_back(i+1);
                    res.push_back(j+1);
                    break;
                }       
            }
        }
        return res;
    }
};

13.给出两个有序的整数数组A和B，请将数组B合并到数组A中，变成一个有序的数组
注意：
可以假设A数组有足够的空间存放B数组的元素，A和B中初始的元素数目分别为M和N.
知识点：数组 、双指针

解：
class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
       int *p = &A[m-1], *q = &B[n-1], *r = &A[m+n-1];
        while (m + n > 0) {
            if (m > 0 && n > 0){
                if(*p > *q) { *r = *p; --m; --r; --p; }
                else { *r = *q; --n; --r; --q; }
            } else {
                while (m--) { *r = *p; --p; --r; }
                while (n--) { *r = *q; --q; --r; }
            }
        }
    }
};

14.给定一个数组arr，返回arr的最长无的重复子串的长度(无重复指的是所有数字都不相同)。
考点：哈希 双指针
输入： [2,3,4,5]
返回值：4

#include<unordered_map>
class Solution {
public:
    /**
     * 
     * @param arr int整型vector the array
     * @return int整型
     */
    int maxLength(vector<int>& arr) {
        // write code here
        unordered_map<int , int> mymap;
        int i = 0 , Max = INT_MIN;
        while(i<arr.size())
        {
            mymap.clear();
            mymap[arr[i]] = i;
            int j = i+1;
            while(j<arr.size())
            {
                if(mymap.count(arr[j])==0)//返回匹配特定键的元素数量
                {
                    mymap[arr[j]] = j;
                }
                else
                {
                    i = mymap.at(arr[j]);//访问指定键值的元素
                    break;
                }
                j++;
            }
            i++;
            int temp = mymap.size();
            Max = max(Max , temp);
        }
        return Max;
    }
};

15.写出一个程序，接受一个字符串，然后输出该字符串反转后的字符串。（字符串长度不超过1000）
class Solution {
public:
    /**
     * 反转字符串
     * @param str string字符串 
     * @return string字符串
     */
    string solve(string str) {
        // write code here
        string tmp ;
        tmp.assign(str.rbegin(),str.rend());
        return tmp;
    }
};


