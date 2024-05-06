make
insmod vmalloc.ko
lsmod | grep vmalloc
rmmod vmalloc.ko
dmesg | tail -n5
make clean
