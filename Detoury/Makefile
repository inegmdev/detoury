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
ifeq ($(arch),32)
	detours_target=86
endif
## Generated Build Command File for Detours
GEN_DETOURS_BUILD_CMD_FILE=./Build/build_tmp.cmd
## Detours External Dir

EXTERNAL_DETOURS_DIR_BASH=$(shell realpath ./External/Detours)
EXTERNAL_DETOURS_DIR_WIN_STEP1=$(subst /c/,C:\,$(EXTERNAL_DETOURS_DIR_BASH))
EXTERNAL_DETOURS_DIR_WIN=$(subst /,\\,$(EXTERNAL_DETOURS_DIR_WIN_STEP1))

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
