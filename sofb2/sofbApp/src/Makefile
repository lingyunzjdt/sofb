TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = sofb
# sofb.dbd will be created and installed
DBD += sofb.dbd

# sofb.dbd will be made up from these files:
sofb_DBD += base.dbd

# Include dbd files from all support applications:
sofb_DBD += aSubMergeSplit.dbd orbitCor.dbd
sofb_DBD += sofbLocalBump.dbd

sofb_DIR += /usr/lib
# Add all the support libraries needed by this IOC
#sofb_LIBS += xxx
sofb_SYS_LIBS += gsl gslcblas

# sofb_registerRecordDeviceDriver.cpp derives from sofb.dbd
sofb_SRCS += sofb_registerRecordDeviceDriver.cpp
sofb_SRCS += aSubMergeSplit.c orbitCor.c 
sofb_SRCS += sofbLocalBump.c

# Build the main IOC entry point on workstation OSs.
sofb_SRCS_DEFAULT += sofbMain.cpp
sofb_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#sofb_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
sofb_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

#sofb_INCLUDES += -I/usr/include

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

