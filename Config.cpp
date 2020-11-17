#include "config.hpp"
#include <winerror.h>
#pragma warning( disable : 4091)
#include <ShlObj.h>
#include <string>
#include <sstream>

const char* GetWeaponNames( int id )
{
	switch ( id )
	{
	case 1:
		return "deagle";
	case 2:
		return "elite";
	case 3:
		return "fiveseven";
	case 4:
		return "glock";
	case 7:
		return "ak47";
	case 8:
		return "aug";
	case 9:
		return "awp";
	case 10:
		return "famas";
	case 11:
		return "g3sg1";
	case 13:
		return "galilar";
	case 14:
		return "m249";
	case 60:
		return "m4a1_silencer";
	case 16:
		return "m4a1";
	case 17:
		return "mac10";
	case 19:
		return "p90";
	case 24:
		return "ump45";
	case 25:
		return "xm1014";
	case 26:
		return "bizon";
	case 27:
		return "mag7";
	case 28:
		return "negev";
	case 29:
		return "sawedoff";
	case 30:
		return "tec9";
	case 32:
		return "hkp2000";
	case 33:
		return "mp7";
	case 34:
		return "mp9";
	case 35:
		return "nova";
	case 36:
		return "p250";
	case 38:
		return "scar20";
	case 39:
		return "sg556";
	case 40:
		return "ssg08";
	case 61:
		return "usp_silencer";
	case 63:
		return "cz75a";
	case 64:
		return "revolver";
	case 508:
		return "knife_m9_bayonet";
	case 500:
		return "bayonet";
	case 505:
		return "knife_flip";
	case 506:
		return "knife_gut";
	case 507:
		return "knife_karambit";
	case 509:
		return "knife_tactical";
	case 512:
		return "knife_falchion";
	case 514:
		return "knife_survival_bowie";
	case 515:
		return "knife_butterfly";
	case 516:
		return "knife_push";
	case 517:
		return "knife_cord";
	case 518:
		return "knife_canis";
	case 519:
		return "knife_ursus";
	case 520:
		return "knife_gypsy_jackknife";
	case 522:
		return "knife_stiletto";
	case 521:
		return "knife_outdoor";
	case 523:
		return "knife_widowmaker";
	case 525:
		return "knife_skeleton";


	default:
		return "";
	}
}

void c_config::setup( )
{
	//ragebot
	SetupValue( Variables.rageaimbot.rageenable, false, ("Ragebot"), ("Enable") );
	SetupValue( Variables.rageaimbot.autofire, false, ("Ragebot"), ("Autoshoot") );
	SetupValue( Variables.rageaimbot.doubletab, 0, ("Ragebot"), ("doubletab") );
	SetupValue( Variables.rageaimbot.fastshoot, 0, ("Ragebot"), ("Dtkey") );
	SetupValue( Variables.rageaimbot.autozeus, false, ("Ragebot"), ("autozeus") );
	SetupValue( Variables.rageaimbot.autoknife, false, ("Ragebot"), ("autoknife") );
	SetupValue( Variables.rageaimbot.autorevolvo, false, ("Ragebot"), ("autorevolvo") );
	SetupValue( Variables.rageaimbot.rageautoscope, false, ("Ragebot"), ("rageautoscope") );
	SetupValue( Variables.rageaimbot.rageautostop, false, ("Ragebot"), ("rageautostop") );

	SetupValue( Variables.rageaimbot.safepoint, false, ("Ragebot"), ("safepoint") );
	SetupValue( Variables.rageaimbot.baimiflethal, false, ("Ragebot"), ("baimiflethal") );
	SetupValue( Variables.rageaimbot.baimiflethal, false, ("Ragebot"), ("baimiflethal") );
	SetupValue( Variables.rageaimbot.baimkey, 0, ("Ragebot"), ("baimkey") );

	//ragebot weapon config 
	//auto
	SetupValue( Variables.rageaimbot.auto_multipoint, false, ("Ragebot"), ("auto_multipoint") );
	SetupValue( Variables.rageaimbot.auto_bodyscale, 0, ("Ragebot"), ("auto_bodyscale") );
	SetupValue( Variables.rageaimbot.auto_headscale, 0, ("Ragebot"), ("auto_headscale") );
	SetupValue( Variables.rageaimbot.auto_hitchance, 0, ("Ragebot"), ("auto_hitchance") );
	SetupValue( Variables.rageaimbot.auto_mindamage, 0, ("Ragebot"), ("auto_minimumdmage") );
	SetupValue( Variables.rageaimbot.auto_mindamagevisible, 0, ("Ragebot"), ("auto_minimumdmagevisible") );
	SetupValue( Variables.rageaimbot.auto_head, false, ("Ragebot"), ("auto_head") );
	SetupValue( Variables.rageaimbot.auto_neck, false, ("Ragebot"), ("auto_neck") );
	SetupValue( Variables.rageaimbot.auto_chest, false, ("Ragebot"), ("auto_chest") );
	SetupValue( Variables.rageaimbot.auto_arms, false, ("Ragebot"), ("auto_arms") );
	SetupValue( Variables.rageaimbot.auto_stomach, false, ("Ragebot"), ("auto_stomach") );
	SetupValue( Variables.rageaimbot.auto_pelvis, false, ("Ragebot"), ("auto_pelvis") );
	SetupValue( Variables.rageaimbot.auto_body, false, ("Ragebot"), ("auto_body") );
	SetupValue( Variables.rageaimbot.auto_legs, false, ("Ragebot"), ("auto_legs") );
	SetupValue( Variables.rageaimbot.auto_toes, false, ("Ragebot"), ("auto_toes") );

	//scout
	SetupValue( Variables.rageaimbot.scout_multipoint, false, ("Ragebot"), ("scout_multipoint") );
	SetupValue( Variables.rageaimbot.scout_bodyscale, 0, ("Ragebot"), ("scout_bodyscale") );
	SetupValue( Variables.rageaimbot.scout_headscale, 0, ("Ragebot"), ("scout_headscale") );
	SetupValue( Variables.rageaimbot.scout_hitchance, 0, ("Ragebot"), ("scout_hitchance") );
	SetupValue( Variables.rageaimbot.scout_mindamage, 0, ("Ragebot"), ("scout_minimumdmage") );
	SetupValue( Variables.rageaimbot.scout_mindamagevisible, 0, ("Ragebot"), ("scout_minimumdmagevisible") );
	SetupValue( Variables.rageaimbot.scout_head, false, ("Ragebot"), ("scout_head") );
	SetupValue( Variables.rageaimbot.scout_neck, false, ("Ragebot"), ("scout_neck") );
	SetupValue( Variables.rageaimbot.scout_chest, false, ("Ragebot"), ("scout_chest") );
	SetupValue( Variables.rageaimbot.scout_arms, false, ("Ragebot"), ("scout_arms") );
	SetupValue( Variables.rageaimbot.scout_stomach, false, ("Ragebot"), ("scout_stomach") );
	SetupValue( Variables.rageaimbot.scout_pelvis, false, ("Ragebot"), ("scout_pelvis") );
	SetupValue( Variables.rageaimbot.scout_body, false, ("Ragebot"), ("scout_body") );
	SetupValue( Variables.rageaimbot.scout_legs, false, ("Ragebot"), ("scout_legs") );
	SetupValue( Variables.rageaimbot.scout_toes, false, ("Ragebot"), ("scout_toes") );

	//awp
	SetupValue( Variables.rageaimbot.awp_multipoint, false, ("Ragebot"), ("awp_multipoint") );
	SetupValue( Variables.rageaimbot.awp_bodyscale, 0, ("Ragebot"), ("awp_bodyscale") );
	SetupValue( Variables.rageaimbot.awp_headscale, 0, ("Ragebot"), ("awp_headscale") );
	SetupValue( Variables.rageaimbot.awp_hitchance, 0, ("Ragebot"), ("awp_hitchance") );
	SetupValue( Variables.rageaimbot.awp_mindamage, 0, ("Ragebot"), ("awp_minimumdmage") );
	SetupValue( Variables.rageaimbot.awp_mindamagevisible, 0, ("Ragebot"), ("awp_minimumdmagevisible") );
	SetupValue( Variables.rageaimbot.awp_head, false, ("Ragebot"), ("awp_head") );
	SetupValue( Variables.rageaimbot.awp_neck, false, ("Ragebot"), ("awp_neck") );
	SetupValue( Variables.rageaimbot.awp_chest, false, ("Ragebot"), ("awp_chest") );
	SetupValue( Variables.rageaimbot.awp_arms, false, ("Ragebot"), ("awp_arms") );
	SetupValue( Variables.rageaimbot.awp_stomach, false, ("Ragebot"), ("awp_stomach") );
	SetupValue( Variables.rageaimbot.awp_pelvis, false, ("Ragebot"), ("awp_pelvis") );
	SetupValue( Variables.rageaimbot.awp_body, false, ("Ragebot"), ("awp_body") );
	SetupValue( Variables.rageaimbot.awp_legs, false, ("Ragebot"), ("awp_legs") );
	SetupValue( Variables.rageaimbot.awp_toes, false, ("Ragebot"), ("awp_toes") );

	//heavy_pistol
	SetupValue( Variables.rageaimbot.heavy_pistol_multipoint, false, ("Ragebot"), ("heavy_pistol_multipoint") );
	SetupValue( Variables.rageaimbot.heavy_pistol_bodyscale, 0, ("Ragebot"), ("heavy_pistol_bodyscale") );
	SetupValue( Variables.rageaimbot.heavy_pistol_headscale, 0, ("Ragebot"), ("heavy_pistol_headscale") );
	SetupValue( Variables.rageaimbot.heavy_pistol_hitchance, 0, ("Ragebot"), ("heavy_pistol_hitchance") );
	SetupValue( Variables.rageaimbot.heavy_pistol_mindamage, 0, ("Ragebot"), ("heavy_pistol_minimumdmage") );
	SetupValue( Variables.rageaimbot.heavy_pistol_mindamagevisible, 0, ("Ragebot"), ("heavy_pistol_minimumdmagevisible") );
	SetupValue( Variables.rageaimbot.heavy_pistol_head, false, ("Ragebot"), ("heavy_pistol_head") );
	SetupValue( Variables.rageaimbot.heavy_pistol_neck, false, ("Ragebot"), ("heavy_pistol_neck") );
	SetupValue( Variables.rageaimbot.heavy_pistol_chest, false, ("Ragebot"), ("heavy_pistol_chest") );
	SetupValue( Variables.rageaimbot.heavy_pistol_arms, false, ("Ragebot"), ("heavy_pistol_arms") );
	SetupValue( Variables.rageaimbot.heavy_pistol_stomach, false, ("Ragebot"), ("heavy_pistol_stomach") );
	SetupValue( Variables.rageaimbot.heavy_pistol_pelvis, false, ("Ragebot"), ("heavy_pistol_pelvis") );
	SetupValue( Variables.rageaimbot.heavy_pistol_body, false, ("Ragebot"), ("heavy_pistol_body") );
	SetupValue( Variables.rageaimbot.heavy_pistol_legs, false, ("Ragebot"), ("heavy_pistol_legs") );
	SetupValue( Variables.rageaimbot.heavy_pistol_toes, false, ("Ragebot"), ("heavy_pistol_toes") );

	//other
	SetupValue( Variables.rageaimbot.multipoint, false, ("Ragebot"), ("multipoint") );
	SetupValue( Variables.rageaimbot.bodyscale, 0, ("Ragebot"), ("bodyscale") );
	SetupValue( Variables.rageaimbot.headscale, 0, ("Ragebot"), ("headscale") );
	SetupValue( Variables.rageaimbot.hitchance, 0, ("Ragebot"), ("hitchance") );
	SetupValue( Variables.rageaimbot.minimumdmage, 0, ("Ragebot"), ("minimumdmage") );
	SetupValue( Variables.rageaimbot.minimumdmagevisible, 0, ("Ragebot"), ("minimumdmagevisible") );
	SetupValue( Variables.rageaimbot.head, false, ("Ragebot"), ("head") );
	SetupValue( Variables.rageaimbot.neck, false, ("Ragebot"), ("neck") );
	SetupValue( Variables.rageaimbot.chest, false, ("Ragebot"), ("chest") );
	SetupValue( Variables.rageaimbot.arms, false, ("Ragebot"), ("arms") );
	SetupValue( Variables.rageaimbot.stomach, false, ("Ragebot"), ("stomach") );
	SetupValue( Variables.rageaimbot.pelvis, false, ("Ragebot"), ("pelvis") );
	SetupValue( Variables.rageaimbot.body, false, ("Ragebot"), ("body") );
	SetupValue( Variables.rageaimbot.legs, false, ("Ragebot"), ("legs") );
	SetupValue( Variables.rageaimbot.toes, false, ("Ragebot"), ("toes") );

	SetupValue( Variables.Visuals.enemy_layer, false, ( "Visuals"), ("enemy_layer" ) );
	SetupValue( Variables.Visuals.enemy_layer_int, 0, ( "Visuals" ), ( "enemymaterial" ) );

	SetupValue( Variables.Visuals.desync_layer, false, ( "Visuals" ), ( "enemwqey_lwayer" ) );
	SetupValue( Variables.Visuals.desync_layer_material, 0, ( "Visuals" ), ( "enemweymawqeqterial" ) );

	SetupValue( Variables.Visuals.local_layer, false, ( "Visuals" ), ( "locallaer" ) );
	SetupValue( Variables.Visuals.local_layer_material, 0, ( "Visuals" ), ( "localmaterual" ) );

	SetupValue( Variables.Visuals.enemy_layer_color[ 0 ], 1.f, ( "ChamsColor" ), ( "VisualswqdChamsColorIgnoreZ_r" ) );
	SetupValue( Variables.Visuals.enemy_layer_color[ 1 ], 1.f, ( "ChamsColor" ), ( "VisueqwalsqweqChamsColorIgnoreZ_g" ) );
	SetupValue( Variables.Visuals.enemy_layer_color[ 2 ], 1.f, ( "ChamsColor" ), ( "VisueqwealsChamwqesColorIgnoreZ_b" ) );
	SetupValue( Variables.Visuals.enemy_layer_color[ 3 ], 1.f, ( "ChamsColor" ), ( "VisualsCwqeqhamsColorIgnoreZ_a" ) );

	SetupValue( Variables.Visuals.desync_layer_color[ 0 ], 1.f, ( "ChamsColor" ), ( "wqe" ) );
	SetupValue( Variables.Visuals.desync_layer_color[ 1 ], 1.f, ( "ChamsColor" ), ( "dqwdq" ) );
	SetupValue( Variables.Visuals.desync_layer_color[ 2 ], 1.f, ( "ChamsColor" ), ( "wqeq" ) );
	SetupValue( Variables.Visuals.desync_layer_color[ 3 ], 1.f, ( "ChamsColor" ), ( "weqfq" ) );

	SetupValue( Variables.Visuals.local_layer_color[ 0 ], 1.f, ( "ChamsColor" ), ( "wqw32qe21e" ) );
	SetupValue( Variables.Visuals.local_layer_color[ 2 ], 1.f, ( "ChamsColor" ), ( "wqe322w" ) );
	SetupValue( Variables.Visuals.local_layer_color[ 3 ], 1.f, ( "ChamsColor" ), ( "weqw12331fq" ) );


	//antiaim
	SetupValue( Variables.rageaimbot.antiaimenable, false, ("AntiAim"), ("Enable") );
	SetupValue( Variables.rageaimbot.pitch, 0, ("AntiAim"), ("pitch") );
	//standing
	SetupValue( Variables.rageaimbot.standingaa, 0, ("AntiAim"), ("standingaa") );
	SetupValue( Variables.rageaimbot.jitterenablestanding, false, ("AntiAim"), ("jitterenablestanding") );
	SetupValue( Variables.rageaimbot.jittervaluestanding, 0, ("AntiAim"), ("jittervaluestanding") );
	//moving
	SetupValue( Variables.rageaimbot.movingaa, 0, ("AntiAim"), ("movingaa") );
	SetupValue( Variables.rageaimbot.jitterenablemoving, false, ("AntiAim"), ("jitterenablemoving") );
	SetupValue( Variables.rageaimbot.jittervaluemoving, 0, ("AntiAim"), ("jittervaluemoving") );
	//air
	SetupValue( Variables.rageaimbot.airaa, 0, ("AntiAim"), ("airaa") );
	SetupValue( Variables.rageaimbot.jitterenableair, false, ("AntiAim"), ("jitterenableair") );
	SetupValue( Variables.rageaimbot.jittervalueair, 0, ("AntiAim"), ("jittervalueair") );
	//desync antiaim
	SetupValue( Variables.rageaimbot.desynctype, 0, ("AntiAim"), ("desynctype") );
	//bodylean jitter and inverter key
	SetupValue( Variables.rageaimbot.staticinverter, 0, ("AntiAim"), ("staticinverter") );
	SetupValue( Variables.rageaimbot.staticrightsidevalue, 0, ("AntiAim"), ("staticrightsidevalue") );
	SetupValue( Variables.rageaimbot.staticleftsidevalue, 0, ("AntiAim"), ("staticleftsidevalue") );
	SetupValue( Variables.rageaimbot.staticjittervalue, 0, ("AntiAim"), ("staticjittervalue") );
	//manual aa
	SetupValue( Variables.rageaimbot.left, 0, ("AntiAim"), ("left") );
	SetupValue( Variables.rageaimbot.right, 0, ("AntiAim"), ("right") );
	SetupValue( Variables.rageaimbot.back, 0, ("AntiAim"), ("back") );
	SetupValue( Variables.rageaimbot.front, 0, ("AntiAim"), ("front") );
	//flag misc
	//slowwalk
	SetupValue( Variables.Misc.slowwalk, false, ("Misc"), ("slowwalk") );
	SetupValue( Variables.Misc.slowwalkspeed, 0, ("Misc"), ("slowwalkspeed") );
	//fakelag
	SetupValue( Variables.Misc.MiscFakelagChoke, 0, ("Misc"), ("MiscFakelagChoke") );
	SetupValue( Variables.rageaimbot.fakeduckkey, 0, ("Misc"), ("fakeduckkey") );




	//legitbot
	SetupValue( Variables.enablelgit, false, ("Legit"), ("Enable") );
	SetupValue( Variables.aimbot.Backtrack, false, ("Legit"), ("Backtrack") );
	SetupValue( Variables.aimbot.BacktrackTime, 0, ("Legit"), ("bttime") );
	//weapon cfgs //snipers
	SetupValue( Variables.aimbot.Snipers.Enabled, false, ("Legit"), ("SnipersEnabled") );
	SetupValue( Variables.aimbot.Snipers.Recoil, false, ("Legit"), ("SnipersRecoil") );
	SetupValue( Variables.aimbot.Snipers.AimType, 0, ("Legit"), ("SnipersAimType") );
	SetupValue( Variables.aimbot.Snipers.Fov, 0, ("Legit"), ("SnipersFov") );
	SetupValue( Variables.aimbot.Snipers.Hitbox, 0, ("Legit"), ("SnipersHitbox") );
	//pistols
	SetupValue( Variables.aimbot.Pistols.Enabled, false, ("Legit"), ("PistolsEnabled") );
	SetupValue( Variables.aimbot.Pistols.Recoil, false, ("Legit"), ("PistolsRecoil") );
	SetupValue( Variables.aimbot.Pistols.AimType, 0, ("Legit"), ("PistolsAimType") );
	SetupValue( Variables.aimbot.Pistols.Fov, 0, ("Legit"), ("PistolsFov") );
	SetupValue( Variables.aimbot.Pistols.Hitbox, 0, ("Legit"), ("PistolsHitbox") );
	//rifle
	SetupValue( Variables.aimbot.Rifles.Enabled, false, ("Legit"), ("RiflesEnabled") );
	SetupValue( Variables.aimbot.Rifles.Recoil, false, ("Legit"), ("RiflesRecoil") );
	SetupValue( Variables.aimbot.Rifles.AimType, 0, ("Legit"), ("RiflesAimType") );
	SetupValue( Variables.aimbot.Rifles.Fov, 0, ("Legit"), ("RiflesFov") );
	SetupValue( Variables.aimbot.Rifles.Hitbox, 0, ("Legit"), ("RiflesHitbox") );





	//visuals players 
	SetupValue( Variables.Visuals.VisualsBox, false, ("Visuals"), ("VisualsBox") );
	SetupValue( Variables.Visuals.VisualsName, false, ("Visuals"), ("VisualsName") );
	SetupValue( Variables.Visuals.VisualsHealth, false, ("Visuals"), ("VisualsHealth") );
	SetupValue( Variables.Visuals.VisualsArmor, false, ("Visuals"), ("VisualsArmor") );
	SetupValue( Variables.Visuals.VisualsWeapon, false, ("Visuals"), ("VisualsWeapon") );
	SetupValue( Variables.Visuals.VisualsSkeleton, false, ("Visuals"), ("VisualsSkeleton") );
	SetupValue( Variables.Visuals.drawflags, false, ("Visuals"), ("drawflags") );
	SetupValue( Variables.Visuals.VisualsSkeletonHistory, false, ("Visuals"), ("VisualsSkeletonHistory") );


	//world
	SetupValue( Variables.Visuals.skychangar, 0, ("Visuals"), ("skychangar") );
	SetupValue( Variables.Visuals.nightmode, false, ("Visuals"), ("nightmode") );
	SetupValue( Variables.Visuals.playerhitmarker, false, ("Visuals"), ("playerhitmarker") );
	SetupValue( Variables.Visuals.greane_prediction, false, ("Visuals"), ("greane_prediction") );
	SetupValue( Variables.Visuals.beams, false, ("Visuals"), ("beams") );
	SetupValue( Variables.Visuals.lagcompydady, false, ("Visuals"), ("lagcompydady") );
	SetupValue( Variables.Visuals.selfcircle, false, ("Visuals"), ("selfcircle") );
	//helpers
	SetupValue( Variables.Visuals.drawc4, 0, ("Visuals"), ("drawc4") );
	SetupValue( Variables.Visuals.drawnades, false, ("Visuals"), ("drawnades") );
	SetupValue( Variables.Visuals.droppedweapons, false, ("Visuals"), ("droppedweapons") );
	SetupValue( Variables.Visuals.povarrows, false, ("Visuals"), ("povarrows") );
	//misc visuals
	SetupValue( Variables.Visuals.wasdindicator, false, ("Visuals"), ("wasdindicator") );
	SetupValue( Variables.Visuals.infobar, false, ("Visuals"), ("infobar") );
	SetupValue( Variables.Visuals.infobarx, 0, ("Visuals"), ("infobarx") );
	SetupValue( Variables.Visuals.infobary, 0, ("Visuals"), ("infobary") );
	SetupValue( Variables.Visuals.miscbar, false, ("Visuals"), ("miscbar") );
	SetupValue( Variables.Visuals.kill_effect, false, ("Visuals"), ("kill_effect") );
	SetupValue( Variables.Visuals.miscbarx, 0, ("Visuals"), ("miscbarx") );
	SetupValue( Variables.Visuals.miscbary, 0, ("Visuals"), ("miscbary") );
	SetupValue( Variables.Visuals.preservekillfeed, false, ("Misc"), ("preservekillfeed") );

	//removals
	SetupValue( Variables.Visuals.novisrecoil, false, ("Visuals"), ("novisrecoil") );
	SetupValue( Variables.Visuals.nopostprocsess, false, ("Visuals"), ("nopostprocsess") );
	SetupValue( Variables.Visuals.VisualsNoScope, false, ("Visuals"), ("VisualsNoScope") );
	SetupValue( Variables.Visuals.nosmoke, false, ("Visuals"), ("nosmoke") );
	SetupValue( Variables.Visuals.noflash, false, ("Visuals"), ("noflash") );



	//misc
	SetupValue( Variables.Misc.bhop, false, ("Misc"), ("bhop") );
	SetupValue( Variables.Misc.autostrafe, false, ("Misc"), ("autostrafe") );
	SetupValue( Variables.Misc.serverhitboxes, false, ("Misc"), ("serverhitboxes") );
	SetupValue( Variables.Misc.eventlogs, false, ("Misc"), ("eventlogs") );
	SetupValue( Variables.Visuals.hitsound, 0, ("Misc"), ("hitsound") );
	//viewmodel changer
	SetupValue( Variables.Visuals.fieldofview, 0, ("Visuals"), ("fieldofview") );
	SetupValue( Variables.Visuals.viewmodelfov, 0, ("Visuals"), ("viewmodelfov") );
	SetupValue( Variables.Visuals.viewmodeloffsetx, 0, ("Visuals"), ("viewmodeloffsetx") );
	SetupValue( Variables.Visuals.viewmodeloffsety, 0, ("Visuals"), ("viewmodeloffsety") );
	SetupValue( Variables.Visuals.viewmodeloffsetz, 0, ("Visuals"), ("viewmodeloffsetz") );
	//aspect ratio changer
	SetupValue( Variables.Visuals.aspectratioenable, false, ("Visuals"), ("aspectratioenable") );
	SetupValue( Variables.Visuals.aspectratiox, 0, ("Visuals"), ("aspectratiox") );
	SetupValue( Variables.Visuals.aspectratioxy, 0, ("Visuals"), ("aspectratioxy") );





	//chams //enemy
	SetupValue( Variables.Visuals.VisualsChamsEnabled, false, ("Visuals"), ("VisualsChamsEnabled") );
	SetupValue( Variables.Visuals.VisualsChamsIgnoreZ, false, ("Visuals"), ("VisualsChamsIgnoreZ") );
	SetupValue( Variables.Visuals.VisualsChamsMaterial, 0, ("Visuals"), ("VisualsChamsMaterial") );
	//local
	SetupValue( Variables.Visuals.enablelocalchams, false, ("Visuals"), ("enablelocalchams") );
	SetupValue( Variables.Visuals.VisualsLocalChamsMaterial, 0, ("Visuals"), ("VisualsLocalChamsMaterial") );
	//desync
	SetupValue( Variables.Visuals.desyncchamsenable, false, ("Visuals"), ("desyncchamsenable") );
	SetupValue( Variables.Visuals.VisualsDesyncChamsMaterial, 0, ("Visuals"), ("VisualsDesyncChamsMaterial") );
	//weapon
	SetupValue( Variables.Visuals.enableweaponchams, false, ("Visuals"), ("weaponchamsenable") );
	SetupValue( Variables.Visuals.VisualsWeaponChamsMaterial, 0, ("Visuals"), ("VisualsweaponChamsMaterial") );
	//hand
	SetupValue( Variables.Visuals.enablehandchams, false, ("Visuals"), ("handchamsenable") );
	SetupValue( Variables.Visuals.VisualsHandChamsMaterial, 0, ("Visuals"), ("VisualsHandChamsMaterial") );



	//glow //enemy
	SetupValue( Variables.Visuals.VisualsGlowEnabled, false, ("Visuals"), ("VisualsGlowEnabled") );
	SetupValue( Variables.Visuals.VisualsGlowGlowstyle, 0, ("Visuals"), ("VisualsGlowGlowstyle") );
	//local
	SetupValue( Variables.Visuals.VisualsLocalGlowEnabled, false, ("Visuals"), ("VisualsLocalGlowEnabled") );
	SetupValue( Variables.Visuals.VisualsLocalGlowGlowstyle, 0, ("Visuals"), ("VisualsLocalGlowGlowstyle") );





	//colors //box
	SetupValue( Variables.Visuals.boxcolor [ 0 ], 1.f, ("VisualsColor"), ("boxcolor_r") );
	SetupValue( Variables.Visuals.boxcolor [ 1 ], 1.f, ("VisualsColor"), ("boxcolor_g") );
	SetupValue( Variables.Visuals.boxcolor [ 2 ], 1.f, ("VisualsColor"), ("boxcolor_b") );
	//name
	SetupValue( Variables.Visuals.namecolor [ 0 ], 1.f, ("VisualsColor"), ("namecolor_r") );
	SetupValue( Variables.Visuals.namecolor [ 1 ], 1.f, ("VisualsColor"), ("namecolor_g") );
	SetupValue( Variables.Visuals.namecolor [ 2 ], 1.f, ("VisualsColor"), ("namecolor_b") );
	//health
	SetupValue( Variables.Visuals.healthcolor [ 0 ], 1.f, ("VisualsColor"), ("healthcolor_r") );
	SetupValue( Variables.Visuals.healthcolor [ 1 ], 1.f, ("VisualsColor"), ("healthcolor_g") );
	SetupValue( Variables.Visuals.healthcolor [ 2 ], 1.f, ("VisualsColor"), ("healthcolor_b") );
	//armor
	SetupValue( Variables.Visuals.armorcolor [ 0 ], 1.f, ("VisualsColor"), ("armorcolor_r") );
	SetupValue( Variables.Visuals.armorcolor [ 1 ], 1.f, ("VisualsColor"), ("armorcolor_g") );
	SetupValue( Variables.Visuals.armorcolor [ 2 ], 1.f, ("VisualsColor"), ("armorcolor_b") );
	//weapon
	SetupValue( Variables.Visuals.weaponcolor [ 0 ], 1.f, ("VisualsColor"), ("weaponcolor_r") );
	SetupValue( Variables.Visuals.weaponcolor [ 1 ], 1.f, ("VisualsColor"), ("weaponcolor_g") );
	SetupValue( Variables.Visuals.weaponcolor [ 2 ], 1.f, ("VisualsColor"), ("weaponcolor_b") );
	//skeleton
	SetupValue( Variables.Visuals.skelecolor [ 0 ], 1.f, ("VisualsColor"), ("skelecolor_r") );
	SetupValue( Variables.Visuals.skelecolor [ 1 ], 1.f, ("VisualsColor"), ("skelecolor_g") );
	SetupValue( Variables.Visuals.skelecolor [ 2 ], 1.f, ("VisualsColor"), ("skelecolor_b") );

	SetupValue( Variables.Visuals.skelehistorycolor [ 0 ], 1.f, ("VisualsColor"), ("skelehistorycolor_r") );
	SetupValue( Variables.Visuals.skelehistorycolor [ 1 ], 1.f, ("VisualsColor"), ("skelehistorycolor_g") );
	SetupValue( Variables.Visuals.skelehistorycolor [ 2 ], 1.f, ("VisualsColor"), ("skelehistorycolor_b") );
	//marker
	SetupValue( Variables.Visuals.markercol [ 0 ], 1.f, ("VisualsColor"), ("markercol_r") );
	SetupValue( Variables.Visuals.markercol [ 1 ], 1.f, ("VisualsColor"), ("markercol_g") );
	SetupValue( Variables.Visuals.markercol [ 2 ], 1.f, ("VisualsColor"), ("markercol_b") );
	//beam
	SetupValue( Variables.Visuals.beamcolor [ 0 ], 1.f, ("VisualsColor"), ("beamcolor_r") );
	SetupValue( Variables.Visuals.beamcolor [ 1 ], 1.f, ("VisualsColor"), ("beamcolor_g") );
	SetupValue( Variables.Visuals.beamcolor [ 2 ], 1.f, ("VisualsColor"), ("beamcolor_b") );
	//povarrow
	SetupValue( Variables.Visuals.povarrowscol [ 0 ], 1.f, ("VisualsColor"), ("povarrowscol_r") );
	SetupValue( Variables.Visuals.povarrowscol [ 1 ], 1.f, ("VisualsColor"), ("povarrowscol_g") );
	SetupValue( Variables.Visuals.povarrowscol [ 2 ], 1.f, ("VisualsColor"), ("povarrowscol_b") );

	//chamscolor //enemy
	SetupValue( Variables.Visuals.VisualsChamsColor [ 0 ], 1.f, ("ChamsColor"), ("VisualsChamsColor_r") );
	SetupValue( Variables.Visuals.VisualsChamsColor [ 1 ], 1.f, ("ChamsColor"), ("VisualsChamsColor_g") );
	SetupValue( Variables.Visuals.VisualsChamsColor [ 2 ], 1.f, ("ChamsColor"), ("VisualsChamsColor_b") );
	SetupValue( Variables.Visuals.VisualsChamsColor [ 3 ], 1.f, ("ChamsColor"), ("VisualsChamsColor_a") );

	SetupValue( Variables.Visuals.VisualsChamsColorIgnoreZ [ 0 ], 1.f, ("ChamsColor"), ("VisualsChamsColorIgnoreZ_r") );
	SetupValue( Variables.Visuals.VisualsChamsColorIgnoreZ [ 1 ], 1.f, ("ChamsColor"), ("VisualsChamsColorIgnoreZ_g") );
	SetupValue( Variables.Visuals.VisualsChamsColorIgnoreZ [ 2 ], 1.f, ("ChamsColor"), ("VisualsChamsColorIgnoreZ_b") );
	SetupValue( Variables.Visuals.VisualsChamsColorIgnoreZ [ 3 ], 1.f, ("ChamsColor"), ("VisualsChamsColorIgnoreZ_a") );
	//local
	SetupValue( Variables.Visuals.localchamscol [ 0 ], 1.f, ("ChamsColor"), ("localchamscol_r") );
	SetupValue( Variables.Visuals.localchamscol [ 1 ], 1.f, ("ChamsColor"), ("localchamscol_g") );
	SetupValue( Variables.Visuals.localchamscol [ 2 ], 1.f, ("ChamsColor"), ("localchamscol_b") );
	SetupValue( Variables.Visuals.localchamscol [ 3 ], 1.f, ("ChamsColor"), ("localchamscol_a") );
	//desync
	SetupValue( Variables.Visuals.localdesynccol [ 0 ], 1.f, ("ChamsColor"), ("localdesynccol_r") );
	SetupValue( Variables.Visuals.localdesynccol [ 1 ], 1.f, ("ChamsColor"), ("localdesynccol_g") );
	SetupValue( Variables.Visuals.localdesynccol [ 2 ], 1.f, ("ChamsColor"), ("localdesynccol_b") );
	SetupValue( Variables.Visuals.localdesynccol [ 3 ], 1.f, ("ChamsColor"), ("localdesynccol_a") );
	//hand
	SetupValue( Variables.Visuals.handchamscol [ 0 ], 1.f, ("ChamsColor"), ("handchamscol_r") );
	SetupValue( Variables.Visuals.handchamscol [ 1 ], 1.f, ("ChamsColor"), ("handchamscol_g") );
	SetupValue( Variables.Visuals.handchamscol [ 2 ], 1.f, ("ChamsColor"), ("handchamscol_b") );
	SetupValue( Variables.Visuals.handchamscol [ 3 ], 1.f, ("ChamsColor"), ("handchamscol_a") );
	//weapon
	SetupValue( Variables.Visuals.weaponchamscol [ 0 ], 1.f, ("ChamsColor"), ("weaponchamscol_r") );
	SetupValue( Variables.Visuals.weaponchamscol [ 1 ], 1.f, ("ChamsColor"), ("weaponchamscol_g") );
	SetupValue( Variables.Visuals.weaponchamscol [ 2 ], 1.f, ("ChamsColor"), ("weaponchamscol_b") );
	SetupValue( Variables.Visuals.weaponchamscol [ 3 ], 1.f, ("ChamsColor"), ("weaponchamscol_a") );


	//glowcolor //enemy
	SetupValue( Variables.Visuals.VisualsGlowColor [ 0 ], 1.f, ("GlowColor"), ("VisualsGlowColor_r") );
	SetupValue( Variables.Visuals.VisualsGlowColor [ 1 ], 1.f, ("GlowColor"), ("VisualsGlowColor_g") );
	SetupValue( Variables.Visuals.VisualsGlowColor [ 2 ], 1.f, ("GlowColor"), ("VisualsGlowColor_b") );
	SetupValue( Variables.Visuals.VisualsGlowColor [ 3 ], 1.f, ("GlowColor"), ("VisualsGlowColor_a") );
	//local
	SetupValue( Variables.Visuals.VisualsLocalGlowColor [ 0 ], 1.f, ("GlowColor"), ("VisualsLocalGlowColor_r") );
	SetupValue( Variables.Visuals.VisualsLocalGlowColor [ 1 ], 1.f, ("GlowColor"), ("VisualsLocalGlowColor_g") );
	SetupValue( Variables.Visuals.VisualsLocalGlowColor [ 2 ], 1.f, ("GlowColor"), ("VisualsLocalGlowColor_b") );
	SetupValue( Variables.Visuals.VisualsLocalGlowColor [ 3 ], 1.f, ("GlowColor"), ("VisualsLocalGlowColor_a") );
	//menucolor
	SetupValue( Variables.menucolor [ 0 ], 1.f, ("menucolors"), ("menucolor_r") );
	SetupValue( Variables.menucolor [ 1 ], 1.f, ("menucolors"), ("menucolor_g") );
	SetupValue( Variables.menucolor [ 2 ], 1.f, ("menucolors"), ("menucolor_b") );
}

void c_config::SetupValue( int& value, int def, std::string category, std::string name )
{
	value = def;
	ints.push_back( new ConfigValue<int>( category, name, &value ) );
}

void c_config::SetupValue( float& value, float def, std::string category, std::string name )
{
	value = def;
	floats.push_back( new ConfigValue<float>( category, name, &value ) );
}

void c_config::SetupValue( bool& value, bool def, std::string category, std::string name )
{
	value = def;
	bools.push_back( new ConfigValue<bool>( category, name, &value ) );
}


void c_config::Save( )
{
	static char path [ MAX_PATH ];
	std::string folder, file;

	if ( SUCCEEDED( SHGetFolderPathA( NULL, CSIDL_MYDOCUMENTS, NULL, 0, path ) ) )
	{
		char szCmd [ 256 ];
		sprintf( szCmd, "\\versas\\%s.cfg", Variables.Misc.config_name );

		folder = std::string( path ) + "\\versas\\";
		file = std::string( path ) + szCmd;
	}

	CreateDirectoryA( folder.c_str( ), NULL );

	for ( auto value : ints )
		WritePrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), std::to_string( *value->value ).c_str( ), file.c_str( ) );

	for ( auto value : floats )
		WritePrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), std::to_string( *value->value ).c_str( ), file.c_str( ) );

	for ( auto value : bools )
		WritePrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), *value->value ? "true" : "false", file.c_str( ) );
}

void c_config::Load( )
{
	static char path [ MAX_PATH ];
	std::string folder, file;

	if ( SUCCEEDED( SHGetFolderPathA( NULL, CSIDL_MYDOCUMENTS, NULL, 0, path ) ) )
	{
		char szCmd [ 256 ];
		sprintf( szCmd, "\\versas\\%s.cfg", Variables.Misc.config_name );

		folder = std::string( path ) + "\\versas\\";
		file = std::string( path ) + szCmd;
	}

	CreateDirectoryA( folder.c_str( ), NULL );

	char value_l [ 32 ] = { '\0' };

	for ( auto value : ints )
	{
		GetPrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), "", value_l, 32, file.c_str( ) );
		*value->value = atoi( value_l );
	}

	for ( auto value : floats )
	{
		GetPrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), "", value_l, 32, file.c_str( ) );
		*value->value = atof( value_l );
	}

	for ( auto value : bools )
	{
		GetPrivateProfileStringA( value->category.c_str( ), value->name.c_str( ), "", value_l, 32, file.c_str( ) );
		*value->value = !strcmp( value_l, "true" );
	}
}

c_config* Config = new c_config( );