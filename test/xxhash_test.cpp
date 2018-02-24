#include <cstdint>
#include <cstring>
#include <random>


#include <gtest/gtest.h>

#include "xxhash.h"

#define	XXHASH_CX_XXH32_SEED_MIN	(0UL)
#define	XXHASH_CX_XXH64_SEED_MIN	(0ULL)
#define	XXHASH_CX_XXH32_SEED_MAX	(UINT32_MAX)
#define	XXHASH_CX_XXH64_SEED_MAX	(UINT64_MAX)
#define	XXHASH_CX_XXH32_SEED_TEST	(20180211UL)
#define	XXHASH_CX_XXH64_SEED_TEST	(201802111229ULL)
#define	XXHASH_CX_XXH32_SEED	XXHASH_CX_XXH32_SEED_TEST
#define	XXHASH_CX_XXH64_SEED	XXHASH_CX_XXH32_SEED_TEST

#include "xxhash_cx.h"

#define	STR_XXH32_(s)	s ## _xxh32
#define	STR_XXH64_(s)	s ## _xxh64
#define	STR_XXH32(s)	STR_XXH32_(s)
#define	STR_XXH64(s)	STR_XXH64_(s)

#define	STR_ABC	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"

using xxhash::operator""_xxh32;
using xxhash::operator""_xxh64;

template <class T>
void gen_random_data(std::vector<T>& buf, std::size_t size)
{
	std::random_device rd;
	std::mt19937 mt(rd());

	buf.reserve(size);
	for (int i = 0; i < size; ++i) {
		buf.push_back(mt());
	}
}



TEST(xxh32_cx_test, xxh32)
{
	std::vector<std::uint32_t>	buffer;

	gen_random_data(buffer, 256);
	std::uint32_t c_h = XXH32(buffer.data(), buffer.size() * sizeof(std::uint32_t), XXHASH_CX_XXH32_SEED);
	std::uint32_t cx_h = xxhash::xxh32((char*)buffer.data(), buffer.size() * sizeof(std::uint32_t), XXHASH_CX_XXH32_SEED);
	EXPECT_EQ(c_h, cx_h);

	gen_random_data(buffer, 3);
	c_h = XXH32(buffer.data(), buffer.size() * sizeof(std::uint32_t), XXHASH_CX_XXH32_SEED);
	cx_h = xxhash::xxh32((char*)buffer.data(), buffer.size() * sizeof(std::uint32_t), XXHASH_CX_XXH32_SEED);

	EXPECT_EQ(c_h, cx_h);
}

TEST(xxh64_cx_test, xxh64)
{
	std::vector<std::uint32_t>	buffer;

	gen_random_data(buffer, 256);
	std::uint64_t c_h = XXH64(buffer.data(), buffer.size() * sizeof(std::uint32_t), XXHASH_CX_XXH64_SEED);
	std::uint64_t cx_h = xxhash::xxh64((char*)buffer.data(), buffer.size() * sizeof(std::uint32_t), XXHASH_CX_XXH64_SEED);
	EXPECT_EQ(c_h, cx_h);

	gen_random_data(buffer, 3);
	c_h = XXH64(buffer.data(), buffer.size() * sizeof(std::uint32_t), XXHASH_CX_XXH64_SEED);
	cx_h = xxhash::xxh64((char*)buffer.data(), buffer.size() * sizeof(std::uint32_t), XXHASH_CX_XXH64_SEED);
	EXPECT_EQ(c_h, cx_h);
}

TEST(xxh32_cx_test, xxh32_cx_seed)
{
	std::uint32_t c_h = XXH32(STR_ABC, std::strlen(STR_ABC), XXHASH_CX_XXH32_SEED_MIN);
	constexpr xxhash::hash<32>::hash_type cx_h = xxhash::xxh32(STR_ABC, sizeof(STR_ABC)-1, XXHASH_CX_XXH32_SEED_MIN);
	EXPECT_EQ(c_h, cx_h);
	std::uint32_t c_h2 = XXH32(STR_ABC, std::strlen(STR_ABC), XXHASH_CX_XXH32_SEED_MAX);
	constexpr xxhash::hash<32>::hash_type cx_h2 = xxhash::xxh32(STR_ABC, sizeof(STR_ABC)-1, XXHASH_CX_XXH32_SEED_MAX);
	EXPECT_EQ(c_h2, cx_h2);
	std::uint32_t c_h3 = XXH32(STR_ABC, std::strlen(STR_ABC), XXHASH_CX_XXH32_SEED_TEST);
	constexpr xxhash::hash<32>::hash_type cx_h3 = xxhash::xxh32(STR_ABC, sizeof(STR_ABC)-1, XXHASH_CX_XXH32_SEED_TEST);
	EXPECT_EQ(c_h3, cx_h3);
}

TEST(xxh64_cx_test, xxh64_cx_seed)
{
	std::uint64_t c_h = XXH64(STR_ABC, std::strlen(STR_ABC), XXHASH_CX_XXH64_SEED_MIN);
	constexpr xxhash::hash<64>::hash_type cx_h = xxhash::xxh64(STR_ABC, sizeof(STR_ABC)-1, XXHASH_CX_XXH64_SEED_MIN);
	EXPECT_EQ(c_h, cx_h);
	std::uint64_t c_h2 = XXH64(STR_ABC, std::strlen(STR_ABC), XXHASH_CX_XXH64_SEED_MAX);
	constexpr xxhash::hash<64>::hash_type cx_h2 = xxhash::xxh64(STR_ABC, sizeof(STR_ABC)-1, XXHASH_CX_XXH64_SEED_MAX);
	EXPECT_EQ(c_h2, cx_h2);
	std::uint64_t c_h3 = XXH64(STR_ABC, std::strlen(STR_ABC), XXHASH_CX_XXH64_SEED_TEST);
	constexpr xxhash::hash<64>::hash_type cx_h3 = xxhash::xxh64(STR_ABC, sizeof(STR_ABC)-1, XXHASH_CX_XXH64_SEED_TEST);
	EXPECT_EQ(c_h3, cx_h3);
}



TEST(xxh32_cx_test, user_literal_xxh32_cx_raw)
{
	std::uint32_t c_h = XXH32("ABC", std::strlen("ABC"), XXHASH_CX_XXH32_SEED);
	constexpr xxhash::hash<32>::hash_type cx_h = "ABC"_xxh32;
	EXPECT_EQ(c_h, cx_h);
}

TEST(xxh64_cx_test, user_literal_xxh64_cx_raw)
{
	std::uint64_t c_h = XXH64("ABC", std::strlen("ABC"), XXHASH_CX_XXH64_SEED);
	constexpr xxhash::hash<64>::hash_type cx_h = "ABC"_xxh64;
	EXPECT_EQ(c_h, cx_h);
}



TEST(xxh32_cx_test, user_literal_xxh32_cx)
{
	std::uint32_t c_h = XXH32(STR_ABC, std::strlen(STR_ABC), XXHASH_CX_XXH32_SEED);
	const xxhash::hash<32>::hash_type cx_h = STR_XXH32(STR_ABC);
	EXPECT_EQ(c_h, cx_h);
}

TEST(xxh64_cx_test, user_literal_xxh64_cx)
{
	std::uint64_t c_h = XXH64(STR_ABC, std::strlen(STR_ABC), XXHASH_CX_XXH64_SEED);
	const xxhash::hash<64>::hash_type cx_h = STR_XXH64(STR_ABC);
	EXPECT_EQ(c_h, cx_h);
}


