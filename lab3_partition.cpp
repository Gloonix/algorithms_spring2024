#include <iostream>
#include <functional>

template <typename T, typename Comparator = std::less<T>>
int partition(T *arr, int l, int r, Comparator cmp = Comparator())
{
    T pivot = arr[l];
    int i = l + 1;
    int j = r;
    
    while (1)
    {
        while (i <= r && cmp(arr[i], pivot))
            i++;
        while (cmp(pivot, arr[j]))
            j--;
        
        if (i >= j)
        {
            std::swap(arr[l], arr[j]);
            return j;
        }
        
        std::swap(arr[i], arr[j]);
        i++;
        j--;
    }
}

template <typename T, typename Comparator = std::less<T>>
T kth_statistic(T *arr, int k, int l, int r, Comparator cmp = Comparator())
{
    int pivot_pos = partition(arr, l, r, cmp);
    
    if (pivot_pos == k)
    {
        return arr[pivot_pos];
    }
    if (pivot_pos > k)
    {
        return kth_statistic(arr, k, l, pivot_pos - 1, cmp);
    }
    return kth_statistic(arr, k, pivot_pos + 1, r, cmp);
}

int main(int argc, const char * argv[]) {
    int n = 0;
    std::cin >> n;
    
    std::string *arr = new std::string[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    
    for (int i = 0; i < n; i++)
    {
        std::cout << kth_statistic(arr, i, 0, n - 1) << " ";
    }
    std::cout << std::endl;
    
    delete[] arr;
    return 0;
}
