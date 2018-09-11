#!/usr/bin/env python3

import Adafruit_BBIO.GPIO as GPIO
import time
import sys

try:
	LED = sys.argv[1]
	delay = float(sys.argv[2])
	ret = GPIO.setup(LED, GPIO.OUT)
	while True:
		GPIO.output(LED, 1)
		time.sleep(delay)
		GPIO.output(LED, 0)
		time.sleep(delay)
except KeyboardInterrupt:
	GPIO.cleanup()
