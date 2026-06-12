#include "MenuSystem.h"
#include "config.h"

MenuSystem::MenuSystem(DisplayManager* display)
  : displayManager(display), selectedIndex(0), lastDisplayTime(0) {
}

MenuSystem::~MenuSystem() {
  menuItems.clear();
}

void MenuSystem::addMenuItem(const String& name, int id) {
  MenuItem item;
  item.name = name;
  item.id = id;
  item.selected = (selectedIndex == menuItems.size());
  menuItems.push_back(item);
  
  Serial.println("  [MenuSystem] Added menu item: " + name);
}

void MenuSystem::removeMenuItem(int id) {
  for (auto it = menuItems.begin(); it != menuItems.end(); ++it) {
    if (it->id == id) {
      menuItems.erase(it);
      return;
    }
  }
}

void MenuSystem::clearMenuItems() {
  menuItems.clear();
  selectedIndex = 0;
}

void MenuSystem::moveUp() {
  if (menuItems.empty()) return;
  
  selectedIndex = (selectedIndex - 1 + menuItems.size()) % menuItems.size();
  Serial.println("  [MenuSystem] Moved up to: " + menuItems[selectedIndex].name);
}

void MenuSystem::moveDown() {
  if (menuItems.empty()) return;
  
  selectedIndex = (selectedIndex + 1) % menuItems.size();
  Serial.println("  [MenuSystem] Moved down to: " + menuItems[selectedIndex].name);
}

void MenuSystem::setSelectedIndex(int index) {
  if (index >= 0 && index < menuItems.size()) {
    selectedIndex = index;
  }
}

int MenuSystem::getSelectedID() const {
  if (selectedIndex < menuItems.size()) {
    return menuItems[selectedIndex].id;
  }
  return -1;
}

String MenuSystem::getSelectedName() const {
  if (selectedIndex < menuItems.size()) {
    return menuItems[selectedIndex].name;
  }
  return "";
}

void MenuSystem::display() {
  if (menuItems.empty() || displayManager == nullptr) return;
  
  if (millis() - lastDisplayTime < 100) return;
  lastDisplayTime = millis();
  
  displayManager->clear();
  
  displayManager->setCursor(0, 0);
  displayManager->print(">");
  displayManager->print(menuItems[selectedIndex].name);
  
  int nextIndex = (selectedIndex + 1) % menuItems.size();
  displayManager->setCursor(0, 1);
  displayManager->print(" ");
  displayManager->print(menuItems[nextIndex].name);
}