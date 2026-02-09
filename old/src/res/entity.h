#pragma once

#define ENTITIES_COUNT 4000

struct ENTITY
{
	enum class TYPE : u8
	{
		/* unknown */
		UNKNOWN = 0,
		UNKNOWN_SHIELD_ITEM,
		UNKNOWN_ITEM,

		/* shield */
		EXTRA_SHIELD,
		SHIELD_FULL,
		DOUBLE_SHIELD,

		/* ammo */
		EXTRA_AMMO,
		AMMO_FULL,
		DOUBLE_AMMO,

		/* fuel */
		EXTRA_FUEL,
		FUEL_FULL,
		DOUBLE_FUEL,

		/* item upgrades */
		MINIGUN_UPGRADE,
		MISSILE_UPGRADE,
		BOOSTER_UPGRADE,

		/* walls */
		WALL_SEGMENT,

		/* waypoints */
		WAYPOINT_FUEL,
		WAYPOINT_AMMO,
		WAYPOINT_SHIELD,
		WAYPOINT_SPECIAL1,
		WAYPOINT_SPECIAL2,
		WAYPOINT_SPECIAL3,
		WAYPOINT_FAST,
		WAYPOINT_SLOW,
		WAYPOINT_SHORTCUT,

		/* recovery */
		RECOVERY_TRUCK,

		/* checkpoint steam */
		STEAM_STRONG,
		STEAM_LIGHT,
		BARREL,
		CONE,
		CHECKPOINT,

		/* morph */
		MORPH_SOURCE1,
		MORPH_SOURCE2,
		MORPH_ONCE,
		MORPH_PERMANENT,

		/* triggers */
		TRIGGER_CRAFT,
		TRIGGER_TIMED,
		TRIGGER_ROCKET,

		/* damage */
		DAMAGE_CRAFT,

		/* explosions */
		EXPLOSION,
		EXPLOSION_PARTICLES,

		/* sizes */
		TYPE_SIZE,
		TYPE_MAX = UINT8_MAX,
	};
	struct ENTRY
	{
		enum TYPE   type;
		std::string name;
	};

	union {
		u8 data[24];
		struct{
			union {
				struct {
					u8 type;
					u8 subtype;
				};
				u8 type_field;
			};
			i16 group;
			i16 target_group;
			u8 unknown[6];
			i16 next_id;
			i16 value;
			fxd x;
			fxd z;
			fxd offset_x;
			fxd offset_y;
		};
	};

	struct table
	{
		size_t TYPE_SIZE;
		size_t SUBTYPE_SIZE;
		std::vector<std::string>   names;
		std::vector<ENTRY*     > entries;
	};
};


extern entity_type_table_t* entity_type_table;

bool entity_type_table_destroy(entity_type_table_t* entities);
entity_type_table_t* entity_type_table_create(char* entity_info_file);
char* entity_type_table_print();
entity_type_t entity_identify(entity_t* entity);
bool entity_print(entity_t* entity);

#endif
