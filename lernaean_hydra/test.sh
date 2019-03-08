#! /bin/sh

run() {
	make >/dev/null && ./hydra -D
}

kill() {
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
