/*
* Copyright 2021 <QQQ>
*/

#include <string>
#include <string_view>
#include <sstream>
#include <unordered_set>

#include "./test1.h"
#include "../../../../base/logs.h"

using TContainer = std::unordered_set<std::string>;

void Add(TContainer &container, const std::string &item) {
  container.insert(item);
}

void Dump(TContainer &container) {
  LOG_BEG()
  for (const auto &p : container) {
    std::cout << p << std::endl;
  }
  LOG_END()
}

void Find(TContainer &container, const std::string &item) {
  LOG_FUNC()
  TContainer::iterator it(container.find(item));
  if (it != container.end()) {
    std::cout << "Found: "<< *it << std::endl;
  } else {
    std::cout << "NOT Found: "<< item << std::endl;
  }
}

void Test1() {
  TContainer container;
  Add(container, "aaa");
  Add(container, "bbb");
  Add(container, "ccc");
  Dump(container);
  Find(container, "bbb");
  Find(container, "qwerty");
}
