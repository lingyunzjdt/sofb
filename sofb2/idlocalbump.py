import numpy as np
import aphla as ap
import time
import cothread
from cothread.catools import caget

# I know the macro in, escape {}
_tmpl = { "cmd": "SR:APHLA:SOFB{{BUMP:{ID}}}{XY}-Cmd",
          "cmddone": "SR:APHLA:SOFB{{BUMP:{ID}}}{XY}-CmdDone",
          "angle": "SR:APHLA:SOFB{{BUMP:{ID}}}angle:{XY}-SP",
          "offset": "SR:APHLA:SOFB{{BUMP:{ID}}}offset:{XY}-SP",
          "s1": "SR:APHLA:SOFB{{BUMP:{ID}}}S1:{XY}-I",
          "s2": "SR:APHLA:SOFB{{BUMP:{ID}}}S2:{XY}-I",
          "s3": "SR:APHLA:SOFB{{BUMP:{ID}}}S3:{XY}-I",
          "mmscale": "SR:APHLA:SOFB{{BUMP:{ID}}}mmscale:{XY}-I",
          "op": "SR:APHLA:SOFB{{BUMP:{ID}}}op:{XY}-SP",
          "hv1": "SR:C{C1}-BI{{BPM:{I1}}}Pos:{HV}ref-SP",
          "hv2": "SR:C{C2}-BI{{BPM:{I2}}}Pos:{HV}ref-SP",
          "usr1": "SR:C{C1}-BI{{BPM:{I1}}}Pos:Usr{XY}offset-SP",
          "usr2": "SR:C{C2}-BI{{BPM:{I2}}}Pos:Usr{XY}offset-SP", }

_pvcmd = "SR:APHLA:SOFB{BUMP:ALL}cmd"

_id_macros = [
    {"idname": "ivu20g1c03c", "bpm1": "pu1g1c03a", "bpm2": "pu4g1c03a",
     "ID": "C03-HXN", "XY":"X", "HV": "H", "C1": "03", "I1": "7",
     "C2": "03", "I2": "8", "S1": "-2.543", "S2": "0", "S3": "2.679"},
    {"idname": "ivu20g1c03c", "bpm1": "pu1g1c03a", "bpm2": "pu4g1c03a",
     "ID": "C03-HXN", "XY": "Y", "HV": "V", "C1": "03", "I1": "7",
     "C2": "03", "I2": "8", "S1": "-2.543", "S2": "0", "S3": "2.679"},
    #
    {"idname": "", "bpm1": "pu1g1c05a", "bpm2": "pu2g1c05a",
     "ID": "C05u-SRX", "XY": "X", "HV": "H", "C1": "05", "I1": "7",
     "C2": "05", "I2": "8", "S1": "-1.304", "S2": "0", "S3": "1.304"},
    {"idname": "", "bpm1": "pu1g1c05a", "bpm2": "pu2g1c05a",
     "ID": "C05u-SRX", "XY": "Y", "HV": "V", "C1": "05", "I1": "7",
     "C2": "05", "I2": "8", "S1": "-1.304", "S2": "0", "S3": "1.304"},
    #
    {"idname": "ivu21g1c05d", "bpm1": "pu2g1c05a", "bpm2": "pu4g1c05a",
     "ID": "C05d-SRX", "XY": "X", "HV": "H", "C1": "05", "I1": "8",
     "C2": "05", "I2": "9", "S1": "-1.453", "S2": "0", "S3": "1.453"},
    {"idname": "ivu21g1c05d", "bpm1": "pu2g1c05a", "bpm2": "pu4g1c05a",
     "ID": "C05d-SRX", "XY": "Y", "HV": "V", "C1": "05", "I1": "8",
     "C2": "05", "I2": "9", "S1": "-1.453", "S2": "0", "S3": "1.453"},
    #
    {"idname": "dw100g1c08u", "bpm1": "pu1g1c08a", "bpm2": "pu4g1c08a",
     "ID": "C08-XPD", "XY": "X", "HV": "H", "C1": "08", "I1": "7",
     "C2": "08", "I2": "8", "S1": "-1.453", "S2": "0", "S3": "1.453"},
    {"idname": "dw100g1c08u", "bpm1": "pu1g1c08a", "bpm2": "pu4g1c08a",
     "ID": "C08-XPD", "XY": "Y", "HV": "V", "C1": "08", "I1": "7",
     "C2": "08", "I2": "8", "S1": "-1.453", "S2": "0", "S3": "1.453"},
    #
    {"idname": "ivu22g1c10c", "bpm1": "pu1g1c10a", "bpm2": "pu4g1c10a",
     "ID": "C10-IXS", "XY": "X", "HV": "H", "C1": "10", "I1": "7",
     "C2": "10", "I2": "8", "S1": "-3.898", "S2": "0", "S3": "4.029"},
    {"idname": "ivu22g1c10c", "bpm1": "pu1g1c10a", "bpm2": "pu4g1c10a",
     "ID": "C10-IXS", "XY": "Y", "HV": "V", "C1": "10", "I1": "7",
     "C2": "10", "I2": "8", "S1": "-3.898", "S2": "0", "S3": "4.029"},

    {"idname": "ivu20g1c11c", "bpm1": "pu1g1c11a", "bpm2": "pu4g1c11a",
     "ID": "C11-CHX", "XY": "X", "HV": "H", "C1": "11", "I1": "7",
     "C2": "11", "I2": "8", "S1": "-2.543", "S2": "0", "S3": "2.679"},
    {"idname": "ivu20g1c11c", "bpm1": "pu1g1c11a", "bpm2": "pu4g1c11a",
     "ID": "C11-CHX", "XY": "Y", "HV": "V", "C1": "11", "I1": "7",
     "C2": "11", "I2": "8", "S1": "-2.543", "S2": "0", "S3": "2.679"},

    # C16
    {"idname": "ivu23g1c16c", "bpm1": "pu1g1c16a", "bpm2": "pu4g1c16a",
     "ID": "C16-LIX", "XY": "X", "HV": "H", "C1": "16", "I1": "7",
     "C2": "16", "I2": "8", "S1": "-2.071", "S2": "0", "S3": "2.071"},
    {"idname": "ivu23g1c16c", "bpm1": "pu1g1c16a", "bpm2": "pu4g1c16a",
     "ID": "C16-LIX", "XY": "Y", "HV": "V", "C1": "16", "I1": "7",
     "C2": "16", "I2": "8", "S1": "-2.071", "S2": "0", "S3": "2.071"},

    # C17-1
    {"idname": "ivu21g1c17c", "bpm1": "pu1g1c17a", "bpm2": "pu2g1c17a",
     "ID": "C17u-FMX", "XY": "X", "HV": "H", "C1": "17", "I1": "7",
     "C2": "17", "I2": "8", "S1": "-1.342", "S2": "0", "S3": "1.240"},
    {"idname": "ivu20g1c17c", "bpm1": "pu1g1c17a", "bpm2": "pu2g1c17a",
     "ID": "C17u-FMX", "XY": "Y", "HV": "V", "C1": "17", "I1": "7",
     "C2": "17", "I2": "8", "S1": "-1.342", "S2": "0", "S3": "1.240"},

    # C17-2
    {"idname": "ivu21g1c17d", "bpm1": "pu2g1c17a", "bpm2": "pu4g1c17a",
     "ID": "C17d-AMX", "XY": "X", "HV": "H", "C1": "17", "I1": "8",
     "C2": "17", "I2": "9", "S1": "-1.3868", "S2": "0", "S3": "1.5192"},
    {"idname": "ivu21g1c17d", "bpm1": "pu2g1c17a", "bpm2": "pu4g1c17a",
     "ID": "C17d-AMX", "XY": "Y", "HV": "V", "C1": "17", "I1": "8",
     "C2": "17", "I2": "9", "S1": "-1.3868", "S2": "0", "S3": "1.5192"},

    # C18
    {"idname": "dw100g1c18d", "bpm1": "pu1g1c18a", "bpm2": "pu4g1c18a",
     "ID": "C18-XPD", "XY": "X", "HV": "H", "C1": "18", "I1": "7",
     "C2": "18", "I2": "8", "S1": "-3.6615", "S2": "0", "S3": "3.6775"},
    {"idname": "dw100g1c18d", "bpm1": "pu1g1c18a", "bpm2": "pu4g1c18a",
     "ID": "C18-XPD", "XY": "Y", "HV": "V", "C1": "18", "I1": "7",
     "C2": "18", "I2": "8", "S1": "-3.6615", "S2": "0", "S3": "3.6775"},

    {"idname": "epu49g1c23u", "bpm1": "pu1g1c23a", "bpm2": "pu3g1c23a",
     "ID": "C23u-CSX", "XY": "X", "HV": "H", "C1": "23", "I1": "7",
     "C2": "23", "I2": "8", "S1": "-2.553", "S2": "0", "S3": "1.238"},
    {"idname": "epu49g1c23u", "bpm1": "pu1g1c23a", "bpm2": "pu3g1c23a",
     "ID": "C23u-CSX", "XY": "Y", "HV": "V", "C1": "23", "I1": "7",
     "C2": "23", "I2": "8", "S1": "-2.553", "S2": "0", "S3": "1.238"},

    {"idname": "epu49g1c23d", "bpm1": "pu3g1c23a", "bpm2": "pu4g1c23a",
     "ID": "C23d-CSX", "XY": "X", "HV": "H", "C1": "23", "I1": "8",
     "C2": "23", "I2": "9", "S1": "-1.102", "S2": "0", "S3": "1.102"},
    {"idname": "epu49g1c23d", "bpm1": "pu3g1c23a", "bpm2": "pu4g1c23a",
     "ID": "C23d-CSX", "XY": "Y", "HV": "V", "C1": "23", "I1": "8",
     "C2": "23", "I2": "9", "S1": "-1.102", "S2": "0", "S3": "1.102"},

    {"idname": "dw100g1c28u", "bpm1": "pu1g1c28a", "bpm2": "pu4g1c28a",
     "ID": "C28-XPD", "XY": "X", "HV": "H", "C1": "28", "I1": "7",
     "C2": "28", "I2": "8", "S1": "-3.662", "S2": "0", "S3": "3.678"},
    {"idname": "dw100g1c28u", "bpm1": "pu1g1c28a", "bpm2": "pu4g1c28a",
     "ID": "C28-XPD", "XY": "Y", "HV": "V", "C1": "28", "I1": "7",
     "C2": "28", "I2": "8", "S1": "-3.662", "S2": "0", "S3": "3.678"},

    #{"idname": "", "bpm1": "pu1g1c03a", "bpm2": "pu4g1c03a", "ID": "C10-ISX", "XY": "X", "HV": "H", "C1": "10", "I1": "7", "C2": "10", "I2": "8", "S1": "-3.899", "S2": "0", "S3": "4.029"},
]

def run_single_bumps(pvmaps):
    for pvm in pvmaps:
        if ap.caget(pvm["cmd"]) == 0: continue
        ap.caput(pvm["cmddone"], 0)
        ename = pvm["idname"]
        if not ename: continue
        if ap.caget(pvm["op"]) == 0: continue
        xc, xangle = ap.caget([pvm["offset"], pvm["angle"]])
        plane = pvm["XY"].lower()
        print ename, xc, xangle, plane
        norm0, norm1, norm2, corvals = ap.setIdBump(
            ename, xc, xangle, plane=plane, check=False, ncor=6, dImax=0.5)
        print "Norm:", norm0, norm1, norm2
        print corvals
        ap.caput(pvm["cmddone"], 1)
        ap.caput(pvm["cmd"], 0)
        cothread.Yield(0.1)
        
            
if __name__ == "__main__":
    ap.machines.load("nsls2", "SR")
    pvmaps = []
    for mac in _id_macros:
        pvls = [(k,mac[k]) for k in ("idname", "bpm1", "bpm2", "XY")]
        for k,v in _tmpl.items():
            pv = v.format(**mac)
            pvls.append((k, pv))
        pvdict = dict(pvls)
        #print k, pv, caget(pv)
        bpm = ap.getElements(pvdict["bpm1"])[0]
        if mac["HV"] == "H" and pvdict["hv1"] != bpm.pv(field="xref1")[0]:
            print bpm.name, mac["HV"], pvdict["hv1"], bpm.pv(field="xref1")[0]
        pvmaps.append(pvdict)

    #for b in ap.getElements("UBPM"):
    #    print b.name, b.pv(field="x")
    print "Start checking IDLocalBump command ..."
    while True:
        run_single_bumps(pvmaps)
        if ap.caget(_pvcmd) == 0:
            time.sleep(1)
            continue
        #obt = ap.getOrbit(spos=True)
        #print "BPMS:", len(ap.getElements("BPM")),
        #print np.average(obt[:,0]), np.std(obt[:,0])
        for pvm in pvmaps:
            ap.caput(pvm["cmddone"], 0)
        for pvm in pvmaps:
            ename = pvm["idname"]
            if not ename: continue
            if ap.caget(pvm["op"]) == 0: continue
            xc, xangle = ap.caget([pvm["offset"], pvm["angle"]])
            plane = pvm["XY"].lower()
            print ename, xc, xangle, plane
            norm0, norm1, norm2, corvals = ap.setIdBump(
                ename, xc, xangle, plane=plane, check=False, ncor=6, dImax=0.5)
            print "Norm:", norm0, norm1, norm2
            print corvals
            ap.caput(pvm["cmddone"], 1)
            cothread.Yield(0.1)
        time.sleep(1)
        ap.caput(_pvcmd, 0) 
