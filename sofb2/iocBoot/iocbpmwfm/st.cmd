#!../../bin/linux-x86_64/bpmwfm

## You may have to change bpmwfm to something else
## everywhere it appears in this file

#< envPaths

## Register all support components
dbLoadDatabase("../../dbd/bpmwfm.dbd",0,0)
bpmwfm_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("../../db/bpmwfm.db","p=l:,XY=X,SIGNAL=wUsrOff-Calc")
dbLoadRecords("../../db/bpmshuffle.db","p=l:,XY=X,SIGNAL=wUsrOff-Calc")

iocInit()

## Start any sequence programs
#seq sncbpmwfm,"user=lyyang"
