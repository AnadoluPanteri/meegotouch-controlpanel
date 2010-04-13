!dcpconfig {
    CONFIG += dcpconfig
# some hack for some problems experienced before
{
	QMAKE_CXXFLAGS_RELEASE += -g                                                                                                                       
	QMAKE_RPATH = -Wl
}

# Directories
{
	DCP_PREFIX = /usr
	DCP_INSTALL_LIB = $$DCP_PREFIX/lib
	DCP_INSTALL_HEADERS = $$DCP_PREFIX/include/mcontrolpanel
	DCP_THEME_DIR = $$DCP_PREFIX/share/themes/base/m/mcontrolpanel
	DCP_CSS_DIR = $$DCP_THEME_DIR/style/
	DCP_DESKTOP_DIR = $$DCP_PREFIX/lib/mcontrolpanel
	DCP_APPLET_DIR = $$DCP_PREFIX/lib/mcontrolpanel/applets
	DCP_UIDESC_DIR = $$DCP_PREFIX/lib/mcontrolpanel/uidescriptions
	DCP_TRANSLATIONS_DIR = $$DCP_PREFIX/share/l10n/m
}

# Gconf keys 
{
	DCP_MOSTUSEDCOUNTER_GCONFKEY = /apps/mcontrolpanel/usagecount
}

# defines for directories, they work cross-platform like this
{
	DEFINES += PREFIX=\\\"\"$$DCP_PREFIX\"\\\"
	# THEMEDIR determines the location of the theme
	DEFINES += THEMEDIR=\\\"\"$$DCP_THEME_DIR\"\\\"

	DEFINES += CSSDIR=\\\"\"$$DCP_CSS_DIR\"\\\"

	# APPLET_LIBS determines the location where all applet binaries are
	DEFINES += APPLET_LIBS=\\\"\"$$DCP_APPLET_DIR\"\\\"

	# APPLET_DATA determines where the .desktop files are located
	DEFINES += DESKTOP_DIR=\\\"\"$$DCP_DESKTOP_DIR\"\\\"

	DEFINES += TRANSLATIONS_DIR=\\\"\"$$DCP_TRANSLATIONS_DIR\"\\\"

	DEFINES += MOSTUSEDCOUNTER_GCONFKEY=\\\"\"$$DCP_MOSTUSEDCOUNTER_GCONFKEY\"\\\"
}
}
