// From : http://stackoverflow.com/questions/13124271/driving-beaglebone-gpio-through-dev-mem
//
// Read one gpio pin and write it out to another using mmap.
// Be sure to set -O3 when compiling.
// Modified by Mark A. Yoder  26-Sept-2013
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <signal.h>    // Defines signal-handling functions (i.e. trap Ctrl-C)
#include "beaglebone_gpio.h"

/****************************************************************
 * Global variables
 ****************************************************************/
int keepgoing = 1;    // Set to 0 when ctrl-c is pressed

/****************************************************************
 * signal_handler
 ****************************************************************/
void signal_handler(int sig);
// Callback called when SIGINT is sent to the process (Ctrl-C)
void signal_handler(int sig)
{
    printf( "\nCtrl-C pressed, cleaning up and exiting...\n" );
	keepgoing = 0;
}

int main(int argc, char *argv[]) {
    volatile void *gpio_addr_0;
    volatile unsigned int *gpio_oe_addr_0;
    volatile unsigned int *gpio_datain_0;
    volatile unsigned int *gpio_setdataout_addr_0;
    volatile unsigned int *gpio_cleardataout_addr_0;
    volatile void *gpio_addr_1;
    volatile unsigned int *gpio_oe_addr_1;
    volatile unsigned int *gpio_datain_1;
    volatile unsigned int *gpio_setdataout_addr_1;
    volatile unsigned int *gpio_cleardataout_addr_1;
    unsigned int reg;
    long delay = atoi(argv[1]);
    // Set the signal callback for Ctrl-C
    signal(SIGINT, signal_handler);

    int fd = open("/dev/mem", O_RDWR);

    // printf("Mapping %X - %X (size: %X)\n", GPIO0_START_ADDR, GPIO0_END_ADDR, 
    //                                        GPIO0_SIZE);

    // gpio_addr_0 = mmap(0, GPIO0_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 
    //                     GPIO0_START_ADDR);
    gpio_addr_1 = mmap(0, GPIO1_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 
                        GPIO1_START_ADDR);

    // gpio_oe_addr_0           = gpio_addr_0 + GPIO_OE;
    // gpio_datain_0            = gpio_addr_0 + GPIO_DATAIN;
    // gpio_setdataout_addr_0   = gpio_addr_0 + GPIO_SETDATAOUT;
    // gpio_cleardataout_addr_0 = gpio_addr_0 + GPIO_CLEARDATAOUT;

    // if(gpio_addr_0 == MAP_FAILED) {
    //     printf("Unable to map GPIO 0\n");
    //     exit(1);
    // }

    gpio_oe_addr_1           = gpio_addr_1 + GPIO_OE;
    gpio_datain_1            = gpio_addr_1 + GPIO_DATAIN;
    gpio_setdataout_addr_1   = gpio_addr_1 + GPIO_SETDATAOUT;
    gpio_cleardataout_addr_1 = gpio_addr_1 + GPIO_CLEARDATAOUT;

    if(gpio_addr_1 == MAP_FAILED) {
        printf("Unable to map GPIO 1\n");
        exit(1);
    }
    
    // printf("GPIO mapped to %p\n", gpio_addr_0);
    // printf("GPIO OE mapped to %p\n", gpio_oe_addr_0);
    // printf("GPIO SETDATAOUTADDR mapped to %p\n", gpio_setdataout_addr_0);
    // printf("GPIO CLEARDATAOUT mapped to %p\n", gpio_cleardataout_addr_0);

    reg = *gpio_oe_addr_1;
    printf("GPIO1 configuration: %X\n", reg);
    reg &= ~(1<<16);
    reg &= ~(1<<18);
    *gpio_oe_addr_1 = reg;
    printf("GPIO1 configuration: %X\n", reg);

    // int i=0;
    while(keepgoing) {
        *gpio_setdataout_addr_1   = (1<<18);
	usleep(delay);
        *gpio_cleardataout_addr_1 = (1<<18);
        // usleep(10);
        // i++;
        usleep(delay);
    }

    // munmap((void *)gpio_addr_0, GPIO0_SIZE);
    munmap((void *)gpio_addr_1, GPIO1_SIZE);
    close(fd);
    return 0;
}
