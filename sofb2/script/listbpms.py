from cothread.catools import caget

p="l:"

k = 0
for i in range(10):
    pv = "l:SR:APHLA:SOFB{BPM}Pos:XwUsrOff-Calc_1_%d_asub_" % i
    for j in range(21):
        pvj = str(caget(pv + ".INP" + chr(ord("A") + j)))
        if not pvj.strip(): continue
        print k, pvj.split()[0]
        k = k+1
