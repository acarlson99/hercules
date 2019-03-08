#! /bin/sh

run() {
	echo "Running hydra"
	a=$(pgrep 'hydra')
	echo $a
	if [ ! $a ]
	then
	   make >/dev/null && ./hydra -D
	else
		echo 'There is already one hydra alive and kicking.  One at a time'
	fi
}

kill() {
	echo "Slicing heads and cauterizing wounds"
	pkill hydra
}

connect() {
	nc localhost $(grep PORT server.h | awk '{print $4}')
}

case $1 in
	run)
		run
		;;
	setup)
		run
		;;
	kill)
		kill
		;;
	shutdown)
		kill
		;;
	restart)
		kill && run
		;;
	connect)
		connect
		;;
	*)
		echo "Usage:
\trun/setup:      runs server as daemon
\tkill/shutdown:  kills server
\tconnect:        connects to server for testing"
		;;

esac
