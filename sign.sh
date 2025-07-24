#!/bin/sh
if [ "$#" = 1 ]; then
  stty -F /dev/ttyUSB0 -hupcl raw -echo
  echo "$1" > /dev/ttyUSB0
else
  echo "$0 'Text'"
fi
