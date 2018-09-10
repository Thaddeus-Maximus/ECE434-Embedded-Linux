#!/usr/bin/env python3

import Adafruit_BBIO.GPIO as GPIO
import time
import sys



BUTTONs = ["P9_15","P9_16","P9_17","P9_18"]
for BUTTON in BUTTONs:
	GPIO.setup(BUTTON, GPIO.IN)

LEDs    = ["P9_11","P9_12","P9_13","P9_14"]
for LED in LEDs:
	GPIO.setup(LED, GPIO.OUT)


map = {BUTTONs[0]: LEDs[0], BUTTONs[1]: LEDs[1], BUTTONs[2]: LEDs[2], BUTTONs[3]: LEDs[3]}

def updateLED(channel):
	state = GPIO.input(channel)
	GPIO.output(map[channel], state)

for BUTTON in BUTTONs:
	GPIO.add_event_detect(BUTTON, GPIO.BOTH, callback=updateLED)

try:
	while True:
		time.sleep(100)
except KeyboardInterrupt:
	GPIO.cleanup()
GPIO.cleanup()
