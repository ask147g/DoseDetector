# Verification with Gamma const of Co60 in air
import matplotlib.pyplot as plt
import numpy as np

# CONSTS
activity = 1000000 # Bq

gamma1 = 84.6 # aGy m2 / (s Bq)
gamma2 = 12.85 # R cm2 / (h mKu) 

mKu = 2.7027*pow(10, -8)
m = 0.01
sec = 3600
Sv = 0.01

atto = pow(10, -18)
pico = pow(10, -9)

# nSv
geant4 = [35.20411, 8.868605, 3.860845, 2.191883, 1.42956, 0.3570066, 0.156568, 0.08921372, 0.05447549, 0.03968703, 0.02808561, 0.02090691]
error = [0.146379973205202, 0.081948871221295, 0.0656616264140124, 0.0607429754603591, 0.0427934969099019, 0.0230300439001849, 0.0147080785662544, 0.00679606867106107, 0.0105765806475597, 0.00583276695746634, 0.00622979437139693, 0.00481610095904007]
# Gamma 1 and 2
r = [5, 10, 15, 20, 25, 50, 75, 100, 125, 150, 175, 200] # cm

doseG1 = []
doseG2 = []
for i in range(len(r)):
    doseG1.append(activity*gamma1/(r[i]*m)**2*atto/pico)
    doseG2.append(activity*mKu*gamma2/r[i]**2/sec*Sv/pico)

fig,ax=plt.subplots(1,1)
ax.set_xlabel('r, (cm)')
ax.set_ylabel('H, (pSv/sec)')
ax.set_title('A = 1000000 Bq')
plt.errorbar(r, geant4, yerr=error, fmt='ko', label='geant4')
plt.plot(r, doseG1, color='blue', label='Г = 84.6 aGy m2 / (s Bq)')
plt.plot(r, doseG2, color='red', label='Г = 12.85 R cm2 / (h mKu) ')
ax.set_yscale('log')
plt.legend(loc="upper right")
plt.grid()
plt.show()