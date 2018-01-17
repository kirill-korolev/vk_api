#ifndef URLREQUESTINTERCEPTOR_H
#define URLREQUESTINTERCEPTOR_H

#include <QWebEngineUrlRequestInterceptor>

class UrlRequestInterceptor: public QWebEngineUrlRequestInterceptor
{
    Q_OBJECT
public:
    UrlRequestInterceptor(QObject *p = Q_NULLPTR);
    void interceptRequest(QWebEngineUrlRequestInfo &info) override;
};

#endif // URLREQUESTINTERCEPTOR_H
