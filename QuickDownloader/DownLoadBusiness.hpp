//
//  DownloadBusiness.hpp
//  Main logic for Download
//
//  Created by 张成 on 2023/8/22.
//

#ifndef DownloadBusiness_hpp
#define DownloadBusiness_hpp

#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <fstream>
#include <chrono>
#include "HTTPProtocol.hpp"
#include "ProtocolFactory.hpp"

template <typename ProtocolType>
class Initializer {
public:
    Initializer() {
        if(std::is_same<ProtocolType, HTTPProtocol>::value){
            curl_global_init(CURL_GLOBAL_ALL);
        }
    }

    ~Initializer() {
        if(std::is_same<ProtocolType, HTTPProtocol>::value){
            curl_global_cleanup();
        }
    }
};

class DownLoadBusiness{
public:
    template <typename ProtocolType>
    static bool Download(const std::string& url, const std::string& fileName){

        auto startTime = std::chrono::high_resolution_clock::now();
        //1. init protocol
        Initializer<ProtocolType> curInitializer;
        
        //2. caluate file size and get thread count
        size_t fileSize = 0;
        bool ret = ProtocolFactory::CreateProtocol<ProtocolType>()->GetFileSize(url, fileName, fileSize);
        if(!ret || fileSize == 0){
            std::cout << " get file size failed or file size is 0, url=" << url << std::endl;
            return false;
        }
        else{
            ShowFileSize(fileSize);
        }
        
        int thread_count = CalcluateThreadCount(fileSize);
        const long segment_size = fileSize / thread_count;
        std::vector<std::thread> threads;
        std::mutex mutex;
        
        //3. run on muti thread
        for (int i = 0; i < thread_count; ++i) {
            long start = i * segment_size;
            long end = (i == thread_count - 1) ? fileSize - 1 : start + segment_size - 1;
            std::cout<< "start to download file " << fileName << " ["<<start<<","<<end<<"]"<< std::endl;
            
            threads.emplace_back([=,&mutex]() {
                bool ret = ProtocolFactory::CreateProtocol<ProtocolType>()->Download(url, fileName + std::to_string(i), start, end);
                {
                    std::lock_guard<std::mutex> lock(mutex);
                    std::cout << "download file " << fileName <<  " ["<<start<<","<<end<<"] result = " << (ret?"success":"fail") << std::endl;
                }
                
            });
        }

        //4. wait to complement
        for (auto& thread : threads) {
            thread.join();
        }
        
        //5. Merge downloaded segments into a single file
        std::ofstream final_output(fileName, std::ios::binary);
        for (int i = 0; i < thread_count; ++i) {
            std::ifstream segment(fileName + std::to_string(i), std::ios::binary);
            final_output << segment.rdbuf();
            segment.close();
            std::remove((fileName + std::to_string(i)).c_str());
        }
        
        // End the timer
        auto endTime = std::chrono::high_resolution_clock::now();

        // Calculate the duration
        std::chrono::duration<double> duration = endTime - startTime;

        // Print the elapsed time in seconds
        std::cout << "Download success, it took " << duration.count() << " seconds" << std::endl;

        return true;
    }
    
private:
    static int CalcluateThreadCount(size_t fileSize){
        const int min_thread_size = 1; // Minimum number of threads
        const int max_thread_size = 8; // Maximum number of threads
        constexpr size_t one_split_size = 1024 * 100; // 1M
        return std::min(max_thread_size, std::max(min_thread_size, static_cast<int> (fileSize/one_split_size)));
    }
    
    static void ShowFileSize(size_t fileSize){
        std::cout << "file size is ";
        constexpr int GB_SIZE = 1024 * 1024 * 1024;
        constexpr int MB_SIZE = 1024 * 1024;
        constexpr int KB_SIZE = 1024;
        
        if(fileSize > GB_SIZE){
            std::cout << fileSize * 1.0 / GB_SIZE << "GB" << std::endl;
        }
        else if(fileSize > MB_SIZE){
            std::cout << fileSize * 1.0 / MB_SIZE << "MB" << std::endl;
        }
        else if(fileSize > KB_SIZE){
            std::cout << fileSize * 1.0 / KB_SIZE << "KB" << std::endl;
        }
        else{
            std::cout << fileSize << "B" << std::endl;
        }
    }
};

#endif /* DownloadBusiness_hpp */
