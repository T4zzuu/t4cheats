#pragma once
#include "../../dependencies/math/math.hpp"
#include <array>
#include "collideable.hpp"
#include "client_class.hpp"
#include "../structs/animstate.hpp"
#include "../../dependencies/utilities/netvars/netvars.hpp"

enum data_update_type_t {
	DATA_UPDATE_CREATED = 0,
	DATA_UPDATE_DATATABLE_CHANGED,
};

enum cs_weapon_type {
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};

enum client_frame_stage_t {
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

enum move_type {
	movetype_none = 0,
	movetype_isometric,
	movetype_walk,
	movetype_step,
	movetype_fly,
	movetype_flygravity,
	movetype_vphysics,
	movetype_push,
	movetype_noclip,
	movetype_ladder,
	movetype_observer,
	movetype_custom,
	movetype_last = movetype_custom,
	movetype_max_bits = 4,
	max_movetype
};

enum entity_flags {
	fl_onground = (1 << 0),
	fl_ducking = (1 << 1),
	fl_waterjump = (1 << 2),
	fl_ontrain = (1 << 3),
	fl_inrain = (1 << 4),
	fl_frozen = (1 << 5),
	fl_atcontrols = (1 << 6),
	fl_client = (1 << 7),
	fl_fakeclient = (1 << 8),
	fl_inwater = (1 << 9),
	fl_fly = (1 << 10),
	fl_swim = (1 << 11),
	fl_conveyor = (1 << 12),
	fl_npc = (1 << 13),
	fl_godmode = (1 << 14),
	fl_notarget = (1 << 15),
	fl_aimtarget = (1 << 16),
	fl_partialground = (1 << 17),
	fl_staticprop = (1 << 18),
	fl_graphed = (1 << 19),
	fl_grenade = (1 << 20),
	fl_stepmovement = (1 << 21),
	fl_donttouch = (1 << 22),
	fl_basevelocity = (1 << 23),
	fl_worldbrush = (1 << 24),
	fl_object = (1 << 25),
	fl_killme = (1 << 26),
	fl_onfire = (1 << 27),
	fl_dissolving = (1 << 28),
	fl_transragdoll = (1 << 29),
	fl_unblockable_by_player = (1 << 30)
};
enum item_definition_indexes {
	WEAPON_NONE = 0,
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SHIELD,
	WEAPON_SCAR20,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_SNOWBALL,
	WEAPON_BUMPMINE,
	WEAPON_BAYONET = 500,
	WEAPON_KNIFE_CSS = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035
};

enum obs_modes {
	obs_mode_none = 0,
	obs_mode_deathcam,
	obs_mode_freezecam,
	obs_mode_fixed,
	obs_mode_in_eye,
	obs_mode_chase,
	obs_mode_roaming
};

class entity_t {
public:
	void* animating() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x4);
	}

	void* networkable() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x8);
	}

	collideable_t* collideable() {
		using original_fn = collideable_t * (__thiscall*)(void*);
		return (*(original_fn * *)this)[3](this);
	}

	matrix_t& coordinateframe() {
		static auto m_rgflCoordinateFrame = netvar_manager::get_net_var(fnv::hash("DT_BaseEntity"), fnv::hash("m_CollisionGroup")) - 0x30;
		return *(matrix_t*)((uintptr_t)this + m_rgflCoordinateFrame);
	}

	c_client_class* client_class() {
		using original_fn = c_client_class * (__thiscall*)(void*);
		return (*(original_fn * *)networkable())[2](networkable());
	}

	int index() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn * *)networkable())[10](networkable());
	}

	bool is_player() {
		using original_fn = bool(__thiscall*)(entity_t*);
		return (*(original_fn * *)this)[157](this);
	}

	bool is_weapon() {
		using original_fn = bool(__thiscall*)(entity_t*);
		return (*(original_fn * *)this)[165](this);
	}

	bool setup_bones(matrix_t * out, int max_bones, int mask, float time) {
		if (!this)
			return false;

		using original_fn = bool(__thiscall*)(void*, matrix_t*, int, int, float);
		return (*(original_fn * *)animating())[13](animating(), out, max_bones, mask, time);
	}

	model_t* model() {
		using original_fn = model_t * (__thiscall*)(void*);
		return (*(original_fn * *)animating())[8](animating());
	}

	void update() {
		using original_fn = void(__thiscall*)(entity_t*);
		(*(original_fn * *)this)[218](this);
	}

	int draw_model(int flags, uint8_t alpha) {
		using original_fn = int(__thiscall*)(void*, int, uint8_t);
		return (*(original_fn * *)animating())[9](animating(), flags, alpha);
	}

	void set_angles(vec3_t angles) {
		using original_fn = void(__thiscall*)(void*, const vec3_t&);
		static original_fn set_angles_fn = (original_fn)((DWORD)utilities::pattern_scan("client_panorama.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1"));
		set_angles_fn(this, angles);
	}

	void set_position(vec3_t position) {
		using original_fn = void(__thiscall*)(void*, const vec3_t&);
		static original_fn set_position_fn = (original_fn)((DWORD)utilities::pattern_scan("client_panorama.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8"));
		set_position_fn(this, position);
	}

	void set_model_index(int index) {
		using original_fn = void(__thiscall*)(void*, int);
		return (*(original_fn * *)this)[75](this, index);
	}

	void net_pre_data_update(int update_type) {
		using original_fn = void(__thiscall*)(void*, int);
		return (*(original_fn * *)networkable())[6](networkable(), update_type);
	}

	void net_release() {
		using original_fn = void(__thiscall*)(void*);
		return (*(original_fn * *)networkable())[1](networkable());
	}

	int net_set_destroyed_on_recreate_entities() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn * *)networkable())[13](networkable());
	}

	offset(bool, dormant, 0xED)

	netvar("DT_CSPlayer", "m_fFlags", flags, int)
	netvar("DT_BaseEntity", "m_hOwnerEntity", owner_handle, unsigned long)
	netvar("DT_CSPlayer", "m_flSimulationTime", simulation_time, float)
	netvar("DT_BasePlayer", "m_vecOrigin", origin, vec3_t)
	netvar("DT_BasePlayer", "m_vecViewOffset[0]", view_offset, vec3_t)
	netvar("DT_CSPlayer", "m_iTeamNum", team, int)
	netvar("DT_BaseEntity", "m_bSpotted", spotted, bool)
	netvar("DT_CSPlayer", "m_nSurvivalTeam", survival_team, int)
	netvar("DT_CSPlayer", "m_flHealthShotBoostExpirationTime", health_boost_time, float)
};

class econ_view_item_t {
public:
	netvar("DT_ScriptCreatedItem", "m_bInitialized", is_initialized, bool)
	netvar("DT_ScriptCreatedItem", "m_iEntityLevel", entity_level, int)
	netvar("DT_ScriptCreatedItem", "m_iAccountID", account_id, int)
	netvar("DT_ScriptCreatedItem", "m_iItemIDLow", item_id_low, int)
};

class base_view_model_t : public entity_t {
public:
	netvar("DT_BaseViewModel", "m_nModelIndex", model_index, int);
	netvar("DT_BaseViewModel", "m_nViewModelIndex", view_model_index, int);
	netvar("DT_BaseViewModel", "m_hWeapon", m_hweapon, int);
	netvar("DT_BaseViewModel", "m_hOwner", m_howner, int);
};

class weapon_t : public entity_t {
public:
	netvar("DT_BaseCombatWeapon", "m_flNextPrimaryAttack", next_primary_attack, float);
	netvar("DT_BaseCombatWeapon", "m_flNextSecondaryAttack", next_secondary_attack, float);
	netvar("DT_BaseCombatWeapon", "m_iClip1", clip1_count, int);
	netvar("DT_BaseCombatWeapon", "m_iClip2", clip2_count, int);
	netvar("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount", primary_reserve_ammo_acount, int);
	netvar("DT_WeaponCSBase", "m_flRecoilIndex", recoil_index, float);
	netvar("DT_WeaponCSBaseGun", "m_zoomLevel", zoom_level, float);
	netvar("DT_BaseAttributableItem", "m_iItemDefinitionIndex", item_definition_index, short);
	netvar("DT_BaseCombatWeapon", "m_iEntityQuality", entity_quality, int);

	float inaccuracy() {
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn * *)this)[482](this);
	}

	float get_spread() {
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn * *)this)[452](this);
	}

	void update_accuracy_penalty() {
		using original_fn = void(__thiscall*)(void*);
		(*(original_fn * *)this)[483](this);
	}

	weapon_info_t* get_weapon_data() {
		return interfaces::weapon_system->get_weapon_data(this->item_definition_index());
	}

	std::string get_weapon_name() {
		switch (this->client_class()->class_id)
		{
		case class_ids::cak47: return "ak47"; break;
		case class_ids::cbreachcharge: return "breachcharge"; break;
		case class_ids::cbumpmine: return "bumpmine"; break;
		case class_ids::cc4: return "c4"; break;
		case class_ids::cdeagle: return "deagle"; break;
		case class_ids::cdecoygrenade: return "decoygrenade"; break;
		case class_ids::cflashbang: return "flashbang"; break;
		case class_ids::chegrenade: return "hegrenade"; break;
		case class_ids::cincendiarygrenade: return "incendiarygrenade"; break;
		case class_ids::cknife: return "knife"; break;
		case class_ids::cknifegg: return "golden knife"; break;
		case class_ids::cmelee: return "melee"; break;
		case class_ids::cfists: return "fists"; break;
		case class_ids::cmolotovgrenade: return "molotovgrenade"; break;
		case class_ids::cscar17: return "scar17"; break;
		case class_ids::csensorgrenade: return "sensorgrenade"; break;
		case class_ids::csmokegrenade: return "smokegrenade"; break;
		case class_ids::csnowball: return "snowball"; break;
		case class_ids::ctablet: return "tablet"; break;
		case class_ids::cweaponaug: return "aug"; break;
		case class_ids::cweaponawp: return "awp"; break;
		case class_ids::cweaponbizon: return "bizon"; break;
		case class_ids::cweaponelite: return "elites"; break;
		case class_ids::cweaponfamas: return "famas"; break;
		case class_ids::cweaponfiveseven: return "fiveseven"; break;
		case class_ids::cweapong3sg1: return "g3sg1"; break;
		case class_ids::cweapongalil: return "galil"; break;
		case class_ids::cweapongalilar: return "galilar"; break;
		case class_ids::cweaponglock: return "glock"; break;
		case class_ids::cweaponhkp2000: return "hkp2000"; break;
		case class_ids::cweaponm249: return "m249"; break;
		case class_ids::cweaponm4a1: return "m4a1"; break;
		case class_ids::cweaponmac10: return "mac10"; break;
		case class_ids::cweaponmag7: return "mag7"; break;
		case class_ids::cweaponmp5navy: return "mp5sd"; break;
		case class_ids::cweaponmp7: return "mp7"; break;
		case class_ids::cweaponmp9: return "mp9"; break;
		case class_ids::cweaponnegev: return "negev"; break;
		case class_ids::cweaponnova: return "nova"; break;
		case class_ids::cweaponp250: return "p250"; break;
		case class_ids::cweaponp90: return "p90"; break;
		case class_ids::cweaponsawedoff: return "sawedoff"; break;
		case class_ids::cweaponscar20: return "scar20"; break;
		case class_ids::cweaponscout: return "scout"; break;
		case class_ids::cweaponsg550: return "sg550"; break;
		case class_ids::cweaponsg552: return "sg552"; break;
		case class_ids::cweaponsg556: return "sg556"; break;
		case class_ids::cweaponshield: return "shield"; break;
		case class_ids::cweaponssg08: return "ssg08"; break;
		case class_ids::cweapontaser: return "taser"; break;
		case class_ids::cweapontec9: return "tec9"; break;
		case class_ids::cweaponump45: return "ump45"; break;
		case class_ids::cweaponusp: return "usp-s"; break;
		case class_ids::cweaponxm1014: return "xm1014"; break;
		default: return ""; break;
		}
	}
};

class player_t : public entity_t {
private:
	template <typename T>
	T& read(uintptr_t offset) {
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	template <typename T>
	void write(uintptr_t offset, T data) {
		*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset) = data;
	}

public:
	netvar("DT_CSPlayer", "m_ArmorValue", armor, int)
	netvar("DT_CSPlayer", "m_bHasHelmet", has_helmet, bool)
	netvar("DT_CSPlayer", "m_bIsScoped", is_scoped, bool)
	netvar("DT_CSPlayer", "m_flFlashDuration", flash_duration, float)
	netvar("DT_CSPlayer", "m_flFlashMaxAlpha", flash_alpha, float)
	netvar("DT_CSPlayer", "m_bHasNightVision", m_bHasNightVision, float)
	netvar("DT_CSPlayer", "m_bNightVisionOn", m_bNightVisionOn, float)
	netvar("DT_CSPlayer", "m_iHealth", health, int)
	netvar("DT_CSPlayer", "m_lifeState", life_state, int)
	netvar("DT_CSPlayer", "m_fFlags", flags, int)
	netvar("DT_CSPlayer", "m_nTickBase", get_tick_base, int)
	netvar("DT_CSPlayer", "m_flDuckAmount", duck_amount, float)
	netvar("DT_CSPlayer", "m_bHasHeavyArmor", has_heavy_armor, bool)
	netvar("DT_BasePlayer", "m_hViewModel[0]", view_model, int)
	netvar("DT_BasePlayer", "m_viewPunchAngle", punch_angle, vec3_t)
	netvar("DT_BasePlayer", "m_aimPunchAngle", aim_punch_angle, vec3_t)
	netvar("DT_BasePlayer", "m_vecVelocity[0]", velocity, vec3_t)
	netvar("DT_BasePlayer", "m_flMaxspeed", max_speed, float)
	netvar("DT_BaseEntity", "m_flShadowCastDistance", m_flFOVTime, float)
	netvar("DT_BasePlayer", "m_hObserverTarget", observer_target, unsigned long)
	netvar("DT_BasePlayer", "m_iObserverMode", observer_mode, int)
	netvar("DT_BasePlayer", "m_nHitboxSet", hitbox_set, int)
	netvar("DT_SmokeGrenadeProjectile", "m_nSmokeEffectTickBegin", smoke_grenade_tick_begin, int)

	offset(anim_state*, animstate, 0x3900)
	offset(float, spawn_time, 0xA360)

	virtual_method(vec3_t&, get_abs_origin(), 10, (this))
	virtual_method(void, update_client_side_animations(), 223, (this))
	virtual_method(weapon_t*, active_weapon(), 267, (this))

	player_t* get_observer_target() {
		return reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity_handle(this->observer_target()));;
	}

	vec3_t get_eye_pos() {
		return origin() + view_offset();
	}

	vec3_t get_hitbox_position(int i) {
		if (const auto studio_model = interfaces::model_info->get_studio_model(model())) {
			if (const auto hitbox = studio_model->hitbox_set(0)->hitbox(i)) {
				matrix_t bone_matrix[MAXSTUDIOBONES];

				if (!setup_bones(bone_matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.f))
					return { };

				vec3_t min, max;

				math::transform_vector(hitbox->mins, bone_matrix[hitbox->bone], min);
				math::transform_vector(hitbox->maxs, bone_matrix[hitbox->bone], max);

				return (min + max) * .5f;
			}
		}

		return { };
	}

	bool is_alive() {
		return life_state() == 0;
	}

	bool is_enemy(player_t* target) {
		return this->team() != target->team();
	}
};

class inferno_t : public entity_t {
public:
	offset(float, spawn_time, 0x20)
};