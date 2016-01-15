#!/home/lyyang/sofb/sofb2/bin/linux-x86_64/corwfm
#!/epics/iocs/srSOFB2/sofb2/bin/linux-x86_64/corwfm

## You may have to change corwfm to something else
## everywhere it appears in this file

epicsEnvSet("ENGINEER","lyyang x4692")

#< envPaths
< /epics/iocs/srSOFB2/sofb2/iocBoot/ioccorwfm/envPaths

#cd ${TOP}
#cd /direct/phy_iocs/srSOFB2/sofb2
cd /home/lyyang/sofb/sofb2

## Register all support components
dbLoadDatabase("dbd/corwfm.dbd",0,0)
corwfm_registerRecordDeviceDriver(pdbbase) 

dbLoadRecords("db/iocAdminSoft.db", "IOC=OP-APHLA{IOC:corwfm}")

## Load record instances
#dbLoadRecords("db/corwfm.db","user=lyyang")
##dbLoadRecords("db/cor_rb_merge.db", "p=l:,PLN=X,PSi=Ps1")
##dbLoadRecords("db/cor_rb_merge.db", "p=l:,PLN=Y,PSi=Ps2")
dbLoadRecords("db/cor_wfm_merge.db", "p=l:,SYS=SR,FLD=I:Ps1DCCT1-I,XSel=Ps1DCCT1,T=DOUBLE")
dbLoadRecords("db/cor_wfm_merge.db", "p=l:,SYS=SR,FLD=I:Ps2DCCT1-I,XSel=Ps2DCCT1,T=DOUBLE")

##dbLoadRecords("db/cor_sp_merge.db", "p=l:,PLN=X,SPi=Sp1")
##dbLoadRecords("db/cor_sp_merge.db", "p=l:,PLN=Y,SPi=Sp2")
dbLoadRecords("db/cor_wfm_merge.db", "p=l:,SYS=SR,FLD=I:Sp1-SP,XSel=Sp1,T=DOUBLE")
dbLoadRecords("db/cor_wfm_merge.db", "p=l:,SYS=SR,FLD=I:Sp2-SP,XSel=Sp2,T=DOUBLE")

dbLoadRecords("db/cor_wfm_merge.db", "p=l:,SYS=SR,FLD=Enbl:Ps1OC-Cmd,XSel=XSel,T=CHAR")
dbLoadRecords("db/cor_wfm_merge.db", "p=l:,SYS=SR,FLD=Enbl:Ps2OC-Cmd,XSel=YSel,T=CHAR")

#dbLoadRecords("db/cor_sp_split.db", "p=l:,PLN=X,SPi=Sp1")
#dbLoadRecords("db/cor_sp_split.db", "p=l:,PLN=Y,SPi=Sp2")
#dbLoadRecords("db/cor_wfm_split.db", "p=l:,FLD=I:Sp1-SP,OSGNL=Sp1-Calc,T=DOUBLE")
#dbLoadRecords("db/cor_wfm_split.db", "p=l:,FLD=I:Sp2-SP,OSGNL=Sp2-Calc,T=DOUBLE")

dbLoadRecords("db/cor_test.db", "p=l:,pt=l:,SGNL=Sp1")
dbLoadRecords("db/cor_test.db", "p=l:,pt=l:,SGNL=Sp2")

dbLoadRecords("db/cor_masp_split.db", "p=l:,pt=,SGNL=I:Sp1-SP,FLD=I:Sp1")

#dbLoadRecords("db/cor.db", "p=l:,T=CHAR")

set_savefile_path("as/corwfm","/save")
set_requestfile_path("as/corwfm","/req")
set_pass1_restoreFile("ioc_settings.sav")

asSetFilename("/cf-update/acf/default.acf")

iocInit()

caPutLogInit("ioclog.cs.nsls2.local:7004", 1)
 
makeAutosaveFileFromDbInfo("as/corwfm/req/ioc_settings.req", "autosaveFields_pass1")
create_monitor_set("ioc_settings.req", 30, "")

## Start any sequence programs
#seq snccorwfm,"user=lyyang"
