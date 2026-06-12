/*
 * Menu System - Handles navigation and display of menu items
 */

#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include <Arduino.h>
#include <vector>
#include "DisplayManager.h"

struct MenuItem {
  String name;
  int id;
  bool selected;
};

class MenuSystem {
private:
  DisplayManager* displayManager;
  std::vector<MenuItem> menuItems;
  int selectedIndex;
  unsigned long lastDisplayTime;
  
public:
  MenuSystem(DisplayManager* display);
  ~MenuSystem();
  
  // Menu management
  void addMenuItem(const String& name, int id);
  void removeMenuItem(int id);
  void clearMenuItems();
  
  // Navigation
  void moveUp();
  void moveDown();
  void setSelectedIndex(int index);
  
  // Display
  void display();
  void displayPage();
  
  // Accessors
  int getSelectedIndex() const { return selectedIndex; }
  int getSelectedID() const;
  String getSelectedName() const;
  int getMenuItemCount() const { return menuItems.size(); }
};

#endif