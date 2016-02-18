# -*- coding: utf-8 -*-
"""
Created on Sun Nov  8 21:16:15 2015

@author: navid
"""

from scipy.optimize import differential_evolution
from scipy.optimize import basinhopping
from tuner import *
from deepovFunction import *
from interface import *
import settings

elo = -10000
values = []

# TODO : create a function to save result of each step in the algorithms (callable func in scipy.optimize)

def opt_differential_evolution(parametersList):
    # Maximul of iterations of the algorithm
    max_iter=10
    # Set the bounds of each parameter
    bounds=list()
    for i in range(0,len(parametersList)):
        bounds.append((parametersList[i][1],parametersList[i][2]))
    # TODO : change the criterium of convergence 
    scipy_res=differential_evolution(deepov_func,bounds,args=parametersList,maxiter=max_iter,disp=True,polish=False)
    return scipy_res
    
def opt_basinhopping(parametersList):
    # Number of iterations of the algorithm
    n_iter=10
    # Set the bounds of each parameter
    bounds=list()
    for i in range(0,len(parametersList)):
        bounds.append((parametersList[i][1],parametersList[i][2]))
        
    # Set the dictionary of additional options
    args={'bounds':bounds,'args':parametersList}
    
    # Find the initial guess
    x0=[parametersList[i][4] for i in range(0,len(parametersList))]
    print('Initial guess')
    print(x0)
    scipy_res=basinhopping(deepov_func,x0,niter=n_iter,T=50,stepsize=10, minimizer_kwargs=args,niter_success=3,disp=True)
    return scipy_res

def opt_gridSearch(parametersList):
    """ Does a simple grid search over the parameter space and returns the elo win and the best values in a dictionnary"""
        
    global elo
    global values

    values = list() # Stores the results
    n = len(parametersList) # dimension of the problem = number of parameters
    
    # Iterates over the the parameters to initialize values list
    # The parameter temporary value does not need an initial guess in grid search and is set as the lower bound
    for i in range(0,n):
        parametersList[i][4] = parametersList[i][1]
        values.append(parametersList[i][1])
        
        # Initialize the lists in the dataset (a list of n lists)
        settings.dataset.append([])
                
    # Add one dimension to store the corresponding elo
    settings.dataset.append([])

    # Goes over the paramter space and launch cutechess at each point
    recursive_iterate(parametersList,0,n)
    
    return values,elo
    
def recursive_iterate(parametersList,i,max_dim):
    global elo
    global values

    """ Recursive iteration  along the dimension current_dim """
    # At the leaf of the tree
    if (i == max_dim-1):
        while ( parametersList[i][4] <= parametersList[i][2] ):
            # step 1 : evaluate the score at current leaf
            parameters = setParam(parametersList)
            command = generateCommand(parameters)
            score = evaluate(command)
            print("score {}".format(score))
            print("For values: {}".format([parametersList[j][4] for j in range(0,max_dim)]  ))
            
            # Store results in the dataset
            for i in range(0,max_dim):            
                settings.dataset[i].append(parametersList[i][4])
                
            # Appends the score in the nth list
            settings.dataset[max_dim].append(score)

            if score > elo:
                values = [parametersList[j][4] for j in range(0,max_dim)]          
                elo = score
                print("NEW ELO: {}".format(elo))
                print("For values: {}".format(values))
                print("")
                
            # step 2 : at end of evaluation, increment current leave
            parametersList[i][4] += parametersList[i][3]

        # step 3 : at end of loop, reinitialize the leaf at lower bound
        parametersList[i][4] = parametersList[i][1]
        
    else:
        while ( parametersList[i][4] <= parametersList[i][2] ):
            # step 1b : if not at leaf, recursive call at dim i+1
            recursive_iterate(parametersList,i+1,max_dim,values,elo)
            # step 2b : at end of evaluation, increment current dim
            parametersList[i][4] += parametersList[i][3]

         
        # step 3b : at end of loop, reinitialize the dim at lower bound and i++
        parametersList[i][4] = parametersList[i][1]
            