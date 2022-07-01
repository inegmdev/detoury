#!/bin/bash

set -e
arch=$1

list_of_supported_archs="64 32"

# Check if it is not empty
if [[ -z ${arch} ]]; then
    echo "[ERROR] arch option is empty."
    exit 1
fi

for x in ${list_of_supported_archs}; do
    if [[ "${x}" == "${arch}" ]]; then
        # Found the arch in the list of supported archs
        exit 0
    fi
done

# If still not found
echo "[ERROR] arch option value is not on supported architectures list."
exit 1