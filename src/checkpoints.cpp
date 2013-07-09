// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 CHNCoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (		1, uint256("0x83620ee23c8cdfc2b6c7d712baf583c855be05870a8b8ba41731077cacdc5258"))
            (		2, uint256("0x1d06e68b4920ffa741b6d50e43e2a6159a11ee51206e544b436970ce52c9f75b"))
			(	22892, uint256("0x908b2a5950136e285d52093f8706a4582a48bf975a5d34221c3e1c42e378001a"))
			(	31854, uint256("0xa20a4dfc0ac4fb00a7583e1aab95b274295f2ae15a3055ef489eefe565897834"))
			(	45005, uint256("0x388693cb9d1b91a209ad6ecea2973e284e69175652bf4f2cc98a1173776157f3"))
			(	55536, uint256("0x29624edea73b2d0cbda0188d051c88553ab8c380b84f95f89d3751042de35753"))
			(	59712, uint256("0x5cd6219856e32209b3b7fd3312e255881b0e0e648693d749dc87c230ea6fef9e"))
            ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
		
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
