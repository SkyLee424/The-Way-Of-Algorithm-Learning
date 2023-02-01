#include<iostream>
#include<stack>
#include<queue>
#include<vector>
class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode()
        : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val)
        : val(val), left(nullptr), right(nullptr) {}
};
TreeNode *createTree(void)
{
    TreeNode *pHead = new TreeNode;
    std::queue<TreeNode *> q;
    q.push(pHead);
    while (!q.empty())
    {
        int n = q.size();
        for (int i = 0; i < n; ++i)
        {
            auto node = q.front();
            q.pop();
            int val;
            std::cin >> val;
            if (val == -1)
            {
                if (node)
                {
                    node = nullptr;
                    delete node;
                    node = nullptr;
                }
                continue;
            }
            node->val = val;
            node->left = new TreeNode;
            node->right = new TreeNode;
            q.push(node->left);
            q.push(node->right);
        }
    }
    return pHead;
}
std::vector<int> preorderTraversal(TreeNode *pHead)
{
    std::vector<int> res;
    if (!pHead)
        return res;
    std::stack<TreeNode *> s;
    s.push(pHead);
    while (!s.empty())
    {
        auto node = s.top();
        s.pop();
        if (node->val != 0)
            res.push_back(node->val);
        if (node->right)
            s.push(node->right);
        if (node->left)
            s.push(node->left);
    }
    return res;
}
std::vector<int> inorderTraversal(TreeNode *pHead)
{
    std::vector<int> res;
    if (!pHead)
        return res;
    std::stack<TreeNode *> s;
    auto cur = pHead;
    while (cur || !s.empty())
    {
        if (cur)
        {
            s.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = s.top();
            s.pop();
            if (cur->val != 0)
                res.push_back(cur->val);
            cur = cur->right;
        }
    }
    return res;
}