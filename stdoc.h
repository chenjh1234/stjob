#ifndef ST_DOC_H
#define ST_DOC_H
#include <iostream>
#include <QString>
#include <QTextStream>
#include <QFile>
#include "LFileDate.h"
#include "stdata.h"
//#include "LLicEncrypt.h"
using namespace std;
#define ORG_NAME "STAPP"
#define APP_NAME "stjob"
#define APP_VERSION "1.001"
#define APP_DATE " 2017.10.1 "
//
#define CMD_SHOWPDF "showpdf "

#define LIC_ROOT_PATH "LIC_ROOT_PATH" //  licdatadir 
#define LIC_LOG_PATH "log" //  $LIC_ROOT/log
#define LIC_FILE_PATH "file" //  $LIC_ROOT/log
#define ALOG "ALOG"

 

#define PACKAGE_DEFINE {(char*)PACKAGENAME,(char*)PVERSION,\
                        (char*)PTYPE,(char*)PLIMIT,(char*)PSTARTDATE,\
                        (char*)PENDDATE,(char*)PKEY,\
                        NULL}
class StDoc 
{
public:
    StDoc();
    ~StDoc();
    void init();
    void doSt(QString file);


    QString logDir();    
    QString rootDir();    
    QString docPath();    
    QString  logFile(QString month);
    int drawDay();
    int drawMonth();

    float *_buf;
    int _maxBuf;
    int _lenBuf;


    QDate _startDate,_endDate;
    QStringList _fileList,_dayList,_monthList;
    QString _fileOut;
    QStringList _venderList, _userList,_packageList;
    StData _stData;
 
   
};
#endif

