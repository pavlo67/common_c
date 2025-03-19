#ifndef JDICT_H
#define JDICT_H

#include "jsoncpp/json/json.h"

const std::string J_KEY_DELIMITER = "::";
const std::string J_HEADER_KEY = "header";

bool jlist_read(const std::string& filename, Json::Value& jv_header, Json::Value& jv_list);
bool jdict_read_key(const std::string& filename, const std::string& key, Json::Value& jv);

#endif //JDICT_H
