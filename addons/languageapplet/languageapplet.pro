TEMPLATE      = lib
CONFIG       += plugin gui dui
LIBS         += -ldui
INCLUDEPATH  += $$[QT_INSTALL_HEADERS]/dui
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = languageapplet.h \
                languagewidget.h \
                languagebutton.h

SOURCES       = languageapplet.cpp \
                languagewidget.cpp \
                languagebutton.cpp

TARGET        = $$qtLibraryTarget(languageapplet)
DESTDIR       = lib

target.path += $$[QT_INSTALL_LIBS]/duicontrolpanel/applets

INSTALLS += \
	    target