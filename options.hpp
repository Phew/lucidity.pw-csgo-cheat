#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "valve_sdk/Misc/Color.hpp"

class Options
{
public:

	bool enablelgit;
	struct
	{
		struct
		{
			bool Enabled;
			int AimType;
			float Fov;
			float Smooth;
			bool Recoil;
			int Hitbox;
		} Rifles;
		struct
		{
			bool Enabled;
			int AimType;
			float Fov;
			float Smooth;
			bool Recoil;
			int Hitbox;
		} Pistols;
		struct
		{
			bool Enabled;
			int AimType;
			float Fov;
			float Smooth;
			bool Recoil;
			int Hitbox;
		} Snipers;
		bool Backtrack;
		int BacktrackTime = 200.f;
	} aimbot;


	struct
	{
		bool autofire;

		bool rageenable;
		bool pitchresolver;
		bool resolverenable;
		bool autodirection;
		bool resolverenable2;
		bool antiaimenable;
		int pitch;
		int standingaa;
		int movingaa;
		int airaa;

		bool jitterenablestanding;
		bool jitterenablemoving;
		bool jitterenableair;
		int jittervaluestanding;
		int jittervaluemoving;
		int jittervalueair;

		bool desyncenable;
		int desynctype;

		int staticleftsidevalue;
		int staticrightsidevalue;
		int staticinverter;
		int staticjittervalue;

		int left;
		int right;
		int back;
		int front;

		int move_left;
		int move_right;
		int move_back;
		int move_front;

		int air_left;
		int air_right;
		int air_back;
		int air_front;

		int doubletab;
		int fastshoot;


		bool rageautoscope;
		bool rageautostop;
		bool autorevolvo;
		bool autozeus;
		bool autoknife;


		int fakeduckkey;
		bool antifreestanding;
		bool resolver;
		bool baimafter3misses;
		int baimkey;
		bool baimiflethal;
		bool safepoint;

		//auto
		int auto_mindamagevisible;
		int auto_mindamage;
		int auto_hitchance;
		bool auto_multipoint;
		int auto_bodyscale;
		int auto_headscale;
		bool auto_head;
		bool auto_neck;
		bool auto_chest;
		bool auto_body;
		bool auto_stomach;
		bool auto_arms;
		bool auto_pelvis;
		bool auto_legs;
		bool auto_toes;

		//scout
		int scout_mindamagevisible;
		int scout_mindamage;
		int scout_hitchance;
		bool scout_multipoint;
		int scout_bodyscale;
		int scout_headscale;
		bool scout_head;
		bool scout_neck;
		bool scout_chest;
		bool scout_body;
		bool scout_stomach;
		bool scout_arms;
		bool scout_pelvis;
		bool scout_legs;
		bool scout_toes;

		//awp
		int awp_mindamagevisible;
		int awp_mindamage;
		int awp_hitchance;
		bool awp_multipoint;
		int awp_bodyscale;
		int awp_headscale;
		bool awp_head;
		bool awp_neck;
		bool awp_chest;
		bool awp_body;
		bool awp_stomach;
		bool awp_arms;
		bool awp_pelvis;
		bool awp_legs;
		bool awp_toes;

		//heavy_pistol
		int heavy_pistol_mindamagevisible;
		int heavy_pistol_mindamage;
		int heavy_pistol_hitchance;
		bool heavy_pistol_multipoint;
		int heavy_pistol_bodyscale;
		int heavy_pistol_headscale;
		bool heavy_pistol_head;
		bool heavy_pistol_neck;
		bool heavy_pistol_chest;
		bool heavy_pistol_body;
		bool heavy_pistol_stomach;
		bool heavy_pistol_arms;
		bool heavy_pistol_pelvis;
		bool heavy_pistol_legs;
		bool heavy_pistol_toes;

		//other
		int hitchance = 0;
		int minimumdmage = 0;
		int minimumdmagevisible = 0;
		bool multipoint;
		int headscale;
		int bodyscale;
		bool head;
		bool neck;
		bool chest;
		bool body;
		bool stomach;
		bool arms;
		bool pelvis;
		bool legs;
		bool toes;

		int slowwalkkey;
		bool fakeduckenable;
	} rageaimbot;


	struct
	{
		//visuals
		bool drawflags;

		bool VisualsBox = false;
		bool VisualsName = false;
		bool VisualsWeapon = false;
		bool VisualsHealth = false;
		bool VisualsArmor = false;
		bool VisualsSkeleton = false;
		bool VisualsSkeletonHistory = false;



		float boxcolor [ 3 ] = { 1.f, 1.f, 1.f };
		float namecolor [ 3 ] = { 1.f, 1.f, 1.f };
		float weaponcolor [ 3 ] = { 1.f, 1.f, 1.f };
		float healthcolor [ 3 ] = { 1.f, 1.f, 1.f };
		float armorcolor [ 3 ] = { 1.f, 1.f, 1.f };

		float skelecolor [ 3 ] = { 1.f, 1.f, 1.f };
		float skelehistorycolor [ 3 ] = { 1.f, 1.f, 1.f };

		bool droppedweapons;
		bool drawc4;
		bool povarrows;
		bool pwatermark;
		bool drawnades;
		float povarrowscol [ 3 ] = { 1,1,1 };

		bool VisualsChamsEnabled = false;
		float VisualsChamsColor [ 4 ] = { 1.f, 1.f, 1.f, 1.f };
		int VisualsChamsMaterial = 2;
		bool VisualsChamsIgnoreZ = false;
		float VisualsChamsColorIgnoreZ [ 4 ] = { 1.f, 1.f, 1.f , 1.f };

		int VisualsLocalChamsMaterial;
		int VisualsDesyncChamsMaterial;
		int VisualsHandChamsMaterial;
		int VisualsWeaponChamsMaterial;

		bool enemy_layer;
		int enemy_layer_int;
		float enemy_layer_color[ 4 ] = { 1.f, 1.f, 1.f, 1.f, };

		bool desync_layer;
		int desync_layer_material;
		float desync_layer_color[ 4 ] = { 1.f, 1.f, 1.f, 1.f };
		bool indicator;
		bool local_layer;
		int local_layer_material;
		float local_layer_color[ 4 ] = { 1.f, 1.f, 1.f,1.f };

		bool hand_layer;
		int hand_layer_material;
		float hand_layer_color[ 4 ] = { 1.f, 1.f, 1.f,1.f };

		bool desyncchamsenable;
		float localdesynccol [ 4 ] = { 1.f, 1.f, 1.f, 1.f };

		bool enablelocalchams;
		float localchamscol [ 4 ] = { 1.f, 1.f, 1.f, 1.f };

		bool enablehandchams;
		float handchamscol [ 4 ] = { 1.f, 1.f, 1.f, 1.f };

		bool enableweaponchams;
		float weaponchamscol [ 4 ] = { 1.f, 1.f, 1.f, 1.f };
		bool VisualsGlowEnabled = false;

		int VisualsGlowGlowstyle = 0;
		float VisualsGlowColor [ 4 ] = { 1.f, 1.f, 1.f, 1.f };
		//int VisualsGlowAlpha = 255;

		bool VisualsLocalGlowEnabled = false;

		int VisualsLocalGlowGlowstyle = 0;
		float VisualsLocalGlowColor [ 4 ] = { 1.f, 1.f, 1.f, 1.f };
		//int VisualsLocalGlowAlphaz = 255;

		float fieldofview;
		float viewmodelfov;
		float viewmodeloffsetx;
		float viewmodeloffsety;
		float viewmodeloffsetz;
		bool aspectratioenable;
		int aspectratiox;
		int aspectratioxy;

		bool wasdindicator;
		bool playerhitmarker;
		int skychangar;
		bool nightmode;
		bool lagcompydady;
		int hitsound;
		bool greane_prediction;
		bool beams;

		bool selfcircle;

		float markercol [ 3 ] = { 1.f, 1.f, 1.f };
		float beamcolor [ 3 ] = { 1.f, 1.f, 1.f };


		bool infobar;
		int infobarx;
		int infobary;

		bool miscbar;
		int miscbarx;
		int miscbary;
		bool preservekillfeed;
		bool kill_effect;
		bool VisualsNoScope = false;
		bool nopostprocsess;
		bool novisrecoil;
		bool nosmoke;
		bool noflash;
	} Visuals;

	struct
	{
		int MiscFakelagChoke = 0;




		bool bhop;
		bool autostrafe;
		bool serverhitboxes;
		bool eventlogs;

		bool slowwalk;
		int slowwalkspeed;
		char config_name [ 52 ];
		int config_selection;
		char configname [ 128 ];
	} Misc;

	struct
	{
		bool Enabled;
		//knife
		int weapoinzz;
		int Knife;

		int customidknife;

		int customidusp;
		int customidp2000;
		int customidglock18;
		int customiddeagle;
		int customidrevolver;
		int customidawp;
		int customidssg08;
		int customiddual;
		int customidp250;
		int customidcz75;
		int customidfive7;
		int customidtec9;
		int customidnova;
		int customidxm1014;
		int customidmag7;
		int customidsawedoff;
		int customidnegev;
		int customidm249;
		int customidmp9;
		int customidmac10;
		int customidmp7;
		int customidump45;
		int customidp90;
		int customidppbizon;
		int customidGalil;
		int customidfamas;
		int customidm4a4;
		int customidm4a1;
		int customidak47;
		int customidaug;
		int customidsg553;
		int customidscar20;
		int customidg3sg1;
		int customidmp5;

	} Skinchanger;

	//misc
	//skins
	float menucolor [ 3 ] = { 0.00f, 0.29f, 1.00f };



	//menu
	int ConfigFile = 0;


	int menustyle = 3;


	bool Save( std::string file_name );
	bool Load( std::string file_name );
	void CreateConfig( std::string name );
	void Delete( std::string name );
	std::vector<std::string> GetConfigs( );

};
inline Options Variables;
