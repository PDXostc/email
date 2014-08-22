#!/bin/bash

# check if app is up and running after 2s, if not try to start it again

# This launches 3 services as background processes for email and messaging.
# They are:
#
#    msg-server
#    contacts-service-ipcd
#    email-service
#
# We should move these to a more standard deamon launch.


sleep 2

rm -f /tmp/vcon.log

echo "##################################################" >> /tmp/vcon.log
date                                                      >> /tmp/vcon.log

while true; do
    proc=`ps aux | grep e[m]ail-service` # [] used to exclude grep itself
    set -- $proc
    if [ -z "$2" ]; then
        # the application is not running - start it again

        echo "No email-service running"                                         >> /tmp/vcon.log

        /bin/vconftool set -t int  memory/dnet/status 2 -f                 2>&1 >> /tmp/vcon.log
        /bin/vconftool set -t int  memory/dnet/network_config 1 -f         2>&1 >> /tmp/vcon.log
        /bin/vconftool set -t int  memory/dnet/wifi 2 -f                   2>&1 >> /tmp/vcon.log
        /bin/vconftool set -t int  memory/wifi/state 2 -f                  2>&1 >> /tmp/vcon.log
        /bin/vconftool set -t int  memory/wifi/transfer_state 3 -f         2>&1 >> /tmp/vcon.log
        /bin/vconftool set -t int  memory/sync/email  1 -f                 2>&1 >> /tmp/vcon.log
        #vconftool set -t string memory/dnet/proxy "http://10.245.64.22:83" -f 
  
        # make sure we do not double launch the msg-server or contacts-service-ipcd
        proc=`ps aux | grep m[s]g-server`
        set -- $proc
        if [ -z "$2" ]; then
            echo "Launching msg-server"                        >> /tmp/vcon.log
            /bin/msg-server                               2>&1 >> /tmp/vcon.log &
        fi

        proc=`ps aux | grep c[o]tacts-service-ipcd`
        set -- $proc
        if [ -z "$2" ]; then
            echo "Launching contacts-service-ipcd"             >> /tmp/vcon.log
            /bin/contacts-service-ipcd                    2>&1 >> /tmp/vcon.log &
        fi

        echo "Launching email-service"                         >> /tmp/vcon.log
        /bin/email-service                                2>&1 >> /tmp/vcon.log &
    else
        echo "email-service running, exitting"                 >> /tmp/vcon.log
        break
    fi
    sleep 5 # check every 5 seconds
done

