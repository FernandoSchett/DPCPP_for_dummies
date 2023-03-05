#include <CL/sycl.hpp>
#include <bits/stdc++.h>

using namespace std;

constexpr int n = 20;


int main(){
    sycl :: queue qs {sycl :: cpu_selector{}};
    vector < int > primes(n * n + 1, 1);

    // creating buffers
    sycl::buffer buffPrimes{primes};
    //submitting work in queue
    qs.submit([&] (sycl :: handler &h){
        // creating accessor
        sycl::accessor accPrimes{buffPrimes,h};
        h.parallel_for(sycl::range{n},[=] (sycl::id<1> idx){
            // excluding all multiple values of i
            int i = idx[0];
            if(i >= 2){
                int size = n * n;
                for(int k = i + i; k <= size; k += i)
                    accPrimes[k] = 0;
            }
            
        });
    }).wait();
    
    // view prime numbers
    for(int i = 2; i <= n * n; i ++)
        if(primes[i])
            cout << i << " ";
    cout << "\n";
    return 0;
}