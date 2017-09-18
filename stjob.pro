 
TEMPLATE = app
QT += widgets
QT += testlib

DESTDIR = Debug
CONFIG += debug

TARGET = stjob

 
#DESTDIR =Debug
CONFIG += debug

LIBS +=\   
	-lssl
          

INCLUDEPATH += .\
         ../licwork\
	 ../draw\
         ../crypt

HEADERS       =   \
	../crypt/LEncrypt.h \ 
	../draw/drawdata.h \ 
		../draw/drawframe.h \ 
		../draw/drawing.h \ 
		../draw/drawitem.h \ 
		../draw/drawscene.h \ 
		../draw/colorbar.h \ 
		../draw/colormapdlg.h \ 
		../draw/arraydata.h \ 
		../draw/arraydraw.h\ 
		../draw/arraypaint.h \ 
		../draw/rulerframe.h \ 
		../draw/messagepad.h \ 
	parawin.h\
	reportwin.h\
		stmain.h\
		stdoc.h\
		stapp.h\
                stdata.h 
		 
SOURCES       =  \
		../licwork/LFileDate.cpp\
		../crypt/LEncrypt.cpp \ 
		../draw/drawdata.cpp \ 
		../draw/drawframe.cpp \ 
		../draw/drawing.cpp \ 
		../draw/drawitem.cpp \ 
		../draw/drawscene.cpp \ 
		../draw/colorbar.cpp \ 
		../draw/colormapdlg.cpp \ 
		../draw/arraydata.cpp \ 
		../draw/arraydraw.cpp \ 
		../draw/arraypaint.cpp \ 
		../draw/rulerframe.cpp \ 
		../draw/messagepad.cpp\ 
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

