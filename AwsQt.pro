QT -= gui
QT += core network

TARGET = AwsQt

TEMPLATE = lib
DEFINES += AWSQT_LIBRARY
win32:CONFIG += dll

#CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    awsaccount.cpp \
    awsapiauth.cpp \
    awshttp.cpp \
    jsonparser.cpp \
    sesjsonprocessor.cpp \
    sqsjsonprocessor.cpp \
    sqsmessage.cpp \
    sqsmessagedeleteresult.cpp \
    sqsmessagedeleteresultitem.cpp \
    sqsmessageses.cpp

HEADERS += \
    AwsQtMime \
    awsaccount.h \
    awsapiauth.h \
    awshttp.h \
    awsqt_global.h \
    jsonparser.h \
    sesjsonprocessor.h \
    sqsjsonprocessor.h \
    sqsmessage.h \
    sqsmessagedeleteresult.h \
    sqsmessagedeleteresultitem.h \
    sqsmessageses.h

# Default rules for deployment.
unix {
    headers.files = $$HEADERS
    headers.path = /usr/include/AwsQt
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target headers
