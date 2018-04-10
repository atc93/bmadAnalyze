import numpy as np
import matplotlib as mpl
mpl.use('TkAgg')
import matplotlib.pyplot as plt

#opens the 5 data files
filename = 'harp_plane_hits.dat'
input_dataT1 = np.loadtxt(filename, usecols=1, skiprows=1)
input_dataX1 = np.loadtxt(filename, usecols=3, skiprows=1)
input_dataY1 = np.loadtxt(filename, usecols=5, skiprows=1)

filename = 'harpdata2.dat'
input_dataT2 = (np.loadtxt(filename, usecols=1, skiprows=1))
input_dataX2 = (np.loadtxt(filename, usecols=3, skiprows=1))
input_dataY2 = (np.loadtxt(filename, usecols=5, skiprows=1))

filename = 'harpdata3.dat'
input_dataT3 = (np.loadtxt(filename, usecols=1, skiprows=1))
input_dataX3 = (np.loadtxt(filename, usecols=3, skiprows=1))
input_dataY3 = (np.loadtxt(filename, usecols=5, skiprows=1))

filename = 'harpdata4.dat'
input_dataT4 = (np.loadtxt(filename, usecols=1, skiprows=1))
input_dataX4 = (np.loadtxt(filename, usecols=3, skiprows=1))
input_dataY4 = (np.loadtxt(filename, usecols=5, skiprows=1))

filename = 'harpdata5.dat'
input_dataT5 = (np.loadtxt(filename, usecols=1, skiprows=1))
input_dataX5 = (np.loadtxt(filename, usecols=3, skiprows=1))
input_dataY5 = (np.loadtxt(filename, usecols=5, skiprows=1))

#compbiines the data from all 5 different data files.
input_dataT = np.concatenate((input_dataT1, input_dataT2, input_dataT3, input_dataT4, input_dataT5))
input_dataX = np.concatenate((input_dataX1, input_dataX2, input_dataX3, input_dataX4, input_dataX5))
input_dataY = np.concatenate((input_dataY1, input_dataY2, input_dataY3, input_dataY4, input_dataY5))

harp1T = []
#harp2T = []
harp3T = []
#harp4T = []

harp1X = []
#harp2X = []
harp3X = []
#harp4X = []

harp1Y = []
#harp2Y = []
harp3Y = []
#harp4Y = []

#seperates the data into the different harps. We are focussing only on Harp 1 and 3.
for i in range(len(input_dataT)):
    if (i % 4) == 0:
        harp1T.append(input_dataT[i])
 #   elif (i % 4) == 1:
  #      harp2T.append(input_dataT[i])
    elif (i % 4) == 2:
        harp3T.append(input_dataT[i])
   # elif (i % 4) == 3:
    #    harp4T.append(input_dataT[i])

for i in range(len(input_dataX)):
    if (i % 4) == 0:
        harp1X.append(input_dataX[i])
  #  elif (i % 4) == 1:
   #     harp2X.append(input_dataX[i])
    elif (i % 4) == 2:
        harp3X.append(input_dataX[i])
    #elif (i % 4) == 3:
     #   harp4X.append(input_dataX[i])
        
for i in range(len(input_dataY)):
    if (i % 4) == 0:
        harp1Y.append(input_dataY[i])
#    elif (i % 4) == 1:
 #       harp2Y.append(input_dataY[i])
    elif (i % 4) == 2:
        harp3Y.append(input_dataY[i])
  #  elif (i % 4) == 3:
   #     harp4Y.append(input_dataY[i])
   
def maxAndMin(lst, max_min):
    '''
    takes a list and replaces all elements greater than to max_min
    or less than negative max_min with max_min.
    '''
    for i in range(len(lst)):
        if lst[i] > max_min:
            lst[i] = max_min
        elif lst[i] < -max_min:
            lst[i] = -max_min

#limits the x and y to +45mm or -45mm.
maxValue = .045
maxAndMin(harp1X, maxValue)
maxAndMin(harp1Y, maxValue)
maxAndMin(harp3X, maxValue)
maxAndMin(harp3Y, maxValue)

binsize = 150*10**-9

#Harp1X

#takes the data and seperates it into a smaller amound of bins to graph with less data points
numBins1 = int(max(harp1T)/binsize) + 1
harpBin1X = []
for i in range(numBins1):
    temp = []
    for j in range(len(harp1T)):
        if binsize*i <= harp1T[j] < binsize*(i+1):
            temp.append(harp1X[j])
    harpBin1X.append(temp)

average1 = []
for i in harpBin1X:
    average1.append(sum(i)/len(i))
bins = []
for i in range(1,numBins1+1):
    bins.append(i*binsize/2)

#takes the frequency domain and the absolute forier transform squared amplitude
f = abs(np.fft.fft(average1))**2
freq = np.fft.fftfreq(len(average1), d = binsize)

#gets rid of the reflected part (the negative frequency) and also the trivial peak at 0 hz 
removeList = []
for i in range(len(freq)):
    if freq[i] < 50000:
        removeList.append(i)
f = np.delete(f,removeList)
freq = np.delete(freq,removeList)

#plots the forier transform vs the frequency domain and the max frequency
plt.plot(freq, f)
plt.title('Harp 1')
maxHz = round(freq[np.argmax(f)],2) #finds the max value of the frequency
plt.xlabel('frequency (hz) with a peak at ' + str(maxHz))
plt.ylabel('FFT X')
plt.show()

#Harp1Y
numBins1 = int(max(harp1T)/binsize) + 1
harpBin1Y = []
for i in range(numBins1):
    temp = []
    for j in range(len(harp1T)):
        if binsize*i <= harp1T[j] < binsize*(i+1):
            temp.append(harp1Y[j])
    harpBin1Y.append(temp)

average1 = []
for i in harpBin1Y:
    average1.append(sum(i)/len(i))
bins = []
for i in range(1,numBins1+1):
    bins.append(i*binsize/2)

f = abs(np.fft.fft(average1))**2
freq = np.fft.fftfreq(len(average1), d = binsize)

removeList = []
for i in range(len(freq)):
    if freq[i] < 50000:
        removeList.append(i)
f = np.delete(f,removeList)
freq = np.delete(freq,removeList)
        
plt.plot(freq, f)
plt.title('Harp 1')
maxHz = round(freq[np.argmax(f)],2)
plt.xlabel('frequency (hz) with a peak at ' + str(maxHz))
plt.ylabel('FFT Y')
plt.show()

#Harp3X
numBins3 = int(max(harp3T)/binsize) + 1
harpBin3X = []
for i in range(numBins3):
    temp = []
    for j in range(len(harp3T)):
        if binsize*i <= harp3T[j] < binsize*(i+1):
            temp.append(harp3X[j])
    harpBin3X.append(temp)

average3 = []
for i in harpBin3X:
    average3.append(sum(i)/len(i))
bins = []
for i in range(1,numBins3+1):
    bins.append(i*binsize/2)
    
f = abs(np.fft.fft(average3))**2 
freq = np.fft.fftfreq(len(average3), d = binsize)

removeList = []
for i in range(len(freq)):
    if freq[i] < 50000:
        removeList.append(i)
f = np.delete(f,removeList)
freq = np.delete(freq,removeList)

plt.plot(freq, f)
plt.title('Harp 3')  
maxHz = round(freq[np.argmax(f)],2)
plt.xlabel('frequency (hz) with a peak at ' + str(maxHz))
plt.ylabel('FFT X')
plt.show()

#Harp3Y
numBins3 = int(max(harp3T)/binsize) + 1
harpBin3Y = []
for i in range(numBins3):
    temp = []
    for j in range(len(harp3T)):
        if binsize*i <= harp3T[j] < binsize*(i+1):
            temp.append(harp3Y[j])
    harpBin3Y.append(temp)

average3 = []
for i in harpBin3Y:
    average3.append(sum(i)/len(i))
bins = []
for i in range(1,numBins3+1):
    bins.append(i*binsize/2)
    
f = abs(np.fft.fft(average3))**2
freq = np.fft.fftfreq(len(average3), d = binsize)

removeList = []
for i in range(len(freq)):
    if freq[i] < 50000:
        removeList.append(i)
f = np.delete(f,removeList)
freq = np.delete(freq,removeList)
        
plt.plot(freq, f)
plt.title('Harp 3')  
maxHz = round(freq[np.argmax(f)],2)
plt.xlabel('frequency (hz) with a peak at ' + str(maxHz))
plt.ylabel('FFT Y')
plt.show()
