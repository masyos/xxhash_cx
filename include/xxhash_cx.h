// xxHash 32/64 - C++14 constexpr version.

// reference: https://github.com/Cyan4973/xxHash/wiki/xxHash-specification-(draft)

#pragma once

#ifndef	XXHASH_CX_H
#define	XXHASH_CX_H

#include <cstdint>
#include <array>
#include <string>
#include <limits>

#ifndef	XXHASH_CX_XXH32_SEED
///	@brief	user defined literals - default xxHash32 seed. 
#define	XXHASH_CX_XXH32_SEED	(20180101UL)
#endif
#ifndef	XXHASH_CX_XXH64_SEED	
///	@brief	user defined literals - default xxHash64 seed. 
#define	XXHASH_CX_XXH64_SEED	(201801011200ULL)
#endif

///	@brief	xxhash namespace.
namespace xxhash {

	
namespace details {

	template <class T>
	constexpr T rotl(T n, std::size_t shift)
	{
		static_assert(std::numeric_limits<T>::is_integer, "integer only.");
		return ((n << shift) | (n >> (std::numeric_limits<T>::digits - shift)));
	}
	template <class T>
	constexpr T read(const void*& p)
	{
		const T* t = static_cast<const T*>(p);
		p = t + 1;
		return *t;
	}
}

///	@brief	xxHash.
template <int N>
class hash {
};


///	@brief	xxHash32
template<>
class hash<32> {
public:
	///	@brief	xxHash32 data.
	using hash_type = std::uint32_t;

	constexpr static hash_type xxh(const void* input, std::size_t len, hash_type seed) {
		const void* src = static_cast<const std::uint8_t*>(input);
		const std::uint8_t* end = static_cast<const std::uint8_t*>(src) + len;
		hash_type acc = 0;
		// step 1.
		if (len >= 16) {
			const std::uint8_t* limit = end - 16;
			hash_type acc0 = seed + prime(0) + prime(1);
			hash_type acc1 = seed + prime(1);
			hash_type acc2 = seed + 0;
			hash_type acc3 = seed - prime(0);
			// step 2.
			do {
				acc0 = round(acc0, details::read<std::uint32_t>(src));
				acc1 = round(acc1, details::read<std::uint32_t>(src));
				acc2 = round(acc2, details::read<std::uint32_t>(src));
				acc3 = round(acc3, details::read<std::uint32_t>(src));
			} while (src <= limit);
			// step 3.
			acc = convergence(acc0, acc1, acc2, acc3);
		} else {
			acc = seed + prime(4);
		}
		// step 4.
		acc += static_cast<hash_type>(len);
		// step 5.
		while ((static_cast<const std::uint8_t*>(src) + 4) <= end) {
			acc = details::rotl<hash_type>(acc + (details::read<std::uint32_t>(src) * prime(2)), 17) * prime(3);
		}
		while (src < end) {
			acc = details::rotl<hash_type>(acc + details::read<std::uint8_t>(src) * prime(4), 11) * prime(0);
		}
		// step 6.
		acc = final_mix(acc);
		// step 7.
		return acc;
	}

private:
	constexpr static std::array<hash_type, 5> primes{
		2654435761U, 2246822519U, 3266489917U, 668265263U, 374761393U
	};
	constexpr static hash_type prime(int i) { return primes[i]; }

	constexpr static hash_type round(hash_type acc, hash_type input)
	{
		return details::rotl<hash_type>(acc + (input * prime(1)), 13) * prime(0);
	}

	constexpr static hash_type convergence(hash_type acc0, hash_type acc1, hash_type acc2, hash_type acc3)
	{
		return details::rotl(acc0, 1) + details::rotl(acc1, 7) + details::rotl(acc2, 12) + details::rotl(acc3, 18);
	}

	constexpr static hash_type final_mix(hash_type acc)
	{
		acc = (acc ^ (acc >> 15)) * prime(1);
		acc = (acc ^ (acc >> 13)) * prime(2);
		acc = acc ^ (acc >> 16);
		return acc;
	}
};

///	@brief	xxHash64.
template <>
class hash<64> {
public:
	///	@brief	xxHash64 data.
	using hash_type = std::uint64_t;

	constexpr static hash_type xxh(const void* input, std::size_t len, hash_type seed)
	{
		const void* src = static_cast<const std::uint8_t*>(input);
		const std::uint8_t* end = static_cast<const std::uint8_t*>(src) + len;
		hash_type acc = 0;
		// step 1.
		if (len >= 32) {
			const std::uint8_t* limit = end - 32;
			hash_type acc0 = seed + prime(0) + prime(1);
			hash_type acc1 = seed + prime(1);
			hash_type acc2 = seed + 0;
			hash_type acc3 = seed - prime(0);
			// step 2.
			do {
				acc0 = round(acc0, details::read<std::uint64_t>(src));
				acc1 = round(acc1, details::read<std::uint64_t>(src));
				acc2 = round(acc2, details::read<std::uint64_t>(src));
				acc3 = round(acc3, details::read<std::uint64_t>(src));
			} while (src <= limit);
			// step 3.
			acc = convergence(acc0, acc1, acc2, acc3);
		} else {
			acc = seed + prime(4);
		}
		// step 4.
		acc += len;
		// step 5.
		while ((static_cast<const std::uint8_t*>(src) + 8) <= end)
		{
			acc = details::rotl<std::uint64_t>(acc ^ round(0, details::read<std::uint64_t>(src)), 27) * prime(0) + prime(3);
		}
		if ((static_cast<const std::uint8_t*>(src) + 4) <= end) {
			acc = details::rotl<hash_type>(acc ^ (details::read<std::uint32_t>(src) * prime(0)), 23) * prime(1) + prime(2);
		}
		while (src < end) {
			acc = details::rotl<hash_type>(acc ^ (details::read<std::uint8_t>(src) * prime(4)), 11) * prime(0);
		}
		// step 6.
		acc = final_mix(acc);
		// step 7.
		return acc;
	}

private:
	constexpr static std::array<hash_type, 5> primes{
		11400714785074694791ULL, 14029467366897019727ULL, 1609587929392839161ULL, 9650029242287828579ULL, 2870177450012600261ULL
	};
	constexpr static hash_type prime(int i) { return primes[i]; }

	constexpr static hash_type round(hash_type acc, hash_type input)
	{
		acc += input * prime(1);
		acc = details::rotl(acc, 31);
		return (acc * prime(0));
	}

	constexpr static hash_type mearge_accumulator(hash_type acc, hash_type acc_n)
	{
		return ((acc ^ round(0, acc_n)) * prime(0)) + prime(3);
	}

	constexpr static hash_type convergence(hash_type acc0, hash_type acc1, hash_type acc2, hash_type acc3)
	{
		hash_type acc = details::rotl(acc0, 1) + details::rotl(acc1, 7) + details::rotl(acc2, 12) + details::rotl(acc3, 18);
		acc = mearge_accumulator(acc, acc0);
		acc = mearge_accumulator(acc, acc1);
		acc = mearge_accumulator(acc, acc2);
		acc = mearge_accumulator(acc, acc3);
		return acc;
	}

	constexpr static hash_type final_mix(hash_type acc) {
		acc = (acc ^ (acc >> 33)) * prime(1);
		acc = (acc ^ (acc >> 29)) * prime(2);
		acc = (acc ^ (acc >> 32));
		return acc;
	}

};


///	@brief	xxHash32.
///	@param	buf		data.
///	@param	len		data length(byte).
///	@param	seed	seed.
///	@return	xxHash32
constexpr hash<32>::hash_type xxh32(const void* buf, std::size_t len, hash<32>::hash_type seed) {
	return hash<32>::xxh(buf, len, seed);
}

///	@brief	xxHash64.
///	@param	buf		data.
///	@param	len		data length(byte).
///	@param	seed	seed.
///	@return	xxHash64
constexpr hash<64>::hash_type xxh64(const void* buf, std::size_t len, hash<64>::hash_type seed) {
	return hash<64>::xxh(buf, len, seed);
}


///	@brief	user defined literals - xxHash32.
constexpr hash<32>::hash_type operator"" _xxh32(const char* str, std::size_t len) {
	return xxh32(str, len, XXHASH_CX_XXH32_SEED);
}

///	@brief	user defined literals - xxHash64.
constexpr hash<64>::hash_type operator"" _xxh64(const char* str, std::size_t len) {
	return xxh64(str, len, XXHASH_CX_XXH64_SEED);
}

}	// namespace xxhash.

#endif

