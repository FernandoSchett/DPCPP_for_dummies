// /%***************************
// %  Code: 
// %    arrayReduction.cpp
// %
// % Purpose:
// %   Parallel code array reduction in Cpp 
// %   with DPCPP
// %
// %  Modified:
// %   fev 28 2023 19:20
// %
// %  Author:
// %    Orlando Mota Pires [orlando.pires 'at' fbter.org.br]
// %
// %  How to Compile:
// %    Go to dpcpp-for-dummies directory and run the following: 
// %      dpcpp -O2 -g -std=c++17 -o arrayReduction codes/arrayReduction.cpp
// %
// %  How to Execute: 
// %    ./arrayReduction 
// %
// %*************************

#include <CL/sycl.hpp>
#include <array>
#include <iostream>
#if FPGA || FPGA_EMULATOR
#include <CL/sycl/INTEL/fpga_extensions.hpp>
#endif

using namespace sycl;

// Array type and data size for this example.
constexpr size_t array_size = 151;
typedef std::array<int, array_size> IntArray;

// Create an exception handler for asynchronous SYCL exceptions
static auto exception_handler = [](sycl::exception_list e_list) {
  for (std::exception_ptr const &e : e_list) {
    try {
      std::rethrow_exception(e);
    }
    catch (std::exception const &e) {
#if _DEBUG
      std::cout << "Failure" << std::endl;
#endif
      std::terminate();
    }
  }
};

void VectorAdd(queue &q, IntArray &array, int *sum_parallel) {

  range<1> num_items{array.size()};
  buffer array_buf(array.data(), num_items);
  
  q.submit([&](handler &h) {
    accessor array_a(array_buf, h, read_only);
    h.parallel_for(num_items, [=](auto i) { *sum_parallel += array_a[i]; });
  });

}

void InitializeArray(IntArray &array) {
  for (size_t i = 0; i < array.size(); i++) array[i] = i;
}

int main() {

  #if FPGA_EMULATOR
    INTEL::fpga_emulator_selector d_selector;
  #elif FPGA
    INTEL::fpga_selector d_selector;
  #else
    default_selector d_selector;
  #endif

  IntArray array;
  int sum_sequential = 0, sum_parallel = 0;


  InitializeArray(array);

  try {
    queue q(d_selector, exception_handler);

    std::cout << "Running on device: " << q.get_device().get_info<info::device::name>() << "\n";
    std::cout << "Vector size: " << array.size() << "\n";

    VectorAdd(q, array, &sum_parallel);
  } catch (exception const &e) {
    std::cout << "An exception is caught for vector add.\n";
    std::terminate();
  }

  for (size_t i = 0; i < array.size(); i++)
    sum_sequential += array[i];

  if(sum_sequential == sum_parallel){
    std::cout << "Array reduction worked successfully\n";
    std::cout << "\nSum_parallel: " << sum_parallel << std::endl;
    std::cout << "Sum_sequential: " << sum_sequential << std::endl;
  }else{
    std::cout << "The parallel and sequential sums dont match. :(\n\n";
    std::cout << "Sum_sequential: " << sum_sequential << std::endl;
    std::cout << "Sum_parallel: " << sum_parallel << std::endl;
   
  }

  return 0;
}
