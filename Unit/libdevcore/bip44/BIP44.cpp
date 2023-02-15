#include "BIP44.hpp"

BIP44Result BIP44::generateWallet(int len, uint16_t account, unsigned char change)
{
    if (len != PHRASE_12 && len != PHRASE_24)
        return BIP44Result("BAD PHRASE");

    if (change != INTERNAL_CHANGE && change != EXTERNAL_CHANGE)
        return BIP44Result("BAD CHANGE");

    BIP39 mnemonic = BIP39();
    BIP39Result mnemonic_code;

    if (len == PHRASE_12)
        mnemonic_code = mnemonic.generateMnemonic_12("");
    else
        mnemonic_code = mnemonic.generateMnemonic("");

    BIP32 bip32 = BIP32();

    BIP32::BIP32NodeResult m_node = bip32.gen_master(mnemonic_code.seed);
    if (m_node.xprv_base58 == "")
        return BIP44Result("BAD MASTER");

    BIP32::BIP32NodeResult purpose_node = bip32.gen_child_from_xprv(m_node, HARDENED_VALUE + 44, "01");
    if (purpose_node.xprv_base58 == "")
        return BIP44Result("BAD PUPROSE");

    BIP32::BIP32NodeResult coin_node = bip32.gen_child_from_xprv(purpose_node, HARDENED_VALUE + UNIT_COINTYPE, "02");
    if (coin_node.xprv_base58 == "")
        return BIP44Result("BAD COINTYPE");

    BIP32::BIP32NodeResult account_node = bip32.gen_child_from_xprv(coin_node, HARDENED_VALUE + account, "03");
    if (account_node.xprv_base58 == "")
        return BIP44Result("BAD ACCOUNT");

    BIP32::BIP32NodeResult change_node = bip32.gen_child_from_xprv(account_node, change, "04");
    if (change_node.xprv_base58 == "")
        return BIP44Result("BAD CHANGE NODE");

    BIP32::BIP32NodeResult address_node = bip32.gen_child_from_xprv(change_node, 0, "05");
    if (address_node.xprv_base58 == "")
        return BIP44Result("BAD ADDRESS");

    Addresses adr;
    std::string wallet_address = adr.pub2addr(address_node.ecdsa_pub);

    return BIP44Result("m/44'/992'/" + std::to_string(account) + "'/" + std::to_string(change) + "/0",
                       address_node.xprv_base58,
                       address_node.xpub_base58,
                       address_node.ecdsa_prv,
                       address_node.ecdsa_pub,
                       wallet_address,
                       mnemonic_code);
}


BIP44Result BIP44::generateWallet(int len, uint16_t account, unsigned char change, std::string password)
{
    if (len != PHRASE_12 && len != PHRASE_24)
        return BIP44Result("BAD PHRASE");

    if (change != INTERNAL_CHANGE && change != EXTERNAL_CHANGE)
        return BIP44Result("BAD CHANGE");

    BIP39 mnemonic = BIP39();
    BIP39Result mnemonic_code;

    if (len == PHRASE_12)
        mnemonic_code = mnemonic.generateMnemonic_12(password);
    else
        mnemonic_code = mnemonic.generateMnemonic(password);

    BIP32 bip32 = BIP32();

    BIP32::BIP32NodeResult m_node = bip32.gen_master(mnemonic_code.seed);
    if (m_node.xprv_base58 == "")
        return BIP44Result("BAD MASTER");

    BIP32::BIP32NodeResult purpose_node = bip32.gen_child_from_xprv(m_node, HARDENED_VALUE + 44, "01");
    if (purpose_node.xprv_base58 == "")
        return BIP44Result("BAD PUPROSE");

    BIP32::BIP32NodeResult coin_node = bip32.gen_child_from_xprv(purpose_node, HARDENED_VALUE + UNIT_COINTYPE, "02");
    if (coin_node.xprv_base58 == "")
        return BIP44Result("BAD COINTYPE");

    BIP32::BIP32NodeResult account_node = bip32.gen_child_from_xprv(coin_node, HARDENED_VALUE + account, "03");
    if (account_node.xprv_base58 == "")
        return BIP44Result("BAD ACCOUNT");

    BIP32::BIP32NodeResult change_node = bip32.gen_child_from_xprv(account_node, change, "04");
    if (change_node.xprv_base58 == "")
        return BIP44Result("BAD CHANGE NODE");

    BIP32::BIP32NodeResult address_node = bip32.gen_child_from_xprv(change_node, 0, "05");
    if (address_node.xprv_base58 == "")
        return BIP44Result("BAD ADDRESS");

    Addresses adr;
    std::string wallet_address = adr.pub2addr(address_node.ecdsa_pub);

    return BIP44Result("m/44'/992'/" + std::to_string(account) + "'/" + std::to_string(change) + "/0",
                       address_node.xprv_base58,
                       address_node.xpub_base58,
                       address_node.ecdsa_prv,
                       address_node.ecdsa_pub,
                       wallet_address,
                       mnemonic_code);
}


BIP44Result BIP44::generateAddress(BIP39Result mnemonic, uint16_t account, unsigned char change, uint16_t address_index) 
{
    BIP32 bip32 = BIP32();
    BIP32::BIP32NodeResult m_node = bip32.gen_master(mnemonic.seed);
    if (m_node.xprv_base58 == "")
        return BIP44Result("BAD MASTER");

    BIP32::BIP32NodeResult purpose_node = bip32.gen_child_from_xprv(m_node, HARDENED_VALUE + 44, "01");
    if (purpose_node.xprv_base58 == "")
        return BIP44Result("BAD PUPROSE");

    BIP32::BIP32NodeResult coin_node = bip32.gen_child_from_xprv(purpose_node, HARDENED_VALUE + UNIT_COINTYPE, "02");
    if (coin_node.xprv_base58 == "")
        return BIP44Result("BAD COINTYPE");

    BIP32::BIP32NodeResult account_node = bip32.gen_child_from_xprv(coin_node, HARDENED_VALUE + account, "03");
    if (account_node.xprv_base58 == "")
        return BIP44Result("BAD ACCOUNT");

    BIP32::BIP32NodeResult change_node = bip32.gen_child_from_xprv(account_node, change, "04");
    if (change_node.xprv_base58 == "")
        return BIP44Result("BAD CHANGE NODE");

    BIP32::BIP32NodeResult address_node = bip32.gen_child_from_xprv(change_node, address_index, "05");
    if (address_node.xprv_base58 == "")
        return BIP44Result("BAD ADDRESS");

    Addresses adr;
    std::string wallet_address = adr.pub2addr(address_node.ecdsa_pub);

    return BIP44Result("m/44'/992'/" + std::to_string(account) + "'/" + std::to_string(change) + "/"+std::to_string(address_index),
                       address_node.xprv_base58,
                       address_node.xpub_base58,
                       address_node.ecdsa_prv,
                       address_node.ecdsa_pub,
                       wallet_address,
                       mnemonic);
}
