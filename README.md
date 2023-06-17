### This READ.md template was written based on this [repository](https://github.com/FernandoSchett/github_readme_template).

<h1 align="center">🖥️ DPCPP for dummies 🖥️</h1>

<div align="center">
	<a href="link_for_webite">
	<img height = "250em" src = "" />
    </a>
</div>

## Developed by 💻:

- [Fernando Schettini](https://github.com/FernandoSchett).
- [Orlando Mota](https://github.com/orlandomotapires).
- [Antonio Horácio](https://github.com/AntonioHoracio77).

## Special thanks to 🥰:

- [Murillo Boratto](https://github.com/muriloboratto), our mentor, your experience and knowledge have been invaluable to our progress.

## About 🤔:

This repository contains code samples in DPC++, an extension of the C++ standard created by Intel for heterogeneous parallel programming. The code samples were created with the aim of helping developers understand and use the DPC++ language in their projects.

### What is DPC++?
DPC++ is an extension of the C++ standard that enables heterogeneous parallel programming on systems with multiple types of processors, such as CPUs and GPUs. It was created by Intel in collaboration with other companies and is based on open-source technologies like LLVM and SYCL.

## Resourses 🧑‍🔬:

- 
- 


## Results 📈:

## Dependencies 🚚:

The project dependencies are described in a dependencies file within the repository. In summary, heres what you're gonna need in order to run the project:

- 
- 

For installing dependencies more quickly, you can run the following command at terminal, inside the clonned repository:

    pip3 install -r ./dependencies/requirements.txt

Make sure you have all Dependencies before running the project.

## How to run it 🏃:

To use the code samples, you need to have a compiler that supports DPC++, such as the Intel DPC++ Compiler or hipSYCL. You also need a system with support for heterogeneous processors, such as an Intel CPU and an AMD Radeon GPU.</br>
To compile and run the examples in this repository, inside the "codes" directory, execute the following commands, where "output-name" refers to the name the executable file will have after compilation, and "source-code" refers to the name of the code file you want to compile:

1. Load the oneAPI environment with the following command:

	source /opt/intel/oneapi/setvars.sh

2. To compile, use the following command:
	
	dpcpp -o output-name source-code

3. Running the code:
	
	./output-name

4. **[ Example ]** To compile the arrayReduction, we need to run the following commands:

	source /opt/intel/oneapi/setvars.sh
	dpcpp -o arrayReduction ./arrayReduction.cpp
	./arrayReduction


## Development Process ⚙️:

Developers used [Trello]() to get things organized, each one using their own branch to code, using names to identify the commit type then merginng the features into develop branch. After testing, the group update the main branch. This application was developed in xx/xx/20xx until xx/xx/20xx.

### Tools Used 🛠️: 

- [VScode](https://code.visualstudio.com/).  

## How to contribute 🫂:

Feel free to create a new branch, fork the project, create a new Issue or make a pull request contact one of us to develop at DPCPP for dummies.

## Licence 📜:

[Apache V2](https://choosealicense.com/licenses/apache-2.0/)