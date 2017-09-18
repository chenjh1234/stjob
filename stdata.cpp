#include "StData.h"
QString StData::report( ST * item)
{
    QString s;
    s = QString(" Venders: %1\n").arg(Vender.size());
    s += QString(" Packags: %1\n").arg(Package.size());
    s += QString(" Users: %1\n").arg(User.size());
    s += QString(" Nodes: %1\n").arg(Node.size());
    s += QString(" Jobs: %1\n").arg(item->jobs);
    s += QString(" Licenses: %1\n").arg(item->lics);
    s += QString(" Times: %1\n").arg(item->tms);
    s += QString(" Mean Times: %1\n").arg(item->mtime());
    return s;
}
QString StData::report( )
{
    QString s;
    s ="\nAll summary:\n";
    s += report(ALL);
    s +="\nPackages summary:\n";
    s += reportList(Package);
    s +="\nUsers summary:\n";
    s += reportList(User);
    return s;
}
QString StData::reportList( QMap<QString ,ST*> item)
{
    QStringList slist;
    QString s;
    int i,sz;
    int sjobs,slics,stms,smtms;
    slist = item.keys();
    sz = slist.size();

    if (sz == 0) return s;
    s="";
    sjobs = 0;
    slics = 0;
    stms = 0;
    for(i = 0; i <sz; i++)
    {
        s += QString(" %1: %2 , Jobs =%3, Lics = %4, Times = %5, Mean Times = %6\n").arg(i)
        .arg(slist[i]).arg(item[slist[i]]->jobs).arg(item[slist[i]]->lics).arg(item[slist[i]]->tms).arg(item[slist[i]]->mtime());
        sjobs += item[slist[i]]->jobs;
        slics += item[slist[i]]->lics;
        stms += item[slist[i]]->tms;
    }
    if(sjobs !=0)
        smtms = stms/sjobs;
    s += QString("%1: Jobs =%2, Lics = %3, Times = %4, Mean Times = %5\n")
        .arg("summary: ").arg(sjobs).arg(slics).arg(stms).arg(smtms);

    return s;
}
StData::StData()
{
    All["All"] = new ST();
 
}
#define P_ST(p) \
    p->job();\
    p->lic(number);\
    p->tm(tm);\
    p->vender(vender);\
    p->vender(package);\
    p->vender(user);\
    p->vender(node);
 

void StData::dost(QString vender,QString package,QString user,QString node,QString day,int number,int tm)
{
    QString month;
    month = day.left(6);

    ST *p;
    // all:
    // qDebug() << " all";
    p=ALL;
    P_ST(p);
    //Vender:
    //qDebug() << " vender";
    setItem(Vender,vender);
   // qDebug() << " vender";
    p = Vender[vender];
    //qDebug() << " p=" << p;
    P_ST(p);
    //Package:
    //qDebug() << " vender";
    setItem(Package,package);
    p = Package[package];
    P_ST(p);
    //User:
    setItem(User,user);
    p =User[user];
    P_ST(p);
    //Node:
    setItem(Node,node);
    p =Node[node];
    P_ST(p);
    //Month:
    setItem(Month,month);
    p =Month[month];
    P_ST(p);
    //day:
    setItem(Day,day);
    p =Day[day];
    P_ST(p);
}
 
void StData::setItem(QMap<QString,ST*>  &item,QString key)
{
    //qDebug() << key << item.contains(key);
    if (item.contains(key)) return;
    // qDebug() << key ;
    item[key] = new ST;  
    // qDebug() <<  item[key] ;
}
void StData::clearItem(QMap<QString,ST*>  &item)
{
    int i,sz;
    sz = item.size();
    if (sz == 0) return;
    ST *it;
    QStringList slist;
    slist = item.keys();

    for ( i= 0; i < sz;i++)
    {
        it = item[slist[i]];
        delete it;
    }
    item.clear(); 
}
void StData::clear()
{
    //Vender,Package,User,Node,Month,Day
    ALL->clear();
    clearItem(Vender);
    clearItem(Package);
    clearItem(User);
    clearItem(Node);
    clearItem(Month);
    clearItem(Day);
}

