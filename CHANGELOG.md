# Change Log 

## (v1.0.0)

### APIs Hooked so far

#### Time-related APIs
* Sleep

#### Process APIs
* CreateProcessA
* OpenProcss
* ExitProcess
* ShellExecuteA
* GetCommandLineA
* GetStartupInfoW

#### File APIs
* CreateFileA
* CopyFileA
* DeleteFileA
* FindFirstFileA
* FindNextFileA

#### Registery APIs
* RegOpenKeyA
* RegCloseKey
* RegDeleteKeyA
* RegDeleteValueA
* RegSaveKeyA
* RegSetValueA

#### Mutex APIs
* CreateMutexA
* OpenMutexA
* ReleaseMutex

### How to Use

* Use `Detoury_x<arch>.cmd <executable_full_path>` to inject the DLL inside the executable and then start logging.
* You will find a MessageBox that comes up notifying you that the logs will be saved under `C:\logs\<time_stamp>__Detoury_log.txt`
* The log file syntax is logged in JSON style rows, to be used later by a tool to filter and work with it.
* Note: You can use a tool like [jq JSON command line processor](https://stedolan.github.io/jq/) or you can use the Power Queries in Excel after importing the JSON file in it.