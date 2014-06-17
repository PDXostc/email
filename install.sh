#!/bin/sh
cd wrt_plugin_src
cmake .
make clean
make
make install
wrt-installer -p
cp ../vcon.sh /etc/profile.d/vcon.sh
cd ../WGT
wrt-installer -i Email.wgt

