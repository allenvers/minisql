//
//  BPTree.hpp
//  MiniSQL
//
//  Created by fan wu on 10/29/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#ifndef BPTree_hpp
#define BPTree_hpp

#include "BPTreeKey.hpp"
#include "BPTreeEntry.hpp"
#include "BPTreeNode.hpp"
#include "BufferManager.cpp"
#include "Global.h"
#include "Page.hpp"
#include <string>

using namespace std;

class BPTree {
public:
    BPTree(string tableName, string attributeName, BPTreeKeyType keyType, int keyDataLength) {
        assert(tableName != "");
        assert(attributeName != "");
        this->tableName = tableName;
        this->attributeName = attributeName;
        this->keyType = keyType;
        this->keyDataLength = keyDataLength;
        BPTreeNode node = getNodeAtPage(ROOTPAGE);
        if (node.nodeType == BPTreeNodeType::BPTreeUndefinedNode) {
            node.nodeEntries[0].pagePointer = UNDEFINEED_PAGE_NUM;
            node.entryNumber = 1;
            node.keyDataLength = keyDataLength;
            node.keyType = keyType;
            node.parentNodePagePointer = UNDEFINEED_PAGE_NUM;
            node.siblingNodePagePointer = UNDEFINEED_PAGE_NUM;
            node.nodeType = BPTreeNodeType::BPTreeLeafNode;
            node.writeNode();
        }
    }
    
    ~BPTree() {}
    
    PageIndexType getLeadingPage();
    
    BPTreeNode getNodeAtPage(PageIndexType pageIndex);
    
    bool insertKeyPointerPair(BPTreeKey key, PageIndexType pagePointer);
    
    bool isRoot(BPTreeNode node);
    
    BPTreeKey getMaxKey(BPTreeNode node);
    BPTreeKey getMinKey(BPTreeNode node);
    
    string          tableName;
    string          attributeName;
    BPTreeKeyType   keyType;
    int             keyDataLength;
};

#endif /* BPTree_hpp */
