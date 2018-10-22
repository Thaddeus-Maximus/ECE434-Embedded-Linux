#!/bin/bash
config-pin P9_27 out

export PRUN=0
export TARGET=hello
echo PRUN=$PRUN
echo TARGET=$TARGET

echo none > /sys/class/leds/beaglebone\:green\:usr3/trigger
