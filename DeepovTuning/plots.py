# -*- coding: utf-8 -*-
"""
Created on Fri Feb  5 23:07:48 2016

@author: navid
"""

import settings
import matplotlib.pyplot as plt

def scatter_plot(n):
    """ 2D scatter plot of the evaluated elo (y) vs. the nth option value (x)"""
    plt.scatter(settings.dataset[n],settings.dataset[-1])
    plt.show()