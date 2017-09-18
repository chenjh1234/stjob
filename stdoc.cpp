#include "stdoc.h"
 

StDoc::StDoc()
{
    init();
}
StDoc::~StDoc()
{
    //qDebug() << "stDoc down = " << _buf;
    if (_buf != NULL)  delete []_buf; 
      
}
void  StDoc::init()
{ 
     _venderList.clear();
     _packageList.clear();
     _userList.clear();
     _lenBuf = 0;
     _fileList.clear();
     _dayList.clear();
     _monthList.clear();
     _stData.clear();
     _buf = NULL;

}

QString StDoc::rootDir()
{
   QString s;
   s = getenv(LIC_ROOT_PATH);
   if (s == "")  s = ".";
   return s;
}

QString StDoc::logDir()
{
   QString s;
   s = rootDir() + "/" + LIC_LOG_PATH;
   return s;
}
QString StDoc::docPath()
{
   QString s;
   s = rootDir() + "/" + LIC_FILE_PATH;
   return s;
}
QString StDoc::logFile(QString month)
{
   QString s;
   s = logDir() + "/" +ALOG + month+".log" ;
   return s;
}
void StDoc::doSt(QString file)
{
   QFile f;
   LFileDate fd;
   QString str,line,startDate,endDate;
   QStringList slist,sslist;
   //QString vender, QString package, QString user, QString node, QString day, int number, int tm
   QString vender,package,user,node,month,version,appname,day;
   int number,tm;

   startDate = fd.Date(_startDate);
   endDate = fd.Date(_endDate);
   //qDebug() << "s,e date=" << startDate << endDate;
   f.setFileName(file);
   if (f.open(QIODevice::ReadOnly |QIODevice::Text )) 
   {
//20170829102628 geoeast_pc1_1.0 192.168.109.132_12890_10867 cjh Debug/appt_geoeast_pc1_1.0_2_200_ 20170829101750 20170829102628 518 2 task 
//0:datetime 1: packID; 2:appid; 3:  user; 4:appname; 5:start; 6:end 7:time ;8: nnumber 9:type;
       QTextStream in(&f);     
       while (!in.atEnd()) 
       {
           line = in.readLine();
           slist =line.split(" ");
 // date:
           str = slist[0].left(8) ;// date;
           qDebug() << " line date=" << str;
           if (startDate <=str && endDate >=str) 
           {
// day:
               day = slist[0].left(8);
 // packid:
               str = slist[1];//packid:
               sslist = str.split("_");
               if (slist.size() >=3)  
               {   vender = sslist[0]; 
                    package = slist[1];
                    version = slist[2];
               }
               // vender,package:
               //qDebug() << vender<<package << _venderList.size() << _packageList.size() << (_venderList.size() !=0 )<<  !(_venderList.contains(vender));
                if (_venderList.size() !=0 && !_venderList.contains(vender))  continue;
                if (_packageList.size() !=0 && !_packageList.contains(package))  continue;
//appid:
                str = slist[2];//appid
                node = str.split("_")[0];        
                 qDebug() << "appid= " << node;
//user:app
                user =   slist[3];
                appname = slist[4];    
                 if (_userList.size() !=0 && !_userList.contains(user))  continue; 
// time:number:
                tm = slist[7].toInt();
                number = slist[8].toInt();
// void dost(QString vender, QString package, QString user, QString node, QString day, int number, int tm);
                qDebug() << vender<<package<<user<<node<<day<<number<<tm;
                _stData.dost(vender,package,user,node,day,number,tm);

           }// in time range:   
       } //while  
       f.close();
   }//fopen;
}


int  StDoc::drawDay( )
{

     int sz,i;
     QString d;
     sz = _dayList.size();
     if (sz <= 0)  return -1;
// buf:
    if (sz > _lenBuf) 
    {
        if (_buf != NULL)  delete []_buf; 
        _buf =new float[sz];
    }
   _lenBuf = sz;
 
    qDebug() << "days" << sz;
    float max = 0;
 
    for (i = 0; i <sz ;i ++) 
    {
        d = _dayList[i];
        //qDebug() << "in dayloop ="<< i << d <<_stData.Day.contains(d) << sz ;
        if (_stData.Day.contains(d) )
        {
             qDebug() << "yy" << _stData.Day[d];
            _buf[i] = _stData.Day[d]->lics;
        }
            else
        {
                //qDebug() << "yy";
            _buf[i] =0;
        }     
        if (max < _buf[i])  max = _buf[i];
    }
    _maxBuf = max ;
    qDebug() << "max = " << max;
    return sz;
}

int  StDoc::drawMonth( )
{
     int sz,i;
     QString d;
     float max;
     sz = _monthList.size();
     qDebug() << "months" << sz;
     if (sz <= 0)  return -1;
// buf:
    if (sz > _lenBuf) 
    {
        if (_buf != NULL)  delete []_buf; 
        _buf =new float[sz];
    }
   _lenBuf = sz;
 
    max = 0;
 //
    for (i = 0; i < sz ;i ++) 
    {
        d = _monthList[i];
        //qDebug() << "in monthloop ="<< i << d <<_stData.Month.contains(d) ;
        if (_stData.Month.contains(d) )
            _buf[i] = _stData.Month[d]->lics;
        else
            _buf[i] =0;
        if (max < _buf[i])  max = _buf[i];
    }
    _maxBuf = max ;
    return sz;
}
 
