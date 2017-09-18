#ifndef REPORT_WIN_H
#define REPORT_WIN_H
 
 
#include <QTextBrowser>
#include <QGridLayout>
#include <QGraphicsView>

class ReportWin :public QGraphicsView
{
Q_OBJECT

public:
    ReportWin(QWidget *p);
    ~ReportWin();
  
    void setData(QString s);
 
    QString getData();
    void init();
    void clear();
     

    QTextBrowser *textView;
    QGridLayout *gridLayout;
  
 
};
#endif




