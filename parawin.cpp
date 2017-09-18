#include "parawin.h"
 
ParamWin::ParamWin(QWidget *p):QWidget(p)
{
    ui.setupUi(this);
    init();
    connect((QObject*)ui.radioButtonMonth,SIGNAL(clicked ()),this,SLOT(slotMonth()));
    connect((QObject*)ui.radioButtonDay,SIGNAL(clicked ()),this,SLOT(slotDay()));
}
ParamWin::~ParamWin()
{
} 
void ParamWin::init()
{

    QDate dt,dt0;
    int y,m;
    dt = QDateTime::currentDateTime().date();
    y = dt.year();
    m = dt.month();
    dt0.setDate(y,m,1);


    ui.endDate->setMaximumDate(dt);
    ui.startDate->setMaximumDate(dt);
       
    ui.endDate->setDate(dt);
    ui.startDate->setDate(dt0);

    ui.lineEditUser->setText("");
    ui.lineEditPackage->setText("");
    ui.lineEditVender->setText("");
    ui.radioButtonMonth->setChecked(false);
    ui.radioButtonDay->setChecked(false);
     
    //radioButtonMonth
 
 
    
}
void ParamWin::slotDay()
{
    qDebug() << " in day";
    emit sigDay();

}
void ParamWin::slotMonth()
{
    emit sigMonth();
}
void ParamWin::getData()
{
    QString str;
    DOC->_startDate = ui.startDate->date();
    DOC->_endDate = ui.endDate->date();

    str = ui.lineEditVender->text();
    if (!str.isEmpty() )
        DOC->_venderList = str.split(","); 

    str = ui.lineEditPackage->text();
    if (!str.isEmpty() )
        DOC->_packageList = str.split(",");

    str = ui.lineEditUser->text();
    if (!str.isEmpty() )
         DOC->_userList = str.split(",");
}
void ParamWin::getFiles()
{
    int i;
    LFileDate fd;
    QDate s,e;
    QDateTime dt;
    QStringList fileList,mList;
    QString m;
    fileList.clear();
    mList.clear();
    getData();
     s = DOC->_startDate;
     e = DOC->_endDate;
 
     i = 0;
   // get files:
    while (s < e) 
    {
        dt.setDate(s);
        m = fd.DT(dt).left(6);
        //qDebug() << fd.Date(dt);
        mList << m;

        fileList << DOC->logFile(m);
        s = s.addMonths(1);
        i++;
         if (i >100)  break;
     }
    DOC->_fileList = fileList;
    DOC->_monthList = mList;
// get days:

    fileList.clear();
    i = 0;
    s = DOC->_startDate;
    e = DOC->_endDate;
   while (s < e) 
   {
       dt.setDate(s);
       m = fd.DT(dt).left(8);
       fileList << m;
       s = s.addDays(1);
       i++;
        if (i >1000)  break;
    }
    DOC->_dayList = fileList;
}
