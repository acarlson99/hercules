#! /bin/bash

if [ $EUID -ne 0 ]
then
	echo "Run as super user"
	exit 1
fi

apt-get install openssh-server -y

if [ ! -f /etc/ssh/sshd_config ]
then
	echo "File not found"
	exit 1
fi

sed 's/^#\? \?Port .*/Port 50000/' /etc/ssh/sshd_config > sshd_config.tmp

if [ ! -f sshd_config.tmp ]
then
	echo "File not found"
	exit 1
fi

mv sshd_config.tmp /etc/ssh/sshd_config
service sshd restart
