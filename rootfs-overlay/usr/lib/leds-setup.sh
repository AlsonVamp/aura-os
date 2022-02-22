#!/bin/sh

echo wlan0 > /sys/class/leds/aura\:wg\:link/device_name 
echo 1 > /sys/class/leds/aura\:wg\:link/link
echo 1 > /sys/class/leds/aura\:wg\:link/tx
echo 1 > /sys/class/leds/aura\:wg\:link/rx