import time
import unittest
import random

from cothread.catools import caget, caput

P = "l:"

class TestCorSel(unittest.TestCase):
    def setUp(self):
        # read cor device, e.g. C29-MG{PS:CH1B}
        self._cor_dev = [s.strip() for s in 
                         open("dev_cor.txt", "r").readlines()]

    def test_xsel(self):
        pvs = ["SR:" + s + "Enbl:Ps1OC-Cmd"
               for s in self._cor_dev]
        xsel_vec = caget(pvs)
        xsel_wfm = caget(P + "SR:APHLA:SOFB{COR}XSel-I")
        self.assertEqual(len(xsel_vec), len(xsel_wfm))
        for i in range(len(xsel_vec)):
            self.assertEqual(xsel_vec[i], xsel_wfm[i])

    def test_xsel_1x1(self):
        pvs = ["SR:" + s + "Enbl:Ps1OC-Cmd"
               for s in self._cor_dev]
        jl = random.sample(range(len(pvs)), 20)
        pvjl = [pvs[j] for j in jl]
        x0 = caget(pvjl)
        x1 = [1 - x for x in x0]
        caput(pvjl, x1)
        time.sleep(1.5)
        x2wfm = caget(P + "SR:APHLA:SOFB{COR}XSel-I")
        for i,j in enumerate(jl):
            self.assertEqual(x1[i], x2wfm[j])
        caput(pvjl, x0)

