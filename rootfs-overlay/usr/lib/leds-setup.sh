#!/bin/sh

# wireguard indicator
echo wg0 > /sys/class/leds/aura\:wg\:link/device_name 
# echo 1 > /sys/class/leds/aura\:wg\:link/link
echo 1 > /sys/class/leds/aura\:wg\:link/tx
echo 1 > /sys/class/leds/aura\:wg\:link/rx

# buzzer
echo 100 > /sys/class/leds/aura:beeper/delay_on
echo 1 > /sys/class/leds/aura:beeper/shot