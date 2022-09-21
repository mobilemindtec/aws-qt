#include "jsonparser.h"

JsonParser::JsonParser()
{
    this->_error = false;
}

bool JsonParser::error(){
    return this->_error;
}

void JsonParser::setDebug(const bool& debug){
    this->_debug = debug;
}

QString JsonParser::errorMessage(){
    return this->_errorMessage;
}

void JsonParser::setError(const QString& errorMessage){
    this->_error = true;
    this->_errorMessage = errorMessage;
}

QJsonDocument* JsonParser::parseJson(QByteArray *data, QString step){
    QJsonParseError errorPtr;
    QJsonDocument *doc = new QJsonDocument(QJsonDocument::fromJson(*data, &errorPtr));
    if(doc->isNull()){
        this->setError("JsonParser: Parse [" + step + "] failed: " + errorPtr.errorString());
        qDebug() << this->_errorMessage;
        return nullptr;
    }

    if(this->_debug){
        qDebug() << "JsonParser: parse " << step << " successful";
    }

    return doc;
}

QJsonDocument* JsonParser::parseJson(QString data, QString step){
    QByteArray d = data.toUtf8();
    return this->parseJson(&d, step);
}
