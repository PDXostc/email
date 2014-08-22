PROJECT = Email
INSTALL_FILES = $(PROJECT).wgt

VERSION := 0.0.1
PACKAGE = $(PROJECT)-$(VERSION)

INSTALL_DIR = $(DESTDIR)/opt/usr/apps/.preinstallWidgets

dev: 	clean dev-common
	zip -r $(PROJECT).wgt config.xml css icon.png index.html js images components

all:
	@echo "Nothing to build"

wgtPkg:	common 
	zip -r $(INSTALL_FILES) config.xml css icon.png index.html js images components

clean:
	rm -rf js/services
	rm -rf css/car
	rm -rf css/user
	rm -f $(PROJECT).wgt

common: /opt/usr/apps/common
	cp -r /opt/usr/apps/common/js/* js/
	cp -r /opt/usr/apps/common/css/* css/

/opt/usr/apps/common:
	echo "Please install Common Assets"
	exit 1

dev-common: 
	cp -r ../../common/js/* js/
	cp -r ../../common/css/* css/

install:
	@echo "Installing $(PROJECT), stand by..."
	mkdir -p $(INSTALL_DIR)/
	cp $(INSTALL_FILES) $(INSTALL_DIR)/

dist:
	tar czf ../$(PROJECT).tar.bz2 .
