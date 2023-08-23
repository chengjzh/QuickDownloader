//
//  main.cpp
//
//
//  Created by Chengjun on 2023/8/21.
//

#include <iostream>
#include "DownLoadBusiness.hpp"
#include "HTTPProtocol.hpp"
#include "FileVerify.hpp"

int main(int argc, const char * argv[]) {
    
    //1. check the paramter
    //command line Usage
    //argv[1] : download url
    //argv[2] : save the output file after we download it.
    //argv[3] : check whether the file is valid. If miss this paramter, it will ignore verify process
    
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <URL> <OutputFile> <ExpectMD5> " << std::endl;
        std::cerr << "Note: expect MD5 is optional" << std::endl;
        return 1;
    }

    std::string url = argv[1];
    std::string output = argv[2];
    std::string expectMD5Value;
    if(argc == 4){
        expectMD5Value = argv[3];
    }
    
    //2. execute download logic
    bool ret = DownLoadBusiness::Download<HTTPProtocol>(url , output);
    if(!ret){
        std::cerr << "download failed..." << std::endl;
        return 1;
    }
    
    //3. verify the MD5 if finished download
    if(!expectMD5Value.empty()){
        return FileVerify::VerifyMD5(expectMD5Value, output)?0:1;
    }
    
    return 0;
}


