#include "stapp.h"
StApp *theApp;

StApp::StApp( int & argc, char ** argv ):QApplication(argc,argv)
{
    init();
}
StApp::~StApp()
{
        qDebug() << "app down";
}
void  StApp::init()
{
    theApp = this;

}
