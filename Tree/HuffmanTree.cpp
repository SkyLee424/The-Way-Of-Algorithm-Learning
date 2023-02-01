#include <iostream>
#include <string>
#include <algorithm>
class HuffmanTree
{
public:
    char val;
    int lchild, rchild, parent;
    double weight;
    std::string Lib;
    HuffmanTree()
        : lchild(0), rchild(0), weight(0.0), parent(0), Lib("") {}
};
class Solution
{
public:
    void findmin(HuffmanTree *H, int &minpos0, int &minpos1, int len)
    {
        minpos0 = minpos1 = 0;
        double min0 = INT32_MAX, min1 = INT32_MAX;
        for (int i = 1; i < len; i++)
        {
            if (H[i].parent)
                continue;
            if (H[i].weight <= min0)
            {
                min0 = H[i].weight;
                minpos0 = i;
            }
        }
        for (int i = 1; i < len; i++)
        {
            if (H[i].parent || i == minpos0)
                continue;
            if (H[i].weight < min1)
            {
                min1 = H[i].weight;
                minpos1 = i;
            }
        }
    }
    void CreateTree(HuffmanTree H[], int n)
    {
        std::cout << "Please enter dictionary element" << '\n';
        for (int i = 1; i <= n; i++)
        {
            std::cin >> H[i].val;
        }
        std::cout << "Please enter the weight corresponding to the dictionary element" << std::endl;
        for (int i = 1; i <= n; i++)
        {
            std::cin >> H[i].weight;
        }
        for (int i = n + 1; i < 2 * n; i++)
        {
            int minpos0, minpos1;
            findmin(H, minpos0, minpos1, i);
            H[i].lchild = minpos0;
            H[i].rchild = minpos1;
            H[i].weight = H[minpos0].weight + H[minpos1].weight;
            H[minpos0].parent = i;
            H[minpos1].parent = i;
        }
    }
    void CreateLibrary(HuffmanTree *H, int n)
    {
        for (int i = 1; i <= n; i++)
        {
            int j = i;
            std::string tmp;
            while (1)
            {
                int Parent = H[j].parent;
                /*
                for debug:
                int debug0 = H[Parent].lchild;
                int debug1 = H[Parent].rchild;
                */
                if (Parent)
                {
                    if (H[Parent].lchild == j)
                    {
                        tmp.push_back('0');
                    }
                    else
                        tmp.push_back('1');
                    j = Parent;
                }
                else
                    break;
            }
            std::reverse(tmp.begin(), tmp.end());
            H[i].Lib = tmp;
        }
    }
    void Print(HuffmanTree *H, int n)
    {
        for (int i = 1; i <= n; i++)
        {
            //std::cout << i << " " << H[i].weight << " " << H[i].parent << " " << H[i].lchild << " " << H[i].rchild << std::endl;
            std::cout << H[i].val << "'s Huffman code is " << H[i].Lib << std::endl;
        }
    }
};
int main(void)
{
    Solution s;
    int n;
    std::cout << "Please enter the number of dictionary elements" << '\n';
    std::cin >> n;
    HuffmanTree H[2 * n];
    s.CreateTree(H, n);
    s.CreateLibrary(H, n);
    s.Print(H, n);
    //Encrypting
    std::cout << "Please enter the orginal code." << std::endl;
    std::string S;
    std::cin >> S;
    std::string cipher;
    for(int i = 0;i < S.length();i++){
        for(int j = 1;j <= n;j++){
            if(S[i] == H[j].val){
                cipher += H[j].Lib; 
                break;
            }
        }
    }
    std::cout << "After encryption: " << cipher << std::endl;
    //Decrypting
    int len = cipher.length();
    std::string orginlstring;
    int i = 0;
    while (i < len)
    {
        HuffmanTree head = H[2 * n - 1];
        while (head.lchild && head.rchild)
        {
            if(cipher[i] == '0'){
                head = H[head.lchild];
            }
            else head = H[head.rchild];
            i++;
        }
        orginlstring.push_back(head.val);
    }
    std::cout << "After decryption : " << orginlstring << std::endl;
}