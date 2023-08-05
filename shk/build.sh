#!/bin/sh
gcc multikey_one.c -o multikey_one
gcc multikey_run.c -o multikey_run
sudo chown root:root multikey_run
sudo chmod u+s multikey_run
sudo chown root:root multikey_one
sudo chmod u+s multikey_onr
