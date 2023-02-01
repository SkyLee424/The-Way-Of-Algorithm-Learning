#include<iostream>
#include<string>
#include<vector>
// 当 pattern[j] 与 original[i] 不匹配时
// 利用 pattern 相同前缀与 original[i] 前面的一部分匹配
// 避免 i 指针后移，提高效率
// next 数组：前缀表
// 在这里，next[i] 表示：i 之前（不包括 i）的最长相同前后缀长度
// 例如：aabaab
// next数组对应为 0 0 1 0 1 2
// 当 pattern[5] 与 original[i] 不匹配时
// j 指针回到 2
// 就可以利用 aa（pattern[0]、pattern[1]） 与 original[i - 1] original[i - 2] 匹配
class Solution
{
    std::vector<int> getNext(const std::string &s)
    {
        int n = s.size(); // s 是模式串
        std::vector<int> next(n);
        next[0] = -1; // 此时，j 指针无法移动，初始化为 -1 是为了告诉 i 指针移动
        int i = 0, j = -1;
        while (i < n - 1)
        {
            if(j == -1 || s[i] == s[j])
            {
                // 找到相同前后缀
                // i、j 指针同时后移
                // next[++i] = ++j;
                // 优化后：
                if(s[++i] == s[++j])
                {
                    next[i] = next[j];
                }
                else next[i] = j;
            }
            // 没找到，j 回到应该回到的位置
            else j = next[j];
        }
        return next;
    }

public:
    int Kmp(const std::string &original, const std::string &pattern)
    {
        int n = original.size(), m = pattern.size();
        auto next = getNext(pattern); // next 数组只与 pattern 有关(因为是找pattern中的最长相同前后缀)
        int i = 0, j = 0;
        while (i < n && j < m)
        {
            // 匹配成功或 j 指针无法前移
            if(j == -1 || original[i] == pattern[j])
            {
                ++i;
                ++j;
            }
            // 匹配失败
            else j = next[j];
        }
        return j == m ? i - j : -1;
    }    
};

int main(void)
{
    std::string s0 = "", s1 = "";
    std::getline(std::cin, s0);
    std::getline(std::cin, s1);
    Solution s;
    std::cout << s.Kmp(s0,s1) << std::endl;
    std::cout << (int)s0.find(s1) << std::endl;
}