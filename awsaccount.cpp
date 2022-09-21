#include "awsaccount.h"



AwsAccount::AwsAccount(){};

AwsAccount::AwsAccount(const QString& accessKey, const QString& secretKey, const QString& region, const QString& accountId){
    this->_accessKey = accessKey;
    this->_secretKey = secretKey;
    this->_region = region;
    this->_accountId = accountId;
}

AwsAccount::~AwsAccount(){

};

QString AwsAccount::accessKey() const { return this->_accessKey; }
QString AwsAccount::secretKey() const { return this->_secretKey; }
QString AwsAccount::region() const { return this->_region; }
QString AwsAccount::accountId() const { return this->_accountId; }
