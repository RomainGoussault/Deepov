# -*- coding: utf-8 -*-
"""
Created on Sun Nov  8 21:32:42 2015

@author: navid
"""

from tuner import runCutechess
import re

# TODO : split the command to use several processors ?

def evaluate(command):
    """ Evaluate the score after changing the option value and returns the score of the engine. """
    s = runCutechess(command) # Get the cutechess output
    index = s.decode('UTF-8').find('ELO')
    s = s[index:-1] # Suppress everything before 'ELO' 
    score = int(re.search(r'\d+', s.decode('UTF-8')).group())

    return score