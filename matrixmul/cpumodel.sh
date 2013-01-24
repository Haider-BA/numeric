#!/bin/sh

# Find the model name of the system CPU
cat /proc/cpuinfo | grep "model name" | tail -1 | cut -f 1 -d ':' --complement
