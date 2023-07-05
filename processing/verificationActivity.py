# Verification Induced Activity in Pb
import matplotlib.pyplot as plt
import numpy as np
import math

sigma208 = 0.390563e-24 # cm2
halfLife = 500e-9
AvogadroNumber = 6.022045e23

density = 11.35 # g/cm3
mu = 208

r = 1.5 # cm
A = 100000 # Bq
a = 1 # cm
#fluence = A/a**2
fluence = 24*1000

N = density*a**3/mu*AvogadroNumber

Activity = N*fluence*sigma208*(1-math.exp(-math.log(2)/halfLife*1))
print(Activity)