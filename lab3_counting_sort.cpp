#include <iostream>
#include <cassert>

void counting_sort(int *arr, int n)
{
    assert( arr != nullptr );
    assert( n > 0 );
    
    int minVal = arr[0];
    int maxVal = arr[0];
    
    for (int i = 1; i < n; i++)
    {
        minVal = std::min(minVal, arr[i]);
        maxVal = std::max(maxVal, arr[i]);
    }
    
    int countBufSize = maxVal - minVal + 1;
    int *countBuf = new int[countBufSize]();
    
    for (int i = 0; i < n; i++)
    {
        countBuf[arr[i] - minVal]++;
    }
    
    int *tmpBuf = new int[n]();
    
    for (int i = 1; i < countBufSize; i++)
    {
        countBuf[i] += countBuf[i - 1];
    }
    
    for (int i = n - 1; i >= 0; i--)
    {
        int countBufPos = arr[i] - minVal;
        countBuf[countBufPos]--;
        tmpBuf[countBuf[countBufPos]] = arr[i];
    }
    
    for (int i = 0; i < n; i++)
    {
        arr[i] = tmpBuf[i];
    }
    
    /*
    int p = 0;
    for (int i = 0; i < countBufSize; i++)
    {
        for (int j = 0; j < countBuf[i]; j++)
        {
            arr[p++] = i + minVal;
        }
    }
    */
    
    delete[] countBuf;
    delete[] tmpBuf;
}

int main(int argc, const char * argv[]) {
    int n = 0;
    std::cin >> n;
    
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    
    counting_sort(arr, n);
    
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    delete[] arr;
    return 0;
}
