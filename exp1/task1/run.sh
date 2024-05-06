make
insmod kmalloc.ko
lsmod | grep kmalloc
rmmod kmalloc.ko
dmesg | tail -n6
make clean
