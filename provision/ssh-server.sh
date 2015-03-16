#!/usr/bin/env bash

cat <<STOP
|--------------------------
| Install SSH server
|--------------------------

STOP

hash sshd 2>/dev/null && {
	echo 'SSH server already installed'
} || {
	echo 'Installing SSH server...'
	sudo apt-get install openssh-server -y
}
