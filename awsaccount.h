#ifndef AWSACCOUNT_H
#define AWSACCOUNT_H

#include <QtCore>
#include "awsqt_global.h"

class AWSQT_EXPORT AwsAccount{
private:
    QString _accessKey;
    QString _secretKey;
    QString _region;
    QString _accountId;
public:
    AwsAccount();
    AwsAccount(const QString& accessKey, const QString& secretKey, const QString& region, const QString& accountId);
    ~AwsAccount();

    QString accessKey() const;
    QString secretKey() const;
    QString region() const;
    QString accountId() const;

};

#endif // AWSACCOUNT_H
