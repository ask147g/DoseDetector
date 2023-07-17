import math

material = "natural"
energy = ""

f = open('natural/all.csv', 'r')
fINL = open('natural/nCapture.csv', 'r')
fNG = open('natural/neutronInelastic.csv', 'r')

# consts
AvogadroNumber = 6.02214082e23

# target
density = 10.22 # g/cm3
mu = 98 # g/mol
x, y, z = [1, 1, 1] # cm
area = z*y
r = 0 # cm
#        92       94      95      96       97     98      100
isotope = [92, 94, 95, 96, 97, 98, 100]
rate = [0.1586, 0.0912, 0.1570, 0.1650, 0.0945, 0.2375, 0.0962]

# reaction
#    Mo98(N,INL)Mo99*     Mo98(N,G)Mo99
#           92       94      95      96       97     98      100
# 1.1732 MeV
sigmaINL = [0, 0.8042555, 1.4472322, 0.967497, 1.6932966, 1.1736908, 1.195025]
sigmaNG = [0.036571108, 0.0357026, 0.05105354, 0.029366381, 0.045161232, 0.029013628, 0.012686701]

# 5 MeV
#sigmaINL = [1.69765, 1.82084, 2.01126, 1.82474, 1.83319, 1.71879, 1.8755]
#sigmaNG = [0.006837, 0.00756734, 0.00338892, 0.00718594, 0.00291436, 0.00481017, 0.00218341]

# 0.5 MeV
#sigmaINL = [0, 0, 0.637726, 0, 0.0491739, 0, 0]
#sigmaNG = [0.029318715, 0.05312822, 0.0874912, 0.04775087, 0.0919547, 0.04849691, 0.0316967]

# source
Bq = 10000000

# product
halfLife = 65.976*3600 # sec

V = x*y*z

# GEANT4
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

G4Isotopes = []
for i in range(len(isotope)):
    G4Isotopes.append(0)
    for k in range(len(ions)):
        if ("Mo"+str(isotope[i]+1) in ions[k]):
            G4Isotopes[i] += nuclides[k]

# Inelastic
ionsINL = []
nuclidesINL = []
lifeTimeINL = []
for line in fINL:
    ion, N0, tau = line.split(' ') 
    ionsINL.append(ion)
    nuclidesINL.append(float(N0))
    lifeTimeINL.append(float(tau))

sumINL = 0
for i in range(len(nuclidesINL)):
    sumINL += nuclidesINL[i]

G4IsotopesINL = []
for i in range(len(isotope)):
    G4IsotopesINL.append(0)
    for k in range(len(ionsINL)):
        if ("Mo"+str(isotope[i]+1) in ionsINL[k]):
            G4IsotopesINL[i] += nuclidesINL[k]

# Inelastic
ionsNG = []
nuclidesNG = []
lifeTimeNG = []
for line in fNG:
    ion, N0, tau = line.split(' ') 
    ionsNG.append(ion)
    nuclidesNG.append(float(N0))
    lifeTimeNG.append(float(tau))

sumNG = 0
for i in range(len(nuclidesNG)):
    sumNG += nuclidesNG[i]

G4IsotopesNG = []
for i in range(len(isotope)):
    G4IsotopesNG.append(0)
    for k in range(len(ionsNG)):
        if ("Mo"+str(isotope[i]+1) in ionsNG[k]):
            G4IsotopesNG[i] += nuclidesNG[k]

# CALCULATION
fluence = Bq/area
N = []
nuclei = []
nucleiINL = []
nucleiNG = []
sum_nuclei = 0
sum_nucleiINL = 0
sum_nucleiNG = 0
for i in range(len(rate)):
    N.append(V*density/isotope[i]*AvogadroNumber*rate[i])
    nuclei.append((sigmaINL[i]+sigmaNG[i])*1e-24*N[i]*fluence)
    nucleiINL.append((sigmaINL[i])*1e-24*N[i]*fluence)
    nucleiNG.append((sigmaNG[i])*1e-24*N[i]*fluence)
    sum_nuclei += nuclei[i]
    sum_nucleiINL += nucleiINL[i]
    sum_nucleiNG += nucleiNG[i]

for i in range(len(isotope)):
    print(f"Mo{isotope[i]}")
    if (nuclei[i] == 0):
        print(f"ALL: {G4Isotopes[i]} {nuclei[i]} -")
    else:
        print(f"ALL: {G4Isotopes[i]} {nuclei[i]} {G4Isotopes[i]/nuclei[i]}")
    if (nucleiINL[i] == 0):
        print(f"INL: {G4IsotopesINL[i]} {nucleiINL[i]} -")
    else:
        print(f"INL: {G4IsotopesINL[i]} {nucleiINL[i]} {G4IsotopesINL[i]/nucleiINL[i]}")
    if (nucleiNG[i] == 0):
        print(f"NG: {G4IsotopesNG[i]} {nucleiNG[i]} -")
    else:
        print(f"NG: {G4IsotopesNG[i]} {nucleiNG[i]} {G4IsotopesNG[i]/nucleiNG[i]}")

print("TOTAL:")
print(f"ALL: {sum} {sum_nuclei} {sum/sum_nuclei}")
print(f"INL: {sumINL} {sum_nucleiINL} {sumINL/sum_nucleiINL}")
print(f"NG: {sumNG} {sum_nucleiNG} {sumNG/sum_nucleiNG}")