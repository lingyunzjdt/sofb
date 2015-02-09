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

dbLoadRecords("db/localbump.db", "ID=C03-HXN,XY=X,HV=H,C1=03,I1=7,C2=03,I2=8,S1=-2.543,S2=0,S3=2.679")

dbLoadRecords("db/localbump.db", "ID=C05u-SRX,XY=X,HV=H,C1=05,I1=7,C2=05,I2=8,S1=-1.304,S2=0,S3=1.304")

dbLoadRecords("db/localbump.db", "ID=C05d-SRX,XY=X,HV=H,C1=05,I1=8,C2=05,I2=9,S1=-1.453,S2=0,S3=1.453")

#dbLoadRecords("db/localbump.db", "ID=C08-XPD,XY=X,HV=H,C1=10,I1=7,C2=10,I2=8,S1=-1.453,S2=0,S3=1.453")

dbLoadRecords("db/localbump.db", "ID=C10-IXS,XY=X,HV=H,C1=10,I1=7,C2=10,I2=8,S1=-3.898,S2=0,S3=4.029")

dbLoadRecords("db/localbump.db", "ID=C11-CHX,XY=X,HV=H,C1=11,I1=7,C2=11,I2=8,S1=-2.543,S2=0,S3=2.679")

#dbLoadRecords("db/localbump.db", "ID=C18-XPD,XY=X,HV=H,C1=18,I1=7,C2=18,I2=8,S1=-2.553,S2=0,S3=1.238")

dbLoadRecords("db/localbump.db", "ID=C23u-CSX,XY=X,HV=H,C1=23,I1=7,C2=23,I2=8,S1=-2.553,S2=0,S3=1.238")

dbLoadRecords("db/localbump.db", "ID=C23d-CSX,XY=X,HV=H,C1=23,I1=8,C2=23,I2=9,S1=-1.102,S2=0,S3=1.102")

dbLoadRecords("db/localbump.db", "ID=C28-XPD,XY=X,HV=H,C1=28,I1=7,C2=28,I2=8,S1=-3.662,S2=0,S3=3.678")

#dbLoadRecords("db/localbump.db", "ID=C10-ISX,XY=X,HV=H,C1=10,I1=7,C2=10,I2=8,S1=-3.899,S2=0,S3=4.029")

iocInit()

## Start any sequence programs
#seq sncbump,"user=lyyang"
