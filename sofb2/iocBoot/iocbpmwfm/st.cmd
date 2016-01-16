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
dbLoadRecords("db/bpmwfm_merge.db","p=,SGNL1=Pos:XwUsrOff-Calc,SGNL2=XwUsrOff-Calc_,SCAN=.1 second")
dbLoadRecords("db/bpmwfm_merge.db","p=,SGNL1=Pos:YwUsrOff-Calc,SGNL2=YwUsrOff-Calc_,SCAN=.1 second")

dbLoadRecords("db/bpmwfm_merge.db","p=,SGNL1=Pos:X-I,SGNL2=X0-I_,SCAN=.1 second")
dbLoadRecords("db/bpmwfm_merge.db","p=,SGNL1=Pos:Y-I,SGNL2=Y0-I_,SCAN=.1 second")

dbLoadRecords("db/bpmwfm.db","p=")

set_savefile_path("/epics/iocs/srSOFB2/sofb2/as/bpmwfm","/save")
set_requestfile_path("/epics/iocs/srSOFB2/sofb2/as/bpmwfm","/req")
set_pass1_restoreFile("ioc_settings.sav")

asSetFilename("/cf-update/acf/default.acf")

iocInit()

caPutLogInit("ioclog.cs.nsls2.local:7004", 1)

makeAutosaveFileFromDbInfo("as/bpmwfm/req/ioc_settings.req", "autosaveFields_pass1")
create_monitor_set("ioc_settings.req", 30, "")



## Start any sequence programs
#seq sncbpmwfm,"user=lyyang"
