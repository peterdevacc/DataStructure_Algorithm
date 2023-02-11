// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "core_hash.h"

uint32_t Ex::murmurHash(const std::string &key, uint32_t seed) {
    auto rawData = static_cast<const void *>(key.c_str());
    auto data = static_cast<const uint8_t *>(rawData);
    auto len = static_cast<const int>(key.length());
    const int numBlocks = len / 4;

    uint32_t hash = seed;

    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;

    auto blocks = (const uint32_t *) (data + numBlocks * 4);

    for (int i = -numBlocks; i; i++) {
        uint32_t k1 = blocks[i];

        k1 *= c1;
        k1 = (k1 << (int8_t)15) | (k1 >> (32 - (int8_t)15));
        k1 *= c2;

        hash ^= k1;
        hash = (hash << (int8_t)13) | (hash >> (32 - (int8_t)13));
        hash = hash * 5 + 0xe6546b64;
    }

    auto tail = static_cast<const uint8_t *>(data + numBlocks * 4);

    uint32_t k1 = 0;

    switch (len & 3) {
        case 3:
            k1 ^= tail[2] << 16;
        case 2:
            k1 ^= tail[1] << 8;
        case 1:
            k1 ^= tail[0];
            k1 *= c1;
            k1 = (k1 << (int8_t)15) | (k1 >> (32 - (int8_t)15));
            k1 *= c2;
            hash ^= k1;
    }

    hash ^= len;

    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;

    return hash;
}