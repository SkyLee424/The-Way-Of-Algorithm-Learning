#include <iostream>
class TreeNode
{
public:
    int val;
    TreeNode *left, *right;
    TreeNode(int num)
        : val(num), left(nullptr), right(nullptr) {}
};
class Solution
{
public:
    void Insert(int val, TreeNode *&root)
    {
        if (!root)
        {
            root = new TreeNode(val);
            return;
        }
        if (root->val == val)
            return;
        if (val < root->val)
            Insert(val, root->left);
        else
            Insert(val, root->right);
    }
    TreeNode *Search(int key, TreeNode *root)
    {
        if (!root)
            return root;
        if (key == root->val)
            return root;
        if (key < root->val)
            return Search(key, root->left);
        return Search(key, root->right);
    }
    void Del(int key, TreeNode *&root)
    {
        if (!root)
            return;
        if (root->val == key)
        {
            auto temp = root;
            if (!root->left)
                root = root->right;
            else if (!root->right)
                root = root->left;
            else
            {
                temp = root->left;
                TreeNode *pre = temp;
                while (temp->right)
                {
                    pre = temp;
                    temp = temp->right;
                }
                root->val = temp->val;
                if (temp->left)
                    pre->right = temp->left;
            }
            delete temp;
            temp = nullptr;
            return;
        }
        Del(key, root->left);
        Del(key, root->right);
    }
    void tranverse(TreeNode *root)
    {
        if (!root)
            return;
        tranverse(root->left);
        std::cout << root->val << " ";
        tranverse(root->right);
    }
};
int main(void)
{
    TreeNode *root = nullptr;
    Solution s;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int val;
        std::cin >> val;
        s.Insert(val, root);
    }
    int key;
    std::cin >> key;
    s.Del(key, root);
    s.tranverse(root);
}
