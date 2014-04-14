#!/bin/sh
clear
zypper install ss-server
zypper install msg-service
zypper install msg-service-tools
zypper install contacts-service2
zypper install email-services 
cp -r ./wrt_plugin_src/Emailplugin /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src/
cp ./wrt_plugin_src/wrt-plugins-tizen-emailplugin.pc.in /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/pkgconfigs/
cd /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src 

