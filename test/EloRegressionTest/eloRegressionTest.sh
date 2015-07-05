#!/bin/bash

echo "Starting ELO testing script"

#Copying current version to the test folder
cp ../../Deepov Deepov


#getting latest release
wget https://github.com/RomainGoussault/Deepov/releases/download/v0.1/Deepov0.1_linux.1

#make it executable
chmod +x Deepov0.1_linux.1

#list files for debug
ls



./cutechess-cli.sh -engine cmd=Deepov -engine cmd=Deepov0.1_linux.1 -each proto=uci tc=100/2 -rounds 2 -pgnout matchOuput.txt -recover -repeat | while read line; do

	if [[ "$line" == *ELO*  ]]; then

		#Ouput ELO line
		echo "$line"
	
		minusSign=`echo "$line" | grep  -o "-"`
		#echo "elo diff $minusSign"

		if [[ $minusSign ]]; then
		
			echo "Regression"
			exit 1

		else

			echo "No Regression well done"
			exit 0
		fi
	fi
done
