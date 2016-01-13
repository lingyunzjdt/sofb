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
DB += bpm_rb0.db bpm_rb.db bpm_sel.db bpm_weight.db bpm_ref.db

# correctors
#DB += corx_sp_merge.db cory_sp_merge.db
DB += cor_sp_merge.db cor_rb_merge.db
#DB += cor_sel.db
DB += cor_sp_split.db
DB += orm.db

DB += localbump.db

# can not be after RULES
DB_INSTALLS += $(EPICS_BASE)/db/iocAdminSoft.db

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

