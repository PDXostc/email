#!/bin/sh
clear
zypper --non-interactive refresh
zypper --non-interactive install git
zypper --non-interactive install cmake
zypper --non-interactive install libuuid-devel
zypper --non-interactive install make
zypper --non-interactive install gcc
zypper --non-interactive install gcc-c++
zypper --non-interactive install boost-devel
zypper --non-interactive install json-glib-devel
zypper --non-interactive install dlogutil
zypper --non-interactive install ss-server
zypper --non-interactive install msg-service
zypper --non-interactive install contacts-service2
zypper --non-interactive install msg-service-tools
zypper --non-interactive install email-service
zypper --non-interactive install libuw-imap-toolkit-devel
zypper --non-interactive install drm-client-devel
zypper --non-interactive install wrt-plugins-tizen-devel


