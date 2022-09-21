# aws-qt
AWS Qt

Only SQS for SES

### Create account

``` 
QString accessKey = "--";
QString secretKey = "--";
QString region = "us-east-1";
QString accountId = "--";

AwsAccount account(accessKey, secretKey, region, accountId);

``` 

### Request messages

``` 


AwsApiAuth apiAuth;
AwsHttp http;

apiAuth.setAccount(account);
apiAuth.setService("sqs");
apiAuth.setUrlPath("queue-name");
apiAuth.setApiVersion("2012-11-05");
apiAuth.setExpires("30");
//apiAuth.setDebug(true);


apiAuth.addQueryParam("Action", "ReceiveMessage");
apiAuth.addQueryParam("AttributeName", "All");
apiAuth.addQueryParam("MaxNumberOfMessages", 5);
apiAuth.addQueryParam("VisibilityTimeout", "30");

QString authUrl = apiAuth.generateAuthUrl();


QByteArray response = http.get(authUrl);


if(http.error()){
    qDebug() << http.errorMessage();;    
    return;
}

SESJsonProcessor jsonProcessor;

//jsonProcessor.setDebug(true);
QList<SQSMessage> messages = jsonProcessor.processResponse(&response);

if(jsonProcessor.error()){
    qDebug() << jsonPorcessor.errorMessage();
    return;
}

``` 

#### Delete messages

```
    AwsApiAuth apiAuth;
    AwsHttp http;

    apiAuth.setAccount(account);
    apiAuth.setService(this->_service);
    apiAuth.setUrlPath(this->_queue);
    apiAuth.setApiVersion(this->_apiVersion);
    //apiAuth.setDebug(true);

    apiAuth.addQueryParam("Action", "DeleteMessageBatch");

    for(int i = 0; i < messages->size(); i++){
        SQSMessage msg = messages->value(i);

        QString key = QString::number(i+1);
        apiAuth.addQueryParam("DeleteMessageBatchRequestEntry." + key + ".Id", "msg" + key);
        apiAuth.addQueryParam("DeleteMessageBatchRequestEntry." + key + ".ReceiptHandle", QUrl::toPercentEncoding(msg.receiptHandle));
    }

    QString authUrl = apiAuth.generateAuthUrl();


    QByteArray response = http.get(authUrl);

    if(http.error()){
        qDebug() << http.errorMessage();;
        return;
    }

    SQSJsonProcessor jsonProcessor;
    //jsonProcessor.setDebug(true);

    SQSMessageDeleteResult deleteResult = jsonProcessor.processDeleteReponse(&response);

    if(jsonProcessor.error()){
        qDebug() << jsonPorcessor.errorMessage();
        return
    }

    tDebug() << "SQS Messages Delete result = " << deleteResult.toString();

```