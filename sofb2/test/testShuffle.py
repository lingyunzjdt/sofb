import unittest
from cothread.catools import caget, caput

P = "l:"
class TestBpmShuffle(unittest.TestCase):
    def test_1(self):
        caput(P+"SR:APHLA:SOFB{BPM}Index", [1, 3, 2, 4, 0])
        caput("l:SR:APHLA:SOFB{BPM}Sel", [1, 1, 1, 0, 0])
        caput("l:SR:APHLA:SOFB{BPM}Index_", [5, 5, 5, 5, 5])

        caput("l:SR:APHLA:SOFB{BPM}_index_asub_.PROC", 1)
        print caget("l:SR:APHLA:SOFB{BPM}Index_")

        caput("l:SR:APHLA:SOFB{BPM}X_", [10., 11., 12., 13., 14.])
        caput("l:SR:APHLA:SOFB{BPM}_shuffle_asub_.PROC", 1)
        for s in range(1, 21):
            print caget("l:SR:APHLA:SOFB{BPM}X" + chr(ord('A') + s))


