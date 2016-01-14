TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = corwfm
# corwfm.dbd will be created and installed
DBD += corwfm.dbd

# corwfm.dbd will be made up from these files:
corwfm_DBD += base.dbd

# Include dbd files from all support applications:
corwfm_DBD += asSupport.dbd
corwfm_DBD += calcSupport.dbd
corwfm_DBD += caPutLog.dbd # put logging
corwfm_DBD += aSubMergeSplit.dbd
corwfm_DBD += iocAdmin.dbd

# Add all the support libraries needed by this IOC
#corwfm_LIBS += xxx

# add aSub from lib
SRC_DIRS += $(TOP)/src
corwfm_SRCS += aSubLib.c

# corwfm_registerRecordDeviceDriver.cpp derives from corwfm.dbd
corwfm_SRCS += corwfm_registerRecordDeviceDriver.cpp
##corwfm_SRCS += aSubMergeSplit.c

# Build the main IOC entry point on workstation OSs.
corwfm_SRCS_DEFAULT += corwfmMain.cpp
corwfm_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#corwfm_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
corwfm_LIBS += autosave calc caPutLog devIocStats
corwfm_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

