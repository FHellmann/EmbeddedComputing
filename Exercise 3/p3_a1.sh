#!/bin/bash
cd /sys/class/leds/beaglebone:green:usr0
echo timer > trigger
cd /sys/class/leds/beaglebone:green:usr1
echo timer > trigger
