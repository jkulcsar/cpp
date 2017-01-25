#pragma once

//
// RCWidget is a wrapper around the Widget class
// to enable the Widget class for reference counting
//

#include "Widget.hpp"
#include "RCIPtr.hpp"

class RCWidget {
public:
  RCWidget(int size): value(new Widget(size)) {}
  void doThis() { value->doThis(); }
  int showThat() const { return value->showThat(); }
private:
  RCIPtr<Widget> value;
};
