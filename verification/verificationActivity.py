# Verification Induced Activity in Pb
import matplotlib.pyplot as plt
import numpy as np
import math

# geant4
geant4 = [0.238078, 0.1661, 0.113452, 0.0766683, 0.0520806, 0.0352383, 0.0239567, 0.0161763, 0.0107753, 0.00739482, 0.00496914, 0.00351794, 0.00214666, 0.00146803, 0.00100532, 0.000696857, 0.000472517, 0.000286034, 0.00021733, 0.000121985]

# consts
AvogadroNumber = 0.029013628e23

# target
density = 10.22 # g/cm3
mu = 98 # g/mol
a, b, c = [1, 1, 20] # cm
area = a*b
r = [0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 16.5, 17.5, 18.5, 19.5] # cm

# source
Bq = 10000000
time = 1

# reaction
#sigma = 6.28227e-24 # cm2
sigma = (1.1736908+0.029013628)*1e-24 # cm2 total for N
coolTime = 1 # sec

# product
halfLife = 65.976*3600 # sec

N = density/mu*AvogadroNumber # cm-3
V = a*b*c

fluence = []
activity = []
for i in range(len(r)):
    fluence.append(Bq/area/time*math.exp(-sigma*N*V*i*r[i]))
    activity.append(N*sigma*fluence[i]*math.log(2)/halfLife*math.exp(-math.log(2)/halfLife*coolTime))

print(fluence)
fig,ax=plt.subplots(1,1)
ax.set_xlabel('r, (cm)')
ax.set_ylabel('A, Bq')
ax.set_title('N = 10000000 particles')
plt.plot(r, activity, color='blue', label='calculation')
plt.plot(r, geant4, color='red', label='geant4')
plt.legend(loc="upper right")
plt.grid()
plt.show()