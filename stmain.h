#ifndef ST_APP_WINDOW_H
#define ST_APP_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
//class QPlainTextEdit;
QT_END_NAMESPACE


#include <QDockWidget>
#include <QTextBrowser>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QProcess>

#define STT(x) statusBar()->showMessage(x);

#include "stapp.h"
#include "iostream"
#include "parawin.h"
#include "reportwin.h"
#include "arraydraw.h"
 

using namespace std;
 
class StMain : public QMainWindow
{
    Q_OBJECT
public: 
   StMain();
    bool ask(QString str,QString title="Please conform:");
    void msg(QString str,QString title="Information:");
    void fileText(QString str,QString title="Information:");


protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void run();
    bool save();
    bool saveAs();
    void about();

 
   
private: 
    
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();

    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void report();
    void draw(int len,QString key);
 
    QString strippedName(const QString &fullFileName);
    void setTitle();

    QDockWidget *paraDockWidget;
    QWidget *paraManager,*reportManager;

    ParamWin *paraWin;
    ReportWin *reportWin;

    arrayDraw *drawWin,*drawMonth,*drawDay;
   
    QMenu *fileMenu,*helpMenu;   
    QMenu *runMenu;
    
    QToolBar *fileToolBar;
    QToolBar *runToolBar;
    QToolBar *helpToolBar;

    QAction *newAct;
    QAction *runAct;
    QAction *saveAct;
    QAction *saveAsAct;   
    QAction *exitAct;

    QAction *reportAct;
    QAction *monthAct;
    QAction *dayAct;
     
  
    QAction *aboutAct;
    QAction *helpAct;
public:
    QProcess hrun;
  

public slots:
   
   // void slotTextFlow();
    void  slotHelp();
    void  slotMonth ();
    void  slotDay ();
  
    void resizeEvent ( QResizeEvent * event );
public:
     
private:
    
    int m_w,m_h;
    //bool isflowMode();
 
};
//! [0]

#endif

