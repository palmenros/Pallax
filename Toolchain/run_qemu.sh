#!/bin/bash

qemu-system-i386 -no-reboot -no-shutdown -d cpu_reset,int,guest_errors $2 -kernel "$1"