import shutil

def insert_bpms(fdb, fold, fnew):
    bpms1 = [s.split()[-1].strip()
             for s in open(fold, 'r').readlines()]
    bpms2 = [s.split()[-1].strip()
             for s in open(fnew, 'r').readlines()]
    for i in range(len(bpms2) - len(bpms1)):
        bpms1.append(None)
    shutil.copy(fdb, fdb + ".bak")
    print len(bpms2), len(bpms1)
    s = open(fdb, 'r').read()
    for b1, b2 in zip(bpms1, bpms2):
        print b1, b2
        if b1 is None:
            print "{0} is new".format(b2)
            continue
        s = s.replace(b1, b2)
    f = open(fdb, 'w')
    f.write(s)
    f.close()

if __name__ == "__main__":
    insert_bpms("Db/bpm_wfm_merge.db", "bpmlst198.txt", "bpmlst211.txt")
    
