// Copyright (c) 2013, Facebook, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.

#ifndef STORAGE_LEVELDB_INCLUDE_STATISTICS_H_
#define STORAGE_LEVELDB_INCLUDE_STATISTICS_H_

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>

namespace leveldb {

/**
 * Keep adding ticker's here.
 *  1. Any ticker should be added before TICKER_ENUM_MAX.
 *  2. Add a readable string in TickersNameMap below for the newly added ticker.
 */
enum Tickers : uint32_t {
  // total block cache misses
  // REQUIRES: BLOCK_CACHE_MISS == BLOCK_CACHE_INDEX_MISS +
  //                               BLOCK_CACHE_FILTER_MISS +
  //                               BLOCK_CACHE_DATA_MISS;
  //BLOCK_CACHE_MISS = 0,
  // total block cache hit
  // REQUIRES: BLOCK_CACHE_HIT == BLOCK_CACHE_INDEX_HIT +
  //                              BLOCK_CACHE_FILTER_HIT +
  //                              BLOCK_CACHE_DATA_HIT;
  //BLOCK_CACHE_HIT,
  // # of blocks added to block cache.
  //BLOCK_CACHE_ADD,
  // # of times cache miss when accessing index block from block cache.
  //BLOCK_CACHE_INDEX_MISS,
  // # of times cache hit when accessing index block from block cache.
  //BLOCK_CACHE_INDEX_HIT,
  // # of times cache miss when accessing filter block from block cache.
  //BLOCK_CACHE_FILTER_MISS,
  // # of times cache hit when accessing filter block from block cache.
  //BLOCK_CACHE_FILTER_HIT,
  // # of times cache miss when accessing data block from block cache.
  //BLOCK_CACHE_DATA_MISS,
  // # of times cache hit when accessing data block from block cache.
  //BLOCK_CACHE_DATA_HIT,
  // # of times bloom filter has avoided file reads.
  //BLOOM_FILTER_USEFUL,

  // Table cache hit/miss rates
  TABLE_CACHE_HIT,
  TABLE_CACHE_MISS,

  // # of memtable hits.
  MEMTABLE_HIT,
  // # of memtable misses.
  MEMTABLE_MISS,

  /**
   * COMPACTION_KEY_DROP_* count the reasons for key drop during compaction
   * There are 3 reasons currently.
   */
  //COMPACTION_KEY_DROP_NEWER_ENTRY,  // key was written with a newer value.
  //COMPACTION_KEY_DROP_OBSOLETE,     // The key is obsolete.
  //COMPACTION_KEY_DROP_USER,  // user compaction function has dropped the key.

  // Number of keys written to the database via the Put and Write call's
  NUMBER_KEYS_WRITTEN,
  // Number of Keys read,
  NUMBER_KEYS_READ,
  // Number keys updated, if inplace update is enabled
  NUMBER_KEYS_UPDATED,
  // Bytes written / read
  BYTES_WRITTEN,
  BYTES_READ,
  NO_FILE_CLOSES,
  NO_FILE_OPENS,
  NO_FILE_ERRORS,
  // Time system had to wait to do LO-L1 compactions
  //STALL_L0_SLOWDOWN_MICROS,
  // Time system had to wait to move memtable to L1.
  //STALL_MEMTABLE_COMPACTION_MICROS,
  // write throttle because of too many files in L0
  //STALL_L0_NUM_FILES_MICROS,
  //RATE_LIMIT_DELAY_MILLIS,
  //NO_ITERATORS,  // number of iterators currently open

  // Number of MultiGet calls, keys read, and bytes read
  //NUMBER_MULTIGET_CALLS,
  //NUMBER_MULTIGET_KEYS_READ,
  //NUMBER_MULTIGET_BYTES_READ,

  // Number of deletes records that were not required to be
  // written to storage because key does not exist
  //NUMBER_FILTERED_DELETES,
  //NUMBER_MERGE_FAILURES,
  //SEQUENCE_NUMBER,

  // number of times bloom was checked before creating iterator on a
  // file, and the number of times the check was useful in avoiding
  // iterator creation (and thus likely IOPs).
  //BLOOM_FILTER_PREFIX_CHECKED,
  //BLOOM_FILTER_PREFIX_USEFUL,

  // Number of times we had to reseek inside an iteration to skip
  // over large number of keys with same userkey.
  //NUMBER_OF_RESEEKS_IN_ITERATION,

  // Record the number of calls to GetUpadtesSince. Useful to keep track of
  // transaction log iterator refreshes
  //GET_UPDATES_SINCE_CALLS,
  //BLOCK_CACHE_COMPRESSED_MISS,  // miss in the compressed block cache
  //BLOCK_CACHE_COMPRESSED_HIT,   // hit in the compressed block cache
  //WAL_FILE_SYNCED,              // Number of times WAL sync is done
  //WAL_FILE_BYTES,               // Number of bytes written to WAL

  // Writes can be processed by requesting thread or by the thread at the
  // head of the writers queue.
  //WRITE_DONE_BY_SELF,
  //WRITE_DONE_BY_OTHER,
  //WRITE_TIMEDOUT,       // Number of writes ending up with timed-out.
  //WRITE_WITH_WAL,       // Number of Write calls that request WAL
  //COMPACT_READ_BYTES,   // Bytes read during compaction
  //COMPACT_WRITE_BYTES,  // Bytes written during compaction
  //FLUSH_WRITE_BYTES,    // Bytes written during flush

  // Number of table's properties loaded directly from file, without creating
  // table reader object.
  //NUMBER_DIRECT_LOAD_TABLE_PROPERTIES,
  //NUMBER_SUPERVERSION_ACQUIRES,
  //NUMBER_SUPERVERSION_RELEASES,
  //NUMBER_SUPERVERSION_CLEANUPS,
  //NUMBER_BLOCK_NOT_COMPRESSED,
  LEVEL_0_HIT,
  LEVEL_1_HIT,
  LEVEL_2_HIT,
  LEVEL_3_HIT,
  LEVEL_4_HIT,
  LEVEL_5_HIT,
  LEVEL_6_HIT,
  LEVEL_7_HIT,
  NUM_THROTTLED_WRITES,
  NUM_MEMTABLE_WAIT_WRITES,
  NUM_STALLED_WRITES,
  NUM_COMPACTIONS,
  NUM_READ_COMPACTIONS,
  NUM_WRITE_COMPACTIONS,
  SSD_CACHE_HITS,
  SSD_CACHE_MISSES,
  TICKER_ENUM_MAX
};

// The order of items listed in  Tickers should be the same as
// the order listed in TickersNameMap
const std::vector<std::pair<Tickers, std::string>> TickersNameMap = {
    //{BLOCK_CACHE_MISS, "leveldb.block.cache.miss"},
    //{BLOCK_CACHE_HIT, "leveldb.block.cache.hit"},
    //{BLOCK_CACHE_ADD, "leveldb.block.cache.add"},
    //{BLOCK_CACHE_INDEX_MISS, "leveldb.block.cache.index.miss"},
    //{BLOCK_CACHE_INDEX_HIT, "leveldb.block.cache.index.hit"},
    //{BLOCK_CACHE_FILTER_MISS, "leveldb.block.cache.filter.miss"},
    //{BLOCK_CACHE_FILTER_HIT, "leveldb.block.cache.filter.hit"},
    //{BLOCK_CACHE_DATA_MISS, "leveldb.block.cache.data.miss"},
    //{BLOCK_CACHE_DATA_HIT, "leveldb.block.cache.data.hit"},
    //{BLOOM_FILTER_USEFUL, "leveldb.bloom.filter.useful"},
    {TABLE_CACHE_HIT, "leveldb.tablecache.hit"},
    {TABLE_CACHE_MISS, "leveldb.tablecache.miss"},
    {MEMTABLE_HIT, "leveldb.memtable.hit"},
    {MEMTABLE_MISS, "leveldb.memtable.miss"},
    //{COMPACTION_KEY_DROP_NEWER_ENTRY, "leveldb.compaction.key.drop.new"},
    //{COMPACTION_KEY_DROP_OBSOLETE, "leveldb.compaction.key.drop.obsolete"},
    //{COMPACTION_KEY_DROP_USER, "leveldb.compaction.key.drop.user"},
    {NUMBER_KEYS_WRITTEN, "leveldb.number.keys.written"},
    {NUMBER_KEYS_READ, "leveldb.number.keys.read"},
    {NUMBER_KEYS_UPDATED, "leveldb.number.keys.updated"},
    {BYTES_WRITTEN, "leveldb.bytes.written"},
    {BYTES_READ, "leveldb.bytes.read"},
    {NO_FILE_CLOSES, "leveldb.no.file.closes"},
    {NO_FILE_OPENS, "leveldb.no.file.opens"},
    {NO_FILE_ERRORS, "leveldb.no.file.errors"},
    //{STALL_L0_SLOWDOWN_MICROS, "leveldb.l0.slowdown.micros"},
    //{STALL_MEMTABLE_COMPACTION_MICROS, "leveldb.memtable.compaction.micros"},
    //{STALL_L0_NUM_FILES_MICROS, "leveldb.l0.num.files.stall.micros"},
    //{RATE_LIMIT_DELAY_MILLIS, "leveldb.rate.limit.delay.millis"},
    //{NO_ITERATORS, "leveldb.num.iterators"},
    //{NUMBER_MULTIGET_CALLS, "leveldb.number.multiget.get"},
    //{NUMBER_MULTIGET_KEYS_READ, "leveldb.number.multiget.keys.read"},
    //{NUMBER_MULTIGET_BYTES_READ, "leveldb.number.multiget.bytes.read"},
    //{NUMBER_FILTERED_DELETES, "leveldb.number.deletes.filtered"},
    //{NUMBER_MERGE_FAILURES, "leveldb.number.merge.failures"},
    //{SEQUENCE_NUMBER, "leveldb.sequence.number"},
    //{BLOOM_FILTER_PREFIX_CHECKED, "leveldb.bloom.filter.prefix.checked"},
    //{BLOOM_FILTER_PREFIX_USEFUL, "leveldb.bloom.filter.prefix.useful"},
    //{NUMBER_OF_RESEEKS_IN_ITERATION, "leveldb.number.reseeks.iteration"},
    //{GET_UPDATES_SINCE_CALLS, "leveldb.getupdatessince.calls"},
    //{BLOCK_CACHE_COMPRESSED_MISS, "leveldb.block.cachecompressed.miss"},
    //{BLOCK_CACHE_COMPRESSED_HIT, "leveldb.block.cachecompressed.hit"},
    //{WAL_FILE_SYNCED, "leveldb.wal.synced"},
    //{WAL_FILE_BYTES, "leveldb.wal.bytes"},
    //{WRITE_DONE_BY_SELF, "leveldb.write.self"},
    //{WRITE_DONE_BY_OTHER, "leveldb.write.other"},
    //{WRITE_TIMEDOUT, "leveldb.write.timedout"},
    //{WRITE_WITH_WAL, "leveldb.write.wal"},
    //{FLUSH_WRITE_BYTES, "leveldb.flush.write.bytes"},
    //{COMPACT_READ_BYTES, "leveldb.compact.read.bytes"},
    //{COMPACT_WRITE_BYTES, "leveldb.compact.write.bytes"},
    //{NUMBER_DIRECT_LOAD_TABLE_PROPERTIES,
    // "leveldb.number.direct.load.table.properties"},
    //{NUMBER_SUPERVERSION_ACQUIRES, "leveldb.number.superversion_acquires"},
    //{NUMBER_SUPERVERSION_RELEASES, "leveldb.number.superversion_releases"},
    //{NUMBER_SUPERVERSION_CLEANUPS, "leveldb.number.superversion_cleanups"},
    //{NUMBER_BLOCK_NOT_COMPRESSED, "leveldb.number.block.not_compressed"},
    {LEVEL_0_HIT, "leveldb.level-0.hits"},
    {LEVEL_1_HIT, "leveldb.level-1.hits"},
    {LEVEL_2_HIT, "leveldb.level-2.hits"},
    {LEVEL_3_HIT, "leveldb.level-3.hits"},
    {LEVEL_4_HIT, "leveldb.level-4.hits"},
    {LEVEL_5_HIT, "leveldb.level-5.hits"},
    {LEVEL_6_HIT, "leveldb.level-6.hits"},
    {LEVEL_7_HIT, "leveldb.level-7.hits"},
    {NUM_THROTTLED_WRITES, "leveldb.no.throttled.writes"},
    {NUM_MEMTABLE_WAIT_WRITES, "leveldb.no.memtable-wait.writes"},
    {NUM_STALLED_WRITES, "leveldb.no.stalled.writes"},
    {NUM_COMPACTIONS, "leveldb.num.compactions"},
    {NUM_READ_COMPACTIONS, "leveldb.num.read.compactions"},
    {NUM_WRITE_COMPACTIONS, "leveldb.num.write.compactions"},
    {SSD_CACHE_HITS, "leveldb.num.ssd.cache.hits"},
    {SSD_CACHE_MISSES, "leveldb.num.ssd.cache.misses"},
};

/**
 * Keep adding histogram's here.
 * Any histogram whould have value less than HISTOGRAM_ENUM_MAX
 * Add a new Histogram by assigning it the current value of HISTOGRAM_ENUM_MAX
 * Add a string representation in HistogramsNameMap below
 * And increment HISTOGRAM_ENUM_MAX
 */
enum Histograms : uint32_t {
  DB_GET = 0,
  DB_WRITE,
  //COMPACTION_TIME,
  TABLE_SYNC_MICROS,
  COMPACTION_OUTFILE_SYNC_MICROS,
  //WAL_FILE_SYNC_MICROS,
  //MANIFEST_FILE_SYNC_MICROS,
  // TIME SPENT IN IO DURING TABLE OPEN
  READ_TABLE_FOOTER_MICROS,
  READ_TABLE_INDEX_MICROS,
  READ_TABLE_META_MICROS,
  TABLE_OPEN_IO_MICROS,
  //DB_MULTIGET,
  ///READ_BLOCK_COMPACTION_MICROS,
  READ_BLOCK_GET_MICROS,
  //WRITE_RAW_BLOCK_MICROS,
  //STALL_L0_SLOWDOWN_COUNT,
  //STALL_MEMTABLE_COMPACTION_COUNT,
  //STALL_L0_NUM_FILES_COUNT,
  //HARD_RATE_LIMIT_DELAY_COUNT,
  //SOFT_RATE_LIMIT_DELAY_COUNT,
  NUM_FILES_IN_SINGLE_COMPACTION,
  //DB_SEEK,
  //WRITE_STALL,
  MEMTABLE_WAIT_MICROS,
  STALLED_WRITE_MICROS,
  MEMTABLE_INSERT_MICROS,
  WAL_APPEND_MICROS,
  FILES_PROBED_PER_READ,
  NUM_LEVELS_PROBED_PER_READ,
  MEMTABLE_FLUSH_MICROS,
  SSD_CACHE_INSERT_MICROS,
  SSD_CACHE_CHECK_KEY_MICROS,
  SSD_CACHE_LOOKUP_MICROS,
  SSD_CACHE_INSERT_ON_MISS_MICROS,
  BUILD_BATCH_GROUP_MICROS,
  TABLE_CACHE_GET_MICROS,
  VERSION_SET_GET_MICROS,
  MEMTABLE_GET_MICROS,
  IMM_MEMTABLE_GET_MICROS,
  MAYBE_SCHEDULE_COMPACTION_MICROS,
  GET_REF_STUFF_MICROS,
  GET_UNREF_STUFF_MICROS,
  GET_UPDATE_STATS_MICROS,
  GET_UNLOCK_MICROS,
  GET_LOCK_MICROS,
  HISTOGRAM_ENUM_MAX,
};

const std::vector<std::pair<Histograms, std::string>> HistogramsNameMap = {
  { DB_GET, "leveldb.db.get.micros" },
  { DB_WRITE, "leveldb.db.write.micros" },
  //{ COMPACTION_TIME, "leveldb.compaction.times.micros" },
  { TABLE_SYNC_MICROS, "leveldb.table.sync.micros" },
  { COMPACTION_OUTFILE_SYNC_MICROS, "leveldb.compaction.outfile.sync.micros" },
  //{ WAL_FILE_SYNC_MICROS, "leveldb.wal.file.sync.micros" },
  //{ MANIFEST_FILE_SYNC_MICROS, "leveldb.manifest.file.sync.micros" },
  { READ_TABLE_FOOTER_MICROS, "leveldb.read.table.footer.micros" },
  { READ_TABLE_INDEX_MICROS, "leveldb.read.table.index.micros" },
  { READ_TABLE_META_MICROS, "leveldb.read.table.meta.micros" },
  { TABLE_OPEN_IO_MICROS, "leveldb.table.open.io.micros" },
  //{ DB_MULTIGET, "leveldb.db.multiget.micros" },
  //{ READ_BLOCK_COMPACTION_MICROS, "leveldb.read.block.compaction.micros" },
  { READ_BLOCK_GET_MICROS, "leveldb.read.block.get.micros" },
  //{ WRITE_RAW_BLOCK_MICROS, "leveldb.write.raw.block.micros" },
  //{ STALL_L0_SLOWDOWN_COUNT, "leveldb.l0.slowdown.count"},
  //{ STALL_MEMTABLE_COMPACTION_COUNT, "leveldb.memtable.compaction.count"},
  //{ STALL_L0_NUM_FILES_COUNT, "leveldb.num.files.stall.count"},
  //{ HARD_RATE_LIMIT_DELAY_COUNT, "leveldb.hard.rate.limit.delay.count"},
  //{ SOFT_RATE_LIMIT_DELAY_COUNT, "leveldb.soft.rate.limit.delay.count"},
  { NUM_FILES_IN_SINGLE_COMPACTION, "leveldb.numfiles.in.singlecompaction" },
  //{ DB_SEEK, "leveldb.db.seek.micros" },
  { MEMTABLE_WAIT_MICROS, "leveldb.memtable.wait.micros" },
  { STALLED_WRITE_MICROS, "leveldb.stalled.writes.micros" },
  { MEMTABLE_INSERT_MICROS, "leveldb.memtable.insert.micros" },
  { WAL_APPEND_MICROS, "leveldb.wal.append.micros" },
  { FILES_PROBED_PER_READ, "leveldb.files.probed.per.read" },
  { NUM_LEVELS_PROBED_PER_READ, "leveldb.levels.probed.per.read" },
  { MEMTABLE_FLUSH_MICROS, "leveldb.memtable.flush.micros" },
  { SSD_CACHE_INSERT_MICROS, "leveldb.ssd.cache.insert.micros" },
  { SSD_CACHE_CHECK_KEY_MICROS, "leveldb.ssd.cache.check.key.micros" },
  { SSD_CACHE_LOOKUP_MICROS, "leveldb.ssd.cache.lookup.micros" },
  { SSD_CACHE_INSERT_ON_MISS_MICROS, "leveldb.ssd.cache.insert.on.miss.micros" },
  { BUILD_BATCH_GROUP_MICROS, "leveldb.build.batch.group.micros" },
  { TABLE_CACHE_GET_MICROS, "leveldb.table.cache.get.micros" },
  { VERSION_SET_GET_MICROS, "leveldb.versionset.get.micros" },
  { MEMTABLE_GET_MICROS, "leveldb.memtable.get.micros" },
  { IMM_MEMTABLE_GET_MICROS, "leveldb.imm.memtable.get.micros" },
  { MAYBE_SCHEDULE_COMPACTION_MICROS, "leveldb.schedule.compaction.micros" },
  { GET_REF_STUFF_MICROS, "leveldb.get.ref.stuff.micros" },
  { GET_UNREF_STUFF_MICROS, "leveldb.get.unref.stuff.micros" },
  { GET_UPDATE_STATS_MICROS, "leveldb.get.update.stats.micros" },
  { GET_UNLOCK_MICROS, "leveldb.get.unlock.micros" },
  { GET_LOCK_MICROS, "leveldb.get.lock.micros" },
};

struct HistogramData {
  double median;
  double percentile95;
  double percentile99;
  double average;
  double standard_deviation;
};

// Analyze the performance of a db
class Statistics {
 public:
  virtual ~Statistics() {}

  virtual uint64_t getTickerCount(uint32_t tickerType) const = 0;
  virtual void histogramData(uint32_t type,
                             HistogramData* const data) const = 0;

  virtual void recordTick(uint32_t tickerType, uint64_t count = 0) = 0;
  virtual void setTickerCount(uint32_t tickerType, uint64_t count) = 0;
  virtual void measureTime(uint32_t histogramType, uint64_t time) = 0;

  // String representation of the statistic object.
  virtual std::string ToString() const {
    // Do nothing by default
    return std::string("ToString(): not implemented");
  }

  // Override this function to disable particular histogram collection
  virtual bool HistEnabledForType(uint32_t type) const {
    return type < HISTOGRAM_ENUM_MAX;
  }

  virtual void clear() = 0;
};

// Create a concrete DBStatistics object
std::shared_ptr<Statistics> CreateDBStatistics();

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_INCLUDE_STATISTICS_H_
