//
//  vk_api.cpp
//  vk_api
//
//  Created by Kirill Korolev on 16/01/2018.
//  Copyright © 2018 Kirill Korolev. All rights reserved.
//


#include "vk_api.h"
#include <iostream>

namespace vk_api {
    const std::string constant::auth_url = "https://oauth.vk.com/authorize?";
    const std::string constant::version = "5.69";
    const std::string constant::response_type = "token";
    const std::string constant::redirect_uri = "https://oauth.vk.com/blank.html";
    const std::string constant::display_type = "page";
}


namespace vk_api {
    std::string scopes::to_string(scope_t sc){
        return std::to_string(sc);
    }
}

