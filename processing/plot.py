import matplotlib.pyplot as plt
import numpy as np

detNum = [20, 20, 20]
detSize = [1, 1, 1] # cm
f = open('output.csv', 'r')

doseRate = np.array([])
for line in f:
    doseRate = np.append(doseRate, line.rstrip())

xValue = np.array([])
yValue = np.array([])
zValue = np.array([])
for x in range(detNum[0]):
    for y in range(detNum[1]):
        for z in range(detNum[2]):
            xValue = np.append(xValue, x*detSize[0])
            yValue = np.append(yValue, y*detSize[1]+y/2*detSize[1])
            zValue = np.append(zValue, z*detSize[2]+z/2*detSize[2])
print(zValue[0:20])
dose = np.reshape(doseRate[0:400], (-1, 20))
#dose = np.array([20][20])
#for i in range(20):
#    dose[i] = np.append(dose[i], doseRate[0:19])
#print(dose[15][0])
fig,ax=plt.subplots(1,1)
cp = ax.contourf(np.array(zValue[0:20], dtype=float), np.array(yValue[0:20], dtype=float), np.array(dose, dtype=float))
fig.colorbar(cp) # Add a colorbar to a plot
plt.show()
#for x in range(detNum[0]):

#for x in range(20):
#    for y in range(20):
#        for z in range(20):

#            print(x)

#xlist = np.linspace(-3.0, 3.0, 100)
#ylist = np.linspace(-3.0, 3.0, 100)
#X, Y = np.meshgrid(xlist, ylist)
#Z = np.sqrt(X**2 + Y**2)
#fig,ax=plt.subplots(1,1)
#cp = ax.contourf(X, Y, Z)
#fig.colorbar(cp) # Add a colorbar to a plot
#ax.set_title('Filled Contours Plot')
##ax.set_xlabel('x (cm)')
#ax.set_ylabel('y (cm)')
#plt.show()