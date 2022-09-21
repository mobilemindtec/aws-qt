#ifndef AWSHTTP_H
#define AWSHTTP_H

#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "awsqt_global.h"

class AWSQT_EXPORT AwsHttp
{    
private:
    bool _error;
    QString _errorMessage;        
public:
    AwsHttp();
    ~AwsHttp();

    bool error();
    QString errorMessage();

    QByteArray get(QString url, QMap<QString, QString> headers, bool json = true);
    QByteArray get(QString url, bool json = true);
};

#endif // AWSHTTP_H
