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
#        92       94      95      96       97     98      100
rate = [0.1586, 0.0912, 0.1570, 0.1650, 0.0945, 0.2375, 0.0962]

# reaction
#    Mo99(N,INL)Mo99     Mo98(N,G)Mo99
sigma = (1.1736908)*1e-24 # cm2
#           92       94      95      96       97     98      100
# 1.1732 MeV
sigmaINL = [0, 0.8042555, 1.4472322, 0.967497, ]
sigmaNG = [0.036571108, 0.0357026, 0.05105354, 0.029366381, ]

# 5 MeV
#sigmaINL = [1.69765, 1.82084, 2.01126, 1.82474, ]
#sigmaNG = [0.006837, 0.00756734, 0.00338892, 0.00718594, ]

# 0.5 MeV
#sigmaINL = [0, 0, 0.637726, 0, ]
#sigmaNG = [0.029318715, 0.05312822, 0.0874912, 0.04775087, ]

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