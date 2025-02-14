SUBDIRS := $(sort $(subdirs-y))
FINALDIRS := $(sort $(finaldirs-y))

all: $(SUBDIRS) $(FINALDIRS)

$(SUBDIRS): $(FORCE)
	@mkdir -p ${OUTPUT}/$@
	@$(MAKE) -f $(SRCTREE)/scripts/build_makefile.mk -C $@ OUTPUT=$(OUTPUT)/$@

$(FINALDIRS): $(FORCE) $(SUBDIRS)
	@mkdir -p ${OUTPUT}/$@
	@$(MAKE) -f $(SRCTREE)/scripts/build_makefile.mk -C $@ OUTPUT=$(OUTPUT)/$@

