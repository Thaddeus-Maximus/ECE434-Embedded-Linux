#!/usr/bin/env python3
# Write an 8x8 Red/Green LED matrix
# Thad Hughes
# Adapted from https://www.adafruit.com/product/902
from Adafruit_BBIO.Encoder import RotaryEncoder, eQEP1, eQEP2
import smbus
import time
bus = smbus.SMBus(2)  # Use i2c bus 1
matrix = 0x70         # Use address 0x70

bus.write_byte_data(matrix, 0x21, 0)   # Start oscillator (p10)
bus.write_byte_data(matrix, 0x81, 0)   # Disp on, blink off (p11)
bus.write_byte_data(matrix, 0xe7, 0)   # Full brightness (page 15)

# The first byte is GREEN, the second is RED.
smile = [0x00, 0x3c, 0x00, 0x42, 0x28, 0x89, 0x04, 0x85,
    0x04, 0x85, 0x28, 0x89, 0x00, 0x42, 0x00, 0x3c
]

grid = [0x00 for i in range(16)]

def reset():
  grid = [0x00 for i in range(16)]
  bus.write_i2c_block_data(matrix,0,grid)

def flip_to(x,y, color='r'):
  "Flips the LED at x,y to the desigated color (r, g, y, or something else for off)"
  off = 1
  if color == 'g':
    # Take the relevant column
    # AND-Mask it with a column of 1s except for the point in question (turn the point OFF fully)
    # OR-Mask that with a column of 0s except for the point in question (turn the point ON for the color requested)
    grid[x*2+0] = grid[x*2+0] & (~(0x01 << y)) | (0x01 << y)
    grid[x*2+1] = grid[x*2+1] & (~(0x01 << y))
  elif color == 'r':
    grid[x*2+1] = grid[x*2+1] & (~(0x01 << y)) | (0x01 << y)
    grid[x*2+0] = grid[x*2+0] & (~(0x01 << y))
  elif color == 'y':
    grid[x*2+0] = grid[x*2+0] & (~(0x01 << y)) | (0x01 << y)
    grid[x*2+1] = grid[x*2+1] & (~(0x01 << y)) | (0x01 << y)
  else:
    grid[x*2+0] = grid[x*2+0] & (~(0x01 << y))
    grid[x*2+1] = grid[x*2+1] & (~(0x01 << y))
  # send the updated grid to the LED matrix
  bus.write_i2c_block_data(matrix, 0, grid)

### Setup Encoders ###
xEncoder = RotaryEncoder(eQEP2)
xEncoder.setAbsolute()
xEncoder.enable()

yEncoder = RotaryEncoder(eQEP1)
yEncoder.setAbsolute()
yEncoder.enable()


prevx = 0
prevy = 0
try:
  while True:
    thisx = int(xEncoder.position/4)%8
    thisy = int(yEncoder.position/4)%8
    #print(thisx, thisy, prevx, prevy)
    flip_to(thisx, thisy, 'r')

    if (thisx != prevx or thisy != prevy):
      #print("flip old")
      flip_to(prevx, prevy, 'y')
    prevx=thisx
    prevy=thisy
    #time.sleep(0.1)
except KeyboardInterrupt:
  reset()
