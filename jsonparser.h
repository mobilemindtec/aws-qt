#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QtCore>
#include "awsqt_global.h"

class AWSQT_EXPORT JsonParser
{
private:
    QString _errorMessage;
    bool _error;    

    void setError(const QString& errorMessage);

protected:
    bool _debug;

public:
    JsonParser();

    QString errorMessage();
    bool error();
    void setDebug(const bool& debug);

    QJsonDocument* parseJson(QByteArray* data, QString step);
    QJsonDocument* parseJson(QString data, QString step);

};

#endif // JSONPARSER_H
