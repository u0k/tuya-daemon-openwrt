include $(TOPDIR)/rules.mk

PKG_NAME:=tuya-sdk
PKG_RELEASE:=1
PKG_VERSION:=1.0.0
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/tuya/tuya-iot-core-sdk.git
PKG_SOURCE_VERSION:=0208badefb2003d30e70b5b875395e3187c850d9

CMAKE_BINARY_SUBDIR:=build
CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/tuya-sdk
	CATEGORY:=Daemon Packages
	TITLE:=tuya-sdk
endef

define Package/tuya-sdk/description
	Remote package for Tuya SDK
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib $(1)/usr/include
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/*.so $(1)/usr/lib/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/include/*.h $(1)/usr/include/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/interface/*.h $(1)/usr/include/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/utils/*.h $(1)/usr/include/
endef

define Package/tuya-sdk/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/*.so $(1)/usr/lib/
endef

define Build/Prepare
	@mkdir -p $(PKG_BUILD_DIR)/build
	$(call Build/Prepare/Default)
endef

$(eval $(call BuildPackage,tuya-sdk))
