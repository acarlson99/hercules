#! /bin/sh

run() {
	echo 'Attempting to run hydra'
	if [ ! $(pgrep 'hydra') ]
	then
		echo 'Running hydra'
	   make >/dev/null && ./hydra -D
	else
		echo 'There is already one hydra alive and kicking.  One at a time'
	fi
}

kill() {
	echo 'Slicing heads and cauterizing wounds'
	pkill hydra
}

connect() {
	echo 'Attempting to connect to server'
	nc localhost $(grep PORT src/server.h | awk '{print $4}')
}

check() {
	if [ $(pgrep 'hydra') ]
	then
		echo 'Server is running'
		return 1
	else
		echo 'Server not running'
		return 0
	fi
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
	check)
		check
		;;
	*)
		echo "Usage:
\trun/setup:      runs server as daemon
\tkill/shutdown:  kills server
\tconnect:        connects to server for testing"
		;;

esac
