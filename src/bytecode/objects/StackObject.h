#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace Bytecode {
    enum ObjectType : uint8_t {
        None,
        Number,
        Boolean,
        String,
        Lambda,
    };

    class StackObject {
        union Data {
            double number;
            size_t reg;
            char *string;
            bool boolean;
        };
        Data data;

    public:
        uint8_t type;

        explicit StackObject() = default;
        explicit StackObject(const size_t segment)
            : type(Lambda) { data.reg = segment; };
        explicit StackObject(const double number)
            : data({number}), type(Number){};
        explicit StackObject(const bool boolean)
            : type(Boolean) { data.boolean = boolean; };
        explicit StackObject(const std::string &str)
            : type(String) {
            // TODO: This is a dumb workaround, fix it later
            data.string = strdup(str.c_str());
        };

        [[nodiscard]] std::string asString() const {
            return data.string;
        }

        [[nodiscard]] double asNumber() const {
            return data.number;
        }

        [[nodiscard]] bool asBoolean() const {
            return data.boolean;
        }

        [[nodiscard]] size_t asLambda() const {
            return data.reg;
        }

        [[nodiscard]] std::string toString() const {
            switch (type) {
                case Boolean:
                    return asBoolean() ? std::string("#true")
                                       : std::string("#false");
                case Number: {
                    std::ostringstream s;
                    s.precision(std::numeric_limits<double>::digits10);
                    s << std::fixed << asNumber();
                    std::string str = s.str();
                    str.erase(str.find_last_not_of('0') + 1);
                    str.erase(str.find_last_not_of('.') + 1);
                    return str;
                }
                case String: {
                    std::string string = asString();
                    return string[0] == '"' && string.back() == '"'
                                   ? string.substr(1, string.size() - 2)
                                   : string;
                }
                case Lambda:
                    return ":" + std::to_string(data.reg);
                default:
                    return "";
            }
        }

        bool operator==(const StackObject o) const {
            if (o.type == type) {
                switch (type) {
                    case None:
                        return true;
                    case Number:
                        return std::abs(data.number - o.data.number) <
                               std::numeric_limits<double>::epsilon() * 10;
                    case Boolean:
                        return data.boolean == o.data.boolean;
                    case String:
                        return !strcmp(data.string, o.data.string);
                    default:
                        return false;
                }
            }
            return false;
        }
    };
}// namespace Bytecode