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
    /*decltype(_impl_.resource_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.dest_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.data_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.method_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
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
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_protobufMessage_2eproto[1];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_protobufMessage_2eproto = nullptr;

const uint32_t TableStruct_protobufMessage_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_.method_),
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_.resource_),
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_.dest_),
  PROTOBUF_FIELD_OFFSET(::RouterProtobufMessage, _impl_.data_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::RouterProtobufMessage)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_RouterProtobufMessage_default_instance_._instance,
};

const char descriptor_table_protodef_protobufMessage_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\025protobufMessage.proto\"e\n\025RouterProtobu"
  "fMessage\022\036\n\006method\030\001 \001(\0162\016.RouterMethods"
  "\022\020\n\010resource\030\002 \001(\t\022\014\n\004dest\030\003 \001(\t\022\014\n\004data"
  "\030\004 \001(\t*h\n\rRouterMethods\022\027\n\023ROUTER_METHOD"
  "S_OCPP\020\000\022\034\n\030ROUTER_METHODS_SAVE_DATA\020\001\022 "
  "\n\034ROUTER_METHODS_DELETE_SOCKET\020\002b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_protobufMessage_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_protobufMessage_2eproto = {
    false, false, 240, descriptor_table_protodef_protobufMessage_2eproto,
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
      return true;
    default:
      return false;
  }
}


// ===================================================================

class RouterProtobufMessage::_Internal {
 public:
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
      decltype(_impl_.resource_){}
    , decltype(_impl_.dest_){}
    , decltype(_impl_.data_){}
    , decltype(_impl_.method_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.resource_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.resource_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_resource().empty()) {
    _this->_impl_.resource_.Set(from._internal_resource(), 
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
  _this->_impl_.method_ = from._impl_.method_;
  // @@protoc_insertion_point(copy_constructor:RouterProtobufMessage)
}

inline void RouterProtobufMessage::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.resource_){}
    , decltype(_impl_.dest_){}
    , decltype(_impl_.data_){}
    , decltype(_impl_.method_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.resource_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.resource_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.dest_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.dest_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.data_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data_.Set("", GetArenaForAllocation());
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
  _impl_.resource_.Destroy();
  _impl_.dest_.Destroy();
  _impl_.data_.Destroy();
}

void RouterProtobufMessage::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void RouterProtobufMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:RouterProtobufMessage)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.resource_.ClearToEmpty();
  _impl_.dest_.ClearToEmpty();
  _impl_.data_.ClearToEmpty();
  _impl_.method_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* RouterProtobufMessage::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .RouterMethods method = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_method(static_cast<::RouterMethods>(val));
        } else
          goto handle_unusual;
        continue;
      // string resource = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_resource();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "RouterProtobufMessage.resource"));
        } else
          goto handle_unusual;
        continue;
      // string dest = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_dest();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "RouterProtobufMessage.dest"));
        } else
          goto handle_unusual;
        continue;
      // string data = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          auto str = _internal_mutable_data();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "RouterProtobufMessage.data"));
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

  // .RouterMethods method = 1;
  if (this->_internal_method() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      1, this->_internal_method(), target);
  }

  // string resource = 2;
  if (!this->_internal_resource().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_resource().data(), static_cast<int>(this->_internal_resource().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "RouterProtobufMessage.resource");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_resource(), target);
  }

  // string dest = 3;
  if (!this->_internal_dest().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_dest().data(), static_cast<int>(this->_internal_dest().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "RouterProtobufMessage.dest");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_dest(), target);
  }

  // string data = 4;
  if (!this->_internal_data().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_data().data(), static_cast<int>(this->_internal_data().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "RouterProtobufMessage.data");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_data(), target);
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

  // string resource = 2;
  if (!this->_internal_resource().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_resource());
  }

  // string dest = 3;
  if (!this->_internal_dest().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_dest());
  }

  // string data = 4;
  if (!this->_internal_data().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_data());
  }

  // .RouterMethods method = 1;
  if (this->_internal_method() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_method());
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

  if (!from._internal_resource().empty()) {
    _this->_internal_set_resource(from._internal_resource());
  }
  if (!from._internal_dest().empty()) {
    _this->_internal_set_dest(from._internal_dest());
  }
  if (!from._internal_data().empty()) {
    _this->_internal_set_data(from._internal_data());
  }
  if (from._internal_method() != 0) {
    _this->_internal_set_method(from._internal_method());
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
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.resource_, lhs_arena,
      &other->_impl_.resource_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.dest_, lhs_arena,
      &other->_impl_.dest_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.data_, lhs_arena,
      &other->_impl_.data_, rhs_arena
  );
  swap(_impl_.method_, other->_impl_.method_);
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
