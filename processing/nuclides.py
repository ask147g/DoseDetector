import math

f = open('HP/endf.csv', 'r')

# consts
AvogadroNumber = 6.02214082e23

# target
density = 10.22 # g/cm3
mu = 98 # g/mol
x, y, z = [1, 1, 1] # cm
area = z*y
r = 0 # cm

# reaction
#    Mo98(N,INL)Mo99     Mo98(N,G)Mo99
# ENDF/B-VIII.0
# 98
sigmaINL = (1.1736908)*1e-24 # cm2
sigmaNG = (0.028616352)*1e-24

# 100 
#sigmaINL = (0)*1e-24 # cm2
#sigmaNG = (0.0316967)*1e-24

# source
Bq = 10000000

# product
halfLife = 65.976*3600 # sec

N = density/mu*AvogadroNumber # cm-3
V = x*y*z

ions = []
nuclides = []
lifeTime = []
for line in f:
    ion, N0, tau = line.split(' ') 
    ions.append(ion)
    nuclides.append(float(N0))
    lifeTime.append(float(tau))

sum = 0
for i in range(len(nuclides)):
    sum += nuclides[i]

NGReaction = 0
for i in range(len(ions)):
    if (ions[i] == "Mo99"):
        NGReaction += nuclides[i]

fluence = Bq/area
nuclei = (sigmaNG)*N*V*fluence

print(f"Geant4: {sum}; Calculate: {nuclei}.\n")
print(f"Difference g4/calc: {sum/nuclei}")