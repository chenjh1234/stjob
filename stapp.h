#ifndef ST_APP_H
#define ST_APP_H

#include <QApplication>
//#include "mainwindow.h"
#include "stdoc.h"
class StApp;
class StMain;
#include <iostream>

#define DOC theApp->m_doc
#define WIN theApp->m_win

using namespace std;
extern StApp *theApp;
 
class StApp :public QApplication  
{
public:
    StApp( int & argc, char ** argv );
    ~StApp();
    StDoc *m_doc;
    StMain *m_win;


private:

    void init();

};
#endif
