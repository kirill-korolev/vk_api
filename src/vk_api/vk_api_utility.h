#ifndef vk_api_utility_h
#define vk_api_utility_h

#include <string>
#include <unordered_map>

namespace vk_api { namespace utils {

    // get parameters
    using params = std::unordered_map<std::string, std::string>;

    std::string build_params(const params& ps);
    params fetch_params(const std::string& str);
    std::string encode_url(const std::string& url);


    struct converter{
        static std::string char_to_hex(const char& c);
    };

    struct curly {
        typedef size_t result_t;
        static const std::string empty_result;
        static result_t writer(char* data, size_t size, size_t nmemb, std::string* buffer);
    };


    std::string request(const std::string& url, const std::string& ps, std::string& curl_buffer);

}}

#endif // vk_api_utility_h
