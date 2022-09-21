#include "sqsmessageses.h"

SQSMessageSES::SQSMessageSES()
{

}

SQSMessageSES::~SQSMessageSES()
{

}



void SQSMessageSES::setEventType(const QString& eventType){

    this->eventTypeStr = eventType;

    if (eventType == "Bounce"){
        this->eventType = SESEventType::Bounce;
    }else if (eventType == "Complaint"){
        this->eventType = SESEventType::Complaint;
    }else if (eventType == "Delivery"){
        this->eventType = SESEventType::Delivery;
    }else if (eventType == "Send"){
        this->eventType = SESEventType::Send;
    }else if (eventType == "Reject"){
        this->eventType = SESEventType::Reject;
    }else if (eventType == "Open"){
        this->eventType = SESEventType::Open;
    }else if (eventType == "Click"){
        this->eventType = SESEventType::Click;
    }else if (eventType == "Rendering Failure"){
        this->eventType = SESEventType::RenderingFailure;
    }else if (eventType == "DeliveryDelay"){
        this->eventType = SESEventType::DeliveryDelay;
    }else if (eventType == "Subscription"){
        this->eventType = SESEventType::Subscription;
    }else{
        this->eventType = SESEventType::EventNone;
    }
}

void SQSMessageSES::setBounceType(const QString& bounceType){

    this->bounceTypeStr = bounceType;

    if(bounceType == "Undetermined"){
        this->bounceType = SESBounceType::Undetermined;
    }else if(bounceType == "Permanent"){
        this->bounceType = SESBounceType::Permanent;
    }else{
        this->bounceType = SESBounceType::BounceNone;
    }
}

void SQSMessageSES::collectRecipients(const QJsonObject& data){
    QJsonArray recipients;

    switch(this->eventType){
        case SESEventType::Bounce: {
            QJsonObject bounceObj = data.value("bounce").toObject();
            QString bounceType = bounceObj.value("bounceType").toString();
            recipients = bounceObj.value("bouncedRecipients").toArray();
            this->setBounceType(bounceType);
            break;
        }
        case SESEventType::Complaint:
            recipients = data.value("complaint").toObject().value("complainedRecipients").toArray();
            break;
        case SESEventType::Delivery:
            recipients = data.value("delivery").toObject().value("recipients").toArray();
            break;
        case SESEventType::Send:
            //recipients = data.value("send").toObject().value("bouncedRecipients").toArray();
            break;
        case SESEventType::Reject:
            this->errorMessage = "Reject: " +  data.value("reject").toObject().value("reason").toString();
            break;
        case SESEventType::Open:
            recipients = data.value("open").toObject().value("bouncedRecipients").toArray();
            break;
        case SESEventType::Click:
            this->cickedLink = data.value("click").toObject().value("link").toString();
            break;
        case SESEventType::RenderingFailure:
            this->errorMessage = "Reject: " +  data.value("failure").toObject().value("errorMessage").toString();
            break;
        case SESEventType::DeliveryDelay:
            recipients = data.value("deliveryDelay").toObject().value("delayedRecipients").toArray();
            break;
        case SESEventType::Subscription:
            //recipients = data.value("subscription").toObject().value("bouncedRecipients").toArray();
            break;
        default:
            qDebug() << "event type none";
    }

    for(auto&& obj : recipients){
        QString emailAddress;

        if(obj.isString()){
            emailAddress = obj.toString();
        }else{
            emailAddress = obj.toObject().value("emailAddress").toString();
        }

        this->recipients.append(emailAddress);
    }
}

void SQSMessageSES::fillJson(const QJsonObject& data){

    QJsonObject mail = data.value("mail").toObject();
    QJsonObject commonHeaders = mail.value("commonHeaders").toObject();
    QJsonArray toArray = mail.value("destination").toArray();

    this->setEventType(data.value("eventType").toString());
    this->collectRecipients(data);

    this->source = mail.value("source").toString();
    this->subject = commonHeaders.value("subject").toString();
    this->from = commonHeaders.value("from").toArray().first().toString();

    //https://stackoverflow.com/questions/25158976/forcing-auto-to-be-a-reference-type-in-a-range-for-loop
    for(auto&& it : toArray){
        this->to.append(it.toString());
    }
}

QVariant SQSMessageSES::toVariant(){
    QVariantMap var;
    var["eventType"] = this->eventTypeStr;
    var["bounceType"] = this->bounceTypeStr;
    var["from"] = this->from;
    var["source"] = this->source;
    var["subject"] = this->subject;
    var["errorMessage"] = this->errorMessage;
    var["cickedLink"] = this->cickedLink;

    QVariantList recipientsTmp;
    for(QString& it : this->recipients){
        recipientsTmp.append(it);
    }

    QVariantList toTmp;
    for(QString& it : this->recipients){
        recipientsTmp.append(it);
    }

    var["recipients"] = recipientsTmp;
    var["to"] = toTmp;

    return var;
}

QString SQSMessageSES::toString(){
    return QString(QJsonDocument::fromVariant(this->toVariant()).toJson());
}
