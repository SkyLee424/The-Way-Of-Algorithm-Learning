/*https://blog.csdn.net/songshuai0223/article/details/106551499?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166867725516782390527280%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166867725516782390527280&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-106551499-null-null.142^v64^control,201^v3^add_ask,213^v2^t3_control1&utm_term=%E7%BA%BF%E7%B4%A2%E4%BA%8C%E5%8F%89%E6%A0%91&spm=1018.2226.3001.4187*/
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;
enum
{
    Link,
    Thread
};
class Thread_bitree
{
public:
    Thread_bitree *lchild, *rchild;
    char val;
    int Ltag, Rtag;
    Thread_bitree()
        : val('0'), Ltag(Link), Rtag(Link) {}
    // Ltag == Thread，lchild指向前驱节点
    // 同理......
};
void CreateTree(Thread_bitree *&T)
{
    char Val;
    cin >> Val;
    if (Val == '#')
    {
        T = nullptr;
        return;
    }
    T = new Thread_bitree;
    T->val = Val;
    CreateTree(T->lchild);
    CreateTree(T->rchild);
}
/*中序线索化*/
void In_Threading0(Thread_bitree *&T, Thread_bitree **pre)
{
    /*
    将 prev 指针作为二级指针传入，是因为递归过程需要改变 prev 指针指向的地址中的值，想要修改一级指针的话就需要传入一级指针的地址，也就是二级指针
    */
    if (!T)
        return;
    In_Threading0(T->lchild, pre);
    if (!T->lchild)
    {                       // 该节点左子树为空
        T->lchild = (*pre); // 让该节点左子树指向该节点前驱
        T->Ltag = Thread;   // 改变状态
    }
    if ((*pre) && !(*pre)->rchild)
    {
        // T的前驱pre没有右孩子，让pre指向其后继，即T
        (*pre)->rchild = T; // T是pre的后继
        (*pre)->Rtag = Thread;
    }
    // 保证*pre指向T的前驱；
    (*pre) = T;
    In_Threading0(T->rchild, pre);
}
Thread_bitree *findbacknode(Thread_bitree *key)
{
    if (!key)
        return nullptr;
    if (key->Rtag == Thread)
    {
        // 也即key的右子树的头节点就是其后继
        return key->rchild;
    }
    else
    {
        // key的后继为其右子树的最左端(看图理解)
        key = key->rchild;
        while (key->Ltag == Link) // key->Ltag != Thread
        {
            key = key->lchild;
        }
        return key;
    }
    // 若想找前驱节点，将上述代码的r改为l，l改为r即可
}
/*中序线索化输出*/
void Print0(Thread_bitree *T)
{
    if (!T)
        return;
    // 寻找第一个节点
    while (T->Ltag != Thread)
    {
        T = T->lchild;
    }
    cout << T->val << " ";
    // 当第一个节点有后继
    while (T->rchild)
    {
        T = findbacknode(T); // T = T的后继
        cout << T->val << " ";
    }
    cout << endl;
}
/*前序线索化*/
void In_Threading1(Thread_bitree *&T, Thread_bitree **pre)
{
    if (!T)
        return;
    if (!T->lchild)
    {
        T->lchild = (*pre);
        T->Ltag = Thread;
    }
    if ((*pre) && !(*pre)->rchild)
    {
        (*pre)->rchild = T;
        (*pre)->Rtag = Thread;
    }
    (*pre) = T;
    // 注意：不加判断会导致陷入死循环
    if (T->Ltag == Link)
    {
        In_Threading1(T->lchild, pre);
    }
    if (T->Rtag == Link)
    {
        In_Threading1(T->rchild, pre);
    }
}
/*前序线索化输出*/
void Print1(Thread_bitree *T)
{
    if (!T)
        return;
    while (T)
    {
        while (T->Ltag == Link)
        {
            cout << T->val << " ";
            T = T->lchild;
        }
        cout << T->val << " ";
        T = T->rchild;
    }
}
int main(void)
{
    /*中序*/
    Thread_bitree *T;
    CreateTree(T);
    Thread_bitree **pre0 = new Thread_bitree *;
    (*pre0) = nullptr;
    In_Threading0(T, pre0);
    Print0(T);
    /*前序*/
    Thread_bitree *T1;
    CreateTree(T1);
    Thread_bitree **pre1 = new Thread_bitree *;
    (*pre1) = nullptr;
    In_Threading1(T1, pre1);
    Print1(T1);
}