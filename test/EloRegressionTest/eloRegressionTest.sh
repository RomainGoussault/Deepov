#!/bin/bash

echo "Starting ELO testing script"

#Copying current version to the test folder
cp ../../Deepov DeepovCurrent

git clone --branch=master git://github.com/RomainGoussault/Deepov.git LatestRelease/
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

cp Deepov ../Deepov
cd ..

./cutechess-cli.sh -engine cmd=DeepovCurrent -engine cmd=Deepov -each proto=uci tc=100/2 -rounds 2 -pgnout matchOuput.txt -recover -repeat | while read line; do
		
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
