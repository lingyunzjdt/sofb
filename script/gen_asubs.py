import sys
import math
from datetime import datetime

def build_tree(sl, n, level = 0, prefix=""):
    if len(sl) <= n:
        ntot = sum([si[1] for si in sl])
        return ("%s" % (prefix,), ntot, sl)
    # more
    nbit = int(math.ceil(math.log10(len(sl) // n + 1)))
    fmt = "%s_aSub_%%d_%%0%dd" % (prefix, nbit)
    grp = []
    for i,s in enumerate(sl):
        if i % n == 0:
            grp.append([fmt % (level, i//n), s[1], [s,]])
        else:
            grp[-1][2].append(s)
            grp[-1][1] += s[1]
    return build_tree(grp, n, level + 1, prefix=prefix)

def output_tree(sl, level = 0):
    # leaf
    if not sl[-1]: return
    idt = "    " * level
    print idt + "%s[%d] { " % (sl[0], sl[1]), 
    for i,si in enumerate(sl[2]):
        if not si[-1]:
            print si,
        else:
            # the leaf node
            print si[0],
    print " }"
    for i,si in enumerate(sl[2]):
        output_tree(si, level+1)

def move_up_sl(stree):
    # move up single leaf
    if not stree[-1]: return False
    #print stree
    if len(stree[-1]) == 1 and stree[-1][-1]:
        # move up one level
        stree[0] = stree[-1][0][0]
        stree[-1] = stree[-1][0][-1]
        return True
    for subtree in stree[-1]:
        if move_up_sl(subtree): return True
    return False

def flat_tree(sl):
    # generate a flat list of [parent, out_size, list_of_(child, size)] 
    # leaf
    if all([not si[-1] for i,si in enumerate(sl[2])]):
        # it is aleaf
        return [(sl[0], sl[1], [(si[0], si[1]) for si in sl[2]])]
    subgrp = [[sl[0], sl[1], [(si[0], si[1]) for si in sl[2]]]]
    for i,si in enumerate(sl[2]):
        # single leaf does not need extra record
        if not si[-1]: continue
        subgrp.extend(flat_tree(si))
    return subgrp
                

TMPL_WFM = """
record(waveform, "%(pv)s") {
    field(NELM, "%(nelm)d")
    field(FTVL, "FLOAT")
}

"""

TMPL_ASUB_HEAD = """
record(aSub, "%(pv)s_aSub_") {
    field(SNAM, "%(snam)s")
"""
TMPL_ASUB_INP = """
    field(INP%(i)s, "%(pvi)s")
    field(FT%(i)s,  "%(fti)s")
    field(NO%(i)s,  "%(noi)s")"""
TMPL_ASUB_OUT = """
    field(OUT%(i)s, "%(pvi)s PP")
    field(FTV%(i)s,  "%(fti)s")
    field(NOV%(i)s,  "%(noi)s")"""

def output_db(output, rlst, snam = "_merge", fti="FLOAT"):
    # output record list to output file
    f = open(output, "w")
    f.write("## Generated from List of PVs.\n")
    f.write("## Lingyun Yang <lyyang@bnl.gov>, %s\n" % \
            datetime.now().strftime("%m-%d-%Y %H:%M:%S"))
    f.write("##\n")
    for r in rlst:
        wfm, nelm, subs = r
        f.write(TMPL_WFM % {"nelm": nelm, "pv": wfm})
        f.write(TMPL_ASUB_HEAD % {"pv": wfm, "snam": snam})
        for i,(pvi, noi) in enumerate(subs):
            ir = chr(ord('A') + i)
            f.write(TMPL_ASUB_INP % {
                "i": ir, "pvi": pvi, "noi": noi, "fti": fti})
        f.write(TMPL_ASUB_OUT % {
            "i": "A", "pvi": wfm, "noi": nelm, "fti": fti})
        f.write("\n}\n")
    f.close()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print "Usage: python %s inputpvs.txt" % sys.argv[0]

    allpvs = [s.strip() for s in open(sys.argv[1]).readlines()]
    pvsum = allpvs[0]
    nodes = [[pvi, 1, []] for pvi in allpvs[1:]]
    print "Building aSub for %d pvs into %s" % (len(nodes), pvsum)
    stree = build_tree(nodes, 20, prefix=pvsum)
    #print stree
    #output_tree(stree, 0)
    while move_up_sl(stree):
        pass
        #output_tree(stree, 0)
    rlst = flat_tree(stree)
    mlen = 0
    for r in rlst:
        mlen = max(len(r[0]), mlen)
    output_db("test.db", rlst, snam="mergePvs", scan=".1 second")
    print "Max length:", mlen

