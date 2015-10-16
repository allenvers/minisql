//
//  Global.hpp
//  MiniSQL
//
//  Created by fan wu on 10/16/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include "assert.h"

typedef unsigned long long PageIndex;
const int PAGESIZE = 4096 * sizeof(char);
const PageIndex UNDEFINEED_PAGE = 0xFFFFFFFFFFFFFFFF;