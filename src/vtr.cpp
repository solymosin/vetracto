#include "vtr.h"
#include <qstring.h>

vtr::vtr()
{

}

QString vtr::fereghajtoIDentify(const QString& fereghajto){

    QString sql = QString("Select count(az) as n from xbfereghajtok where fereghajto = '%1'").arg(fereghajto);
    QSqlQuery query(sql);
    QSqlRecord record = query.record();
    query.first();
    QString res = query.value(record.indexOf("n")).toString();

    return res;
}

