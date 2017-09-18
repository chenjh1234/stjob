#include "reportwin.h"
#include "stapp.h"
#include <QGraphicsScene>
 
#include <QMessageBox>
 
ReportWin::ReportWin(QWidget *p) : QGraphicsView(p)
{
   init();
}
//=======================
ReportWin::~ReportWin()
{
    qDebug() << "report win down";

}
void ReportWin::init()
{
   // table:
   gridLayout = new QGridLayout(this);
   gridLayout->setObjectName(QStringLiteral("gridLayout"));
   textView = new QTextBrowser(this);
   textView->setObjectName(QStringLiteral("textView"));
   gridLayout->addWidget(textView, 0, 0, 1, 1);
   textView->setReadOnly(true);
   // table:
  
   //connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSelect(QModelIndex)));
   //  connect(buttonBox, SIGNAL(accepted()),this, SLOT(accept()));
}
void ReportWin::clear()
{
     textView->clear();
 
}
 void ReportWin::setData(QString data)
{
     textView->setText(data);
    
}
QString  ReportWin::getData()
{
    return  textView->toPlainText();
}
  