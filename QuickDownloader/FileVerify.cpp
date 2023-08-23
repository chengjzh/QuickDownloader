//
//  FileVerify.cpp
//  Check file whether it's valid
//
//  Created by Chengjun on 2023/8/23.
//

#include "FileVerify.hpp"
#include <openssl/evp.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

bool FileVerify::VerifyMD5(const std::string& expectMD5, const std::string& fileName){
    if(expectMD5.empty()){
        return true;
    }
    
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for calculating MD5" << std::endl;
        return false;
    }

    EVP_MD_CTX* md5Context = EVP_MD_CTX_new();
    if (!md5Context) {
        std::cerr << "Failed to create MD5 context" << std::endl;
        return false;
    }

    EVP_DigestInit_ex(md5Context, EVP_md5(), nullptr);

    char buffer[1024];
    while (!file.eof()) {
        file.read(buffer, sizeof(buffer));
        EVP_DigestUpdate(md5Context, buffer, file.gcount());
    }

    unsigned char md5Digest[EVP_MAX_MD_SIZE];
    unsigned int md5DigestLength;
    EVP_DigestFinal_ex(md5Context, md5Digest, &md5DigestLength);

    EVP_MD_CTX_free(md5Context);

    std::stringstream ss;
    for (unsigned int i = 0; i < md5DigestLength; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(md5Digest[i]);
    }

    if(ss.str() != expectMD5){
        std::cerr << "verify failed, expectMD5=" << expectMD5 << ",currentMD5=" <<ss.str()<< std::endl;
        return false;
    }
    
    std::cout << "file verify success, md5=" << expectMD5 << std::endl;
    return true;
}
