TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
#  Optimization of db files using dbst (DEFAULT: NO)
#DB_OPT = YES

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this
DB += bpmwfm.db bpmshuffle.db
DB += bpmwfm_merge.db bpmwfm_compress.db

#ifneq ($(DEVIOCSTATS),)
## see /usr/lib/epics/db/iocAdminSoft.db
#DB_INSTALLS += $(DEVIOCSTATS)/db/iocAdminSoft.db
#endif

#ifneq ($(AUTOSAVE),)
#DB_INSTALLS += $(AUTOSAVE)/db/save_restoreStatus.db
#endif


#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

