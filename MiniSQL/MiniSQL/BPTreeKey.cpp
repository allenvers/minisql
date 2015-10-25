//
//  BPTreeKey.cpp
//  MiniSQL
//
//  Created by fan wu on 10/25/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include "BPTreeKey.hpp"

BPTreeKey::BPTreeKey() {
    keyLen = 0;
    intData = 0;
    floatData = 0.0f;
    charData[0] = '\0';
    type = BPTreeKeyType::UNDEFINED;
}

BPTreeKey::BPTreeKey(BPTreeKey &key) {
    keyLen = key.keyLen;
    intData = key.intData;
    floatData = key.floatData;
    memcpy(charData, key.charData, keyLen);
    type = key.type;
}

BPTreeKey::~BPTreeKey() {
}

int BPTreeKey::getKeyDataLength() {
    switch (type) {
        case BPTreeKeyType::CHAR:
            return keyLen;
            break;
        
        case BPTreeKeyType::FLOAT:
            return sizeof(float);
            break;
            
        case BPTreeKeyType::INT:
            return sizeof(int);
            break;
            
        case BPTreeKeyType::UNDEFINED:
            return 0;
            break;
            
        default:
            break;
    }
}

int BPTreeKey::compare(const BPTreeKey &key) {
    assert(type == key.type);
    assert(type != BPTreeKeyType::UNDEFINED);
    switch (type) {
        case BPTreeKeyType::INT: {
            if (intData > key.intData)
                return 1;
            else if (intData == key.intData)
                return 0;
            else return -1;
            break;
        }
        
        case BPTreeKeyType::FLOAT: {
            if (floatData > key.floatData)
                return 1;
            else if ( (floatData - key.floatData) < 0.000001)
                return 0;
            else return -1;
            break;
        }
            
        case BPTreeKeyType::CHAR: {
            return strncmp(charData, key.charData, 256);
            break;
        }
            
        default:
            return 0;
            break;
    }
}

void BPTreeKey::convertToRawData() {
    assert(type != BPTreeKeyType::UNDEFINED);
    
    switch (type) {
        case BPTreeKeyType::INT: {
            keyLen = sizeof(int);
            memcpy(rawData, &intData, keyLen);
            break;
        }
            
        case BPTreeKeyType::FLOAT: {
            keyLen = sizeof(float);
            memcpy(rawData, &floatData, keyLen);
            break;
        }
            
        case BPTreeKeyType::CHAR: {
            assert(keyLen >= 0);
            assert(keyLen <= 255);
            memcpy(rawData, charData, keyLen);
            break;
        }
            
        default:
            break;
    }
}

void BPTreeKey::parseFromRawData() {
    assert(type != BPTreeKeyType::UNDEFINED);
    keyLen = getKeyDataLength();
    switch (type) {
        case BPTreeKeyType::INT: {
            assert(keyLen == sizeof(int));
            memcpy(&intData, rawData, keyLen);
            break;
        }
            
        case BPTreeKeyType::FLOAT: {
            assert(keyLen == sizeof(float));
            memcpy(&floatData, rawData, keyLen);
            break;
        }
            
        case BPTreeKeyType::CHAR: {
            assert(keyLen >= 0);
            assert(keyLen <= 255);
            memcpy(charData, rawData, keyLen);
        }
            
        default:
            break;
    }
}

bool BPTreeKey::operator< (const BPTreeKey &key) {
    return compare(key) == -1;
}

bool BPTreeKey::operator==(const BPTreeKey &key) {
    return compare(key) == 0;
}

bool BPTreeKey::operator> (const BPTreeKey &key) {
    return compare(key) == 1;
}