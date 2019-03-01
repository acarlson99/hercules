#! /bin/sh

sed 's/#Port 22/Port 50000/' /etc/ssh/sshd_config > sshd_config.tmp
mv sshd_config.tmp /etc/ssh/sshd_config
service sshd restart
