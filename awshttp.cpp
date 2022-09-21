#include "awshttp.h"


AwsHttp::AwsHttp()
{
    this->_error = false;
}

AwsHttp::~AwsHttp()
{

}


bool AwsHttp::error() { return this->_error; }

QString AwsHttp::errorMessage() { return this->_errorMessage; }

QByteArray AwsHttp::get(QString url, bool json){

    QMap<QString, QString> headers;

    return this->get(url, headers, json);
}

QByteArray AwsHttp::get(QString url, QMap<QString, QString> headers, bool json){


    if(json){
        headers["Content-Yype"] = "application/json";
        headers["DataType"] = "json";
        headers["Accept"] = "application/json";
    }

    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    // "finished()" AwsHttp, when the network request "finished()"
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( (QUrl( QString(url) )) );


    QList<QString> keys = headers.keys();
    for(const QString& k : keys){
        req.setRawHeader(k.toUtf8(), headers[k].toUtf8());
    }


    QNetworkReply *reply = mgr.get(req);
    qDebug() << "waiting for event loop";
    eventLoop.exec();    
    qDebug() << "event loop finished";


    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Http GET Success";
        //success
        QByteArray b = reply->readAll();
        //qDebug() << "Http Response: " << QString(b);
        delete reply;
        return b;
    }
    else {
        //failure
        qDebug() << "Http GET Failure: " << reply->errorString();
        this->_error = true;
        this->_errorMessage =  reply->errorString();
        delete reply;
    }




    return QByteArray();
}
