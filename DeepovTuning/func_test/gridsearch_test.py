# -*- coding: utf-8 -*-
"""
Created on Sat Jan  9 08:08:00 2016

@author: navid
"""

## TODO : implement in a real testing framework

            
def recursivity_test2(parametersList,count,max_dim):
    """ Recursive iteration  along the dimension current_dim """
 # dimension of the problem = number of parameters
    # Initial dimension
    print('Hi, count is = ' + str(count))
    if (count == max_dim-1):
        while ( parametersList[count][4] <= parametersList[count][2] ):
            # step 1 : evaluate the score at current leave
            print('Current leave =' + str([parametersList[j][4] for j in range(0,len(parametersList))]))            
            # step 2 : at end of evaluation, increment current leave
            parametersList[count][4] += parametersList[count][3]
        # step 3 : at end of loop, reinitialize the dim at lower bound and i++
        parametersList[count][4] = parametersList[count][1]
    
    else:
        #for i in range(0,count+1):
        while ( parametersList[count][4] <= parametersList[count][2] ):
                # step 2b : incrementation of current dim
                recursivity_test2(parametersList,count+1,max_dim)
                parametersList[count][4] += parametersList[count][3]

        # step 3 : at end of loop, reinitialize the dim at lower bound and i++
        parametersList[count][4] = parametersList[count][1]
        print("I'm at i = " + str(count))
        

parametersList = []
parametersList.append(['name',0,1,1,0])
parametersList.append(['name2',1,3,1,1])
parametersList.append(['name3',1,4,2,1])
max_dim = len(parametersList)
print("number of dimensions is " + str(max_dim))
print(parametersList)
recursivity_test2(parametersList,0,max_dim)

