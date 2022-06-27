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
  - `make init` to run automatic installer for all needed packages (pacman/python virtualenv)

*Note: MSYS2 must be used to envoke all the make commands here, it's the only supported terminal till now*

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

### Configuring the Hooks

#### Add new API Hook is easy

* Go to `Tools/Hooks_Generator/Hooks` dir.
* Create a new file with the API name for example `CreateFileA`.
* Copy the "docs.microsoft.com" MSDN Syntax documentation of the API.
* Run `make hooks` this will autogenerate the file `Hooks.h` and then you can re-build and start using it.

## References Used During Development

* [Custom Formatting - Spdlog v1.x - DocsForge](https://spdlog.docsforge.com/v1.x/3.custom-formatting/#pattern-flags)

## License 

Check `../LICENSE`

