# xxhash_cx

[xxHash](https://github.com/Cyan4973/xxHash)  
C++ (C++14) constexpr version.

I looked at the algorithm document and wrote it.  
ref. xxHash-specification - (xxHash/doc/xxhash_spec.md) 


## usage

### simple

```C++:simple.cpp
#include "xxhash_cx.h"

void func()
{
  xxhash::hash<32>::hash_type h32 = xxhash::xxh32(data, bytes, seed);
  xxhash::hash<64>::hash_type h64 = xxhash::xxh64(data, bytes, seed);
  // ...
}
```

### user defined literal.

```C++:user_literals.cpp
#include "xxhash_cx.h"

void func()
{
  using namespace xxhash::literals;

  xxhash::hash<32>::hash_type h32 = "text-hogehoge"_xxh32;
  xxhash::hash<64>::hash_type h64 = "text-hogehoge"_xxh64;
  // ...
}
```
### user defined literal & MACRO string.

```C++:user_literals_macro.cpp
#include "xxhash_cx.h"

#define	STR_XXH32_(s)	s ## _xxh32
#define	STR_XXH64_(s)	s ## _xxh64
#define	STR_XXH32(s)	STR_XXH32_(s)
#define	STR_XXH64(s)	STR_XXH64_(s)

#define STR_HOGE  "hogehoge"

using namespace xxhash::literals;
void func()
{
  const xxhash::hash<32>::hash_type cx_h = STR_XXH32(STR_HOGE);
  const xxhash::hash<64>::hash_type cx_h = STR_XXH64(STR_HOGE);
  // ...
}
```

### change user defined literal seed.

```C++:user_literals_seed.cpp
#define	XXHASH_CX_XXH32_SEED	(20180101UL)
#define	XXHASH_CX_XXH64_SEED	(201801011200ULL)
#include "xxhash_cx.h"

void func()
{
  // ...
}

```

## warning

* Little endian only.

## License

MIT License.
