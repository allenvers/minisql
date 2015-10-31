//
//  BPTree.cpp
//  MiniSQL
//
//  Created by fan wu on 10/29/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include "BPTree.hpp"

BPTreeNode BPTree::splitLeaveNode(BPTreeNode &node) {
    BPTreeNode newNode(createNode());
    Page tempPage = newNode.nodePage;
    newNode = node;
    newNode.nodePage = tempPage;
    node.siblingNodePagePointer = newNode.nodePage.pageIndex;
    
    int mid = node.entryNumber / 2;
    node.entryNumber = mid;
    
    for (int i = mid; i < newNode.entryNumber; ++i) {
        newNode.nodeEntries[i - mid + 1] = newNode.nodeEntries[i];
    }
    newNode.entryNumber -= mid - 1;
    return newNode;
}

BPTreeNode BPTree::splitInternalNode(BPTreeNode &node) {
    BPTreeNode newNode = createNode();
    Page tempPage = newNode.nodePage;
    newNode = node;
    newNode.nodePage = tempPage;
    node.siblingNodePagePointer = newNode.nodePage.pageIndex;
    
    int mid = node.entryNumber / 2;
    node.entryNumber = mid;
    
    for (int i = mid; i < newNode.entryNumber; ++i) {
        newNode.nodeEntries[i - mid] = newNode.nodeEntries[i];
    }
    newNode.entryNumber -= mid;
    return newNode;
}

BPTreeNode BPTree::createNode() {
    BPTreeNode node;
    node.nodeEntries[0].pagePointer = UNDEFINEED_PAGE_NUM;
    node.entryNumber = 1;
    node.keyDataLength = keyDataLength;
    node.keyType = keyType;
    node.parentNodePagePointer = UNDEFINEED_PAGE_NUM;
    node.siblingNodePagePointer = UNDEFINEED_PAGE_NUM;
    node.nodeType = BPTreeNodeType::BPTreeUndefinedNode;
    
    node.nodePage.tableName = tableName;
    node.nodePage.attributeName = attributeName;
    node.nodePage.pageType = PageType::IndexPage;
    BufferManager bufferManager;
    bufferManager.allocatePage(node.nodePage);
    return node;
}

bool BPTree::deleteNode(BPTreeNode &node) {
    BufferManager bufferManager;
    return bufferManager.deallocatePage(node.nodePage);
}

PageIndexType BPTree::getLeadingPage() {
    return getLeadingPageAtNode(getNodeAtPage(ROOTPAGE));
}

PageIndexType BPTree::getLeadingPageAtNode(BPTreeNode node) {
    assert(node.nodeType != BPTreeNodeType::BPTreeUndefinedNode);
    assert(!node.isEmpty());
    if (node.nodeType == BPTreeNodeType::BPTreeLeafNode) {
        return node.nodePage.pageIndex;
    } else {
        return getLeadingPageAtNode(getNodeAtPage(node.nodeEntries[0].pagePointer));
    }
}

BPTreeNode BPTree::getNodeAtPage(PageIndexType pageIndex) {
    BPTreeNode node;
    node.nodePage.tableName     = tableName;
    node.nodePage.attributeName = attributeName;
    node.nodePage.pageType      = PageType::IndexPage;
    node.nodePage.pageIndex     = pageIndex;
    node.readNode();
    return node;
}

bool BPTree::insertKeyPointerPair(BPTreeKey key, PageIndexType pagePointer) {
    assert(key.type == keyType);
    assert(pagePointer != UNDEFINEED_PAGE_NUM);
    assert(key.keyLen == keyDataLength);
    BPTreeEntry entry;
    entry.key         = key;
    entry.pagePointer = pagePointer;
    BPTreeNode tempNode = getNodeAtPage(ROOTPAGE);
    return this->insertEntryIntoNode(entry, tempNode);
}

bool BPTree::insertEntryIntoNode(BPTreeEntry entry, BPTreeNode node) {
    assert(node.nodeType != BPTreeNodeType::BPTreeUndefinedNode);
    if (node.nodeType == BPTreeNodeType::BPTreeInternalNode) {
        if (entry.key < node.nodeEntries[1].key) {
            BPTreeNode tempNode = getNodeAtPage(node.nodeEntries[0].pagePointer);
            return this->insertEntryIntoNode(entry, tempNode);
        } else {
            for (int i = 1; i < node.entryNumber; ++i) {
                if (entry.key >= node.nodeEntries[i].key) {
                    BPTreeNode node2 = getNodeAtPage(node.nodeEntries[i].pagePointer);
                    return this->insertEntryIntoNode(entry, getNodeAtPage(node.nodeEntries[i].pagePointer));
                }
            }
        }
    } else if (node.nodeType == BPTreeNodeType::BPTreeLeafNode) {
        node.insertEntry(entry);
        if (!node.isOverflow()) {
            node.writeNode();
            return true;
        } else {
            if (!isRoot(node)) {
                BPTreeNode newNode = splitLeaveNode(node);
                node.writeNode();
                newNode.writeNode();
                BPTreeEntry entry;
                entry.key = getMinKey(newNode);
                entry.pagePointer = newNode.nodePage.pageIndex;
                return updateEntryIntoNode(entry, getNodeAtPage(node.parentNodePagePointer));
            } else {
                BPTreeNode leftNode = createNode();
                Page tempPage = leftNode.nodePage;
                leftNode = node;
                leftNode.nodePage = tempPage;
                BPTreeNode rightNode = splitLeaveNode(leftNode);
                
                leftNode.parentNodePagePointer = node.nodePage.pageIndex;
                rightNode.parentNodePagePointer = node.nodePage.pageIndex;
                
                leftNode.writeNode();
                rightNode.writeNode();
                
                node.clearNode();
                node.entryNumber = 2;
                node.nodeEntries[0].pagePointer = leftNode.nodePage.pageIndex;
                node.nodeEntries[1].pagePointer = rightNode.nodePage.pageIndex;
                node.nodeEntries[1].key = getMinKey(rightNode);
                node.nodeType = BPTreeNodeType::BPTreeInternalNode;
                node.writeNode();
                return true;
            }
        }
    }
    assert(false); // Error
    return false;
}

bool BPTree::updateEntryIntoNode(BPTreeEntry entry, BPTreeNode node) {
    assert(node.nodeType != BPTreeNodeType::BPTreeUndefinedNode);
    node.insertEntry(entry);
    if (!node.isOverflow()) {
        node.writeNode();
        return true;
    } else {
        if (!isRoot(node)) {
            BPTreeNode newNode = splitInternalNode(node);
            node.writeNode();
            newNode.writeNode();
            BPTreeEntry entry;
            entry.key = getMinKey(newNode);
            entry.pagePointer = newNode.nodePage.pageIndex;
            return updateEntryIntoNode(entry, getNodeAtPage(node.parentNodePagePointer));
        } else {
            BPTreeNode leftNode = createNode();
            Page tempPage = leftNode.nodePage;
            leftNode = node;
            leftNode.nodePage = tempPage;
            BPTreeNode rightNode = splitInternalNode(leftNode);
            
            leftNode.parentNodePagePointer = node.nodePage.pageIndex;
            rightNode.parentNodePagePointer = node.nodePage.pageIndex;
            
            leftNode.writeNode();
            rightNode.writeNode();
            
            node.clearNode();
            node.entryNumber = 2;
            node.nodeEntries[0].pagePointer = leftNode.nodePage.pageIndex;
            node.nodeEntries[1].pagePointer = rightNode.nodePage.pageIndex;
            node.nodeEntries[1].key = getMinKey(rightNode);
            node.nodeType = BPTreeNodeType::BPTreeInternalNode;
            node.writeNode();
            return true;
        }
    }
    assert(false);
    return false;
}

PageIndexType BPTree::searchKeyForPagePointer(BPTreeKey key) {
    assert(key.type == keyType);
    assert(key.keyLen == keyDataLength);
    return searchKeyForPagePointerInNode(key, getNodeAtPage(ROOTPAGE));
}

PageIndexType BPTree::searchKeyForPagePointerInNode(BPTreeKey key, BPTreeNode node) {
    assert(key.keyLen == node.keyDataLength);
    assert(key.type == node.keyType);
    if (node.nodeType == BPTreeNodeType::BPTreeLeafNode) {
        for (int i = 0; i < node.entryNumber; ++i) {
            if (node.nodeEntries[i].key == key)
                return node.nodeEntries[i].pagePointer;
        }
    } else if (node.nodeType == BPTreeNodeType::BPTreeInternalNode) {
        if (key < node.nodeEntries[1].key) {
            return searchKeyForPagePointerInNode(key, getNodeAtPage(node.nodeEntries[0].pagePointer));
        } else {
            for (int i = 1; i < node.entryNumber; ++i) {
                if (key >= node.nodeEntries[i].key)
                    return searchKeyForPagePointerInNode(key, getNodeAtPage(node.nodeEntries[i].pagePointer));
            }
        }
    }
    assert(false); // Error
}

bool BPTree::isRoot(BPTreeNode node) {
    return node.nodePage.pageIndex == ROOTPAGE;
}

BPTreeKey BPTree::getMaxKey(BPTreeNode node) {
    assert(node.nodeType != BPTreeNodeType::BPTreeUndefinedNode);
    assert(!node.isEmpty());
    if (node.nodeType == BPTreeNodeType::BPTreeLeafNode) {
        return node.nodeEntries[node.entryNumber - 1].key;
    } else if (node.nodeType == BPTreeNodeType::BPTreeInternalNode){
        return getMaxKey(getNodeAtPage(node.nodeEntries[node.entryNumber - 1].pagePointer));
    }
    assert(false); // Error
}

BPTreeKey BPTree::getMinKey(BPTreeNode node) {
    assert(node.nodeType != BPTreeNodeType::BPTreeUndefinedNode);
    assert(!node.isEmpty());
    if (node.nodeType == BPTreeNodeType::BPTreeLeafNode) {
        return node.nodeEntries[1].key;
    } else if (node.nodeType == BPTreeNodeType::BPTreeInternalNode) {
        return getMinKey(getNodeAtPage(node.nodeEntries[0].pagePointer));
    }
    assert(false); // Error
}
