import numpy as np
from scipy import signal
from scipy.signal import remez

import matplotlib.pyplot as plt 

# https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.remez.html#scipy.signal.remez

def plot_response(w, h, title):
    "Utility function to plot response functions"
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.plot(w, 20*np.log10(np.abs(h)))
    ax.set_ylim(-40, 5)
    ax.grid(True)
    ax.set_xlabel('Frequency (Hz)')
    ax.set_ylabel('Gain (dB)')
    ax.set_title(title)

taps = signal.remez(5,[0,1.0/16,1.0/16+0.1,0.5],[1,0])

print(taps)

w, h = signal.freqz(taps, [1], worN=2000)
plot_response(w, h, "Low-pass Filter")
plt.show()
