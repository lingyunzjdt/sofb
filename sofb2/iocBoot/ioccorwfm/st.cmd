#!../../bin/linux-x86_64/corwfm

## You may have to change corwfm to something else
## everywhere it appears in this file

#< envPaths

## Register all support components
dbLoadDatabase("../../dbd/corwfm.dbd",0,0)
corwfm_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("../../db/corwfm.db","user=lyyang")
dbLoadRecords("../../db/cor_rb_merge.db", "p=lyyang:,PLN=X,PSi=Ps1")
dbLoadRecords("../../db/cor_rb_merge.db", "p=lyyang:,PLN=Y,PSi=Ps2")

dbLoadRecords("../../db/cor_sp_merge.db", "p=lyyang:,PLN=X,SPi=Sp1")
dbLoadRecords("../../db/cor_sp_merge.db", "p=lyyang:,PLN=Y,SPi=Sp2")

dbLoadRecords("../../db/cor_sel.db", "p=lyyang:,XSel=XSel,T=CHAR")
dbLoadRecords("../../db/cor_sel.db", "p=lyyang:,XSel=YSel,T=CHAR")

dbLoadRecords("../../db/cor_sp_split.db", "p=lyyang:,PLN=X,SPi=Sp1")
dbLoadRecords("../../db/cor_sp_split.db", "p=lyyang:,PLN=Y,SPi=Sp2")


dbLoadRecords("../../db/cor.db", "p=lyyang:,XSel=YSel,T=CHAR")

iocInit()

## Start any sequence programs
#seq snccorwfm,"user=lyyang"
