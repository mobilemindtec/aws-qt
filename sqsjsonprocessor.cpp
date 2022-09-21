#include "sqsjsonprocessor.h"

SQSJsonProcessor::SQSJsonProcessor() : JsonParser()
{

}

SQSJsonProcessor::~SQSJsonProcessor()
{
}


SQSMessageDeleteResult SQSJsonProcessor::processDeleteReponse(QByteArray *data){
    QScopedPointer<QJsonDocument> doc(parseJson(data, "deleteMessageBatchResponse"));
    QJsonObject deleteMessageBatchResponse = doc->object().value("DeleteMessageBatchResponse").toObject();
    QJsonObject deleteMessageBatchResult = deleteMessageBatchResponse.value("DeleteMessageBatchResult").toObject();
    QJsonArray failed = deleteMessageBatchResult.value("Failed").toArray();
    QJsonArray successful = deleteMessageBatchResult.value("Successful").toArray();

    SQSMessageDeleteResult deleteResult;

    for(int i = 0; i < failed.size(); i++){
        QJsonObject json = failed[i].toObject();
        SQSMessageDeleteResultItem item;
        item.id = json.value("Id").toString();
        item.message = json.value("Message").toString();
        //item.senderFault = json.value("SenderFault").toString();
        deleteResult.results.append(item);
    }

    for(int i = 0; i < successful.size(); i++){
        QJsonObject json = successful[i].toObject();
        SQSMessageDeleteResultItem item;
        item.id = json.value("Id").toString();
        item.deleted = true;
        deleteResult.results.append(item);
    }

    return deleteResult;
}
