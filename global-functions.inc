#!/usr/bin/env bash

function validate_param {
	# Param is empty
	if [ -z "$1" ]; then
		echo $2
		exit
	fi
	return 0
}

function file_exists {
	validate_param $1 "No file given"

	# File doesn't exist
	if [ ! -f $1 ]; then
		echo "Can't locate file [$1]"
		return 1
	fi
	return 0
}

# Service installed
function service_installed {
	validate_param $1 "No service given"

	if dpkg -s $1 | grep -q "install ok installed"; then
		return 0
	fi
	return 1
}

# Backup a file
function backup_file {

	# Check if file exists
	if ! file_exists $1; then
		return 1
	fi

	local TARGET=$1
	if [ -n "$2" ]; then
		TARGET="$TARGET.$2"
	else
		TARGET="$1.original"
	fi

	# Check if it's already backed up
	if file_exists $TARGET; then
		echo "File [$1] already copied to [$TARGET]"
		return 0
	fi

	# Backup the file
	echo "Copying [$1] to [$TARGET]"
	sudo cp $1 $TARGET
	return 0
}

# Copy configs into temp file, replace tokens and the copy to target
function copy_configs {
	if ! file_exists $1; then
		return 1
	fi
	validate_param $2 "Destination path not given."

	if [ ! -d $_BUILDDIR_ ]; then
		sudo mkdir $_BUILDDIR_
	fi

	# Replace slashes
	local TEMP=$_BUILDDIR_/"${1//\//-}"
	cp $1 $TEMP
	local MATCHES=$( grep -o '{[A-Z]\{1,\}_[A-Z]\{1,\}}' $TEMP | sort | uniq )
	if [ -n "$MATCHES" ]; then
		for MATCH in ${MATCHES[@]}; do
			local VAR="${MATCH:1:(-1)}"
			if ! validate_param ${!VAR} "Environment variable not defined"; then
				exit
			fi
			sudo sed -i "s/$MATCH/${!VAR}/g" $TEMP
		done
	fi
	echo "Copying file to [$2]..."
	sudo cp $TEMP $2
	return 0
}
