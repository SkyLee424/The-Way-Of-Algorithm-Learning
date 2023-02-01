#include<iostream>
#include<vector>
int binary_search(std::vector<int> arr,int key)
{
    int l = 0, r = arr.size() - 1;//确定查找区间为[l,r]
    //int l = 0, r = arr.size(); [l,r)
    //while(l < r) l == r时退出
    while (l <= r) //由上述查找区间可知：循环退出条件为l > r
    {
        int mid = l + (r - l) / 2; //避免(l + r)溢出
        if(arr[mid] == key) return mid; //找到即退出
        else if(arr[mid] < key) l = mid + 1;
        else if(arr[mid] > key) r = mid - 1;
    }
    return -1;
}
/*寻找左侧边界的二分查找*/
//因为我们初始化 right = nums.size() - 1
//所以决定了我们的「搜索区间」是 [left, right]
//所以决定了 while (left <= right)
//同时也决定了 left = mid + 1 和 right = mid - 1
//因为我们需找到 target 的最左侧索引
//所以当 nums[mid] == target 时不要立即返回
//而要收紧右侧边界以锁定左侧边界
int left_bound(std::vector<int> arr,int key)
{

    int l = 0,r = arr.size() - 1;
    int res = r + 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if(arr[mid] == key) 
        {
            res = mid;
            r = mid - 1; //不要立即返回
        }
        else if(arr[mid] < key) l = mid + 1;
        else if(arr[mid] > key) r = mid - 1;
    }
    return res;
}
int right_bound(std::vector<int> arr,int key)
{
    int l = 0, r = arr.size() - 1;
    int res = l - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if(arr[mid] == key) 
        {
            res = mid;
            l = mid + 1; //不要立即返回
        }
        else if(arr[mid] < key) l = mid + 1;
        else if(arr[mid] > key) r = mid - 1;
    }
    // if(r < 0 || arr[r] != key) return -1; //没找到
    return res;
}
int main(void)
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for(int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    int target;
    std::cin >> target;
    std::cout << left_bound(arr, target) << std::endl;
    std::cout << right_bound(arr,target) << std::endl;
}