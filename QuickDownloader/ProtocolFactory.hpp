//
//  ProtocolFactory.h
//  Generate Protocol Factory
//
//  Created by Chengjun on 2023/8/21.
//
#ifndef NetworkWorker_h
#define NetworkWorker_h
#include "Protocol.hpp"
#include <memory>

class ProtocolFactory {
public:
    template <typename ProtocolType>
    static std::unique_ptr<IProtocol> CreateProtocol(){
        std::unique_ptr<IProtocol> pProtocol(new ProtocolType);
        return pProtocol;
    }
};

#endif /* ProtocolFactory */
