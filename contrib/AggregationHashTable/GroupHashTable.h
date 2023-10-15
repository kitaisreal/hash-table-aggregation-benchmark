#pragma once

#include <cstring>

#include <cmath>
#include <stdexcept>
#include <exception>

#include <new>
#include <utility>
#include <memory>
#include <cassert>
#include <iostream>

#include <emmintrin.h>

#define ALWAYS_INLINE __attribute__((__always_inline__))
// #define DBMS_HASH_MAP_COUNT_COLLISIONS

// #define ALWAYS_INLINE

#if !defined(likely)
#    define likely(x)   (__builtin_expect(!!(x), 1))
#endif
#if !defined(unlikely)
#    define unlikely(x) (__builtin_expect(!!(x), 0))
#endif

namespace CH
{

/**
  * Returns the key. Can return the temporary key initially.
  * After the call to keyHolderPersistKey(), must return the persistent key.
  */
template <typename Key>
inline Key & ALWAYS_INLINE keyHolderGetKey(Key && key) { return key; }

/**
  * Make the key persistent. keyHolderGetKey() must return the persistent key
  * after this call.
  */
template <typename Key>
inline void ALWAYS_INLINE keyHolderPersistKey(Key &&) {}

/**
  * Discard the key. Calling keyHolderGetKey() is ill-defined after this.
  */
template <typename Key>
inline void ALWAYS_INLINE keyHolderDiscardKey(Key &&) {}

/** NOTE HashTable could only be used for memmoveable (position independent) types.
  * Example: std::string is not position independent in libstdc++ with C++11 ABI or in libc++.
  * Also, key in hash table must be of type, that zero bytes is compared equals to zero key.
  */


/** The state of the hash table that affects the properties of its cells.
  * Used as a template parameter.
  * For example, there is an implementation of an instantly clearable hash table - ClearableHashMap.
  * For it, each cell holds the version number, and in the hash table itself is the current version.
  *  When clearing, the current version simply increases; All cells with a mismatching version are considered empty.
  *  Another example: for an approximate calculation of the number of unique visitors, there is a hash table for UniquesHashSet.
  *  It has the concept of "degree". At each overflow, cells with keys that do not divide by the corresponding power of the two are deleted.
  */
struct GroupHashTableNoState
{
};


/// These functions can be overloaded for custom types.
namespace ZeroTraits
{

template <typename T>
bool check(const T x) { return x == T{}; }

template <typename T>
void set(T & x) { x = T{}; }

}


/** Numbers are compared bitwise.
  * Complex types are compared by operator== as usual (this is important if there are gaps).
  *
  * This is needed if you use floats as keys. They are compared by bit equality.
  * Otherwise the invariants in hash table probing do not met when NaNs are present.
  */
template <typename T>
inline bool bitEquals(T && a, T && b)
{
    using RealT = std::decay_t<T>;

    if constexpr (std::is_floating_point_v<RealT>)
        return 0 == memcmp(&a, &b, sizeof(RealT));  /// Note that memcmp with constant size is compiler builtin.
    else
        return a == b;
}


/**
  * getKey/Mapped -- methods to get key/"mapped" values from the LookupResult returned by find() and
  * emplace() methods of HashTable. Must not be called for a null LookupResult.
  *
  * We don't use iterators for lookup result. Instead, LookupResult is a pointer of some kind. There
  * are methods getKey/Mapped, that return references or values to key/"mapped" values.
  *
  * Different hash table implementations support this interface to a varying degree:
  *
  * 1) Hash tables that store neither the key in its original form, nor a "mapped" value:
  *    FixedHashTable or StringHashTable. Neither GetKey nor GetMapped are supported, the only valid
  *    operation is checking LookupResult for null.
  *
  * 2) Hash maps that do not store the key, e.g. FixedHashMap or StringHashMap. Only GetMapped is
  *    supported.
  *
  * 3) Hash tables that store the key and do not have a "mapped" value, e.g. the normal HashTable.
  *    GetKey returns the key, and GetMapped returns a zero void pointer. This simplifies generic
  *    code that works with mapped values: it can overload on the return type of GetMapped(), and
  *    doesn't need other parameters. One example is Cell::setMapped() function.
  *
  * 4) Hash tables that store both the key and the "mapped" value, e.g. HashMap. Both GetKey and
  *    GetMapped are supported.
  *
  * The implementation side goes as follows:
  *
  * for (1), LookupResult->getKey = const VoidKey, LookupResult->getMapped = VoidMapped;
  *
  * for (2), LookupResult->getKey = const VoidKey, LookupResult->getMapped = Mapped &;
  *
  * for (3) and (4), LookupResult->getKey = const Key [&], LookupResult->getMapped = Mapped &;
  * VoidKey and VoidMapped may have specialized function overloads for generic code.
  */

struct GroupVoidKey {};
struct GroupVoidMapped
{
    template <typename T>
    auto & operator=(const T &)
    {
        return *this;
    }
};

/** Compile-time interface for cell of the hash table.
  * Different cell types are used to implement different hash tables.
  * The cell must contain a key.
  * It can also contain a value and arbitrary additional data
  *  (example: the stored hash value; version number for ClearableHashMap).
  */
template <typename Key, typename Hash, typename TState = GroupHashTableNoState>
struct GroupHashTableCell
{
    using State = TState;

    using key_type = Key;
    using value_type = Key;
    using mapped_type = GroupVoidMapped;

    Key key;

    GroupHashTableCell() {} /// NOLINT

    /// Create a cell with the given key / key and value.
    GroupHashTableCell(const Key & key_, const State &) : key(key_) {}

    /// Get the key (externally).
    const Key & getKey() const { return key; }
    GroupVoidMapped getMapped() const { return {}; }
    const value_type & getValue() const { return key; }

    /// Get the key (internally).
    static const Key & getKey(const value_type & value) { return value; }

    /// Are the keys at the cells equal?
    bool keyEquals(const Key & key_) const { return bitEquals(key, key_); }
    bool keyEquals(const Key & key_, size_t /*hash_*/) const { return bitEquals(key, key_); }
    bool keyEquals(const Key & key_, size_t /*hash_*/, const State & /*state*/) const { return bitEquals(key, key_); }

    /// If the cell can remember the value of the hash function, then remember it.
    void setHash(size_t /*hash_value*/) {}

    /// If the cell can store the hash value in itself, then return the stored value.
    /// It must be at least once calculated before.
    /// If storing the hash value is not provided, then just compute the hash.
    size_t getHash(const Hash & hash) const { return hash(key); }

    /// Whether the key is zero. In the main buffer, cells with a zero key are considered empty.
    /// If zero keys can be inserted into the table, then the cell for the zero key is stored separately, not in the main buffer.
    /// Zero keys must be such that the zeroed-down piece of memory is a zero key.
    bool isZero(const State & state) const { return isZero(key, state); }
    static bool isZero(const Key & key, const State & /*state*/) { return ZeroTraits::check(key); }

    /// Set the key value to zero.
    void setZero() { ZeroTraits::set(key); }

    /// Do the hash table need to store the zero key separately (that is, can a zero key be inserted into the hash table).
    static constexpr bool need_zero_value_storage = true;

    /// Set the mapped value, if any (for HashMap), to the corresponding `value`.
    void setMapped(const value_type & /*value*/) {}

};


/** If you want to store the zero key separately - a place to store it. */
template <bool need_zero_value_storage, typename Cell>
struct GroupZeroValueStorage;

template <typename Cell>
struct GroupZeroValueStorage<true, Cell>
{
private:
    bool has_zero = false;
    std::aligned_storage_t<sizeof(Cell), alignof(Cell)> zero_value_storage; /// Storage of element with zero key.

public:
    bool hasZero() const { return has_zero; }

    void setHasZero()
    {
        has_zero = true;
        new (zeroValue()) Cell();
    }

    void clearHasZero()
    {
        has_zero = false;
        zeroValue()->~Cell();
    }

    void clearHasZeroFlag()
    {
        has_zero = false;
    }

    Cell * zeroValue()             { return std::launder(reinterpret_cast<Cell*>(&zero_value_storage)); }
    const Cell * zeroValue() const { return std::launder(reinterpret_cast<const Cell*>(&zero_value_storage)); }
};

template <typename Cell>
struct GroupZeroValueStorage<false, Cell>
{
    bool hasZero() const { return false; }
    void setHasZero() { throw std::logic_error("HashTable: logical error"); }
    void clearHasZero() {}
    void clearHasZeroFlag() {}

    Cell * zeroValue()             { return nullptr; }
    const Cell * zeroValue() const { return nullptr; }
};

template <size_t initial_groups_size_degree = 0>
struct GroupHashTableGrower
{
    /// The state of this structure is enough to get the buffer size of the hash table.

    uint8_t size_degree = initial_groups_size_degree;
    static constexpr auto initial_groups_count = 1ULL << initial_groups_size_degree;

    static constexpr size_t max_size_degree = 23;

    /// The size of the hash table in the cells.
    size_t bufSize() const               { return 1ULL << size_degree; }

    size_t maxFill() const               { return 1ULL << (size_degree - 1); }
    size_t mask() const                  { return bufSize() - 1; }

    /// From the hash value, get the cell number in the hash table.
    size_t place(size_t x) const         { return x & mask(); }

    /// The next cell in the collision resolution chain.
    size_t next(size_t pos) const        { ++pos; return pos & mask(); }

    /// Whether the hash table is sufficiently full. You need to increase the size of the hash table, or remove something unnecessary from it.
    bool overflow(size_t elems) const    {
        size_t max_available_elements = bufSize() * 16;
        size_t max_capacity = (max_available_elements * 3) / 4;
        // size_t max_capacity = max_available_elements / 2;
        return elems > max_capacity;
    }

    /// Increase the size of the hash table.
    void increaseSize()
    {
        size_degree += 1;
    }

    /// Set the buffer size by the number of elements in the hash table. Used when deserializing a hash table.
    // void set(size_t num_elements)
    // {
    //     if (num_elements <= 1)
    //         size_degree = initial_groups_count;
    //     else if (initial_groups_count * 16 > static_cast<size_t>(log2(num_elements - 1)) + 2)
    //         size_degree = initial_groups_count;
    //     else
    //         size_degree = static_cast<size_t>(log2(num_elements - 1)) + 2;
    // }

    // void setBufSize(size_t buf_size_)
    // {
    //     size_degree = static_cast<size_t>(log2(buf_size_ - 1) + 1);
    // }
};

// The HashTable
template <typename Key, typename Cell, typename Hash, typename Allocator>
class GroupHashTable : protected Hash,
                  protected Allocator,
                  protected Cell::State,
                  public GroupZeroValueStorage<Cell::need_zero_value_storage, Cell> /// empty base optimization
{
public:
    struct Group
    {
        uint8_t metadata[16];
        Cell cells[16];
    };

    using Grower = GroupHashTableGrower<>;

    // If we use an allocator with inline memory, check that the initial
    // size of the hash table is in sync with the amount of this memory.
    static constexpr size_t initial_buffer_bytes
        = Grower::initial_groups_count * sizeof(Group);

protected:
    using HashValue = size_t;
    using Self = GroupHashTable;

    size_t m_size = 0;        /// Amount of elements
    Group * buf;               /// A piece of memory for all groups
    Grower grower;

    // Cell * ALWAYS_INLINE findCellPrepareInsertSingleGroup(const Key & x, size_t hash_value) const
    // {
        // Group & group = buf[0];
        // Cell * cell = group.cells;
        // uint8_t h2 = (hash_value & 255) | 1UL;

        // while (!cell->isZero(*this) && !cell->keyEquals(x, hash_value, *this))
        //     ++cell;

        // group.metadata[cell - group.cells] = h2;

    //     return cell;
    // }

    /// Find a cell with the same key or an empty cell, starting from the specified position and further along the collision resolution chain.
    Cell * ALWAYS_INLINE findCellPrepareInsert(const Key & x, size_t hash_value) const
    {
        uint8_t h2 = (hash_value & 255) | 1UL;
        size_t h1 = hash_value >> 8;
        size_t group_place_value = grower.place(h1);

        while (true)
        {
            Group & group = buf[group_place_value];
            __m128i group_metadata = _mm_loadu_si128(reinterpret_cast<const __m128i *>(group.metadata));

            __m128i metadata_cmpeq_same_hash_vector = _mm_cmpeq_epi8(group_metadata, _mm_set1_epi8(h2));
            __m128i metadata_cmpeq_empty_vector = _mm_cmpeq_epi8(group_metadata, _mm_set1_epi8(0));

            uint16_t bitmask_to_check = _mm_movemask_epi8(_mm_or_si128(metadata_cmpeq_same_hash_vector, metadata_cmpeq_empty_vector));

            while (bitmask_to_check != 0)
            {
                uint8_t group_cell_index_to_check = __builtin_ctzs(bitmask_to_check);
                if (group.metadata[group_cell_index_to_check] == 0)
                {
                    group.metadata[group_cell_index_to_check] = h2;
                    return &group.cells[group_cell_index_to_check];
                }

                if (likely(group.cells[group_cell_index_to_check].keyEquals(x, hash_value, *this)))
                    return &group.cells[group_cell_index_to_check];

                bitmask_to_check &= bitmask_to_check - 1;
            }

            group_place_value = grower.next(group_place_value);
        }
    }

    Cell * ALWAYS_INLINE findCellPrepareInsertLinearProbing(const Key & x, size_t hash_value) const
    {
        size_t h1 = hash_value >> 8;
        size_t group_place_value = grower.place(h1);

        uint8_t h2 = (hash_value & 255) | 1UL;

        while (true)
        {
            Group & group = buf[group_place_value];

            for (size_t i = 0; i < 16; ++i)
            {
                if (group.cells[i].isZero(*this) || group.cells[i].keyEquals(x, hash_value, *this))
                {
                    group.metadata[i] = h2;
                    return &group.cells[i];
                }
            }

            group_place_value = grower.next(group_place_value);
        }
    }

    Cell * ALWAYS_INLINE findCell(const Key & x, size_t hash_value) const
    {
        size_t h1 = hash_value >> 8;
        size_t group_place_value = grower.place(h1);

        uint8_t h2 = (hash_value & 255) | 1UL;

        while (true)
        {
            Group & group = buf[group_place_value];
            __m128i group_metadata = _mm_loadu_si128(reinterpret_cast<const __m128i *>(group.metadata));

            __m128i metadata_cmpeq_same_hash_vector = _mm_cmpeq_epi8(group_metadata, _mm_set1_epi8(h2));
            uint16_t bitmask_to_check = _mm_movemask_epi8(metadata_cmpeq_same_hash_vector);

            while (bitmask_to_check != 0)
            {
                uint8_t group_cell_index_to_check = __builtin_ctzs(bitmask_to_check);
                if (likely(group.cells[group_cell_index_to_check].keyEquals(x, hash_value, *this)))
                    return &group.cells[group_cell_index_to_check];

                bitmask_to_check &= bitmask_to_check - 1;
            }

            group_place_value = grower.next(group_place_value);
        }
    }

    template <typename T>
    static inline bool mulOverflow(T x, T y, T & res)
    {
        return __builtin_mul_overflow(x, y, &res);
    }

    template <typename T, typename U, typename R>
    static inline bool mulOverflow(T x, U y, R & res)
    {
        return __builtin_mul_overflow(x, y, &res);
    }

    template <>
    static inline bool mulOverflow(int x, int y, int & res)
    {
        return __builtin_smul_overflow(x, y, &res);
    }

    template <>
    static inline bool mulOverflow(long x, long y, long & res)
    {
        return __builtin_smull_overflow(x, y, &res);
    }

    template <>
    static inline bool mulOverflow(long long x, long long y, long long & res)
    {
        return __builtin_smulll_overflow(x, y, &res);
    }

    static size_t allocCheckOverflow(size_t buffer_groups_size)
    {
        size_t size = 0;
        if (mulOverflow(buffer_groups_size, sizeof(Group), size))
            throw std::runtime_error("Integer overflow trying to allocate memory for HashTable");

        return size;
    }

    void alloc(const Grower & new_grower)
    {
        buf = reinterpret_cast<Group *>(Allocator::alloc(allocCheckOverflow(new_grower.bufSize())));
        grower = new_grower;
    }

    void free()
    {
        if (buf)
        {
            Allocator::free(buf, getBufferSizeInBytes());
            buf = nullptr;
        }
    }

    /// Increase the size of the buffer.
    void resize()
    {
        size_t old_size = grower.bufSize();
        size_t old_buffer_size = getBufferSizeInBytes();

        grower.increaseSize();

        /// Expand the space.

        buf = reinterpret_cast<Group *>(Allocator::realloc(buf, old_buffer_size, allocCheckOverflow(grower.bufSize())));

        /** Now some items may need to be moved to a new location.
          * The element can stay in place, or move to a new location "on the right",
          *  or move to the left of the collision resolution chain, because the elements to the left of it have been moved to the new "right" location.
          */
        size_t group_index = 0;
        for (; group_index < old_size; ++group_index)
        {
            Group & group = buf[group_index];

            for (size_t cell_index = 0; cell_index < 16; ++cell_index)
            {
                if (group.cells[cell_index].isZero(*this))
                    break;

                reinsert(group, cell_index, group.cells[cell_index].getHash(*this));
            }
        }

        /** There is also a special case:
          *    if the element was to be at the end of the old buffer,                  [        x]
          *    but is at the beginning because of the collision resolution chain,      [o       x]
          *    then after resizing, it will first be out of place again,               [        xo        ]
          *    and in order to transfer it where necessary,
          *    after transferring all the elements from the old halves you need to     [         o   x    ]
          *    process tail from the collision resolution chain immediately after it   [        o    x    ]
          */
        size_t new_size = grower.bufSize();
        for (; group_index < new_size; ++group_index)
        {
            Group & group = buf[group_index];

            for (size_t cell_index = 0; cell_index < 16; ++cell_index)
            {
                if (group.cells[cell_index].isZero(*this))
                    return;

                reinsert(group, cell_index, group.cells[cell_index].getHash(*this));
            }
        }
    }


    /** Paste into the new buffer the value that was in the old buffer.
      * Used when increasing the buffer size.
      */
    void reinsert(Group & group, size_t cell_index, size_t hash_value)
    {
        /// Compute a new location, taking into account the collision resolution chain.
        Cell * reinserted_cell = findCellPrepareInsert(Cell::getKey(group.cells[cell_index].getValue()), hash_value);

        /// If the item remains in its place in the old collision resolution chain.
        if (&group.cells[cell_index] == reinserted_cell)
            return;

        /// Copy to a new location and zero the old one.
        reinserted_cell->setHash(hash_value);
        memcpy(static_cast<void*>(reinserted_cell), &group.cells[cell_index], sizeof(group.cells[cell_index]));

        group.cells[cell_index].setZero();
        group.metadata[cell_index] = 0;
    }

public:
    using key_type = Key;
    using grower_type = Grower;
    using mapped_type = typename Cell::mapped_type;
    using value_type = typename Cell::value_type;
    using cell_type = Cell;

    using LookupResult = Cell *;
    using ConstLookupResult = const Cell *;

    size_t hash(const Key & x) const { return Hash::operator()(x); }

    GroupHashTable()
    {
        if (Cell::need_zero_value_storage)
            this->zeroValue()->setZero();

        alloc(grower);
    }

    GroupHashTable(const GroupHashTable &) = delete;
    GroupHashTable& operator=(const GroupHashTable &) = delete;
    GroupHashTable(const GroupHashTable &&) = delete;
    GroupHashTable& operator=(const GroupHashTable &&) = delete;

    ~GroupHashTable()
    {
        this->clearHasZero();
        free();
    }

    void dump(std::ostream & stream) {
        stream << "Size " << m_size << ' ';
        stream << "Groups size " << grower.bufSize() << '\n';

        for (size_t i = 0; i < grower.bufSize(); ++i) {
            stream << "Group " << i << '\n';
            Group & group = buf[i];

            stream << "Metadata values ";
            for (size_t j = 0; j < 16; ++j) {
                stream << static_cast<uint16_t>(group.metadata[j]) << ' ';
            }
            stream << '\n';

            stream << "Cells keys values ";
            for (size_t j = 0; j < 16; ++j) {
                stream << group.cells[j].getKey() << ' ';
            }
            stream << '\n';
        }
    }

protected:
    /// If the key is zero, insert it into a special place and return true.
    /// We don't have to persist a zero key, because it's not actually inserted.
    /// That's why we just take a Key by value, an not a key holder.
    bool ALWAYS_INLINE emplaceIfZero(const Key & x, LookupResult & it, bool & inserted, size_t hash_value)
    {
        /// If it is claimed that the zero key can not be inserted into the table.
        if constexpr (!Cell::need_zero_value_storage)
            return false;

        if (unlikely(Cell::isZero(x, *this)))
        {
            it = this->zeroValue();

            if (!this->hasZero())
            {
                ++m_size;
                this->setHasZero();
                this->zeroValue()->setHash(hash_value);
                inserted = true;
            }
            else
                inserted = false;

            return true;
        }

        return false;
    }

    /// Only for non-zero keys. Find the right place, insert the key there, if it does not already exist. Set iterator to the cell in output parameter.
    template <typename KeyHolder>
    void ALWAYS_INLINE emplaceNonZero(KeyHolder && key_holder, LookupResult & it,
                                      bool & inserted, size_t hash_value)
    {
        if (unlikely(grower.overflow(m_size)))
            resize();

        const auto & key = keyHolderGetKey(key_holder);
        Cell * cell = nullptr;

        if (grower.bufSize() <= 8)
            cell = findCellPrepareInsert(key, hash_value);
        else
            cell = findCellPrepareInsert(key, hash_value);

        it = cell;

        if (!cell->isZero(*this))
        {
            keyHolderDiscardKey(key_holder);
            inserted = false;
            return;
        }

        keyHolderPersistKey(key_holder);

        new (cell) Cell(key, *this);
        cell->setHash(hash_value);
        inserted = true;
        ++m_size;
    }

public:
    /** Insert the key.
      * Return values:
      * 'it' -- a LookupResult pointing to the corresponding key/mapped pair.
      * 'inserted' -- whether a new key was inserted.
      *
      * You have to make `placement new` of value if you inserted a new key,
      * since when destroying a hash table, it will call the destructor!
      *
      * Example usage:
      *
      * Map::LookupResult it;
      * bool inserted;
      * map.emplace(key, it, inserted);
      * if (inserted)
      *     new (&it->getMapped()) Mapped(value);
      */
    template <typename KeyHolder>
    void ALWAYS_INLINE emplace(KeyHolder && key_holder, LookupResult & it, bool & inserted)
    {
        const auto & key = keyHolderGetKey(key_holder);
        emplace(key_holder, it, inserted, hash(key));
    }

    template <typename KeyHolder>
    void ALWAYS_INLINE emplace(KeyHolder && key_holder, LookupResult & it,
                                  bool & inserted, size_t hash_value)
    {
        const auto & key = keyHolderGetKey(key_holder);

        if (!emplaceIfZero(key, it, inserted, hash_value))
            emplaceNonZero(key_holder, it, inserted, hash_value);
    }

    std::pair<LookupResult, bool> ALWAYS_INLINE insert(const value_type & x)
    {
        std::pair<LookupResult, bool> res;
        emplace(Cell::getKey(x), res.first, res.second);
        if (res.second)
            res.first->setMapped(x);

        return res;
    }

    LookupResult ALWAYS_INLINE find(const Key & x, size_t hash_value)
    {
        if (Cell::isZero(x, *this))
            return this->hasZero() ? this->zeroValue() : nullptr;

        Cell * cell = findCell(x, hash_value);
        return !cell->isZero(*this) ? cell : nullptr;
    }

    ConstLookupResult ALWAYS_INLINE find(const Key & x, size_t hash_value) const
    {
        return const_cast<std::decay_t<decltype(*this)> *>(this)->find(x, hash_value);
    }

    LookupResult ALWAYS_INLINE find(const Key & x)
    {
        size_t hash_value = hash(x);
        return find(x, hash_value);
    }

    LookupResult ALWAYS_INLINE find(const Key & x) const
    {
        size_t hash_value = hash(x);
        return find(x, hash_value);
    }

    std::pair<LookupResult, bool> insert(std::pair<Key, typename Cell::Mapped> value)
    {
        return insert(value_type(value.first, value.second));
    }

    typename Cell::Mapped & ALWAYS_INLINE operator[](const Key & x)
    {
        LookupResult it;
        bool inserted;
        this->emplace(x, it, inserted);

        /** It may seem that initialization is not necessary for POD-types (or __has_trivial_constructor),
          *  since the hash table memory is initially initialized with zeros.
          * But, in fact, an empty cell may not be initialized with zeros in the following cases:
          * - ZeroValueStorage (it only zeros the key);
          * - after resizing and moving a part of the cells to the new half of the hash table, the old cells also have only the key to zero.
          *
          * On performance, there is almost always no difference, due to the fact that it->second is usually assigned immediately
          *  after calling `operator[]`, and since `operator[]` is inlined, the compiler removes unnecessary initialization.
          *
          * Sometimes due to initialization, the performance even grows. This occurs in code like `++map[key]`.
          * When we do the initialization, for new cells, it's enough to make `store 1` right away.
          * And if we did not initialize, then even though there was zero in the cell,
          *  the compiler can not guess about this, and generates the `load`, `increment`, `store` code.
          */
        if (inserted)
            new (&it->getMapped()) typename Cell::Mapped();

        return it->getMapped();
    }

    size_t getBufferSizeInBytes() const
    {
        return grower.bufSize() * sizeof(Group);
    }

    size_t size() const
    {
        return m_size;
    }

    bool empty() const
    {
        return m_size == 0;
    }
};


struct GroupNoInitTag
{
};

/// A pair that does not initialize the elements, if not needed.
template <typename First, typename Second>
struct GroupPairNoInit
{
    First first;
    Second second;

    GroupPairNoInit() {} /// NOLINT

    template <typename FirstValue>
    GroupPairNoInit(FirstValue && first_, GroupNoInitTag)
        : first(std::forward<FirstValue>(first_))
    {
    }

    template <typename FirstValue, typename SecondValue>
    GroupPairNoInit(FirstValue && first_, SecondValue && second_)
        : first(std::forward<FirstValue>(first_))
        , second(std::forward<SecondValue>(second_))
    {
    }
};

template <typename First, typename Second>
GroupPairNoInit<std::decay_t<First>, std::decay_t<Second>> makeGroupPairNoInit(First && first, Second && second)
{
    return PairNoInit<std::decay_t<First>, std::decay_t<Second>>(std::forward<First>(first), std::forward<Second>(second));
}


template <typename Key, typename TMapped, typename Hash, typename TState = GroupHashTableNoState, typename Pair = GroupPairNoInit<Key, TMapped>>
struct GroupHashMapCell
{
    using Mapped = TMapped;
    using State = TState;

    using value_type = Pair;
    using mapped_type = Mapped;
    using key_type = Key;

    value_type value;

    GroupHashMapCell() = default;
    GroupHashMapCell(const Key & key_, const State &) : value(key_, GroupNoInitTag()) {}
    GroupHashMapCell(const value_type & value_, const State &) : value(value_) {}

    /// Get the key (externally).
    const Key & getKey() const { return value.first; }
    Mapped & getMapped() { return value.second; }
    const Mapped & getMapped() const { return value.second; }
    const value_type & getValue() const { return value; }

    /// Get the key (internally).
    static const Key & getKey(const value_type & value) { return value.first; }

    bool keyEquals(const Key & key_) const { return bitEquals(value.first, key_); }
    bool keyEquals(const Key & key_, size_t /*hash_*/) const { return bitEquals(value.first, key_); }
    bool keyEquals(const Key & key_, size_t /*hash_*/, const State & /*state*/) const { return bitEquals(value.first, key_); }

    void setHash(size_t /*hash_value*/) {}
    size_t getHash(const Hash & hash) const { return hash(value.first); }

    bool isZero(const State & state) const { return isZero(value.first, state); }
    static bool isZero(const Key & key, const State & /*state*/) { return ZeroTraits::check(key); }

    /// Set the key value to zero.
    void setZero() { ZeroTraits::set(value.first); }

    /// Do I need to store the zero key separately (that is, can a zero key be inserted into the hash table).
    static constexpr bool need_zero_value_storage = true;

    void setMapped(const value_type & value_) { value.second = value_.second; }

    /// Serialization, in binary and text form.
    // void write(DB::WriteBuffer & wb) const
    // {
    //     DB::writeBinary(value.first, wb);
    //     DB::writeBinary(value.second, wb);
    // }

    // void writeText(DB::WriteBuffer & wb) const
    // {
    //     DB::writeDoubleQuoted(value.first, wb);
    //     DB::writeChar(',', wb);
    //     DB::writeDoubleQuoted(value.second, wb);
    // }

    /// Deserialization, in binary and text form.
    // void read(DB::ReadBuffer & rb)
    // {
    //     DB::readBinary(value.first, rb);
    //     DB::readBinary(value.second, rb);
    // }

    // void readText(DB::ReadBuffer & rb)
    // {
    //     DB::readDoubleQuoted(value.first, rb);
    //     DB::assertChar(',', rb);
    //     DB::readDoubleQuoted(value.second, rb);
    // }

    template <size_t I>
    auto & get() & {
        if constexpr (I == 0) return value.first;
        else if constexpr (I == 1) return value.second;
    }

    template <size_t I>
    auto const & get() const & {
        if constexpr (I == 0) return value.first;
        else if constexpr (I == 1) return value.second;
    }

    template <size_t I>
    auto && get() && {
        if constexpr (I == 0) return std::move(value.first);
        else if constexpr (I == 1) return std::move(value.second);
    }

};

template <
    typename Key,
    typename Mapped,
    typename Hash,
    typename Allocator>
using GroupHashMap = GroupHashTable<Key, GroupHashMapCell<Key, Mapped, Hash>, Hash, Allocator>;

}

namespace std
{

    template <typename Key, typename TMapped, typename Hash, typename TState, typename Pair>
    struct tuple_size<CH::GroupHashMapCell<Key, TMapped, Hash, TState, Pair>> : std::integral_constant<size_t, 2> { };

    template <typename Key, typename TMapped, typename Hash, typename TState, typename Pair>
    struct tuple_element<0, CH::GroupHashMapCell<Key, TMapped, Hash, TState, Pair>> { using type = Key; };

    template <typename Key, typename TMapped, typename Hash, typename TState, typename Pair>
    struct tuple_element<1, CH::GroupHashMapCell<Key, TMapped, Hash, TState, Pair>> { using type = TMapped; };
}
