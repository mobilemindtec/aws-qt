#ifndef SQSMESSAGEDELETERESULT_H
#define SQSMESSAGEDELETERESULT_H

#include <QtCore>
#include "sqsmessagedeleteresultitem.h"
#include "awsqt_global.h"

class AWSQT_EXPORT SQSMessageDeleteResult {
public:
    QList<SQSMessageDeleteResultItem> results;
    SQSMessageDeleteResult();
    ~SQSMessageDeleteResult();
    QString toString();
};
#endif // SQSMESSAGEDELETERESULT_H
