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
dbLoadRecords("db/bpmx.db", "")

iocInit()

## Start any sequence programs
#seq sncsofb,"user=lyyang"
