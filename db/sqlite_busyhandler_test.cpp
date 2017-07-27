/**
 * @file
 * @author shancheng.cn@gmail.com
 * @version 0.1
 * @section DESCRIPTION
 *
 * Verify no SQLITE_BUSY after setup busy handler
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/thread.hpp>
#include <sqlite3.h>

namespace po = boost::program_options;
using namespace std;

namespace {

struct Option {
  size_t threadcount;
  size_t busytimeout;
  bool debug;

  Option()
      : threadcount(10),
        busytimeout(0),
        debug(false) {
  }

  void Print(ostream& os) {
    os << "Options: \n";
    os << "-----------------------------------------------------------------\n";
    os << "Thread count: " << threadcount << "\n";
    os << "Busy timeout: " << busytimeout << "\n";
    os << "Debug mode: " << debug << "\n";
    os << "\n";
  }
} option;

// Total I/O count
// For simplicity, assume it's an atomic integer, don't protect with mutex
uint32_t total_iocount = 0;

// Total busy count
// For simplicity, assume it's an atomic integer, don't protect with mutex
uint32_t total_busycount = 0;

// A vector of DB pointers
vector<sqlite3*> dbvec;

class Job {
public:
  Job(int threadindex, sqlite3* db)
      : threadindex_(threadindex),
        db_(db),
        insertcount_(0) {
  }

  void operator()() {
    while (true) {
      int randval = random() % 500 + 500; // 0 - 1000
      usleep(randval * 1000); // 1ms - 1s
      if (ReadTenRecords()) {
        ++total_iocount;
      }
      if (AppendOneRecord()) {
        ++total_iocount;
      }
    }
  }

private:
  bool Execute(const string& sql) {
    char* errmsg = NULL;
    while (true) {
      int status = sqlite3_exec(db_, sql.c_str(), NULL, NULL, &errmsg);
      if (status == SQLITE_OK) {
        return true;
      } else if (status == SQLITE_BUSY) {
        ++total_busycount;
        if (option.debug) {
          cerr << "Thread " << threadindex_ << ": failed to execute " << sql << " (" << errmsg << ")\n";
        }
        sqlite3_free(errmsg);
        sleep(1);
      } else {
        cerr << "Thread " << threadindex_ << ": failed to execute " << sql << " (" << errmsg << ")\n";
        sqlite3_free(errmsg);
        return false;
      }
    }
    return false;
  }

  void ProcessRecord(sqlite3_stmt* stmt) {
    // Discard data
  }

  bool ReadTenRecords() {
    bool result = true;
    sqlite3_stmt* stmt = NULL;
    while (true) {
      int status = sqlite3_prepare(db_, "SELECT value FROM test", -1, &stmt, NULL);
      if (status == SQLITE_OK) {
        break;
      } else if (status == SQLITE_BUSY) {
        ++total_busycount;
        if (option.debug) {
          cerr << "Thread " << threadindex_ << ": failed to prepare read statement (" << sqlite3_errmsg(db_) << ")\n";
        }
        sleep(1);
      } else {
        cerr << "Thread " << threadindex_ << ": failed to prepare read statement (" << sqlite3_errmsg(db_) << ")\n";
        result = false;
        goto cleanup;
      }
    }
    for (size_t i = 0; i < 10; ++i) {
      int status = sqlite3_step(stmt);
      if (status == SQLITE_ROW) {
        ProcessRecord(stmt);
        usleep(5000); // Sleep to increase the lock time
      } else if (status == SQLITE_DONE) {
        break;
      } else if (status == SQLITE_BUSY) {
        ++total_busycount;
        if (option.debug) {
          cerr << "Thread " << threadindex_ << ": failed to read data (" << sqlite3_errmsg(db_) << ")\n";
        }
        usleep(50000);
        --i; // Don't increase i
      } else {
        cerr << "Thread " << threadindex_ << ": failed to read data (" << sqlite3_errmsg(db_) << ")\n";
        result = false;
        break;
      }
    }

  cleanup:
    sqlite3_finalize(stmt);
    return result;
  }

  bool AppendOneRecord() {
    ostringstream oss;
    oss << "INSERT INTO test(value) VALUES('thread_" << threadindex_ << "-" << insertcount_++ << "')";
    return Execute(oss.str());
  }

  size_t threadindex_;
  sqlite3* db_;
  size_t insertcount_;
};

int BusyHandler(void* userdata, int busycount) {
  usleep(100 * 1000);
  return 1;
}

} // namespace

int main(int argc, char* argv[]) {
  po::options_description opts("Options");
  opts.add_options()
    ("threadcount",  po::value<size_t>(), "set thread count")
    ("busytimeout",  po::value<size_t>(), "set busy timeout value (ms)")
    ("debug",                             "debug mode")
    ("help,h",                            "show the help");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, opts), vm);
  po::notify(vm);
  if (vm.count("help") > 0 ) {
    cout << opts << "\n";
    return 0;
  }
  if (vm.count("threadcount") > 0) {
    option.threadcount = vm["threadcount"].as<size_t>();
  }
  if (vm.count("busytimeout") > 0) {
    option.busytimeout = vm["busytimeout"].as<size_t>();
  }
  if (vm.count("debug") > 0) {
    option.debug = true;
  }
  option.Print(cout);

  boost::thread_group threadgroup;
  dbvec.resize(option.threadcount);
  time_t begin = time(NULL);
  for (size_t i = 0; i < option.threadcount; ++i) {
    if (sqlite3_open("concurrencytest.db", &dbvec[i]) != SQLITE_OK) {
      cerr << "Failed to open database\n";
      goto cleanup;
    }
    if (sqlite3_busy_handler(dbvec[i], BusyHandler, NULL) != SQLITE_OK) {
      cerr << "Failed to set busy handler (" << sqlite3_errmsg(dbvec[i]) << ")\n";
      goto cleanup;
    }
  }
  for (size_t i = 0; i < option.threadcount; ++i) {
    threadgroup.create_thread(Job(i, dbvec[i]));
  }
  for (size_t i = 0; ; ++i) {
    sleep(1);
    time_t now = time(NULL);
    cout << i << " IOPS: " << 1000L * total_iocount / (now - begin) << " busy count:" << total_busycount << "\n";
  }
  threadgroup.join_all();

cleanup:
  for (size_t i = 0; i < option.threadcount; ++i) {
    sqlite3_close(dbvec[i]);
  }

  return 0;
}

