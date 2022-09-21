#include "sqsmessagedeleteresult.h"

SQSMessageDeleteResult::SQSMessageDeleteResult(){
}

SQSMessageDeleteResult::~SQSMessageDeleteResult(){

}

QString SQSMessageDeleteResult::toString(){
    QVariantList list;
    int size = this->results.size();
    int deleteCount = 0, errorCount = 0;
    for(int i = 0; i < size; i++){
        SQSMessageDeleteResultItem item = this->results.value(i);
        list.append(item.toString());

        if(item.deleted)
            deleteCount += 1;
        else
            errorCount += 1;

    }
    QVariantMap var;
    var["results"] = list;
    var["delete_count"] = deleteCount;
    var["error_count"] = errorCount;

    return QString(QJsonDocument::fromVariant(var).toJson());
}
