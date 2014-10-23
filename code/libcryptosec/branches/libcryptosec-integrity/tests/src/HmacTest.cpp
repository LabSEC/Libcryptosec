#include <libcryptosec/Hmac.h>
#include "gtest.h"

class HmacTest : public ::testing::Test {

protected:
	virtual void SetUp() {
		key30bytes = ByteArray("XthisIsMyFavoriteKeyOf30bytesX");
		key63bytes = ByteArray("MyKeyMyKeyMyKeyMyKeyMyKeyMyKey"
							   "MyKeyMyKeyMyKeyMyKeyMyKeyMyKey123");
		key64bytes = ByteArray("Key123Key456Key789Key123Key456Ke"
							   "y789Key123Key456Key789Key123Key4");
		key128bytes = ByteArray("AbCdEfGhAbCdEfGhAbCdEfGhAbCdEfGh"
								"AbCdEfGhAbCdEfGhAbCdEfGhAbCdEfGh"
								"AbCdEfGhAbCdEfGhAbCdEfGhAbCdEfGh"
								"AbCdEfGhAbCdEfGhAbCdEfGhAbCdEfGh");
		key129bytes = ByteArray("AbCdEfGhAbCdEfGhAbCdEfGhAbCdEfGh"
								"AbCdEfGhAbCdEfGhAbCdEfGhAbCdEfGh"
								"AbCdEfGhAbCdEfGhAbCdEfGhAbCdEfGh"
								"AbCdEfGhAbCdEfGhAbCdEfGhAbCdEfGh1");
		key150bytes = ByteArray("keyKEYkeyKEYkeyKEYkeyKEYkeyKEYkey"
								"KEYkeyKEYkeyKEYkeyKEYkeyKEYkeyKEY"
								"keyKEYkeyKEYkeyKEYkeyKEYkeyKEYkey"
								"KEYkeyKEYkeyKEYkeyKEYkeyKEYkeyKEY"
								"keyKEYkeyKEYkeyKEY");
		ByteArray pText("plainText");
		plainTexts = std::vector<ByteArray>(30, pText);
	}

	Hmac hmac;
	ByteArray emptyKey;
	ByteArray key30bytes;
	ByteArray key63bytes;
	ByteArray key64bytes;
	ByteArray key128bytes;
	ByteArray key129bytes;
	ByteArray key150bytes;
	std::vector<ByteArray> plainTexts;

};

/**
 * Geração de Hmac
 */
TEST_F(HmacTest, HmacSha256_key30bytes) {
	hmac.init(key30bytes, MessageDigest::SHA256);
	EXPECT_STRCASEEQ("47460fd58266a86d9fe2e9c902ca0c97c58306d3de53fc0596c2df7f251e4d2d",
					hmac.doFinal(plainTexts[0]).toHex().c_str());
}

TEST_F(HmacTest, HmacSha256_key64bytes) {
	hmac.init(key64bytes, MessageDigest::SHA256);
	EXPECT_STRCASEEQ("ff6d20b3d45b6c01fe8d07f155be6e94401ebb348fbaf51af8f3d4505d805306",
					hmac.doFinal(plainTexts[0]).toHex().c_str());
}

TEST_F(HmacTest, HmacSha256_key150bytes) {
	hmac.init(key150bytes, MessageDigest::SHA256);
	EXPECT_STRCASEEQ("9d448d43be3fde104ca6041fa33a3fd5874cabdb6d37fff8e6d6886529f222cd",
					hmac.doFinal(plainTexts[0]).toHex().c_str());
}

TEST_F(HmacTest, HmacSha512_key30bytes) {
	hmac.init(key63bytes, MessageDigest::SHA512);
	EXPECT_STRCASEEQ("60cf29ec2d024968219034b3843bb3f01bca73a1b03e84ab92ab4d12da9b71aa"
					 "fe156c48a1439d4fa25bd230d4b0b05591a7aedfe99b5f2a96ecacce6996ee6a",
					hmac.doFinal(plainTexts[0]).toHex().c_str());
}

TEST_F(HmacTest, HmacSha512_key64bytes) {
	hmac.init(key128bytes, MessageDigest::SHA512);
	EXPECT_STRCASEEQ("eeea8e1889a1ae943f8995de5eaffcefdb35a45d6fb27f8e1c14bc7d5c88cd5e"
					 "35b9c96014d521afddbb479b0a1f9581a64e8f42dd5614deeca147aba6451bf8",
					hmac.doFinal(plainTexts[0]).toHex().c_str());
}

TEST_F(HmacTest, HmacSha512_key150bytes) {
	hmac.init(key129bytes, MessageDigest::SHA512);
	EXPECT_STRCASEEQ("c50e6385aa695a38309e5a6910137e52d53f82b96288de04455cf5ac4fd68567"
					 "9ca604f0405e8f4d0c24327bca3dbb9dd2ba6d14a5ca2a7234892f359c0830bc",
					hmac.doFinal(plainTexts[0]).toHex().c_str());
}

TEST_F(HmacTest, HmacSha512Stress_key150bytes) {
	for(int i = 0; i < 100000; i++) {
		hmac.init(key129bytes, MessageDigest::SHA512);
		ASSERT_STRCASEEQ("c50e6385aa695a38309e5a6910137e52d53f82b96288de04455cf5ac4fd68567"
						 "9ca604f0405e8f4d0c24327bca3dbb9dd2ba6d14a5ca2a7234892f359c0830bc",
						hmac.doFinal(plainTexts[0]).toHex().c_str());
	}
}

TEST_F(HmacTest, HmacSha256FromVector_key63bytes) {
	hmac.init(key63bytes, MessageDigest::SHA256);
	hmac.update(plainTexts);
	EXPECT_STRCASEEQ("d98759ff86c0b1b5aa39f6454acbc3a8f3c2fddd97856890d5150aac565eb44b",
					hmac.doFinal().toHex().c_str());
}

TEST_F(HmacTest, HmacShaMd5_emptyKey) {
	hmac.init(emptyKey, MessageDigest::MD5);
	EXPECT_STRCASEEQ("0d371a986922b57b2247ec55f4b9bea4",
					hmac.doFinal(plainTexts[0]).toHex().c_str());
}

TEST_F(HmacTest, HmacSha256FromEmptyText_key150bytes) {
	hmac.init(key150bytes, MessageDigest::SHA256);
	EXPECT_STRCASEEQ("0dc9c8bb5048d5219ad0f621387b1bb4a4c06e8c0fe22b24bc1dcce2a1b61677",
					hmac.doFinal("").toHex().c_str());
}

TEST_F(HmacTest, HmacNoInitializationAndDoFinal) {
	EXPECT_THROW(hmac.doFinal(), InvalidStateException);
}

TEST_F(HmacTest, HmacNoInitializationAndUpdate) {
	EXPECT_THROW(hmac.update(""), InvalidStateException);
}

TEST_F(HmacTest, HmacInitializationTwice) {
	hmac.init(key30bytes, MessageDigest::SHA256);
	hmac.init(key64bytes, MessageDigest::SHA256);
	EXPECT_STRCASEEQ("ff6d20b3d45b6c01fe8d07f155be6e94401ebb348fbaf51af8f3d4505d805306",
			hmac.doFinal(plainTexts[0]).toHex().c_str());
}

TEST_F(HmacTest, HmacNoUpdateAndDoFinal) {
	hmac.init(key64bytes, MessageDigest::SHA256);
	EXPECT_THROW(hmac.doFinal(), InvalidStateException);
}

TEST_F(HmacTest, HmacDoFinalTwice) {
	hmac.init(key30bytes, MessageDigest::SHA256);
	hmac.doFinal("");
	EXPECT_THROW(hmac.doFinal(), InvalidStateException);
}
