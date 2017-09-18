#ifndef STDATA_HH
#define STDATA_HH

#include<QString>
#include<QStringList>
#include<QMap>
#include<QSet>
#include<QDebug>
#define ALL All["All"]
struct ST {
   ST() {clear();};
   int jobs;
   int lics;
   int tms;
   QSet<QString> venders,packages,users,nodes;

   void clear()
   {
      jobs = 0;
      lics = 0;
      tms = 0;
      venders.clear();
      packages.clear();
      users.clear();
      nodes.clear();
   };
   // maintime
   int mtime()
   {
      if (jobs != 0) return tms / jobs;
      else return 0;
   };
   //----------------------get list of itmes 
   void vender(QString v)
   {
      if (v != "") venders << v;
   };
   void package(QString v)
   {
      if (v != "") packages << v;
   };
   void user(QString v)
   {
      if (v != "") users << v;
   };
   void node(QString v)
   {
      if (v != "") nodes << v;
   };

   //---------------------job,lic,tms:
   void job() 
   {
      jobs++;
   }
   void lic(int num =1)
   {
      lics = lics + num;
   }
   void tm(int num)
   {
      tms = tms + num;
   }
  

};
/** 
 * statistic the data from log file,mesages: 
 * (vender, package, user, node, job ,date, lic_number time) ;
 *  
 *  data structure for ST :
 *  ALL:1
 *      vender:1-m
 *          package:1-m
 *              job:(user,node,month,day);job;lic;tms;  
 * 
 *  
 */
class StData
{
public:
   StData();
   /// do the statistic from the given parameters:
   void dost(QString vender, QString package, QString user, QString node, QString day, int number, int tm);
   /// get the itme data space ;new ST() if it is NULL;
   void setItem(QMap<QString, ST *>  &item, QString s);
   /// clear all data the the item, and delete the space od STs;
   void clearItem(QMap<QString, ST *>  &item);
   ///report a ST data: for All usally;
   int size() {return Package.size();};
  
   QString report(  ST*  item);
   QString report();
   QString reportList(QMap<QString, ST *>);
   void clear();

   /// items: each items cntain several ST data;
   QMap<QString, ST *> All,Vender,Package,User,Node,Month,Day;
};


#endif

