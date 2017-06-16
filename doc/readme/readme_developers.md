This is the documentation for developers: source code structure, build instructions, tools required, etc.

# Source-code structure
```
.
<<<<<<< HEAD
+-- bin
|   +-- ocladock_<type>_<N>wi
+-- common
|   +-- calcenergy_basic.h
|   +-- defines.h
+-- device
|   +-- auxiliary_genetic.cl
|   +-- calcenergy.cl
|   +-- kernel1.cl
|   +-- kernel2.cl
|   +-- kernel3.cl
|   +-- kernel4.cl
+-- doc
+-- host
|   +-- inc
    |   +-- calcenergy.h
    |   +-- getparameters.h
    |   +-- miscellaneous.h
    |   +-- performdocking.h
    |   +-- processgrid.h
    |   +-- processligand.h
    |   +-- processresult.h
|   +-- src
    |   +-- calcenergy.cpp
    |   +-- getparameters.cpp
    |   +-- main.cpp
    |   +-- miscellaneous.cpp
    |   +-- performdocking.cpp
    |   +-- processgrid.cpp
    |   +-- processligand.cpp
    |   +-- processresult.cpp
+-- input
|   +-- 1stp
|   +-- 3ce3
+-- wrapcl
|   +-- inc
    |   +-- BufferObjects.h
    |   +-- CommandQueues.h
    |   +-- commonMacros.h
    |   +-- Contexts.h
    |   +-- Devices.h
    |   +-- ImportBinary.h
    |   +-- ImportSource.h
    |   +-- Kernels.h
    |   +-- listAttributes.h
    |   +-- Platforms.h
    |   +-- Programs.h
|   +-- src
|   +-- BufferObjects.cpp
|   +-- CommandQueues.cpp
|   +-- Contexts.cpp
|   +-- Devices.cpp
|   +-- ImportBinary.cpp
|   +-- ImportSource.cpp
|   +-- Kernels.cpp
|   +-- listAttributes.cpp
|   +-- Platforms.cpp
|   +-- Programs.cpp
+-- prebuilt
=======
+-- hola
+-- amigos
|   +-- son todos
|   +-- muy
|   +-- buenos
|-- amigos
```
>>>>>>> 765aa7531c94fd16a284e0c605c8f3107acec118

# Compilation

## Basic
```zsh
make DEVICE=<TYPE> NUMWI=<NWI>
```
`<TYPE>` : CPU, GPU.

`<NUMWI>` : 16, 32, 64

After successful compilation, the host binary `ocladock_<type>_<N>wi` is placed under [bin](./bin).

`type` denotes the accelerator chosen: `cpu` or `gpu`.

`N` denotes the OpenCL work-group size: `16`, `32`, or `64`.

## All available options
```zsh
make DEVICE=<TYPE> NUMWI=<NWI> CONFIG=<CFG> DOCK_DEBUG=<Y/N> REPRO=<Y/N>
```
| Argument    | Description                           | Possible values          |
|-------------|---------------------------------------|--------------------------|
| DEVICE      | OpenCL device type                    | `<TYPE>`: CPU, GPU       |
| NUMWI       | Number of work items per work group   | `<NWI>` : 16, 32, 64     |
| CONFIG      | Host configuration                    | `<CFG>` : DEBUG, RELEASE |
| DOCK_DEBUG  | Enable debug info from host & device  | `<Y/N>` : YES, NO        |
| REPRO       | Reproduce results (remove randomness) | `<Y/N>` : YES, NO        |

## Configuration file
Check the configurations in the project's [Makefile](../Makefile).

# Requirements