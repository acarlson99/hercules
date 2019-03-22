#! /bin/bash

MONTH=12
DAY=21
HOUR=08
MINUTE=42
read -p "Would you like to set the script for ${MONTH}${DAY}${HOUR}${MINUTE}? [yn] " -r
if [[ $REPLY =~ ^[Yy] ]]
then
	at -t ${MONTH}${DAY}${HOUR}${MINUTE} -f execute_me.sh
elif [[ $REPLY =~ ^[nN] ]]
then
	echo 'Terminating'
else
	echo 'Invalid command.  Terminating'
fi
