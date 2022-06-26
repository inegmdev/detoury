# Detoury

## Introduction

### About The Tool
Tracing tool used for malware analysis based on MS Detours as the hooking/detouring library, implemented as a course assignment for CIT661 @ NU Egypt.

### Final Deliverable
The final product is a DLL file that can be injected using any debugger or using `withdll.exe` file that is also provided here.

### Audience
Infosec students who are curious how to use MS Detours.

## How to use
### Install Prerequistes 

* MS Visual Studio, I used 2022 Community Edition.
* MSYS2
  - `pacman -S make`

### Before Building

* Edit `MS_VC_DIR` with the right path for your environment.

### Building

#### Microsoft Detours Static Library

* 32-Bit: `make ms-detours arch=32` 
* 64-Bit: `make ms-detours arch=64`

### Building Detoury

* Open the MS VS Solution.
* **Choose** the right **solution platfrom**, either: "x64, x86"
* Start building the solution, **Build >> Build Solution**

## License 

Check `../LICENSE`

