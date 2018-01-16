//
//  vk_api.h
//  vk_api
//
//  Created by Kirill Korolev on 16/01/2018.
//  Copyright © 2018 Kirill Korolev. All rights reserved.
//

#ifndef vk_api_h
#define vk_api_h

#include <string>
#include <unordered_map>

namespace vk_api {
    
    // get parameters
    using params = std::unordered_map<std::string, std::string>;
    
    // vk_api constants
    struct constant{
        static const std::string auth_url;
        static const std::string version;
        static const std::string response_type;
        static const std::string redirect_uri;
        static const std::string display_type;
    };
    
    // utility methods
    struct utility{
        static std::string build_params(const params& ps);
        static std::string encode_url(const std::string& url);
    };
    
    struct converter{
        static std::string char_to_hex(const char& c);
    };
    
    // api permissions scopes
    struct scopes{
        using scope_t = const long;
        
        static scope_t notify = 1 << 0;
        static scope_t friends = 1 << 1;
        static scope_t photos = 1 << 2;
        static scope_t audio = 1 << 3;
        static scope_t video = 1 << 4;
        static scope_t pages = 1 << 5;
        static scope_t sidebar = 1 << 6;
        static scope_t status = 1 << 7;
        static scope_t notes = 1 << 8;
        static scope_t messages = 1 << 9;
        static scope_t wall = 1 << 10;
        static scope_t ads = 1 << 11;
        static scope_t offline = 1 << 12;
        static scope_t docs = 1 << 13;
        static scope_t groups = 1 << 14;
        static scope_t notifications = 1 << 15;
        static scope_t stats = 1 << 16;
        static scope_t email = 1 << 17;
        static scope_t market = 1 << 18;
        
        static std::string to_string(scope_t sc);
    };
    
    struct curly{
        typedef size_t result_t;
        static const std::string empty_result;
        static result_t writer(char* data, size_t size, size_t nmemb, std::string* buffer);
    };
    
    typedef std::string (*auth_callback)(const std::string&);

    bool auth(const std::string& client_id,
              scopes::scope_t scopes,
              auth_callback f,
              const std::string& redirect_uri=constant::redirect_uri);
    
    std::string request(const std::string& url, const std::string& ps, std::string& curl_buffer);
}

#endif /* vk_api_h */
