#!/bin/bash

if [ $1 = "1" ]; then
	config-pin P9_27 out

	export PRUN=0
	export TARGET=hello

	echo none > /sys/class/leds/beaglebone\:green\:usr3/trigger
else
	export PRUN=0	

	# Configure the PRU pins based on which Beagle is running
	machine=$(awk '{print $NF}' /proc/device-tree/model)
	echo -n $machine
	if [ $machine = "Black" ]; then
	    echo " Found"
	    pins="P9_31 P9_29 P9_30 P9_28"
	elif [ $machine = "Blue" ]; then
	    echo " Found"
	    pins=""
	elif [ $machine = "PocketBeagle" ]; then
	    echo " Found"
	    pins="P1_36 P1_33 P2_32 P2_30"
	else
	    echo " Not Found"
	    pins=""
	fi

	for pin in $pins
	do
	    echo $pin
	    config-pin $pin pruout
	    config-pin -q $pin
	done

	if [ $1 = "2" ]; then
		export TARGET=pwm1
	elif [ $1 = "3" ]; then
		export PRUN=1
		export TARGET=pwm4
	elif [ $1 = "4" ]; then
		export TARGET=pwm5
	elif [ $1 = "5" ]; then
		export TARGET=input1
		# Configure the PRU pins based on which Beagle is running
		machine=$(awk '{print $NF}' /proc/device-tree/model)
		echo -n $machine
		if [ $machine = "Black" ]; then
		    echo " Found"
		    config-pin P9_29 pruout
		    config-pin -q P9_29
		    config-pin P9_25 pruin
		    config-pin -q P9_25
		elif [ $machine = "Blue" ]; then
		    echo " Found"
		    pins=""
		elif [ $machine = "PocketBeagle" ]; then
		    echo " Found"
		    config-pin P1_36 pruout
		    config-pin -q P1_36
		    config-pin P1_29 pruin
		    config-pin -q P1_29
		else
		    echo " Not Found"
		    pins=""
		fi
	elif [ $1 = "6" ]; then
		export TARGET=sine1
	else
		echo " Not Found"
	fi
fi
echo PRUN=$PRUN
echo TARGET=$TARGET