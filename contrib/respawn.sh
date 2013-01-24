#!/bin/sh
while [ -e /etc/passwd ]; do
	cat /lib/firmware/sysmobts-v2.bit > /dev/fpgadl_par0
	sleep 2s
	cat /lib/firmware/sysmobts-v?.out > /dev/dspdl_dm644x_0
	sleep 2s
	echo "0" > /sys/class/leds/activity_led/brightness
	nice -n -20 $*
	sleep 8s
done
