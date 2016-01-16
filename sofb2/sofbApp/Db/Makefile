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
DB += sofb2_bpm_rb0.db sofb2_bpm_rb.db sofb2_bpm_sel.db sofb2_bpm_weight.db sofb2_bpm_ref.db

# correctors
#DB += corx_sp_merge.db cory_sp_merge.db
DB += sofb2_cor_sp_merge.db sofb2_cor_rb_merge.db
DB += sofb2_cor_sel.db
DB += sofb2_cor_sp_split.db
DB += sofb2_cor_delta.db
DB += sofb2_orm.db

DB += localbump.db

# can not be after RULES
DB_INSTALLS += $(EPICS_BASE)/db/iocAdminSoft.db

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

