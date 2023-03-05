#include <CL/sycl.hpp>
#include <iostream>

constexpr size_t N = 1024;

int main() {
    // Create two vectors to sum
    std::vector<int> a(N, 1);
    std::vector<int> b(N, 2);
    std::vector<int> c(N, 0);

    try {
        // Create a SYCL queue to launch kernels on
        sycl::queue q{sycl::default_selector{}};

        // Create buffers to hold the input and output data
        sycl::buffer<int, 1> a_buf{a.data(), sycl::range<1>{N}};
        sycl::buffer<int, 1> b_buf{b.data(), sycl::range<1>{N}};
        sycl::buffer<int, 1> c_buf{c.data(), sycl::range<1>{N}};

        // Submit a command group to the queue
        q.submit([&](sycl::handler& h) {
            // Get accessors to the input and output buffers
            auto a = a_buf.get_access<sycl::access::mode::read>(h);
            auto b = b_buf.get_access<sycl::access::mode::read>(h);
            auto c = c_buf.get_access<sycl::access::mode::write>(h);

            // Launch a parallel kernel to sum the vectors
            h.parallel_for<class vector_add>(sycl::range<1>{N}, [=](sycl::id<1> i) {
                c[i] = a[i] + b[i];
            });
        });

        // Wait for the command group to finish and then print the result
        q.wait();
        std::cout << "Result: ";
        for (int i = 0; i < N; ++i) {
            std::cout << c[i] << " ";
        }
        std::cout << std::endl;

    } catch (sycl::exception e) {
        std::cerr << "SYCL exception caught: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}