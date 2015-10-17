//
//  BufferManager.cpp
//  MiniSQL
//
//  Created by fan wu on 10/16/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include "BufferManager.hpp"

bool BufferManager::openTableFile(string tableName) {
    string filePath = tableFilePath(tableName);
    if (tableFileHandles.find(tableName) == tableFileHandles.end()) {
        int fileHandle = open(filePath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fileHandle < 0) return false;
        tableFileHandles[tableName] = fileHandle;
        makeTwoPages(fileHandle);
        return true;
    }
    cout << "File " << filePath << " " << "already opened" << endl;
    return false;
}

bool BufferManager::openIndexFile(string tableName, string attributeName) {
    auto indexPair = make_pair(tableName, attributeName);
    string filePath = indexFilePath(tableName, attributeName);
    if (indexFileHandles.find(indexPair) == indexFileHandles.end()) {
        int fileHandle = open(filePath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fileHandle < 0) return false;
        indexFileHandles[indexPair] = fileHandle;
        makeTwoPages(fileHandle);
        return true;
    }
    cout << "File " << filePath << " " << "already opened" << endl;
    return false;
}

bool BufferManager::openTableCatalogFile(string tableName) {
    string filePath = tableCatalogFilePath(tableName);
    if (tableCatalogFileHandles.find(tableName) == tableCatalogFileHandles.end()) {
        int fileHandle = open(filePath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fileHandle < 0) return false;
        tableCatalogFileHandles[tableName] = fileHandle;
        makeTwoPages(fileHandle);
        return true;
    }
    cout << "File " << filePath << " " << "already opened" << endl;
    return false;
}

bool BufferManager::openIndexCatalogFile(string tableName, string attributeName) {
    auto indexPair = make_pair(tableName, attributeName);
    string filePath = indexFilePath(tableName, attributeName);
    if (indexCalalogFileHandles.find(indexPair) == indexCalalogFileHandles.end()) {
        int fileHandle = open(filePath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fileHandle < 0) return false;
        indexCalalogFileHandles[indexPair] = fileHandle;
        makeTwoPages(fileHandle);
        return true;
    }
    cout << "File " << filePath << " " << "already opened" << endl;
    return false;
}

string BufferManager::tableFilePath(string tableName) {
    return recordFilesDirectory + "/" + tableName + ".db";
}

string BufferManager::indexFilePath(string tableName, string attributeName) {
    return indexFilesDirectory + "/" + tableName + "_" + attributeName + ".db";
}

string BufferManager::tableCatalogFilePath(string tableName) {
    return recordCatalogFilesDirectory + "/" + tableName + ".db";
}

string BufferManager::indexCatalogFilePath(string tableName, string attributeName) {
    return indexCatalogFilesDirectory + "/" + tableName + "_" + attributeName + ".db";
}

void BufferManager::makeTwoPages(int fileHandle) {
    if (lseek(fileHandle, 0, SEEK_END) / PAGESIZE < 2) {
        char *pageBuffer = new char[PAGESIZE * 2];
        memset(pageBuffer, 0 , PAGESIZE * 2);
        write(fileHandle, pageBuffer, PAGESIZE * 2);
    }
}

bool BufferManager::closeTableFile(string tableName) {
    if (tableFileHandles.find(tableName) == tableFileHandles.end())
        return false;
    int handle = tableFileHandles[tableName];
    if (close(handle) != -1) return true;
    return false;
}

bool BufferManager::closeIndexFile(string tableName, string attributeName) {
    auto indexPair = make_pair(tableName, attributeName);
    if (indexFileHandles.find(indexPair) == indexFileHandles.end())
        return false;
    int handle = indexFileHandles[indexPair];
    if (close(handle) != -1) return true;
    return false;
}

bool BufferManager::closeTableCatalogFile(string tableName) {
    if (tableCatalogFileHandles.find(tableName) == tableCatalogFileHandles.end()) {
        return false;
    }
    int handle = tableCatalogFileHandles[tableName];
    if (close(handle) != -1) return true;
    return false;
}

bool BufferManager::closeIndexCatalogFile(string tableName, string attributeName) {
    auto indexPair = make_pair(tableName, attributeName);
    if (indexCalalogFileHandles.find(indexPair) == indexCalalogFileHandles.end()) {
        return false;
    }
    int handle = indexCalalogFileHandles[indexPair];
    if (close(handle != -1)) return true;
    return false;
}

