#!../../bin/linux-x86_64/sofb

## You may have to change sofb to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

## Register all support components
dbLoadDatabase("dbd/sofb.dbd",0,0)
sofb_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("db/sofb.db","user=lyyang")
dbLoadRecords("db/bpmx0.db", "")
dbLoadRecords("db/bpmx.db", "")
dbLoadRecords("db/bpmy0.db", "")
dbLoadRecords("db/bpmy.db", "")

dbLoadRecords("db/corx_sp_merge.db", "")
dbLoadRecords("db/cory_sp_merge.db", "")
dbLoadRecords("db/corx_rb_merge.db", "")
dbLoadRecords("db/cory_rb_merge.db", "")
dbLoadRecords("db/corx_sel.db", "")
dbLoadRecords("db/cory_sel.db", "")
dbLoadRecords("db/corx_sp_split.db", "")
dbLoadRecords("db/cory_sp_split.db", "")

iocInit()

## Start any sequence programs
#seq sncsofb,"user=lyyang"
