#! /usr/bin/python3.4
#-*- coding: utf-8 -*-

import os
import sys
import subprocess
import argparse
import socket

def main(argv):
	print("Start Deepov tuning v0.1")
	
	# Default cutechess-cli options
	protocol = '-each proto=uci '
	otherOptions = '-recover -repeat -event "Deepov Tuning" -site '

	if argv is None:
		argv = sys.argv[1:]

	args=createParser()
#	print("List of arguments\n")
#	print(args)
	

# Mandatory arguments
	cutechessCommand = (args.cutechess + ' -engine cmd=' + args.engine + ' dir=' + args.dir +
	' -engine cmd=' + args.opponent + ' dir=' + args.dir)
# Optional arguments
	cutechessCommand += (' -each proto=uci tc=' + args.time + ' -rounds ' + args.rounds + ' -pgnout ' + args.output +
	' -openings file=' + args.book)
# Some options set as default
	cutechessCommand += ' ' + otherOptions + socket.gethostname()
	
	if args.verbosity:
		print('Sending command to cutechess :')
		print(cutechessCommand)
		print('\n')
	
	runCutechess(cutechessCommand)

	return 0

def createParser():

	parser = argparse.ArgumentParser(description='Program to tune Deepov chess engine parameters.')
	parser.add_argument("engine", help="Executable of the engine to tune.")
	parser.add_argument("opponent", help="Executable of opponent engine.")
	parser.add_argument("-d","--dir", help="Path to the engines folder",default='./')
	parser.add_argument("-c","--cutechess", help="Path to cutechess.",default='./cutechess-cli.sh')
	parser.add_argument("-v", "--verbosity", help="Increase output verbosity.", action="store_true")
	parser.add_argument("-t", "--time", help="Define the allocated time for engines in cutechess. The format is moves/time+increment, where moves is the number of moves per tc, time is time per tc (either seconds or minutes:seconds), and increment is time increment per move in seconds. Infinite time control can be set with tc=inf (source : cutechess doc).", default="100/1")
	parser.add_argument("-r", "--rounds", help="Number of rounds to play between the engines",default='500')
	parser.add_argument("-b", "--book", help="Openings book file path", default="openings.pgn")
	parser.add_argument("-o", "--output", help="Output file ", default="a.out")

	return parser.parse_args()

def setOption(name,value):
	value=str(value)
	option = "setoption " + name + " value " + value	
	return option
	


#def parseArguments(argv):
#	try:                                
#     #   opts, args = getopt.getopt(argv, "hpitrb", ["help", "path=","input=","time=","rounds=","book=" ])
#		
#    except getopt.GetoptError:
#        usage()
#        sys.exit(2)          

def runCutechess(command):
	process = subprocess.Popen(command.split())
	output = process.communicate()[0]
	if process.returncode != 0:
		print('Could not execute command: %s' % command)
		return 2

	return output


# execution of the tuning
if __name__ == '__main__':
    # sys.exit(main(sys.argv)) # used to give a better look to exists
    main(sys.argv[1:]) # sys.argv[0] is the name of the script


