#ifndef GODOTCORD_UTILS_H
#define GODOTCORD_UTILS_H

#include "core/ustring.h"

#define GET_SET_COMBO(property, type)        \
	void set_##property(type p_##property) { \
		property = p_##property;             \
	}                                        \
	type get_##property() const {            \
		return property;                     \
	}

#define ADD_GODOTCORD_PROPERTY(class, property, type)                                     \
	ClassDB::bind_method(D_METHOD("set_" #property, #property), &class ::set_##property); \
	ClassDB::bind_method(D_METHOD("get_" #property), &class ::get_##property);            \
	ADD_PROPERTY(PropertyInfo(type, #property), "set_" #property, "get_" #property);

inline uint8_t* godotcord_hex_str_to_uint8(String string) {

    if (string == "")
        return NULL;

    if ((string.length() % 2) != 0) // must be even
        return NULL;

    size_t dlength = string.length() / 2;

    uint8_t* data = (uint8_t*)malloc(dlength);

    memset(data, 0, dlength);

    size_t index = 0;
	while (index < string.length()) {
        char c = string[index];
        int value = 0;
        if (c >= '0' && c <= '9')
            value = (c - '0');
        else if (c >= 'A' && c <= 'F')
            value = (10 + (c - 'A'));
        else if (c >= 'a' && c <= 'f')
            value = (10 + (c - 'a'));
        else
            return NULL;

        data[(index / 2)] += value << (((index + 1) % 2) * 4);

        index++;
    }

    return data;
}

#endif
