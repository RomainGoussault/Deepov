#! /usr/bin/python3.4
#-*- coding: utf-8 -*-

import sys
import subprocess
from interface import *

def main(argv):
    print("Start Deepov tuning v0.1")
    # Define global variables that will contain the cutechess configuration    
    main_command = ''
    main_config = ''


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


