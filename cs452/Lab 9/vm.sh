#!/bin/bash
#
# Bash script to run vmstat infinitely every 1 second
#
# @author Ron Rounsifer

while :
do
	vmstat;
	sleep 1;
done
