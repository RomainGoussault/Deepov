#! /usr/bin/python3.4
#-*- coding: utf-8 -*-

import os
import sys
import argparse

def main(argv):
	print("Start Deepov tuning v0.1")
	
	# Path to the cutechess-cli executable.
	cutechess_cli_path = './cutechess-cli/cutechess-cli.sh'
	# The engine whose parameters will be optimized
	engine = 'cmd=Deepov'
	# Opponent
	opponent = 'cmd=Deepov0.2'
	# Additional cutechess-cli options
	options = ' -each proto=uci tc=100/1 -rounds 500 -pgnout matchOuput.txt -recover -repeat -openings 			file=openings.pgn'

	if argv is None:
		argv = sys.argv[1:]

	if len(argv) == 0 or argv[0] == '--help':
		print(__doc__)
		return 0

	if len(argv) < 3:
		print('Too few arguments')
		return 2

	args=createParser()
	print("List of arguments\n")
	print(args)

#	cutechessCommand = cutechess_cli_path + engine + opponent + options

def createParser():
	parser = argparse.ArgumentParser(description='Get tuning parameters ...')
	parser.add_argument("engine", help="Path to the engine to tune.")
	parser.add_argument("opponent", help="Path to the opponent engine.")
	parser.add_argument("cutechess", help="Path to cutechess.")
	parser.add_argument("-v", "--verbose", help="Increase output verbosity.",action="store_true")
	parser.add_argument("-t", "--time", help="Define the allocated time for engines in cutechess. The format is moves/time+increment, where moves is the number of moves per tc, time is time per tc (either seconds or minutes:seconds), and increment is time increment per move in seconds. Infinite time control can be set with tc=inf (source : cutechess doc).",default="100/1")
	parser.add_argument("-r", "--rounds", help="Number of rounds to play between the engines",type=int,default=500)
	parser.add_argument("-b", "--book", help="Openings book file path",default="openings.pgn")
	return parser.parse_args()


#def parseArguments(argv):
#	try:                                
#     #   opts, args = getopt.getopt(argv, "hpitrb", ["help", "path=","input=","time=","rounds=","book=" ])
#		
#    except getopt.GetoptError:
#        usage()
#        sys.exit(2)          

#def runCutechess(command):
#	process = subprocess.Popen(cutechessCommand.split())
#	output = process.communicate()[0]
#    if process.returncode != 0:
#        print('Could not execute command: %s' % command)
#        return 2

#	return output


# execution of the tuning
if __name__ == '__main__':
    # sys.exit(main(sys.argv)) # used to give a better look to exists
    main(sys.argv[1:]) # sys.argv[0] is the name of the script


