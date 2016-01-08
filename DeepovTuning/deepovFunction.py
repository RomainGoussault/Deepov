# -*- coding: utf-8 -*-
"""
Created on Sun Nov  8 21:32:42 2015

@author: navid
"""

from tuner import runCutechess

# TODO : split the command to use several processors

def evaluate(command):
    """ Evaluate the score after changing the option value and returns the score of the engine. """
    s = runCutechess(command) # Get the cutechess output
    index = s.find('ELO')
    s = s[index:-1] # Suppress everything before 'ELO'
    numbers = sum(c.isdigit() for c in s) # Count how many numbers in the score
    index=s.find("\n")
    # Get the score
    score = s[index-numbers-1:index]
    score = int(score)
    return score