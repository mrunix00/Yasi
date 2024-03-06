#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

namespace Bytecode {
    enum ObjectType : uint8_t {
        None,
        Number,
        Boolean,
        String,
    };

    class StackObject {
        union Data {
            double number;
            char *string;
            bool boolean;
        };
        union Data data;

    public:
        explicit StackObject() = default;
        explicit StackObject(double number)
            : data({number}), type(ObjectType::Number){};
        explicit StackObject(bool boolean)
            : type(ObjectType::Boolean) { data.boolean = boolean; };
        explicit StackObject(const std::string &str)
            : type(ObjectType::String) {
            // TODO: This is a dumb workaround, fix it later
            data.string = strdup(str.c_str());
        };

        [[nodiscard]] inline std::string asString() const {
            return data.string;
        }

        [[nodiscard]] inline double asNumber() const {
            return data.number;
        }

        [[nodiscard]] inline bool asBoolean() const {
            return data.boolean;
        }

        bool operator==(StackObject o) const {
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
        uint8_t type;
    };
}// namespace Bytecode