#include "jsoncpp/json/json.h"

#include "lib/helpers/filelib.h"

#include "jdict.h"


const std::string KEY_DELIMITER = "::";

bool jdict_read(const std::string& filename, const std::string& key, Json::Value& jv) {
    std::vector<std::string> info_lines;
    read_text_file(filename, info_lines);
    if (!info_lines.empty()) {
        for (const auto& line : info_lines) {
            auto pos = line.find(KEY_DELIMITER);
            if (pos == key.length() && line.substr(0, pos) == key) {
                Json::Reader reader;
                if (reader.parse(line.substr(pos + KEY_DELIMITER.length()), jv)) {
                    return true;
                }
                printf(("jdict_read(): " + reader.getFormattedErrorMessages()).c_str());
            }
        }
    }

    printf("jdict_read(): no data for key '%s' found in %s\n", key.c_str(), filename.c_str());
    return false;
}
