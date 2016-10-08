#!/bin/bash

echo "Starting ELO testing script"

##Copying current version to the test folder
cp ../../Deepov DeepovCurrent

if [ ! -f Deepov ]; then

    echo "Deepov not found. Cloning from github and building"

	git clone --depth 1 --branch=master git://github.com/RomainGoussault/Deepov.git LatestRelease/
	cd LatestRelease/
	mkdir obj

	# Get new tags from remote
	git fetch --tags 

	# Get latest tag name
	latestTag=$(git describe --tags `git rev-list --tags --max-count=1`)

	# Checkout latest tag
	git checkout $latestTag

	#Compile it and make it executable
	make Deepov
	chmod +x Deepov

	#Copying latest release version to the test folder
	cp Deepov ../Deepov
	cd ..
fi

./cutechess-cli.sh -engine cmd=DeepovCurrent -engine cmd=Deepov -each proto=uci tc=100/1+0.01 -rounds 700 -pgnout matchOuput.txt -recover -repeat -openings file=openings.pgn | while read line; do

		
	echo "$line"
		
	if [[ "$line" == *ELO*  ]]; then

		#Ouput ELO line
		echo "$line"
	
		minusSign=`echo "$line" | grep -o "-"`

		if [[ $minusSign ]]; then
		
		eloDiff=`echo "$line" | grep -o "[0-9]*"`
		
			if [[ $eloDiff -ge 20 ]]; then #allow up to 20 in Regression
		
				echo "Regression"
				exit 1
			fi
		fi

		echo "No Regression well done"
		exit 0

	fi
done
