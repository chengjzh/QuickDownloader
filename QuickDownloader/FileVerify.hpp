//
//  FileVerify.hpp
//  Check file whether it's valid
//
//  Created by 张成 on 2023/8/23.
//

#ifndef FileVerify_hpp
#define FileVerify_hpp
#include <string>

class FileVerify{
public:
    static bool VerifyMD5(const std::string& expectMD5, const std::string& fileName);
};
#endif /* FileVerify_hpp */
