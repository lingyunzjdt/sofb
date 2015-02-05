#!/epics/iocs/srSOFB2/sofb2/bin/linux-x86_64/bump

## You may have to change bump to something else
## everywhere it appears in this file

#< envPaths

< /epics/iocs/srSOFB2/sofb2/iocBoot/iocbump/envPaths

epicsEnvSet("EPICS_CA_MAX_ARRAY_BYTES", "30000000")

#cd ${TOP}
#cd /direct/phy_iocs/srSOFB2/sofb2
cd /epics/iocs/srSOFB2/sofb2

## Register all support components
dbLoadDatabase("dbd/bump.dbd",0,0)
bump_registerRecordDeviceDriver(pdbbase) 

## Load record instances
#dbLoadRecords("db/bump.db","user=lyyang")

dbLoadRecords("db/localbump.db", "ID=ISX,PL=X,L=7.928,OFST1L=SR:C10-BI{BPM:7}Pos:Href-SP,OFST1R=SR:C10-BI{BPM:8}Pos:Href-SP,OFST2L=SR:C10-BI{BPM:7}Pos:UsrXoffset-SP,OFST2R=SR:C10-BI{BPM:8}Pos:UsrXoffset-SP,X1=SR:C10-BI{BPM:7}Pos:XwUsrOff-Calc,X2=SR:C10-BI{BPM:8}Pos:XwUsrOff-Calc,X01=SR:C10-BI{BPM:7}Pos:X-I,X02=SR:C10-BI{BPM:8}Pos:X-I")

iocInit()

## Start any sequence programs
#seq sncbump,"user=lyyang"
