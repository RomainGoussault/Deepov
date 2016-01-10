# -*- coding: utf-8 -*-
"""
Created on Sun Jan 10 01:19:41 2016

@author: navid
"""

from optRoutines import *

class TestAlgos:

    def setup_class(self):
        """ Defines the variables needed to test the module """
    
        self.param_list1 = [['param1',0,0,0,0]]
        
        self.param_list2 = []
        self.param_list2.append(['param1',0,1,1,0])
        self.param_list2.append(['param2',1,3,1,1])
        self.param_list2.append(['param3',1,4,2,1])
    