# -*- coding: utf-8 -*-
"""
Created on Sun Nov  8 21:16:15 2015

@author: navid
"""

import scipy.optimize
from tuner import *
from deepovFunction import *
from interface import *

def opt_BasinHopping(init_guess,niter):
#    scipy.optimize.basinhopping(evaluate,init_guess,niter,T=100.,)
    return value

def opt_gridSearch(optionMap,dx=[1]):
    # TODO : use numpy arrays instead of lists to optimize speed
    """ Does a simple grid search over the parameter space and returns the elo win and the best values in a dictionnary"""
    elo = -10000 # Stores the final score for best case
    values = dict() # Stores the results
    dim = len(optionMap) # dimension of the problem = number of parameters
    ind = list() # list of indices of size dim
    for i in range(0,dim):
        ind.append(0)
    
    # Iterates over the name of the parameters to initialize values list
    # The parameter temporary value does not need an initial guess in grid search and is set as the lower bound
    for key in optionMap.keys:
        optionMap[key][1] = optionMap[key][2]
        values[key] = optionMap[key][2]
        
    
        

    # Goes over the paramter space and launch cutechess at each point : TODO
    for key in optionMap.keys:
        while ( optionMap[key][1] < optionMap[key][3]-dx ):
            optionMap[key][1] += dx
            parameters = engineConfig(pmap)
            command = generateCommand(parameters)
            score = evaluate(command)
            if score > elo:
                value = pmap[name]            
                elo = score
    
    return value,elo
    
 #   def visit(pmap,current_key):
  #          for i in range(x0,x1):
        
        