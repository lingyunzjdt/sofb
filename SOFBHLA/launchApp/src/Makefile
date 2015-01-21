TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================


LIBRARY_IOC = elaunch
DBD += elaunchSupport.dbd

elaunch_SRCS += launcher.c

#=============================
# Build the IOC application

PROD_IOC = scriptlaunch

DBD += scriptlaunch.dbd

# launch.dbd will be made up from these files:
scriptlaunch_DBD += base.dbd
scriptlaunch_DBD += elaunchSupport.dbd
scriptlaunch_DBD += asSupport.dbd
scriptlaunch_DBD += devIocStats.dbd
scriptlaunch_DBD += calcSupport.dbd
scriptlaunch_DBD += sscanSupport.dbd
scriptlaunch_DBD += busySupport.dbd
scriptlaunch_DBD += system.dbd

scriptlaunch_LIBS += elaunch
scriptlaunch_LIBS += autosave devIocStats calc sscan busy asyn

# launch_registerRecordDeviceDriver.cpp derives from launch.dbd
scriptlaunch_SRCS += scriptlaunch_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
scriptlaunch_SRCS_DEFAULT += launchMain.cpp
scriptlaunch_SRCS_vxWorks += -nil-

# Finally link to the EPICS Base libraries
scriptlaunch_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

