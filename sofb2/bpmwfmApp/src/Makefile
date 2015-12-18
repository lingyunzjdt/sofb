TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = bpmwfm
# bpmwfm.dbd will be created and installed
DBD += bpmwfm.dbd

# bpmwfm.dbd will be made up from these files:
bpmwfm_DBD += base.dbd

# Include dbd files from all support applications:
bpmwfm_DBD += asSupport.dbd
bpmwfm_DBD += calcSupport.dbd
bpmwfm_DBD += caPutLog.dbd # put logging
bpmwfm_DBD += aSubMergeSplit.dbd

# Add all the support libraries needed by this IOC
#bpmwfm_LIBS += xxx
bpmwfm_SYS_LIBS += gsl gslcblas

# bpmwfm_registerRecordDeviceDriver.cpp derives from bpmwfm.dbd
bpmwfm_SRCS += bpmwfm_registerRecordDeviceDriver.cpp
bpmwfm_SRCS += aSubMergeSplit.c

# Build the main IOC entry point on workstation OSs.
bpmwfm_SRCS_DEFAULT += bpmwfmMain.cpp
bpmwfm_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#bpmwfm_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
bpmwfm_LIBS += autosave calc caPutLog
bpmwfm_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

