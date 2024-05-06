make
insmod request_region.ko
lsmod | grep request_region
rmmod request_region.ko
dmesg | tail -n4
make clean
