#!/usr/bin/bash

# Move to the directory of this file, instead of CWD
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path"

# Create log folder
mkdir -p ../cmake-build-debug/qemu/

/bin/bash ./run_qemu.sh "$1" "-s -S" &> ../cmake-build-debug/qemu/log &