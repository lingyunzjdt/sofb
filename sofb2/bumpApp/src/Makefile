TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = bump
# bump.dbd will be created and installed
DBD += bump.dbd

# bump.dbd will be made up from these files:
bump_DBD += base.dbd system.dbd asSupport.dbd caPutLog.dbd

# Include dbd files from all support applications:
#bump_DBD += xxx.dbd
#bump_DBD += sofbLocalBump.dbd
bump_DBD += sofbLocalBump.dbd

# Add all the support libraries needed by this IOC
#bump_LIBS += xxx

# bump_registerRecordDeviceDriver.cpp derives from bump.dbd
bump_SRCS += bump_registerRecordDeviceDriver.cpp
bump_SRCS += sofbLocalBump.c

# Build the main IOC entry point on workstation OSs.
bump_SRCS_DEFAULT += bumpMain.cpp
bump_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#bump_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
bump_LIBS += autosave calc caPutLog
bump_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

