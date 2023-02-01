#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
class Union_Find
{
    std::vector<int> rank;
    std::vector<int> uf;

public:
    Union_Find(int n)
    {
        rank = std::vector<int>(n + 1, 1);
        uf = std::vector<int>(n + 1);
        // 初始化上级为自己
        std::iota(uf.begin(), uf.end(), 0);
        // std::cout << uf[n];
    }
    // 寻找x的根节点
    int find(int x)
    {
        return uf[x] == x ? x : uf[x] = find(uf[x]);
    }
    // 合并节点x,y
    void Union(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        // x的根节点的等级更高
        if (rank[x] > rank[y])
        {
            uf[y] = x; // y的上级改为x
        }
        else
        {
            // 二者等级相同
            if (rank[x] == rank[y])
            {
                rank[y]++; // x变为y的下级，y的等级自然应该+1
            }
            uf[x] = y;
        }
    }
};
int main(void)
{
    int n; // 节点总个数
    std::cin >> n;
    Union_Find uf(n);
    for (int i = 0; i < n; i++)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        uf.Union(v1, v2);
    }
    //判断两点间是否存在路径
    while (1)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        if (uf.find(v1) == uf.find(v2))
            std::cout << "存在";
        else
            std::cout << "不存在";
        std::cout << std::endl;
    }
    
    
}