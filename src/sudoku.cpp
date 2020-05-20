#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>

namespace po = boost::program_options;
using namespace std;

typedef vector<int> IntVector;

namespace {

const uint32_t MAXBLOCKSIZE = 5;
const uint32_t MAXSIZE = MAXBLOCKSIZE * MAXBLOCKSIZE;

bool CheckBit(uint32_t flags, uint32_t bit) {
  return (flags & (0x01 << bit)) != 0;
}

struct Options {
  string opt_file;
  uint32_t opt_size;
  uint32_t opt_blocksize;
  bool opt_debug;

  Options() {
    SetSize(9);
    opt_debug = false;
  }

  void SetSize(uint32_t size) {
    opt_size = size;
    opt_blocksize = static_cast<uint32_t>(sqrt(size + 1));
  }

  void Print(ostream& os) {
    os << "Options: \n";
    os << "---------------------------------------------------------------\n";
    os << "File:       " << opt_file << "\n";
    os << "Size:       " << opt_size << "\n";
    os << "Block size: " << opt_blocksize << "\n";
    os << "\n";
  }
} options;

struct Cell {
  uint32_t row {0};
  uint32_t col {0};
  uint32_t value {0};

  // Use uint32_t as a set, bit n represents the value n
  uint32_t* rowflag {NULL};
  uint32_t* colflag {NULL};
  uint32_t* blockflag {NULL};

  IntVector candidates;
  size_t key;  // Used for comparison

  void SetFlag(uint32_t value) {
    uint32_t bitval = 0x01 << value; 
    *rowflag |= bitval;
    *colflag |= bitval;
    *blockflag |= bitval;
  }

  void ClearFlag(uint32_t value) {
    uint32_t bitval = ~(0x01 << value); 
    *rowflag &= bitval;
    *colflag &= bitval;
    *blockflag &= bitval;
  }
};
typedef vector<Cell*> CellPtrVector;

ostream& operator<<(ostream& os, const Cell& cell) {
  os << '(' << (cell.row + 1) << ',' << (cell.col + 1) << ',' << cell.value << ',';
  for (auto it = cell.candidates.begin(); it != cell.candidates.end(); ++it) {
    os << *it << " ";
  }
  os << ')' << "\n";
  return os;
}

struct CellComparator {
  bool operator()(const Cell* x, const Cell* y) const {
    return x->key < y->key;
  }
};

class Sudoku {
public:
  Cell cells_[MAXSIZE][MAXSIZE];
  uint32_t rowflags_[MAXSIZE];
  uint32_t colflags_[MAXSIZE];
  uint32_t blockflags_[MAXBLOCKSIZE][MAXBLOCKSIZE];
  CellPtrVector vec_;
  bool found_ {false};

  Sudoku() {
    memset(&cells_, 0, sizeof(cells_));
    memset(&rowflags_, 0, sizeof(rowflags_));
    memset(&colflags_, 0, sizeof(colflags_));
    memset(&blockflags_, 0, sizeof(blockflags_));
  }

  bool Init() {
    char buf[1024];
    FILE* fp = fopen(options.opt_file.c_str(), "r");
    boost::shared_ptr<FILE> fileguard(fp, fclose);
    if (fp == NULL) {
      cerr << "Failed to open file " << options.opt_file << "\n";
      return false;
    }
    uint32_t row = 0;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
      uint32_t col = 0;
      char* tok = strtok(buf, " ");
      while (tok != NULL) {
        Cell& cell = cells_[row][col];
        cell.row = row;
        cell.col = col;
        cell.rowflag = &rowflags_[row];
        cell.colflag = &colflags_[col];
        cell.blockflag = &blockflags_[row / options.opt_blocksize][col / options.opt_blocksize];
        cell.value = strtoull(tok, NULL, 10);
        cell.SetFlag(cell.value);
        ++col;
        tok = strtok(NULL, " ");
      }
      ++row;
    }
    Print(cout);
    if (options.opt_debug) {
      cout << "\nDetails:\n";
      cout << "-----------------------------------------------------------\n";
    }
    for (uint32_t row = 0; row < options.opt_size; ++row) {
      for (uint32_t col = 0; col < options.opt_size; ++col) {
        Cell& cell = cells_[row][col];
        if (cell.value == 0) {
          uint32_t flags = *cell.rowflag | *cell.colflag | *cell.blockflag;
          for (uint32_t i = 1; i <= options.opt_size; ++i) {
            if (!CheckBit(flags, i)) {
              cell.candidates.push_back(i);
            }
          }
          cell.key = MAXSIZE * MAXSIZE * cell.candidates.size() + MAXSIZE * cell.row + cell.col;
          vec_.push_back(&cell);
        }
        if (options.opt_debug) {
          cout << cells_[row][col];
        }
      }
    }
    sort(vec_.begin(), vec_.end(), CellComparator());
    if (options.opt_debug) {
      cout << "\nEmpty cells:\n";
      cout << "-----------------------------------------------------------\n";
      for (auto it = vec_.begin(); it != vec_.end(); ++it) {
        cout << *(*it);
      }
    }
    return true;
  }

  bool Solve(size_t index) {
    if (found_) {
      return true;
    }
    if (index == vec_.size()) {
      cout << "\nSolution:\n";
      cout << "-----------------------------------------------------------\n";
      Print(cout);
      return true;
    }
    Cell& cell = *vec_[index];
    auto endit = cell.candidates.end();
    for (auto it = cell.candidates.begin(); it != endit; ++it) {
      if (IsOk(cell, *it)) {
        cell.value = *it;
        cell.SetFlag(*it);
        if (Solve(index + 1)) {
          return true;
        }
        cell.ClearFlag(*it);
      }
    }
    return false;
  }

  void Solve() {
    found_ = false;
    Solve(0);
  }

private:
  void Print(ostream& os) {
    for (uint32_t row = 0; row < options.opt_size; ++row) {
      for (uint32_t col = 0; col < options.opt_size; ++col) {
        os << setw(2) << cells_[row][col].value << " ";
      }
      os << "\n";
    }
  }

  bool IsOk(const Cell& cell, int value) {
    uint32_t flags = *cell.rowflag | *cell.colflag | *cell.blockflag;
    return !CheckBit(flags, value);
  }
};

} // namespace

int main(int argc, char* argv[]) {
  po::options_description desc("Options");
  desc.add_options()
    ("file",         po::value<string>(),   "set input file")
    ("size",         po::value<uint32_t>(), "set size")
    ("debug",                               "debug mode")
    ("help",                                "show the help");
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);
  if (vm.count("file") > 0) {
    options.opt_file = vm["file"].as<string>();
  }
  if (vm.count("size") > 0) {
    options.SetSize(vm["size"].as<uint32_t>());
  }
  if (vm.count("debug") > 0) {
    options.opt_debug = true;
  }
  if (vm.count("help") > 0 ) {
    cout << desc << "\n";
    return 0;
  }
  options.Print(cout);

  Sudoku sudoku;
  if (!sudoku.Init()) {
    cerr << "Failed to init the sudoku data\n";
    return 1;
  }
  sudoku.Solve();
  return 0;
}

