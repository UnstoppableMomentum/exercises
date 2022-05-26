//////////////////////////////////
//                              //
// Copyright (c) 2022 Exercises //
//                              //
//////////////////////////////////


#include <string>
#include <string_view>
#include <sstream>
#include <unordered_set>

#include "./test3.h"
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

class Container {
 public:
  using TContainer = std::unordered_set<CItem, Hash>;
  TContainer container_;

 public:
  void Add(const std::string& item) {
    container_.insert(CItem(item));
  }

  bool Exists(const std::string &item) {
    LOG_FUNC()
    TContainer::iterator it(container_.find(CItem(item)));
    return it != container_.end();
  }

  void Dump() const {
    LOG_BEG()
    for (const auto &p : container_) {
      std::cout << p.id() << std::endl;
    }
    LOG_END()
  }

  TContainer::iterator Find(const std::string &item) {
    LOG_FUNC()
    return container_.find(CItem(item));
  }
  TContainer::const_iterator Find(const std::string &item) const {
    LOG_FUNC()
    return container_.find(CItem(item));
  }
};

}  // namespace


void Test3() {
  LOG_BR()
  Container cont;

  cont.Add("Test3aaa");
  cont.Add("Test3bbb");
  cont.Add("Test3ccc");
  cont.Dump();
  std::cout << " Exists Test3bbb:" << cont.Exists("Test3bbb") << std::endl;
  std::cout << " Exists qwerty:" << cont.Exists("qwerty") << std::endl;
  Container::TContainer::iterator it(cont.Find("Test3ccc"));
}