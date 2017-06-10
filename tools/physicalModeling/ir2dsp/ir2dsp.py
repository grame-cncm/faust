#!/usr/bin/env python
# id2dsp.py
# Copyright Pierre-Amaury Grumiaux, Pierre Jouvelot, Emilio Jesus Gallego Arias,
# and Romain Michon

from __future__ import division
import math
import numpy as np
import matplotlib.pyplot as plt
from sys import argv
import subprocess
from scipy.io.wavfile import read
import peakutils
import peakutils.plot as pkplt
import operator
import argparse

# Help for use of the script
parser = argparse.ArgumentParser(description = "IR2dsp.py is a python script that generates a .dsp file from an impulse response file (a .wav file).The impulse response is analyzed in order to rebuild the sound of the vibration of the object based on this impulse response.", epilog = "See http://faust.grame.fr/images/faust-tutorial2.pdf for more information about Faust")
parser.add_argument("soundFile", type = str, help = "Path of the sound file")
parser.add_argument("modelName", help = "The name of the model created in the .dsp file")
parser.add_argument("peakThreshold", help = "Minimum value of peaks in dB (between -infinity and 0)")
parser.add_argument("peakDistance", help = "Minimum distance between two peaks in Hertz")
ars = parser.parse_args ()
# Arguments
script, soundFile, modelName, peakThreshold, peakDistance = argv

# Reading file
(fs, x) = read(soundFile)
# Normalizing sound
x = x/max(x)

# FFT
X = np.abs(np.fft.fft(x))
X = X/(max(X))
# computing corresponding frequencies
time_step = 1/fs
freqs = np.fft.fftfreq(x.size, time_step)
idx = np.argsort(freqs)

# plot for debug
# plt.plot(freqs[idx],20*np.log(X[idx]))
# plt.show()

# detecting peaks
threshold = math.pow(10, float(peakThreshold)/20) # from dB to X unit
distance = int(peakDistance)/(fs/x.size)
indexes = peakutils.indexes(X[idx], thres = threshold, min_dist = distance)

# Storing frequencies and modes for each bp filters
peaksFreq = []
peaksGains = []
nbOfPeaks = 0
for i in indexes :
	if freqs[idx][i] > 0:
		peaksFreq.append(freqs[idx][i])
		peaksGains.append(X[idx][i])
		nbOfPeaks += 1
peaksGains = peaksGains/(max(peaksGains))

#Computing t60 values
peakst60 = []
for i in range(0, nbOfPeaks) :
	offset = pow(10, -3/20) # conversion of -3 dB in X unit
	peakIndex = indexes[len(indexes) - nbOfPeaks + i]

	n = peakIndex
	while X[idx][n] > (X[idx][peakIndex]*offset):
		n = n-1
	a = n

	n = peakIndex
	while X[idx][n] > (X[idx][peakIndex]*offset):
		n = n+1
	b = n

	bandwidth = (b-a)/(fs/x.size) # bandwidth in Hz
	print(bandwidth)
	peakst60.append(6.91/fs/(1-math.exp(-math.pi*bandwidth/fs)))

print(" peaks frequencies : ")
print(peaksFreq)
print(" corresponding gains : ")
print(peaksGains)
print(" corresponding t60 : ")
print(peakst60)

# Writing the dsp file #
# #######################
file = open(modelName + ".dsp", "w")
file.write("import(\"pm.lib\");\n")
file.write("import(\"libraries/old/music.lib\");\n\n")
file.write("pi = 4*atan(1.0);\n")
file.write("nModes = ")
file.write(str(len(peaksGains)))
file.write(";\n")
file.write("modeFrequencies=("); # writing the frequencies list
k = 0
for i in peaksFreq:
	file.write(str(i))
	if (k+1<len(peaksGains)):
		file.write(",")
	k += 1
file.write(");\n");
file.write("massEigenValues=("); # writing the masses list
k = 0
for i in peaksGains:
	file.write(str(i))
	if (k+1 < len(peaksGains)):
		file.write(",")
	k += 1
file.write(");\n");
file.write("t60=("); # writing the t60 list
k = 0
for i in peakst60:
	file.write(str(i))
	if (k+1 < len(peaksGains)):
		file.write(",")
	k += 1
file.write(");\n");
file.write("modeFreqs=par(i,nModes,take(i+1, modeFrequencies));\n")
file.write("modeGains=par(i,nModes,take(i+1, massEigenValues));\n")
file.write("modeT60 = par(i,nModes,take(i+1,t60));\n")
file.write(modelName)
file.write("=modalModel(nModes,modeFrequencies,modeGains,modeT60);");
file.write('\ngate = button("gate");')
file.write("\nprocess = impulseExcitation(gate) : " + modelName + " <: _,_; ")
file.close();
