#!/bin/sh

dayandate (){
	date '+%d. %b. %Y, %a'
}

timedate () {
	date '+%H:%M:%S'
}

# cpu usage
cpu () {
	# Ottieni i valori di idle dalla seconda riga di `vmstat`
	idle=$(vmstat 1 2 | tail -1 | awk '{print $15}')

	# Calcola l'uso della CPU come 100% meno il tempo inattivo
	cpu_usage=$((100 - idle))

	# wMostra il risultato
	echo "${cpu_usage}%"
}

# ram usage
ram () {
  # Ottieni la memoria totale e quella usata da /proc/meminfo
  total_mem=$(awk '/MemTotal/ {print $2}' /proc/meminfo)
  used_mem=$(awk '/MemAvailable/ {print $2}' /proc/meminfo)
  
  # Calcola la percentuale di memoria usata
  ram_usage=$(( (total_mem - used_mem) * 100 / total_mem ))
  # Mostra l'uso della RAM come percentuale
  echo "${ram_usage}%"
}

# read battery perc. and the state
battery () {
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
    	echo ":$CAPACITY%"
	else
    	echo "󰂂:$CAPACITY%"
	fi
}

# verify wifi connection
wifi () {
	# Estrai il livello di segnale con una sola operazione
	SIGNAL=$(nmcli -t -f IN-USE,SIGNAL dev wifi | awk -F: '/^\*:/{print $2}')

	# Verifica se il segnale è vuoto
	if [ -z "$SIGNAL" ]; then
    	echo "n/a"
	else
    	echo "$SIGNAL"
	fi
}


# Variabili per il controllo degli aggiornamenti
counter=7 # inizializzato per gestire possibili conflitti
wifi_data="n/a"
battery_data="n/a"
cpu_data="n/a"
ram_data="n/a"


while :; do

	# si aggiorna cpu, ram ogni 5 secondi
	if [ $((counter % 5)) -eq 0 ]; then
		cpu_data=$(cpu)
		ram_data=$(ram)
	fi

	# si aggiorna la batteria, wifi ogni 10 secondi
	if [ $((counter % 10)) -eq 0 ]; then
		wifi_data=$(wifi)
		battery_data=$(battery)
		counter=0 # Resetta il contatore per evitare overflow
	fi

	xsetroot -name "$(dayandate)"";""[󰖩 :$wifi_data |  :$cpu_data -  :$ram_data | $battery_data]""[$(timedate)]"

	# incrementa il contatore
	counter=$((counter + 1))
	# attendi 1 secondo
	sleep 1
done
