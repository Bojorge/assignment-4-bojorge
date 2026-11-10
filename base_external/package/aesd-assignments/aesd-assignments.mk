##############################################################
#
# AESD-ASSIGNMENTS
#
##############################################################

# Use the main branch (or you can use the hash of the last commit from the Task 3)
AESD_ASSIGNMENTS_VERSION = main
# SSH URL for assignment 3 repository
AESD_ASSIGNMENTS_SITE = git@github.com:Bojorge/assignment-3-bojorge.git
AESD_ASSIGNMENTS_SITE_METHOD = git
AESD_ASSIGNMENTS_GIT_SUBMODULES = YES

# TARGET_CONFIGURE_OPTS is an excellent Buildroot variable that passes 
# all the cross-compiler flags (CC, CFLAGS, LDFLAGS, etc.) to your Makefile
define AESD_ASSIGNMENTS_BUILD_CMDS
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D)/finder-app all
endef

# Install binaries in /usr/bin and configurations in /etc
define AESD_ASSIGNMENTS_INSTALL_TARGET_CMDS
	# 1. Install binaries and scripts in /usr/bin
	$(INSTALL) -D -m 0755 $(@D)/finder-app/writer $(TARGET_DIR)/usr/bin/writer
	$(INSTALL) -D -m 0755 $(@D)/finder-app/finder.sh $(TARGET_DIR)/usr/bin/finder.sh
	$(INSTALL) -D -m 0755 $(@D)/finder-app/finder-test.sh $(TARGET_DIR)/usr/bin/finder-test.sh
	
	# 2. Create the configuration directory and install the config files
	$(INSTALL) -d -m 0755 $(TARGET_DIR)/etc/finder-app/conf/
	$(INSTALL) -m 0644 $(@D)/conf/* $(TARGET_DIR)/etc/finder-app/conf/
endef

$(eval $(generic-package))
