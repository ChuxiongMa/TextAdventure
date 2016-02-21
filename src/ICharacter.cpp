#include "ICharacter.hpp"

void textadventure::ICharacter::clampZero(int &value) {
  if (value < 0) {
    value = 0;
  }
}

string textadventure::ICharacter::getDescription() const {
  return description;
}
textadventure::Attributes textadventure::ICharacter::getAllAttributes() {
  return attributes;
}
int textadventure::ICharacter::getHealth() const {
  return attributes.health;
}
int textadventure::ICharacter::getStrength() const {
  return attributes.strength;
}
int textadventure::ICharacter::getIntelligence() const {
  return attributes.intelligence;
}
int textadventure::ICharacter::getDexterity() const {
  return attributes.dexterity;
}
int textadventure::ICharacter::getCharisma() const {
  return attributes.charisma;
}
void textadventure::ICharacter::modifyHealth(int delta) {
  attributes.health += delta;
  clampZero(attributes.health);
}
void textadventure::ICharacter::modifyStrength(int delta) {
  attributes.strength += delta;
  clampZero(attributes.strength);
}
void textadventure::ICharacter::modifyIntelligence(int delta) {
  attributes.intelligence += delta;
  clampZero(attributes.intelligence);
}
void textadventure::ICharacter::modifyDexterity(int delta) {
  attributes.dexterity += delta;
  clampZero(attributes.dexterity);
}
void textadventure::ICharacter::modifyCharisma(int delta) {
  attributes.charisma += delta;
  clampZero(attributes.charisma);
}
bool textadventure::ICharacter::getIsExploring() const {
  return !isInBattle;
}
void textadventure::ICharacter::setIsExploring() {
  isInBattle = false;
}
bool textadventure::ICharacter::getIsInBattle() const {
  return isInBattle;
}
void textadventure::ICharacter::setIsInBattle() {
  isInBattle = true;
}
bool textadventure::ICharacter::getIsOptedInForBattles() const {
  return isOptedInForBattles;
}
void textadventure::ICharacter::setIsOptedInForBattles(bool value) {
  isOptedInForBattles = value;
}
bool textadventure::ICharacter::operator==(const ICharacter &other) const {
  return (description == other.description &&
      attributes == other.attributes &&
      isInBattle == other.isInBattle &&
      isOptedInForBattles == other.isOptedInForBattles);
}
