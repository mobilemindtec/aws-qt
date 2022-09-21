#ifndef SQSJSONPROCESSOR_H
#define SQSJSONPROCESSOR_H

#include "jsonparser.h"
#include "sqsmessagedeleteresult.h"
#include "awsqt_global.h"

class AWSQT_EXPORT SQSJsonProcessor : public JsonParser
{
private:

public:
    SQSJsonProcessor();
    ~SQSJsonProcessor();

    SQSMessageDeleteResult processDeleteReponse(QByteArray *data);
};

#endif // SQSJSONPROCESSOR_H
