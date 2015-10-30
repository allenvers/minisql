//
//  BPTree.cpp
//  MiniSQL
//
//  Created by fan wu on 10/29/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include "BPTree.hpp"

BPTreeNode BPTree::getNodeAtPage(PageIndexType pageIndex) {
    BPTreeNode node;
    node.nodePage.tableName  = tableName;
    node.nodePage.attributeName = attributeName;
    node.nodePage.pageType = PageType::IndexPage;
    node.nodePage.pageIndex = pageIndex;
    node.readNode();
    return node;
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