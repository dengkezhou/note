__LIBS := $(addprefix $(OBJTREE)/built_archives/,$(libs-y))
__NAME := $(basename $(BINARY))

all: $(BINARY)

$(BINARY): $(__LIBS) $(LINKERFILE_DST) 
	@INITCALL=`$(OBJDUMP) -x $(__LIBS) | \
			 sed  -n -e 's/.*\(__initcall_.*\)/-u\1/p'|sort|uniq`;\
			 cd $(OBJTREE) && $(CC) -o $(OBJTREE)/$@ $(LDFLAGS) \
			 -Wl,-Map=$(OBJTREE)/$(__NAME).map \
				$$INITCALL -Wl,--start-group $(__LIBS) \
			 -lgcc -Wl,--end-group  || exit 1
	 @$(OBJCOPY) --gap-fill=0xff -O binary $(OBJTREE)/$@ $(OBJTREE)/$(__NAME).bin
	 @$(OBJCOPY) -O srec $(OBJTREE)/$(__NAME).elf $(OBJTREE)/$(__NAME).hex
	 @$(OBJDUMP) $(OBJTREE)/$@ -dl > $(OBJTREE)/$(__NAME).S
	 @ls $(OBJTREE)/$(__NAME).bin -lh | awk '{print "      $@ ("$$5") is ready!"}'

$(LINKERFILE_DST): $(LINKERFILE_SRC) $(FORCE) $(PLATFORM_HEAD)
	@$(CC) $(CUSTOM_AFLAGS) $(AFLAGS) -P -E -o $@ $<
	@echo "      $(TARGET) linkerfile updated!"
