/*https://leetcode.cn/problems/maximum-number-of-points-from-grid-queries/description/*/
//并查集+离线+排序
#include<iostream>
#include<algorithm>
#include<vector>
#include<numeric>
using namespace std;
class Union_Find
{
    std::vector<int>uf;
public:
    std::vector<int>size;
    Union_Find(int n)
    {
        uf = std::vector<int>(n);
        size = std::vector<int>(n,1);
        std::iota(uf.begin(),uf.end(),0);
    }
    int Find(int key)
    {
        return uf[key] == key ? key : uf[key] = Find(uf[key]);
    }
    void Union(int x,int y)
    {
        x = Find(x);
        y = Find(y);
        if(x != y)
        {
            uf[x] = y;
            size[y] += size[x];
        }
    }
};
class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) 
    {
        int row = grid.size(),col = grid[0].size();

        //grid一维化，便于并查集的联合
        vector<vector<int> >one_grid(row * col,vector<int>(3));
        for(int i = 0;i < row;i++)
        {
            for(int j = 0;j < col;j++)
            {
                one_grid[i * col + j][0] = grid[i][j];
                one_grid[i * col + j][1] = i; //保存坐标
                one_grid[i * col + j][2] = j;
            }
        }
        //对grid进行升序排列
        sort(one_grid.begin(),one_grid.end());

        //对queries进行升序排列，同时防止因排序后导致结果错位
        vector<vector<int> >queries_and_index(queries.size(),vector<int>(2)); 
        for(int i = 0;i < queries.size();i++)
        {
            queries_and_index[i][0] = queries[i];
            queries_and_index[i][1] = i;
        }
        sort(queries_and_index.begin(),queries_and_index.end());

        vector<int>res(queries.size(),0);
        Union_Find uf(row * col);//并查集
        int j = 0;
        const int move[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
        for(int i = 0;i < queries_and_index.size();i++)
        {
            int q = queries_and_index[i][0];
            //把边添加进并查集
            for(;j < row * col && one_grid[j][0] < q;j++)
            {
                int x1 = one_grid[j][1], y1 = one_grid[j][2];
                //枚举四种移动方式
                for(int k = 0;k < 4;k++)
                {
                    int x2 = x1 + move[k][0], y2 = y1 + move[k][1];
                    if(x2 >= 0 && x2 < row && y2 >= 0 && y2 < col) //防止越界
                    {
                        if(grid[x2][y2] < q)
                        {
                            uf.Union(x1 * col + y1,x2 * col + y2);
                        }
                    }
                }
            }
            if(grid[0][0] < q)
            {
                res[queries_and_index[i][1]] = uf.size[uf.Find(0)];//即为(0,0)的连通块数量,也即(0,0)的下级个数
            }
        }
        return res;
    }
};
int main(void)
{
    int m,n;
    cin >> m >> n;
    vector<vector<int> > grid(m,vector<int>(n));
    for(int i = 0;i < m;i++)
    {
        for(int j = 0;j < n;j++)
        {
            cin >> grid[i][j];
        }
    }
    int size;
    cin >> size;
    vector<int> queries(size);
    for(int i = 0;i < size;i++)
    {
       cin >> queries[i];
    }
    vector<int> res(size);
    Solution s;
    res = s.maxPoints(grid,queries);
    for(int i = 0;i < size;i++)
    {
        cout << res[i] << " ";
    }
}