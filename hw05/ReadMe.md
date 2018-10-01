# Cross-Compiling

To compile and deploy for the bone using compilers in `~/bb-kernel/dl/`, use `./crossCompileEnv.sh`.

The output from running the hello world program on the bone is:

`Hello, World! Main is executing at 0x103d5
This address (0xbea36bc4) is in our stack frame
This address (0x21030) is in our bss section
This address (0x21028) is in our data section`

# Kernel Modules

`make` will produce `gpio_test.ko` which can be loaded as a kernel module with `sudo insmod gpio_test.ko`. This will copy the value of `P9_15` to `P9_16` when loaded.