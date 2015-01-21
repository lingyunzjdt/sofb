TOP=../..

include $(TOP)/configure/CONFIG
#=============================
# Build the IOC application
PROD_IOC = SOFB
# SOFB.dbd will be created and installed
DBD += SOFB.dbd

# SOFB.dbd will be made up from these files:
SOFB_DBD += base.dbd
SOFB_DBD += aSubOperations.dbd
SOFB_DBD += system.dbd

# SOFB_registerRecordDeviceDriver.cpp derives from SOFB.dbd
SOFB_SRCS += SOFB_registerRecordDeviceDriver.cpp
SOFB_SRCS += aSubOperations.c

SOFB_SRCS += SOFB.st

# Build the main IOC entry point on workstation OSs.
SOFB_SRCS_DEFAULT += SOFBMain.cpp
SOFB_SRCS_vxWorks += -nil-

SOFB_LIBS += asyn
SOFB_LIBS += seq pv
SOFB_LIBS += devIocStats

# Finally link to the EPICS Base libraries
SOFB_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================
include $(TOP)/configure/RULES
