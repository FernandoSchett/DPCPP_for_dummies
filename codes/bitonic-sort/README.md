# Exemplo de Bitonic Sort

*Esta é uma versão em portguês e mais simplificada do README original feito pela intel para o algoritmo bitonic-sort*

Este exemplo de código demonstra a implementação do bitonic sort usando o Intel Data Parallel C++ para transferir a computação para uma GPU. Nesta implementação, é fornecida uma sequência aleatória de 2**n elementos (onde n é um número positivo) como entrada, e o algoritmo classifica a sequência em paralelo. A sequência resultante está em ordem crescente.

Para obter instruções abrangentes sobre programação DPC++, consulte https://software.intel.com/en-us/oneapi-programming-guide e pesquise com base em termos relevantes mencionados nos comentários.
  
| Otimizado para                    | Description
|:---                               |:---
| Sistema operacional               | Linux Ubuntu 18.04
| Hardware                          | Skylake com GEN9 ou mais recente
| Software                          | Compilador Intel® oneAPI DPC++/C++
| O que você aprenderá              | Implementar o bitonic sort usando o compilador Intel® oneAPI DPC++/C++
| Tempo estimado de conclusão       | 15 minutos


## Propósito

O algoritmo converte uma sequência aleatória de números em uma sequência bitônica (duas sequências ordenadas) e, em seguida, mescla essas duas sequências ordenadas em uma sequência ordenada. O algoritmo bitonic sort é descrito brevemente da seguinte forma:

- Primeiro, ele decompõe a sequência aleatória de tamanho 2**n em 2**(n-1) pares, onde cada par consiste em 2 elementos consecutivos. Observe que cada par é uma sequência bitônica.
- Passo 0: para cada par (sequência de tamanho 2), os dois elementos são trocados para que os dois pares consecutivos formem uma sequência bitônica em ordem crescente, os próximos dois pares formem a segunda sequência bitônica em ordem decrescente, os próximos dois pares formem a terceira sequência bitônica em ordem crescente, etc., .... No final deste passo, temos 2**(n-1) sequências bitônicas de tamanho 2, e elas seguem uma ordem crescente, decrescente, crescente, .., decrescente. Assim, elas formam 2**(n-2) sequências bitônicas de tamanho 4.
- Passo 1: para cada nova sequência bitônica de tamanho 4 com 2**(n-2) elementos (cada nova sequência consiste em 2 sequências anteriores consecutivas), ela troca os elementos para que, no final do passo 1, tenhamos 2**(n-2) sequências bitônicas de tamanho 4, e elas seguem uma ordem: crescente, decrescente, crescente, ..., decrescente. Assim, elas formam 2**(n-3) sequências bitônicas de tamanho 8.
- A mesma lógica se aplica até chegarmos ao último passo.
- Passo n: neste último passo, temos uma sequência bitônica de tamanho 2**n. Os elementos na sequência são trocados até que tenhamos uma sequência em ordem crescente.

O código tentará primeiro executar em uma GPU disponível e recorrerá à CPU do sistema se uma GPU compatível não for detectada.

## Detalhes chave da implementação

A implementação básica do DPC++ explicada no código inclui o seletor de dispositivo, buffer, acessador, kernel e grupos de comando. Unified Shared Memory (USM) e Buffer Object são usados para gerenciamento de dados.

## Licença  
Este exemplo de código é licenciado sob a licença MIT.

## Compilando bitonic-sort para CPU e GPU

### Arquivos de inclusão
A pasta de inclusão está localizada em %ONEAPI_ROOT%\dev-utilities\latest\include em seu sistema de desenvolvimento.

### Executando amostras no DevCloud
Se você estiver executando uma amostra no Intel DevCloud, lembre-se de que é necessário especificar o nó de computação (CPU, GPU, FPGA), bem como se deseja executar em modo de lote ou interativo. Para obter mais informações, consulte o Guia de introdução do conjunto de ferramentas base Intel® oneAPI (https://devcloud.intel.com/oneapi/get-started/base-toolkit/)

### Em um sistema Linux*
1. Compile o programa usando os seguintes comandos.
    ``` 
    $ cd bitonic-sort
    $ dpcpp -O3 -fsycl -std=c++17 -o bitonic-sort ./bitonic-sort.cpp 
    ```

2. Execute o programa:
    ```
    ./bitonic-sort n k
    ```

## Executando a amostra

### Parâmetros da aplicação

    Uso: bitonic-sort <expoente> <semente>

onde

exponente é um número positivo. O comprimento da sequência é 2**exponente.

semente é a semente usada pelo gerador aleatório para gerar a aleatoriedade.

A amostra transfere o cálculo para a GPU e, em seguida, realiza o cálculo em série na CPU. Os resultados da computação paralela e serial são comparados. Se os resultados coincidirem e a ordem ascendente for verificada, o aplicativo exibirá uma mensagem "Success!".

### Exemplo de saída
```
$ ./bitonic-sort 21 47
Array size: 2097152, seed: 47
Device: Intel(R) Gen9 HD Graphics NEO
Warm up ...
Kernel time using USM: 0.248422 sec
Kernel time using buffer allocation: 0.253364 sec
CPU serial time: 0.628803 sec

Success!
```
