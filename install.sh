#!/bin/sh
clear
./prep.sh
cd /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src 
cmake .
cd src/Emailplugin
make clean
make
cd ../..
make install
cp -rv /usr/local/lib/wrt-plugins/tizen-emailplugin /usr/lib/wrt-plugins/
wrt-installer -p
cd src/Emailplugin
echo "cd /prj/GITFolder/16-Email" >> /etc/profile.d/local_env.sh
echo "./vcon.sh" >> /etc/profile.d/local_env.sh
source /etc/profile.d/local_env.sh


