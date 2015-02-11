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
#dbLoadRecords("db/sofb.db","user=lyyang")
dbLoadRecords("db/bpmx0.db", "")
dbLoadRecords("db/bpmx.db", "")
dbLoadRecords("db/bpmy0.db", "")
dbLoadRecords("db/bpmy.db", "")

dbLoadRecords("db/bpm_sel.db", "XSel=XSel,T=CHAR")
dbLoadRecords("db/bpm_sel.db", "XSel=YSel,T=CHAR")

dbLoadRecords("db/bpm_weight.db", "XWeight=XWeight,T=DOUBLE")
dbLoadRecords("db/bpm_weight.db", "XWeight=YWeight,T=DOUBLE")

#dbLoadRecords("db/corx_sp_merge.db", "")
#dbLoadRecords("db/cory_sp_merge.db", "")
dbLoadRecords("db/cor_sp_merge.db", "PLN=X,SPi=Sp1")
dbLoadRecords("db/cor_sp_merge.db", "PLN=Y,SPi=Sp2")
#dbLoadRecords("db/corx_rb_merge.db", "")
#dbLoadRecords("db/cory_rb_merge.db", "")
dbLoadRecords("db/cor_rb_merge.db", "PLN=X,PSi=Ps1")
dbLoadRecords("db/cor_rb_merge.db", "PLN=Y,PSi=Ps2")
dbLoadRecords("db/cor_sel.db", "XSel=XSel,T=CHAR")
dbLoadRecords("db/cor_sel.db", "XSel=YSel,T=CHAR")
#dbLoadRecords("db/corx_sp_split.db", "")
#dbLoadRecords("db/cory_sp_split.db", "")

dbLoadRecords("db/cor_sp_split.db", "PLN=X,SPi=Sp1")
dbLoadRecords("db/cor_sp_split.db", "PLN=Y,SPi=Sp2")


dbLoadRecords("db/orm.db", "")

#dbLoadRecords("db/localbump.db", "ID=ISX,PL=X,L=7.928,OFST1L=SR:C10-BI{BPM:7}Pos:Href-SP,OFST1R=SR:C10-BI{BPM:8}Pos:Href-SP,OFST2L=SR:C10-BI{BPM:7}Pos:UsrXoffset-SP,OFST2R=SR:C10-BI{BPM:8}Pos:UsrXoffset-SP,X1=SR:C10-BI{BPM:7}Pos:XwUsrOff-Calc,X2=SR:C10-BI{BPM:8}Pos:XwUsrOff-Calc,X01=SR:C10-BI{BPM:7}Pos:X-I,X02=SR:C10-BI{BPM:8}Pos:X-I")

set_savefile_path("/epics/iocs/srSOFB2/sofb2/as","/save")
set_requestfile_path("/epics/iocs/srSOFB2/sofb2/as","/req")
set_pass1_restoreFile("ioc_settings.sav")

iocInit()

makeAutosaveFileFromDbInfo("as/req/ioc_settings.req", "autosaveFields_pass1")
create_monitor_set("ioc_settings.req", 30, "")

## Start any sequence programs
#seq sncsofb,"user=lyyang"
