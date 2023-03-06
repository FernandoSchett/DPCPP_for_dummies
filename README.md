# DPCPP-for-Dummies

Este repositório contém amostras de código em DPC++, uma extensão do padrão C++ criada pela Intel para programação paralela heterogênea. As amostras de código foram criadas com o objetivo de ajudar desenvolvedores a entenderem e utilizarem a linguagem DPC++ em seus projetos.

## O que é DPC++?
DPC++ é uma extensão do padrão C++ que permite a programação paralela heterogênea em sistemas com múltiplos tipos de processadores, como CPUs e GPUs. Ele foi criado pela Intel em conjunto com outras empresas e é baseado em tecnologias de código aberto, como o LLVM e o SYCL.

## Como executar códigos em DPC++

Para utilizar as amostras de código, é necessário ter um compilador que suporte DPC++, como o Intel DPC++ Compiler ou o hipSYCL. Também é necessário ter um sistema com suporte a processadores heterogêneos, como uma CPU Intel e uma GPU AMD Radeon.</br>
Para compilar executar os exemplos presentes neste repositório, dentro do diretório <i>codes</i>, execute os comandos a seguir, tendo em vista que "nome-da-saida" se refere ao nome que o arquivo executável terá após a compilação e  "codigo-fonte" referese ao nome do arquivo código que você deseja compilar: 

1. Carregue o ambiente oneAPI com o seguinte comando:

    ```
    source /opt/intel/oneapi/setvars.sh
    ```

2. Para compilar, use  seguinte comando:

    ```
    dpcpp -o nome-da-saida codigo-fonte 
    ```

3. Executando:

    ```
    ./nome-da-saida
    ```

4. Exemplo: Para compilar o arrayReduction precisamos rodar os seguintes comandos:
    
    ```
    source /opt/intel/oneapi/setvars.sh
    dpcpp -o arrayReduction ./arrayReduction.cpp
    ./arrayReduction 
    ```
