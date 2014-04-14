#!/bin/sh
clear
cp -r ./wrt_plugin_src/Emailplugin /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src/
cp ./wrt_plugin_src/wrt-plugins-tizen-emailplugin.pc /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/pkgconfigs/
cp ./wrt_plugin_src/wrt-plugins-tizen-emailplugin.pc.in /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/pkgconfigs/
cd /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/ 
cmake .
cd src/Emailplugin
make clean
make
cd ../..
make install
cp -rv /usr/local/lib/wrt-plugins/tizen-emailplugin /usr/lib/wrt-plugins/
wrt-installer -p
cd src/Emailplugin

