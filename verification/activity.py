f = open('activity.csv', 'r')

ions = []
nuclides = []
lifeTime = []
for line in f:
    ion, N0, tau = line.split(' ') 
    ions.append(ions, ion)
    nuclides.append(nuclides, float(N0))
    lifeTime.append(lifeTime, float(tau))

