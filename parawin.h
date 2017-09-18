#ifndef  PARAM_WIN_H
#define  PARAM_WIN_H
#include <QDialog>
#include <QWidget>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include "stapp.h"
#include "ui_stjob.h"
 
class ParamWin : public QWidget
{
    Q_OBJECT
public:
    ParamWin(QWidget *p);
    ~ParamWin();
     
 
    void init();
    void getFiles(); 
public slots:    
    void getData();
    void slotDay();
    void slotMonth();
signals:
    void sigMonth();
    void sigDay();

private:

    Ui::paramWin ui;

};
#endif


