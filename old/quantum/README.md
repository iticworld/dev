# QUANTUM

## WELCOME TO THE MICROSOFT QUANTUM DEVELOPMENT KIT PREVIEW

Thank you for your interest in Microsoft Quantum Development Kit preview.
The development kit contains the tools you'll need to build your own quantum computing programs and experiments.

To jump right in, go to [Getting Started with the Quantum Development Kit](https://docs.microsoft.com/en-us/quantum/install-guide/index?view=qsharp-preview). This shows you how to explore Q# through Jupyter Notebooks, an open source web application, without installing the Quantum Development Kit. You'll then be guided through installing the Quantum Development Kit on Windows, Linux, or macOS machines so that you can write your own quantum programs. With the Quantum Development Kit, you can choose which classical host (Python, C# or other .NET programming language) to use to invoke your Q# program. The development kit also offers extentions to Visual Studio and Visual Studio Code for a great developer experience. Choose the development environment that's right for you!

Next, follow [Quickstart - your first quantum program](https://docs.microsoft.com/en-us/quantum/quickstart?view=qsharp-preview&tabs=tabid-vscode) to write your first quantum program using your command line, Visual Studio or Visual Studio Code. Learn about the structure of a Q# project and develop the quantum equivalent of "Hello, World!" - creating entanglement, or what is also known as a Bell State, in Q#.

To go further, the Quantum Development Kit provides many ways to learn how to develop a quantum program with Q#.

- Visit our [samples repository](https://github.com/Microsoft/Quantum) that showcases multiple examples on how to write quantum program using Q#. Most of these samples are written using our open-source [quantum libraries](https://github.com/Microsoft/QuantumLibraries), including our [standard](https://docs.microsoft.com/en-us/quantum/libraries/standard/index?view=qsharp-preview) and [chemistry](https://docs.microsoft.com/en-us/quantum/libraries/chemistry/index?view=qsharp-preview) libraries.

- If you want to dive deeper into Q# programming, check out the [Quantum Katas](https://github.com/Microsoft/QuantumKatas) - a collection of self-paced programming exercises that introduce you to quantum computing via programming exercises in Q#. Many of these katas are also available as Q# Notebooks.

- [Quantum computing concepts](https://docs.microsoft.com/en-us/quantum/concepts/index?view=qsharp-preview) includes more in depth topics such as the relevance of linear algebra to quantum computing, the nature and use of a qubit, how to read a quantum circuit, and more. See also the full list of documentation at the end of this article.

### BE A PART OF THE Q# OPEN SOURCE COMMUNITY

The Quantum Development Kit is an open source development kit that empowers developers to make quantum computing more accessible to all so that we can solve some of the world's most pressing challenges. Academic institutions who require open source software will be able to deploy Q# for their quantum learning and development. Open sourcing the development kit also empowers developers and domain experts an opportunity to contribute improvements and ideas via their coee.

Your feedback, participation and contributions to the Quantum Development Kit is important. To learn more about the Quantum Development Kit sources, provide feedback, and find out how you can participate in the decisions and contribute to this growing quantum development platform, see [Contributing to the Quantum Development Kit](https://docs.microsoft.com/en-us/quantum/contributing/index?view=qsharp-preview).

If you'd like more general information about Microsoft's quantum computing initiative, see [Microsoft Quantum](https://www.microsoft.com/en-us/quantum/).

### MICROSOFT QUANTUM DEVELOPMENT KIT COMPONENTS

The Quantum Development Kit preview provides a complete quantum program development and simulation environment that contains the following components. To find the open source Github source code repository for these components, see [Contributing to the Quantum Development Kit](https://www.microsoft.com/en-us/quantum/).

| COMPONENT                        | FUNCTION |
| -------------------------------- | -------- |
| Q# LANGUAGE AND COMPILER         | -        |
| Q# LIBRARY                       | -        |
| LOCAL QUANTUM MACHINE SIMULATOR  | -        |
| QUANTUM COMPUTER TRACE SIMULATOR | -        |
| RESOURCE ESTIMATOR               | -        |
| VISUAL STUDIO EXTENTION          | -        |
| VISUAL STUDIO CODE EXTENTION     | -        |
| QSHARP FOR PYTHON                | -        |
| IQ#                              | -        |

__Q# LANGUAGE AND COMPILER__: Q# is a domain specific programming language used for expressing quantum algorithms. It is used for writing sub-programs that execute on an adjunct quantum processor under the control of a classical host program and computer.

__Q# LIBRARY__: The library contains operations and functions that support both the classical language control requirement and the Q# quantum algorithms.

__LOCAL QUANTUM MACHINE SIMULATOR__: A full state vector simulator optimized for accurate vector simulation and speed.

__QUANTUM COMPUTER TRACE SIMULATOR__: The trace simulator does not simulate the quantum environment like the local quantum simulator. It is used to estimate the resources required to execute a quantum program and also faster debugging of the non-Q# control code.

__RESOURCE ESTIMATOR__: The resource estimator estimates the resources required to run a given instance of a Q# operation on a quantum computer.

__VISUAL STUDIO EXTENTION__: This extension contains templates for Q# files and projects as well as syntax highlighting and intelliSense support.

__VISUAL STUDIO CODE EXTENTION__: This extension contains syntax highlighting as well as code snippets for Q# and IntelliSense support.

__QSHARP FOR PYTHON__: The qsharp package for Python makes it easy to simulate Q# operations and functions from within Python.

__IQ#__: IQ# (pronounced i-q-sharp) is an extension primarily used by Jupyter and Python to the .NET Core SDK that provides the core functionality for compiling and simulating Q# operations.

### QUANTUM DEVELOPMENT KIT DOCUMENTATION

The current documentation includes the following topics.

- [Microsoft Quantum Development Kit release notes](https://docs.microsoft.com/en-us/quantum/relnotes/index?view=qsharp-preview)
- [Quantum computing concepts](https://docs.microsoft.com/en-us/quantum/concepts/index?view=qsharp-preview) includes topics such as the relevance of linear algebra to quantum computing, the nature and use of a qubit, how to read a quantum circuit, and more.
- [Getting Started with the Quantum Development Kit](https://docs.microsoft.com/en-us/quantum/install-guide/index?view=qsharp-preview) describes how to quickly set up your quantum development environment from any platform (Windows 10, Linux, and Mac) using Visual Studio, Visual Studio Code or the command line.
- [Quickstart - your first quantum program](https://docs.microsoft.com/en-us/quantum/quickstart?view=qsharp-preview&tabs=tabid-vscode) walks you through how to write an application that creates a quantum entanglment state in the Visual Studio development environment. You'll learn how to define a Q# operation, call the Q# operation using C#, and how to execute your quantum algorithm.
- [Managing quantum machines and drivers](https://docs.microsoft.com/en-us/quantum/machines/index?view=qsharp-preview) describes how quantum algorithms are executed, what quantum machines are available, and how to write a non-Q# driver for the quantum program.
- [Quantum development techniques](https://docs.microsoft.com/en-us/quantum/techniques/index?view=qsharp-preview) specifies the core concepts used to create quantum programs in Q#. Topics include file structures, operations and functions, working with qubits, and some advanced topics.
- [Q# standard libraries](https://docs.microsoft.com/en-us/quantum/libraries/standard/index?view=qsharp-preview) describes the operations and functions that support both the classical language control requirement and the Q# quantum algorithms. Topics include control flow, data structures, error correction, testing, and debugging.
- [Q# language reference](https://docs.microsoft.com/en-us/quantum/language/index?view=qsharp-preview) details the Q# language including the type model, expressions, statements, and compiler use.
- [For more Information](https://docs.microsoft.com/en-us/quantum/for-more-info?view=qsharp-preview) contains specially selected references to deep coverage of quantum computing topics.
- [Quantum trace simulator reference](https://docs.microsoft.com/en-us/dotnet/api/microsoft.quantum.simulation.simulators.qctracesimulators) contains reference material about trace simulator entities and exceptions.
- [Q# library reference](https://docs.microsoft.com/en-us/qsharp/api/index?view=qsharp-preview) contains reference information about library entities by namespace.

## GETTING STARTED

### GETTING STARTED WITH THE MICROSOFT QUANTUM DEVELOPMENT KIT

#### CHOOSE THE ENVIRONMENT THAT'S RIGHT FOR YOU

__JUPYTER NOTEBOOKS__

A great way to get started with Q# before installing the Quantum Development Kit is via some of the Jupyter notebooks available in our [Github Quantum repository](https://github.com/Microsoft/Quantum). In particular:

- [Q# Notebooks](https://github.com/microsoft/Quantum/blob/master/Samples/src/IntroToIQSharp/Notebook.ipynb) [(Run inline)](https://gke.mybinder.org/v2/gh/Microsoft/Quantum/master?filepath=Samples%2Fsrc%2FIntroToIQSharp%2FNotebook.ipynb): explains how to compile and simulate Q# operations inside a Jupyter notebook.
- [Teleport](https://github.com/microsoft/Quantum/blob/master/Samples/src/Teleportation/Notebook.ipynb) [(Run online)](https://mybinder.org/v2/gh/microsoft/Quantum/master?filepath=Samples%2Fsrc%2FTeleportation%2FNotebook.ipynb): shows how to implement the teleport algorithm using Q#.

To run these locally, take a look at our [Jupyter notebooks getting started guide](https://docs.microsoft.com/en-us/quantum/install-guide/jupyter?view=qsharp-preview).

__VISUAL STUDIO__

If you are already a [Visual Studio](https://visualstudio.microsoft.com/vs/) user, you can install the extension to get started developing Q# in Visual Studio.

[VISUAL STUDIO EXTENSION](https://marketplace.visualstudio.com/items?itemName=quantum.DevKit)

Then, check our [quickstart guide](https://docs.microsoft.com/en-us/quantum/quickstart?view=qsharp-preview&tabs=tabid-vscode) for step by step instructions for your first quantum program.

__VISUAL STUDIO CODE__

If you are already a Visual Studio Code user, start by installing the latest version of the [.NET Core SDK](https://dotnet.microsoft.com/) (2.2 or later) by following the instructions from the [.NET downloads page](https://dotnet.microsoft.com/download). Then, you can install the extension to get started developing Q# in Visual Studio Code.

[VISUAL STUDIO CODE EXTENSION](https://marketplace.visualstudio.com/items?itemName=quantum.quantum-devkit-vscode)

Then, check out [quickstart guide](https://docs.microsoft.com/en-us/quantum/quickstart?view=qsharp-preview&tabs=tabid-vscode) for step-by-step instructions for your first quantum program.

__PYTHON__

If you are a Python user, check out our [getting started with Python and the Quantum Development Kit guide](https://docs.microsoft.com/en-us/quantum/install-guide/python?view=qsharp-preview).

#### LEARN QUANTUM COMPUTING WITH Q#

- [Quantum Katas](https://github.com/Microsoft/QuantumKatas)
- [Samples](https://github.com/Microsoft/Quantum)
- [Quantum Computing Concepts](https://docs.microsoft.com/en-us/quantum/concepts/index?view=qsharp-preview)
- [Microsoft Quantum Blog](https://cloudblogs.microsoft.com/quantum/?ext)
- [Q# Blog](https://devblogs.microsoft.com/qsharp/)


## GETTING STARTED WITH C# AND THE QUANTUM DEVELOPMENT KIT

C# is supported natively in the Quantum Development Kit making it easy to call Q# operations from C#.

### PREREQUISITES

To write C# programs, download and install the .NET Core SDK 2.1 or later from the [.NET downloads page](https://dotnet.microsoft.com/download).

### INSTALLATION

To download the latest templates for creating new C# projects and libraries that invoke Q# operations, execute this from a command line:

```
dotnet new -i Microsoft.Quantum.ProjectTemplates
```

To verify everything is correctly installed, create and run a new program using the following from command line:

```
dotnet new console -lang Q# -o myApp
cd myApp
dotnet run
```

If everything works ok, you will see a "Hello quantum world!" message, for example:

```
dotnet new console -lang Q# -o myApp
cd myApp
dotnet run
```

### UPDATE

Follow these instructions to migrate your .csproj files to the newest version:

1. Consult [Nuget.org](https://www.nuget.org/packages/Microsoft.Quantum.Development.Kit/) for the PackageReferene number, "0.n.xxxx.yyyy" for the Microsoft Quantum Development Kit package.
2. Projects need to be upgraded in order. If you have a solution with multiple projects, update each project in the order they are referenced.
3. From a command line, run dotnet clean to remove all existing binaries and intermediate files.
4. In a text editor, edit the .csproj file to change the version fo all the "Microsoft.Quantum" packageReference to the package reference number, for example:

```
<PackageReference Include="Microsoft.Quantum.Standard" Version="0.n.xxxx.yyy" />
<PackageReference Include="Microsoft.Quantum.Development.Kit" Version="0.n.xxxx.yyy" />
```

5. From the command line, run this command: dotnet build

### USAGE

Take a look at the [quickstart guide](https://docs.microsoft.com/en-us/quantum/quickstart?view=qsharp-preview&tabs=tabid-vscode) for information on how to write Q# operations and how to invoke them from C#
