# firmware

FIRMWARE_VERSION = 1.0.0
FIRMWARE_SOURCE = 
FIRMWARE_SITE  = 

FIRMWARE_LICENSE = 
FIRMWARE_LICENSE_FILES = README

FIRMWARE_MAINTAINED = YES
FIRMWARE_AUTORECONF = YES
FIRMWARE_INSTALL_STAGING = YES
FIRMWARE_DEPENDENCIES = host-pkgconf

# pakcage options
FIRMWARE_EXTRACT_CMDS = cp -pdrf $(FIRMWARE_PKGDIR)/* $(@D)


FIRMWARE_BUILD_CMDS = $(MAKE) -j1 -C $(@D) all

# install headers
define FIRMWARE_POST_INSTALL_STAGING_HEADERS
endef
FIRMWARE_POST_INSTALL_STAGING_HOOKS  += FIRMWARE_POST_INSTALL_STAGING_HEADERS
#FIRMWARE_POST_BUILD_HOOKS += 

$(eval $(generic-package))
