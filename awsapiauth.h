#ifndef AWSAPIAUTH_H
#define AWSAPIAUTH_H

#include <QtCore>
#include "awsaccount.h"
#include "awsqt_global.h"

class AWSQT_EXPORT AwsApiAuth
{
private:
    AwsAccount _account;
    QList<QString> _urlQueryParams;
    QString _method;
    QString _service;
    QString _algorithm;
    QString _urlPath;
    QString _host;
    QString _canonicalUri;
    QString _canonicalHeaders;
    QString _signedHeaders;
    QString _apiVersion;
    QString _expires;
    bool _debug;

    QString createSha2Hash(QString text);
    QByteArray sign(QByteArray key, QByteArray msg);
    QByteArray getSignatureKey(QString key, QString dateStamp, QString regionName, QString serviceName);


public:
    AwsApiAuth();
    ~AwsApiAuth();

    void addQueryParam(const QString& name, const QString& value);
    void setAccount(const AwsAccount& account);
    void setMethod(const QString& method);
    void setService(const QString& service);
    void setAlgorithm(const QString& algorithm);
    void setUrlPath(const QString& urlPath);
    void setHost(const QString& host);
    void setCanonicalUri(const QString& canonicalUri);
    void setCanonicalHeaders(const QString& canonicalHeaders);
    void setSignedHeaders(const QString& signedHeaders);
    void setApiVersion(const QString& apiVersion);
    void setDebug(const bool& debug);
    void setExpires(const QString& expires);
    bool hasQueryParam(const QString& key);


    QString generateAuthUrl();

};

#endif // AWSAPIAUTH_H
