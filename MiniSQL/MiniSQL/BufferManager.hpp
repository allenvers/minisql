//
//  BufferManager.hpp
//  MiniSQL
//
//  Created by fan wu on 10/16/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#ifndef BufferManager_hpp
#define BufferManager_hpp

#include "Global.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


class BufferManager {
    BufferManager() {
        if (mkdir("./RecordFiles", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
            //TODO
        }
        if (mkdir("./IndexFiles", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
            //TODO
        }
        if (mkdir("./RecordCatalogFiles", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
            //TODO
        }
        if (mkdir("./IndexCatalogFiles", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
            //TODO
        }
        // 初始化存放文件的文件夹，根据表名以及索引键建立文件
    }
};


#endif /* BufferManager_hpp */
