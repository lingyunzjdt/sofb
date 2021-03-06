import sys
import math
import re
from datetime import datetime

def build_tree(sl, n, level = 1):
    nbit = max(3, int(math.ceil(math.log10(len(sl) // n + 1))))
    # format the node name
    if len(sl) <= n:
        ntot = sum([si[2] for si in sl])
        return [level, 0, ntot, sl], 1
    # more
    grp = []
    for i,s in enumerate(sl):
        if i % n == 0:
            grp.append([level, i//n, s[-2], [s,]])
        else:
            # append and update count
            grp[-1][-1].append(s)
            grp[-1][-2] += s[-2]
    subtree, height = build_tree(grp, n, level + 1)
    return subtree, height + 1

def output_tree(sl, level = 0):
    # leaf
    if not sl[-1]: return
    idt = "    " * level
    lvl, idx, ntot, sub = sl
    print "{0} ({1}, {2}) {3} :/ ".format(idt, lvl, idx, ntot),
    for i,si in enumerate(sub):
        lvli, idxi, ntoti, subi = si
        if not subi:
            print "\n{0}     {1}".format(idt, si),
        else:
            # the leaf node
            print "\n{0}    ({1},{2}) {3}".format(idt, lvli, idxi, ntoti),
    print " /"
    for i,si in enumerate(sub):
        output_tree(si, level+1)

def move_up_sl(stree, n):
    """
    move up single leaf
    """
    #if n > 15:
    #    print "Max achived"
    #    sys.exit(0)
    if not stree[-1]: return False
    #print "Moving up", stree
    if len(stree[-1]) == 1 and stree[-1][-1]:
        #print stree
        # move up one level
        for i in range(len(stree)):
            stree[i] = stree[-1][0][i]
        #print stree
        return True
    for subtree in stree[-1]:
        if move_up_sl(subtree, n+1): return True
    return False

def flat_tree(sl):
    # generate a flat list of [level, index, out_size, list_of_(child, size)] 
    subgrp = [[sl[0], sl[1], sl[2], [
        (si[0], si[1], si[2]) if si[-1] else (si[0], si[2])
        for si in sl[-1]]]]
    for i,si in enumerate(sl[-1]):
        # single leaf does not need extra record
        if not si[-1]: continue
        subgrp.extend(flat_tree(si))
    return subgrp
                

def build_flnk(rlst):
    asubs = []
    for r in rlst:
        if re.match(r'.+_subtree_\d+_\d+', r[0]):
            asubs.append(r[0])
    asubs = sorted(asubs)
    #print asubs
    ret = []
    for r in rlst:
        try:
            i = asubs.index(r[0])
            flnk = asubs[i+1]
        except:
            flnk = None
        ret.append([ri for ri in r] + [flnk,])
    return ret

def build_record_merge(rlist, pvsum, iroot,
                       FTVL="DOUBLE", SNAM="mergePvs", SCAN=".1 second"):
    #the first record must be the root
    recs = []
    asubr = []
    flnk = None
    wfm = pvsum["waveform"]
    for i,r in enumerate(rlst):
        lvl, idx, n, subs = r
        # the result waveform
        pvwfm = "{0}_{1}_{2}_wfm_".format(wfm, lvl, idx)
        if i == iroot:
            pvwfm = wfm
        recs.append(["waveform", pvwfm, {"NELM": "%d" % n, "FTVL": FTVL}])
        # the asub record
        rsub = {"SNAM": SNAM, "OUTA": pvwfm + " PP",
                "FTVA": FTVL, "NOVA": "%d" % n}
        if i == iroot:
            for j,pv in enumerate(pvsum["stat"]):
                ir = chr(ord('B') + j)
                rsub["OUT%s" % ir] = "%s PP" % pv
                rsub["FTV%s" % ir] = FTVL
                rsub["NOV%s" % ir] = "1"
        for j,sub in enumerate(subs):
            ir = chr(ord('A') + j)
            pv = sub[0]
            if len(sub) == 3:
                pv = "{0}_{1}_{2}_wfm_".format(wfm, sub[0], sub[1])
                
            rsub["INP%s" % ir] = pv
            rsub["FT%s" % ir ] = FTVL
            rsub["NO%s" % ir ] = "%d" % sub[-1]
        if flnk:
            rsub["FLNK"] = flnk
        recs.append(["aSub", "{0}_{1}_{2}_asub_".format(wfm, r[0], r[1]), rsub])
        flnk = recs[-1][1]
    # recs[0][1] = wfm
    for pv in pvsum["stat"]:
        recs.append(["ao", pv, {}])
    recs.append(["bo", "{0}:status".format(wfm),
                 {"VAL": "1", "ZNAM": "Idle", "ONAM": "Running"}])
    recs.append(["calcout", "{0}:timer_".format(wfm),
                 {"SCAN": SCAN, "INPA": "{0}:status".format(wfm),
                  "CALC": "A>0?1:0", "OUT": flnk + " PP",
                  "OOPT": "When Non-zero", "DOPT": "Use CALC"}])
    return recs

def build_record_split(rlist, wfm, iroot,
                       FTVL="DOUBLE", SNAM="splitPvs", SCAN=".1 second"):
    #the first record must be the root
    recs = []
    asubr = []
    flnk = None
    wfm = pvsum["waveform"]
    for i,r in enumerate(rlst):
        lvl, idx, n, subs = r
        # the result waveform
        pvwfm = "{0}_{1}_{2}_wfm".format(wfm, lvl, idx)
        if i == iroot or iroot % len(rlst) == i:
            pvwfm = wfm
        recs.append(["waveform", pvwfm, {"NELM": "%d" % n, "FTVL": FTVL}])

        # the asub record
        rsub = {"SNAM": SNAM, "INPA": pvwfm,
                "FTA": FTVL, "NOA": "%d" % n}
        for j,sub in enumerate(subs):
            ir = chr(ord('A') + j)
            pv = sub[0]
            if len(sub) == 3:
                pv = "{0}_{1}_{2}_wfm".format(wfm, sub[0], sub[1])
                
            rsub["OUT%s" % ir] = "%s PP" % pv
            rsub["FTV%s" % ir ] = FTVL
            rsub["NOV%s" % ir ] = "%d" % sub[-1]
        if flnk:
            rsub["FLNK"] = flnk
        recs.append(["aSub", "{0}_{1}_{2}_asub".format(wfm, r[0], r[1]), rsub])
        if i == iroot or iroot % len(rlst) == i:
            # forward FLNK to its asub
            print "Setting flnk= %s for pv=%s" % (recs[-1][1], recs[-2][1])
            recs[-2][2]["FLNK"] = recs[-1][1]
        flnk = recs[-1][1]
    # recs[0][1] = wfm
    #recs.append(["bo", "{0}:status".format(wfm),
    #             {"VAL": "0", "ZNAM": "Idle", "ONAM": "Running"}])
    #recs.append(["calcout", "{0}:timer_".format(wfm),
    #             {"SCAN": SCAN, "INPA": "{0}:status".format(wfm),
    #              "CALC": "A>0?1:0", "OUT": flnk + " PP",
    #              "OOPT": "When Non-zero", "DOPT": "Use CALC"}])
    return recs

def write_db(dbf, recs, fmode = "w"):
    f = open(dbf, fmode)
    f.write("## Generated from List of PVs.\n")
    f.write("## Lingyun Yang <lyyang@bnl.gov>, %s\n" % \
            datetime.now().strftime("%m-%d-%Y %H:%M:%S"))
    f.write("##\n")

    for r in recs:
        f.write('record({0}, "{1}") {{\n'.format(r[0], r[1]))
        for fld in sorted(r[2].keys()):
            f.write('   field({0}, "{1}")\n'.format(fld, r[2][fld]))
        f.write('}\n\n')
    f.close()


    
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print "Usage: python %s inputpvs.txt" % sys.argv[0]

    allpvs = [s.strip() for s in open(sys.argv[-1]).readlines()]
    pvres, ntot, nelem = allpvs[0].split()
    ntot = int(ntot)
    nelem = int(nelem)
    pvsum = {"waveform": pvres, "stat": allpvs[1:-ntot]}
    nodes = [[pvi, 0, 1, []] for pvi in allpvs[-ntot:]]
    print "Building aSub for %d pvs into %s" % (len(nodes), pvsum)
    stree, height = build_tree(nodes, int(nelem), 1)

    #print stree
    output_tree(stree, 0)
    #move_up_sl(stree, 0)
    #move_up_sl(stree, 0)
    #print stree
    while move_up_sl(stree, 0):
        continue
        #output_tree(stree, 0)
    print "Clean Tree: height= %d" % height
    output_tree(stree, 0)
    if "--merge" in sys.argv:
        rlst = sorted(flat_tree(stree), reverse=True)
        if rlst[0][1] != 0 or rlst[0][2] != len(nodes):
            raise RuntimeError("tree root is wrong!: {0}".format(rlst[0]))
        recs = build_record_merge(rlst, pvsum, 0)
    elif "--split" in sys.argv:
        rlst = sorted(flat_tree(stree), reverse=False)
        if rlst[-1][1] != 0 or rlst[-1][2] != len(nodes):
            raise RuntimeError("tree root is wrong!: {0}".format(rlst[-1]))
        recs = build_record_split(rlst, pvsum, -1)
    #rlst = build_flnk(rlst)
    # add statistics
    #mlen = 0
    #for r in rlst:
    #    print r
    #    #mlen = max(len(r[0]), mlen)
    #output_db("test.db", rlst, snam="mergePvs", scan=".1 second")
    #print "Max length:", mlen
    write_db("test.db", recs, fmode="w")
    #
    # in case the sub pvs are new, need to create them as new record
    #inprecs = [["bo", pv, {"VAL": "1", "ONAM": "Used in aphla",
    #                       "ZNAM": "Not used in aphla"}]
    #           for pv in allpvs[-ntot:]]
    #write_db("test.db", inprecs, fmode="a")
