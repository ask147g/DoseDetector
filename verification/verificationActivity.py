# Verification Induced Activity in Pb
import matplotlib.pyplot as plt
import numpy as np
import math

sigma208 = 0.00107358e-24 # cm2
halfLife = 65.976*3600 # sec
AvogadroNumber = 6.022045e23

density = 10.22 # g/cm3
mu = 98

a = 1 # cm
fluence = 6000*1000
N = density*a**3/mu*AvogadroNumber

Activity = N*fluence*sigma208*math.exp(-math.log(2)/halfLife)
print(Activity)