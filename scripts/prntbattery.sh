#!/bin/sh

# percorso per la capacità della batteria
BAT=/sys/class/power_supply/BAT0/capacity

# percorso per lo stato della batteria
STATUS=/sys/class/power_supply/BAT0/status


# Controlla se il file della capacità esiste
if [ ! -f "$BAT" ]; then
    # Se il file non esiste, restituisci "n/a" e termina lo script
    echo "n/a"
    exit 1
fi

CAPACITY=$(cat "$BAT")
STATE=$(cat "$STATUS")

if [ $STATE = "Charging" ]; then
    echo "$CAPACITY%  "
else
    echo "$CAPACITY% 󰂂 "
fi
