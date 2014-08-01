// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef SETTINGS_ODB_HXX
#define SETTINGS_ODB_HXX

#include <odb/version.hxx>

#if (ODB_VERSION != 20300UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "Settings.hpp"

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
  // Settings
  //
  template <>
  struct class_traits< ::db::table::Settings >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::db::table::Settings >
  {
    public:
    typedef ::db::table::Settings object_type;
    typedef ::db::table::Settings* pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef ::std::string id_type;

    static const bool auto_id = false;

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
  // Settings
  //
  template <typename A>
  struct query_columns< ::db::table::Settings, id_sqlite, A >
  {
    // id
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    id_type_;

    static const id_type_ id;
  };

  template <typename A>
  const typename query_columns< ::db::table::Settings, id_sqlite, A >::id_type_
  query_columns< ::db::table::Settings, id_sqlite, A >::
  id (A::table_name, "\"id\"", 0);

  template <typename A>
  struct pointer_query_columns< ::db::table::Settings, id_sqlite, A >:
    query_columns< ::db::table::Settings, id_sqlite, A >
  {
  };

  template <>
  class access::object_traits_impl< ::db::table::Settings, id_sqlite >:
    public access::object_traits< ::db::table::Settings >
  {
    public:
    struct id_image_type
    {
      details::buffer id_value;
      std::size_t id_size;
      bool id_null;

      std::size_t version;
    };

    struct image_type
    {
      // id
      //
      details::buffer id_value;
      std::size_t id_size;
      bool id_null;

      std::size_t version;
    };

    struct extra_statement_cache_type;

    // settings
    //
    struct settings_traits
    {
      static const std::size_t id_column_count = 1UL;
      static const std::size_t data_column_count = 3UL;

      static const bool versioned = false;

      static const char insert_statement[];
      static const char select_statement[];
      static const char delete_statement[];

      typedef ::std::map< ::std::basic_string< char >, ::std::basic_string< char > > container_type;
      typedef
      odb::access::container_traits<container_type>
      container_traits_type;
      typedef container_traits_type::key_type key_type;
      typedef container_traits_type::value_type value_type;

      typedef map_functions<key_type, value_type> functions_type;
      typedef sqlite::container_statements< settings_traits > statements_type;

      struct data_image_type
      {
        // key
        //
        details::buffer key_value;
        std::size_t key_size;
        bool key_null;

        // value
        //
        details::buffer value_value;
        std::size_t value_size;
        bool value_null;

        std::size_t version;
      };

      static void
      bind (sqlite::bind*,
            const sqlite::bind* id,
            std::size_t id_size,
            data_image_type&);

      static void
      grow (data_image_type&,
            bool*);

      static void
      init (data_image_type&,
            const key_type*,
            const value_type&);

      static void
      init (key_type&,
            value_type&,
            const data_image_type&,
            database*);

      static void
      insert (const key_type&, const value_type&, void*);

      static bool
      select (key_type&, value_type&, void*);

      static void
      delete_ (void*);

      static void
      persist (const container_type&,
               statements_type&);

      static void
      load (container_type&,
            statements_type&);

      static void
      update (const container_type&,
              statements_type&);

      static void
      erase (statements_type&);
    };

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

    static const std::size_t column_count = 1UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char find_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

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
  class access::object_traits_impl< ::db::table::Settings, id_common >:
    public access::object_traits_impl< ::db::table::Settings, id_sqlite >
  {
  };

  // Settings
  //
}

#include "Settings-odb.ixx"

#include <odb/post.hxx>

#endif // SETTINGS_ODB_HXX
