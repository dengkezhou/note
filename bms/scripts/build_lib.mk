
ifneq ($(CUSTOM_RP),)
C_SRCS := $(addprefix $(SRCTREE)/$(CUSTOM_RP)/,$(filter %.c,$(SRCS)))
S_SRCS := $(addprefix $(SRCTREE)/$(CUSTOM_RP)/,$(filter %.S,$(SRCS)))
else
C_SRCS := $(addprefix $(CURDIR)/,$(filter %.c,$(SRCS)))
S_SRCS := $(addprefix $(CURDIR)/,$(filter %.S,$(SRCS)))
endif

C_OBJS := $(subst .c,.o,$(subst $(SRCTREE),$(OBJTREE),$(C_SRCS)))
S_OBJS := $(subst .S,.o,$(subst $(SRCTREE),$(OBJTREE),$(S_SRCS)))

OBJS := $(C_OBJS) $(S_OBJS)
DEPS := $(subst $(SRCTREE),$(OBJTREE),$(addsuffix .d,$(C_SRCS) $(S_SRCS)))
ARCHIVE := $(addprefix $(OBJTREE)/built_archives/,$(ARCHIVE))

all: $(DEPS) $(ARCHIVE)

$(DEPS): $(FORCE)
	$(shell mkdir -p $(dir $@))
	$(CC) -M $(CUSTOM_CFLAGS) $(CFLAGS) -MQ $(subst .c.d,.o,$(subst .S.d,.o,$@)) \
		 $(subst $(OBJTREE),$(SRCTREE),$(subst .d,,$@)) > $@

$(ARCHIVE): $(OBJS)
	$(if $(findstring $(notdir $(ARCHIVE)), $(DELBFCRTA)),rm -rf $(ARCHIVE),)
	$(AR) $(ARFLAGS) $@ $(OBJS)

sinclude $(DEPS)

$(S_OBJS):
	@echo "  s | $(subst $(SRCTREE)/,,$<)"
	@mkdir -p $(dir $@)
	$(CC) -c $(CUSTOM_AFLAGS) $(AFLAGS) $(subst $(OBJTREE),$(SRCTREE),$(subst .o,.S,$@)) -o $@

$(C_OBJS):
	@echo "  c | $(subst $(SRCTREE)/,,$<)"
	@mkdir -p $(dir $@)
	$(CC) -c $(CUSTOM_CFLAGS) $(CFLAGS) $(subst $(OBJTREE),$(SRCTREE),$(subst .o,.c,$@)) -o $@

