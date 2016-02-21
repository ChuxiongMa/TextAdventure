#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

using namespace std;

namespace textadventure {
  class Item {
  public:
    Item(int id, vector<string> keywords, string shortDesc, string longDesc);
    Item(int id, vector<string> keywords, string shortDesc, string longDesc, string description);
    virtual ~Item();
    bool operator==(const Item &otherItem) const;
    int getId() const;
    vector<string> getKeywords() const;
    bool containsKeyword(string keyword) const;
    string getShortDescription() const;
    string getLongDescription() const;
    string getDescription() const;
    static const string NO_DESCRIPTION;
  private:
    Item();
    int id;
    vector<string> keywords;
    string shortDesc;
    string longDesc;
    string description;
  };
}

#endif
