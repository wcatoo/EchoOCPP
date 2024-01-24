// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protobufMessage.proto

#include "protobufMessage.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

PROTOBUF_CONSTEXPR RouterProtobufMessage::RouterProtobufMessage(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.uuid_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.source_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.dest_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.data_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.ocpp_type_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.method_)*/0
  , /*decltype(_impl_.message_type_)*/0} {}
struct RouterProtobufMessageDefaultTypeInternal {
  PROTOBUF_CONSTEXPR RouterProtobufMessageDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~RouterProtobufMessageDefaultTypeInternal() {}
  union {
    RouterProtobufMessage _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 RouterProtobufMessageDefaultTypeInternal _RouterProtobufMessage_default_instance_;
static ::_pb::Metadata file_level_metadata_protobufMessage_2eproto[1];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_protobufMessage_2eproto[2];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_protobufMessage_2eproto = nullptr;

const uint32_t TableStruct_protobufMessage_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_.uuid_),
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_.method_),
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_.message_type_),
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_.source_),
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_.dest_),
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_.data_),
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_.ocpp_type_),
  ~0u,
  ~0u,
  ~0u,
  ~0u,
  ~0u,
  ~0u,
  0,
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 13, -1, sizeof(::RouterProtobufMessage)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_RouterProtobufMessage_default_instance_._instance,
};

const char descriptor_table_protodef_protobufMessage_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\025protobufMessage.proto\"\273\001\n\025RouterProtob"
  "ufMessage\022\014\n\004uuid\030\001 \001(\t\022\036\n\006method\030\002 \001(\0162"
  "\016.RouterMethods\022\"\n\014message_type\030\003 \001(\0162\014."
  "MessageType\022\016\n\006source\030\004 \001(\t\022\014\n\004dest\030\005 \001("
  "\t\022\014\n\004data\030\006 \001(\t\022\026\n\tocpp_type\030\007 \001(\tH\000\210\001\001B"
  "\014\n\n_ocpp_type*\277\001\n\rRouterMethods\022\032\n\026ROUTE"
  "R_METHODS_OCPP201\020\000\022!\n\035ROUTER_METHODS_WR"
  "ITE_DATABASE\020\001\022 \n\034ROUTER_METHODS_READ_DA"
  "TABASE\020\002\022\'\n#ROUTER_METHODS_NOTIFY_REALTI"
  "ME_DATA\020\003\022$\n ROUTER_METHODS_GET_REALTIME"
  "_DATA\020\004*Q\n\013MessageType\022\013\n\007REQUEST\020\000\022\014\n\010R"
  "ESPONSE\020\001\022\022\n\016NETWORK_ONLINE\020\002\022\023\n\017NETWORK"
  "_OFFLINE\020\003b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_protobufMessage_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_protobufMessage_2eproto = {
    false, false, 498, descriptor_table_protodef_protobufMessage_2eproto,
    "protobufMessage.proto",
    &descriptor_table_protobufMessage_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_protobufMessage_2eproto::offsets,
    file_level_metadata_protobufMessage_2eproto, file_level_enum_descriptors_protobufMessage_2eproto,
    file_level_service_descriptors_protobufMessage_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_protobufMessage_2eproto_getter() {
  return &descriptor_table_protobufMessage_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_protobufMessage_2eproto(&descriptor_table_protobufMessage_2eproto);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* RouterMethods_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_protobufMessage_2eproto);
  return file_level_enum_descriptors_protobufMessage_2eproto[0];
}
bool RouterMethods_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MessageType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_protobufMessage_2eproto);
  return file_level_enum_descriptors_protobufMessage_2eproto[1];
}
bool MessageType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class RouterProtobufMessage::_Internal {
 public:
  using HasBits = decltype(std::declval<RouterProtobufMessage>()._impl_._has_bits_);
  static void set_has_ocpp_type(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

RouterProtobufMessage::RouterProtobufMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:RouterProtobufMessage)
}
RouterProtobufMessage::RouterProtobufMessage(const RouterProtobufMessage& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  RouterProtobufMessage* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.uuid_){}
    , decltype(_impl_.source_){}
    , decltype(_impl_.dest_){}
    , decltype(_impl_.data_){}
    , decltype(_impl_.ocpp_type_){}
    , decltype(_impl_.method_){}
    , decltype(_impl_.message_type_){}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.uuid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.uuid_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_uuid().empty()) {
    _this->_impl_.uuid_.Set(from._internal_uuid(), 
      _this->GetArenaForAllocation());
  }
  _impl_.source_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.source_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_source().empty()) {
    _this->_impl_.source_.Set(from._internal_source(), 
      _this->GetArenaForAllocation());
  }
  _impl_.dest_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.dest_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_dest().empty()) {
    _this->_impl_.dest_.Set(from._internal_dest(), 
      _this->GetArenaForAllocation());
  }
  _impl_.data_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_data().empty()) {
    _this->_impl_.data_.Set(from._internal_data(), 
      _this->GetArenaForAllocation());
  }
  _impl_.ocpp_type_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.ocpp_type_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (from._internal_has_ocpp_type()) {
    _this->_impl_.ocpp_type_.Set(from._internal_ocpp_type(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.method_, &from._impl_.method_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.message_type_) -
    reinterpret_cast<char*>(&_impl_.method_)) + sizeof(_impl_.message_type_));
  // @@protoc_insertion_point(copy_constructor:RouterProtobufMessage)
}

inline void RouterProtobufMessage::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.uuid_){}
    , decltype(_impl_.source_){}
    , decltype(_impl_.dest_){}
    , decltype(_impl_.data_){}
    , decltype(_impl_.ocpp_type_){}
    , decltype(_impl_.method_){0}
    , decltype(_impl_.message_type_){0}
  };
  _impl_.uuid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.uuid_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.source_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.source_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.dest_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.dest_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.data_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.ocpp_type_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.ocpp_type_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

RouterProtobufMessage::~RouterProtobufMessage() {
  // @@protoc_insertion_point(destructor:RouterProtobufMessage)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void RouterProtobufMessage::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.uuid_.Destroy();
  _impl_.source_.Destroy();
  _impl_.dest_.Destroy();
  _impl_.data_.Destroy();
  _impl_.ocpp_type_.Destroy();
}

void RouterProtobufMessage::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void RouterProtobufMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:RouterProtobufMessage)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.uuid_.ClearToEmpty();
  _impl_.source_.ClearToEmpty();
  _impl_.dest_.ClearToEmpty();
  _impl_.data_.ClearToEmpty();
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    _impl_.ocpp_type_.ClearNonDefaultToEmpty();
  }
  ::memset(&_impl_.method_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.message_type_) -
      reinterpret_cast<char*>(&_impl_.method_)) + sizeof(_impl_.message_type_));
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* RouterProtobufMessage::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string uuid = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_uuid();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "RouterProtobufMessage.uuid"));
        } else
          goto handle_unusual;
        continue;
      // .RouterMethods method = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_method(static_cast<::RouterMethods>(val));
        } else
          goto handle_unusual;
        continue;
      // .MessageType message_type = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_message_type(static_cast<::MessageType>(val));
        } else
          goto handle_unusual;
        continue;
      // string source = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          auto str = _internal_mutable_source();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "RouterProtobufMessage.source"));
        } else
          goto handle_unusual;
        continue;
      // string dest = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          auto str = _internal_mutable_dest();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "RouterProtobufMessage.dest"));
        } else
          goto handle_unusual;
        continue;
      // string data = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 50)) {
          auto str = _internal_mutable_data();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "RouterProtobufMessage.data"));
        } else
          goto handle_unusual;
        continue;
      // optional string ocpp_type = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 58)) {
          auto str = _internal_mutable_ocpp_type();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "RouterProtobufMessage.ocpp_type"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _impl_._has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* RouterProtobufMessage::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:RouterProtobufMessage)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string uuid = 1;
  if (!this->_internal_uuid().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_uuid().data(), static_cast<int>(this->_internal_uuid().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "RouterProtobufMessage.uuid");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_uuid(), target);
  }

  // .RouterMethods method = 2;
  if (this->_internal_method() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      2, this->_internal_method(), target);
  }

  // .MessageType message_type = 3;
  if (this->_internal_message_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      3, this->_internal_message_type(), target);
  }

  // string source = 4;
  if (!this->_internal_source().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_source().data(), static_cast<int>(this->_internal_source().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "RouterProtobufMessage.source");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_source(), target);
  }

  // string dest = 5;
  if (!this->_internal_dest().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_dest().data(), static_cast<int>(this->_internal_dest().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "RouterProtobufMessage.dest");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_dest(), target);
  }

  // string data = 6;
  if (!this->_internal_data().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_data().data(), static_cast<int>(this->_internal_data().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "RouterProtobufMessage.data");
    target = stream->WriteStringMaybeAliased(
        6, this->_internal_data(), target);
  }

  // optional string ocpp_type = 7;
  if (_internal_has_ocpp_type()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_ocpp_type().data(), static_cast<int>(this->_internal_ocpp_type().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "RouterProtobufMessage.ocpp_type");
    target = stream->WriteStringMaybeAliased(
        7, this->_internal_ocpp_type(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:RouterProtobufMessage)
  return target;
}

size_t RouterProtobufMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:RouterProtobufMessage)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string uuid = 1;
  if (!this->_internal_uuid().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_uuid());
  }

  // string source = 4;
  if (!this->_internal_source().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_source());
  }

  // string dest = 5;
  if (!this->_internal_dest().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_dest());
  }

  // string data = 6;
  if (!this->_internal_data().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_data());
  }

  // optional string ocpp_type = 7;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_ocpp_type());
  }

  // .RouterMethods method = 2;
  if (this->_internal_method() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_method());
  }

  // .MessageType message_type = 3;
  if (this->_internal_message_type() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_message_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData RouterProtobufMessage::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    RouterProtobufMessage::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*RouterProtobufMessage::GetClassData() const { return &_class_data_; }


void RouterProtobufMessage::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<RouterProtobufMessage*>(&to_msg);
  auto& from = static_cast<const RouterProtobufMessage&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:RouterProtobufMessage)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_uuid().empty()) {
    _this->_internal_set_uuid(from._internal_uuid());
  }
  if (!from._internal_source().empty()) {
    _this->_internal_set_source(from._internal_source());
  }
  if (!from._internal_dest().empty()) {
    _this->_internal_set_dest(from._internal_dest());
  }
  if (!from._internal_data().empty()) {
    _this->_internal_set_data(from._internal_data());
  }
  if (from._internal_has_ocpp_type()) {
    _this->_internal_set_ocpp_type(from._internal_ocpp_type());
  }
  if (from._internal_method() != 0) {
    _this->_internal_set_method(from._internal_method());
  }
  if (from._internal_message_type() != 0) {
    _this->_internal_set_message_type(from._internal_message_type());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void RouterProtobufMessage::CopyFrom(const RouterProtobufMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:RouterProtobufMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RouterProtobufMessage::IsInitialized() const {
  return true;
}

void RouterProtobufMessage::InternalSwap(RouterProtobufMessage* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.uuid_, lhs_arena,
      &other->_impl_.uuid_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.source_, lhs_arena,
      &other->_impl_.source_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.dest_, lhs_arena,
      &other->_impl_.dest_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.data_, lhs_arena,
      &other->_impl_.data_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.ocpp_type_, lhs_arena,
      &other->_impl_.ocpp_type_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(RouterProtobufMessage, _impl_.message_type_)
      + sizeof(RouterProtobufMessage::_impl_.message_type_)
      - PROTOBUF_FIELD_OFFSET(RouterProtobufMessage, _impl_.method_)>(
          reinterpret_cast<char*>(&_impl_.method_),
          reinterpret_cast<char*>(&other->_impl_.method_));
}

::PROTOBUF_NAMESPACE_ID::Metadata RouterProtobufMessage::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_protobufMessage_2eproto_getter, &descriptor_table_protobufMessage_2eproto_once,
      file_level_metadata_protobufMessage_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::RouterProtobufMessage*
Arena::CreateMaybeMessage< ::RouterProtobufMessage >(Arena* arena) {
  return Arena::CreateMessageInternal< ::RouterProtobufMessage >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
