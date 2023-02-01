#include <iostream>
#include <string>
#include <map>
class TreeNode
{
public:
    int val;
    int height;
    TreeNode *left, *right;
    TreeNode(int num)
        : val(num), height(1), left(nullptr), right(nullptr) {}
};
class Solution
{
    void RefreshHeight(TreeNode *&node)
    {
        int lh = 0, rh = 0;
        if (node->left)
            lh = node->left->height;
        if (node->right)
            rh = node->right->height;
        node->height = std::max(lh, rh) + 1;
    }
    TreeNode *LL_Rotate(TreeNode *unbalanced_node)
    {
        auto B = unbalanced_node->left;
        unbalanced_node->left = B->right;
        B->right = unbalanced_node;
        RefreshHeight(B->left);
        RefreshHeight(B->right);
        RefreshHeight(B);
        return B;
    }
    TreeNode *RR_Rotate(TreeNode *unbalanced_node)
    {
        auto B = unbalanced_node->right;
        unbalanced_node->right = B->left;
        B->left = unbalanced_node;
        RefreshHeight(B->left);
        RefreshHeight(B->right);
        RefreshHeight(B);
        return B;
    }
    TreeNode *RL_Rotate(TreeNode *unbalanced_node)
    {
        auto B = unbalanced_node->right;
        // B = LL_Rotate(B);
        // return RR_Rotate(unbalanced_node);
        auto C = B->left;
        unbalanced_node->right = C->left;
        B->left = C->right;
        C->left = unbalanced_node;
        C->right = B;
        RefreshHeight(C->left);
        RefreshHeight(C->right);
        RefreshHeight(C);
        return C;
    }
    TreeNode *LR_Rotate(TreeNode *unbalanced_node)
    {
        auto B = unbalanced_node->left;
        // B = RR_Rotate(B);
        // return LL_Rotate(unbalanced_node);
        auto C = B->right;
        unbalanced_node->left = C->right;
        B->right = C->left;
        C->left = B;
        C->right = unbalanced_node;
        RefreshHeight(C->left);
        RefreshHeight(C->right);
        RefreshHeight(C);
        return C;
    }
    int isbalanced(TreeNode *node)
    {
        int lh = 0, rh = 0;
        if (node->left)
            lh = node->left->height;
        if (node->right)
            rh = node->right->height;
        return lh - rh;
    }

public:
    void Insert(TreeNode *&root, int val)
    {
        if (!root)
        {
            root = new TreeNode(val);
            return;
        }
        if (val < root->val)
            Insert(root->left, val);
        else if (val > root->val)
            Insert(root->right, val);
        else
            return;

        RefreshHeight(root);
        int balance = isbalanced(root);
        if (balance > 1)
        {
            if (val < root->left->val)
                root = LL_Rotate(root);
            else
                root = LR_Rotate(root);
        }
        else if (balance < -1)
        {
            if (val > root->right->val)
                root = RR_Rotate(root);
            else
                root = RL_Rotate(root);
        }
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
        s.Insert(root, val);
    }
    s.tranverse(root);
}