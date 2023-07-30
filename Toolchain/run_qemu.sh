#!/bin/bash

# Useful options for -d: cpu_reset,int,guest_errors
qemu-system-i386 -no-reboot -no-shutdown -d cpu_reset,guest_errors $2 -kernel "$1" -serial stdio