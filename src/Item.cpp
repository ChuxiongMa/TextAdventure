#include "Item.hpp"

#include <algorithm>
#include <vector>

const string textadventure::Item::NO_DESCRIPTION = "No description";

textadventure::Item::Item(int id, vector<string> keywords, string shortDesc, string longDesc)
  : Item(id, keywords, shortDesc, longDesc, NO_DESCRIPTION)
{}
textadventure::Item::Item(int id, vector<string> keywords, string shortDesc, string longDesc, string description)
  : id(id),
    keywords(keywords),
    shortDesc(shortDesc),
    longDesc(longDesc),
    description(description)
{}

textadventure::Item::~Item() {
}

bool textadventure::Item::operator==(const textadventure::Item &otherItem) const {
  return (this->id == otherItem.id &&
      this->keywords == otherItem.keywords);
}

int textadventure::Item::getId() const {
  return id;
}

vector<string> textadventure::Item::getKeywords() const {
  return keywords;
}

bool textadventure::Item::containsKeyword(string keyword) const {
  return (std::find(keywords.begin(), keywords.end(), keyword) != keywords.end());
}

string textadventure::Item::getShortDescription() const {
  return shortDesc;
}

string textadventure::Item::getLongDescription() const {
  return longDesc;
}

string textadventure::Item::getDescription() const {
  return description;
}
