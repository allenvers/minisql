//
//  Global.hpp
//  MiniSQL
//
//  Created by fan wu on 10/16/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#ifndef Global_hpp
#define Global_hpp

#include "assert.h"

typedef int PageIndex;
const int PAGESIZE = 4096 * sizeof(char);
const PageIndex UNDEFINEED_PAGE_NUM = 0xFFFFFFFF;

#endif