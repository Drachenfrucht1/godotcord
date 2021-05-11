#ifndef GODOTCORD_UTILS_H
#define GODOTCORD_UTILS_H

#define GET_SET_COMBO(property, type)        \
	void set_##property(type p_##property) { \
		property = p_##property;             \
	}                                        \
	type get_##property() const {            \
		return property;                     \
	}										 \

#define GET_SET_COMBO_OBJ(property, type)    \
	void set_##property(Ref<type> p_##property) { \
		property = p_##property;             \
	}                                        \
	Ref<type> get_##property() const {            \
		return property;                     \
	}										 \

#define ADD_GODOTCORD_PROPERTY(class, property, type)                                     \
	ClassDB::bind_method(D_METHOD("set_" #property, #property), &class ::set_##property); \
	ClassDB::bind_method(D_METHOD("get_" #property), &class ::get_##property);            \
	ADD_PROPERTY(PropertyInfo(type, #property), "set_" #property, "get_" #property);	  \

#endif