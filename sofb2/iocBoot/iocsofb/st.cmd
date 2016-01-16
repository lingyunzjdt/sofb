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

dbLoadRecords("db/iocAdminSoft.db", "IOC=OP-APHLA{IOC:SOFB2}")
## Load record instances
#dbLoadRecords("db/sofb.db","user=lyyang")
#dbLoadRecords("db/sofb2_bpm_rb0.db", "XY=X")
#dbLoadRecords("db/sofb2_bpm_rb0.db", "XY=Y")
#dbLoadRecords("db/sofb2_bpm_rb.db", "XY=X")
#dbLoadRecords("db/sofb2_bpm_rb.db", "XY=Y")

dbLoadRecords("db/sofb2_bpm_sel.db", "XSel=XSel,T=CHAR")
dbLoadRecords("db/sofb2_bpm_sel.db", "XSel=YSel,T=CHAR")

dbLoadRecords("db/sofb2_bpm_weight.db", "XWeight=XWeight,T=DOUBLE")
dbLoadRecords("db/sofb2_bpm_weight.db", "XWeight=YWeight,T=DOUBLE")

dbLoadRecords("db/sofb2_bpm_ref.db", "WFM=Href,PFX=Pos:Href-SP")
dbLoadRecords("db/sofb2_bpm_ref.db", "WFM=Vref,PFX=Pos:Vref-SP")
dbLoadRecords("db/sofb2_bpm_ref.db", "WFM=UsrXref,PFX=Pos:UsrXoffset-SP")
dbLoadRecords("db/sofb2_bpm_ref.db", "WFM=UsrYref,PFX=Pos:UsrYoffset-SP")

dbLoadRecords("db/sofb2_cor_sp_merge.db", "PLN=X,SPi=Sp1,p=")
dbLoadRecords("db/sofb2_cor_sp_merge.db", "PLN=Y,SPi=Sp2,p=")
dbLoadRecords("db/sofb2_cor_rb_merge.db", "PLN=X,PSi=Ps1,p=")
dbLoadRecords("db/sofb2_cor_rb_merge.db", "PLN=Y,PSi=Ps2,p=")

dbLoadRecords("db/sofb2_cor_sel.db", "XSel=XSel,T=CHAR,Psi=Ps1,p=")
dbLoadRecords("db/sofb2_cor_sel.db", "XSel=YSel,T=CHAR,Psi=Ps2,p=")

dbLoadRecords("db/sofb2_cor_sp_split.db", "PLN=X,SPi=Sp1,p=")
dbLoadRecords("db/sofb2_cor_sp_split.db", "PLN=Y,SPi=Sp2,p=")

dbLoadRecords("db/sofb2_cor_delta.db", "Spi=Sp1,Psi=Ps1")
dbLoadRecords("db/sofb2_cor_delta.db", "Spi=Sp2,Psi=Ps2")
dbLoadRecords("db/sofb2_orm.db", "")

#dbLoadRecords("db/localbump.db", "ID=ISX,PL=X,L=7.928,OFST1L=SR:C10-BI{BPM:7}Pos:Href-SP,OFST1R=SR:C10-BI{BPM:8}Pos:Href-SP,OFST2L=SR:C10-BI{BPM:7}Pos:UsrXoffset-SP,OFST2R=SR:C10-BI{BPM:8}Pos:UsrXoffset-SP,X1=SR:C10-BI{BPM:7}Pos:XwUsrOff-Calc,X2=SR:C10-BI{BPM:8}Pos:XwUsrOff-Calc,X01=SR:C10-BI{BPM:7}Pos:X-I,X02=SR:C10-BI{BPM:8}Pos:X-I")

set_savefile_path("/epics/iocs/srSOFB2/sofb2/as/sofb","/save")
set_requestfile_path("/epics/iocs/srSOFB2/sofb2/as/sofb","/req")
set_pass1_restoreFile("ioc_settings.sav")

asSetFilename("/cf-update/acf/default.acf")

iocInit()

caPutLogInit("ioclog.cs.nsls2.local:7004", 1)
 
makeAutosaveFileFromDbInfo("as/sofb/req/ioc_settings.req", "autosaveFields_pass1")
create_monitor_set("ioc_settings.req", 30, "")

## Start any sequence programs
#seq sncsofb,"user=lyyang"
