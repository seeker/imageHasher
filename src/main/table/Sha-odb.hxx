// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef SHA_ODB_HXX
#define SHA_ODB_HXX

#include <odb/version.hxx>

#if (ODB_VERSION != 20300UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "Sha.hpp"

#include <memory>
#include <cstddef>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#include <odb/container-traits.hxx>
#include <odb/no-op-cache-traits.hxx>
#include <odb/prepared-query.hxx>
#include <odb/result.hxx>
#include <odb/simple-object-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  // Sha
  //
  template <>
  struct class_traits< ::imageHasher::db::table::Sha >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::imageHasher::db::table::Sha >
  {
    public:
    typedef ::imageHasher::db::table::Sha object_type;
    typedef ::imageHasher::db::table::Sha* pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef int id_type;

    static const bool auto_id = true;

    static const bool abstract = false;

    static id_type
    id (const object_type&);

    typedef
    no_op_pointer_cache_traits<pointer_type>
    pointer_cache_traits;

    typedef
    no_op_reference_cache_traits<object_type>
    reference_cache_traits;

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);
  };
}

#include <odb/details/buffer.hxx>

#include <odb/sqlite/version.hxx>
#include <odb/sqlite/forward.hxx>
#include <odb/sqlite/binding.hxx>
#include <odb/sqlite/sqlite-types.hxx>
#include <odb/sqlite/query.hxx>

namespace odb
{
  // Sha
  //
  template <typename A>
  struct query_columns< ::imageHasher::db::table::Sha, id_sqlite, A >
  {
    // id
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        int,
        sqlite::id_integer >::query_type,
      sqlite::id_integer >
    id_type_;

    static const id_type_ id;

    // sha256
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    sha256_type_;

    static const sha256_type_ sha256;
  };

  template <typename A>
  const typename query_columns< ::imageHasher::db::table::Sha, id_sqlite, A >::id_type_
  query_columns< ::imageHasher::db::table::Sha, id_sqlite, A >::
  id (A::table_name, "\"id\"", 0);

  template <typename A>
  const typename query_columns< ::imageHasher::db::table::Sha, id_sqlite, A >::sha256_type_
  query_columns< ::imageHasher::db::table::Sha, id_sqlite, A >::
  sha256 (A::table_name, "\"sha256\"", 0);

  template <typename A>
  struct pointer_query_columns< ::imageHasher::db::table::Sha, id_sqlite, A >:
    query_columns< ::imageHasher::db::table::Sha, id_sqlite, A >
  {
  };

  template <>
  class access::object_traits_impl< ::imageHasher::db::table::Sha, id_sqlite >:
    public access::object_traits< ::imageHasher::db::table::Sha >
  {
    public:
    struct id_image_type
    {
      long long id_value;
      bool id_null;

      std::size_t version;
    };

    struct image_type
    {
      // id
      //
      long long id_value;
      bool id_null;

      // sha256
      //
      details::buffer sha256_value;
      std::size_t sha256_size;
      bool sha256_null;

      std::size_t version;
    };

    struct extra_statement_cache_type;

    using object_traits<object_type>::id;

    static id_type
    id (const image_type&);

    static bool
    grow (image_type&,
          bool*);

    static void
    bind (sqlite::bind*,
          image_type&,
          sqlite::statement_kind);

    static void
    bind (sqlite::bind*, id_image_type&);

    static bool
    init (image_type&,
          const object_type&,
          sqlite::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    static void
    init (id_image_type&, const id_type&);

    typedef sqlite::object_statements<object_type> statements_type;

    typedef sqlite::query_base query_base_type;

    static const std::size_t column_count = 2UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, object_type&);

    static pointer_type
    find (database&, const id_type&);

    static bool
    find (database&, const id_type&, object_type&);

    static bool
    reload (database&, object_type&);

    static void
    update (database&, const object_type&);

    static void
    erase (database&, const id_type&);

    static void
    erase (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    static odb::details::shared_ptr<prepared_query_impl>
    prepare_query (connection&, const char*, const query_base_type&);

    static odb::details::shared_ptr<result_impl>
    execute_query (prepared_query_impl&);

    public:
    static bool
    find_ (statements_type&,
           const id_type*);

    static void
    load_ (statements_type&,
           object_type&,
           bool reload);
  };

  template <>
  class access::object_traits_impl< ::imageHasher::db::table::Sha, id_common >:
    public access::object_traits_impl< ::imageHasher::db::table::Sha, id_sqlite >
  {
  };

  // Sha
  //
}

#include "Sha-odb.ixx"

#include <odb/post.hxx>

#endif // SHA_ODB_HXX
