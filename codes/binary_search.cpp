


#include <CL/sycl.hpp>
#include <iostream>
#include <vector>

namespace sycl = cl::sycl;

class BinarySearchKernel;

// Função de busca binária que será executada em paralelo
template <typename T>
int parallelBinarySearch(sycl::queue& q, const std::vector<T>& data, const T& value) {
  size_t n = data.size();

  // Crie buffers para os dados de entrada e de saída
  sycl::buffer<T> data_buf(data);
  sycl::buffer<int> result_buf(1);

  // Inicie o kernel de busca binária
  q.submit([&](sycl::handler& h) {
    // Acesso somente leitura aos dados de entrada
    sycl::accessor<T, 1, sycl::access::mode::read, sycl::access::target::global_buffer>
        data_accessor(data_buf, h);

    // Acesso somente escrita ao resultado
    sycl::accessor<int, 1, sycl::access::mode::write, sycl::access::target::global_buffer>
        result_accessor(result_buf, h);

    // Crie um objeto kernel e passe os acessores como argumentos
    h.parallel_for<BinarySearchKernel>(sycl::range<1>(1), [=](sycl::id<1> idx) {
      int left = 0;
      int right = n - 1;
      int result = -1;

      while (left <= right) {
        int mid = (left + right) / 2;

        if (data_accessor[mid] == value) {
          result = mid;
          break;
        } else if (data_accessor[mid] < value) {
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      }

      result_accessor[0] = result;
    });
  });

  // Espere a finalização do kernel e leia o resultado
  auto result = result_buf.get_access<sycl::access::mode::read>()[0];
  return result;
}

int main() {
  const int size = 1024;
  std::vector<int> data(size);

  // Preencha o vetor com valores crescentes
  for (int i = 0; i < size; ++i) {
    data[i] = i;
  }

  // Escolha um valor para buscar
  int value = 512;

  // Crie uma fila SYCL para execução em GPU ou CPU
  sycl::queue q(sycl::gpu_selector{});

  // Execute a busca binária em paralelo
  int result = parallelBinarySearch(q, data, value);

  if (result != -1) {
    std::cout << "Valor " << value << " encontrado no índice " << result << std::endl;
  } else {
    std::cout << "Valor " << value << " não encontrado" << std::endl;
  }

  return 0;
}
