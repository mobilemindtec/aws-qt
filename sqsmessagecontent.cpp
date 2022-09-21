#include "sqsmessagecontent.h"

SQSMessageContent::SQSMessageContent()
{

}

SQSMessageContent::~SQSMessageContent()
{

}

QVariant SQSMessageContent::toVariant(){
    return QVariant();
}

QString SQSMessageContent::toString(){
    return "";
}

void SQSMessageContent::fillJson(const QJsonObject& data){
    Q_UNUSED(data);
}
