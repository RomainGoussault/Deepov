#! /usr/bin/python3.4
#-*- coding: utf-8 -*-

import sys
import subprocess
from interface import *
from optRoutines import *
import settings
import plots



def main(argv):
    settings.init()          # Call only once
    print("Start Deepov tuning v0.2")
    #TODO make a useful main function
    # Define global variables that will contain the cutechess configuration    

    if argv is None:
        argv = sys.argv[1:]

    args=createParser()
#	print("List of arguments\n")
#	print(args)
	

     
    # Store the run configuration
    settings.main_command,settings.main_config=cutechessConfig(args)
    
#    if args.verbosity:
#        print('Sending command to cutechess :')
#        print(settings.main_command+settings.main_config)
#        print('\n')
    
    # No input parameters ( for test purpose )
    if args.name is None:
        if args.verbosity:
            print("#WARNING : No input parameters.")    

        command = settings.main_command+settings.main_config
        runCutechess(command)        
        return 0        
        
    paramList=initParameters(args)
    if args.verbosity:
        print("List of parameters : ")
        print(paramList)

    # Choose method
    print("Initial empty dataset")
    print(settings.dataset)

    # Execute method
    print(settings.main_command+settings.main_config)
    
    # Ensure method is an interger
    args.method = int(args.method)
    
    if (args.method==0):    # brute force (opt_gridSearch)
        best,elo=opt_gridSearch(paramList)
        # Display resultes
        print("Best set of values is {}".format(best))
        print("Elo improvement is {}".format(elo))
        # Display the stored dataset
        print(settings.dataset)
        plots.scatter_plot(0)
    elif (args.method==1):
        scipy_res=opt_differential_evolution(paramList)
        print(scipy_res)
    elif (args.method==2):
        scipy_res=opt_basinhopping(paramList)
        print(scipy_res)
    else:
        print("#WARNING> Not a valid optimization method.")
        
#    if args.verbosity:
#        print(results) ???

    return 0
    

def setOption(name,value):
	value=str(value)
	option = "setoption {} value {}".format(name,value)
	return option

def runCutechess(command):
    
    print("runCutechess with command :")
    print(command)

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


