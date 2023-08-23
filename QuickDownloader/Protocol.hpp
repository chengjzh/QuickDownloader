//
//  IProtocol.h
//  Basic inteface for Protocol
//
//  Created by Chengjun on 2023/8/21.
//

#ifndef IProtocol_h
#define IProtocol_h
#include <string>
// Abstract base class for different protocols
class IProtocol {
public:
    virtual bool Download(const std::string& url, const std::string& filename,long start, long end) = 0;
    virtual bool GetFileSize(const std::string& url, const std::string& filename, size_t& fileSize) = 0;
    virtual ~IProtocol() {}
};

#endif /* Protocol_h */
