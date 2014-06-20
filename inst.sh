#!/bin/sh
cd wrt_plugin
cmake .
make clean
make
make install
wrt-installer -p
cp ../vcon.sh /etc/profile.d/vcon.sh

