################################################################################
#
# multibutton
#
################################################################################

MULTIBUTTON_VERSION = 1.0
MULTIBUTTON_SITE = $(BR2_EXTERNAL_AURA_PATH)/package/multibutton/src
MULTIBUTTON_SITE_METHOD = local

define MULTIBUTTON_BUILD_CMDS
    $(MAKE) CC="$(TARGET_CC)" -C $(@D)
endef

define MULTIBUTTON_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/multibutton $(TARGET_DIR)/usr/bin/multibutton
endef

define MULTIBUTTON_INSTALL_INIT_SYSTEMD
	$(INSTALL) -D -m 0644 $(BR2_EXTERNAL_AURA_PATH)/package/multibutton/multibutton.service \
		$(TARGET_DIR)/usr/lib/systemd/system/multibutton.service
endef


$(eval $(generic-package))
