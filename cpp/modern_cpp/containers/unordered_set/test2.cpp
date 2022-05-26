//////////////////////////////////
//                              //
// Copyright (c) 2022 Exercises //
//                              //
//////////////////////////////////


#include <string>
#include <string_view>
#include <sstream>
#include <unordered_set>

#include "./test2.h"
#include "../../../../base/logs.h"

namespace {

class CItem {
  const std::string id_;

 public:
  CItem() {
  }
  explicit CItem(const std::string& id)
  : id_(id) {
  }

  bool operator==(const CItem& other) const {
        return (this->id() == other.id());
    }

  const std::string& id() const { return id_; }
};

struct Hash {
      std::size_t operator()(const CItem& item) const {
        return std::hash<std::string>()(item.id());
    }
};

using TContainer = std::unordered_set<CItem, Hash>;

void Add(TContainer &container, const std::string &item) {
  container.insert(CItem(item));
}

void Dump(TContainer &container) {
  LOG_BEG()
  for (const auto &p : container) {
    std::cout << p.id() << std::endl;
  }
  LOG_END()
}

void Find(TContainer &container, const std::string &item) {
  LOG_FUNC()
  TContainer::iterator it(container.find(CItem(item)));
  if (it != container.end()) {
    std::cout << "Found: "<< it->id() << std::endl;
  } else {
    std::cout << "NOT Found: "<< item << std::endl;
  }
}

}  // namespace

void Test2() {
  LOG_BR()
  TContainer container;
  Add(container, "Test2aaa");
  Add(container, "Test2bbb");
  Add(container, "Test2ccc");
  Dump(container);
  Find(container, "Test2bbb");
  Find(container, "qwerty");
}
