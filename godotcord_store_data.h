#ifndef GODOT_GODOTCORD_STORE_DATA_H
#define GODOT_GODOTCORD_STORE_DATA_H

#include "core/reference.h"
#include "godotcord_utils.h"

class GodotcordSKUPrice : public Reference {
	GDCLASS(GodotcordSKUPrice, Reference)
protected:
	static void _bind_methods() {
		ADD_GODOTCORD_PROPERTY(GodotcordSKUPrice, amount, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordSKUPrice, currency, Variant::STRING)
	};

public:
	uint32_t amount;
	String currency;

	GET_SET_COMBO(amount, uint32_t)
	GET_SET_COMBO(currency, String)
};
class GodotcordSKU : public Reference {
GDCLASS(GodotcordSKU, Reference)

public:
	enum SkuType {
		APP = 1,
		DLC,
		CONSUMABLE,
		BUNDLE
	};

protected:
	static void _bind_methods() {
		ADD_GODOTCORD_PROPERTY(GodotcordSKU, id, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordSKU, type, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordSKU, name, Variant::STRING)
		ADD_GODOTCORD_PROPERTY(GodotcordSKU, price, Variant::OBJECT)
		BIND_ENUM_CONSTANT(APP);
		BIND_ENUM_CONSTANT(DLC);
		BIND_ENUM_CONSTANT(CONSUMABLE);
		BIND_ENUM_CONSTANT(BUNDLE);
	};

public:
	uint64_t id;
	SkuType type;
	String name;
	Ref<GodotcordSKUPrice> price;

	GET_SET_COMBO(id, uint64_t)
	GET_SET_COMBO(type, SkuType)
	GET_SET_COMBO(name, String)
	GET_SET_COMBO(price, Ref<GodotcordSKUPrice>)
};

class GodotcordEntitlement : public Reference {
GDCLASS(GodotcordEntitlement, Reference)

public:
	enum EntitlementType {
		PURCHASE = 1,
		PREMIUM_SUBSCRIPTION,
		DEVELOPER_GIFT,
		TEST_MODE_PURCHASE,
		FREE_PURCHASE,
		USER_GIFT,
		PREMIUM_PURCHASE,
	};

protected:
	static void _bind_methods() {

		ADD_GODOTCORD_PROPERTY(GodotcordEntitlement, id, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordEntitlement, type, Variant::INT)
		ADD_GODOTCORD_PROPERTY(GodotcordEntitlement, sku_id, Variant::INT)
		BIND_ENUM_CONSTANT(PURCHASE);
		BIND_ENUM_CONSTANT(PREMIUM_SUBSCRIPTION);
		BIND_ENUM_CONSTANT(DEVELOPER_GIFT);
		BIND_ENUM_CONSTANT(TEST_MODE_PURCHASE);
		BIND_ENUM_CONSTANT(FREE_PURCHASE);
		BIND_ENUM_CONSTANT(USER_GIFT);
		BIND_ENUM_CONSTANT(PREMIUM_PURCHASE);
	}

public:
	uint64_t id = 0;
	EntitlementType type = EntitlementType::FREE_PURCHASE;
	uint64_t sku_id = 0;

	GET_SET_COMBO(id, uint64_t);
	GET_SET_COMBO(type, EntitlementType)
	GET_SET_COMBO(sku_id, uint64_t)
};

VARIANT_ENUM_CAST(GodotcordSKU::SkuType);
VARIANT_ENUM_CAST(GodotcordEntitlement::EntitlementType);


#endif //GODOT_GODOTCORD_STORE_DATA_H
