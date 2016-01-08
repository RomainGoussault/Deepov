# -*- coding: utf-8 -*-
"""
Created on Fri Jan  8 06:14:08 2016

@author: navid
"""
import platform
import socket
import argparse
from tuner import main_command, main_config

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
    """ Convert the parameters given by command line to a dictionnary.
    The dictionnary value is a tuple, its first value is the initial parameter value.
    Second and third value are the bounds """
    
    
    if (len(args.name) != len(args.guess) or len(args.name) != len(args.bounds) or len(args.guess) != len(args.bounds)):
        print('Parameters should have an initial value and a range of possible values.')
        # TODO : initial guess should be optional
        return 2
    
    optionMap = dict()
    i=0
    # Go through the args.name list and build it into a dictionnary
    while i < len(args.name):
        optionMap[args.name[i]] = (args.guess[i],args.bounds[i][1],args.bound[i][2])
        i+=1
        
    return optionMap
    
        
def engineConfig(optionMap):
    """ Transform the dictionnary of parameters to a command line option in cutechess. 
    The dictionnary value is a tuple, its first value is the parameter value.
    Second and third value are the bounds and are not used as arguments to cutechess"""    
    
    parameters=''
    for key in optionMap.keys():
        parameters +='option.{0}={1}'.format(key,optionMap[key][1])
    return parameters
    
    
def generateCommand(parameters):
    """ Add the main command, the parameters and the config together to make a cutechess command"""
    # main_command and main_config are global variables and do not change during the process
    # parameters is the output of engineConfig, and changes at each evaluation of the engine score
    cutechessCommand = main_command + parameters + main_config
    return cutechessCommand


def createParser():
    """ Creates the command line interface using argsparse package"""
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
    # bounds are given as a list of two parameters
    # TODO : initial guess should be optional
    parser.add_argument("-n", "--name", help="Name of the parameter", action="append", type=str)
    parser.add_argument("-x0", "--guess", help="Initial guess for the parameter value", action="append", default=0, type=int)
    parser.add_argument("--bounds", help="Lower and upper bound of the parameter range", action="append", default=[0,0], type=int)

    return parser.parse_args()