#include <iostream>
#include "stapp.h"
#include "stdoc.h"
#include "stdata.h"

#include "stmain.h"
using namespace std;

int main (int argc, char *argv[])
{
    //cout << "hello world" << endl;       
    QString qstr;
    StApp  app(argc, argv);
    app.setOrganizationName(ORG_NAME);
    app.setApplicationName(APP_NAME);
  
    StDoc doc;
    app.m_doc =&doc;
     
    StMain mainWin;
 
    app.m_win = &mainWin;
    
    mainWin.show();
    return app.exec();
}

int main1 (int argc, char *argv[])
{
    StData dt;
    QString v,p,u,n,d,pp,uu;
    int num,tm;
    //dost(QString vender, QString package, QString user, QString node, QString month, int number, int tm);
    v = "GeoEast";
    pp = "GeoPS_v1.0";
    uu = "cjh";
    n = "pc1";
    d = "20170909";
    num = 1;
    tm = 3;
    int i;
    for (i = 0; i <20;i++)
    {
        p = pp+QString("%1").arg(i/4);
        u = uu+QString("%1").arg(i/5);
        num = 1+i/10;
       // qDebug() << i;
        dt.dost(v,p,u,n,d,num,tm);
       // qDebug() << i;
    }
    qDebug()<<"report All summary:";
    qDebug()<< dt.report(dt.ALL);
    qDebug()<<"report Packages:";
    qDebug()<< dt.reportList(dt.Package);
    qDebug()<<"report Users:";
    qDebug()<< dt.reportList(dt.User);
    qDebug()<<"report Day:";
    qDebug()<< dt.reportList(dt.Day);

    


    cout << "hello world" << endl;

    return(0);
}

