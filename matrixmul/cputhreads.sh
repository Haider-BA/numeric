#!/bin/sh
# Returns the number of threads the system CPU(s) have
threads=`cat /proc/cpuinfo | grep processor | awk '{print $3}' | tail -1` && echo "$threads+1" | bc
