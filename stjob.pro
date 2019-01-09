
include (../../licInclude.config)
TEMPLATE = app
QT += widgets
QT += testlib
  
DESTDIR =$${LIC_BIN}
TARGET = stjob

#INCLUDEPATH += $${INCLUDE_BUS}

INCLUDEPATH +=./  \
	../../draw\
	../../property/include\
	../../licbase

#LIBS +=  $${LIBS_BUS}

LIBS += \
	-L $${LIC_ROOT_PATH}/lib\
	-llicbase   -ldraw

 

HEADERS       =   \
	parawin.h\
	reportwin.h\
		stmain.h\
		stdoc.h\
		stapp.h\
                stdata.h 
		 
SOURCES       =  \
		reportwin.cpp\
		parawin.cpp\
		stmain.cpp\
		stdoc.cpp\
		stapp.cpp\
               stdata.cpp\
                stjob.cpp

FORMS       =  stjob.ui
RESOURCES  += \
	stjob.qrc

