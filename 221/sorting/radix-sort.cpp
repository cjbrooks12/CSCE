//============================================================================
// Name        : radix-sort.cpp
// Author      : Troy Korenek
// Date        : 9-22-13
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
//#include "std_lib_facilities_3.h"

// A utility function to get maximum value in A[]
int getMax(int A[], int size)
{
    int mx = A[0];
    for (int i = 1; i < size; i++)
        if (A[i] > mx)
            mx = A[i];
    return mx;
}
 
// A function to do counting sort of arr[] according to
// the digit represented by exp.
int countSort(int A[], int size, int exp)
{
    int output[size]; // output array
    int i, count[10] = {0};
 
    // Store count of occurrences in count[]
    for (i = 0; i < size; i++)
        count[ (A[i]/exp)%10 ]++;
 
    // Change count[i] so that count[i] now contains actual position of
    // this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = size - 1; i >= 0; i--)
    {
        output[count[ (A[i]/exp)%10 ] - 1] = A[i];
        count[ (A[i]/exp)%10 ]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to curent digit
    for (i = 0; i < size; i++)
        A[i] = output[i];
}
 
// The main function to that sorts arr[] of size n using Radix Sort
//void RadixSort::sort(int A[], int size)
void RadixSort(int A[], int size)
{
    // Find the maximum number to know number of digits
    int m = getMax(A, size);
 
    // Do counting sort for every digit. Note that instead of passing digit number,
    // exp is passed. exp is 10^i where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(A, size, exp);
}
 /*
// A utility function to print an array
void print(int A[], int size)
{
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
}
 
//test
/*
int main()
{
    int A[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int size = sizeof(A)/sizeof(A[0]);
    RadixSort(A, size);
    print(A, size);
    return 0;
}*/

