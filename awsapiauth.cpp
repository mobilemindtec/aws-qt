#include "awsapiauth.h"

AwsApiAuth::AwsApiAuth()
{
    this->_method = "GET";
    this->_algorithm = "AWS4-HMAC-SHA256";
    this->_expires = "30";
    this->_apiVersion = "2012-11-05";
    this->_debug = false;
}

AwsApiAuth::~AwsApiAuth()
{
}

QString AwsApiAuth::createSha2Hash(QString text){
    return QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Sha256).toHex();
}

QByteArray AwsApiAuth::sign(QByteArray key, QByteArray msg){
    QMessageAuthenticationCode code(QCryptographicHash::Sha256);
    code.setKey(key);
    code.addData(msg);

    if(this->_debug){
        qDebug() << "---------------------------------------------------------------------------------------------";
        qDebug() << "sign: " << QString(code.result().toHex());
        qDebug() << "---------------------------------------------------------------------------------------------";
    }

    return code.result();
}

QByteArray AwsApiAuth::getSignatureKey(QString key, QString dateStamp, QString regionName, QString serviceName){
    QByteArray kSecret = QString("AWS4"+key).toUtf8();
    QByteArray kDate = sign(kSecret, dateStamp.toUtf8());
    QByteArray kRegion = sign(kDate, regionName.toUtf8());
    QByteArray kService = sign(kRegion, serviceName.toUtf8());
    QByteArray kSigning = sign(kService, QString("aws4_request").toUtf8());
    return kSigning;
}


void AwsApiAuth::addQueryParam(const QString& name, const QString& value){
    this->_urlQueryParams.append(QString("%1=%2").arg(name, value));
}

void AwsApiAuth::setAccount(const AwsAccount& account){
    this->_account = account;
}

void AwsApiAuth::setMethod(const QString& method){
    this->_method = method;
}

void AwsApiAuth::setService(const QString& service){
    this->_service = service;
}

void AwsApiAuth::setAlgorithm(const QString& algorithm){
    this->_algorithm = algorithm;
}

void AwsApiAuth::setUrlPath(const QString& urlPath){
    this->_urlPath = urlPath;
}

void AwsApiAuth::setHost(const QString& host){
    this->_host = host;
}

void AwsApiAuth::setCanonicalUri(const QString& canonicalUri){
    this->_canonicalUri = canonicalUri;
}

void AwsApiAuth::setCanonicalHeaders(const QString& canonicalHeaders){
    this->_canonicalHeaders = canonicalHeaders;
}

void AwsApiAuth::setSignedHeaders(const QString& signedHeaders){
    this->_signedHeaders = signedHeaders;
}

void AwsApiAuth::setApiVersion(const QString& apiVersion){
    this->_apiVersion = apiVersion;
}

void AwsApiAuth::setExpires(const QString& expires){
    this->_expires = expires;
}

void AwsApiAuth::setDebug(const bool& debug){
    this->_debug = debug;
}

bool AwsApiAuth::hasQueryParam(const QString& key){
    for(int i = 0; i < this->_urlQueryParams.size(); i++){
        QString pname = this->_urlQueryParams.value(i).split("=")[0];
        if(pname.toLower() == key.toLower())
            return true;
    }
    return false;
}

QString AwsApiAuth::generateAuthUrl(){

    QDateTime now = QDateTime::currentDateTime().currentDateTimeUtc();
    QString amzdate = now.toString("yyyyMMddTHHmmssZ");
    QString datestamp = now.toString("yyyyMMdd");

    QString accessKey = this->_account.accessKey();
    QString secretKey = this->_account.secretKey();
    //this->_urlQueryParams = new QList<QString>();

    QString region = this->_account.region();
    QString accountId = this->_account.accountId();

    QString host = this->_host;
    QString signedHeaders = this->_signedHeaders;
    QString canonicalUri = this->_canonicalUri;
    QString canonicalHeaders = this->_canonicalHeaders;

    if(host.isEmpty())
        host = QString("%1.%2.amazonaws.com").arg(this->_service, this->_account.region());

    if(signedHeaders.isEmpty())
        signedHeaders = "host";

    if(canonicalUri.isEmpty())
        canonicalUri = QString("/%1/%2/").arg(accountId, this->_urlPath);

    if(canonicalHeaders.isEmpty())
        canonicalHeaders = QString("host:%1\n").arg(host);


    QString credentialScope = QString("%1/%2/%3/aws4_request").arg(datestamp, region, this->_service);
    QString endpoint = QString("https://%1%2").arg(host, canonicalUri);


    this->addQueryParam("X-Amz-Algorithm", this->_algorithm);
    this->addQueryParam("X-Amz-Credential", QUrl::toPercentEncoding(accessKey + "/" + credentialScope));
    this->addQueryParam("X-Amz-Date", amzdate);
    this->addQueryParam("X-Amz-SignedHeaders", signedHeaders);

    if(!this->hasQueryParam("X-Amz-Expires"))
        this->addQueryParam("X-Amz-Expires", this->_expires);

    if(!this->hasQueryParam("Version"))
        this->addQueryParam("Version", this->_apiVersion);

    // parametros devem estar em orde alfabetica
    this->_urlQueryParams.sort();

    QString requestParameters = this->_urlQueryParams.join("&");

    if(this->_debug){
        qDebug() << "---------------------------------------------------------------------------------------------";
        qDebug() << "requestParameters: " << requestParameters;
        qDebug() << "---------------------------------------------------------------------------------------------";
    }

    QString canonicalQuerystring = requestParameters;
    QString payloadHash = this->createSha2Hash("");
    QString canonicalRequest = QString("%1\n%2\n%3\n%4\n%5\n%6")
            .arg(this->_method, canonicalUri, canonicalQuerystring, canonicalHeaders, signedHeaders, payloadHash);

    if(this->_debug){
        qDebug() << "---------------------------------------------------------------------------------------------";
        qDebug() << "canonicalRequest: " << canonicalRequest;
        qDebug() << "---------------------------------------------------------------------------------------------";
    }

    QString stringToSign = QString("%1\n%2\n%3\n%4")
            .arg(this->_algorithm, amzdate, credentialScope, this->createSha2Hash(canonicalRequest));

    if(this->_debug){
        qDebug() << "---------------------------------------------------------------------------------------------";
        qDebug() << "stringToSign: " << stringToSign;
        qDebug() << "---------------------------------------------------------------------------------------------";
    }

    QByteArray signingKey = getSignatureKey(secretKey, datestamp, region, this->_service);

    if(this->_debug){
        qDebug() << "---------------------------------------------------------------------------------------------";
        qDebug() << "signingKey: " << signingKey;
        qDebug() << "---------------------------------------------------------------------------------------------";
    }

    QString signature = sign(signingKey, stringToSign.toUtf8()).toHex();

    if(this->_debug){
        qDebug() << "---------------------------------------------------------------------------------------------";
        qDebug() << "signature: " << signature;
        qDebug() << "---------------------------------------------------------------------------------------------";
    }

    canonicalQuerystring += "&X-Amz-Signature="+signature;
    QString requestUrl = endpoint + "?" + canonicalQuerystring;

    if(this->_debug){
        qDebug() << "---------------------------------------------------------------------------------------------";
        qDebug() << "requestUrl: " << requestUrl;
        qDebug() << "---------------------------------------------------------------------------------------------";
    }

    return requestUrl;
}
