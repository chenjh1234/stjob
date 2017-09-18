 
#include <QtWidgets>
#include <QMessageBox>
#include "stmain.h"
#define stringList csVector<std::string>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QPixmap>
#include <QVBoxLayout>
 
 
StMain::StMain():QMainWindow()
{
    //left dock: up:modules,down:moduleHelp:
//dock
    m_w=  1500;
    m_h = 800;
     
    paraDockWidget = new QDockWidget("paraView",this );
    addDockWidget(Qt::LeftDockWidgetArea, paraDockWidget);
    //venderDockWidget->setFixedWidth(300);
     
//paraWin:
 
    paraManager = new  QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(paraManager);

    paraWin = new ParamWin(paraManager);
 

    vlayout->setSpacing(1);
    vlayout->addWidget(paraWin);

    paraDockWidget->setWidget(paraManager);
    connect((QObject*)paraWin,SIGNAL(sigDay()),this,SLOT(slotDay()));
    connect((QObject*)paraWin,SIGNAL(sigMonth ()),this,SLOT(slotMonth()));
  
 
 // reportWin: 
   
    reportManager  = new QWidget(this);
    QVBoxLayout *vvlayout = new QVBoxLayout(reportManager);
     reportWin  = new ReportWin(this);
    setCentralWidget(reportManager);
    vvlayout->addWidget(reportWin);
  
// drawWin
    drawDay = new arrayDraw(this);
    drawMonth = new arrayDraw(this);
    // drawWin = new arrayDraw(this);
    vvlayout->addWidget(drawMonth);
    vvlayout->addWidget(drawDay);
  //  drawWin->setDrawStyle(DRAW_RECT,1,1,1,3);// rect,red,wide =1,fill, 3=blue;
    drawMonth->hide();
    drawDay->hide();


// connect:
   // connect(editFilter,SIGNAL(textChanged(QString )),modListView,SLOT(slotFilter(QString)));
   // connect(buttonModAll,SIGNAL(clicked ()),modListView,SLOT(slotFilterAll()));

 
 
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    setWindowModified(false);//init
    resize(m_w,m_h);
    paraDockWidget->resize(m_w/2,m_h);
  
    setTitle();
   // slotDay();
 
    return; 
  
}
void StMain::setTitle()
{
  
    QString str;
    str = "";
    str = str + APP_NAME + "-"+APP_VERSION +"-"+ __DATE__ ;
    
    setWindowTitle(str);
    qDebug() << "title = " << str;

}
  
 
    
void StMain::closeEvent(QCloseEvent *event)

{
    qDebug() << " main win downo";

 
        writeSettings();
        event->accept();
        qDebug() << " main win down";
    
}
 
void StMain::newFile()
{
   // setFile(LICFILE_DEFAULT);
    paraWin->init();
    reportWin->setData("");
    drawDay->hide();
    drawMonth->hide();
}

void StMain::run()
{
    QString filename;
    LFileDate fd;
    QString str;
    int ic,sz,i;
//files:
    paraWin->getFiles();
    sz = DOC->_fileList.size();
    if (sz == 0)  
    {
        str= "No log file selected";
        STT(str);
    }
    ic = 0;
//clear data:
    DOC->_stData.clear();
// do statistics: in each file:

    for (i = 0; i < sz; i++) 
    {
        filename  = DOC->_fileList[i];
        if (fd.isFile(filename)) 
        {
            DOC->doSt(filename);
            str=" statistic: "+filename;
             STT(str);
             ic++;
        }
        else
        {
            str = "No this filename : " + filename;
            qDebug() << "No this filename = " << filename;
        }
    }
    str= QString("all files: %1").arg(ic);
    STT(str);
    report();
}
void  StMain::report()
{
    LFileDate fd;
    QString start,end,rp;
    start = fd.Date(DOC->_startDate);
    end = fd.Date(DOC->_endDate);
    rp = QString("report Date: %1 to %2\n").arg(start).arg(end);
    rp += DOC->_stData.report();
    reportWin->setData(rp);
}
  

bool StMain::save()
{
       bool b;
    
    if (DOC->_fileOut.isEmpty()) 
    {
        b = saveAs();
    } 
    else 
    {
        b =  saveFile(DOC->_fileOut);
    }
    qDebug() << "save =" << b;
    return b;
}

bool StMain::saveAs()
{
    bool b;
    #if 1
    QString strt,strd,strf,str;
    strf = "*.rpt";
    strt = "save reportfile";
    strd = "";
  
    QString fileName = QFileDialog::getSaveFileName(this,strt,strd,strf);
    if (fileName.isEmpty())
    {
        STT("No File spcified");
        return false;
    }
    QFileInfo fi(fileName);

    QString ext = "rpt";
    if (fi.suffix() != ext) 
    {
        fileName = fileName +"."+ext;
    }
    DOC->_fileOut = fileName;
    b =  saveFile(fileName);
    qDebug() << "save =" << b;
    #endif
    return b;
}
 
void StMain::about()
//! [13] //! [14]
{
    QString title,str,str1;
    title = ORG_NAME;
    str1 = __DATE__;
    str = QString("   App name : ") +QString(APP_NAME) + "\n" +
          QString("App version : ") +QString(APP_VERSION) + "\n" +
          QString("       Date : ") +str1;
   QMessageBox::about(this, title,str);
}
 
void StMain::createActions()
{
    qDebug() << "create acton start";
    //new
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    runAct = new QAction(QIcon(":/images/run.png"), tr("&Run..."), this);
   // runAct->setShortcuts(QKeySequence::Open);
    runAct->setStatusTip(tr("Start statistics"));
    connect(runAct, SIGNAL(triggered()), this, SLOT(run()));
 
    
    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
 
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
 
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    // edit:
   

 
//help

    helpAct = new QAction(QIcon(":/images/help.png"), tr("&Help"), this);
    helpAct->setStatusTip(tr("User manual of flowPad"));
    connect(helpAct, SIGNAL(triggered()), this, SLOT(slotHelp()));
    //qDebug() << "create action OK";


//about

    aboutAct = new QAction(QIcon(":/images/about.png"), tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    qDebug() << "create action OK";
    return;
   
}
 void StMain::createMenus()
{
   // open
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    //fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addSeparator();
 //   fileMenu->addAction(openOutAct);
    fileMenu->addSeparator();
    
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    runMenu = menuBar()->addMenu(tr("&Run"));
    runMenu->addAction(runAct);

  
 
 
//help
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
    helpMenu->addAction(aboutAct);
    qDebug() << "create menu OK";
    return;
}

void StMain::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveAsAct);
          //fileToolBar->addAction(textFlowAct);
    runToolBar = addToolBar(tr("Run"));
    runToolBar->addAction(runAct);

 
     helpToolBar = addToolBar(tr("Help"));
      helpToolBar->addAction(helpAct);
     helpToolBar->addAction(aboutAct);
 
    qDebug() << "create toolbar OK";
    return;
}

void StMain::createStatusBar()

{
    statusBar()->showMessage(tr("Ready"));
}

void StMain::readSettings()
{
    //QSettings settings(ORG_NAME, APP_NAME);
    //QString str = settings.value("flow").toString();
    //theApp->m_doc->m_filename =str; 
 
}
void StMain::writeSettings()
{
    #if 0
    QString str;
    QSettings settings(ORG_NAME,APP_NAME);
    str = QString("\"") + theApp->m_doc->m_filename + QString("\"");
    settings.setValue("flow", theApp->m_doc->m_filename);
    #endif
}

bool StMain::maybeSave()
{ 
    #if 0
    if ( isWindowModified ()) 
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("You will New your flow"),
                     tr("The current flow has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    } 
    #endif
    return true;
}
 

bool StMain::saveFile(const QString &fileName)
{

    int i;
    LFileDate fd;
    QString str;
    str = reportWin->getData();
    fd.writeText(fileName,str);
    return true;
}
 
QString StMain::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
  
        
void StMain::resizeEvent ( QResizeEvent * event )
{
    //int w,h;
    m_w = event->size().width();
    m_h = event->size().height();
    //flowMode();
}
void StMain::slotHelp()
{
    QString cmd,str;
    char *ch;
    cmd = CMD_SHOWPDF;
    cmd = cmd+  DOC->docPath()+ "/" + APP_NAME+".pdf";
        //cmd = "ls";
    qDebug() << "cmd=" <<cmd;
    hrun.start(cmd);

}
 
void StMain::slotDay()
{
    int i;
    QString key = "Day";
    drawDay->endDraw();
    //setDrawStyle(2, 0, 1, 1, 7);

    STT(key);
    i = DOC->drawDay();
 
    if (i < 0) 
    {
        STT("Draw Day error");
         return;
    }
      draw(i,key);
#if 0
    qDebug() << "max,=" <<i<< DOC->_dayList.size() << DOC->_lenBuf<< DOC->_maxBuf<<DOC->_buf;
 
   drawWin->setMaxMin(0,0,i-1,DOC->_maxBuf );
     drawWin->setColorBar(0);
   // drawWin->setDrawStyle(0,1,1,1,3);// rect,red,wide =1,fill, 3=blue;
    drawWin->setDrawStyle(DRAW_RECT,1,1,1,3);// rect,red,wide =1,fill, 3=blue;
    drawWin->setFitWin();
    drawWin->setCoordinate(RIGHT_UP);
    drawWin->startDraw(DOC->_buf,DOC->_lenBuf,key);
    drawWin->show();
    #endif
}
void StMain::slotMonth()
{
    int i;
    QString key = "Month";
    drawMonth->endDraw();
    STT("Month");
    i = DOC->drawMonth();
    if (i <0)
    {
        STT("Draw month error");
         return;
    }
    draw(i,key);
}
void StMain::draw(int i,QString key)
{
    qreal *buf;
    QStringList slist;

    if (key == "Day")  
    {
        drawWin = drawDay;
        drawMonth->hide();
        slist = DOC->_dayList;
        
    }
        else
    {
        drawWin = drawMonth;
        drawDay->hide();
        slist = DOC->_monthList;
         
    }
     buf = new qreal[i];

     for (int j = 0; j < i; j++) 
     {
         buf[j] = slist[j].toInt();
     }

    drawWin->setColorBar(0);
    drawWin->setMaxMin(0,0,i-1,DOC->_maxBuf);
    drawWin->setDrawStyle(DRAW_RECT,1,1,1,3);// rect,red,wide =1,fill, 3=blue;
    // drawWin->setDrawStyle(0,1,1,1,3);// rect,red,wide =1,fill, 3=blue;
    drawWin->setFitWin();
    //drawWin->setScale(4,4);
    drawWin->setLabX(buf,i);
    drawWin->setGrid(5,10);
    
    drawWin->setCoordinate(RIGHT_UP);
    drawWin->startDraw(DOC->_buf, DOC->_lenBuf, key); 
  
    drawWin->show();    
    delete []buf;
}
 
bool StMain::ask(QString str,QString title)
{
    int id;
    id = QMessageBox::question(this,title,str);
    if (id ==QMessageBox::Yes) 
        return true;
    return false;
}

void StMain::msg(QString str,QString title)
{
     QMessageBox::information(this,title,str);
}
void StMain::fileText(QString file,QString title)
{
    LFileDate fd;
    QString str;
    str = fd.getText(file);
     QMessageBox::information(this,title,str);
}
