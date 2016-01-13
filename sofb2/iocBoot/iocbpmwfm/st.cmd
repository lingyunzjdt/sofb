#!/epics/iocs/srSOFB2/sofb2/bin/linux-x86_64/bpmwfm

## You may have to change bpmwfm to something else
## everywhere it appears in this file

epicsEnvSet("ENGINEER","lyyang x4692")

#< envPaths

cd /epics/iocs/srSOFB2/sofb2

## Register all support components
dbLoadDatabase("dbd/bpmwfm.dbd",0,0)
bpmwfm_registerRecordDeviceDriver(pdbbase) 

dbLoadRecords("db/iocAdminSoft.db", "IOC=OP-APHLA{IOC:bpmwfm}")

## Load record instances
dbLoadRecords("db/bpmwfm.db","p=l:,SIGNAL=Pos:XwUsrOff-Calc")
dbLoadRecords("db/bpmshuffle.db","p=l:,SIGNAL=Pos:XwUsrOff-Calc")

iocInit()

## Start any sequence programs
#seq sncbpmwfm,"user=lyyang"
