export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
export PATH=$PATH:~/bb-kernel/dl/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabihf/bin

${CROSS_COMPILE}gcc helloWorld.c
scp a.out root@bone:.
