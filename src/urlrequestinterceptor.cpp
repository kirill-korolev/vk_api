#include "urlrequestinterceptor.h"
#include "vk_api/vk_api_utility.h"
#include <iostream>

UrlRequestInterceptor::UrlRequestInterceptor(QObject *p): QWebEngineUrlRequestInterceptor(p) {}

void UrlRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info){

    QString urlString = info.requestUrl().url();

    if(urlString.contains("access_token")){
        std::string url = urlString.toUtf8().constData();
        auto params = vk_api::utils::fetch_params(url);

        for(auto& kv: params){
            std::cout << kv.first << "=" << kv.second << std::endl;
        }
    }

}
