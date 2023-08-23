//
//  CurlDownloader.cpp
//  Curl download implemention
//
//  Created by Chengjun on 2023/8/22.
//

#include "CUrlDownloader.hpp"
#include <fstream>
#include <iostream>

size_t CurlDownloader::WriteCallback(void* ptr, size_t size, size_t count, void* stream) {
    std::ofstream* file = static_cast<std::ofstream*>(stream);
    if (file) {
        file->write(static_cast<char*>(ptr), size * count);
        return size * count;
    }
    
    return 0;
}

size_t CurlDownloader::HeaderCallback(void* buffer, size_t size, size_t nmemb, void* userData) {
    size_t totalSize = size * nmemb;
    std::string headerLine(static_cast<const char*>(buffer), totalSize);
    const std::string contentLengthHeader = "Content-Length: ";

    size_t contentLengthPos = headerLine.find(contentLengthHeader);
    if (contentLengthPos != std::string::npos) {
        size_t fileSizeStart = contentLengthPos + contentLengthHeader.length();
        size_t fileSizeEnd = headerLine.find("\r\n", fileSizeStart);
        if (fileSizeEnd != std::string::npos) {
            std::string fileSizeStr = headerLine.substr(fileSizeStart, fileSizeEnd - fileSizeStart);
            try {
                size_t downloadSize = std::stoul(fileSizeStr);
                *static_cast<size_t*>(userData) = downloadSize;
            } catch (const std::exception& ex) {
                // Handle conversion error
            }
        }
    }
    return totalSize;
}

bool CurlDownloader::GetFileSize(size_t& file_size){
    if(!m_url){
        m_url = curl_easy_init();
    }
    
    if (m_url) {
        curl_easy_setopt(m_url, CURLOPT_URL, m_sUrl.c_str());
        curl_easy_setopt(m_url, CURLOPT_HEADERFUNCTION, HeaderCallback);
        curl_easy_setopt(m_url, CURLOPT_HEADER, 1L);
        curl_easy_setopt(m_url, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(m_url, CURLOPT_HEADERDATA, &file_size);

        CURLcode res = curl_easy_perform(m_url);
        if (res == CURLE_OK) {
            return true;
        }
        else{
            std::cerr << "Failed to get file size: " << curl_easy_strerror(res) << std::endl;
        }
    }
    return false;
}

bool CurlDownloader::DownloadProcess(long start, long end) {
    std::ofstream outputFile(m_sOutputFilename, std::ios::binary | std::ios::app);
    if(!m_url){
        m_url = curl_easy_init();
    }
    
    if (m_url) {
        curl_easy_setopt(m_url, CURLOPT_URL, m_sUrl.c_str());
        curl_easy_setopt(m_url, CURLOPT_RANGE, (std::to_string(start) + "-" + std::to_string(end)).c_str());
        curl_easy_setopt(m_url, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(m_url, CURLOPT_WRITEDATA, &outputFile);

        CURLcode res = curl_easy_perform(m_url);
        if (res == CURLE_OK) {
            return true;
        }
    }
    return false;
}
