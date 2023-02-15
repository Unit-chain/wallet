#pragma once
#include "utils.hpp"
#include "utils.cpp"

#define HARDENED_VALUE 2147483648
#define NMODULO boost::multiprecision::uint512_t("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141")

using uint512 = boost::multiprecision::uint512_t;

/// @brief Defines BIP32 with OpenSSL cryptography
class BIP32
{
private:
    /// @brief Contains information from secp256k1 EC
    struct secp256k1_result
    {
        std::string private_key;
        std::string point_x;
        std::string point_y;
        std::string public_key;
        secp256k1_result(std::string _prv, std::string _x, std::string _y, std::string _pbc)
        {
            private_key = _prv;
            point_x = _x;
            point_y = _y;
            public_key = _pbc;
        }
    };
 //   secp256k1_result get_pub_from_seed_secp256k1(std::string);
secp256k1_result get_pub_from_seed_secp256k1(std::string seed)
{
    EC_KEY *key_pair_obj = nullptr;
    int ret_error;
    BIGNUM *priv_key = NULL;
    // set private key from 32 byte seed
    BN_hex2bn(&priv_key, (seed).c_str());
    EC_POINT *pub_key;
    EC_GROUP *secp256k1_group;
    char *pub_key_char, *priv_key_char;

    // Generate secp256k1 key pair
    key_pair_obj = EC_KEY_new_by_curve_name(NID_secp256k1);
    secp256k1_group = (EC_GROUP *)EC_KEY_get0_group(key_pair_obj);
    pub_key = EC_POINT_new(secp256k1_group);

    // Set private key
    if (!EC_KEY_set_private_key(key_pair_obj, priv_key))
    {
        return BIP32::secp256k1_result("", "", "", "");
    }

    // Calculate public key
    if (!EC_POINT_mul(secp256k1_group, pub_key, priv_key, NULL, NULL, nullptr))
    {
        return BIP32::secp256k1_result("", "", "", "");
    }
    EC_KEY_set_public_key(key_pair_obj, pub_key);

    pub_key_char = EC_POINT_point2hex(secp256k1_group, pub_key, POINT_CONVERSION_COMPRESSED, nullptr);

    BIGNUM *x = BN_new();
    BIGNUM *y = BN_new();
    if (!EC_POINT_get_affine_coordinates(secp256k1_group, pub_key, x, y, NULL))
    {
        BN_free(x);
        BN_free(y);
        EC_GROUP_free(secp256k1_group);
        return BIP32::secp256k1_result("", "", "", "");
    }
    EC_GROUP_free(secp256k1_group);

    BIP32::secp256k1_result sig(seed, BN_bn2hex(x), BN_bn2hex(y), pub_key_char);

    BN_free(x);
    BN_free(y);
    return sig;
}
public:
    /// @brief Result of generating BIP32 node
    struct BIP32NodeResult
    {
        std::string depth;         // hex
        std::string keypair_index; // hex
        std::string ecdsa_pub;     // hex
        std::string ecdsa_prv;     // hex
        std::string hex_prv_key;
        std::string hex_pub_key;
        std::string xprv_base58;
        std::string xpub_base58;

        /// @brief Constructor of the BIP32 result struct. Contains everything to generate child keys.
        /// @param d depth of the child node ("00", "01", "02"...)
        /// @param pair_i index of the keys pair. can be hardened or not.
        /// hardened values use macro HARDENED. ("00000001", "00000002", ... , "80000000", "80000001"...)
        ///
        /// @param h_prv hex representation of extended private key
        /// @param h_pub hex representation of extended public key
        /// @param b_prv base58 representation of extended private key
        /// @param b_pub base58 representation of extended public key
        /// @param ecdsa_pk hex representaion of public key
        /// @param ecdsa_pv hex representaion of private key
        BIP32NodeResult(std::string d, std::string pair_i, std::string h_prv, std::string h_pub, std::string b_prv, std::string b_pub, std::string ecdsa_pk, std::string ecdsa_pv)
        {
            depth = d;
            keypair_index = pair_i;
            hex_prv_key = h_prv;
            hex_pub_key = h_pub;
            xprv_base58 = b_prv;
            xpub_base58 = b_pub;
            ecdsa_pub = ecdsa_pk;
            ecdsa_prv = ecdsa_pv;
        }

        /// @brief Empty constructor. Use it when error has happened.
        BIP32NodeResult()
        {
            depth = "";
            keypair_index = "";
            hex_prv_key = "";
            hex_pub_key = "";
            xprv_base58 = "";
            xpub_base58 = "";
            ecdsa_pub = "";
            ecdsa_prv = "";
        }
    };

    /// @brief generating master-node for BIP32.
    /// @param seed from BIP38
    /// @return BIP32 master-node
    BIP32NodeResult gen_master(std::string seed);

    /// @brief generate child from parent's private key
    /// @param res parent's node
    /// @param i desired keypair index
    /// @param d desired depth of the node
    /// @return new BIP32 child node
    BIP32NodeResult gen_child_from_xprv(BIP32NodeResult res, uint32_t i, std::string d);
};


