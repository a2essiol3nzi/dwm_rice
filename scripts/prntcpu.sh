#!/bin/bash

# Ottieni i valori di idle dalla seconda riga di `vmstat`
idle=$(vmstat 1 2 | tail -1 | awk '{print $15}')

# Calcola l'uso della CPU come 100% meno il tempo inattivo
cpu_usage=$((100 - idle))

# Mostra il risultato
echo "${cpu_usage}%"
