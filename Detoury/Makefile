SHELL=/bin/bash

#######################################################################
#                           Configurations                            #
#######################################################################
# Configuration
MS_VC_DIR=G:\Program Files\Microsoft Visual Studio\2022\Community

# Default values for optional parameters
arch?=64

#######################################################################
#                               Globals                               #
#######################################################################
## MS VC Dirs
MS_VC_TOOLS_DIR=$(MS_VC_DIR)\Common7\Tools
MS_VC_BUILD_CMD_DIR=$(MS_VC_DIR)\VC\Auxiliary\Build
## Detours Architecture Target
detours_target?=$(arch)
detoury_out_dir?=x$(arch)/
ifeq ($(arch),32)
	detours_target=86
	detoury_out_dir=
endif
## Generated Build Command File for Detours
GEN_DETOURS_BUILD_CMD_FILE=./Build/build_tmp.cmd
## Detours External Dir
EXTERNAL_DETOURS_DIR_BASH=$(shell realpath ./External/Detours)
EXTERNAL_DETOURS_DIR_WIN_STEP1=$(subst /c/,C:\,$(EXTERNAL_DETOURS_DIR_BASH))
EXTERNAL_DETOURS_DIR_WIN=$(subst /,\\,$(EXTERNAL_DETOURS_DIR_WIN_STEP1))
# HOOKS GENERATION TOOL
SCRIPTS_HOOK_GEN_TOOL_DIR=$(shell realpath ./Tools/Hooks_Generator)
SCRIPTS_HOOK_GEN_TOOL_VENV_INSTALLED_FLAG=$(SCRIPTS_HOOK_GEN_TOOL_DIR)/venv.installed
# HOOKS GENETATED FILE
HOOKS_GENERATED_FILE=$(shell realpath ./Detoury/Hooks.h)

#######################################################################
#                               Targets                               #
#######################################################################
.PHONY: all
all:
	$(MAKE) ms-detours arch=64
	$(MAKE) ms-detours arch=32

.PHONY:
_header:
	#
	# Configuration arguments for Makefile:
	#   MS_VC_DIR: $(MS_VC_DIR)
	#   arch: $(arch)
	#
	#

#vvvvvvvvvvvvvvvvvvvvv Start of Environment Init vvvvvvvvvvvvvvvvvvvvv
.PHONY: init
init:
	# Installing python environment for Hooks Generation Tool
	$(MAKE) hooks_install
#^^^^^^^^^^^^^^^^^^^^^  End of Environment Init  ^^^^^^^^^^^^^^^^^^^^^

#vvvvvvvvvvvvvvvvvvvvv Start of Sanity Checks Rules vvvvvvvvvvvvvvvvvvvvv
# Check the arch option value
.PHONY: _sanity_check__arch_value
_sanity_check__arch_value:
	@./Tools/Scripts/SanityChecks/sanity_check__arch_value.sh $(arch)

# Sanity checks executer
.PHONY: _sanity_checks
_sanity_checks: _sanity_check__arch_value
#^^^^^^^^^^^^^^^^^^^^^  End of Sanity Checks Rules  ^^^^^^^^^^^^^^^^^^^^^

#vvvvvvvvvvvvvvvvvvvvv Start of MS Detours Build vvvvvvvvvvvvvvvvvvvvv
.PHONY:ms-detours
ms-detours_prebuild: CMD_BAT=vcvars$(arch).bat
ms-detours_prebuild: MS_VC_BUILD_CMD=$(MS_VC_BUILD_CMD_DIR)\$(CMD_BAT)
ms-detours_prebuild: MS_VC_BUILD_CMD_ESCAPED=$(subst \,\\,$(MS_VC_BUILD_CMD))
ms-detours_prebuild: _header _sanity_checks
	# Prepare the build command temp file ( $(GEN_DETOURS_BUILD_CMD_FILE) )
	@rm -f $(GEN_DETOURS_BUILD_CMD_FILE)
	@echo "@ECHO OFF" > $(GEN_DETOURS_BUILD_CMD_FILE)
	@echo "CD \"$(EXTERNAL_DETOURS_DIR_WIN)\"" >> $(GEN_DETOURS_BUILD_CMD_FILE)
	@echo "ECHO %cd%" >> $(GEN_DETOURS_BUILD_CMD_FILE)
	@echo "SET DETOURS_TARGET_PROCESSOR=X$(detours_target)" >> $(GEN_DETOURS_BUILD_CMD_FILE)
	@echo "CALL \"$(MS_VC_BUILD_CMD_ESCAPED)\"" >> $(GEN_DETOURS_BUILD_CMD_FILE)
	@echo "env -u MAKE -u MAKEFLAGS NMAKE" >> $(GEN_DETOURS_BUILD_CMD_FILE)
	# [Done]
	#

.PHONY:ms-detours_build
ms-detours_build: GEN_BUILD_CMD_FULL_PATH_STEP1=$(shell realpath $(GEN_DETOURS_BUILD_CMD_FILE))
ms-detours_build: GEN_BUILD_CMD_FULL_PATH_STEP2=$(subst /c/,c:\,$(GEN_BUILD_CMD_FULL_PATH_STEP1))
ms-detours_build: GEN_BUILD_CMD_FULL_PATH=$(subst /,\,$(GEN_BUILD_CMD_FULL_PATH_STEP2))
ms-detours_build: GEN_BUILD_CMD_FULL_PATH_ESCAPED=$(subst \,\\,$(GEN_BUILD_CMD_FULL_PATH))
ms-detours_build: _header _sanity_checks
	#
	# Building Detours in path ( $(EXTERNAL_DETOURS_DIR_WIN) )
	# Running the batch file ...
	@cd ./External/Detours && cmd.exe /C "$(GEN_BUILD_CMD_FULL_PATH)"
	# [Done] Successfully built MS Detours
	#

.PHONY:ms-detours
ms-detours: ms-detours_prebuild ms-detours_build
#^^^^^^^^^^^^^^^^^^^^^  End of MS Detours Build  ^^^^^^^^^^^^^^^^^^^^^

#vvvvvvvvvvvvvvvvvvvvv Start of Hooks Generation vvvvvvvvvvvvvvvvvvvvv
.PHONY: hooks_install
hooks_install:
	# Checking if the installation step done before
	@if [[ -e $(SCRIPTS_HOOK_GEN_TOOL_VENV_INSTALLED_FLAG) ]]; then\
        echo "  [SKIP] Python venv for Hooks Generator tool already installed.";\
        exit 0;\
    fi
	# Installing the required packcages to be able to use Hooks Generation scripts
	#
	# 1. Python3
	pacman -S --noconfirm --needed python3
	# [Done] Python3
	#
	# 2. Pip3
	pacman -S --noconfirm --needed python3-pip
	# [Done] Pip3
	#
	# 3. Create the virtual environment
	cd $(SCRIPTS_HOOK_GEN_TOOL_DIR) && python3 -m venv venv
	# [Done] Creation of the virtual environment
	#
	# 4. Install Python requirements inside the virtual environment
	cd $(SCRIPTS_HOOK_GEN_TOOL_DIR) && ./venv_install.sh
	# [Done] Install Python requirements inside the virtual environment
	#
	touch $(SCRIPTS_HOOK_GEN_TOOL_VENV_INSTALLED_FLAG)
	
.PHONY: hooks_generate
hooks_generate:
	# Running the script from virtual env
	cd $(SCRIPTS_HOOK_GEN_TOOL_DIR) && ./run.sh > $(HOOKS_GENERATED_FILE)

.PHONY: hooks_clean
hooks_clean:
	# Removing the python3 venv in Hooks Generator Script
	rm -rf $(SCRIPTS_HOOK_GEN_TOOL_DIR)/venv
	# Removing the flag of installed environment
	rm -f $(SCRIPTS_HOOK_GEN_TOOL_DIR)/venv.installed

.PHONY: hooks
hooks: hooks_generate
#^^^^^^^^^^^^^^^^^^^^^  End of Hooks Generation  ^^^^^^^^^^^^^^^^^^^^^

#vvvvvvvvvvvvvvvvvvvvv Start of Test Commands vvvvvvvvvvvvvvvvvvvvv
.PHONY: test_with_app
test_with_app: CUR_DIR=$(shell realpath .)
test_with_app: DETOURY_OUT_DLL=$(CUR_DIR)/Detoury/x$(detours_target)/Debug/Detoury.dll
test_with_app: DETOURY_OUT_DLL_WIN_STEP1=$(subst /c/,C:\,$(DETOURY_OUT_DLL))
test_with_app: DETOURY_OUT_DLL_WIN=$(subst /,\,$(DETOURY_OUT_DLL_WIN_STEP1))
test_with_app: WITHDLL_EXE=$(CUR_DIR)/Tools/DLL_Injector/withdll_x$(detours_target).exe
test_with_app: WITHDLL_EXE_WIN_STEP1=$(subst /c/,C:\,$(WITHDLL_EXE))
test_with_app: WITHDLL_EXE_WIN=$(subst /,\,$(WITHDLL_EXE_WIN_STEP1))
test_with_app: TEST_CMD=$(CUR_DIR)/Build/test_tmp.cmd
test_with_app: TEST_CMD_WIN_STEP1=$(subst /c/,C:\,$(TEST_CMD))
test_with_app: TEST_CMD_WIN=$(subst /,\\,$(TEST_CMD_WIN_STEP1))
test_with_app:
	# Preparing the test cmd batch
	echo "@ECHO OFF" > $(TEST_CMD)
	echo "start cmd /c \" \"$(WITHDLL_EXE_WIN)\" /d:\"$(DETOURY_OUT_DLL_WIN)\" \"$(app)\"\"" >> $(TEST_CMD)
	cmd /c "$(TEST_CMD_WIN)"

.PHONY: test_notepad
test_notepad:
	$(MAKE) test_with_app app=C:\Windows\System32\notepad.exe
#^^^^^^^^^^^^^^^^^^^^^  End of Test Commands  ^^^^^^^^^^^^^^^^^^^^^

#vvvvvvvvvvvvvvvvvvvvv Start of Install Commands vvvvvvvvvvvvvvvvvvvvv
.PHONY: detoury_install
detoury_install: DETOURY_DLL_OUT=$(shell realpath ./Detoury/$(detoury_out_dir)Debug/Detoury.dll)
detoury_install:
	install -C $(DETOURY_DLL_OUT) ./Release/Detoury_x$(detours_target).dll

.PHONY: withdll_install
withdll_install: WITH_DLL=$(shell realpath ./Tools/DLL_Injector/withdll_x$(detours_target).exe)
withdll_install:
	install -C $(WITH_DLL) ./Release/withdll_x$(detours_target).exe

.PHONY: install
install: detoury_install withdll_install 

.PHONY: delivery
delivery:
	$(MAKE) install arch=64
	$(MAKE) install arch=32

#^^^^^^^^^^^^^^^^^^^^^  End of Install Commands  ^^^^^^^^^^^^^^^^^^^^^