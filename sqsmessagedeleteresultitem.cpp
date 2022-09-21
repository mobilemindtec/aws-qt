#include "sqsmessagedeleteresultitem.h"

SQSMessageDeleteResultItem::SQSMessageDeleteResultItem()
{

}


QString SQSMessageDeleteResultItem::toString(){
    QVariantMap data;
    data["id"] = this->id;
    data["message"] = this->message;
    data["deleted"] = this->deleted;
    return QString(QJsonDocument::fromVariant(data).toJson());
}
