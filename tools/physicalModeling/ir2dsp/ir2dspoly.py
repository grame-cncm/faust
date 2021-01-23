#!/usr/bin/env python
# -*- coding: utf-8 -*-
# id2dsp.py
# Copyright Pierre-Amaury Grumiaux, Pierre Jouvelot, Emilio Jesus Gallego Arias,
# Romain Michon and Jakob Dübel

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
parser.add_argument("rootHz", help = "Root frequency in Hertz")
ars = parser.parse_args ()
# Arguments
script, soundFile, modelName, peakThreshold, peakDistance, rootHz = argv

# Reading file
print("Reading wav file...")
(fs, x) = read(soundFile)
if x.shape[1] == 2:
    x = x[:, 0]
# Normalizing sound
x = x/np.max(x)

# FFT
kk = 1.0/float(rootHz)
print("Computing FFT...")
X = np.abs(np.fft.fft(x))
X = X/(np.max(X))
# computing corresponding frequencies
time_step = 1/fs
freqs = np.fft.fftfreq(x.size, time_step)*kk
idx = np.argsort(freqs)

# plot for debug
# plt.plot(freqs[idx],20*np.log(X[idx]))
# plt.show()

# detecting peaks
print("Detecting FFT peaks...")
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
peaksGains = peaksGains/(np.max(peaksGains))

#Computing t60 values
print("Calculating T60 values...")
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
	peakst60.append((6.91/fs/(1-math.exp(-math.pi*bandwidth/fs)))*150.0)
	#	peakst60.append(6.91/fs/(1-math.exp(-math.pi*bandwidth/fs))) s 

print("Frequency peaks and corresponding gains and T60 has been successfully calculated.")

# Writing the dsp file #
# #######################
print("Writing the dsp file...")
file = open(modelName + ".dsp", "w")
file.write("// -*-Faust-*-\n")
file.write("// generated with ir2dsp.py {0} {1} {2}\n".format(modelName, peakThreshold, peakDistance))
file.write("declare name \"{0}\";\n".format(modelName))
file.write("import(\"stdfaust.lib\");\n\n")
file.write("nModes = ")
file.write(str(len(peaksGains)))
file.write(";\n")
file.write("modeFrequencies = ("); # writing the frequencies list
k = 0
for i in peaksFreq:
	file.write(str(i))
	if (k+1<len(peaksGains)):
		file.write(",")
	k += 1
file.write(");\n");
file.write("massEigenValues = ("); # writing the masses list
k = 0
for i in peaksGains:
	file.write(str(i))
	if (k+1 < len(peaksGains)):
		file.write(",")
	k += 1
file.write(");\n");
file.write("t60 = ("); # writing the t60 list
k = 0
for i in peakst60:
	file.write(str(i))
	if (k+1 < len(peaksGains)):
		file.write(",")
	k += 1
file.write(");\n");
# file.write("modeFreqs=par(i,nModes,ba.take(i+1, modeFrequencies));\n")
# file.write("modeGains=par(i,nModes,ba.take(i+1, massEigenValues));\n")
# file.write("modeT60 = par(i,nModes,ba.take(i+1,t60));\n")
# file.write(modelName)
# file.write("=pm.modalModel(nModes,modeFreqs,modeT60,modeGains);");
# file.write('\ngate = button("gate");')
# file.write("\nprocess = pm.impulseExcitation(gate) : " + modelName + " <: _,_; ")

# file.write("\nmodalModel(n,modeFreqs,modeRes,modeGains) = _ <: par(i,n,pm.modeFilter(freqs(i),res(i),gain(i))) :> _\n")

file.write("\nmodalModel(n,modeFreqs,modeRes,modeGains,rootHz) = _ <: par(i,n,pm.modeFilter(freqs(i),res(i),gain(i))) :> _/n\n")
file.write("with{\n")
file.write("freqs(i) = ba.take(i+1,modeFreqs)*rootHz;\n")
file.write("res(i) = ba.take(i+1,modeRes);\n")
file.write("gain(i) = ba.take(i+1,modeGains);\n")
file.write("};\n\n")

file.write(modelName)
file.write(" = modalModel(nModes,modeFrequencies,t60,massEigenValues,f);");
file.write('\ngate = button("gate");')
file.write('\nf = hslider("freq",220,220,2000,0.01);');
file.write("\nprocess = pm.impulseExcitation(gate) : " + modelName + " <: _,_; ")

file.close();

print(modelName + ".dsp has been successfully created!")