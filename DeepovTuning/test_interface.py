# -*- coding: utf-8 -*-
"""
Created on Sun Jan 10 01:19:18 2016

@author: navid
"""

from interface import *

class TestInterface:

    def setup_class(self):
        """ Defines the variables needed to test the module """
    
        self.param_list1 = [['param1',0,0,0,0]]
        
        self.param_list2 = []
        self.param_list2.append(['param1',0,1,1,0])
        self.param_list2.append(['param2',1,3,1,1])
        self.param_list2.append(['param3',1,4,2,1])
    
    
    def test_setParms(self):
        assert setParam(self.param_list1) == 'option.param1=0 '
        assert setParam(self.param_list2) == 'option.param1=0 option.param2=1 option.param3=1 '
    