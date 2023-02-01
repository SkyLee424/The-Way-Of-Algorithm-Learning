#include <iostream>
#include <vector>
#include <queue>
// Sort类的方法均为升序
class Sort
{
public:
    void directly_insert_sort(std::vector<int> &arr)
    {
        int temp;
        // i前面的已经排好序
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i] < arr[i - 1])
            {
                temp = arr[i];
                int j = i - 1;
                for (; j >= 0 && temp < arr[j]; j--)
                {
                    arr[j + 1] = arr[j];
                }
                arr[j + 1] = temp;
            }
        }
    }
    void Binary_insertion_sort(std::vector<int> &arr)
    {
        int temp;
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i] < arr[i - 1])
            {
                int l = 0, r = i - 1;
                int temp = arr[i];
                while (l <= r)
                {
                    int mid = (l + r) / 2;
                    if (temp > arr[mid])
                        l = mid + 1;
                    else
                        r = mid - 1;
                }
                for (int j = i; j > r + 1; j--)
                {
                    arr[j] = arr[j - 1];
                }
                arr[r + 1] = temp;
            }
        }
    }
    void Bubble_sort(std::vector<int> &arr)
    {
        bool flag = true;
        for (int i = 0; i < arr.size() && flag; i++)
        {
            flag = false;
            for (int j = 1; j < arr.size() - i; j++)
            {
                if (arr[j] < arr[j - 1])
                {
                    flag = true;
                    std::swap(arr[j], arr[j - 1]);
                }
            }
        }
    }
    void quicksort(std::vector<int> &arr, int L, int R)
    {
        if (L >= R)
            return; // 递归出口
        int l = L, r = R;
        int pivot = arr[l];
        while (l < r)
        {
            while (l < r && arr[r] >= pivot)
            {
                r--;
            }
            if (l < r)
                arr[l] = arr[r];
            while (l < r && arr[l] <= pivot)
            {
                l++;
            }
            if (l < r)
                arr[r] = arr[l];
        }
        arr[l] = pivot;
        quicksort(arr, L, l - 1);
        quicksort(arr, r + 1, R);
    }
    void selection_sort(std::vector<int> &arr)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            int minpos = i;
            for (int j = i + 1; j < arr.size(); j++)
            {
                if (arr[j] < arr[minpos])
                    minpos = j;
            }
            std::swap(arr[i], arr[minpos]);
        }
    }

private:
    std::vector<int> mergesort(std::vector<int> l, std::vector<int> r)
    {
        std::vector<int> res;
        int i = 0, j = 0;
        int len0 = l.size(), len1 = r.size();
        while (i < len0 && j < len1)
        {
            if (l[i] < r[j])
            {
                res.push_back(l[i]);
                i++;
            }
            else
            {
                res.push_back(r[j]);
                j++;
            }
        }
        while (i < len0)
        {
            res.push_back(l[i]);
            i++;
        }
        while (j < len1)
        {
            res.push_back(r[j]);
            j++;
        }
        return res;
    }
    void HeapAdjust(std::vector<int> &arr, int start, int end)
    {
        // 调整堆为大根堆
        int temp = arr[start];
        for (int i = start * 2; i <= end; i *= 2)
        {
            if (i < end && arr[i] < arr[i + 1])
                i++; // 选取左右孩子最大的一个
            if (temp >= arr[i])
                break; // 说明该节点此时已经满足大根堆
            arr[start] = arr[i];
            start = i;
        }
        arr[start] = temp; // 不要忘记！！！
    }

public:
    std::vector<int> merge(std::vector<int> &arr, int L, int R)
    {
        if (L >= R)
            return arr;
        int mid = (L + R) / 2;
        std::vector<int> l;
        std::vector<int> r;
        for (int i = L; i <= mid; i++)
        {
            l.push_back(arr[i]);
        }
        for (int i = mid + 1; i <= R; i++)
        {
            r.push_back(arr[i]);
        }
        l = merge(l, 0, l.size() - 1);
        r = merge(r, 0, r.size() - 1);
        return mergesort(l, r);
    }
    void heap_sort(std::vector<int> &arr)
    {
        int n = arr.size();
        for (int i = n / 2; i >= 0; i--)
        {
            HeapAdjust(arr, i, n - 1);
        }
        for (int i = n - 1; i > 0; i--)
        {
            std::swap(arr[0], arr[i]); // 将堆顶元素置后（堆顶元素为堆中所有元素最大值）
            HeapAdjust(arr, 0, i - 1); // end = i - 1（不包括置后的元素）
        }
    }
    void radix_sort(std::vector<int> &arr)
    {
        int maxnum = arr[0];
        for (auto &i : arr)
        {
            maxnum = std::max(maxnum, i);
        }
        int n = 0;
        while (maxnum)
        {
            n++;
            maxnum /= 10;
        }
        std::vector<std::queue<int>> bucket(10);
        int radix = 1; // 基数
        for (int i = 0; i < n; i++)
        {
            for (auto &j : arr)
            {
                bucket[(j / radix) % 10].push(j);
            }
            int cur = 0;
            for (int j = 0; j < 10; j++)
            {
                while (!bucket[j].empty())
                {
                    arr[cur++] = bucket[j].front();
                    bucket[j].pop();
                }
            }
            radix *= 10;
        }
    }
};
int main(void)
{
    Sort s;
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    //s.directly_insert_sort(arr);
    // s.Binary_insertion_sort(arr);
    // s.Bubble_sort(arr);
    // s.quicksort(arr, 0, n - 1);
    // s.selection_sort(arr);
    // arr = s.merge(arr,0,n - 1);
    // s.heap_sort(arr);
    s.radix_sort(arr);
    for (auto &i : arr)
    {
        std::cout << i << " ";
    }
}