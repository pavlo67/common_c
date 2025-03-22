#ifndef JDICT_H
#define JDICT_H

#include "jsoncpp/json/json.h"

bool jdict_read(const std::string& filename, const std::string& key, Json::Value& jv);

#endif //JDICT_H
