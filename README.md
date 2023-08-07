### Multikey
A GTK system tray applet for monitoring your Linux system and controlling your keyboards. Multikey
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
To see all the todo list items run `./multikey` from in the directory it was installed from or read
through the source code and look for `TODO("...");` items.

Make sure that the keyboard listed in `multikey_default.txt` is the main keyboard you would like
to control with the keyboard cleaning mode. (Usually the one built into your laptop)

Make file works on Arch Linux and has not been tested on any other distribution

#### Notes
- Use `cat /proc/bus/input/devices` to find event id for keyboard
- xinput --list-props "keyboard" --> Device Node
- Disable Keyboard Output
    1. Find keyboard using xinput --list
    2. xinput set-int-prop <device number> "Device Enabled" 8 0
        Ex. xinput set-int-prop 14 "Device Enabled" 8 0
