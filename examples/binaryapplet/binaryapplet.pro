TEMPLATE      = subdirs

SUBDIRS += itemlike \
           buttonlike \
           translations

# for check:
QMAKE_EXTRA_TARGETS += check
check.commands = $$system(true)

QMAKE_EXTRA_TARGETS += check-xml
check-xml.commands = $$system(true)

