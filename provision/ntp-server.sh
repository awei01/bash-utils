#!/usr/bin/env bash

cat <<STOP
|--------------------------
| Install NTP time server
|--------------------------

STOP

# Install ntp time server as it's required by Kerberos
if service_installed ntp; then
	echo "NTP already installed"
else
	echo "Installing NTP..."
	sudo apt-get install ntp -y
fi
