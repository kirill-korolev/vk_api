#include "mainwindow.h"
#include "urlrequestinterceptor.h"
#include <QWebEngineProfile>
#include <QApplication>

#include "vk_api/vk_api_utility.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QWebEngineUrlRequestInterceptor* interceptor = new UrlRequestInterceptor(&w);
    QWebEngineProfile::defaultProfile()->setRequestInterceptor(interceptor);

    return a.exec();
}

