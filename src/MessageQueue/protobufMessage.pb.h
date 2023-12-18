// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protobufMessage.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_protobufMessage_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_protobufMessage_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_protobufMessage_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_protobufMessage_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_protobufMessage_2eproto;
class RouterProtobufMessage;
struct RouterProtobufMessageDefaultTypeInternal;
extern RouterProtobufMessageDefaultTypeInternal _RouterProtobufMessage_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::RouterProtobufMessage* Arena::CreateMaybeMessage<::RouterProtobufMessage>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

enum RouterMethods : int {
  ROUTER_METHODS_OCPP = 0,
  ROUTER_METHODS_SAVE_DATA = 1,
  ROUTER_METHODS_DELETE_SOCKET = 2,
  RouterMethods_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  RouterMethods_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool RouterMethods_IsValid(int value);
constexpr RouterMethods RouterMethods_MIN = ROUTER_METHODS_OCPP;
constexpr RouterMethods RouterMethods_MAX = ROUTER_METHODS_DELETE_SOCKET;
constexpr int RouterMethods_ARRAYSIZE = RouterMethods_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* RouterMethods_descriptor();
template<typename T>
inline const std::string& RouterMethods_Name(T enum_t_value) {
  static_assert(::std::is_same<T, RouterMethods>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function RouterMethods_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    RouterMethods_descriptor(), enum_t_value);
}
inline bool RouterMethods_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, RouterMethods* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<RouterMethods>(
    RouterMethods_descriptor(), name, value);
}
// ===================================================================

class RouterProtobufMessage final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:RouterProtobufMessage) */ {
 public:
  inline RouterProtobufMessage() : RouterProtobufMessage(nullptr) {}
  ~RouterProtobufMessage() override;
  explicit PROTOBUF_CONSTEXPR RouterProtobufMessage(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  RouterProtobufMessage(const RouterProtobufMessage& from);
  RouterProtobufMessage(RouterProtobufMessage&& from) noexcept
    : RouterProtobufMessage() {
    *this = ::std::move(from);
  }

  inline RouterProtobufMessage& operator=(const RouterProtobufMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline RouterProtobufMessage& operator=(RouterProtobufMessage&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const RouterProtobufMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const RouterProtobufMessage* internal_default_instance() {
    return reinterpret_cast<const RouterProtobufMessage*>(
               &_RouterProtobufMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(RouterProtobufMessage& a, RouterProtobufMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(RouterProtobufMessage* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RouterProtobufMessage* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  RouterProtobufMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<RouterProtobufMessage>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const RouterProtobufMessage& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const RouterProtobufMessage& from) {
    RouterProtobufMessage::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RouterProtobufMessage* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "RouterProtobufMessage";
  }
  protected:
  explicit RouterProtobufMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kResourceFieldNumber = 2,
    kDestFieldNumber = 3,
    kDataFieldNumber = 4,
    kMethodFieldNumber = 1,
  };
  // string resource = 2;
  void clear_resource();
  const std::string& resource() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_resource(ArgT0&& arg0, ArgT... args);
  std::string* mutable_resource();
  PROTOBUF_NODISCARD std::string* release_resource();
  void set_allocated_resource(std::string* resource);
  private:
  const std::string& _internal_resource() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_resource(const std::string& value);
  std::string* _internal_mutable_resource();
  public:

  // string dest = 3;
  void clear_dest();
  const std::string& dest() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_dest(ArgT0&& arg0, ArgT... args);
  std::string* mutable_dest();
  PROTOBUF_NODISCARD std::string* release_dest();
  void set_allocated_dest(std::string* dest);
  private:
  const std::string& _internal_dest() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_dest(const std::string& value);
  std::string* _internal_mutable_dest();
  public:

  // string data = 4;
  void clear_data();
  const std::string& data() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_data(ArgT0&& arg0, ArgT... args);
  std::string* mutable_data();
  PROTOBUF_NODISCARD std::string* release_data();
  void set_allocated_data(std::string* data);
  private:
  const std::string& _internal_data() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_data(const std::string& value);
  std::string* _internal_mutable_data();
  public:

  // .RouterMethods method = 1;
  void clear_method();
  ::RouterMethods method() const;
  void set_method(::RouterMethods value);
  private:
  ::RouterMethods _internal_method() const;
  void _internal_set_method(::RouterMethods value);
  public:

  // @@protoc_insertion_point(class_scope:RouterProtobufMessage)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr resource_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr dest_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr data_;
    int method_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_protobufMessage_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RouterProtobufMessage

// .RouterMethods method = 1;
inline void RouterProtobufMessage::clear_method() {
  _impl_.method_ = 0;
}
inline ::RouterMethods RouterProtobufMessage::_internal_method() const {
  return static_cast< ::RouterMethods >(_impl_.method_);
}
inline ::RouterMethods RouterProtobufMessage::method() const {
  // @@protoc_insertion_point(field_get:RouterProtobufMessage.method)
  return _internal_method();
}
inline void RouterProtobufMessage::_internal_set_method(::RouterMethods value) {
  
  _impl_.method_ = value;
}
inline void RouterProtobufMessage::set_method(::RouterMethods value) {
  _internal_set_method(value);
  // @@protoc_insertion_point(field_set:RouterProtobufMessage.method)
}

// string resource = 2;
inline void RouterProtobufMessage::clear_resource() {
  _impl_.resource_.ClearToEmpty();
}
inline const std::string& RouterProtobufMessage::resource() const {
  // @@protoc_insertion_point(field_get:RouterProtobufMessage.resource)
  return _internal_resource();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void RouterProtobufMessage::set_resource(ArgT0&& arg0, ArgT... args) {
 
 _impl_.resource_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:RouterProtobufMessage.resource)
}
inline std::string* RouterProtobufMessage::mutable_resource() {
  std::string* _s = _internal_mutable_resource();
  // @@protoc_insertion_point(field_mutable:RouterProtobufMessage.resource)
  return _s;
}
inline const std::string& RouterProtobufMessage::_internal_resource() const {
  return _impl_.resource_.Get();
}
inline void RouterProtobufMessage::_internal_set_resource(const std::string& value) {
  
  _impl_.resource_.Set(value, GetArenaForAllocation());
}
inline std::string* RouterProtobufMessage::_internal_mutable_resource() {
  
  return _impl_.resource_.Mutable(GetArenaForAllocation());
}
inline std::string* RouterProtobufMessage::release_resource() {
  // @@protoc_insertion_point(field_release:RouterProtobufMessage.resource)
  return _impl_.resource_.Release();
}
inline void RouterProtobufMessage::set_allocated_resource(std::string* resource) {
  if (resource != nullptr) {
    
  } else {
    
  }
  _impl_.resource_.SetAllocated(resource, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.resource_.IsDefault()) {
    _impl_.resource_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:RouterProtobufMessage.resource)
}

// string dest = 3;
inline void RouterProtobufMessage::clear_dest() {
  _impl_.dest_.ClearToEmpty();
}
inline const std::string& RouterProtobufMessage::dest() const {
  // @@protoc_insertion_point(field_get:RouterProtobufMessage.dest)
  return _internal_dest();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void RouterProtobufMessage::set_dest(ArgT0&& arg0, ArgT... args) {
 
 _impl_.dest_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:RouterProtobufMessage.dest)
}
inline std::string* RouterProtobufMessage::mutable_dest() {
  std::string* _s = _internal_mutable_dest();
  // @@protoc_insertion_point(field_mutable:RouterProtobufMessage.dest)
  return _s;
}
inline const std::string& RouterProtobufMessage::_internal_dest() const {
  return _impl_.dest_.Get();
}
inline void RouterProtobufMessage::_internal_set_dest(const std::string& value) {
  
  _impl_.dest_.Set(value, GetArenaForAllocation());
}
inline std::string* RouterProtobufMessage::_internal_mutable_dest() {
  
  return _impl_.dest_.Mutable(GetArenaForAllocation());
}
inline std::string* RouterProtobufMessage::release_dest() {
  // @@protoc_insertion_point(field_release:RouterProtobufMessage.dest)
  return _impl_.dest_.Release();
}
inline void RouterProtobufMessage::set_allocated_dest(std::string* dest) {
  if (dest != nullptr) {
    
  } else {
    
  }
  _impl_.dest_.SetAllocated(dest, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.dest_.IsDefault()) {
    _impl_.dest_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:RouterProtobufMessage.dest)
}

// string data = 4;
inline void RouterProtobufMessage::clear_data() {
  _impl_.data_.ClearToEmpty();
}
inline const std::string& RouterProtobufMessage::data() const {
  // @@protoc_insertion_point(field_get:RouterProtobufMessage.data)
  return _internal_data();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void RouterProtobufMessage::set_data(ArgT0&& arg0, ArgT... args) {
 
 _impl_.data_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:RouterProtobufMessage.data)
}
inline std::string* RouterProtobufMessage::mutable_data() {
  std::string* _s = _internal_mutable_data();
  // @@protoc_insertion_point(field_mutable:RouterProtobufMessage.data)
  return _s;
}
inline const std::string& RouterProtobufMessage::_internal_data() const {
  return _impl_.data_.Get();
}
inline void RouterProtobufMessage::_internal_set_data(const std::string& value) {
  
  _impl_.data_.Set(value, GetArenaForAllocation());
}
inline std::string* RouterProtobufMessage::_internal_mutable_data() {
  
  return _impl_.data_.Mutable(GetArenaForAllocation());
}
inline std::string* RouterProtobufMessage::release_data() {
  // @@protoc_insertion_point(field_release:RouterProtobufMessage.data)
  return _impl_.data_.Release();
}
inline void RouterProtobufMessage::set_allocated_data(std::string* data) {
  if (data != nullptr) {
    
  } else {
    
  }
  _impl_.data_.SetAllocated(data, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.data_.IsDefault()) {
    _impl_.data_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:RouterProtobufMessage.data)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::RouterMethods> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::RouterMethods>() {
  return ::RouterMethods_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_protobufMessage_2eproto
