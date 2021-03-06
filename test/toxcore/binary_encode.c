#include "methods.h"


METHOD (bin, Binary_encode, CipherText) { return pending; }


METHOD (array, Binary_encode, DhtPacket) { return pending; }


METHOD (array, Binary_encode, HostAddress) { return pending; }


METHOD (u64, Binary_encode, Word64) { return pending; }


METHOD (bin, Binary_encode, Key) { return pending; }


METHOD (array, Binary_encode, KeyPair)
{
  CHECK_SIZE (args, 2);
  CHECK_TYPE (args.ptr[0], MSGPACK_OBJECT_BIN);
  CHECK_TYPE (args.ptr[1], MSGPACK_OBJECT_BIN);

  msgpack_object_bin secret_key = args.ptr[0].via.bin;
  msgpack_object_bin public_key = args.ptr[1].via.bin;

  CHECK_SIZE (secret_key, 32);
  CHECK_SIZE (public_key, 32);

  SUCCESS {
    uint8_t data[64];
    memcpy (data, secret_key.ptr, 32);
    memcpy (data + 32, public_key.ptr, 32);
    msgpack_pack_bin (res, 64);
    msgpack_pack_bin_body (res, data, 64);
  }

  return 0;
}

METHOD (array, Binary_encode, NodeInfo) { return pending; }


METHOD (bin, Binary_encode, NodesRequest) { return pending; }


METHOD (array, Binary_encode, NodesResponse) { return pending; }


METHOD (array, Binary_encode, Packet) { return pending; }


METHOD (u64, Binary_encode, PacketKind) { return pending; }


METHOD (u64, Binary_encode, PingPacket) { return pending; }


METHOD (bin, Binary_encode, PlainText) { return pending; }


METHOD (u64, Binary_encode, PortNumber) { return pending; }


METHOD (array, Binary_encode, RpcPacket) { return pending; }


METHOD (array, Binary_encode, SocketAddress) { return pending; }


METHOD (u64, Binary_encode, TransportProtocol) { return pending; }


METHOD (array, Binary, encode)
{
  CHECK_SIZE (args, 2);
  CHECK_TYPE (args.ptr[0], MSGPACK_OBJECT_STR);

  msgpack_object_str type = args.ptr[0].via.str;
#define DISPATCH(TYPE, UTYPE, LTYPE) do { \
  if (type.size == sizeof #TYPE - 1 && \
      memcmp (type.ptr, #TYPE, type.size) == 0) \
    { \
      CHECK_TYPE (args.ptr[1], MSGPACK_OBJECT_##UTYPE); \
      return Binary_encode_##TYPE (args.ptr[1].via.LTYPE, res); \
    } \
} while (0)
  DISPATCH (CipherText       , BIN             , bin);
  DISPATCH (DhtPacket        , ARRAY           , array);
  DISPATCH (HostAddress      , ARRAY           , array);
  DISPATCH (Word64           , POSITIVE_INTEGER, u64);
  DISPATCH (Key              , BIN             , bin);
  DISPATCH (KeyPair          , ARRAY           , array);
  DISPATCH (NodeInfo         , ARRAY           , array);
  DISPATCH (NodesRequest     , BIN             , bin);
  DISPATCH (NodesResponse    , ARRAY           , array);
  DISPATCH (Packet           , ARRAY           , array);
  DISPATCH (PacketKind       , POSITIVE_INTEGER, u64);
  DISPATCH (PingPacket       , POSITIVE_INTEGER, u64);
  DISPATCH (PlainText        , BIN             , bin);
  DISPATCH (PortNumber       , POSITIVE_INTEGER, u64);
  DISPATCH (RpcPacket        , ARRAY           , array);
  DISPATCH (SocketAddress    , ARRAY           , array);
  DISPATCH (TransportProtocol, POSITIVE_INTEGER, u64);
#undef DISPATCH

  return unimplemented;
}
