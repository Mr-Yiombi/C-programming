// Lab1 - C/C++ code conversion
    // Subjects:
    // 1. C vs C++
    // 2. #define vs const
    // 3. printf vs cout
    // 4. memory allocation - new & delete
    // 5. pointer vs reference
    //
    // TODO: Convert a C program into C++ 
    // - Use a reference operator, but not a pointer.
    // - Use const, but not #define.
    // - Use new and delete operators.
    // - Use cout & endl instead of printf().
    // - Do not change the return type of sum().
    //     
#if 0
#include <stdio.h>
#define N 40

void sum(int d[], int n, int* p) {
    *p = 0;
    for(int i = 0; i < n; ++i) 
        *p = *p + d[i];
} 

int main(int argc, char *argv[]) {
    int total = 0;
    int data[N];

    for(int i = 0; i < N; ++i) 
        data[i] = i;
    
    sum(data, N, &total);  // total - pass-by-pointer
    printf("The total is %d\n", total);
    return 0;
}
#else 
#include <iostream>

using namespace std;

const int N = 40;

void sum(int d[], int n, int &p){
    p = 0;
    for(int i=0;i<N;i++){
        p = p + d[i];
    }
    
}

int main(int argc, char *argv[]) {

    int total = 0;
    int *data = new int[N];
    for(int i = 0; i < N; ++i) 
        data[i] = i;
    sum(data,N,total);

    cout << "The Total is " << total << "\n";

    delete[] data;
    return 0;
}
#endif