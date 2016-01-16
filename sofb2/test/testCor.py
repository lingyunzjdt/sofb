import time
import unittest
import random

from cothread.catools import caget, caput

P = "l:"


class TestCorMaSpSplit(unittest.TestCase):
    def setUp(self):
        # read cor device, e.g. C29-MG{PS:CH1B}
        self._cor_dev = [s.strip() for s in 
                         open("dev_cor.txt", "r").readlines()]
        #SR:C17-MG{PS:CL1A}I:Sp1-SP  (Sp2)
        #SR:C17-MG{PS:CL1A}I:Ps1DCCT1-I (Ps2)
        self._pvs = ["SR:" + s + "I:Sp1-SP" for s in self._cor_dev] + \
            ["SR:" + s + "I:Sp2-SP" for s in self._cor_dev]
        self._pvsrb = ["SR:" + s + "I:Ps1DCCT1-I" for s in self._cor_dev] + \
            ["SR:" + s + "I:Ps2DCCT1-I" for s in self._cor_dev]
        self._v0 = caget(self._pvs)

    def testDx(self):
        v1 = [v + 0.1 for v in self._v0]
        caput(self._pvs, v1, wait=True)
        time.sleep(5)
        v1r = caget(self._pvsrb)
        v1w = caget(self._pvs)
        for i,vi in enumerate(v1):
            self.assertAlmostEqual(v1[i], v1r[i], places=1,
                                   msg= "{0} != {1} for {2}".format(v1[i], v1r[i], self._pvs[i]))
            self.assertAlmostEqual(v1[i], v1w[i], places=5)

    def testMaskedSp(self):
        v1 = []
        for v in self._v0[-20:]:
            v1.extend([v+3.0, 1.0])
        v1[-1] = 0
        v1[-3] = 0
        v1[-5] = 0
        caput("l:SR:APHLA:SOFB{COR}I:Sp1Mark_wfm_8_", v1)
        time.sleep(15)
        #v1r = caget(self._pvsrb)
        #v1w = caget(self._pvs)
        #for i,vi in enumerate(self._v0):
        #    self.assertAlmostEqual(self._v0[i], v1r[i], places=1,
        #                           msg= "{0} != {1} for {2}".format(v1[i], v1r[i

    def tearDown(self):
        caput(self._pvs, self._v0)

        
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
        x2 = caget(pvjl)
        x2wfm = caget(P + "SR:APHLA:SOFB{COR}XSel-I")
        for i,j in enumerate(jl):
            self.assertNotEqual(x2[i], x0[i])
            self.assertEqual(x2[i], x2wfm[j])
        caput(pvjl, x0)

