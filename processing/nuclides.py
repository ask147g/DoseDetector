import math

f = open('activity.csv', 'r')

# consts
AvogadroNumber = 6.02214082e23

# target
density = 10.22 # g/cm3
mu = 98 # g/mol
x, y, z = [1, 1, 1] # cm
area = z*y
r = 0 # cm

# reaction
# TENDL-2021
#    Mo99(N,INL)Mo99     Mo98(N,G)Mo99
#    neutronInelastic    nCapture
#sigma = (2.1940424+0.014468811)*1e-24 # cm2
#sigma = 0.014468811e-24
# ENDF/B-VIII.0
#sigma = (1.8429065+0.029013628)*1e-24 # cm2
#sigma = (1.1736908+0.029013628)*1e-24 # cm2 # INL for Mo98
#sigma = (0.86113628)*1e-24 # cm2
sigma = (1.1736908)*1e-24 # cm2


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

fluence = Bq/area*math.exp(-sigma*N*V*r)
nuclei = sigma*N*V*fluence

print(f"Geant4: {sum}; Calculate: {nuclei}.\n")
print(f"Difference g4/calc: {sum/nuclei}")