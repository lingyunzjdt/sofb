#!/epics/iocs/srSOFB2/sofb2/bin/linux-x86_64/bump

## You may have to change bump to something else
## everywhere it appears in this file

#< envPaths

< /epics/iocs/srSOFB2/sofb2/iocBoot/iocbump/envPaths

epicsEnvSet("EPICS_CA_MAX_ARRAY_BYTES", "30000000")
epicsEnvSet("PYTHONPATH", "/epics/op/apps/aphla/lib/python")
epicsEnvSet("APHLA_CONFIG_DIR", "/epics/data/aphla/apconf")

#cd ${TOP}
#cd /direct/phy_iocs/srSOFB2/sofb2
cd /epics/iocs/srSOFB2/sofb2

## Register all support components
dbLoadDatabase("dbd/bump.dbd",0,0)
bump_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("db/bump.db","")

# check the following PVs from active interlock
# SR:C31-{AI}*Aie*:S1*
# SR:C31-{AI}*Aie*:S2*
# SR:C31-{AI}*Aie*:S3*

dbLoadRecords("db/localbump.db", "ID=C03-HXN,XY=X,HV=H,C1=03,I1=7,C2=03,I2=8,S1=-2.543,S2=0,S3=2.679")
dbLoadRecords("db/localbump.db", "ID=C03-HXN,XY=Y,HV=V,C1=03,I1=7,C2=03,I2=8,S1=-2.543,S2=0,S3=2.679")

dbLoadRecords("db/localbump.db", "ID=C04-ISR,XY=X,HV=H,C1=03,I1=6,C2=04,I2=1,S1=-2.25,S2=0,S3=7.6")
dbLoadRecords("db/localbump.db", "ID=C04-ISR,XY=Y,HV=V,C1=03,I1=6,C2=04,I2=1,S1=-2.25,S2=0,S3=7.6")

dbLoadRecords("db/localbump.db", "ID=C05u-SRX,XY=X,HV=H,C1=05,I1=7,C2=05,I2=8,S1=-1.304,S2=0,S3=1.304")
dbLoadRecords("db/localbump.db", "ID=C05u-SRX,XY=Y,HV=V,C1=05,I1=7,C2=05,I2=8,S1=-1.304,S2=0,S3=1.304")

dbLoadRecords("db/localbump.db", "ID=C05d-SRX,XY=X,HV=H,C1=05,I1=8,C2=05,I2=9,S1=-1.453,S2=0,S3=1.453")
dbLoadRecords("db/localbump.db", "ID=C05d-SRX,XY=Y,HV=V,C1=05,I1=8,C2=05,I2=9,S1=-1.453,S2=0,S3=1.453")

dbLoadRecords("db/localbump.db", "ID=C08-XPD,XY=X,HV=H,C1=08,I1=7,C2=08,I2=8,S1=-3.6695,S2=0,S3=3.6695")
dbLoadRecords("db/localbump.db", "ID=C08-XPD,XY=Y,HV=V,C1=08,I1=7,C2=08,I2=8,S1=-3.6695,S2=0,S3=3.6695")

dbLoadRecords("db/localbump.db", "ID=C10-IXS,XY=X,HV=H,C1=10,I1=7,C2=10,I2=8,S1=-3.898,S2=0,S3=4.029")
dbLoadRecords("db/localbump.db", "ID=C10-IXS,XY=Y,HV=V,C1=10,I1=7,C2=10,I2=8,S1=-3.898,S2=0,S3=4.029")

dbLoadRecords("db/localbump.db", "ID=C11-CHX,XY=X,HV=H,C1=11,I1=7,C2=11,I2=8,S1=-2.543,S2=0,S3=2.679")
dbLoadRecords("db/localbump.db", "ID=C11-CHX,XY=Y,HV=V,C1=11,I1=7,C2=11,I2=8,S1=-2.543,S2=0,S3=2.679")


dbLoadRecords("db/localbump.db", "ID=C16-LIX,XY=X,HV=H,C1=16,I1=7,C2=16,I2=8,S1=-2.071,S2=0,S3=2.071")
dbLoadRecords("db/localbump.db", "ID=C16-LIX,XY=Y,HV=V,C1=16,I1=7,C2=16,I2=8,S1=-2.071,S2=0,S3=2.071")

# This S1/S2/S3 just take C05 values, may not correct
dbLoadRecords("db/localbump.db", "ID=C17u-FMX,XY=X,HV=H,C1=17,I1=7,C2=17,I2=8,S1=-1.342,S2=0,S3=1.240")
dbLoadRecords("db/localbump.db", "ID=C17u-FMX,XY=Y,HV=V,C1=17,I1=7,C2=17,I2=8,S1=-1.342,S2=0,S3=1.240")

dbLoadRecords("db/localbump.db", "ID=C17d-AMX,XY=X,HV=H,C1=17,I1=8,C2=17,I2=9,S1=-1.3868,S2=0,S3=1.5192")
dbLoadRecords("db/localbump.db", "ID=C17d-AMX,XY=Y,HV=V,C1=17,I1=8,C2=17,I2=9,S1=-1.3868,S2=0,S3=1.5192")

dbLoadRecords("db/localbump.db", "ID=C18-XPD,XY=X,HV=H,C1=18,I1=7,C2=18,I2=8,S1=-3.6615,S2=0,S3=3.6775")
dbLoadRecords("db/localbump.db", "ID=C18-XPD,XY=Y,HV=V,C1=18,I1=7,C2=18,I2=8,S1=-3.6615,S2=0,S3=3.6775")

dbLoadRecords("db/localbump.db", "ID=C23u-CSX,XY=X,HV=H,C1=23,I1=7,C2=23,I2=8,S1=-2.553,S2=0,S3=1.238")
dbLoadRecords("db/localbump.db", "ID=C23u-CSX,XY=Y,HV=V,C1=23,I1=7,C2=23,I2=8,S1=-2.553,S2=0,S3=1.238")

dbLoadRecords("db/localbump.db", "ID=C23d-CSX,XY=X,HV=H,C1=23,I1=8,C2=23,I2=9,S1=-1.102,S2=0,S3=1.102")
dbLoadRecords("db/localbump.db", "ID=C23d-CSX,XY=Y,HV=V,C1=23,I1=8,C2=23,I2=9,S1=-1.102,S2=0,S3=1.102")

dbLoadRecords("db/localbump.db", "ID=C28-XPD,XY=X,HV=H,C1=28,I1=7,C2=28,I2=8,S1=-3.662,S2=0,S3=3.678")
dbLoadRecords("db/localbump.db", "ID=C28-XPD,XY=Y,HV=V,C1=28,I1=7,C2=28,I2=8,S1=-3.662,S2=0,S3=3.678")

#dbLoadRecords("db/localbump.db", "ID=C10-ISX,XY=X,HV=H,C1=10,I1=7,C2=10,I2=8,S1=-3.899,S2=0,S3=4.029")


set_savefile_path("/epics/iocs/srSOFB2/sofb2/as/bump","/save")
set_requestfile_path("/epics/iocs/srSOFB2/sofb2/as/bump","/req")
set_pass1_restoreFile("ioc_settings.sav")

asSetFilename("/cf-update/acf/default.acf")
 
iocInit()

caPutLogInit("ioclog.cs.nsls2.local:7004", 1)

makeAutosaveFileFromDbInfo("as/bump/req/ioc_settings.req", "autosaveFields_pass1")
create_monitor_set("ioc_settings.req", 30, "")

## Start any sequence programs
#seq sncbump,"user=lyyang"

system("python idlocalbump.py")

