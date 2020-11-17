#include "visuals.hpp"
#include "../hooks/hooks.hpp"
#include "ragebot.hpp"
#include "events.h"
#include "resolver.hpp"
#include "lagcomp.h"
#include <time.h>
#include <corecrt.h>
#include "antiaim.h"
#include "animfix.h"
#include "../globals/globals.hpp"
void Render::CreateFonts( )
{

	namefont = g_VGuiSurface->CreateFont_( );
	g_VGuiSurface->SetFontGlyphSet( namefont, "hooge 05_55 Cyr2", 9, 100, 0, 0, FONTFLAG_OUTLINE );


	weaponfont = g_VGuiSurface->CreateFont_( );
	g_VGuiSurface->SetFontGlyphSet( weaponfont, "hooge 05_55 Cyr2", 9, 100, 0, 0, FONTFLAG_OUTLINE );



	flagfont = g_VGuiSurface->CreateFont_( );
	g_VGuiSurface->SetFontGlyphSet( flagfont, "Smallest Pixel-7", 10, 100, 0, 0, FONTFLAG_OUTLINE );



	eventesp = g_VGuiSurface->CreateFont_( );
	g_VGuiSurface->SetFontGlyphSet( eventesp, "Tahoma", 12, 100, 0, 0, FONTFLAG_OUTLINE );

	esp_font = g_VGuiSurface->CreateFont_( );
	g_VGuiSurface->SetFontGlyphSet( esp_font, "Tahoma", 13, 350, 0, 0, FONTFLAG_OUTLINE, FONTFLAG_ANTIALIAS );

	bombtimerfont = g_VGuiSurface->CreateFont_( );
	g_VGuiSurface->SetFontGlyphSet( bombtimerfont, "Arial", 22, 100, 0, 0, FONTFLAG_OUTLINE );


	ui_font = g_VGuiSurface->CreateFont_( );
	g_VGuiSurface->SetFontGlyphSet( ui_font, "Bell Gothic", 10, 350, 0, 0, FONTFLAG_OUTLINE );

	wasdindicator2 = g_VGuiSurface->CreateFont_( );
	g_VGuiSurface->SetFontGlyphSet( wasdindicator2, "Arial", 22, 100, 0, 0, FONTFLAG_OUTLINE );

	infobaryas = g_VGuiSurface->CreateFont_( );
	g_VGuiSurface->SetFontGlyphSet( infobaryas, "Arial", 30, 500, 0, 0, FONTFLAG_OUTLINE );




	indicators2 = g_VGuiSurface->CreateFont_( );
	g_VGuiSurface->SetFontGlyphSet( indicators2, "Arial", 60, 500, 0, 0, FONTFLAG_ANTIALIAS );


	infobaryas2 = g_VGuiSurface->CreateFont_( );
	g_VGuiSurface->SetFontGlyphSet( infobaryas2, "Arial", 18, 500, 0, 0, FONTFLAG_OUTLINE );
	weapon_font = g_VGuiSurface->CreateFont_( );// 0xA1;
	g_VGuiSurface->SetFontGlyphSet( weapon_font, "Counter-Strike", 16, 500, 0, 0, FONTFLAG_OUTLINE | FONTFLAG_ANTIALIAS );

	//g_VGuiSurface->SetFontGlyphSet(FuckMyAss, "Counter-Strike", 18, 500, 0, 0, FONTFLAG_ANTIALIAS);
}
void Render::Text( int X, int Y, const char* Text, vgui::HFont Font, Color DrawColor, bool Center/*, bool eatmyasscheeks*/ )
{
	std::wstring WText = std::wstring( std::string_view( Text ).begin( ), std::string_view( Text ).end( ) );
	g_VGuiSurface->DrawSetTextFont( Font );
	g_VGuiSurface->DrawSetTextColor( DrawColor );
	if ( Center )
	{
		int TextWidth, TextHeight;
		Render::Get( ).TextSize( TextWidth, TextHeight, Text, Font );
		g_VGuiSurface->DrawSetTextPos( X - TextWidth / 2, Y );
	}
	else
		g_VGuiSurface->DrawSetTextPos( X, Y );
	g_VGuiSurface->DrawPrintText( WText.c_str( ), wcslen( WText.c_str( ) ) );
}

void Render::TextSize( int& Width, int& Height, const char* Text, vgui::HFont Font )
{
	std::wstring WText = std::wstring( std::string_view( Text ).begin( ), std::string_view( Text ).end( ) );
	g_VGuiSurface->GetTextSize( Font, WText.c_str( ), Width, Height );
}
Vector2D  Render::GetTextSize( unsigned int Font, std::string Input, ... )
{
	/* char -> wchar */
	size_t size = Input.size( ) + 1;
	auto wide_buffer = std::make_unique<wchar_t [ ]>( size );
	mbstowcs_s( 0, wide_buffer.get( ), size, Input.c_str( ), size - 1 );

	int width, height;
	g_VGuiSurface->GetTextSize( Font, wide_buffer.get( ), width, height );

	return Vector2D( width, height );
}
void Render::FilledRectange( int X1, int Y1, int X2, int Y2, Color DrawColor )
{
	g_VGuiSurface->DrawSetColor( DrawColor );
	g_VGuiSurface->DrawFilledRect( X1, Y1, X2, Y2 );
}
void Render::OutlinedRectange( int X1, int Y1, int X2, int Y2, Color DrawColor )
{
	g_VGuiSurface->DrawSetColor( DrawColor );
	g_VGuiSurface->DrawOutlinedRect( X1, Y1, X2, Y2 );
}
void Render::Line( int X1, int Y1, int X2, int Y2, Color DrawColor )
{
	g_VGuiSurface->DrawSetColor( DrawColor );
	g_VGuiSurface->DrawLine( X1, Y1, X2, Y2 );
}
void  Render::DrawString( unsigned long font, int x, int y, Color color, unsigned long alignment, const char* msg, ... )
{

	va_list va_alist;
	char buf [ 1024 ];
	va_start( va_alist, msg );
	_vsnprintf( buf, sizeof( buf ), msg, va_alist );
	va_end( va_alist );
	wchar_t wbuf [ 1024 ];
	MultiByteToWideChar( CP_UTF8, 0, buf, 256, wbuf, 256 );

	int r = 255, g = 255, b = 255, a = 255;
	color.GetColor( r, g, b, a );

	int width, height;
	g_VGuiSurface->GetTextSize( font, wbuf, width, height );

	if ( alignment & FONT_RIGHT )
		x -= width;
	if ( alignment & FONT_CENTER )
		x -= width / 2;

	g_VGuiSurface->DrawSetTextFont( font );
	g_VGuiSurface->DrawSetTextColor( r, g, b, a );
	g_VGuiSurface->DrawSetTextPos( x, y - height / 2 );
	g_VGuiSurface->DrawPrintText( wbuf, wcslen( wbuf ) );
}
void Render::TexturedPolygon( int n, std::vector<Vertex_t> vertice, Color color )
{
	static int texture_id = g_VGuiSurface->CreateNewTextureID( true ); // 
	static unsigned char buf [ 4 ] = { 255, 255, 255, 255 };
	g_VGuiSurface->DrawSetTextureRGBA( texture_id, buf, 1, 1 ); //
	g_VGuiSurface->DrawSetColor( color ); //
	g_VGuiSurface->DrawSetTexture( texture_id ); //
	g_VGuiSurface->DrawTexturedPolygon( n, vertice.data( ) ); //
}
Chams::Chams( )
{
	std::ofstream( "csgo\\materials\\textured_virt.vmt" ) << R"("VertexLitGeneric"
				{
					"$basetexture"	"vgui/white"
					"$model"		"1"
					"$flat"			"0"
					"$nocull"		"1"
					"$halflambert"	"1"
					"$nofog"		"1"
					"$ignorez"		"0"
					"$znearer"		"0"
					"$wireframe"	"0"
				})";
	std::ofstream( "csgo\\materials\\flat_virt.vmt" ) << R"("UnlitGeneric"
				{
					"$basetexture"	"vgui/white"
					"$model"		"1"
					"$flat"			"1"
					"$nocull"		"1"
					"$selfillum"	"1"
					"$halflambert"	"1"
					"$nofog"		"1"
					"$ignorez"		"0"
					"$znearer"		"0"
					"$wireframe"	"0"
				})";
	std::ofstream( "csgo/dev/glow_armsrace.vmt" ) << R"#("VertexLitGeneric" {
      "$basetexture" "vgui/white_additive"
      "$ignorez" "0"
      "$envmap" "env_cubemap"
      "$normalmapalphaenvmapmask" "1"
      "$envmapcontrast"  "1"
      "$nofog" "1"
      "$model" "1"
      "$nocull" "0"
      "$selfillum" "1"
      "$halflambert" "1"
      "$znearer" "0"
      "$flat" "1" 
}
)#";
	std::ofstream("csgo/materials/glowOverlay.vmt") << R"#("VertexLitGeneric" {
				"$additive" "1"
				"$envmap" "models/effects/cube_white"
				"$envmaptint" "[1 1 1]"
				"$envmapfresnel" "1"
				"$envmapfresnelminmaxexp" "[0 1 1]"
				"$alpha" "[0.8]"
}
)#";

	materialRegular = g_MatSystem->FindMaterial( "textured_virt", TEXTURE_GROUP_MODEL );
	materialFlat = g_MatSystem->FindMaterial( "flat_virt", TEXTURE_GROUP_MODEL );
	materialMetallic = g_MatSystem->FindMaterial( "material_reflective", TEXTURE_GROUP_MODEL );
	materialDogtag = g_MatSystem->FindMaterial( "models\\inventory_items\\dogtags\\dogtags_outline", TEXTURE_GROUP_OTHER );
	materialGlowArmsrace = g_MatSystem->FindMaterial( "dev/glow_armsrace.vmt", TEXTURE_GROUP_OTHER );
	materialEsoGlow = g_MatSystem->FindMaterial( "glowOverlay", TEXTURE_GROUP_OTHER );
}
Chams::~Chams( )
{
	std::remove( "csgo\\materials\\material_textured.vmt" );
	std::remove( "csgo\\materials\\material_textured_ignorez.vmt" );
	std::remove( "csgo\\materials\\material_flat.vmt" );
	std::remove( "csgo\\materials\\material_flat_ignorez.vmt" );
	std::remove( "csgo\\materials\\material_reflwective.vmt" );
	std::remove( "csgo\\materials\\material_reflective_ignorez.vmt" );
}

void modulate( const float* color, IMaterial* material )
{
	if ( material )
	{
		material->AlphaModulate( color [ 3 ] );
		material->ColorModulate( color [ 0 ], color [ 1 ], color [ 2 ] );
		bool found_tint;
		const auto tint = material->FindVar( "$envmaptint", &found_tint );
		if ( found_tint )
			tint->SetVector( Vector( color [ 0 ], color [ 1 ], color [ 2 ] ) );
	}

}

void Chams::OnDrawModelExecute( IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* matrix )
{
	static auto fnDME = Hooks::mdlrender_hook.get_original<decltype(&Hooks::hkDrawModelExecute)>( index::DrawModelExecute );
	const auto mdl = info.pModel;

	if ( g_MdlRender->IsForcedMaterialOverride( ) )
		return fnDME( g_MdlRender, 0, ctx, state, info, matrix ); 
	auto entity = C_BasePlayer::GetPlayerByIndex( info.entity_index );

	bool is_player = strstr( mdl->szName, "models/player" ) != nullptr;
	bool is_hand = strstr( mdl->szName, "arms" ) != nullptr;
	bool is_weapon = strstr( mdl->szName, "weapons/v_" ) != nullptr;
	static IMaterial* hand = nullptr;
	static IMaterial* normal = nullptr;
	static IMaterial* weapon = nullptr;
	static IMaterial* local = nullptr;
	static IMaterial* desyncmat = nullptr;
	static IMaterial* desync_layer = nullptr;
	static IMaterial* enemy_layer = nullptr;
	static IMaterial* local_layer = nullptr;
	switch ( Variables.Visuals.VisualsChamsMaterial )
	{
	case 0:
		normal = materialRegular;
		break;
	case 1:
		normal = materialFlat;
		break;
	case 2:
		normal = materialMetallic;
		break;
	case 3:
		normal = materialDogtag;
		break;
	case 4:
		normal = materialGlowArmsrace;
		break;
	case 5:
		normal = materialEsoGlow;
		break;
	}

	switch ( Variables.Visuals.enemy_layer_int )
	{
	case 0:
		enemy_layer = materialRegular;
		break;
	case 1:
		enemy_layer = materialFlat;
		break;
	case 2:
		enemy_layer = materialMetallic;
		break;
	case 3:
		enemy_layer = materialDogtag;
		break;
	case 4:
		enemy_layer = materialGlowArmsrace;
		break;
	case 5:
		enemy_layer = materialEsoGlow;
		break;
	}

	switch ( Variables.Visuals.local_layer_material )
	{
	case 0:
		local_layer = materialRegular;
		break;
	case 1:
		local_layer = materialFlat;
		break;
	case 2:
		local_layer = materialMetallic;
		break;
	case 3:
		local_layer = materialDogtag;
		break;
	case 4:
		local_layer = materialGlowArmsrace;
		break;
	case 5:
		local_layer = materialEsoGlow;
		break;
	}

	switch ( Variables.Visuals.desync_layer_material )
	{
	case 0:
		desync_layer = materialRegular;
		break;
	case 1:
		desync_layer = materialFlat;
		break;
	case 2:
		desync_layer = materialMetallic;
		break;
	case 3:
		desync_layer = materialDogtag;
		break;
	case 4:
		desync_layer = materialGlowArmsrace;
		break;
	case 5:
		desync_layer = materialEsoGlow;
		break;
	}

	switch ( Variables.Visuals.VisualsLocalChamsMaterial )
	{
	case 0:
		local = materialRegular;
		break;
	case 1:
		local = materialFlat;
		break;
	case 2:
		local = materialMetallic;
		break;
	case 3:
		local = materialDogtag;
		break;
	case 4:
		local = materialGlowArmsrace;
		break;
	case 5:
		local = materialEsoGlow;
		break;
	}

	switch ( Variables.Visuals.VisualsDesyncChamsMaterial )
	{
	case 0:
		desyncmat = materialRegular;
		break;
	case 1:
		desyncmat = materialFlat;
		break;
	case 2:
		desyncmat = materialMetallic;

		break;
	case 3:
		desyncmat = materialDogtag;
		break;
	case 4:
		desyncmat = materialGlowArmsrace;
		break;
	case 5:
		desyncmat = materialEsoGlow;
		break;
	}

	switch ( Variables.Visuals.VisualsHandChamsMaterial )
	{
	case 0:
		hand = materialRegular;
		break;
	case 1:
		hand = materialFlat;
		break;
	case 2:
		hand = materialMetallic;
		break;
	case 3:
		hand = materialDogtag;
		break;
	case 4:
		hand = materialGlowArmsrace;
		break;
	case 5:
		hand = materialEsoGlow;
		break;
	}

	switch ( Variables.Visuals.VisualsWeaponChamsMaterial )
	{
	case 0:
		weapon = materialRegular;
		break;
	case 1:
		weapon = materialFlat;
		break;
	case 2:
		weapon = materialMetallic;
		break;
	case 3:
		weapon = materialDogtag;
		break;
	case 4:
		weapon = materialGlowArmsrace;
		break;
	case 5:
		weapon = materialEsoGlow;
		break;
	}

	if ( is_player )
	{
		if ( g_LocalPlayer && entity && entity->IsAlive( ) && !entity->IsDormant( ) )
		{
			if ( entity->IsEnemy( ) && Variables.Visuals.VisualsChamsEnabled )
			{
				if ( Variables.Visuals.VisualsChamsIgnoreZ )
				{
					modulate( Variables.Visuals.VisualsChamsColorIgnoreZ, normal );
					normal->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true );
					g_MdlRender->ForcedMaterialOverride( normal );
					fnDME( g_MdlRender, 0, ctx, state, info, matrix );

					
				}

				normal->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false ); // make normal material visible
				modulate( Variables.Visuals.VisualsChamsColor, normal );
				g_MdlRender->ForcedMaterialOverride( normal );
				fnDME( g_MdlRender, 0, ctx, state, info, matrix );

				if ( Variables.Visuals.enemy_layer ) //get ovveride method
				{

					modulate( Variables.Visuals.enemy_layer_color, enemy_layer );
					enemy_layer->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true );
					g_MdlRender->ForcedMaterialOverride( enemy_layer );
					fnDME( g_MdlRender, 0, ctx, state, info, matrix );
				
					enemy_layer->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false ); // make normal material visible
					modulate( Variables.Visuals.enemy_layer_color, enemy_layer );
					g_MdlRender->ForcedMaterialOverride( enemy_layer );
					fnDME( g_MdlRender, 0, ctx, state, info, matrix );
				
				}


			}
			if ( entity == g_LocalPlayer )
			{
				if ( AntiAim::m_got_fake_matrix )
				{
					if ( Variables.Visuals.desyncchamsenable ) { // enabled
						for ( auto& i : AntiAim::m_fake_matrix )
						{
							i [ 0 ][ 3 ] += info.origin.x;
							i [ 1 ][ 3 ] += info.origin.y;
							i [ 2 ][ 3 ] += info.origin.z;
						}
						// visible
						{

							desyncmat->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false );
							modulate( Variables.Visuals.localdesynccol, desyncmat );
							g_MdlRender->ForcedMaterialOverride( desyncmat );
							fnDME( g_MdlRender, 0, ctx, state, info, AntiAim::m_fake_matrix );

							if ( Variables.Visuals.desync_layer )
							{
								desync_layer->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false );
								modulate( Variables.Visuals.desync_layer_color, desync_layer );
								g_MdlRender->ForcedMaterialOverride( desync_layer );
								fnDME( g_MdlRender, 0, ctx, state, info, AntiAim::m_fake_matrix );
							}
						
						}
						for ( auto& i : AntiAim::m_fake_matrix )
						{
							i [ 0 ][ 3 ] -= info.origin.x;
							i [ 1 ][ 3 ] -= info.origin.y;
							i [ 2 ][ 3 ] -= info.origin.z;
						}
						g_MdlRender->ForcedMaterialOverride( nullptr );
					}
				}


				if ( Variables.Visuals.enablelocalchams ) {

					local->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false );
					modulate( Variables.Visuals.localchamscol, local );
					g_MdlRender->ForcedMaterialOverride( local );
					fnDME( g_MdlRender, 0, ctx, state, info, matrix );

					if ( Variables.Visuals.local_layer )
					{
						local_layer->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false );
						modulate( Variables.Visuals.local_layer_color, local_layer );
						g_MdlRender->ForcedMaterialOverride( local_layer );
						fnDME( g_MdlRender, 0, ctx, state, info, matrix );
					}

				}
			}

		}
	}
	if ( is_hand )
	{
		if ( g_LocalPlayer->IsAlive( ) && Variables.Visuals.enablehandchams )
		{
			modulate( Variables.Visuals.handchamscol, hand );
			g_MdlRender->ForcedMaterialOverride( hand );
			fnDME( g_MdlRender, 0, ctx, state, info, matrix );
		}
	}
	if ( is_weapon )
	{
		if ( g_LocalPlayer->IsAlive( ) && Variables.Visuals.enableweaponchams )
		{
			modulate( Variables.Visuals.weaponchamscol, weapon );
			g_MdlRender->ForcedMaterialOverride( weapon );
			fnDME( g_MdlRender, 0, ctx, state, info, matrix );
		}
	}

		fnDME( g_MdlRender, 0, ctx, state, info, matrix );
	g_MdlRender->ForcedMaterialOverride( nullptr );
}

Glow::Glow( )
{
}

Glow::~Glow( )
{
	// We cannot call shutdown here unfortunately.
	// Reason is not very straightforward but anyways:
	// - This destructor will be called when the dll unloads
	//   but it cannot distinguish between manual unload 
	//   (pressing the Unload button or calling FreeLibrary)
	//   or unload due to game exit.
	//   What that means is that this destructor will be called
	//   when the game exits.
	// - When the game is exiting, other dlls might already 
	//   have been unloaded before us, so it is not safe to 
	//   access intermodular variables or functions.
	//   
	//   Trying to call Shutdown here will crash CSGO when it is
	//   exiting (because we try to access g_GlowObjManager).
	//
}

void Glow::Shutdown( )
{
	// Remove glow from all entities
	for ( auto i = 0; i < g_GlowObjManager->m_GlowObjectDefinitions.Count( ); i++ ) {
		auto& glowObject = g_GlowObjManager->m_GlowObjectDefinitions [ i ];
		auto entity = reinterpret_cast< C_BasePlayer* >(glowObject.m_pEntity);

		if ( glowObject.IsUnused( ) )
			continue;

		if ( !entity || entity->IsDormant( ) )
			continue;

		glowObject.m_flAlpha = 0.0f;
	}
}

void Glow::Run( )
{

	for ( auto i = 0; i < g_GlowObjManager->m_GlowObjectDefinitions.Count( ); i++ ) {
		auto& glowObject = g_GlowObjManager->m_GlowObjectDefinitions [ i ];
		auto entity = reinterpret_cast< C_BasePlayer* >(glowObject.m_pEntity);

		if ( glowObject.IsUnused( ) )
			continue;

		if ( !entity || entity->IsDormant( ) )
			continue;

		auto class_id = entity->GetClientClass( )->m_ClassID;
		auto color = Color {};
		switch ( class_id ) {
		case ClassId_CCSPlayer:

			if ( entity->IsAlive( ) && entity->IsEnemy( ) )
			{
				if ( Variables.Visuals.VisualsGlowEnabled )
				{
					color = Color(
						int( Variables.Visuals.VisualsGlowColor [ 0 ] * 255 ),
						int( Variables.Visuals.VisualsGlowColor [ 1 ] * 255 ),
						int( Variables.Visuals.VisualsGlowColor [ 2 ] * 255 ),
						int( Variables.Visuals.VisualsGlowColor [ 3 ] * 255 ) );

					glowObject.m_flRed = color.r( ) / 255.0f;
					glowObject.m_flGreen = color.g( ) / 255.0f;
					glowObject.m_flBlue = color.b( ) / 255.0f;
					glowObject.m_flAlpha = color.a( ) / 255.0f;
					glowObject.m_bRenderWhenOccluded = true;
					glowObject.m_bRenderWhenUnoccluded = false;
					glowObject.m_nGlowStyle = Variables.Visuals.VisualsGlowGlowstyle;
				}

			}

			if ( entity == g_LocalPlayer )
			{
				if ( Variables.Visuals.VisualsLocalGlowEnabled )
				{
					color = Color(
						int( Variables.Visuals.VisualsLocalGlowColor [ 0 ] * 255 ),
						int( Variables.Visuals.VisualsLocalGlowColor [ 1 ] * 255 ),
						int( Variables.Visuals.VisualsLocalGlowColor [ 2 ] * 255 ),
						int( Variables.Visuals.VisualsLocalGlowColor [ 3 ] * 255 ) );

					glowObject.m_flRed = color.r( ) / 255.0f;
					glowObject.m_flGreen = color.g( ) / 255.0f;
					glowObject.m_flBlue = color.b( ) / 255.0f;
					glowObject.m_flAlpha = color.a( ) / 255.0f;
					glowObject.m_bRenderWhenOccluded = true;
					glowObject.m_bRenderWhenUnoccluded = false;
					glowObject.m_nGlowStyle = Variables.Visuals.VisualsLocalGlowGlowstyle;
				}
			}

			break;

			/*case ClassId_CPlantedC4:
				color = Color(255, 255, 255, 170);
				break;
			default:
				if (entity->IsWeapon())
					color = Color(255, 255, 255, 170);*/
		}

	}

}

RECT Visuals::GetBBox( C_BasePlayer* Player, Vector TransformedPoints [ ] ) //not pasted ;))
{
	RECT rect {};
	auto collideable = Player->GetCollideable( );

	if ( !collideable )
		return rect;

	auto min = collideable->OBBMins( );
	auto max = collideable->OBBMaxs( );

	const matrix3x4_t& trans = Player->m_rgflCoordinateFrame( );

	Vector points [ ] =
	{
		Vector( min.x, min.y, min.z ),
		Vector( min.x, max.y, min.z ),
		Vector( max.x, max.y, min.z ),
		Vector( max.x, min.y, min.z ),
		Vector( max.x, max.y, max.z ),
		Vector( min.x, max.y, max.z ),
		Vector( min.x, min.y, max.z ),
		Vector( max.x, min.y, max.z )
	};

	Vector pointsTransformed [ 8 ];
	for ( int i = 0; i < 8; i++ ) {
		Math::VectorTransform( points [ i ], trans, pointsTransformed [ i ] );
	}

	Vector pos = Player->GetAbsOrigin( );
	Vector screen_points [ 8 ] = {};

	for ( int i = 0; i < 8; i++ )
		if ( !Math::WorldToScreen( pointsTransformed [ i ], screen_points [ i ] ) )
			return rect;
		else
			TransformedPoints [ i ] = screen_points [ i ];

	auto left = screen_points [ 0 ].x;
	auto top = screen_points [ 0 ].y;
	auto right = screen_points [ 0 ].x;
	auto bottom = screen_points [ 0 ].y;

	for ( int i = 1; i < 8; i++ )
	{
		if ( left > screen_points [ i ].x )
			left = screen_points [ i ].x;
		if ( top < screen_points [ i ].y )
			top = screen_points [ i ].y;
		if ( right < screen_points [ i ].x )
			right = screen_points [ i ].x;
		if ( bottom > screen_points [ i ].y )
			bottom = screen_points [ i ].y;
	}
	return RECT { ( long ) left, ( long ) top, ( long ) right, ( long ) bottom };
}
void Visuals::Draw3dCube( float scalar, Vector angles, Vector middle_origin, Color outline )
{
	Vector forward, right, up;
	Math::AngleVectors( angles, forward, right, up );

	Vector points [ 8 ];
	points [ 0 ] = middle_origin - (right * scalar) + (up * scalar) - (forward * scalar); // BLT
	points [ 1 ] = middle_origin + (right * scalar) + (up * scalar) - (forward * scalar); // BRT
	points [ 2 ] = middle_origin - (right * scalar) - (up * scalar) - (forward * scalar); // BLB
	points [ 3 ] = middle_origin + (right * scalar) - (up * scalar) - (forward * scalar); // BRB

	points [ 4 ] = middle_origin - (right * scalar) + (up * scalar) + (forward * scalar); // FLT
	points [ 5 ] = middle_origin + (right * scalar) + (up * scalar) + (forward * scalar); // FRT
	points [ 6 ] = middle_origin - (right * scalar) - (up * scalar) + (forward * scalar); // FLB
	points [ 7 ] = middle_origin + (right * scalar) - (up * scalar) + (forward * scalar); // FRB

	Vector points_screen [ 8 ];
	for ( int i = 0; i < 8; i++ )
		if ( !Math::WorldToScreen( points [ i ], points_screen [ i ] ) )
			return;

	g_VGuiSurface->DrawSetColor( outline );

	// Back frame
	g_VGuiSurface->DrawLine( points_screen [ 0 ].x, points_screen [ 0 ].y, points_screen [ 1 ].x, points_screen [ 1 ].y );
	g_VGuiSurface->DrawLine( points_screen [ 0 ].x, points_screen [ 0 ].y, points_screen [ 2 ].x, points_screen [ 2 ].y );
	g_VGuiSurface->DrawLine( points_screen [ 3 ].x, points_screen [ 3 ].y, points_screen [ 1 ].x, points_screen [ 1 ].y );
	g_VGuiSurface->DrawLine( points_screen [ 3 ].x, points_screen [ 3 ].y, points_screen [ 2 ].x, points_screen [ 2 ].y );

	// Frame connector
	g_VGuiSurface->DrawLine( points_screen [ 0 ].x, points_screen [ 0 ].y, points_screen [ 4 ].x, points_screen [ 4 ].y );
	g_VGuiSurface->DrawLine( points_screen [ 1 ].x, points_screen [ 1 ].y, points_screen [ 5 ].x, points_screen [ 5 ].y );
	g_VGuiSurface->DrawLine( points_screen [ 2 ].x, points_screen [ 2 ].y, points_screen [ 6 ].x, points_screen [ 6 ].y );
	g_VGuiSurface->DrawLine( points_screen [ 3 ].x, points_screen [ 3 ].y, points_screen [ 7 ].x, points_screen [ 7 ].y );

	// Front frame
	g_VGuiSurface->DrawLine( points_screen [ 4 ].x, points_screen [ 4 ].y, points_screen [ 5 ].x, points_screen [ 5 ].y );
	g_VGuiSurface->DrawLine( points_screen [ 4 ].x, points_screen [ 4 ].y, points_screen [ 6 ].x, points_screen [ 6 ].y );
	g_VGuiSurface->DrawLine( points_screen [ 7 ].x, points_screen [ 7 ].y, points_screen [ 5 ].x, points_screen [ 5 ].y );
	g_VGuiSurface->DrawLine( points_screen [ 7 ].x, points_screen [ 7 ].y, points_screen [ 6 ].x, points_screen [ 6 ].y );
}


bool Visuals::Begin( C_BasePlayer* Player )
{
	Context.Player = Player;

	if ( !Context.Player->IsEnemy( ) )
		return false;

	if ( Context.Player->IsDormant( ) )
		return false;

	Vector head = Player->GetAbsOrigin( ) + Vector( 0, 0, Player->GetCollideable( )->OBBMaxs( ).z );
	Vector origin = Player->GetAbsOrigin( );
	origin.z -= 5;

	if ( !Math::WorldToScreen( head, Context.HeadPos ) ||
		!Math::WorldToScreen( origin, Context.Origin ) )
		return false;

	auto h = fabs( Context.HeadPos.y - Context.Origin.y );
	auto w = h / 1.65f;


	Context.Box.left = static_cast< long >(Context.Origin.x - w * 0.5f);
	Context.Box.right = static_cast< long >(Context.Box.left + w);
	Context.Box.bottom = (Context.Origin.y > Context.HeadPos.y ? static_cast< long >(Context.Origin.y) : static_cast< long >(Context.HeadPos.y));
	Context.Box.top = (Context.Origin.y > Context.HeadPos.y ? static_cast< long >(Context.HeadPos.y) : static_cast< long >(Context.Origin.y));


	return true;
}


void Visuals::Box( )
{
	auto color = Color {};

	color = Color(
		int( Variables.Visuals.boxcolor [ 0 ] * 255 ),
		int( Variables.Visuals.boxcolor [ 1 ] * 255 ),
		int( Variables.Visuals.boxcolor [ 2 ] * 255 ),
		int( 255 ) );

	//Render::Get().OutlinedRectange(Context.Box.left - 1, Context.Box.top - 1, Context.Box.right + 1, Context.Box.bottom + 1, Color(0, 0, 0, 150));
	//Render::Get().OutlinedRectange(Context.Box.left + 1, Context.Box.top + 1, Context.Box.right - 1, Context.Box.bottom - 1, Color(0, 0, 0, 150));
	Render::Get( ).OutlinedRectange( Context.Box.left, Context.Box.top, Context.Box.right, Context.Box.bottom, color );
}
void Visuals::Name( )
{
	player_info_t PlayerInfo;
	g_EngineClient->GetPlayerInfo( Context.Player->EntIndex( ), &PlayerInfo );
	auto color = Color {};

	color = Color(
		int( Variables.Visuals.namecolor [ 0 ] * 255 ),
		int( Variables.Visuals.namecolor [ 1 ] * 255 ),
		int( Variables.Visuals.namecolor [ 2 ] * 255 ),
		int( 255 ) );

	int TextWidth, TextHeight;
	Render::Get( ).TextSize( TextWidth, TextHeight, PlayerInfo.szName, Render::Get( ).namefont );

	Render::Get( ).Text( Context.Box.left + (Context.Box.right - Context.Box.left) / 2, Context.Box.top - TextHeight, PlayerInfo.szName, Render::Get( ).namefont, color, true );
}
void Visuals::Weapon( )
{
	auto color = Color {};

	color = Color(
		int( Variables.Visuals.weaponcolor [ 0 ] * 255 ),
		int( Variables.Visuals.weaponcolor [ 1 ] * 255 ),
		int( Variables.Visuals.weaponcolor [ 2 ] * 255 ),
		int( 255 ) );

	C_BaseCombatWeapon* Weapon = Context.Player->m_hActiveWeapon( );
	if ( !Weapon ) return;
	std::string WeaponName = std::string( Weapon->GetCSWeaponData( )->szHudName + std::string( " [ " ) + std::to_string( Weapon->m_iClip1( ) ) + std::string( " / " ) + std::to_string( Weapon->m_iPrimaryReserveAmmoCount( ) ) + std::string( " ] " ) );
	WeaponName.erase( 0, 13 );
	int TextWidth, TextHeight;
	Render::Get( ).TextSize( TextWidth, TextHeight, WeaponName.c_str( ), Render::Get( ).weaponfont );
	if ( Variables.Visuals.VisualsArmor )
		Render::Get( ).Text( Context.Box.left + (Context.Box.right - Context.Box.left) / 2, Context.Box.bottom - 1 + 10, WeaponName.c_str( ), Render::Get( ).weaponfont, color, true );
	else
		Render::Get( ).Text( Context.Box.left + (Context.Box.right - Context.Box.left) / 2, Context.Box.bottom - 1, WeaponName.c_str( ), Render::Get( ).weaponfont, Color( 255, 255, 255, 255 ), true );
}
#define FLAG_MACRO std::pair<std::string, Color> // :joy:
#define FLAG(string, color) vecFlags.push_back(FLAG_MACRO(string, color)) //coz, why not

void DrawString( unsigned long font, int x, int y, Color color, unsigned long alignment, const char* msg, ... )
{

	va_list va_alist;
	char buf[ 1024 ];
	va_start( va_alist, msg );
	_vsnprintf( buf, sizeof( buf ), msg, va_alist );
	va_end( va_alist );
	wchar_t wbuf[ 1024 ];
	MultiByteToWideChar( CP_UTF8, 0, buf, 256, wbuf, 256 );

	int r = 255, g = 255, b = 255, a = 255;
	color.GetColor( r, g, b, a );

	int width, height;
	g_VGuiSurface->GetTextSize( font, wbuf, width, height );

	if ( alignment & FONT_RIGHT )
		x -= width;
	if ( alignment & FONT_CENTER )
		x -= width / 2;

	g_VGuiSurface->DrawSetTextFont( font );
	g_VGuiSurface->DrawSetTextColor( r, g, b, a );
	g_VGuiSurface->DrawSetTextPos( x, y - height / 2 );
	g_VGuiSurface->DrawPrintText( wbuf, wcslen( wbuf ) );
}

void Visuals::Health( )
{
	auto color = Color {};

	color = Color(
		int( Variables.Visuals.healthcolor [ 0 ] * 255 ),
		int( Variables.Visuals.healthcolor [ 1 ] * 255 ),
		int( Variables.Visuals.healthcolor [ 2 ] * 255 ),
		int( 255 ) );

	int HealthValue = Context.Player->m_iHealth( );
	std::clamp( HealthValue, 0, 100 );

	float Height = (Context.Box.bottom - Context.Box.top) * float( HealthValue / 100.f );

	Render::Get( ).FilledRectange( Context.Box.left - 7, Context.Box.top - 1, Context.Box.left - 2, Context.Box.bottom + 1, Color( 0, 0, 0, 150 ) );
	Render::Get( ).FilledRectange( Context.Box.left - 6, Context.Box.top, Context.Box.left - 3, Context.Box.top + Height, color );

}





const std::string currentDateTime( ) {
	time_t     now = time( 0 );
	struct tm  tstruct;
	char       buf[ 80 ];
	tstruct = *localtime( &now );
	strftime( buf, sizeof( buf ), "%X", &tstruct );

	return buf;
}
void filled_rect( int x, int y, int w, int h, Color color ) {
	g_VGuiSurface->DrawSetColor( color.r( ), color.g( ), color.b( ), color.a( ) );
	g_VGuiSurface->DrawFilledRect( x, y, x + w, y + h );
}

void Visuals::DrawWatermark( )
{

}
void Visuals::RenderArmour( )
{
	auto  armour = Context.Player->m_ArmorValue( );
	float box_h = ( float ) fabs( Context.Box.right - Context.Box.left );
	//float off = (box_h / 6.f) + 5;
	float off = 4;

	auto height = (((box_h * armour) / 100));

	int x = Context.Box.left + off;
	int y = Context.Box.bottom;
	int w = 4;
	int h = box_h;

	auto color = Color {};

	color = Color(
		int( Variables.Visuals.armorcolor [ 0 ] * 255 ),
		int( Variables.Visuals.armorcolor [ 1 ] * 255 ),
		int( Variables.Visuals.armorcolor [ 2 ] * 255 ),
		int( 255 ) );

	g_VGuiSurface->DrawSetColor( Color::Black );
	g_VGuiSurface->DrawFilledRect( Context.Box.left - 1, Context.Box.bottom + 2, Context.Box.right + 1, Context.Box.bottom + 5 );
	//g_VGuiSurface->DrawFilledRect(x, y, x + w, y + h);
	g_VGuiSurface->DrawSetColor( color );
	//g_VGuiSurface->DrawFilledRect(Context.Box.left + 5, Context.Box.bottom + 2, Context.Box.left + w - 1, y + height - 2);
	g_VGuiSurface->DrawFilledRect( Context.Box.left, Context.Box.bottom + 2, Context.Box.left + height, Context.Box.bottom + 4 );

}
void Visuals::RenderSkelet( )
{
	studiohdr_t* studioHdr = g_MdlInfo->GetStudiomodel( Context.Player->GetModel( ) );
	if ( studioHdr )
	{
		static matrix3x4_t boneToWorldOut [ 128 ];
		if ( Context.Player->SetupBones( boneToWorldOut, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, Context.Player->m_flSimulationTime( ) ) )
			//if(ESP_ctx.player->HandleBoneSetup(BONE_USED_BY_HITBOX, boneToWorldOut))
		{
			for ( int i = 0; i < studioHdr->numbones; i++ )
			{
				mstudiobone_t* bone = studioHdr->GetBone( i );
				if ( !bone || !(bone->flags & BONE_USED_BY_HITBOX) || bone->parent == -1 )
					continue;

				Vector bonePos1;
				if ( !Math::WorldToScreen( Vector( boneToWorldOut [ i ][ 0 ][ 3 ], boneToWorldOut [ i ][ 1 ][ 3 ], boneToWorldOut [ i ][ 2 ][ 3 ] ), bonePos1 ) )
					continue;

				Vector bonePos2;
				if ( !Math::WorldToScreen( Vector( boneToWorldOut [ bone->parent ][ 0 ][ 3 ], boneToWorldOut [ bone->parent ][ 1 ][ 3 ], boneToWorldOut [ bone->parent ][ 2 ][ 3 ] ), bonePos2 ) )
					continue;

				auto color = Color {};

				color = Color(
					int( Variables.Visuals.skelecolor [ 0 ] * 255 ),
					int( Variables.Visuals.skelecolor [ 1 ] * 255 ),
					int( Variables.Visuals.skelecolor [ 2 ] * 255 ),
					int( 255 ) );

				g_VGuiSurface->DrawSetColor( Color( color ) );
				g_VGuiSurface->DrawLine( ( int ) bonePos1.x, ( int ) bonePos1.y, ( int ) bonePos2.x, ( int ) bonePos2.y );
			}
		}
	}
}
/*
void Visuals::RenderSkeletBacktrack(C_BasePlayer* player)
{
	studiohdr_t* studioHdr = g_MdlInfo->GetStudiomodel(Context.Player->GetModel());
	if (studioHdr)
	{
		if (backtrack->BacktrackRecords[player->EntIndex()].size() > 0)
		{
			TickInfo record = backtrack->BacktrackRecords[player->EntIndex()].back();


				for (int i = 0; i < studioHdr->numbones; i++)
				{
					mstudiobone_t* bone = studioHdr->GetBone(i);
					if (!bone || !(bone->flags & BONE_USED_BY_HITBOX) || bone->parent == -1)
						continue;

					Vector bonePos1;
					if (!Math::WorldToScreen(Vector(record.BoneMatrix[i][0][3], record.BoneMatrix[i][1][3], record.BoneMatrix[i][2][3]), bonePos1))
						continue;

					Vector bonePos2;
					if (!Math::WorldToScreen(Vector(record.BoneMatrix[bone->parent][0][3], record.BoneMatrix[bone->parent][1][3], record.matrix[bone->parent][2][3]), bonePos2))
						continue;

					auto color = Color{};

					color = Color(
						int(Variables.Visuals.skelehistorycolor[0] * 255),
						int(Variables.Visuals.skelehistorycolor[1] * 255),
						int(Variables.Visuals.skelehistorycolor[2] * 255),
						int(255));

					g_VGuiSurface->DrawSetColor(Color(color));
					g_VGuiSurface->DrawLine((int)bonePos1.x, (int)bonePos1.y, (int)bonePos2.x, (int)bonePos2.y);

				}


		}
	}
}*/

RECT GetTextSize( vgui::HFont font, const char* text )
{
	/*size_t origsize = strlen(text) + 1;
	const size_t newsize = 500;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);*/

	RECT rect;

	rect.left = rect.right = rect.bottom = rect.top = 0;

	wchar_t wbuf[ 1024 ];
	if ( MultiByteToWideChar( CP_UTF8, 0, text, -1, wbuf, 256 ) > 0 ) {
		int x, y;
		g_VGuiSurface->GetTextSize( font, wbuf, x, y );
		rect.left = x; rect.bottom = y;
		rect.right = x; rect.top = y;
	}

	return rect;
}



void Visuals::drawbombplanetd( C_BasePlayer* entity )
{
	if ( !entity )
		return;


	if ( !g_LocalPlayer )
		return;
	if ( !g_LocalPlayer->IsAlive( ) )
		return;
	CCSBomb* Bomb = ( CCSBomb* ) entity;
	if ( !Bomb )
		return;
	float c4blowtymmeboy = Bomb->GetC4BlowTime( );

	float time = c4blowtymmeboy - (g_pGlobalVars->interval_per_tick * g_LocalPlayer->m_nTickBase( ));
	char c4string [ 64 ];
	sprintf_s( c4string, " : %.1f", time );

//	Render::Get( ).Text( (w2 - 1500) + 75, h2 / 2 + 489, "time", Render::Get( ).bombtimerfont, Color( 255, 255, 255, 255 ), false );
//	Render::Get( ).Text( (w2 - 1455) + 75, h2 / 2 + 489, c4string, Render::Get( ).bombtimerfont, Color( 255, 255, 255, 255 ), false );

//	filled_rect( w2 - 1490, h2 / 2 + 514, 1000, 25, Color( 25, 25, 25, 220 ) );
//	filled_rect( w2 - 1490, h2 / 2 + 514, 1000 * (time / 40), 25, color );

	//get screen size
	int screenW, screenH;
	g_EngineClient->GetScreenSize( screenW, screenH );

	auto bomb_blow_timer = entity->m_flC4Blow( );
	static auto max_bombtime = g_CVar->FindVar( "mp_c4timer" );
	auto max_bombtimer = max_bombtime->GetFloat( );
	auto bomb_defuse_timer = entity->get_bomb_defuse_timer( );
	auto can_defuse = ( bomb_defuse_timer <= bomb_blow_timer && g_LocalPlayer->m_iTeamNum( ) == 3 ) || ( bomb_defuse_timer > bomb_blow_timer && g_LocalPlayer->m_iTeamNum( ) == 2 || bomb_defuse_timer <= bomb_blow_timer );

	int indicators = 0;
	auto ind_h = screenH / 2 + 10;

	auto btime = time * ( 100.f / 40 );

	if ( btime > 100.f )
		btime = 100.f;
	else if ( btime < 0.f )
		btime = 0.f;

	int blow_percent = screenH - ( int )( ( 98 * btime ) / 100 );
	int b_red = 255 - ( btime * 2.55 );
	int b_green = btime * 2.55;

	if ( bomb_blow_timer > 0.f )
	{


		Render::Get( ).Text( 60, ind_h + 15 + 20 * indicators, "BOMB", Render::Get().namefont, can_defuse ? Color( 0, 255, 0, 240 ) : Color( 255, 0, 0, 240 ), false);
		filled_rect( 10, ind_h + 15 + 20 * indicators, 100, 15, { 0, 0, 0, 130 } );
		filled_rect( 11, ind_h + 25 + 20 * indicators++, ( 98.f * float( time / 40 ) ), 4, { b_red,b_green ,0,130 } );
	}
	if ( bomb_defuse_timer > 0.f )
	{
		auto defuser = entity->m_hBombDefuser2( );

		auto max_defuse_timer = ( defuser && defuser->m_bHasDefuser( ) ) ? 5.f : 10.f; //&& !defuser->IsDead( )

		auto dtime = bomb_defuse_timer * ( 100.f / max_defuse_timer );

		if ( dtime > 100.f )
			dtime = 100.f;
		else if ( dtime < 0.f )
			dtime = 0.f;

		int defuse_percent = screenH - ( int )( ( 98 * dtime ) / 100 );
		int d_red = 255 - ( dtime * 2.55 );
		int d_green = dtime * 2.55;

		filled_rect( 10, ind_h + 15 + 20 * indicators, 100, 15, { 0, 0, 0, 130 } );
		Render::Get( ).Text( 60, ind_h + 15 + 20 * indicators, "DEFUSE", Render::Get( ).namefont, can_defuse ? Color( 0, 255, 0, 240 ) : Color( 255, 0, 0, 240 ), false );

		filled_rect( 11, ind_h + 25 + 20 * indicators++, ( 98.f * float( bomb_defuse_timer / max_defuse_timer ) ), 4, { b_red, b_green, 0,130 } );
	}
	
}



void Visuals::RenderWeapon( C_BasePlayer* entity )
{
	if ( !entity )
		return;
	wchar_t buf [ 80 ];
	auto clean_item_name = [ ] ( const char* name ) -> const char*
	{
		if ( name [ 0 ] == 'C' )
			name++;

		auto start = strstr( name, "Weapon" );
		if ( start != nullptr )
			name = start + 6;

		return name;
	};

	if ( entity->m_hOwnerEntity( ).IsValid( ) ||
		entity->m_vecOrigin( ) == Vector( 0, 0, 0 ) )
		return;

	Vector pointsTransformed [ 8 ];
	auto bbox = GetBBox( entity, pointsTransformed );
	if ( bbox.right == 0 || bbox.bottom == 0 )
		return;

	g_VGuiSurface->DrawSetColor( Color::White );

	g_VGuiSurface->DrawLine( bbox.left, bbox.top, bbox.right, bbox.top );
	g_VGuiSurface->DrawLine( bbox.left, bbox.bottom, bbox.right, bbox.bottom );
	g_VGuiSurface->DrawLine( bbox.left, bbox.top, bbox.left, bbox.bottom );
	g_VGuiSurface->DrawLine( bbox.right, bbox.top, bbox.right, bbox.bottom );


	auto name = clean_item_name( entity->GetClientClass( )->m_pNetworkName );
	if ( MultiByteToWideChar( CP_UTF8, 0, name, -1, buf, 80 ) > 0 )
	{
		int w = bbox.right - bbox.left;
		int tw, th;
		g_VGuiSurface->GetTextSize( Render::Get( ).ui_font, buf, tw, th );

		g_VGuiSurface->DrawSetTextFont( Render::Get( ).ui_font );
		g_VGuiSurface->DrawSetTextColor( Color::White );
		g_VGuiSurface->DrawSetTextPos( bbox.left + ((bbox.right - bbox.left) / 2) - (tw / 2), bbox.top + 1 );
		g_VGuiSurface->DrawPrintText( buf, wcslen( buf ) );
	}
}
Vector get_hitbox_pos( C_BasePlayer* entity, int hitbox_id )
{
	auto getHitbox = [ ] ( C_BasePlayer* entity, int hitboxIndex ) -> mstudiobbox_t*
	{
		if ( entity->IsDormant( ) || entity->m_iHealth( ) <= 0 ) return NULL;

		const auto pModel = entity->GetModel( );
		if ( !pModel ) return NULL;

		auto pStudioHdr = g_MdlInfo->GetStudiomodel( pModel );
		if ( !pStudioHdr ) return NULL;

		auto pSet = pStudioHdr->GetHitboxSet( 0 );
		if ( !pSet ) return NULL;

		if ( hitboxIndex >= pSet->numhitboxes || hitboxIndex < 0 ) return NULL;

		return pSet->GetHitbox( hitboxIndex );
	};

	auto hitbox = getHitbox( entity, hitbox_id );
	if ( !hitbox ) return Vector( 0, 0, 0 );

	auto bone_matrix = entity->GetBoneMatrix( hitbox->bone );

	Vector bbmin, bbmax;
	Math::VectorTransform( hitbox->bbmin, bone_matrix, bbmin );
	Math::VectorTransform( hitbox->bbmax, bone_matrix, bbmax );

	return (bbmin + bbmax) * 0.5f;
}
bool IsOnScreen( Vector origin, Vector& screen )
{
	if ( !Math::WorldToScreen( origin, screen ) ) return false;
	int iScreenWidth, iScreenHeight;
	g_EngineClient->GetScreenSize( iScreenWidth, iScreenHeight );
	bool xOk = iScreenWidth > screen.x > 0, yOk = iScreenHeight > screen.y > 0;
	return xOk && yOk;
}

void Visuals::DrawFovArrows( C_BasePlayer* entity )
{

	if ( !g_LocalPlayer ) return;
	if ( entity->IsDormant( ) ) return;

	Vector screenPos;
	Vector  client_viewangles;
	int screen_width = 0, screen_height = 0;
	float radius = 300.f;

	if ( IsOnScreen( get_hitbox_pos( entity, 0 ), screenPos ) ) return;

	g_EngineClient->GetViewAngles( client_viewangles );
	g_EngineClient->GetScreenSize( screen_width, screen_height );

	const auto screen_center = Vector( screen_width / 2.f, screen_height / 2.f, 0 );
	const auto rot = DEG2RAD( client_viewangles.y - Math::CalcAngle( g_LocalPlayer->GetEyePos( ), get_hitbox_pos( entity, 0 ) ).y - 90 );

	std::vector<Vertex_t> vertices;

	vertices.push_back( Vertex_t( Vector2D( screen_center.x + cosf( rot ) * radius, screen_center.y + sinf( rot ) * radius ) ) );
	vertices.push_back( Vertex_t( Vector2D( screen_center.x + cosf( rot + DEG2RAD( 2 ) ) * (radius - 16), screen_center.y + sinf( rot + DEG2RAD( 2 ) ) * (radius - 16) ) ) );
	vertices.push_back( Vertex_t( Vector2D( screen_center.x + cosf( rot - DEG2RAD( 2 ) ) * (radius - 16), screen_center.y + sinf( rot - DEG2RAD( 2 ) ) * (radius - 16) ) ) );

	auto color = Color {};

	color = Color(
		int( Variables.menucolor [ 0 ] * 255 ),
		int( Variables.menucolor [ 1 ] * 255 ),
		int( Variables.menucolor [ 2 ] * 255 ),
		int( 255 ) );
	Render::Get( ).TexturedPolygon( 3, vertices, color );
}




void Visuals::debugshotsmissed( C_BasePlayer* entity )
{

	auto gaags = Color {};

	gaags = Color(
		int( 255 ),
		int( 255 ),
		int( 255 ),
		int( 255 ) );

	if ( missed3shots == true )
		g_VGuiSurface->DrawT( 100, 100, gaags, Render::Get( ).ui_font, false, "true missed 3" );
}

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

void Visuals::indcators( )
{


}


void Visuals::aaindicator( )
{
	if ( !Variables.rageaimbot.antiaimenable )
		return;

	int W, H, cW, cH;
	g_EngineClient->GetScreenSize( W, H );
	cW = W / 2;
	cH = H / 2;

	auto gaags2 = Color {};

	gaags2 = Color(
		int( Variables.menucolor [ 0 ] * 255 ),
		int( Variables.menucolor [ 1 ] * 255 ),
		int( Variables.menucolor [ 2 ] * 255 ),
		int( 255 ) );


	//aaside -> globals


}



void Visuals::DrawFlags( ) /*Not the best way to do this, tbh*/
{
	std::vector<FLAG_MACRO> vecFlags;

	int alpha = 255; // so now, this is epic

	if ( Context.Player->m_ArmorValue( ) > 0 )
		FLAG( Context.Player->GetArmorName( ), Color( 255, 255, 255, alpha ) );

	if ( Context.Player->m_bIsScoped( ) )
		FLAG( "SCOPED", Color( 52, 165, 207, alpha ) );

	int offset = 0; //smh, have to think about a better way just because of this lmao
	for ( auto Text : vecFlags )
	{
		DrawString( Render::Get( ).ui_font, Context.Box.right + 4, (Context.Box.top + 4) + offset, Text.second, FONT_LEFT, Text.first.c_str( ) );
		offset += 9;
	}
}

void Visuals::drawcirclearoundlocal( )
{
	if ( !g_LocalPlayer )
		return;
	Vector origin = g_LocalPlayer->GetEyePos( );
	Vector prev_scr_pos = { -1, -1, -1 }, scr_pos;

	float step = M_PI * 2.0 / 6;
	float rad = 31.55;
	static float rainbow;
	for ( float rotation = 0; rotation < (M_PI * 2.0); rotation += step )
	{
		Vector pos( rad * cos( rotation ) + origin.x, rad * sin( rotation ) + origin.y, origin.z - 20 );

		Ray_t ray;
		trace_t trace;
		CTraceFilter filter;

		filter.pSkip = g_LocalPlayer;
		ray.Init( origin, pos );

		g_EngineTrace->TraceRay( ray, MASK_SHOT_BRUSHONLY, &filter, &trace );


		auto color2 = Color {};

		color2 = Color(
			int( Variables.menucolor [ 0 ] * 255 ),
			int( Variables.menucolor [ 1 ] * 255 ),
			int( Variables.menucolor [ 2 ] * 255 ),
			int( 255 ) );


		if ( Math::WorldToScreen( trace.endpos, scr_pos ) )
		{
			if ( prev_scr_pos != Vector( -1, -1, -1 ) )
			{
				int hue = RAD2DEG( rotation ) + rainbow;
				Color color = Color::FromHSB( hue / 360.f, 1, 1 );
				Render::Get( ).Line( prev_scr_pos.x, prev_scr_pos.y, scr_pos.x, scr_pos.y, color2 );
				Render::Get( ).Line( prev_scr_pos.x, prev_scr_pos.y - 1 - 1, scr_pos.x, scr_pos.y - 2 - 1, Color( 0, 0, 0, 255 ) );
				Render::Get( ).Line( prev_scr_pos.x, prev_scr_pos.y + 1 + 1, scr_pos.x, scr_pos.y + 2 + 1, Color( 0, 0, 0, 255 ) );

				for ( int it = 1; it <= 2; ++it )
				{
					Render::Get( ).Line( prev_scr_pos.x, prev_scr_pos.y - it, scr_pos.x, scr_pos.y - it, color2 );
					Render::Get( ).Line( prev_scr_pos.x, prev_scr_pos.y + it, scr_pos.x, scr_pos.y + it, color2 );
				}
			}
			prev_scr_pos = scr_pos;

		}
	}
	rainbow += .2f;
	if ( rainbow > 1.f ) rainbow = 0.f;
}
void Visuals::run_viewmodel( )
{
	g_CVar->FindVar( "viewmodel_offset_x" )->SetValue( Variables.Visuals.viewmodeloffsetx );
	g_CVar->FindVar( "viewmodel_offset_y" )->SetValue( Variables.Visuals.viewmodeloffsety );
	g_CVar->FindVar( "viewmodel_offset_z" )->SetValue( Variables.Visuals.viewmodeloffsetz );
}

void Polygon( int count, Vertex_t* Vertexs, Color color )
{
	static int Texture = g_VGuiSurface->CreateNewTextureID( true );
	unsigned char buffer [ 4 ] = { color.r( ), color.g( ), color.b( ), color.a( ) };

	g_VGuiSurface->DrawSetTextureRGBA( Texture, buffer, 1, 1 );
	g_VGuiSurface->DrawSetColor( Color( 255, 255, 255, 255 ) );
	g_VGuiSurface->DrawSetTexture( Texture );

	g_VGuiSurface->DrawTexturedPolygon( count, Vertexs );
}

void DrawFilledTriangle( std::array<Vector2D, 3> points, Color color )
{
	std::array<Vertex_t, 3> vertices { Vertex_t( points.at( 0 ) ), Vertex_t( points.at( 1 ) ), Vertex_t( points.at( 2 ) ) };
	Polygon( 3, vertices.data( ), color );
}


void Visuals::DrawPoV( ) /*I am allowed to take this from my old cheat, for all those guys saying this is pasted...*/
{
	auto isOnScreen = [ ] ( Vector origin, Vector& screen ) -> bool
	{
		if ( !Math::WorldToScreen( origin, screen ) )
			return false;

		int iScreenWidth, iScreenHeight;
		g_EngineClient->GetScreenSize( iScreenWidth, iScreenHeight );

		bool xOk = iScreenWidth > screen.x > 0, yOk = iScreenHeight > screen.y > 0;
		return xOk && yOk;
	};

	Vector screenPos;
	if ( isOnScreen( Context.Player->GetHitboxPos( 2 ), screenPos ) ) //TODO (?): maybe a combo/checkbox to turn this on/off
		return;

	auto rotateArrow = [ ] ( std::array< Vector2D, 3 >& points, float rotation ) -> void
	{
		const auto pointsCenter = (points.at( 0 ) + points.at( 1 ) + points.at( 2 )) / 3;
		for ( auto& point : points )
		{
			point -= pointsCenter;

			const auto tempX = point.x;
			const auto tempY = point.y;

			const auto theta = DEG2RAD( rotation );
			const auto c = cos( theta );
			const auto s = sin( theta );

			point.x = tempX * c - tempY * s;
			point.y = tempX * s + tempY * c;

			point += pointsCenter;
		}
	};

	Vector viewAngles;
	g_EngineClient->GetViewAngles( viewAngles );

	int width, height;
	g_EngineClient->GetScreenSize( width, height );

	const auto screenCenter = Vector2D( width * 0.5f, height * 0.5f );
	const auto angleYawRad = DEG2RAD( viewAngles.y - Math::CalcAngle( g_LocalPlayer->GetEyePos( ), Context.Player->GetHitboxPos( 2 ) ).y - 90 );


	const auto newPointX = screenCenter.x + ((((width - (15 * 3)) * 0.5f) * (100 / 100.f)) * cos( angleYawRad )) + ( int ) (6.0f * ((( float ) 15 - 4.f) / 16.0f)); //c-style casting, sorry.
	const auto newPointY = screenCenter.y + ((((height - (15 * 3)) * 0.5f) * (100 / 100.f)) * sin( angleYawRad ));

	std::array<Vector2D, 3> points { Vector2D( newPointX - 15, newPointY - 3 ), Vector2D( newPointX + 15, newPointY ), Vector2D( newPointX - 15, newPointY + 15 ) };

	/*first rotate the arrow, then draw it..*/
	rotateArrow( points, viewAngles.y - Math::CalcAngle( g_LocalPlayer->GetEyePos( ), Context.Player->GetHitboxPos( 2 ) ).y - 90 );



	auto color2 = Color {};

	color2 = Color(
		int( Variables.Visuals.povarrowscol [ 0 ] * 255 ),
		int( Variables.Visuals.povarrowscol [ 1 ] * 255 ),
		int( Variables.Visuals.povarrowscol [ 2 ] * 255 ),
		int( 255 ) );

	DrawFilledTriangle( points, color2 );
}

void Visuals::RenderNadeEsp( C_BasePlayer* nade )
{
	if ( !Variables.Visuals.drawnades )
		return;

	const model_t* model = nade->GetModel( );
	if ( !model )
		return;

	studiohdr_t* hdr = g_MdlInfo->GetStudiomodel( model );
	if ( !hdr )
		return;

	auto color2 = Color {};

	color2 = Color(
		int( Variables.Visuals.povarrowscol [ 0 ] * 255 ),
		int( Variables.Visuals.povarrowscol [ 1 ] * 255 ),
		int( Variables.Visuals.povarrowscol [ 2 ] * 255 ),
		int( 200 ) );
	Color Nadecolor;
	std::string entityName = hdr->szName, icon_character;
	switch ( nade->GetClientClass( )->m_ClassID )
	{
	case 9:
		if ( entityName [ 16 ] == 's' )
		{
			Nadecolor = color2;
			entityName = "Flash";
			icon_character = "G";
		}
		else
		{
			Nadecolor = color2;
			entityName = "Frag";
			icon_character = "H";
		}
		break;
	case 134:
		Nadecolor = color2;
		entityName = "Smoke";
		icon_character = "P";
		break;
	case 98:
		Nadecolor = color2;
		entityName = "Fire";
		icon_character = "P";
		break;
	case 41:
		Nadecolor = color2;
		entityName = "Decoy";
		icon_character = "G";
		break;
	default:
		return;
	}

	Vector points_transformed [ 8 ];
	RECT size = GetBBox( nade, points_transformed );
	if ( size.right == 0 || size.bottom == 0 )
		return;

	int width, height, width_icon, height_icon;
	Render::Get( ).GetTextSize( Render::Get( ).ui_font, entityName.c_str( ), width, height );
	Render::Get( ).GetTextSize( Render::Get( ).weapon_font, icon_character.c_str( ), width_icon, height_icon );

	// + distance? just make it customizable
//	switch (g_Options.esp_grenades_type)
	//{
	//case 1:
		/*g_VGuiSurface->DrawSetColor(Color(20, 20, 20, 240));
		g_VGuiSurface->DrawLine(size.left - 1, size.bottom - 1, size.left - 1, size.top + 1);
		g_VGuiSurface->DrawLine(size.right + 1, size.top + 1, size.right + 1, size.bottom - 1);
		g_VGuiSurface->DrawLine(size.left - 1, size.top + 1, size.right + 1, size.top + 1);
		g_VGuiSurface->DrawLine(size.right + 1, size.bottom - 1, size.left + -1, size.bottom - 1);

		g_VGuiSurface->DrawSetColor(Nadecolor);
		g_VGuiSurface->DrawLine(size.left, size.bottom, size.left, size.top);
		g_VGuiSurface->DrawLine(size.left, size.top, size.right, size.top);
		g_VGuiSurface->DrawLine(size.right, size.top, size.right, size.bottom);
		g_VGuiSurface->DrawLine(size.right, size.bottom, size.left, size.bottom);*/
		//	case 0:
			//	DrawString(ui_font, size.left + ((size.right - size.left) * 0.5), size.bottom + (size.top - size.bottom) + height * 0.5f + 2, Nadecolor, FONT_CENTER, entityName.c_str());
				//break;
		//	case 3:
			//	DrawString(ui_font, size.left + ((size.right - size.left) * 0.5), size.bottom + (size.top - size.bottom) + height_icon * 0.5f + 1, Nadecolor, FONT_CENTER, entityName.c_str());
			//case 2:
	DrawString( Render::Get( ).weapon_font, size.left + ((size.right - size.left) * 0.5), size.bottom + (size.top - size.bottom), Nadecolor, FONT_CENTER, icon_character.c_str( ) );
	DrawString( Render::Get( ).ui_font, size.left + ((size.right - size.left) * 0.5), size.bottom + (size.top - size.bottom) + height_icon * 0.5f + 1, Nadecolor, FONT_CENTER, entityName.c_str( ) );
	//	break;
	//}
}




















































