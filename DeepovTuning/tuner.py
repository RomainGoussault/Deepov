#! /usr/bin/python3.4
#-*- coding: utf-8 -*-

import sys
import subprocess
import argparse
import socket
import platform

def main(argv):
    print("Start Deepov tuning v0.1")
        


    if argv is None:
        argv = sys.argv[1:]

    args=createParser()
#	print("List of arguments\n")
#	print(args)
	

    if args.verbosity:
        print('Sending command to cutechess :')
        print(cutechessCommand)
        print('\n')
	

	
    results = runCutechess(cutechessCommand)
    
    if args.verbosity:
        print(results)

    return 0
    
def cutechessConfig(args):
    """ This function defines the cutechess parameters for the elo evaluation : 
    returns cutechess and engine location (first return), matches configuraton (second return). """
    # cutechess command    
    command = '{0} -engine cmd={1} dir={2}'.format(args.cutechess,args.engine,args.dir)
    # Opponent
    config = ' -engine cmd={1} dir={2}'.format(args.opponent,args.dir)
    # Optional arguments
    config += ' -each proto=uci tc={0} -rounds {1} -pgnout {2}  -openings file={3}'.format(args.time,args.rounds,args.output,args.book)
    # Default cutechess-cli options
    config += ' -recover -repeat -site {}'.format(socket.gethostname())
    
    return command,config
    
def initParameters(args):
    
    if (len(args.name) != len(args.guess) or len(args.name) != len(args.bounds) or len(args.guess) != len(args.bounds)):
        print('Parameters should have an initial value and a range of possible values.')
        return 2
    
    optionMap = dict()
    while i < len(args.name):
        optionMap[args.name[i]] = (args.guess[i],args.bounds[i][1],args.bound[i][2])
        
    return optionMap
    
        
def engineConfig(**name,**value):
    return parameters
    
    
def generateCommand():
    cutechessCommand = command + parameters + config
    return cutechessCommand

def createParser():
    """ Creates the command line interface """
    # Get system bit version   
    bitVersion = platform.architecture()
    if (bitVersion[0] == '32bit'):
        defaultCutechess = './cutechess-cli32.sh'
    else:
        defaultCutechess = './cutechess-cli.sh'

    parser = argparse.ArgumentDefaultsHelpFormatter(description='Program to tune Deepov chess engine parameters.')
    parser.add_argument("engine", help="Executable of the engine to tune.")
    parser.add_argument("opponent", help="Executable of opponent engine.")
    parser.add_argument("-d","--dir", help="Path to the engines folder",default='./')
    parser.add_argument("-c","--cutechess", help="Path to cutechess.",default=defaultCutechess)
    parser.add_argument("-v", "--verbosity", help="Increase output verbosity.", action="store_true")
    parser.add_argument("-t", "--time", help="Define the allocated time for engines in cutechess. The format is moves/time+increment, where moves is the number of moves per tc, time is time per tc (either seconds or minutes:seconds), and increment is time increment per move in seconds. Infinite time control can be set with tc=inf (source : cutechess doc).", default="100/1")
    parser.add_argument("-r", "--rounds", help="Number of rounds to play between the engines",default='500')
    parser.add_argument("-b", "--book", help="Openings book file path", default="openings.pgn")
    parser.add_argument("-o", "--output", help="Output file ", default="a.out")
    
    # Add parameters arguments
    parser.add_argument("-n", "--name", help="Name of the parameter", action="append", type=str)
    parser.add_argument("-x0", "--guess", help="Initial guess for the parameter value", action="append", default=0, type=int)
    parser.add_argument("--bounds", help="Lower and upper bound of the parameter range", action="append", default=[0,0], type=int)

    return parser.parse_args()

def setOption(name,value):
	value=str(value)
	option = "setoption {} value {}".format(name,value)
	return option

def runCutechess(command):
    """ A function to simply run the cutechess command """
    process = subprocess.Popen(command.split(), stdout=subprocess.PIPE)
    output = process.communicate()[0]
    if process.returncode != 0:
        print('Could not execute command: %s' % command)
        return 2
    
    return output


# execution of the tuning
if __name__ == '__main__':
    # sys.exit(main(sys.argv)) # used to give a better look to exists
    main(sys.argv[1:]) # sys.argv[0] is the name of the script


