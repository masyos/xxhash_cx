# xxhash_cx

[xxHash](http://cyan4973.github.io/xxHash/)  
C++14 constexpr version.

I looked at the algorithm document and wrote it.  
ref. [xxHash-specification (draft)](https://github.com/Cyan4973/xxHash/wiki/xxHash-specification-(draft))

## usage

### simple

```C++:simple.cpp
{
  xxhash::hash<32>::hash_type h32 = xxhash::xxh32(data, bytes, seed);
  xxhash::hash<64>::hash_type h64 = xxhash::xxh64(data, bytes, seed);
}
```

### user defined literal.

```C++:user_literals.cpp
{
  using xxhash::operator""_xxh32;
  using xxhash::operator""_xxh64;

  xxhash::hash<32>::hash_type h32 = "text-hogehoge"_xx32;
  xxhash::hash<64>::hash_type h64 = "text-hogehoge"_xx64;
}
```
### user defined literal & MACRO string.

```C++:user_literals_macro.cpp
#define	STR_XXH32_(s)	s ## _xxh32
#define	STR_XXH64_(s)	s ## _xxh64
#define	STR_XXH32(s)	STR_XXH32_(s)
#define	STR_XXH64(s)	STR_XXH64_(s)

#define STR_HOGE  "hogehoge"

using xxhash::operator""_xxh32;
using xxhash::operator""_xxh64;
{
  const xxhash::hash<32>::hash_type cx_h = STR_XXH32(STR_HOGE);
  const xxhash::hash<64>::hash_type cx_h = STR_XXH64(STR_HOGE);
}
```

### change user defined literal seed.

```C++:user_literals_seed.cpp
#define	XXHASH_CX_XXH32_SEED	(20180101UL)
#define	XXHASH_CX_XXH64_SEED	(201801011200ULL)
{
  ...
}

```

## warning

* Little endian only.

## License

BSD 2-Clause License.



