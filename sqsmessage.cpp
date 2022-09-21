#include "sqsmessage.h"


SQSMessage::SQSMessage(){

}

SQSMessage::~SQSMessage(){

}

QString SQSMessage::toString(){
    QVariantMap var;
    var["messageId"] = this->messageId;
    var["receiptHandle"] = this->receiptHandle;
    var["type"] = this->type;
    var["sesMsg"] = this->sesMsg.toString();
    return QString(QJsonDocument::fromVariant(var).toJson());
}

