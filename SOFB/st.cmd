#!./bin/linux-x86_64/SOFB

## You may have to change sToV to something else
## everywhere it appears in this file

< envPaths
epicsEnvSet("EPICS_CA_MAX_ARRAY_BYTES","900000")
epicsEnvSet("EPICS_CA_AUTO_ADDR_LIST","NO")
epicsEnvSet("EPICS_CA_ADDR_LIST","10.0.153.255")

cd ${TOP}

## Register all support components
dbLoadDatabase "dbd/SOFB.dbd"
SOFB_registerRecordDeviceDriver pdbbase

# don't need for real machine
#dbLoadTemplate ("db/vBPM.substitutions")   
# don't need for real machine
#dbLoadTemplate ("db/vCOR.substitutions")

dbLoadRecords ("db/SR.db")


#TimeDelay: 5/5/5

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C01,NEXTCELL=C02, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=1")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C02,NEXTCELL=C03, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=2")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C03,NEXTCELL=C04, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=3")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C04,NEXTCELL=C05, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=4")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C05,NEXTCELL=C06, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=5")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C06,NEXTCELL=C07, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=6")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C07,NEXTCELL=C08, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=7")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C08,NEXTCELL=C09, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=8")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C09,NEXTCELL=C10, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=9")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C10,NEXTCELL=C11, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=10")


dbLoadRecords ("db/COR.db", "SR=SR, CELL=C11,NEXTCELL=C12, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=11")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C12,NEXTCELL=C13, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=12")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C13,NEXTCELL=C14, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=13")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C14,NEXTCELL=C15, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=14")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C15,NEXTCELL=C16, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=15")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C16,NEXTCELL=C17, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=16")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C17,NEXTCELL=C18, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=17")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C18,NEXTCELL=C19, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=18")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C19,NEXTCELL=C20, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=19")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C20,NEXTCELL=C21, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=20")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C21,NEXTCELL=C22, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=21")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C22,NEXTCELL=C23, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=22")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C23,NEXTCELL=C24, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=23")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C24,NEXTCELL=C25, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=24")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C25,NEXTCELL=C26, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=25")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C26,NEXTCELL=C27, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=26")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C27,NEXTCELL=C28, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=27")
dbLoadRecords ("db/COR.db", "SR=SR, CELL=C28,NEXTCELL=C29, NEXTC1=CL1A, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=28")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C29,NEXTCELL=C30, NEXTC1=CH1A, C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH1B,C6=CH2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=29")

dbLoadRecords ("db/COR.db", "SR=SR, CELL=C30,NEXTCELL=C30, NEXTC1=CEND, C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL1B,C6=CL2B, T_Recover=.1,T_ORM_Ready=.4,T_ORM_Measure=.1,CellIndex=30")

dbLoadRecords ("db/BPM.db","SR=SR, CELL=C01")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C02")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C03")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C04")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C05")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C06")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C07")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C08")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C09")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C10")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C11")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C12")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C13")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C14")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C15")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C16")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C17")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C18")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C19")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C20")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C21")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C22")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C23")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C24")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C25")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C26")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C27")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C28")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C29")
dbLoadRecords ("db/BPM.db","SR=SR, CELL=C30")

# add support for user BPM, and append the results to RF BPM.
dbLoadRecords ("db/IDBPM.db","SR=SR")

dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C01")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C02")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C03")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C04")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C05")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C06")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C07")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C08")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C09")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C10")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C11")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C12")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C13")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C14")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C15")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C16")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C17")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C18")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C19")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C20")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C21")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C22")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C23")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C24")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C25")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C26")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C27")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C28")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C29")
dbLoadRecords ("db/InvalidInCell.db","SR=SR, CELL=C30")

dbLoadRecords ("db/InvalidIDBPMInCell.db","SR=SR")

dbLoadRecords ("db/Cell_Merge_BPM.db","SR=SR, TYPE=FLOAT,BPM=BPM, bpmMerge1=bpmMerge1,bpmMerge2=bpmMerge2,bpmMerge3=bpmMergeID, C01=C01,C02=C02,C03=C03,C04=C04,C05=C05,C06=C06,C07=C07,C08=C08,C09=C09,C10=C10, C11=C11,C12=C12,C13=C13,C14=C14,C15=C15,C16=C16,C17=C17,C18=C18,C19=C19,C20=C20, C21=C21,C22=C22,C23=C23,C24=C24,C25=C25,C26=C26,C27=C27,C28=C28,C29=C29,C30=C30,DATA=xORM, SIGNAL=xORM,SOFBRATE=2")

dbLoadRecords ("db/Cell_Merge_BPM.db","SR=SR, TYPE=FLOAT,BPM=BPM, bpmMerge1=bpmMerge1,bpmMerge2=bpmMerge2,bpmMerge3=bpmMergeID, C01=C01,C02=C02,C03=C03,C04=C04,C05=C05,C06=C06,C07=C07,C08=C08,C09=C09,C10=C10, C11=C11,C12=C12,C13=C13,C14=C14,C15=C15,C16=C16,C17=C17,C18=C18,C19=C19,C20=C20, C21=C21,C22=C22,C23=C23,C24=C24,C25=C25,C26=C26,C27=C27,C28=C28,C29=C29,C30=C30,DATA=yORM, SIGNAL=yORM,SOFBRATE=2")

dbLoadRecords ("db/Cell_Merge_BPM.db","SR=SR, TYPE=FLOAT,BPM=BPM, bpmMerge1=bpmMerge1,bpmMerge2=bpmMerge2,bpmMerge3=bpmMergeID, C01=C01,C02=C02,C03=C03,C04=C04,C05=C05,C06=C06,C07=C07,C08=C08,C09=C09,C10=C10, C11=C11,C12=C12,C13=C13,C14=C14,C15=C15,C16=C16,C17=C17,C18=C18,C19=C19,C20=C20, C21=C21,C22=C22,C23=C23,C24=C24,C25=C25,C26=C26,C27=C27,C28=C28,C29=C29,C30=C30,DATA=xSOFB, SIGNAL=xSOFB,SOFBRATE=2")

dbLoadRecords ("db/Cell_Merge_BPM.db","SR=SR, TYPE=FLOAT,BPM=BPM, bpmMerge1=bpmMerge1,bpmMerge2=bpmMerge2,bpmMerge3=bpmMergeID, C01=C01,C02=C02,C03=C03,C04=C04,C05=C05,C06=C06,C07=C07,C08=C08,C09=C09,C10=C10, C11=C11,C12=C12,C13=C13,C14=C14,C15=C15,C16=C16,C17=C17,C18=C18,C19=C19,C20=C20, C21=C21,C22=C22,C23=C23,C24=C24,C25=C25,C26=C26,C27=C27,C28=C28,C29=C29,C30=C30,DATA=ySOFB, SIGNAL=ySOFB,SOFBRATE=2")

dbLoadRecords ("db/Cell_Merge_BPM.db","SR=SR, TYPE=FLOAT,BPM=BPM, bpmMerge1=bpmMerge1,bpmMerge2=bpmMerge2,bpmMerge3=bpmMergeID, C01=C01,C02=C02,C03=C03,C04=C04,C05=C05,C06=C06,C07=C07,C08=C08,C09=C09,C10=C10, C11=C11,C12=C12,C13=C13,C14=C14,C15=C15,C16=C16,C17=C17,C18=C18,C19=C19,C20=C20, C21=C21,C22=C22,C23=C23,C24=C24,C25=C25,C26=C26,C27=C27,C28=C28,C29=C29,C30=C30,DATA=xSA, SIGNAL=X:SA-I,SOFBRATE=2")

dbLoadRecords ("db/Cell_Merge_BPM.db","SR=SR, TYPE=FLOAT,BPM=BPM, bpmMerge1=bpmMerge1,bpmMerge2=bpmMerge2,bpmMerge3=bpmMergeID, C01=C01,C02=C02,C03=C03,C04=C04,C05=C05,C06=C06,C07=C07,C08=C08,C09=C09,C10=C10, C11=C11,C12=C12,C13=C13,C14=C14,C15=C15,C16=C16,C17=C17,C18=C18,C19=C19,C20=C20, C21=C21,C22=C22,C23=C23,C24=C24,C25=C25,C26=C26,C27=C27,C28=C28,C29=C29,C30=C30,DATA=ySA, SIGNAL=Y:SA-I,SOFBRATE=2")

dbLoadRecords ("db/Cell_Merge_BPM.db","SR=SR, TYPE=CHAR, BPM=BPM,bpmMerge1=invalidMerge1,bpmMerge2=invalidMerge2,bpmMerge3=invalidMergeID, C01=C01,C02=C02,C03=C03,C04=C04,C05=C05,C06=C06,C07=C07,C08=C08,C09=C09,C10=C10, C11=C11,C12=C12,C13=C13,C14=C14,C15=C15,C16=C16,C17=C17,C18=C18,C19=C19,C20=C20, C21=C21,C22=C22,C23=C23,C24=C24,C25=C25,C26=C26,C27=C27,C28=C28,C29=C29,C30=C30,DATA=invalid,SIGNAL=XY,SOFBRATE=2")

dbLoadRecords ("db/Cell_Merge.db","SR=SR, TYPE=CHAR, BPM=COR,bpmMerge1=invalidMerge1,bpmMerge2=invalidMerge2, C01=C01,C02=C02,C03=C03,C04=C04,C05=C05,C06=C06,C07=C07,C08=C08,C09=C09,C10=C10, C11=C11,C12=C12,C13=C13,C14=C14,C15=C15,C16=C16,C17=C17,C18=C18,C19=C19,C20=C20, C21=C21,C22=C22,C23=C23,C24=C24,C25=C25,C26=C26,C27=C27,C28=C28,C29=C29,C30=C30,DATA=invalid,SIGNAL=HV,SOFBRATE=2")

## Add Sum
dbLoadRecords ("db/Cell_Merge_BPM.db","SR=SR, TYPE=FLOAT,BPM=BPM, bpmMerge1=bpmMerge1,bpmMerge2=bpmMerge2,bpmMerge3=bpmMergeID,C01=C01,C02=C02,C03=C03,C04=C04,C05=C05,C06=C06,C07=C07,C08=C08,C09=C09,C10=C10, C11=C11,C12=C12,C13=C13,C14=C14,C15=C15,C16=C16,C17=C17,C18=C18,C19=C19,C20=C20, C21=C21,C22=C22,C23=C23,C24=C24,C25=C25,C26=C26,C27=C27,C28=C28,C29=C29,C30=C30,DATA=SumSA, SIGNAL=Sum:SA-I,SOFBRATE=2")


dbLoadRecords ("db/BPM_Cycle.db","SR=SR, CELL_1ST=C01")

# test orbit first
#dbLoadRecords ("db/Orb_Merge.db","SR=SR, DATA=ORM, DATA1=xORM, DATA2=yORM")
#dbLoadRecords ("db/Orb_Merge.db","SR=SR, DATA=SOFB, DATA1=xSOFB, DATA2=ySOFB")
#dbLoadRecords ("db/Orb_Merge.db","SR=SR, DATA=SA, DATA1=xSA, DATA2=ySA")

dbLoadRecords ("db/ORM.db","SR=SR")
dbLoadRecords ("db/SOFB_SP.db","SR=SR")


############## Add Cor SP #######################
dbLoadRecords ("db/CorSP.db","SR=SR,SIG1=I:Sp1-SP,SIG2=I:Sp2-SP,CG=CG1,CGNEXT=CG2,CL1=C01-MG,CL2=C02-MG,CL3=C03-MG,PS=PS:,C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH2B,C6=CH1B,C7=CH1A,C8=CH2A,C9=CM1A,C10=CM1B,C11=CL2B,C12=CL1B,C13=CL1A,C14=CL2A,C15=CM1A,C16=CM1B,C17=CH2B,C18=CH1B,"}

dbLoadRecords ("db/CorSP.db","SR=SR,SIG1=I:Sp1-SP,SIG2=I:Sp2-SP,CG=CG2,CGNEXT=CG3,CL1=C04-MG,CL2=C05-MG,CL3=C06-MG,PS=PS:,C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL2B,C6=CL1B,C7=CL1A,C8=CL2A,C9=CM1A,C10=CM1B,C11=CH2B,C12=CH1B,C13=CH1A,C14=CH2A,C15=CM1A,C16=CM1B,C17=CL2B,C18=CL1B,"}

dbLoadRecords ("db/CorSP.db","SR=SR,SIG1=I:Sp1-SP,SIG2=I:Sp2-SP,CG=CG3,CGNEXT=CG4,CL1=C07-MG,CL2=C08-MG,CL3=C09-MG,PS=PS:,C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH2B,C6=CH1B,C7=CH1A,C8=CH2A,C9=CM1A,C10=CM1B,C11=CL2B,C12=CL1B,C13=CL1A,C14=CL2A,C15=CM1A,C16=CM1B,C17=CH2B,C18=CH1B,"}

dbLoadRecords ("db/CorSP.db","SR=SR,SIG1=I:Sp1-SP,SIG2=I:Sp2-SP,CG=CG4,CGNEXT=CG5,CL1=C10-MG,CL2=C11-MG,CL3=C12-MG,PS=PS:,C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL2B,C6=CL1B,C7=CL1A,C8=CL2A,C9=CM1A,C10=CM1B,C11=CH2B,C12=CH1B,C13=CH1A,C14=CH2A,C15=CM1A,C16=CM1B,C17=CL2B,C18=CL1B,"}

dbLoadRecords ("db/CorSP.db","SR=SR,SIG1=I:Sp1-SP,SIG2=I:Sp2-SP,CG=CG5,CGNEXT=CG6,CL1=C13-MG,CL2=C14-MG,CL3=C15-MG,PS=PS:,C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH2B,C6=CH1B,C7=CH1A,C8=CH2A,C9=CM1A,C10=CM1B,C11=CL2B,C12=CL1B,C13=CL1A,C14=CL2A,C15=CM1A,C16=CM1B,C17=CH2B,C18=CH1B,"}

dbLoadRecords ("db/CorSP.db","SR=SR,SIG1=I:Sp1-SP,SIG2=I:Sp2-SP,CG=CG6,CGNEXT=CG7,CL1=C16-MG,CL2=C17-MG,CL3=C18-MG,PS=PS:,C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL2B,C6=CL1B,C7=CL1A,C8=CL2A,C9=CM1A,C10=CM1B,C11=CH2B,C12=CH1B,C13=CH1A,C14=CH2A,C15=CM1A,C16=CM1B,C17=CL2B,C18=CL1B,"}

dbLoadRecords ("db/CorSP.db","SR=SR,SIG1=I:Sp1-SP,SIG2=I:Sp2-SP,CG=CG7,CGNEXT=CG8,CL1=C19-MG,CL2=C20-MG,CL3=C21-MG,PS=PS:,C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH2B,C6=CH1B,C7=CH1A,C8=CH2A,C9=CM1A,C10=CM1B,C11=CL2B,C12=CL1B,C13=CL1A,C14=CL2A,C15=CM1A,C16=CM1B,C17=CH2B,C18=CH1B,"}

dbLoadRecords ("db/CorSP.db","SR=SR,SIG1=I:Sp1-SP,SIG2=I:Sp2-SP,CG=CG8,CGNEXT=CG9,CL1=C22-MG,CL2=C23-MG,CL3=C24-MG,PS=PS:,C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL2B,C6=CL1B,C7=CL1A,C8=CL2A,C9=CM1A,C10=CM1B,C11=CH2B,C12=CH1B,C13=CH1A,C14=CH2A,C15=CM1A,C16=CM1B,C17=CL2B,C18=CL1B,"}

dbLoadRecords ("db/CorSP.db","SR=SR,SIG1=I:Sp1-SP,SIG2=I:Sp2-SP,CG=CG9,CGNEXT=CG10,CL1=C25-MG,CL2=C26-MG,CL3=C27-MG,PS=PS:,C1=CL1A,C2=CL2A,C3=CM1A,C4=CM1B,C5=CH2B,C6=CH1B,C7=CH1A,C8=CH2A,C9=CM1A,C10=CM1B,C11=CL2B,C12=CL1B,C13=CL1A,C14=CL2A,C15=CM1A,C16=CM1B,C17=CH2B,C18=CH1B,"}

dbLoadRecords ("db/CorSP.db","SR=SR,SIG1=I:Sp1-SP,SIG2=I:Sp2-SP,CG=CG10,CGNEXT=CGEND,CL1=C28-MG,CL2=C29-MG,CL3=C30-MG,PS=PS:,C1=CH1A,C2=CH2A,C3=CM1A,C4=CM1B,C5=CL2B,C6=CL1B,C7=CL1A,C8=CL2A,C9=CM1A,C10=CM1B,C11=CH2B,C12=CH1B,C13=CH1A,C14=CH2A,C15=CM1A,C16=CM1B,C17=CL2B,C18=CL1B,"}

## Merger
dbLoadRecords ("db/CorSP_Merger.db","SR=SR,SIG1=I:Sp1-SP,SIG2=I:Sp2-SP,SIG12=I:Sp1_2-SP,CG1=CG1,CG2=CG2,CG3=CG3,CG4=CG4,CG5=CG5,CG6=CG6,CG7=CG7,CG8=CG8,CG9=CG9,CG10=CG10,CGEND=CGEND,"}



asSetFilename("/cf-update/acf/default.acf")

cd ${TOP}/iocBoot/${IOC}
iocInit

epicsThreadSleep 1
seq sofbST, "ORMStart=SR-SOFB{ORM}ORMStart.VAL, ORM1stKick=SR:C01-SOFB{PS:CL1A-1}LatchSp.PROC"
epicsThreadSleep 1
seqShow sofbST

