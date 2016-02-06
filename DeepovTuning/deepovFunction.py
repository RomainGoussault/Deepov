# -*- coding: utf-8 -*-
"""
Created on Sun Nov  8 21:32:42 2015

@author: navid
"""

from tuner import runCutechess
from interface import generateCommand
import re


# TODO : split the command to use several processors ?

def evaluate(command):
    """ Evaluate the score after changing the option value and returns the score of the engine. """
    s = runCutechess(command) # Get the cutechess output
    index = s.decode('UTF-8').find('ELO')
    s = s[index:-1] # Suppress everything before 'ELO' 
    
    score = int(re.search(r'[-+]?\d+', s.decode('UTF-8')).group())

    return score
    
    
def deepov_func(x,*args):
    """Evaluation function compliant with a scipy.optimize input function."""
    # x is the list of parameters, *args are optional fixed parameters
    global paramList
    
    parameters=''
    for i in range(0,len(x)):
        parameters +=' option.{0}={1} '.format(paramList[i][0],x[i])
    command=generateCommand(parameters)
    score=evaluate(command)
    return -score