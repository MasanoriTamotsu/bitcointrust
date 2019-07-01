// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x8a;
        pchMessageStart[1] = 0x4a;
        pchMessageStart[2] = 0xf4;
        pchMessageStart[3] = 0x1e;
        vAlertPubKey = ParseHex("042ca1e1f8c73380e7db0dfca5041693addc8208c8a1938bf1e19d899fdde58d2cb038f51d9eba7a43e9398a3b1082585f3dad9e8cf08aca31386a3c77462a5208");
        nDefaultPort = 19914;
        nRPCPort = 9913;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=0000016a7cd3c1f5792616373252c5558a3662e7a8ddff510a9a17d98e4833b2, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=39d8cc1293a0267f095c8de46c1a5e7b7b2eb4604b8d3ca94db65087d7f042d6, nTime=1560522306, nBits=1e0fffff, nNonce=12878807, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1560522306, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "14 June 2019";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1560522306, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1560522306;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 12878807;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000016a7cd3c1f5792616373252c5558a3662e7a8ddff510a9a17d98e4833b2"));
        assert(genesis.hashMerkleRoot == uint256("0x39d8cc1293a0267f095c8de46c1a5e7b7b2eb4604b8d3ca94db65087d7f042d6"));

        vSeeds.push_back(CDNSSeedData("walletbuilders.com", "node1.walletbuilders.com"));
        vSeeds.push_back(CDNSSeedData("5.189.139.254", "5.189.139.254"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 66);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 65);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 193);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 700000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0x9e;
        pchMessageStart[2] = 0xec;
        pchMessageStart[3] = 0x79;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("041b2661ba8a4bad6011f4295b0ff994f04029fd95c50afd94cd1144cf5aa726e616a7cc5a33c77b02c7cdbb70a40ebe257e119c54aae2f6984d55b93eb627c13c");
        nDefaultPort = 9914;
        nRPCPort = 19913;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 3796391;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000001092907f109824924c1aca9490f31982405b0376deefc84985490356e91"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x65;
        pchMessageStart[1] = 0x43;
        pchMessageStart[2] = 0xc2;
        pchMessageStart[3] = 0xa7;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1560522311;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1918140;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0x0000013e22da98ee4805c9b6ff93a58c04e8f30c389a5c9bd65f7bcc14ccec75"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
