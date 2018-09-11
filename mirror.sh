#!/bin/bash
# Adapted from rom http://wh1t3s.com/2009/05/14/reading-beagleboard-gpio/
# Orginally /usr/bin/readgpio, Modified by Thad J. Hughes 2-Sep-2011
#
# Mirror the input from one GPIO pin with another

if [ $# -lt 2 ]; then
    echo "Usage: $0 <output gpio pin#> <input gpio pin#>"
    exit 0
fi
GPIO=$1
SWITCH=$2

cleanup() { # Set the GPIO port to 0
  echo 0 > /sys/class/gpio/gpio${GPIO}/value
  echo "Cleaning up"
  echo ""

  echo $SWITCH > /sys/class/gpio/unexport
  echo ""
  echo ""
  exit
}

# Open the GPIO port
#
if [ ! -e /sys/class/gpio/gpio$GPIO ]; then
    echo "$GPIO" > /sys/class/gpio/export
fi
echo "out" > /sys/class/gpio/gpio${GPIO}/direction

if [ ! -e /sys/class/gpio/gpio$SWITCH ]; then
    echo "$SWITCH" > /sys/class/gpio/export
fi
echo "in" > /sys/class/gpio/gpio${SWITCH}/direction

trap cleanup SIGINT # call cleanup on Ctrl-C

THIS_VALUE=0
NEWLINE=0

# Read forever

while [ "1" = "1" ]; do
  THIS_VALUE=`cat /sys/class/gpio/gpio${SWITCH}/value`
  # "^" for high, '_' for low
  if [ "$THIS_VALUE" != 0 ]; then
    EV="${EV}^"
    THIS_VALUE=0
   else
    EV="${EV}_"
    THIS_VALUE=1
  fi
  echo $THIS_VALUE > /sys/class/gpio/gpio${GPIO}/value
  #echo -n $EV

  # sleep for a while
  sleep 0.02

  # wrap line every 72 samples
  NEWLINE=`expr $NEWLINE + 1`
  if [ "$NEWLINE" = "72" ]; then
#    echo ""
    NEWLINE=0
  fi

done

cleanup # call the cleanup routine
