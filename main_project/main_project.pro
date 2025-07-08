TEMPLATE = subdirs

# Using subdirs to separate the application and two unit test
# Qt recommends putting each unit test class in it's own project
SUBDIRS += \
    ../app \
    ../integrationstest_all \
    ../integrationstest_koordinator \
    ../integrationstest_programmsteuerung_bruehgruppe \
    ../unittest_Programmsteuerung_3 \
    ../unittest_bruehgruppe_2 \
    ../unittest_display \
    #../unittest_zahlungseinheit \
    ../unittest_koordinator \
    ../unittest_fuellstandsmessung \
    ../unittest_motorsteuerung






