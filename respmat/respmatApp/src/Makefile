TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#=============================
# Build the IOC support library

LIBRARY_IOC += respmatSupport

# xxxRecord.h will be created from xxxRecord.dbd
DBDINC += xxxRecord
# Install devXxxSoft.dbd into <top>/dbd
DBD += xxxSupport.dbd

# Compile and add the code to the support library
respmatSupport_SRCS += xxxRecord.c
respmatSupport_SRCS += devXxxSoft.c

# Link locally-provided code into the support library,
# rather than directly into the IOC application.
respmatSupport_SRCS += dbSubExample.c
respmatSupport_SRCS += respmatHello.c
respmatSupport_SRCS += initTrace.c

respmatSupport_LIBS += $(EPICS_BASE_IOC_LIBS)

#=============================
# Build the IOC application

PROD_IOC = respmat
# respmat.dbd will be created and installed
DBD += respmat.dbd

# respmat.dbd will be made up from these files:
respmat_DBD += base.dbd
respmat_DBD += xxxSupport.dbd
respmat_DBD += dbSubExample.dbd
respmat_DBD += respmatHello.dbd
respmat_DBD += initTrace.dbd

# respmat_registerRecordDeviceDriver.cpp derives from respmat.dbd
respmat_SRCS += respmat_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
respmat_SRCS_DEFAULT += respmatMain.cpp
respmat_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#respmat_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Link in the code from the support library
respmat_LIBS += respmatSupport

# NOTE: To build SNL programs, SNCSEQ must be defined
# in the <top>/configure/RELEASE file

ifneq ($(SNCSEQ),)
    # Build sncExample into respmatSupport
    sncExample_SNCFLAGS += +r
    respmat_DBD += sncExample.dbd
    respmatSupport_SRCS += sncExample.stt
    respmatSupport_LIBS += seq pv
    respmat_LIBS += seq pv

    # Build sncProgram as a standalone program
    PROD_HOST += sncProgram
    sncProgram_SNCFLAGS += +m
    sncProgram_SRCS += sncProgram.st
    sncProgram_LIBS += seq pv
    sncProgram_LIBS += $(EPICS_BASE_HOST_LIBS)
endif

# Finally link to the EPICS Base libraries
respmat_LIBS += $(EPICS_BASE_IOC_LIBS)

#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

