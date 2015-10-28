//
//  BPTreeNode.cpp
//  MiniSQL
//
//  Created by fan wu on 10/26/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include "BPTreeNode.hpp"

void BPTreeNode::readNodeRawData() {
    BufferManager bufferManager;
    bufferManager.readPage(nodePage);
}

void BPTreeNode::writeNodeRawData() {
    BufferManager bufferManager;
    bufferManager.writePage(nodePage);
}

int BPTreeNode::getNodeRawDataLength() {
//    BPTreeEntry     nodeEntries[1024];
//    int             entryNumber;
//    int             keyDataLength;
//    BPTreeKeyType   keyType;
//    PageIndexType   parentNodePagePointer;
//    PageIndexType   siblingNodePagePointer;
//    Page            nodePage;
//    PageIndexType   nodePath[MAXPATHDEEPTH];
//    BPTreeNodeType  nodeType;
    int accumulator = 0;
    accumulator += sizeof(entryNumber);
    accumulator += sizeof(keyDataLength);
    accumulator += sizeof(BPTreeKeyType);
    accumulator += sizeof(parentNodePagePointer);
    accumulator += sizeof(siblingNodePagePointer);
    accumulator += sizeof(nodeType);
    
    for (int i = 0; i < entryNumber; ++i) {
        accumulator += nodeEntries[i].getEntryDataLength();
    }
    
    return accumulator;
}