# Verification Induced Activity in Pb
import matplotlib.pyplot as plt
import numpy as np
import math

sigma208 = 0.0151504e-24 # cm2
halfLife = 500e-9
AvogadroNumber = 6.022045e23

density = 11.35 # g/cm3
mu = 204

r = 1.5 # cm
A = 100000 # Bq
a = 1 # cm
#fluence = A/a**2
fluence = 429.428*1000

N = density*a**3/mu*AvogadroNumber*1.4/100

Activity = N*fluence*sigma208
print(Activity)