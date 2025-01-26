#!/bin/sh

dayandate (){
	date '+%Y. %b. %d, %a'
}

cpu () {
	~/Suckless/SuckScripts/prntcpu.sh
}

battery () {
	~/Suckless/SuckScripts/prntbattery.sh
}

wifi () {
	~/Suckless/SuckScripts/prntwifi.sh
}

timedate () {
	date '+%H:%M:%S'
}

#volume () {}


# Variabili per il controllo degli aggiornamenti
counter=21 # inizializzato per gestire possibili conflitti
wifi_data="n/a"
battery_data="n/a"
cpu_data="n/a"


while :; do

	# si aggiorna l'uso della cpu ogni 10 secondi 
	if [ $((counter % 10)) -eq 0 ]; then 
		cpu_data=$(cpu)
	fi

	# si aggiorna wifi e batteria ogni 30 secondi
	if [ $((counter % 30)) -eq 0 ]; then
		wifi_data=$(wifi)
		battery_data=$(battery)
		counter=0 # Resetta il contatore per evitare overflow
	fi

	xsetroot -name "$(dayandate)"";""[󰖩 :$wifi_data  :$cpu_data]""[$battery_data]""[$(timedate)]"

	#echo "\n"
	# Debugging
	#echo "CPU Data: $cpu_data"
	#echo "WiFi Data: $wifi_data"
	#echo "Battery Data: $battery_data"
	#echo "\n"

	# incrementa il contatore
	counter=$((counter + 1))
	# attendi 1 secondo
	sleep 1
done
