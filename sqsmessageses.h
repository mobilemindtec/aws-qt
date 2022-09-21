#ifndef SQSMESSAGESES_H
#define SQSMESSAGESES_H

#include "awsqt_global.h"
#include <QtCore>
enum AWSQT_EXPORT SESEventType {
    Bounce,
    Complaint,
    Delivery,
    Send,
    Reject,
    Open,
    Click,
    RenderingFailure,
    DeliveryDelay,
    Subscription,
    EventNone
};

enum AWSQT_EXPORT SESBounceType{
    Undetermined, Permanent, BounceNone
};

class AWSQT_EXPORT SQSMessageSES
{
public:

    SESEventType eventType;
    QString eventTypeStr;
    SESBounceType bounceType;
    QString bounceTypeStr;
    QString from;
    QList<QString> recipients;
    QList<QString> to;
    QString source;
    QString subject;
    QString errorMessage;
    QString cickedLink;

    QVariant toVariant();
    QString toString();
    void fillJson(const QJsonObject& data);

    SQSMessageSES();
    ~SQSMessageSES();

private:
    void setEventType(const QString& eventType);
    void setBounceType(const QString& bounceType);
    void collectRecipients(const QJsonObject& data);
};

#endif // SQSMESSAGESES_H
