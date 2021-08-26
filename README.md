# Suckless Hot Keys
Although not suckless in theory, the configuration of this applicaiton is meant to replicate suckless programs. This program just looks at the keyboard input event and runs actions based on the type of key and what the user specifies.

use `cat /proc/bus/input/devices` to find event id for keyboard

## todo
* [ ] create config.def.h and custom rc file in config folder later
* [ ] put /dev/input/ reading into a function
* [ ] add ability to choose between different keyboards ie. "/dev/intput/event*"
* [ ] add mod key ability ie. "ev.code == KEY.value == EVCODE_DEPRESS"
