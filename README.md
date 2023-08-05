### MultiKey
A GTK system tray applet for monitoring your Linux system and controlling your keyboards. MultiKey
allows you to use extra external keyboards as custom "macro keyboards" by being able to assign
individual events to each key on each keyboard.

#### Dependencies
```
- gtk3
- libappindicator-gtk3
- lm_sensors
- font awesome
```

#### Quick Start
```console
$ sudo make install
$ ./multiKey
```

#### Notes
- use `cat /proc/bus/input/devices` to find event id for keyboard
- xinput --list-props "keyboard" --> Device Node
- Disable Keyboard Output
    1. Find keyboard using xinput --list
    2. xinput set-int-prop <device number> "Device Enabled" 8 0
        Ex. xinput set-int-prop 14 "Device Enabled" 8 0
- MultiKey status
    1. cpuUsed% memoryUsedGB storageUsedGB
    2. Keyboard cleaning mode
    3. List all keyboards available to program using shk
    4. Quit
