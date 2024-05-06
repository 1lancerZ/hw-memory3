make
insmod request_mem_region.ko
lsmod | grep request_mem_region
rmmod request_mem_region.ko
dmesg | tail -n3
make clean
