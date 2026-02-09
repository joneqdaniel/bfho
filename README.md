# bfho

Bullfrog [Hi-Octane](https://en.wikipedia.org/wiki/Hi-Octane) C++ library

## Entity layout
```cpp
ENTITY::ENTRY entities->entries[ENTITY::TYPE_COUNT][ENTITY::SUBTYPE_COUNT] =
{
	           { ENTITY::UNKNOWN,             "Unknown"             },

	[ 1][ 5] = { ENTITY::CHECKPOINT,          "Checkpoint"          },

	[ 2][ 1] = { ENTITY::EXPLOSION_PARTICLES, "Explosion Particles" },
	[ 2][ 2] = { ENTITY::DAMAGE_CRAFT,        "Damage Craft"        },
	[ 2][ 3] = { ENTITY::EXPLOSION,           "Explosion"           },	
	[ 2][ 5] = { ENTITY::STEAM_STRONG,        "Steam Strong"        },
	[ 2][ 7] = { ENTITY::MORPH_SOURCE2,       "Morph Source2"       },
	[ 2][ 8] = { ENTITY::STEAM_LIGHT,         "Steam Light"         },
	[ 2][ 9] = { ENTITY::MORPH_SOURCE1,       "Morph Source1"       },
	[ 2][16] = { ENTITY::MORPH_ONCE,          "Morph Once"          },
	[ 2][23] = { ENTITY::MORPH_PERMANENT,     "Morph Permanent"     },

	[ 3][ 3] = { ENTITY::BARREL,              "Entity Barrel"       },
	[ 3][ 6] = { ENTITY::CONE,                "Entity Cone"         },

	[ 5][ 0] = { ENTITY::UNKNOWN_SHIELD_ITEM, "Unknown Shield"      },
	[ 5][ 1] = { ENTITY::UNKNOWN_ITEM,        "Unknown Item"        },

	[ 5][ 2] = { ENTITY::EXTRA_SHIELD,        "Extra Shield"        },
	[ 5][ 3] = { ENTITY::SHIELD_FULL,         "Shield Full"         },
	[ 5][ 4] = { ENTITY::DOUBLE_SHIELD,       "Double Shield"       },
	[ 5][ 5] = { ENTITY::EXTRA_AMMO,          "Extra Ammo"          },
	[ 5][ 6] = { ENTITY::AMMO_FULL,           "Ammo Full"           },
	[ 5][ 7] = { ENTITY::DOUBLE_AMMO,         "Double Ammo"         },
	[ 5][ 8] = { ENTITY::EXTRA_FUEL,          "Extra Fuel"          },
	[ 5][ 9] = { ENTITY::FUEL_FULL,           "Fuel Full"           },
	[ 5][10] = { ENTITY::DOUBLE_FUEL,         "Double Fuel"         },
	[ 5][11] = { ENTITY::MINIGUN_UPGRADE,     "Minigun Upgrade"     },
	[ 5][12] = { ENTITY::MISSILE_UPGRADE,     "Missile Upgrade"     },
	[ 5][13] = { ENTITY::BOOSTER_UPGRADE,     "Booster Upgrade"     },

	[ 8][ 0] = { ENTITY::TRIGGER_CRAFT,       "Trigger Craft"       },
	[ 8][ 1] = { ENTITY::TRIGGER_TIMED,       "Trigger Timed"       },
	[ 8][ 3] = { ENTITY::TRIGGER_ROCKET,      "Trigger Rocket"      },

	[ 9][ 0] = { ENTITY::WALL_SEGMENT,        "Wall Segment"        },

	[ 9][ 1] = { ENTITY::WAYPOINT_SLOW,       "Waypoint Slow"       },
	[ 9][ 2] = { ENTITY::WAYPOINT_FUEL,       "Waypoint Fuel"       },
	[ 9][ 3] = { ENTITY::WAYPOINT_AMMO,       "Waypoint Ammo"       },
	[ 9][ 4] = { ENTITY::WAYPOINT_SHIELD,     "Waypoint Shield"     },
	[ 9][ 6] = { ENTITY::WAYPOINT_SHORTCUT,   "Waypoint Shortcut"   },
	[ 9][ 7] = { ENTITY::WAYPOINT_SPECIAL1,   "Waypoint Special1"   },
	[ 9][ 8] = { ENTITY::WAYPOINT_SPECIAL2,   "Waypoint Special2"   },
	[ 9][ 9] = { ENTITY::WAYPOINT_FAST,       "Waypoint Fast"       },
	[ 9][10] = { ENTITY::WAYPOINT_SPECIAL3,   "Waypoint Special3"   },

	[10][ 9] = { ENTITY::RECOVERY_TRUCK,      "Recovery Truck"      },
};

```
## Usage

new map list format using simple checksum 
with additional comment line as name

### maps.cfg
```sh
cd data && rhash -C -simple maps/*
```
add map name as a comment beginning with ```; <name>``` after the line following the checksum and file

### entities.cfg

```sh
<hexadecimal type size> <hexadecimal subtype size>
; types count / subtypes count
<hexadecimal type> <hexadecimal subtype> <decimal enum int id>
; Unknown Zero
```
for every entity

```sh
<hexadecimal type> <hexadecimal subtype> <decimal enum int id>
; <entity name string>
```
must be added past the header

## Links
### Irrlicht engine
- [hi-octane202x](https://github.com/woalexan/hi-octane202x)
- [H-Craft Championship](https://github.com/mzeilfelder/hc1)
### C#
- [HiOctaneTools](https://github.com/movAX13h/HiOctaneTools)
### Other
- [moddingwiki](https://moddingwiki.shikadi.net/wiki/Hi_Octane)
- [Debug symbols from the PSX release](https://github.com/RetroReversing/retroReversing/blob/779ab5297c1e5501a4e563e801dfd0724acc1536/pages/ps1/PS1Symbols.md?plain=1#L59)

