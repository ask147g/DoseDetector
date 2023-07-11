import math

f = open('physics/all.csv', 'r')
fCapture = open('physics/nCapture.csv', 'r')
fInelastic = open('physics/neutronInelastic.csv', 'r')
fBoth = open('physics/both.csv', 'r')

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

### 1.1732 MeV ###
sigmaINL = (1.1736908)*1e-24 # cm2 # 0.87
sigmaNG = 0.029013628e-24 # 0.025

### 5 MeV ###
#sigmaINL = 1.71879e-24
#sigmaNG = 0.00481017e-24

### 0.5 MeV ###
#sigmaINL = 1.71879e-24
#sigmaNG = 0.00481017e-24

# source
Bq = 10000000

# product
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

ionsCapture = []
nuclidesCapture = []
lifeTimeCapture = []
for line in fCapture:
    ion, N0, tau = line.split(' ') 
    ionsCapture.append(ion)
    nuclidesCapture.append(float(N0))
    lifeTimeCapture.append(float(tau))

ionsInelastic = []
nuclidesInelastic = []
lifeTimeInelastic = []
for line in fInelastic:
    ion, N0, tau = line.split(' ') 
    ionsInelastic.append(ion)
    nuclidesInelastic.append(float(N0))
    lifeTimeInelastic.append(float(tau))

ionsBoth = []
nuclidesBoth = []
lifeTimeBoth = []
for line in fBoth:
    ion, N0, tau = line.split(' ') 
    ionsBoth.append(ion)
    nuclidesBoth.append(float(N0))
    lifeTimeBoth.append(float(tau))

sum = 0
for i in range(len(nuclides)):
    sum += nuclides[i]

sumCapture = 0
for i in range(len(nuclidesCapture)):
    sumCapture += nuclidesCapture[i]

sumInelastic = 0
for i in range(len(nuclidesInelastic)):
    sumInelastic += nuclidesInelastic[i]

sumBoth = 0
for i in range(len(nuclidesBoth)):
    sumBoth += nuclidesBoth[i]

NGReaction = 0
for i in range(len(ions)):
    if (ions[i] == "Mo99"):
        NGReaction += nuclides[i]

NGReactionCapture = 0
for i in range(len(ionsCapture)):
    if (ionsCapture[i] == "Mo99"):
        NGReactionCapture += nuclidesCapture[i]

NGReactionInelastic = 0
for i in range(len(ionsInelastic)):
    if (ionsInelastic[i] == "Mo99"):
        NGReactionInelastic += nuclidesInelastic[i]

NGReactionBoth = 0
for i in range(len(ionsBoth)):
    if (ionsBoth[i] == "Mo99"):
        NGReactionBoth += nuclidesBoth[i]

fluence = Bq/area*math.exp(-(sigmaINL+sigmaNG)*N*V*r)
nuclei = (sigmaINL+sigmaNG)*N*V*fluence

fluenceINL = Bq/area*math.exp(-(sigmaINL)*N*V*r)
nucleiINL = (sigmaINL)*N*V*fluenceINL

fluenceNG = Bq/area*math.exp(-(sigmaNG)*N*V*r)
nucleiNG = (sigmaNG)*N*V*fluenceNG

#print("GEANT4")
#print(f"ALL: {sum};\n without nCapture: {sumCapture};\n without neutronInelastic: {sumInelastic};\n without both: {sumBoth}.\n")
#print("GEANT4 Only Mo99")
#print(f"ALL: {NGReaction};\n without nCapture: {NGReactionCapture};\n without neutronInelastic: {NGReactionInelastic};\n without both: {NGReactionBoth}.\n")
#
#print("CALCULATION")
#print(f"ALL: {nuclei};\n without nCapture: {nucleiINL};\n without neutronInelastic: {nucleiNG}.\n")
#
#print("RATIO GEANT4/calc ALL:")
#print(f"ALL: {sum/nuclei};\n without nCapture: {sumCapture/nuclei};\n without neutronInelastic: {sumInelastic/nuclei};\n without both: {sumBoth/nuclei}.\n")
#print("RATIO GEANT4/calc without nCapture:")
#print(f"ALL: {sum/nucleiINL};\n without nCapture: {sumCapture/nucleiINL};\n without neutronInelastic: {sumInelastic/nucleiINL};\n without both: {sumBoth/nucleiINL}.\n")
#print("RATIO GEANT4/calc without neutronInelastic:")
#print(f"ALL: {sum/nucleiNG};\n without nCapture: {sumCapture/nucleiNG};\n without neutronInelastic: {sumInelastic/nucleiNG};\n without both: {sumBoth/nucleiNG}.\n")
#
#print("RATIO GEANT4 Only Mo99/calc ALL:")
#print(f"ALL: {NGReaction/nuclei};\n without nCapture: {NGReactionCapture/nuclei};\n without neutronInelastic: {NGReactionInelastic/nuclei};\n without both: {NGReactionBoth/nuclei}.\n")
#print("RATIO GEANT4 Only Mo99/calc without nCapture:")
#print(f"ALL: {NGReaction/nucleiINL};\n without nCapture: {NGReactionCapture/nucleiINL};\n without neutronInelastic: {NGReactionInelastic/nucleiINL};\n without both: {NGReactionBoth/nucleiINL}.\n")
#print("RATIO GEANT4 Only Mo99/calc without neutronInelastic:")
#print(f"ALL: {NGReaction/nucleiNG};\n without nCapture: {NGReactionCapture/nucleiNG};\n without neutronInelastic: {NGReactionInelastic/nucleiNG};\n without both: {NGReactionBoth/nucleiNG}.\n")


#print("GEANT4")
#print(f"ALL: {sum};\n without nCapture: {sumCapture};\n without neutronInelastic: {sumInelastic};\n without both: {sumBoth}.\n")
#print("GEANT4 Only Mo99")
#print(f"ALL: {NGReaction};\n without nCapture: {NGReactionCapture};\n without neutronInelastic: {NGReactionInelastic};\n without both: {NGReactionBoth}.\n")
#
#print("CALCULATION")
#print(f"ALL: {nuclei};\n without nCapture: {nucleiINL};\n without neutronInelastic: {nucleiNG}.\n")
#
#print("RATIO GEANT4/Calculation:")
#print(f"ALL: {sum/nuclei};\n without nCapture: {sumCapture/nucleiINL};\n without neutronInelastic: {sumInelastic/nucleiNG}.\n")
#
#print("RATIO GEANT4 Only Mo99/Calculation:")
#print(f"ALL: {NGReaction/nuclei};\n without nCapture: {NGReactionCapture/nucleiINL};\n without neutronInelastic: {NGReactionInelastic/nucleiNG}.\n")

print("GEANT4")
print(f"ALL: {sum};\n neutronInelastic: {sumCapture};\n nCapture: {sumInelastic};\n without both: {sumBoth}.\n")
print("GEANT4 Only Mo99")
print(f"ALL: {NGReaction};\n neutronInelastic: {NGReactionCapture};\n nCapture: {NGReactionInelastic};\n without both: {NGReactionBoth}.\n")

print("CALCULATION")
print(f"ALL: {nuclei};\n neutronInelastic: {nucleiINL};\n nCapture: {nucleiNG}.\n")

print("RATIO GEANT4/Calculation:")
print(f"ALL: {sum/nuclei};\n neutronInelastic: {sumCapture/nucleiINL};\n nCapture: {sumInelastic/nucleiNG}.\n")

print("RATIO GEANT4 Only Mo99/Calculation:")
print(f"ALL: {NGReaction/nuclei};\n neutronInelastic: {NGReactionCapture/nucleiINL};\n nCapture: {NGReactionInelastic/nucleiNG}.\n")
