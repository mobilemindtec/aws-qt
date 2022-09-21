#ifndef SESJSONPROCESSOR_H
#define SESJSONPROCESSOR_H

#include <QtCore>
#include "jsonparser.h"
#include "sqsmessage.h"
#include "sqsmessageses.h"
#include "awsqt_global.h"


class AWSQT_EXPORT SESJsonProcessor : public JsonParser
{
private:


public:
    SESJsonProcessor();
    ~SESJsonProcessor();

    QList<SQSMessage> processResponse(QByteArray* data);

};

#endif // SESJSONPROCESSOR_H
