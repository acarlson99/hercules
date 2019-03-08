#! /bin/sh

run() {
	if [ ! $(pgrep 'hydra') ]
	then
		echo 'Releasing new hydra'
		make >/dev/null && ./hydra -D
	else
		echo 'There is already one hydra alive and kicking.  One at a time'
	fi
}

kill() {
	if [ $(pgrep 'hydra') ]
	then
		echo 'Slicing heads and cauterizing wounds'
		pkill hydra
	else
		echo 'Hydra has already been slain'
	fi
}

connect() {
	echo 'Attempting to connect to server'
	if [ $(pgrep 'hydra') ]
	then
		nc localhost $(grep PORT src/server.h | awk '{print $4}')
	fi
}

isrunning() {
	if [ $(pgrep 'hydra') ]
	then
		echo 'Server is running'
		return 0
	else
		echo 'Server not running'
		return 1
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
	re)
		kill && run
		;;
	restart)
		kill && run
		;;
	connect)
		connect
		;;
	isrunning)
		isrunning
		;;
	check)
		isrunning
		;;
	*)
		echo 'Usage:
\trun/setup:        run server as daemon
\tkill/shutdown:    kill server
\tre/restart:          restart server
\tconnect:          connect to server for testing
\tisrunning/check:  check if server is running'
		exit 1
		;;
esac
