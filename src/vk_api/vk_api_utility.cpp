#include "vk_api_utility.h"
#include <curl/curl.h>

namespace vk_api { namespace utils {

    std::string converter::char_to_hex(const char& c){

        // first position:
        // x1 x2 x3 x4 x5 x6 x7 x8
        // 1  1  1  1  0  0  0  0
        // _______________________
        // 0  0  0  0  x1 x2 x3 x4

        // second position:
        // x1 x2 x3 x4 x5 x6 x7 x8
        // 0  0  0  0  1  1  1  1
        // _______________________
        // 0  0  0  0  x5 x6 x7 x8

        char first = (c & 0xF0) >> 4;
        char second = c & 0x0F;

        // char(48) == 0
        // 0 <= x <= 9

        // char(97) == a
        // 10 <= x <= 15

        if(0 <= first && first <= 9) first += 48;
        if(10 <= first && first <= 15) first += 87;
        if(0 <= second && second <= 9) second += 48;
        if(10 <= second && second <= 15) second += 87;

        std::string result;
        result.append(&first, 1);
        result.append(&second, 1);
        return result;
    }
}}

namespace vk_api { namespace utils{

    const std::string curly::empty_result = "";

    curly::result_t curly::writer(char* data, size_t size, size_t nmemb, std::string* buffer){
        result_t result = 0;

        if(buffer != nullptr){
            buffer->append(data, size * nmemb);
            result = size * nmemb;
        }

        return result;
    }

}}

namespace vk_api { namespace utils{

    std::string encode_url(const std::string& url){
        std::string result;

        for(auto &c: url){
            if((48 <= c && c <= 57) ||
               (65 <= c && c <= 90) ||
               (97 <= c && c <= 122) ||
               (c == '~' || c == '!' || c == '*' || c == '(' || c == ')' || c == '\'')){

                result.append(&c, 1);

            } else {
                result.append("%");
                result.append(converter::char_to_hex(c));
            }
        }

        return result;
    }

    std::string build_params(const params& ps){
        std::string result;

        for(auto &item: ps){
            result.append(item.first + "=" + encode_url(item.second) + "&");
        }

        result.pop_back();
        return result;
    }

    params fetch_params(const std::string& str){
        params ps;

        size_t start = str.find("?", 0) + 1;
        size_t end = 0;
        if(start == 0) start = str.find("#", 0) + 1;

        if(start != 0) {
            while(end < str.size()){
                end = str.find("=", start);
                if(end == -1) break;
                std::string key = str.substr(start, end - start);
                start = end + 1;
                size_t t = str.find("&", start);
                end = t != -1 ? t : str.size();
                std::string value = str.substr(start, end - start);
                if(value.size() == 0) continue;
                ps.insert(std::make_pair(key, value));
                start = end + 1;
            }
        }

        return ps;
    }

}}

namespace vk_api { namespace utils {

    std::string request(const std::string& url, const std::string& ps, std::string& curl_buffer){

        char errorBuffer[CURL_ERROR_SIZE];
        curl_buffer.clear();

        CURL* curl;
        CURLcode result;

        curl = curl_easy_init();

        if(curl){
            curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "vk_api");
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, ps.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curly::writer);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curl_buffer);
            result = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if(result == CURLE_OK) {
                return curl_buffer;
            } else {
                return errorBuffer;
            }
        }

        curl_easy_cleanup(curl);
        return curly::empty_result;
    }

}}
