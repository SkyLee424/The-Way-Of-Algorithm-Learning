#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
/*
滑动窗口大体分为两种类型：
窗口长度不变型、窗口长度改变型
而窗口长度改变型又可分为：最大窗口长度、最短窗口长度
*/
/*窗口长度不变型*/
using namespace std;
class Example
{
public:
    /*窗口长度不变型*/
    /*窗口长度固定为k*/
    /*Leetcode: 2461. 长度为 K 子数组中的最大和*/
    long long example0(vector<int> &nums, int k)
    {
        std::unordered_map<int, int> cnt; // 存储num出现的次数
        int l = 0, r;
        long long res = 0, sum = 0;
        // 一、寻找第一个滑动窗口
        for (; l < k; l++)
        {
            cnt[nums[l]]++;
            sum += nums[l];
        }
        // 满足条件
        if (cnt.size() == k)
        {
            res = std::max(res, sum); // 二、更新res
        }
        // 三、从第二个窗口开始滑动
        for (l = 1, r = k; r < nums.size(); l++, r++)
        {
            // 更新当前窗口的sum
            sum -= nums[l - 1]; // 减去不属于当前窗口的元素
            sum += nums[r];
            cnt[nums[r]]++;
            // 四、弹出不属于当前窗口的元素
            auto it = cnt.find(nums[l - 1]);
            if ((*it).second == 1)
            {
                cnt.erase(it);
            }
            else
                (*it).second--;
            // 满足条件
            if (cnt.size() == k)
            {
                res = std::max(res, sum); // 五、更新res
            }
        }
        return res;
    }
    /*最大窗口长度型*/
    /*Leetcode:3. 无重复字符的最长子串*/
    int example1(string s)
    {
        int res = 0;
        unordered_map<char, int> map;
        int l = 0, r = 0;
        while (r < s.length())
        {
            // 在不满足条件的情况下，最保守地压缩l，尽可能少的缩小窗口长度，满足条件立即退出
            while (l < s.length() && map.find(s[r]) != map.end())
            {
                map.erase(s[l]);
                l++;
            }
            map.emplace(s[r], r);
            int size = map.size();
            // 满足条件立即比较
            res = std::max(res, size);
            r++; // 右边界右移
        }
        return res;
    }
    /*最短窗口长度型*/
    /*Leetcode: 209. 长度最小的子数组*/
    int example2(int target, vector<int> &nums)
    {
        int l = 0, r = 0;
        int res = INT32_MAX, temp = 0;
        while (r < nums.size())
        {
            temp += nums[r];
            // 在满足条件下，尽可能地大的缩小窗口长度
            while (temp >= target)
            {
                res = min(res, r - l + 1); // 满足条件就更新res的值
                l++;                       // 左边界右移，缩小窗口长度
            }
            r++;
        }
        return res == INT32_MAX ? 0 : res;
    }
};
// int main(void)
// {
//     Example e;
//     int n,k;
//     cin >> n >> k;
//     vector<int> nums(n);
//     for(int i = 0;i < n;i++)
//     {
//         cin >> nums[i];
//     }
//     cout << e.example0(nums,k);
// }