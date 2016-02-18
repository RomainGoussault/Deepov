# -*- coding: utf-8 -*-
"""
Created on Fri Jan  8 06:14:08 2016

@author: navid
"""

import sys
import platform
import socket
import argparse
import settings



# Global variables
#main_command = ''
#main_config = ''

def cutechessConfig(args):
    """ This function defines the cutechess parameters for the elo evaluation : 
    returns cutechess and engine location (first return), matches configuraton (second return). """
    # cutechess command    
    command = '{0} -engine cmd={1} dir={2}'.format(args.cutechess,args.engine,args.dir)
    # Opponent
    config = ' -engine cmd={0} dir={1}'.format(args.opponent,args.dir)

    # Optional arguments
    config += ' -each proto=uci tc={0} -rounds {1} -pgnout {2} -openings file={3}'.format(args.time,args.rounds,args.output,args.book)
    # Default cutechess-cli options
    config += ' -recover -repeat -site {}'.format(socket.gethostname())
    config += ' -concurrency 7' 
    
    return command,config
    
    
def initParameters(args):
    """ Convert the parameters given by command line to a list of tuples.
    The first tuple value is the name, its second value is the initial parameter value.
    Third and fourth value are the bounds. Fifth value is the minimal interval """
    print(args.name)
    print(args.bounds)   
    if (len(args.name) != len(args.bounds)):
        sys.exit('Parameters should have a range of possible values (1).')
    
    parametersList=list()
    i=0
    # Go through the args.name list and build it into a dictionnary
    while i < len(args.name):
        # Handle incorrect inputs
        if (len(args.bounds[i]) < 2 ):
            sys.exit('Parameters should have a range of possible values.')
        if (len(args.bounds[i]) < 3 ):
            args.bounds[i].append(1)
            print('Default interval set to 1.')
            args.bounds[i].append(args.bounds[i][1])
            print('Default initial value set to {}'.format(args.bounds[i][1]))
        
        # Add the list
        current_list = [args.name[i]] + args.bounds[i]
        parametersList.append(current_list)
        i+=1
        
    return parametersList
    
        
def setParam(paramList):
    """ Transform the list of parameters to a command line option in cutechess. 
    The dictionnary value is a tuple, its first value is the parameter value.
    Second and third value are the bounds and are not used as arguments to cutechess"""    
    
    parameters=''
    for i in range(0,len(paramList)):
        parameters +=' option.{0}={1} '.format(paramList[i][0],paramList[i][4])
    return parameters
    
    
def generateCommand(parameters):
    """ Add the main command, the parameters and the config together to make a cutechess command"""
    # main_command and main_config are global variables and do not change during the process
    # parameters is the output of setParam, and changes at each evaluation of the engine score
    cutechessCommand = settings.main_command + parameters + settings.main_config
    return cutechessCommand
    
def multiple(arg):
    """ Defines a list of integers from integers separeted with ,"""
    # http://stackoverflow.com/questions/33499173/how-to-create-argument-of-type-list-of-pairs-with-argparse
    # If you want to do more
    # validation, raise argparse.ArgumentError if you
    # encounter a problem.
    return [int(x) for x in arg.split(',')]


def createParser():
    """ Creates the command line interface using argsparse package"""
    # Get system bit version   
    bitVersion = platform.architecture()
    if (bitVersion[0] == '32bit'):
        defaultCutechess = './cutechess-cli32.sh'
    else:
        defaultCutechess = './cutechess-cli.sh'

    parser = argparse.ArgumentParser(prog='tuner.py',
                                     description='Program to tune Deepov chess engine parameters.',
                                     formatter_class=argparse.ArgumentDefaultsHelpFormatter)
                                     
    parser.add_argument("engine", help="Executable of the engine to tune.")
    parser.add_argument("opponent", help="Executable of opponent engine.")
    parser.add_argument("-d","--dir", help="Path to the engines folder",default='./')
    parser.add_argument("-c","--cutechess", help="Path to cutechess.",default=defaultCutechess)
    parser.add_argument("-v", "--verbosity", help="Increase output verbosity.", action="store_true")
    parser.add_argument("-t", "--time", help="Define the allocated time for engines in cutechess. The format is moves/time+increment, where moves is the number of moves per tc, time is time per tc (either seconds or minutes:seconds), and increment is time increment per move in seconds. Infinite time control can be set with tc=inf (source : cutechess doc).", default="100/0.5+0.01")
    parser.add_argument("-r", "--rounds", help="Number of rounds to play between the engines",default='500')
    parser.add_argument("-b", "--book", help="Openings book file path", default="openings.pgn")
    parser.add_argument("-o", "--output", help="Output file ", default="a.out")
    parser.add_argument("-cc", "--concurrency", help="concurrency", default="7")
    parser.add_argument("-m", "--method", help="Choose method from following : (0) Grid search, (1) Differential evolution, (2) Basinhopping.", default=0)
    
    # Add parameters arguments
    # bounds are given as a list of two parameters
    # TODO : initial guess should be optional, and there should be a default value
    parser.add_argument("-n", "--name", help="Name of the parameter", action="append", type=str)
    #parser.add_argument("--bounds", help="Lower (1) and upper (2) bound of the parameter range, minimum interval (3) and initial value (4)", action="append", default="-1,1,1,0", type=multiple)
    parser.add_argument("--bounds", help="Lower (1) and upper (2) bound of the parameter range, minimum interval (3) and initial value (4)", action="append",nargs=4,type=int)
    return parser.parse_args()