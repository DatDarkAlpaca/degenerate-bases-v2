# Degenerate Bases v2.0

This is the active development version of the degenerate bases algorithm.

This project was created to analyze oligonucleotide sequences containing degenerate bases and generate a file with all possible outcomes using non-degenerate bases, converting degenerate bases into conventional ones.

For more information about the algorithm, check out [this link.](https://brazilianjournals.com/index.php/BRJD/article/view/40982).

# Getting Started

These instructions will help you get a copy of the project up and running on your local machine for development and testing purposes.

## Prerequisites

You'll need to install the following to build this project:

* [Python 3](https://www.python.org/downloads/)
* [Conan 2.0](https://conan.io/downloads)
* [Vulkan](https://vulkan.lunarg.com/#new_tab)
* [Premake 5](https://github.com/premake/premake-core/releases)

## Installation

1. **Clone the repository**
    ```bash
    git clone --recurse-submodules https://github.com/DatDarkAlpaca/degenerate-bases-v2
    ```

2. **Generate the project**
    If you're building on a Windows machine, you can use the build.cmd file to execute the Python script. This automatically calls premake, so you must specify the project file of your choice.

    ```bash
    .\build <action: vs2022, vs2021, gmake, ...>
    ```

3. **Compile the project**
   Use the generated project files to build the project. After that, you should have a working copy under `degenerate-bases-v2/build/bin/{configuration}/degenerate-bases-v2`.


## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT) - see the
[LICENSE](LICENSE) file for details
