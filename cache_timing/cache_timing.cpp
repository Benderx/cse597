#include <iostream>
#include <fstream>
#include <chrono>
#include <unistd.h>
#include <stdlib.h>
#include <cmath>

typedef int testing_type;


std::chrono::duration<double, std::nano> cast_nano(std::chrono::duration<double> x)
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(x);
}

std::chrono::duration<double, std::micro> cast_micro(std::chrono::duration<double> x)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(x);
}

void allocate_arr(testing_type* arr, unsigned long size)
{
    for(unsigned long i = 0; i < size; i++)
    {
        arr[i] = 2; //allocating to something random
    }
}

int to_kb(int bytes)
{
    return 1024 / bytes;
}


int main()
{
    std::chrono::time_point<std::chrono::system_clock> t1, t2;
    std::chrono::duration<double, std::nano> result;
    std::ofstream f;

    unsigned long stride;
    unsigned long arr_size;
    // int dummy_loader;
    unsigned long counter = 0;

    int arr_size_start = 4 * to_kb(sizeof(testing_type));
    int stride_start = 1;
    
    int stride_doublings = 22;
    int array_doublings = 14;
    int sims = 2000;

    f.open("out.csv");

    // write x axis values
    stride = stride_start;
    for(int j = 0; j < stride_doublings; j++)
    {
        f << std::fixed << stride*sizeof(testing_type) << ",";
        stride *= 2;
    }
    f << "-\n";

    // write legend values
    arr_size = arr_size_start;
    for(int j = 0; j < array_doublings; j++)
    {
        f << std::fixed << arr_size*sizeof(testing_type) << ",";
        arr_size *= 2;
    }
    f << "-\n";

    //mallocs and allocates the maximum size of the array
    testing_type* arr = (testing_type*) malloc(arr_size * sizeof(testing_type));
    allocate_arr(arr, arr_size);

    arr_size = arr_size_start; // resets array to initial size
    for(int i = 0; i < array_doublings; i++)
    {
        stride = stride_start; // resets stride to its initial size        
        for(int j = 0; j < stride_doublings && stride < arr_size; j++)
        {
            unsigned long k;
            counter = 0;
            t1 = std::chrono::system_clock::now();
            for(int z = 0; z < sims; z++)
            {
                for(k = 0; k < arr_size; k+=stride)
                {
                    // dummy_loader = *(arr+k); // loads the value into a dummy variable
                    *(arr+k);
                    counter++;
                }
            }
            t2 = std::chrono::system_clock::now();
            result = cast_nano(t2 - t1);
            double temp = (double)result.count() / counter;
            f << std::fixed << temp << ",";
            stride *= 2;
            std::cout << "stride: " << stride << " counter: " << counter << std::endl;
        }
        f << "-\n";
        std::cout << "arr_size: " << arr_size << std::endl;
        arr_size *= 2;
    }

    free(arr);
    f.close();
    return 0;
}