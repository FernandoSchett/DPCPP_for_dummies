### This READ.md template was written based on this [repository](https://github.com/FernandoSchett/github_readme_template).

<h1 align="center">🖥️ DPCPP for dummies 🖥️</h1>

<div align="center">
	<a href="link_for_webite">
	<img height = "250em" src = "https://github.com/FernandoSchett/DPCPP_for_dummies/assets/80331486/90a234f1-0fb4-4389-a713-af7a940cbf23" />
    </a>
</div>

## Developed by 💻:

- [Fernando Schettini](https://github.com/FernandoSchett).
- [Orlando Mota](https://github.com/orlandomotapires).
- [Antonio Horácio](https://github.com/AntonioHoracio77).

## Special thanks to 🥰:

- [Murillo Boratto](https://github.com/muriloboratto), our mentor, your experience and knowledge have been invaluable to our progress.

## About 🤔:

This repository contains code samples in DPC++, an extension of the C++ standard created by Intel® for heterogeneous parallel programming. The code samples were created with the aim of helping developers understand and use the DPC++ language in their projects.

### What is DPC++?
DPC++ is an extension of the C++ standard that enables heterogeneous parallel programming on systems with multiple types of processors, such as CPUs and GPUs. It was created by Intel® in collaboration with other companies and is based on open-source technologies like LLVM and SYCL.

## Resourses 🧑‍🔬:

- Collection of basic parallel DPC++ code examples.
- Instructions and information targeted at beginners in parallel programming.
- Concepts explanations like array reduction, matrix multiplication, and vector addition using DPC++.

## Results 📈:

## Dependencies 🚚:

To use the code samples, you need to have a compiler that supports DPC++, such as the Intel® DPC++ Compiler or hipSYCL. You also need a system with support for heterogeneous processors, such as an Intel® CPU and an AMD Radeon GPU. The project dependencies are described in a dependencies file within the repository. Dont forget to download DPCPP and Sycl libraries within the [Intel® oneAPI DPC++/C++ Compiler](https://www.intel.com/content/www/us/en/developer/articles/tool/intel-system-studio-download-and-install-intel-c-compiler.html) to run the codes inside this repository.

## How to run it 🏃:

To compile and run the examples in this repository, inside the _codes_ directory, execute the following commands, where ```output-name``` refers to the name the executable file will have after compilation, and ```source-code``` refers to the name of the code file you want to compile:

1. Load the oneAPI environment with the following command:

		source /opt/Intel®/oneapi/setvars.sh

2. To compile, use the following command:
	
		dpcpp -o output-name source-code

3. Running the code:
	
		./output-name

4. **[ Example ]** To compile the arrayReduction, we need to run the following commands:

		source /opt/Intel®/oneapi/setvars.sh
		dpcpp -o arrayReduction ./arrayReduction.cpp
		./arrayReduction

## Development Process ⚙️:

Developers worked for two weeks using the Kanban methodology to develop this project. Each week, they synchronized and delivered their tasks.

### Tools Used 🛠️: 

- [VScode](https://code.visualstudio.com/). 
- [GCC](https://gcc.gnu.org/). 
- [Intel® oneAPI DPC++/C++ Compiler](https://www.intel.com/content/www/us/en/developer/articles/tool/intel-system-studio-download-and-install-intel-c-compiler.html)

## How to contribute 🫂:

Feel free to create a new branch, fork the project, create a new Issue or make a pull request contact one of us to develop at DPCPP for dummies.

## Licence 📜:

[Apache V2](https://choosealicense.com/licenses/apache-2.0/)

## References 📙:
	
[1] INTEL. Guia do Desenvolvedor e Referência do Compilador Intel® oneAPI DPC++/C++. [S.l.], 2023. Available at: https://www.intel.com/content/www/us/en/docs/dpcpp-cpp-compiler/developer-guide-reference/2023-0/overview.html. Accessed on: June 16, 2023.