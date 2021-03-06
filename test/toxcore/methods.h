#pragma once

#include "util.h"

#include <msgpack.h>


#define CHECK(COND) do { if (!(COND)) return #COND; } while (0)

#define CHECK_SIZE(ARG, SIZE) do { \
  if ((ARG).size != (SIZE)) \
    return ssprintf ("Size of `" #ARG "' expected to be %zu, but was %zu", \
                     SIZE, (ARG).size); \
} while (0)

#define CHECK_TYPE(ARG, TYPE) do { \
  if ((ARG).type != (TYPE)) \
    return ssprintf ("Type of `" #ARG "' expected to be %s, but was %s", \
                     type_name (TYPE), type_name ((ARG).type)); \
} while (0)


#define SUCCESS msgpack_pack_array (res, 0); if (true)


#define METHOD(TYPE, SERVICE, NAME) \
char const * \
SERVICE##_##NAME (msgpack_object_##TYPE args, msgpack_packer *res)


// These are not defined by msgpack.h, but we need them for uniformity in the
// METHOD macro.
typedef int64_t msgpack_object_i64;
typedef uint64_t msgpack_object_u64;


METHOD (array, Binary, decode);
METHOD (array, Binary, encode);


char const *call_method (msgpack_object_str name, msgpack_object_array args, msgpack_packer *res);

extern char const *const pending;
extern char const *const unimplemented;
