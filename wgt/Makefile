PROJECT = Email
INSTALL_FILES = $(PROJECT).wgt

VERSION := 0.0.1
PACKAGE = $(PROJECT)-$(VERSION)

INSTALL_DIR = $(DESTDIR)/opt/usr/apps/.preinstallWidgets

dev: dev-common
	zip -r $(PROJECT). config.xml css icon.png index.html js images components

all:
	@echo "Nothing to build"

wgtPkg: 
	zip -r $(INSTALL_FILES) config.xml css icon.png index.html js images components

clean:
	rm -rf js/services
	rm -rf css/car
	rm -rf css/user
	rm -f $(PROJECT).

common: /opt/usr/apps/_common
	cp -r /opt/usr/apps/_common/js/* js/
	cp -r /opt/usr/apps/_common/css/* css/

/opt/usr/apps/_common:
	echo "Please install Common Assets"
	exit 1

dev-common: ../_common
	cp -r ../_common/js/* js/
	cp -r ../_common/css/* css/

../_common:
	echo "Please checkout Common Assets"
	exit 1

install:
	@echo "Installing $(PROJECT), stand by..."
	mkdir -p $(INSTALL_DIR)/
	cp $(INSTALL_FILES) $(INSTALL_DIR)/

dist:
	tar czf ../$(PROJECT).tar.bz2 .

