include $(TOPDIR)/rules.mk

PKG_NAME:=tuya_daemon
PKG_RELEASE:=1
PKG_VERSION:=1.0.0

include $(INCLUDE_DIR)/package.mk

define Package/tuya_daemon
	CATEGORY:=Daemon Packages
	TITLE:=tuya_daemon
	DEPENDS:=+tuya-sdk +libubus +libblobmsg-json +libubox
endef

define Package/tuya_daemon/description
	Package for Tuya daemon 
endef



define Package/tuya_daemon/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tuya_daemon $(1)/usr/bin
	$(INSTALL_BIN) ./files/tuya_daemon.init $(1)/etc/init.d/tuya_daemon
	$(INSTALL_CONF) ./files/tuya_daemon.config $(1)/etc/config/tuya_daemon
endef

$(eval $(call BuildPackage,tuya_daemon))