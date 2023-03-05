#include <CL/sycl.hpp>
#include "oneapi/mkl.hpp"
#include <bits/stdc++.h>

using namespace std;

constexpr int n = 20;
int incA = 1,incB = 1;

int main(){
    sycl :: queue qs {sycl :: cpu_selector{}};
    vector < int > A(n);
    vector < int > B(n);

    // creating buffers
    sycl::buffer buffA{A};
    sycl::buffer buffB{B};
    sycl::buffer < int, 1 > ans { sycl::range { 1 }};
    //submitting work in queue
    qs.submit([&] (sycl :: handler &h){
        // creating accessor
        sycl::accessor accA{buffA,h};
        sycl::accessor accB{buffB,h};
        h.parallel_for(sycl::range{n},[=] (sycl::id<1> idx){
            // filling vectors
            int i = idx[0];
            accA[i] = i * 3 + 1;
            accB[i] = i * 2 - 2;
        });
    }).wait();
    
    // usage a oneMKL library function, dot product
    oneapi::mkl::blas::column_major::dot(qs,buffA,incA,buffB,incB,ans);

    sycl::host_accessor hostAns { ans };
    cout << hostAns[0] << "\n";
    return 0;
}