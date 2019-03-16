#! /bin/bash

if [ $# -eq 2 ]
then
	echo "> Setting UID and secret"
	export ceryneian_hind_UID="$1"
	export ceryneian_hind_SECRET="$2"
else
	echo "usage: ./setup.sh UID SECRET"
	exit 1
fi
