//
//  vk_api.h
//  vk_api
//
//  Created by Kirill Korolev on 16/01/2018.
//  Copyright © 2018 Kirill Korolev. All rights reserved.
//

#ifndef vk_api_h
#define vk_api_h

#include "vk_api_utility.h"
#include <string>
#include <unordered_map>

namespace vk_api {
    
    // vk_api constants
    struct constant{
        static const std::string auth_url;
        static const std::string version;
        static const std::string response_type;
        static const std::string redirect_uri;
        static const std::string display_type;
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
    
}

namespace vk_api {

    template <typename callback_function>
    bool auth(const std::string& client_id,
              scopes::scope_t scopes,
              callback_function f,
              const std::string& redirect_uri=constant::redirect_uri){

        utils::params ps = {
            { "client_id", client_id },
            { "scope", scopes::to_string(scopes) },
            { "redirect_uri", redirect_uri },
            { "response_type", constant::response_type },
            { "v", constant::version }
        };

        std::string ps_encoded = utils::build_params(ps);
        std::string curl_buffer;
        std::string response = utils::request(constant::auth_url, ps_encoded, curl_buffer);

        if(response == utils::curly::empty_result) {
            return false;
        }

        std::string tokenized_str = f(response);

        return true;
    }
}

#endif /* vk_api_h */
