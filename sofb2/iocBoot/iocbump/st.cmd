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

dbLoadRecords("db/localbump.db", "ID=ISX,XY=X,HV=H,C1=10,I1=7,C2=10,I2=8,S1=-3.899,S2=0,S3=4.029")

iocInit()

## Start any sequence programs
#seq sncbump,"user=lyyang"
