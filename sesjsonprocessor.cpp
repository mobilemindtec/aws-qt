#include "sesjsonprocessor.h"


SESJsonProcessor::SESJsonProcessor() : JsonParser()
{
}

SESJsonProcessor::~SESJsonProcessor(){

}

QList<SQSMessage> SESJsonProcessor::processResponse(QByteArray* data){

    QScopedPointer<QJsonDocument> doc(this->parseJson(data, "Response"));

    if(doc == NULL){
        return QList<SQSMessage>();
    }

    QJsonObject receiveMessageResponse = doc->object().value("ReceiveMessageResponse").toObject();
    QJsonObject receiveMessageResult = receiveMessageResponse.value("ReceiveMessageResult").toObject();
    QJsonArray jsonMessages = receiveMessageResult.value("messages").toArray();

    int size = jsonMessages.size();
    QList<SQSMessage> messages;

    qDebug() << "process [" << size << "] messages";

    for(int i = 0; i < size; i++){
        QJsonObject jsonObj = jsonMessages[i].toObject();

        qDebug() << "jsonObj keys = " << jsonObj.keys();


        QString body = jsonObj.value("Body").toString();
        QString receiptHandle = jsonObj.value("ReceiptHandle").toString();
        //QString messageId = jsonObj.value("MessageId").toString();

        QScopedPointer<QJsonDocument> bodyDoc(parseJson(body.toUtf8(), "body"));

        if(bodyDoc == NULL){
            qDebug() << "key Body is null for message: " << jsonObj;
            continue;
        }

        QJsonObject bodyJson = bodyDoc->object();
        QString messageStr = bodyJson.value("Message").toString();
        QScopedPointer<QJsonDocument> messageDoc(parseJson(messageStr.toUtf8(), "message"));

        if(messageDoc == NULL){
            qDebug() << "key Message is null for message: " << jsonObj;
            continue;
        }

        QJsonObject jsonMessage = messageDoc->object();

        if(this->_debug){
            qDebug() << "jsonMessage keys = " << jsonMessage.keys();
            qDebug() << "JSON Message start *******************************************************************";
            qDebug() << "JSON Message: " << jsonObj;
            qDebug() << "JSON Message end *******************************************************************";
        }

        SQSMessage message;
        message.messageId = bodyJson.value("MessageId").toString();
        message.receiptHandle = receiptHandle;
        message.type = bodyJson.value("Type").toString();
        message.sesMsg = SQSMessageSES();
        message.sesMsg.fillJson(jsonMessage);

        messages.append(message);

        if(this->_debug){
            qDebug() << "CONV Message start *******************************************************************";
            qDebug() << "CONV Message: " << message.toString();
            qDebug() << "CONV Message end *********************************************************************";
        }

    }
    return messages;
}

