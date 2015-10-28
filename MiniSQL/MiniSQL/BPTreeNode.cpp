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

void BPTreeNode::convertToRawData() {
    char *cursor = nodePage.pageData;
    memcpy(cursor, &entryNumber, sizeof(entryNumber));
    cursor += sizeof(entryNumber);
    memcpy(cursor, &keyDataLength, sizeof(keyDataLength));
    cursor += sizeof(keyDataLength);
    memcpy(cursor, &keyType, sizeof(keyType));
    cursor += sizeof(keyType);
    memcpy(cursor, &parentNodePagePointer, sizeof(parentNodePagePointer));
    cursor += sizeof(parentNodePagePointer);
    memcpy(cursor, &siblingNodePagePointer, sizeof(siblingNodePagePointer));
    cursor += sizeof(siblingNodePagePointer);
    memcpy(cursor, &nodeType, sizeof(nodeType));
    cursor += sizeof(nodeType);

    for (int i = 0; i < entryNumber; ++i) {
        nodeEntries[i].key.convertToRawData();
        memcpy(cursor, nodeEntries[i].key.rawData, nodeEntries[i].key.getKeyDataLength());
        cursor += nodeEntries[i].key.getKeyDataLength();
        memcpy(cursor, &nodeEntries[i].pagePointer, sizeof(PageIndexType));
        cursor += sizeof(PageIndexType);
    }
}

void BPTreeNode::parseFromRawData() {
    char *cursor = nodePage.pageData;
    memcpy(&entryNumber, cursor, sizeof(entryNumber));
    cursor += sizeof(entryNumber);
    memcpy(&keyDataLength, cursor, sizeof(keyDataLength));
    cursor += sizeof(keyDataLength);
    memcpy(&keyType, cursor, sizeof(keyType));
    cursor += sizeof(keyType);
    memcpy(&parentNodePagePointer, cursor, sizeof(parentNodePagePointer));
    cursor += sizeof(parentNodePagePointer);
    memcpy(&siblingNodePagePointer, cursor, sizeof(siblingNodePagePointer));
    cursor += sizeof(siblingNodePagePointer);
    memcpy(&nodeType, cursor, sizeof(nodeType));
    cursor += sizeof(nodeType);
    
    for (int i = 0; i < entryNumber; ++i) {
        nodeEntries[i].key.type = keyType;
        nodeEntries[i].key.keyLen = keyDataLength;
        memcpy(nodeEntries[i].key.rawData, cursor, nodeEntries[i].getEntryDataLength());
        nodeEntries[i].key.parseFromRawData();
        cursor += nodeEntries[i].key.getKeyDataLength();
        memcpy(cursor, &nodeEntries[i].pagePointer, sizeof(PageIndexType));
        cursor += sizeof(PageIndexType);
    }
}


bool BPTreeNode::isOverflow() {
    return getNodeRawDataLength() > PAGESIZE;
}

bool BPTreeNode::isLeaf() {
    return nodeType == BPTreeNodeType::BPTreeLeafNode;
}

bool BPTreeNode::isRoot() {
    return nodeType == BPTreeNodeType::BPTreeRootNode;
}

bool BPTreeNode::insertEntry(BPTreeEntry entry) {
    assert(entry.key.type != BPTreeKeyType::UNDEFINED);
    int insertPoint;
    for (insertPoint = 0; insertPoint < entryNumber; ++insertPoint)
        if (nodeEntries[insertPoint].key > entry.key) break;
    return insertEntryAtIndex(entry, insertPoint);
}

bool BPTreeNode::deleteEntry(BPTreeEntry entry) {
    int deletePoint;
    for (deletePoint = 0; deletePoint < entryNumber; ++deletePoint)
        if (nodeEntries[deletePoint].key == entry.key) break;
    if (deletePoint == entryNumber) return false;
    return deleteEntryAtIndex(deletePoint);
}

bool BPTreeNode::insertEntryAtIndex(BPTreeEntry entry, int index) {
    assert(index >= 0);
    assert(index <= entryNumber);
    for (int i = entryNumber - 1; i >= index; --i) {
        nodeEntries[i + 1]  = nodeEntries[i];
    }
    nodeEntries[index] = entry;
    entryNumber++;
    return true;
}

bool BPTreeNode::deleteEntryAtIndex(int index) {
    assert(index >= 0);
    assert(index < entryNumber);
    for (int i = index; i < entryNumber; ++i) {
        nodeEntries[i] = nodeEntries[i + 1];
    }
    entryNumber--;
    return true;
}

int BPTreeNode::getNodeRawDataLength() {
    int accumulator = 0;
    accumulator += sizeof(entryNumber);
    accumulator += sizeof(keyDataLength);
    accumulator += sizeof(keyType);
    accumulator += sizeof(parentNodePagePointer);
    accumulator += sizeof(siblingNodePagePointer);
    accumulator += sizeof(nodeType);

    for (int i = 0; i < entryNumber; ++i) {
        accumulator += nodeEntries[i].getEntryDataLength();
    }

    return accumulator;
}
