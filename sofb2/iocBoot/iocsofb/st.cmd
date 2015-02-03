#!/epics/iocs/srSOFB2/sofb2/bin/linux-x86_64/sofb

## You may have to change sofb to something else
## everywhere it appears in this file

< /epics/iocs/srSOFB2/sofb2/iocBoot/iocsofb/envPaths

epicsEnvSet("EPICS_CA_MAX_ARRAY_BYTES", "30000000")

cd ${TOP}
cd /direct/phy_iocs/srSOFB2/sofb2

## Register all support components
dbLoadDatabase("dbd/sofb.dbd",0,0)
sofb_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("db/sofb.db","user=lyyang")
dbLoadRecords("db/bpmx0.db", "")
dbLoadRecords("db/bpmx.db", "")
dbLoadRecords("db/bpmy0.db", "")
dbLoadRecords("db/bpmy.db", "")

dbLoadRecords("db/bpm_sel.db", "XSel=XSel,T=CHAR")
dbLoadRecords("db/bpm_sel.db", "XSel=YSel,T=CHAR")

dbLoadRecords("db/corx_sp_merge.db", "")
dbLoadRecords("db/cory_sp_merge.db", "")
dbLoadRecords("db/corx_rb_merge.db", "")
dbLoadRecords("db/cory_rb_merge.db", "")
dbLoadRecords("db/cor_sel.db", "XSel=XSel,T=CHAR")
dbLoadRecords("db/cor_sel.db", "XSel=YSel,T=CHAR")
dbLoadRecords("db/corx_sp_split.db", "")
dbLoadRecords("db/cory_sp_split.db", "")

dbLoadRecords("db/orm.db", "")


iocInit()

## Start any sequence programs
#seq sncsofb,"user=lyyang"
