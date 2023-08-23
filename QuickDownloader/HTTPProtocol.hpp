//
//  HTTPProtocol.h
//  HTTP implementation
//
//  Created by Chengjun on 2023/8/21.
//

#ifndef HTTPProtocol_h
#define HTTPProtocol_h
#include "Protocol.hpp"
#include "CUrlDownloader.hpp"
#include <memory>

// HTTP protocol implementation
class HTTPProtocol : public IProtocol {
public:
    bool Download(const std::string& url, const std::string& filename,long start, long end) override;
    bool GetFileSize(const std::string& url, const std::string& filename, size_t& fileSize) override;
    
private:
    std::unique_ptr<CurlDownloader> m_pCurl = nullptr;
};
#endif /* HTTPProtocol_h */
