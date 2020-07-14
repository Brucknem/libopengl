#!/bin/sh
export XAUTHORITY=~/.Xauthority
Xvfb :99 &
export DISPLAY=:99
