#!/bin/sh
cd wrt_plugin
cmake
make clean
make
make install
wrt-installer -p

cp ../vcon.sh /usr/lib/systemd/system/
cp ../email.service /usr/lib/systemd/system/
systemctl enable email
