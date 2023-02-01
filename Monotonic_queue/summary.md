# 单调队列

## 一、定义

单调队列是一种：队列内元素始终具有单调性的队列。

> 不断地向缓存数组里读入元素，也不时地去掉最老的元素，不定期的询问当前缓存数组里的最大（小）的元素

## 二、类型

一般来说，分为两种类型：
* 单调递增队列
* 单调递减队列

## 三、适用范围

什么时候用单调队列？

当元素以一维方式存储，并且要**寻找特定区间内的最值**，可以考虑使用单调队列

## 四、例题

### [239. 滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/)

**分析：**

单调队列模板题

我们维护一个单调递减的队列，即队头为队内最大的元素，队尾为队内最小的元素

如何维护？

1. 使用 deque 容器，方便同时对队头、队尾元素进行操作
2. push 操作：由于队列是单调递减的，因此，**当 push 的元素大于队尾元素时，就直接将队尾元素舍弃**，它对我们的最大值并无影响
3. pop 操作：当 pop 的元素为队头元素，将其 pop 掉，否则不做操作（因为这个 pop 的元素对最大值并无影响）

这里引用评论区的一句话，帮助理解：

> 单调队列真是一种让人感到五味杂陈的数据结构，它的维护过程更是如此.....就拿此题来说，队头最大，往队尾方向单调......有机会站在**队头的老大永远心狠手辣**，当它**从队尾杀进去**的时候，如果它发现这里面**没一个够自己打**的，它会毫无人性地**屠城**，把原先队里的人头全部丢出去，转身建立起自己的政权，野心勃勃地准备开创一个新的王朝.....这时候，它的人格竟发生了一百八十度大反转，它变成了一位胸怀宽广的慈父！它热情地请那些新来的“小个子”们入住自己的王国......然而，这些**小个子**似乎天性都是一样的——嫉妒心强，倘若**见到比自己还小的居然更早入住王国**，它们会心狠手辣地找一个夜晚**把它们通通干掉**，好让自己享受更大的“蛋糕”；当然，**遇到比自己强大的**，它们也**没辙**，乖乖夹起尾巴做人。像这样的暗杀事件每天都在上演，虽然王国里日益笼罩上白色恐怖，但是好在没有后来者强大到足以干翻国王，江山还算能稳住。直到有一天，闯进来了一位真正厉害的角色，就像当年打江山的国王一样，手段狠辣，野心膨胀，于是又是大屠城......历史总是轮回的。

Code :

~~~C++
class singleQueue
{
    std::deque<int> q;

public:
    void push(int val)
    {
        // 单调递减队列
        // 新来的发现竟然还有比自己小的在队列中
        // 直接杀掉
        // 如果全杀掉了，自己就当老大了
        while (!q.empty() && val > q.back())
        {
            q.pop_back(); // 杀掉队列的最后一个（整个队列中最小的元素)
        }
        q.push_back(val);
    }
    void pop(int val)
    {
        // 时代在变化，窗口在移动
        // 昔日的老大，终将老矣
        if(!q.empty() && q.front() == val)
        {
            q.pop_front();
        }
    }
    int front(void)
    {
        return q.front();
    }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        singleQueue q;
        int i = 0;
        for(; i < k; ++i)
        {
            q.push(nums[i]);
        }
        std::vector<int> res;
        res.push_back(q.front());
        for(; i < nums.size(); ++i)
        {
            q.pop(nums[i - k]);
            q.push(nums[i]);
            res.push_back(q.front());
        }
        return res;
    }
};
~~~

### [918. 环形子数组的最大和](https://leetcode.cn/problems/maximum-sum-circular-subarray/description/)

**分析：**

此题如果使用单调队列解答，难度还是比较大，主要难点有：

1. 环形数组如何处理？
2. 如何抽象成求区间最值问题？

#### 处理环形数组

要处理环形数组，我们只需要在原数组的后面再复制一份原数组即可

比如，[1, 2, 3, 4]，扩展后就为 [1, 2, 3, 4, 1, 2, 3] 

#### 抽象成区间最值问题

首先，既然涉及到了区间和问题，我们可以考虑构造前缀和数组

比如，[1, 2, 3, 4]，前缀和数组为：[0, 1, 3, 6, 10]

此时，我们就能快速得到某一个区间的和

比如，我们要求下标为 j ~ i 的区间的和，只需要求 sum[i + 1] - sum[j] 即可

因此，要想得到下标为 j ~ i 的区间的和的**最大值**，当 i 的位置固定时，只需要让 sum[j] 最小，此时就能得到以 i 为终止位置的区间的和的最大值了

如何快速得到特定区间内 sum[j] 的最小值？

单调递增队列！

Code：

~~~C++
// 单调递增队列 
class singleQueue
{
    std::deque<int> q;

public:
    void push(int val)
    {
        while (!q.empty() && val < q.back())
        {
            q.pop_back();
        }
        q.push_back(val);
    }

    void pop(int val)
    {
        if(!q.empty() && q.front() == val)
        {
            q.pop_front();
        }
    }

    int front(void)
    {
        return q.front();
    }
};

// 求 nums 前缀和 sum
// 区间和 = sum[i] - sum[j]
// 当 i 固定时，只需要找到 sum[j] 的最小值
// 因此，问题转化为：
// 求 窗口长度为 n 的窗口元素中的元素
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int res = INT32_MIN;
        int n = nums.size();
        // 扩张 nums
        for(int i = 0; i < n - 1; ++i)
        {
            nums.push_back(nums[i]);
            res = std::max(res, nums[i]);
        }
        res = std::max(res, nums[n - 1]);
        // 由于题中不允许有空数组，因此，需要特别判断一下
        if(res <= 0) return res;
        // 求前缀和
        std::vector<int> sum(nums.size() + 1, 0);
        for(int i = 1; i <= nums.size(); ++i)
        {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        singleQueue q;
        q.push(0);
        int i = 1;
        // 计算第一个窗口
        for(; i <= n; ++i)
        {
            q.push(sum[i]);
            res = std::max(res, sum[i] - q.front());
        }
        // 开始滑动
        for(; i < nums.size(); ++i)
        {
            // 弹出窗口外的元素
            q.pop(sum[i - n - 1]);
            // 加入新元素
            q.push(sum[i]);
            res = std::max(res, sum[i] - q.front());
        }
        return res;
    }
};
~~~

## 五、总结

1. 当元素以一维方式存储，并且要**寻找特定区间内的最值**，可以考虑使用单调队列
2. 单调队列没有固定模板，不同的题，有不同的实现方式，push、pop 操作会有很大不同

