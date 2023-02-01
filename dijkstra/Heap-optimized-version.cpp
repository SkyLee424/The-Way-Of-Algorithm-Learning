#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <numeric>
#include <algorithm>
// 注意：下列代码起始顶点下标从1开始
void dijkstra(std::unordered_map<int, std::unordered_map<int, int>> map, std::vector<int> &dis, int startpos, int vexnum);
int main(void)
{
    int vexnum, arcnum;
    std::cin >> vexnum >> arcnum;
    int startpos; // 起始点
    std::cin >> startpos;

    // 采用散列表存储边，既可用作邻接矩阵，又可用作邻接表
    std::unordered_map<int, std::unordered_map<int, int>> map;
    for (int i = 0; i < arcnum; i++)
    {
        int start, end, weight;
        std::cin >> start >> end >> weight;
        map[start][end] = weight;
        map[end][start] = weight;
    }

    std::vector<int> dis(vexnum + 1, INT32_MAX); // 保存start到其余个点的距离
    dis[startpos] = 0;                           // 初始化，不要忘记
    dijkstra(map, dis, startpos, vexnum);

    std::cout << startpos << "到各顶点的距离是：";
    for (int i = 1; i <= vexnum; i++)
    {
        std::cout << dis[i] << " ";
    }
    return 0;
}
void dijkstra(std::unordered_map<int, std::unordered_map<int, int>> map, std::vector<int> &dis, int startpos, int vexnum)
{
    //优先队列(此处为小根堆)保存从起始位置到其余各点的距离
    //其可以在O(logn)内完成排序，利用其特性，可以很方便的找到当前从起始位置到其余各点的距离的最小值
    //大大降低了整体的时间复杂度
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pri_q;
    //pri_q.top().second为点i, pri_q.top().first 为startpos到点i的距离
    pri_q.emplace(0,startpos);
    std::vector<bool> visited(vexnum + 1,false); //标记该点是否被访问
    visited[startpos] = true; //起始位置自然已经被访问
    while (!pri_q.empty())
    {
        //auto[Dis,closestNode] = pri_q.top();
        int closestNode = pri_q.top().second; //未被访问，且到n的距离最短的点
        int Dis = pri_q.top().first; // start 到 closestNode 的距离
        pri_q.pop();
        visited[closestNode] = true;
        for(auto[next,weight] : map[closestNode]) //next为closestNode的后继节点(联想邻接表)
        {
            if(!visited[next])
            {
                if(Dis + map[closestNode][next] < dis[next])
                {
                    dis[next] = Dis + map[closestNode][next];
                    pri_q.emplace(dis[next],next); //距离更新就要入堆
                }
            }
        }
    }
   
}