//
//  BPTreeEntry.hpp
//  MiniSQL
//
//  Created by fan wu on 10/25/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#ifndef BPTreeEntry_hpp
#define BPTreeEntry_hpp

#include "BPTreeKey.hpp"
#include <iostream>
#include "Global.h"

using namespace std;

class BPTreeEntry {
public:
    
    int getEntryDataLength();
    
    BPTreeKey       key;
    PageIndexType   pagePointer;
};

#endif /* BPTreeEntry_hpp */
