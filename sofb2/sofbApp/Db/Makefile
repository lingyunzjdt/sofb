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
DB += bpmx0.db bpmy0.db bpmx.db bpmy.db bpm_sel.db

# correctors
DB += corx_sp_merge.db cory_sp_merge.db
DB += corx_rb_merge.db cory_rb_merge.db
DB += cor_sel.db
DB += corx_sp_split.db cory_sp_split.db
DB += orm.db

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

