#!/bin/sh
xinput --list | grep "Keyboard" | grep -Ev "pointer" | cut -c 9- | awk '{print $1 " " $2 " " $3}' > keyboards.txt
