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

typedef int PageIndexType;
const int PAGESIZE = 4096 * sizeof(char);
const PageIndexType UNDEFINEED_PAGE_NUM = -1;

#endif