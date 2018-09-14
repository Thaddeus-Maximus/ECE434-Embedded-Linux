#!/bin/bash

temp1=`i2cget -y 2 0x48`
temp2=`i2cget -y 2 0x4a`

temp1_sc=$(($temp1 /2 *9/5 + 32))
temp2_sc=$(($temp2 /2 *9/5 + 32))

echo "Temp 1 = " "$temp1_sc" "deg C"
echo "Temp 2 = " "$temp2_sc" "deg C"
