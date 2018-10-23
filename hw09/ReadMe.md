# Usage
Run `. setup.sh <part_number>` (source or `.`, don't just run!), then `make` will build and run the specified part on the correct PRU.

| # |Part     | Result                                                                                | Image                                                         |
| - | ------- | ------------------------------------------------------------------------------------- | ------------------------------------------------------------- |
| 1 | Blink   | The max speed was 12.5 MHz. Jitter was bad (-1.1 to 3.8V), but output is consistent.  | ![alttxt](imgs/1-blink.jpg)                                   |
| 2 | PWM     | The standard deviation is 3.6 MHz. Jitter exists but isn't very large.                | ![alttxt](imgs/2-pwm.jpg)                                     |
| 3 | mmap    | The highest frequency is 650 kHz and there is significant jitter (+4.9 to -1.1 V).    | ![alttxt](imgs/3-mmap.jpg)                                    |
| 4 | unroll  | Unrolling really speeds things up; all the way to 2.9 MHz!                            |                                                               |
| 5 | reading | The response time is around 50 ns.                                                    |                                                               |
| 6 | analog  | The analog works! I used a 0.1 uf capacitor and the pot turned all the way to 10kOhm. | ![alttxt](imgs/6-analog_1.jpg) ![alttxt](imgs/6-analog_2.jpg) |
