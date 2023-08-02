
SAMPLINGFREQ = 57445
WAV_SHIFT = 24
DRUM_SHIFT = 20

def midiToFreq(x):
    return(440*2**((x-69)/12))

def freqToPhaseIncrement(f,shift):
    length = 1 << (32 - WAV_SHIFT)
    ref_freq = 1.0*SAMPLINGFREQ / length
    phase_increment = 1.0*f/ref_freq
    return(round(phase_increment * (1<<WAV_SHIFT)))

def drumFreqToPhaseIncrement(record_freq,shift):
    length = 1 << (32 - WAV_SHIFT)
    phase_increment = 1.0*record_freq/SAMPLINGFREQ
    return(round(phase_increment * (1<<WAV_SHIFT)))

def genTable(freqs,name,nb,shift):
    print(f"static const uint32_t {name}[{nb}] = {{")
    nb = 0
    for freq in freqs:
        phaseIncrement = freqToPhaseIncrement(freq,WAV_SHIFT)
        print("%d," % phaseIncrement,end="")
        nb=nb+1 
        if (nb==10):
            print("")
            nb=0
    print("};")

def genDrumTable(freqs,name,nb,shift):
    print(f"static const uint32_t {name}[{nb}] = {{")
    nb = 0
    for freq in freqs:
        phaseIncrement = drumFreqToPhaseIncrement(freq,WAV_SHIFT)
        print("%d," % phaseIncrement,end="")
        nb=nb+1 
        if (nb==10):
            print("")
            nb=0
    print("};")

MIN_NOTE = 21 # we only do the piano range
MAX_NOTE = 108

freqs = [midiToFreq(x) for x in range(MIN_NOTE,MAX_NOTE+1)]
genTable(freqs,"tune_to_phase_increment","NUM_NOTES",WAV_SHIFT)

freqs = [4000, 8000, 8000, 8000, 4000, 4000]
genDrumTable(freqs,"drum_waveform_phase_increment",6,DRUM_SHIFT)