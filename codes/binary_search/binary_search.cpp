#include <CL/sycl.hpp>
#include <iostream>
#include <vector>

using namespace cl::sycl;

// Define o tamanho do vetor
constexpr size_t SIZE = 1024;

// Define o valor a ser buscado
constexpr int TARGET_VALUE = 5;

int main() {
  // Inicializa o vetor com números aleatórios
  std::vector<int> vec(SIZE);
  for (int i = 0; i < SIZE; i++) {
    vec[i] = i;
  }

  // Cria uma fila SYCL para executar o código
  queue q(default_selector{});

  // Cria um buffer SYCL para armazenar o vetor na memória do dispositivo
  buffer<int, 1> buf(vec.data(), range<1>(SIZE));

  // Realiza a busca binária paralelizada
  int found_index = -1;
  q.submit([&](handler &h) {
    // Cria um acesso de leitura ao buffer
    auto acc = buf.get_access<access::mode::read>(h);

    // Cria um acesso de escrita ao índice encontrado
    buffer<int, 1> found_index_buf(&found_index, range<1>(1));
    accessor<int, 1, access::mode::write, access::target::global_buffer> found_index_acc(found_index_buf, h);

    // Define o tamanho do grupo de trabalho
    h.parallel_for<class binary_search>(range<1>(SIZE), [=](id<1> idx) {
      // Realiza a busca binária
      int start = 0;
      int end = SIZE - 1;
      while (start <= end) {
        int mid = (start + end) / 2;
        if (acc[mid] == TARGET_VALUE) {
          // Atualiza o índice encontrado
          found_index_acc[0] = mid;
          return;
        } else if (acc[mid] < TARGET_VALUE) {
          start = mid + 1;
        } else {
          end = mid - 1;
        }
      }
    });
  });

  // Espera a fila terminar de executar
  q.wait();

  // Verifica se o valor foi encontrado
  if (found_index != -1) {
    std::cout << "Valor encontrado no índice " << found_index << std::endl;
  } else {
    std::cout << "Valor não encontrado" << std::endl;
  }

  return 0;
}
