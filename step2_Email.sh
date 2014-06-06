#!/bin/sh
clear
# create /prj folder and dependencies
cd /
mkdir prj
cd prj
mkdir wrt-plugins-ivi
mkdir GITFolder
cd GITFolder
git clone https://github.com/PDXostc/16-Email
cd /prj/GITFolder/16-Email/WRT_Plugin_IVI
find *.rpm | xargs rpm2cpio | cpio -idmv
find *.gz | xargs tar xzf
sleep 2m
cp -R wrt-plugins-ivi-0.13.0 /prj/wrt-plugins-ivi
cd /prj/GITFolder/16-Email/
cp -r ./wrt_plugin_src/Emailplugin /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src/
cp ./wrt_plugin_src/wrt-plugins-tizen-emailplugin.pc.in /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/pkgconfigs/

cd /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/src/
sed -i "s/\(^add_plugin(\)/\1\n\tEmailplugin/" CMakeLists.txt
cd /prj/wrt-plugins-ivi/wrt-plugins-ivi-0.13.0/
cmake .
make
make install
cp -r /usr/local/lib/wrt-plugins/tizen-emailplugin /usr/lib/wrt-plugins
wrt-installer -p
echo "cd /prj/GITFolder/16-Email" >> /etc/profile.d/local_env.sh
echo "./vcon.sh" >> /etc/profile.d/local_env.sh
echo "cd /" >> /etc/profile.d/local_env.sh
source /etc/profile.d/local_env.sh






