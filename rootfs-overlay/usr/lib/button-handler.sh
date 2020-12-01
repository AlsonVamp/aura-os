#!/bin/sh

device='/dev/input/event0'
event_pwr='*code 116 (KEY_POWER), value 1*'

evtest "$device" | while read line; do
  case $line in
    ($event_pwr) shutdown -h now ;;
  esac
done
