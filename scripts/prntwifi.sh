#!/bin/sh

# Estrai il livello di segnale
SIGNAL=$(nmcli -t -f IN-USE,SIGNAL dev wifi | grep '^*:' | cut -d':' -f2)

if [ -z "$SIGNAL" ]; then
    echo "n/a"
else
    echo "$SIGNAL"
fi