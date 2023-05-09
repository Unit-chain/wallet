//
// Created by yourgod on 03/03/2023.
//

#include "aes_256_GCM.h"
using CryptoPP::byte;

std::string aes_256_GCM::encode(const std::string &adata,
                                const std::string &pdata,
                                byte key[],
                                size_t key_size,
                                byte iv[],
                                size_t iv_size,
                                int TAG_SIZE
                                ) {

  std::string encoded;

  std::string cipher; // out
  try {

    GCM<AES>::Encryption e;
    e.SetKeyWithIV(key, key_size, iv, iv_size);

    // Filter wrapper for encrypting
    AuthenticatedEncryptionFilter ef(e, new StringSink(cipher), false,
                                     TAG_SIZE);

    // AuthenticatedEncryptionFilter::ChannelPut
    //  defines two channels: "" (empty) and "AAD"
    //   channel "" is encrypted and authenticated
    //   channel "AAD" is authenticated
    ef.ChannelPut("AAD", (const byte *)adata.data(), adata.size());
    ef.ChannelMessageEnd("AAD");

    // Authenticated data *must* be pushed before
    //  Confidential/Authenticated data. Otherwise
    //  we must catch the BadState exception
    ef.ChannelPut("", (const byte *)pdata.data(),
                  pdata.size()); // user_defined
    ef.ChannelMessageEnd("");

  } catch (CryptoPP::BufferedTransformation::NoChannelSupport &e) {
    // The tag must go in to the default channel:
    //  "unknown: this object doesn't support multiple channels"
    cerr << "Caught NoChannelSupport..." << endl;
    cerr << e.what() << endl;
    cerr << endl;
  } catch (CryptoPP::AuthenticatedSymmetricCipher::BadState &e) {
    // Pushing PDATA before ADATA results in:
    //  "GMC/AES: Update was called before State_IVSet"
    cerr << "Caught BadState..." << endl;
    cerr << e.what() << endl;
    cerr << endl;
  } catch (CryptoPP::InvalidArgument &e) {
    cerr << "Caught InvalidArgument..." << endl;
    cerr << e.what() << endl;
    cerr << endl;
  }

  return cipher;
}

string aes_256_GCM::decode(const string &cipher,
                           const string &adata,
                           byte *key,
                           size_t key_size,
                           byte *iv,
                           size_t iv_size,
                           int TAG_SIZE
                           ) {
  string radata, rpdata;
  try {
    GCM<AES>::Decryption d;
    d.SetKeyWithIV(&key[0], key_size, iv, iv_size);

    // Break the cipher text out into it's
    //  components: Encrypted Data and MAC Value
    string enc = cipher.substr(0, cipher.length() - TAG_SIZE);
    string mac = cipher.substr(cipher.length() - TAG_SIZE);

    // Sanity checks
    assert(cipher.size() == enc.size() + mac.size());
    //    assert(enc.size() == pdata.size());

    assert(TAG_SIZE == mac.size());

    // Not recovered - sent via clear channel
    //    radata = adata;

    // Object will not throw an exception
    //  during decryption\verification _if_
    //  verification fails.
    // AuthenticatedDecryptionFilter df( d, NULL,
    // AuthenticatedDecryptionFilter::MAC_AT_BEGIN );

    AuthenticatedDecryptionFilter df(
        d, NULL,
        AuthenticatedDecryptionFilter::MAC_AT_BEGIN |
            AuthenticatedDecryptionFilter::THROW_EXCEPTION,
        TAG_SIZE);

    // The order of the following calls are important
    df.ChannelPut("", (const byte *)mac.data(), mac.size());
    df.ChannelPut("AAD", (const byte *)adata.data(), adata.size());
    df.ChannelPut("", (const byte *)enc.data(), enc.size());

    // If the object throws, it will most likely occur
    //  during ChannelMessageEnd()
    df.ChannelMessageEnd("AAD");
    df.ChannelMessageEnd("");

    // If the object does not throw, here's the only
    //  opportunity to check the data's integrity
    bool b = false;
    b = df.GetLastResult();
    assert(b);

    // Remove data from channel
    string retrieved;
    size_t n = (size_t)-1;

    // Plain text recovered from enc.data()
    df.SetRetrievalChannel("");
    n = (size_t)df.MaxRetrievable();
    retrieved.resize(n);

    if (n > 0) {
      df.Get((byte *)retrieved.data(), n);
    }
    rpdata = retrieved;

  } catch (CryptoPP::InvalidArgument &e) {
    cerr << "Caught InvalidArgument..." << endl;
    cerr << e.what() << endl;
    cerr << endl;
  } catch (CryptoPP::AuthenticatedSymmetricCipher::BadState &e) {
    // Pushing PDATA before ADATA results in:
    //  "GMC/AES: Update was called before State_IVSet"
    cerr << "Caught BadState..." << endl;
    cerr << e.what() << endl;
    cerr << endl;
  } catch (CryptoPP::HashVerificationFilter::HashVerificationFailed &e) {
    cerr << "Caught HashVerificationFailed..." << endl;
    cerr << e.what() << endl;
    cerr << endl;
  }

  return rpdata;
}
