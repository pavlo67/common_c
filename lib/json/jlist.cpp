#include "lib/helpers/filelib.h"

#include "jlist.h"

// bool jlist_write(const std::string& filename, Json::Value& jv_header, Json::Value& jv_list) {
//     Json::Value jv;
//     set_jv_header(jv, dd.dh);
//     f << J_HEADER_KEY + J_KEY_DELIMITER + writer.write(jv);
//
//     for (auto bb : dd.bboxes) {
//         set_jv_bbox(jv, bb);
//         f << writer.write(jv);
//     }
//     f.close();
// }

bool jlist_read(const std::string& filename, Json::Value& jv_header, Json::Value& jv_list) {
    Json::Reader reader;
    jv_header.clear();
    jv_list.clear();

    bool header_ok = false;

    std::vector<std::string> info_lines;
    read_text_file(filename, info_lines);

    for (const auto& line : info_lines) {

        auto pos = line.find(J_KEY_DELIMITER);
        if (pos == J_HEADER_KEY.length() && line.substr(0, pos) == J_HEADER_KEY) {
            if (header_ok) {
                printf("jlist_read(): header line duplicate is omitted / %s", line.c_str());
            } else if (reader.parse(line.substr(pos + J_KEY_DELIMITER.length()), jv_header)) {
                header_ok = true;
            } else {
                printf("jlist_read(): header line is wrong / %s", line.c_str());
            }
        } else {
            Json::Value jv;
            if (reader.parse(line, jv)) {
                jv_list.append(jv);
                // printf("parsed: %s --> jv_list.size(): %d\n", line.c_str(), jv_list.size());

            } else if (!line.empty()) {
                printf("can't parse jlist line: '%s'\n", line.c_str());

            }
        }
    }

    return header_ok;
}


bool jdict_read_key(const std::string& filename, const std::string& key, Json::Value& jv) {
    Json::Reader reader;
    jv.clear();

    std::vector<std::string> info_lines;
    read_text_file(filename, info_lines);

    for (const auto& line : info_lines) {
        auto pos = line.find(J_KEY_DELIMITER);
        if (pos == key.length() && line.substr(0, pos) == key) {
            if (reader.parse(line.substr(pos + J_KEY_DELIMITER.length()), jv)) {
                return true;
            }
            printf(("jdict_read_key() for key '%s' in %s: " + reader.getFormattedErrorMessages()).c_str(), key.c_str(), filename.c_str());
        }
    }

    printf("jdict_read_key(): no data for key '%s' in %s\n", key.c_str(), filename.c_str());
    return false;
}
