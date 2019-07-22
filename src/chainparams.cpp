// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Copyright (c) 2019 The Ultradash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
boost::assign::map_list_of
(0, uint256("0x0000026ad6b1794c268f5353486d646ff8a6b1af5beaec5f2741a9614ff380a1"))
(1, uint256("0x00000a24fc65d32988f0a3c62d32c11a6ae64f96c82a133f161a76ae0ae53ad3"))
(871, uint256("0xa0760668a5075faa3bab8121ce02f87c1ad455b5383a54af1fcd0bf569e4793b"))
(1422, uint256("0xa9bfe2ea099753e2bb832b6cfbff0a705431f5f7fd4f8b7a17c9c95594d11aa9"))
(2703, uint256("0x531f7df5a312a1c3f774b99acdc5969b01941c9ee9964bf1f3c767710cfea850"))
(3451, uint256("0x2302e2c44525fe543302aed47bd7ee21b0246c18fa4ce94dc4373a84b46044b6"))
(4534, uint256("0x956677c372abcb89885ea7da4f492e9ebaf614eca39819b8df5b89776efedada"))
(5201, uint256("0x84dd9ac8b46f1c8034077114aee8b2ee5a7e377c6b241933bac91563ac608802"))
(6189, uint256("0x1de147e83ef68b23271491f1a1180dd23dbd1f38c8dddb9dbfaf0e8fb7dbd01c"))

;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1563785952, // * UNIX timestamp of last checkpoint block
    13851,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x001"))
	;
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1560843157,
    2501682,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1563429600,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x81;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xad;
        pchMessageStart[3] = 0xe3;
        vAlertPubKey = ParseHex("0000091d3ba6ba6e7423fa5cbd6b65e0a9a5348f88d332b44a5cb1a8b7ed2c1eaa335fc8dc4f012cb8241cc0bdafd6ca70c5f5448916e4e6f511bcd746ed18da31");
        nDefaultPort = 9237;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Ultradash starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 8100; // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Ultradash: 1 day
        nTargetSpacing = 1 * 60;  // Ultradash: 1 minute
        nMaturity = 61;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 1000000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nZerocoinStartHeight = 210;
        nZerocoinStartTime = 1563429600; 
        nBlockLastGoodCheckpoint = 210; //Last valid accumulator checkpoint
        nBlockZerocoinV2 = 210; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        nBlockDoubleAccumulated = 0;

        // Public coin spend enforcement
        nPublicZCSpends = 300;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "UltraDash Masternode Coin";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c10e83b2703cc1265f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92422a4b256cd42774babea0a073b2ed9c1") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 4;
		genesis.nAccumulatorCheckpoint = 0;
        genesis.nTime = 1563429600;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 3272703;

        hashGenesisBlock = genesis.GetHash();

		assert(hashGenesisBlock == uint256("0x0000026ad6b1794c268f5353486d646ff8a6b1af5beaec5f2741a9614ff380a1"));
		assert(genesis.hashMerkleRoot == uint256("0x2728497da8f9df0093110327b1effc8a3f93dda30cbecf0d912c753a434614aa"));

        vSeeds.push_back(CDNSSeedData("1", "dnsseederudsh.udashcoin.info"));    
        vSeeds.push_back(CDNSSeedData("2", "explorer.udashcoin.info"));    
		vSeeds.push_back(CDNSSeedData("3", "seed1.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("4", "seed2.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("5", "seed3.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("6", "seed4.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("7", "seed5.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("8", "seed6.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("9", "seed7.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("10", "seed8.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("11", "seed9.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("12", "seed10.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("13", "seed11.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("14", "seed12.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("15", "seed13.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("16", "seed14.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("17", "seed15.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("18", "seed16.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("19", "seed17.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("20", "seed18.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("21", "seed19.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("22", "seed20.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("23", "seed21.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("24", "seed22.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("25", "seed23.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("26", "seed24.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("27", "seed25.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("28", "seed26.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("29", "seed27.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("30", "seed28.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("31", "seed29.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("32", "seed30.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("33", "seed31.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("34", "seed32.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("35", "seed33.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("36", "seed34.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("37", "seed35.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("38", "seed36.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("39", "seed37.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("40", "seed38.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("41", "seed39.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("42", "seed40.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("43", "seed41.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("44", "seed42.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("45", "seed43.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("46", "seed44.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("47", "seed45.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("48", "seed46.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("49", "seed47.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("50", "seed48.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("51", "seed49.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("52", "seed50.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("53", "seed51.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("54", "seed52.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("55", "seed53.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("56", "seed54.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("57", "seed55.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("58", "seed56.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("59", "seed57.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("60", "seed58.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("61", "seed59.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("62", "seed60.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("63", "seed61.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("64", "seed62.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("65", "seed63.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("66", "seed64.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("67", "seed65.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("68", "seed66.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("69", "seed67.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("70", "seed68.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("71", "seed69.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("72", "seed70.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("73", "seed71.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("74", "seed72.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("75", "seed73.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("76", "seed74.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("77", "seed75.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("78", "seed76.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("79", "seed77.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("80", "seed78.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("81", "seed79.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("82", "seed80.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("83", "seed81.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("84", "seed82.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("85", "seed83.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("86", "seed84.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("87", "seed85.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("88", "seed86.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("89", "seed87.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("90", "seed88.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("91", "seed89.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("92", "seed90.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("93", "seed91.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("94", "seed92.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("95", "seed93.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("96", "seed94.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("97", "seed95.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("98", "seed96.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("99", "seed97.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("100", "seed98.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("101", "seed99.udashcoin.info"));
		vSeeds.push_back(CDNSSeedData("102", "seed100.udashcoin.info"));    

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 68);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nBudgetCycleBlocks = 43200; //!< Amount of blocks in a months period of time (using 1 minutes per) = (60*24*30)
        strSporkKey = "04f8962962391292925b9a11af53bf56c8cdce5fb9907ae998ad680369f8a5dd9800517d37c3d1785e7a7046bd4476d4ae71adab69de108146a222676163c03ffe";
        strObfuscationPoolDummyAddress = "UatTNKnkCGo6tJYNRiTMFRd7WTu6VfBf7f";

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMaxZerocoinPublicSpendsPerTransaction = 637; // Assume about 220 bytes each input
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zudsh to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
        nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("000010e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9");
        nDefaultPort = 51474;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Ultradash: 1 day
        nTargetSpacing = 1 * 60;  // Ultradash: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nMaxMoneyOut = 43199500 * COIN;

        // Public coin spend enforcement
        nPublicZCSpends = 1106100;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1563429600;
        genesis.nNonce = 2402015;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "ultradash-testnet.seed.fuzzbawls.pw"));
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "ultradash-testnet.seed2.fuzzbawls.pw"));
        vSeeds.push_back(CDNSSeedData("warrows.dev", "testnet.dnsseed.ultradash.warrows.dev"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet ultradash addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet ultradash script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet ultradash BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet ultradash BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet ultradash BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        nBudgetCycleBlocks = 144; //!< Ten cycles per day on testnet
        strSporkKey = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nProposalEstablishmentTime = 60 * 5; // Proposals must be at least 5 mns old to make it into a test budget
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Ultradash: 1 day
        nTargetSpacing = 1 * 60;        // Ultradash: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nLastPOWBlock = 250;
        nMaturity = 100;
        nMasternodeCountDrift = 4;
        //nModifierUpdateBlock = 0; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 300;
        nBlockZerocoinV2 = 300;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999; //Last valid accumulator checkpoint

        // Public coin spend enforcement
        nPublicZCSpends = 350;

        //! Modify the regtest genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1563429600;
        genesis.nNonce = 2402015;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
        //assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
