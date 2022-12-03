#ifndef ATLAS_H
#define ATLAS_H

#include <istream>
#include <string>
#include <sstream>
#include <algorithm>

#include "Helpers.h"
#include "Trip.h"


class Atlas {
public:
  static Atlas* create(std::istream& stream);

private:
  // Member Variables
	Mapper mapping;
public:
  // Constructor & Destructor
  Atlas(std::istream& stream);
  ~Atlas();

  // Required Member Function
  Trip route(const std::string& src, const std::string& dst);
};

#endif
