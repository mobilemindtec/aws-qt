#ifndef SQSMESSAGE_H
#define SQSMESSAGE_H


#include <QtCore>
#include "awsqt_global.h"
#include "sqsmessageses.h"

class AWSQT_EXPORT SQSMessage
{
public:
    QString receiptHandle;
    QString messageId;
    QString type;
    SQSMessageSES sesMsg;

    SQSMessage();
    ~SQSMessage();
    QString toString();


};

#endif // SQSMESSAGE_H
