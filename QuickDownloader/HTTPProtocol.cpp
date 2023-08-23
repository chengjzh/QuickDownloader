//
//  HTTPProtocol.cpp
//  
//
//  Created by Chengjun on 2023/8/21.
//

#include "HTTPProtocol.hpp"
#include <iostream>
#include "CUrlDownloader.hpp"

bool HTTPProtocol::Download(const std::string& url, const std::string& filename, long start, long end){
    if(m_pCurl == nullptr){
        m_pCurl.reset(new CurlDownloader(url, filename));
    }
    return  m_pCurl->DownloadProcess(start, end);
}

bool HTTPProtocol::GetFileSize(const std::string& url, const std::string& filename, size_t& fileSize){
    if(m_pCurl == nullptr){
        m_pCurl.reset(new CurlDownloader(url, filename));
    }
    
    return m_pCurl->GetFileSize(fileSize);
}
