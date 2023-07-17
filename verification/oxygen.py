import math

f = open('activity.csv', 'r')

# consts
AvogadroNumber = 6.02214082e23

# target
density = 0.00142897 # g/cm3
mu = 16 # g/mol
x, y, z = [1, 1, 1] # cm
area = z*y

# reaction
# ENDF/B-VIII.0
sigma = (3.8581576)*1e-24
#sigma = 2.75556e-24
# source
Bq = 10000000

# product
V = x*y*z
N = density/mu*AvogadroNumber # cm-3

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

fluence = Bq/area
nuclei = (sigma)*N*V*fluence

lost = fluence - fluence*math.exp(-sigma*N*x)

print(f"Geant4: {sum}; Calculate: {nuclei}. Lost: {lost}\n")
print(f"Difference g4/calc: {sum/nuclei}")