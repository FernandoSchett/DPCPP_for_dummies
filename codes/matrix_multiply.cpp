#include <CL/sycl.hpp>
#include <iostream>
#include <vector>

using namespace cl::sycl;

// Define a função para multiplicação de matrizes
void matrix_multiply(queue& q, int *A, int *B, int *C, int N, int M, int K) {
  // Crie buffers para matrizes A, B e C
  buffer<int, 2> A_buf(A, range<2>{N, M});
  buffer<int, 2> B_buf(B, range<2>{M, K});
  buffer<int, 2> C_buf(C, range<2>{N, K});

  // Execute a multiplicação de matrizes em um kernel
  q.submit([&](handler& h) {
    // Acessa os buffers para matrizes A, B e C
    auto A_acc = A_buf.get_access<handler::read>(h);
    auto B_acc = B_buf.get_access<handler::read>(h);
    auto C_acc = C_buf.get_access<handler::write>(h);

    // Defina o tamanho dos blocos a serem usados ​​para paralelização
    const int block_size = 16;

    // Execute a multiplicação de matrizes em blocos
    h.parallel_for(nd_range<2>{{N, K}, {block_size, block_size}}, [=](nd_item<2> item) {
      int row = item.get_global_id(0);
      int col = item.get_global_id(1);

      int sum = 0;
      for (int i = 0; i < M; i++) {
        sum += A_acc[row][i] * B_acc[i][col];
      }

      C_acc[row][col] = sum;
    });
  });

  // Aguarde a conclusão da tarefa
  q.wait();
}

int main() {
  // Defina as dimensões das matrizes
  const int N = 1024;
  const int M = 512;
  const int K = 256;

  // Crie matrizes A, B e C
  std::vector<int> A(N * M, 1);
  std::vector<int> B(M * K, 2);
  std::vector<int> C(N * K, 0);

  // Selecione um dispositivo de computação
  default_selector selector;
  queue q(selector);

  // Multiplique as matrizes A e B para obter a matriz C
  matrix_multiply(q, A.data(), B.data(), C.data(), N, M, K);

  // Verifique o resultado
  bool passed = true;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      int sum = 0;
      for (int k = 0; k < M; k++) {
        sum += A[i * M + k] * B[k * K + j];
      }
      if (C[i * K + j] != sum) {
        passed = false;
        break;
      }
    }
  }

  if (passed) {
    std::cout << "Matriz multiplicação concluída com sucesso!\n";
  } else {
    std::cout << "Matriz multiplicação falhou.\n";
  }

  return 0;
}
