//
//  CurlDownloader.hpp
//  Curl download define
//
//  Created by Chengjun on 2023/8/22.
//

#ifndef CURLMethod_hpp
#define CURLMethod_hpp
#include <curl/curl.h>
#include <string>

class CurlDownloader{
public:
    CurlDownloader(const std::string& url, const std::string& outputName): m_sUrl{url},m_sOutputFilename{outputName}{
    }
    
    
    ~CurlDownloader(){
        if(m_url){
            curl_easy_cleanup(m_url);
        }
    }
    
    CurlDownloader(CurlDownloader&& downloader) noexcept: m_url(downloader.m_url),m_sUrl(downloader.m_sUrl),m_sOutputFilename(downloader.m_sOutputFilename){
        downloader.m_url = nullptr;
    }
    
    CurlDownloader(const CurlDownloader& curl) = delete;
    CurlDownloader& operator=(const CurlDownloader& curl) = delete;
    
    bool GetFileSize(size_t& file_size);
    bool DownloadProcess(long start, long end);
    
public:
    static size_t WriteCallback(void* ptr, size_t size, size_t count, void* stream);
    // Callback function to gather download size from response headers
    static size_t HeaderCallback(void* buffer, size_t size, size_t nmemb, void* userData);
    
private:
    CURL* m_url = nullptr;
    std::string m_sUrl;
    std::string m_sOutputFilename;
};

#endif /* CurlDownloader */
