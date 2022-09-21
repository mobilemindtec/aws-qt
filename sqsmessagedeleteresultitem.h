#ifndef SQSMESSAGEDELETERESULTITEM_H
#define SQSMESSAGEDELETERESULTITEM_H

#include <QtCore>
#include "awsqt_global.h"

class AWSQT_EXPORT SQSMessageDeleteResultItem{
public:
    QString id;
    QString message;
    //QString senderFault;
    bool deleted;

    SQSMessageDeleteResultItem();
    QString toString();

};


#endif // SQSMESSAGEDELETERESULTITEM_H
