# HW03

## Temp Sensor
`tmp.sh` Reads from the i2c bus 2 (for TMP101 sensors at addresses 0x48 and 0x4a), converts the recieved value to degrees farenheit, and prints it.

## Etch A Sketch
`etchasketch.py` is an etch-a-sketch program that uses an LED matrix and rotary encoders.
The rotary encoders are on QEPs 1&2. The LED matrix is on i2c bus 2 at address 0x70.
The 'cursor' for the etch-a-sketch will be displayed in red, and the trail will be yellow.
When the cursor hits the edge of the screen, it wraps around.

========================
Professor Yoder's Comments

Looks good.

Score:10/10