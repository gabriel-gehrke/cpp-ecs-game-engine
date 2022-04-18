#include "resources.hpp"

#include <unordered_map>

static const char dat[] = "Hallo";

static const std::unordered_map<std::string, Resource> res_map =
{
	{"hallo.txt", {.path="hallo.txt", .data=dat, .size=sizeof(dat)}},
};
