#pragma once

#include "Defines.h"
#include <cryptoTools/Common/Defines.h>
#include <cryptoTools/Common/BitVector.h>
#include <cryptoTools/Common/Matrix.h>
namespace volePSI
{

    class SimpleIndex
    {
    public:


        struct Item
        {
            Item() :mVal(-1) {}

            Item& operator=(const Item&) = default;

            bool isEmpty() const { return mVal == u64(-1); }

            // The index is the index of the input that currently
            // occupies this bin position. The index is encode in the
            // first 7 bytes.
            u64 idx() const { return mVal  & (u64(-1) >> 8); }

            // The index of the hash function that this item is 
            // currently using. This in is encoded in the 8th byte.
            u64 hashIdx() const { return ((u8*)&mVal)[7] & 127; }

            // Return true if this item was set with a collition.
            bool isCollision() const { return  (((u8*)&mVal)[7] >> 7) > 0; }

            // The this item to contain the index idx under the given hash index.
            // The collision value is also encoded.
            void set(u64 idx, u8 hashIdx, bool collision)
            {
                mVal = idx;
                ((u8*)&mVal)[7] = hashIdx | ((collision & 1) << 7);
            }
#ifdef THREAD_SAFE_SIMPLE_INDEX
            Item(const Item& b) : mVal(b.mVal.load(std::memory_order_relaxed)) {}
            Item(Item&& b) : mVal(b.mVal.load(std::memory_order_relaxed)) {}
            std::atomic<u64> mVal;
#else
            Item(const Item& b) : mVal(b.mVal) {}
            Item(Item&& b) : mVal(b.mVal) {}
            u64 mVal;
#endif
        };

        u64 mMaxBinSize, mNumHashFunctions;

        // The current assignment of items to bins. Only
        // the index of the input item is stored in the bin,
        // not the actual item itself.
        Matrix<Item> mBins;
        u64 mNumBins;

        // numBalls x mNumHashFunctions matrix, (i,j) contains the i'th items
        // hash value under hash index j.
        Matrix<u64> mItemToBinMap;

        // The some of each bin.
        std::vector<u64> mBinSizes;

        block mHashSeed;
        void print() ;
        static  u64 get_bin_size(u64 numBins, u64 numBalls, u64 statSecParam, bool approx = true);
        

        void init(u64 numBins, u64 numBalls, u64 statSecParam = 40, u64 numHashFunction = 3);
        void insertItems(span<block> items, block hashingSeed);
    };

}
