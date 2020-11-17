#include "menu.hpp"
#define NOMINMAX
#include <Windows.h>
#include <chrono>
#include <d3dx9.h>
#include <ShlObj_core.h>
#include "../config.hpp"
#include <intrin.h>
#include "../config.hpp"
#include "../imgui/imgui.h"
#include "../menuarrays.hpp"
#include "../hooks/hooks.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
ImFont* bigmenu_font;
ImFont* menu_font;
ImFont* smallmenu_font;


static int selectedcfg = 0;
static std::string cfgname = " default";

std::vector<std::string> configs;

void getconfig( )
{
	//get all files on folder

	configs.clear( );

	static char path [ MAX_PATH ];
	std::string szPath1;

	if ( !SUCCEEDED( SHGetFolderPathA( NULL, CSIDL_MYDOCUMENTS, NULL, 0, path ) ) )
		return;

	szPath1 = std::string( path ) + "\\versas\\*";


	WIN32_FIND_DATA FindFileData;
	HANDLE hf;

	configs.push_back( " choose config" );

	hf = FindFirstFile( szPath1.c_str( ), &FindFileData );
	if ( hf != INVALID_HANDLE_VALUE ) {
		do {
			std::string filename = FindFileData.cFileName;

			if ( filename == "." )
				continue;

			if ( filename == ".." )
				continue;

			if ( !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
			{
				if ( filename.find( ".cfg" ) != std::string::npos )
				{
					configs.push_back( std::string( filename ) );
				}
			}
		} while ( FindNextFile( hf, &FindFileData ) != 0 );
		FindClose( hf );
	}
}

void Menu::Initialize( )
{

	Visible = false;
	LegitAimbot = false;
	LegitTriggerbot = false;
	LegitBacktrack = false;
	VisualsChams = false;
	VisualsGlow = false;


	ImGui::CreateContext( );

	ImGui_ImplDX9_Init( InputSys::Get( ).GetMainWindow( ), g_D3DDevice9 );

	CreateStyle( );
}

void Menu::Shutdown( )
{
	ImGui_ImplDX9_Shutdown( );
}

void Menu::OnDeviceLost( )
{
	ImGui_ImplDX9_InvalidateDeviceObjects( );
}

void Menu::OnDeviceReset( )
{
	ImGui_ImplDX9_CreateDeviceObjects( );
}

IDirect3DTexture9* menuLogo = nullptr;
IDirect3DTexture9* menuLogo2 = nullptr;
IDirect3DTexture9* menuLogo3 = nullptr;
namespace ImGui
{

	static auto vector_getterxd = [ ] ( void* vec, int idx, const char** out_text )
	{
		auto& vector = *static_cast< std::vector<std::string>* >(vec);
		if ( idx < 0 || idx >= static_cast< int >(vector.size( )) ) { return false; }
		*out_text = vector.at( idx ).c_str( );
		return true;
	};

	IMGUI_API  bool TabLabels( int numTabs, const char** tabLabels, int& selectedIndex, const char** tabLabelTooltips, bool autoLayout, int* pOptionalHoveredIndex ) {
		ImGuiStyle& style = ImGui::GetStyle( );

		const ImVec4 color = style.Colors [ ImGuiCol_Button ];
		const ImVec4 Text = style.Colors [ ImGuiCol_Text ];
		const ImVec4 colorActive = style.Colors [ ImGuiCol_ButtonActive ];
		const ImVec4 colorHover = style.Colors [ ImGuiCol_ButtonHovered ];
		const ImVec2 itemSpacing = style.ItemSpacing;
		style.ItemSpacing.x = 2.5;
		style.ItemSpacing.y = 1;
		if ( numTabs > 0 && (selectedIndex < 0 || selectedIndex >= numTabs) ) selectedIndex = 0;
		if ( pOptionalHoveredIndex ) *pOptionalHoveredIndex = -1;

		const float btnOffset = 2.f * style.FramePadding.x;
		const float sameLineOffset = 2.f * style.ItemSpacing.x;
		const float uniqueLineOffset = 2.f * style.WindowPadding.x;

		float windowWidth = 0.f, sumX = 0.f;
		if ( autoLayout ) windowWidth = ImGui::GetWindowWidth( ) - uniqueLineOffset;

		bool selection_changed = false;
		for ( int i = 0; i < numTabs; i++ )
		{
			if ( i == selectedIndex )
			{
				style.Colors [ ImGuiCol_Text ] = ImVec4( 1.f, 1.f, 1.f, 1.f );
				style.Colors [ ImGuiCol_Button ] = colorActive;
				style.Colors [ ImGuiCol_ButtonActive ] = colorActive;
				style.Colors [ ImGuiCol_ButtonHovered ] = colorActive;
			}
			else
			{
				style.Colors [ ImGuiCol_Text ] = Text;
				style.Colors [ ImGuiCol_Button ] = color;
				style.Colors [ ImGuiCol_ButtonActive ] = colorActive;
				style.Colors [ ImGuiCol_ButtonHovered ] = colorHover;
			}

			ImGui::PushID( i );

			if ( !autoLayout ) { if ( i > 0 ) ImGui::SameLine( ); }
			else if ( sumX > 0.f ) {
				sumX += sameLineOffset;
				sumX += ImGui::CalcTextSize( tabLabels [ i ] ).x + btnOffset;
				if ( sumX > windowWidth ) sumX = 0.f;
				else ImGui::SameLine( );
			}
			if ( ImGui::Button( tabLabels [ i ], ImVec2( (windowWidth / numTabs) - 2, 20 ) ) ) { selection_changed = (selectedIndex != i); selectedIndex = i; }
			if ( autoLayout && sumX == 0.f ) {
				sumX = ImGui::GetItemRectSize( ).x;
			}
			if ( pOptionalHoveredIndex ) {
				if ( ImGui::IsItemHovered( ) ) {
					*pOptionalHoveredIndex = i;
					if ( tabLabelTooltips && tabLabelTooltips [ i ] && strlen( tabLabelTooltips [ i ] ) > 0 )  ImGui::SetTooltip( "%s", tabLabelTooltips [ i ] );
				}
			}
			else if ( tabLabelTooltips && tabLabelTooltips [ i ] && ImGui::IsItemHovered( ) && strlen( tabLabelTooltips [ i ] ) > 0 ) ImGui::SetTooltip( "%s", tabLabelTooltips [ i ] );
			ImGui::PopID( );
		}

		style.Colors [ ImGuiCol_Text ] = Text;
		style.Colors [ ImGuiCol_Button ] = color;
		style.Colors [ ImGuiCol_ButtonActive ] = colorActive;
		style.Colors [ ImGuiCol_ButtonHovered ] = colorHover;
		style.ItemSpacing = itemSpacing;
		return selection_changed;
	}


	IMGUI_API bool ComboBoxArrayxd( const char* label, int* currIndex, std::vector<std::string>& values )
	{
		if ( values.empty( ) ) { return false; }
		return Combo( label, currIndex, vector_getterxd,
			static_cast< void* >(&values), values.size( ) );
	}


}
namespace Tabs
{
	//pula 1
	void RenderRagebot( )
	{
		ImGui::Columns( 3, NULL, false );
		ImGui::BeginChild( "##snekeograsa", ImVec2( 256, 450 ), true );
		{
			ImGui::Text( "General" );
			ImGui::Checkbox( "Enable", &Variables.rageaimbot.rageenable );
			ImGui::Checkbox( "Auto fire", &Variables.rageaimbot.autofire );
			ImGui::Combo( "Double-Tap", &Variables.rageaimbot.doubletab, dttt, ARRAYSIZE( dttt ) );
			if ( Variables.rageaimbot.doubletab == 1 )
			{
				ImGui::Hotkey( "##snekegay", &Variables.rageaimbot.fastshoot, ImVec2( 40, 20 ) );
			}

		}ImGui::EndChild( );

		ImGui::Spacing( );
		ImGui::Spacing( );
		ImGui::Spacing( );
		ImGui::Spacing( );

		ImGui::BeginChild( "##sneksugepula", ImVec2( 256, 130 ), true );
		{
			ImGui::Checkbox( "Auto Zeus", &Variables.rageaimbot.autozeus );
			ImGui::Checkbox( "Auto Knife", &Variables.rageaimbot.autoknife );
			ImGui::Checkbox( "Auto R8", &Variables.rageaimbot.autorevolvo );
			ImGui::Checkbox( "Auto Scope", &Variables.rageaimbot.rageautoscope );
			ImGui::Checkbox( "Auto Stop", &Variables.rageaimbot.rageautostop );
		}ImGui::EndChild( );
		ImGui::NextColumn( );

		ImGui::BeginChild( "##111", ImVec2( 256, 600 ), true );
		{
			static int weapons = 0;

			ImGui::Text( "Weapon Config" );
			ImGui::Combo( "Weapons", &weapons, wps, ARRAYSIZE( wps ) );
			if ( weapons == 0 )
			{
				ImGui::SliderInt( "Hitchance", &Variables.rageaimbot.auto_hitchance, 0, 100 );
				ImGui::SliderInt( "Minimum Damage", &Variables.rageaimbot.auto_mindamage, 0, 100 );
				ImGui::SliderInt( "Visible Damage", &Variables.rageaimbot.auto_mindamagevisible, 0, 100 );
				ImGui::Checkbox( "multipoint##multipoint", &Variables.rageaimbot.auto_multipoint );
				if ( Variables.rageaimbot.auto_multipoint )
				{
					ImGui::SliderInt( "Head Scale", &Variables.rageaimbot.auto_headscale, 0.0, 1.0 );
					ImGui::SliderInt( "Body Scale", &Variables.rageaimbot.auto_bodyscale, 0.0, 1.0 );
				}
				ImGui::ListBoxHeader( "" ); {
					ImGui::Selectable( "Head", &Variables.rageaimbot.auto_head );
					ImGui::Selectable( "Neck", &Variables.rageaimbot.auto_neck );
					ImGui::Selectable( "Chest", &Variables.rageaimbot.auto_chest );
					ImGui::Selectable( "Body", &Variables.rageaimbot.auto_body );
					ImGui::Selectable( "Stomach", &Variables.rageaimbot.auto_stomach );
					ImGui::Selectable( "Pelvis", &Variables.rageaimbot.auto_pelvis );
					ImGui::Selectable( "Arms", &Variables.rageaimbot.auto_arms );
					ImGui::Selectable( "Legs", &Variables.rageaimbot.auto_legs );
					ImGui::Selectable( "Feet", &Variables.rageaimbot.auto_toes );
				}
				ImGui::ListBoxFooter( );
			}
			if ( weapons == 1 )
			{
				ImGui::SliderInt( "Hitchance", &Variables.rageaimbot.scout_hitchance, 0, 100 );
				ImGui::SliderInt( "Minimum Damage", &Variables.rageaimbot.scout_mindamage, 0, 100 );
				ImGui::SliderInt( "Visible Damage", &Variables.rageaimbot.scout_mindamagevisible, 0, 100 );
				ImGui::Checkbox( "multipoint##multipoint", &Variables.rageaimbot.scout_multipoint );
				if ( Variables.rageaimbot.scout_multipoint )
				{
					ImGui::SliderInt( "Head Scale", &Variables.rageaimbot.scout_headscale, 0.0, 1.0 );
					ImGui::SliderInt( "Body Scale", &Variables.rageaimbot.scout_bodyscale, 0.0, 1.0 );
				}
				ImGui::ListBoxHeader( "" ); {
					ImGui::Selectable( "Head", &Variables.rageaimbot.scout_head );
					ImGui::Selectable( "Neck", &Variables.rageaimbot.scout_neck );
					ImGui::Selectable( "Chest", &Variables.rageaimbot.scout_chest );
					ImGui::Selectable( "Body", &Variables.rageaimbot.scout_body );
					ImGui::Selectable( "Stomach", &Variables.rageaimbot.scout_stomach );
					ImGui::Selectable( "Pelvis", &Variables.rageaimbot.scout_pelvis );
					ImGui::Selectable( "Arms", &Variables.rageaimbot.scout_arms );
					ImGui::Selectable( "Legs", &Variables.rageaimbot.scout_legs );
					ImGui::Selectable( "Feet", &Variables.rageaimbot.scout_toes );
				}
				ImGui::ListBoxFooter( );
			}
			if ( weapons == 2 )
			{
				ImGui::SliderInt( "Hitchance", &Variables.rageaimbot.awp_hitchance, 0, 100 );
				ImGui::SliderInt( "Minimum Damage", &Variables.rageaimbot.awp_mindamage, 0, 100 );
				ImGui::SliderInt( "Visible Damage", &Variables.rageaimbot.awp_mindamagevisible, 0, 100 );
				ImGui::Checkbox( "multipoint##multipoint", &Variables.rageaimbot.awp_multipoint );
				if ( Variables.rageaimbot.awp_multipoint )
				{
					ImGui::SliderInt( "Head Scale", &Variables.rageaimbot.awp_headscale, 0.0, 1.0 );
					ImGui::SliderInt( "Body Scale", &Variables.rageaimbot.awp_bodyscale, 0.0, 1.0 );
				}
				ImGui::ListBoxHeader( "" ); {
					ImGui::Selectable( "Head", &Variables.rageaimbot.awp_head );
					ImGui::Selectable( "Neck", &Variables.rageaimbot.awp_neck );
					ImGui::Selectable( "Chest", &Variables.rageaimbot.awp_chest );
					ImGui::Selectable( "Body", &Variables.rageaimbot.awp_body );
					ImGui::Selectable( "Stomach", &Variables.rageaimbot.awp_stomach );
					ImGui::Selectable( "Pelvis", &Variables.rageaimbot.awp_pelvis );
					ImGui::Selectable( "Arms", &Variables.rageaimbot.awp_arms );
					ImGui::Selectable( "Legs", &Variables.rageaimbot.awp_legs );
					ImGui::Selectable( "Feet", &Variables.rageaimbot.awp_toes );
				}
				ImGui::ListBoxFooter( );
			}
			if ( weapons == 3 )
			{
				ImGui::SliderInt( "Hitchance", &Variables.rageaimbot.heavy_pistol_hitchance, 0, 100 );
				ImGui::SliderInt( "Minimum Damage", &Variables.rageaimbot.heavy_pistol_mindamage, 0, 100 );
				ImGui::SliderInt( "Visible Damage", &Variables.rageaimbot.heavy_pistol_mindamagevisible, 0, 100 );
				ImGui::Checkbox( "multipoint##multipoint", &Variables.rageaimbot.heavy_pistol_multipoint );
				if ( Variables.rageaimbot.heavy_pistol_multipoint )
				{
					ImGui::SliderInt( "Head Scale", &Variables.rageaimbot.heavy_pistol_headscale, 0.0, 1.0 );
					ImGui::SliderInt( "Body Scale", &Variables.rageaimbot.heavy_pistol_bodyscale, 0.0, 1.0 );
				}
				ImGui::ListBoxHeader( "" ); {
					ImGui::Selectable( "Head", &Variables.rageaimbot.heavy_pistol_head );
					ImGui::Selectable( "Neck", &Variables.rageaimbot.heavy_pistol_neck );
					ImGui::Selectable( "Chest", &Variables.rageaimbot.heavy_pistol_chest );
					ImGui::Selectable( "Body", &Variables.rageaimbot.heavy_pistol_body );
					ImGui::Selectable( "Stomach", &Variables.rageaimbot.heavy_pistol_stomach );
					ImGui::Selectable( "Pelvis", &Variables.rageaimbot.heavy_pistol_pelvis );
					ImGui::Selectable( "Arms", &Variables.rageaimbot.heavy_pistol_arms );
					ImGui::Selectable( "Legs", &Variables.rageaimbot.heavy_pistol_legs );
					ImGui::Selectable( "Feet", &Variables.rageaimbot.heavy_pistol_toes );
				}
				ImGui::ListBoxFooter( );
			}
			if ( weapons == 4 )
			{
				ImGui::SliderInt( "Hitchance", &Variables.rageaimbot.hitchance, 0, 100 );
				ImGui::SliderInt( "Minimum Damage", &Variables.rageaimbot.minimumdmage, 0, 100 );
				ImGui::SliderInt( "Visible Damage", &Variables.rageaimbot.minimumdmagevisible, 0, 100 );
				ImGui::Checkbox( "multipoint##multipoint", &Variables.rageaimbot.multipoint );
				if ( Variables.rageaimbot.multipoint )
				{
					ImGui::SliderInt( "Head Scale", &Variables.rageaimbot.headscale, 0.0, 1.0 );
					ImGui::SliderInt( "Body Scale", &Variables.rageaimbot.bodyscale, 0.0, 1.0 );
				}
				ImGui::ListBoxHeader( "" ); {
					ImGui::Selectable( "Head", &Variables.rageaimbot.head );
					ImGui::Selectable( "Neck", &Variables.rageaimbot.neck );
					ImGui::Selectable( "Chest", &Variables.rageaimbot.chest );
					ImGui::Selectable( "Body", &Variables.rageaimbot.body );
					ImGui::Selectable( "Stomach", &Variables.rageaimbot.stomach );
					ImGui::Selectable( "Pelvis", &Variables.rageaimbot.pelvis );
					ImGui::Selectable( "Arms", &Variables.rageaimbot.arms );
					ImGui::Selectable( "Legs", &Variables.rageaimbot.legs );
					ImGui::Selectable( "Feet", &Variables.rageaimbot.toes );
				}
				ImGui::ListBoxFooter( );
			}
		}ImGui::EndChild( );

		ImGui::NextColumn( );

		ImGui::BeginChild( "##argentecelmaitare", ImVec2( -1, 600 ), true );
		{
			ImGui::Text( "Safety checks" );
			ImGui::Checkbox( "Safe point", &Variables.rageaimbot.safepoint );
			ImGui::Checkbox( "Lethal", &Variables.rageaimbot.baimiflethal );
			ImGui::Checkbox( "Baim After 3 Misses", &Variables.rageaimbot.baimafter3misses );
			ImGui::Hotkey( "Baim key", &Variables.rageaimbot.baimkey );
		}ImGui::EndChild( );

	}
	void RenderAA( )
	{
		ImGui::Columns( 2, NULL, false );
		ImGui::BeginChild( "##ragetab14", ImVec2( 385, 600 ), true );
		{
			ImGui::Checkbox( "Enable", &Variables.rageaimbot.antiaimenable );
			ImGui::Combo( "Pitch", &Variables.rageaimbot.pitch, pitchzzz, ARRAYSIZE( pitchzzz ) );
			static int aamode = 0;
			if ( ImGui::Button( "Stand", ImVec2( 89, 16 ) ) )
				aamode = 0;
			ImGui::SameLine( );
			if ( ImGui::Button( "Move", ImVec2( 89, 16 ) ) )
				aamode = 1;
			ImGui::SameLine( );
			if ( ImGui::Button( "Air", ImVec2( 89, 16 ) ) )
				aamode = 2;

			if ( aamode == 0 )
			{
				ImGui::Combo( "Stand Yaw", &Variables.rageaimbot.standingaa, pitchzzz, ARRAYSIZE( pitchzzz ) );
				ImGui::Checkbox( "Stand Jitter", &Variables.rageaimbot.jitterenablestanding );
				if ( Variables.rageaimbot.standingaa == 2 )
				{
					ImGui::Hotkey( "Left", &Variables.rageaimbot.left );
					ImGui::Hotkey( "Right", &Variables.rageaimbot.right );
					ImGui::Hotkey( "Back", &Variables.rageaimbot.back );
					ImGui::Hotkey( "Front", &Variables.rageaimbot.front );
				}
				if ( Variables.rageaimbot.jitterenablestanding )
					ImGui::SliderInt( "Value", &Variables.rageaimbot.jittervaluestanding, -100, 100 );
			}
			if ( aamode == 1 )
			{
				ImGui::Combo( "Move Yaw", &Variables.rageaimbot.movingaa, pitchzzz, ARRAYSIZE( pitchzzz ) );
				ImGui::Checkbox( "Move Jitter", &Variables.rageaimbot.jitterenablemoving );
				if ( Variables.rageaimbot.movingaa == 2 )
				{
					ImGui::Hotkey( "Left", &Variables.rageaimbot.left );
					ImGui::Hotkey( "Right", &Variables.rageaimbot.right );
					ImGui::Hotkey( "Back", &Variables.rageaimbot.back );
					ImGui::Hotkey( "Front", &Variables.rageaimbot.front );
				}
				if ( Variables.rageaimbot.jitterenablemoving )
					ImGui::SliderInt( "Value", &Variables.rageaimbot.jittervaluemoving, -100, 100 );
			}
			if ( aamode == 2 )
			{
				ImGui::Combo( "Air Yaw", &Variables.rageaimbot.airaa, pitchzzz, ARRAYSIZE( pitchzzz ) );
				if ( Variables.rageaimbot.airaa == 2 )
				{
					ImGui::Hotkey( "Left", &Variables.rageaimbot.left );
					ImGui::Hotkey( "Right", &Variables.rageaimbot.right );
					ImGui::Hotkey( "Back", &Variables.rageaimbot.back );
					ImGui::Hotkey( "Front", &Variables.rageaimbot.front );
				}
				ImGui::Checkbox( "Air Jitter", &Variables.rageaimbot.jitterenableair );
				if ( Variables.rageaimbot.jitterenableair )
					ImGui::SliderInt( "Value", &Variables.rageaimbot.jittervalueair, -100, 100 );

			}
		}ImGui::EndChild( );

		ImGui::NextColumn( );

		ImGui::BeginChild( "##idkidk", ImVec2( -1, 600 ), true );
		{
			ImGui::Combo( "Desync type", &Variables.rageaimbot.desynctype, desynbc, ARRAYSIZE( desynbc ) );
			if ( Variables.rageaimbot.desynctype == 1 )
			{
				ImGui::Hotkey( "Desync Inverter", &Variables.rageaimbot.staticinverter, ImVec2( 40, 20 ) );
				ImGui::SliderInt( "Bodylean", &Variables.rageaimbot.staticrightsidevalue, 0, 100 );
				ImGui::SliderInt( "Inverted Bodylean", &Variables.rageaimbot.staticleftsidevalue, 0, 100 );

			}

			if ( Variables.rageaimbot.desynctype == 2 )
			{
				ImGui::Hotkey( "Desync Inverter", &Variables.rageaimbot.staticinverter, ImVec2( 40, 20 ) );
				ImGui::SliderInt( "Jitter Value", &Variables.rageaimbot.staticjittervalue, -100, 100 );
			}
			ImGui::Checkbox( "Slowwalk", &Variables.Misc.slowwalk );
			if ( Variables.Misc.slowwalk )
			{
				ImGui::SliderInt( "Speed", &Variables.Misc.slowwalkspeed, 0, 100 );
				ImGui::Hotkey( "##tastafgm1", &Variables.rageaimbot.slowwalkkey, ImVec2( 40, 20 ) );
			}

			ImGui::Text( "Fakelag" );
			ImGui::SliderInt( "Amount", &Variables.Misc.MiscFakelagChoke, 0, 14 );
			ImGui::Spacing( );

			ImGui::Checkbox( "Fakeduck##1", &Variables.rageaimbot.fakeduckenable );
			if ( Variables.Misc.slowwalk )
				ImGui::Hotkey( "##tastafgm", &Variables.rageaimbot.fakeduckkey, ImVec2( 40, 20 ) );

		}ImGui::EndChild( );
	}
	void RenderLegit( )
	{
		ImGui::Columns( 2, NULL, false );

		ImGui::BeginChild( "##legittab1", ImVec2( -1, 600 ), true, 0 );
		{
			ImGui::Checkbox( "enable", &Variables.enablelgit );
			ImGui::Checkbox( "backtrack", &Variables.aimbot.Backtrack );
			if ( Variables.aimbot.Backtrack )
			{
				ImGui::SliderInt( "ms##btmslegit", &Variables.aimbot.BacktrackTime, 0, 200 );
			}

		}ImGui::EndChild( );

		ImGui::NextColumn( );

		ImGui::BeginChild( "##legittab2", ImVec2( -1, 600 ), true, 0 );
		{
			static int mota = 0;
			if ( ImGui::Button( "Snipers", ImVec2( 90, 22 ) ) )
				mota = 0;
			ImGui::SameLine( );
			if ( ImGui::Button( "Pistols", ImVec2( 90, 22 ) ) )
				mota = 1;
			ImGui::SameLine( );
			if ( ImGui::Button( "Others", ImVec2( 90, 22 ) ) )
				mota = 2;

			if ( mota == 0 )
			{
				ImGui::Checkbox( "enable##snupperssaenable", &Variables.aimbot.Snipers.Enabled );
				ImGui::Combo( "type##aimtypppe", &Variables.aimbot.Snipers.AimType, aimlegitrtype, ARRAYSIZE( aimlegitrtype ) );
				ImGui::SliderFloat( "fov##legitfovsnipers", &Variables.aimbot.Snipers.Fov, 0, 10 );
				if ( Variables.aimbot.Snipers.AimType == 1 )
					ImGui::SliderFloat( "restrain##restrainsnipers", &Variables.aimbot.Snipers.Fov, 0, 10 );
				ImGui::Checkbox( "auto rcs##rcssnipers", &Variables.aimbot.Snipers.Recoil );
				ImGui::Combo( "hitbox##hitboxlegitsnipers", &Variables.aimbot.Snipers.Hitbox, hitbxlegit, ARRAYSIZE( hitbxlegit ) );
			}
			if ( mota == 1 )
			{
				ImGui::Checkbox( "enable##snuPistolssaenable", &Variables.aimbot.Pistols.Enabled );
				ImGui::Combo( "type##aimtypppe", &Variables.aimbot.Pistols.AimType, aimlegitrtype, ARRAYSIZE( aimlegitrtype ) );
				ImGui::SliderFloat( "fov##legitfovPistols", &Variables.aimbot.Pistols.Fov, 0, 10 );
				if ( Variables.aimbot.Pistols.AimType == 1 )
					ImGui::SliderFloat( "restrain##restrainPistols", &Variables.aimbot.Pistols.Fov, 0, 10 );
				ImGui::Checkbox( "auto rcs##rcsPistols", &Variables.aimbot.Pistols.Recoil );
				ImGui::Combo( "hitbox##hitboxlegitPistols", &Variables.aimbot.Pistols.Hitbox, hitbxlegit, ARRAYSIZE( hitbxlegit ) );

			}
			if ( mota == 2 )
			{
				ImGui::Checkbox( "enable##snuriflessaenable", &Variables.aimbot.Rifles.Enabled );
				ImGui::Combo( "type##aimtypppe", &Variables.aimbot.Rifles.AimType, aimlegitrtype, ARRAYSIZE( aimlegitrtype ) );
				ImGui::SliderFloat( "fov##legitfovRifles", &Variables.aimbot.Rifles.Fov, 0, 10 );
				if ( Variables.aimbot.Rifles.AimType == 1 )
					ImGui::SliderFloat( "restrain##restrainRifles", &Variables.aimbot.Rifles.Fov, 0, 10 );
				ImGui::Checkbox( "auto rcs##rcsRifles", &Variables.aimbot.Rifles.Recoil );
				ImGui::Combo( "hitbox##hitboxlegitRifles", &Variables.aimbot.Rifles.Hitbox, hitbxlegit, ARRAYSIZE( hitbxlegit ) );
			}
		}ImGui::EndChild( );
	}
	void Renderesp( )
	{

		static int aaa22 = 0;
		ImGui::Columns( 2, NULL, false );
		ImGui::BeginChild( "##esptab1", ImVec2( 385, 450 ), true );
		{
			if ( ImGui::Button( "players", ImVec2( 192, 22 ) ) )
				aaa22 = 0;
			ImGui::SameLine( );
			if ( ImGui::Button( "world", ImVec2( -1, 22 ) ) )
				aaa22 = 1;

			if ( aaa22 == 0 )
			{//heh2


				ImGui::Checkbox( "Box", &Variables.Visuals.VisualsBox );
				ImGui::SameLine( );
				ImGui::ColorEdit3( "##boxcolz", Variables.Visuals.boxcolor, ImGuiColorEditFlags_NoInputs );
				ImGui::Checkbox( "Name", &Variables.Visuals.VisualsName );
				ImGui::SameLine( );
				ImGui::ColorEdit3( "##namecolz", Variables.Visuals.namecolor, ImGuiColorEditFlags_NoInputs );
				ImGui::Checkbox( "Health", &Variables.Visuals.VisualsHealth );
				ImGui::SameLine( );
				ImGui::ColorEdit3( "##healthcolor", Variables.Visuals.healthcolor, ImGuiColorEditFlags_NoInputs );
				ImGui::Checkbox( "Armor", &Variables.Visuals.VisualsArmor );
				ImGui::SameLine( );
				ImGui::ColorEdit3( "##armorcolz", Variables.Visuals.armorcolor, ImGuiColorEditFlags_NoInputs );
				ImGui::Checkbox( "Weapon", &Variables.Visuals.VisualsWeapon );
				ImGui::SameLine( );
				ImGui::ColorEdit3( "##weaponcolz", Variables.Visuals.weaponcolor, ImGuiColorEditFlags_NoInputs );
				ImGui::Checkbox( "Skeleton", &Variables.Visuals.VisualsSkeleton );
				ImGui::SameLine( );
				ImGui::ColorEdit3( "##skelecol", Variables.Visuals.skelecolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha );
				ImGui::Checkbox( "History", &Variables.Visuals.VisualsSkeletonHistory );
				ImGui::SameLine( );
				ImGui::ColorEdit3( "##historyskelecol", Variables.Visuals.skelehistorycolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha );
				ImGui::Spacing( );
				ImGui::Checkbox( "Flags", &Variables.Visuals.drawflags );
			}

			if ( aaa22 == 1 )
			{
				static const char* Skyboxmode [ ] =
				{
					"Off",
					"ymaja",
					"himalaya",
					"mijtm",
					"jungle",
					"new jok",
					"light",
					"night",
					"storm light",
					"galaxy"
				};

				ImGui::Combo( "Sky Changer", &Variables.Visuals.skychangar, Skyboxmode, IM_ARRAYSIZE( Skyboxmode ) );
				ImGui::Checkbox( "Nightmode", &Variables.Visuals.nightmode );
				ImGui::Checkbox( "Watermark", &Variables.Visuals.pwatermark );
				ImGui::Checkbox( "Cod Marker", &Variables.Visuals.playerhitmarker );
				ImGui::SameLine( );
				ImGui::ColorEdit3( "##markercol", Variables.Visuals.markercol, ImGuiColorEditFlags_NoInputs );
				ImGui::Combo( "Hitsound", &Variables.Visuals.hitsound, hitsounds, ARRAYSIZE( hitsounds ) );
				ImGui::Checkbox( "Grenade View", &Variables.Visuals.greane_prediction );
				ImGui::Checkbox( "Beams", &Variables.Visuals.beams );
				ImGui::SameLine( );
				ImGui::ColorEdit3( "##beamcolor", Variables.Visuals.beamcolor, ImGuiColorEditFlags_NoInputs );
				ImGui::Checkbox( "Lag Comp Hitbox", &Variables.Visuals.lagcompydady );
				ImGui::Checkbox( "Self Circle", &Variables.Visuals.selfcircle );
			}

		}
		ImGui::EndChild( );
		ImGui::Spacing( );
		ImGui::Spacing( );
		ImGui::Spacing( );
		ImGui::Spacing( );
		ImGui::BeginChild( "##esptab131313", ImVec2( 385, 130 ), true );
		{
			if ( aaa22 == 0 )
			{
				ImGui::Checkbox( "C4", &Variables.Visuals.drawc4 );
				ImGui::Checkbox( "Grenade", &Variables.Visuals.drawnades );
				ImGui::Checkbox( "Dropped Weapons", &Variables.Visuals.droppedweapons );
				ImGui::Checkbox( "Pov Arrows", &Variables.Visuals.povarrows );
				ImGui::SameLine( );
				ImGui::ColorEdit3( "##povawrroscol", Variables.Visuals.povarrowscol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar );
			}
			if ( aaa22 == 1 )
			{
				ImGui::Checkbox( "Aspect Ratio", &Variables.Visuals.aspectratioenable );
				ImGui::SliderInt( "Aspect X", &Variables.Visuals.aspectratiox, 0, 1000, ("%.1f") );
				ImGui::SliderInt( "Aspect Y", &Variables.Visuals.aspectratioxy, 0, 1000, ("%.1f") );
			}
		}ImGui::EndChild( );

		ImGui::NextColumn( );

		ImGui::BeginChild( "##esptab3", ImVec2( -1, 450 ), true );
		{
			if ( aaa22 == 0 )
			{
				ImGui::Text( "Chams" );
				static int chamz = 0;
				if ( ImGui::Button( "Entities", ImVec2( 127, 22 ) ) )
					chamz = 0;
				ImGui::SameLine( );
				if ( ImGui::Button( "Local", ImVec2( 127, 22 ) ) )
					chamz = 1;
				ImGui::SameLine( );
				if ( ImGui::Button( "Hand", ImVec2( -1, 22 ) ) )
					chamz = 2;

				if ( chamz == 0 )
				{
					ImGui::Checkbox( "Enable", &Variables.Visuals.VisualsChamsEnabled );

					ImGui::Combo( "Type", &Variables.Visuals.VisualsChamsMaterial, ChamsMaterials, ARRAYSIZE( ChamsMaterials ) );

					ImGui::Text( "Normal" );
					ImGui::SameLine( );
					ImGui::ColorEdit4( "##chamscolor", Variables.Visuals.VisualsChamsColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar );
					ImGui::Checkbox( "XQZ##chamsingorezenabled", &Variables.Visuals.VisualsChamsIgnoreZ );
					ImGui::SameLine( );
					ImGui::ColorEdit4( "##chamscolorignorez", Variables.Visuals.VisualsChamsColorIgnoreZ, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar );


				}
				if ( chamz == 1 )
				{
					ImGui::Checkbox( "Local Chams", &Variables.Visuals.enablelocalchams );
					ImGui::SameLine( );
					ImGui::ColorEdit4( "##localchamzucol", Variables.Visuals.localchamscol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar );
					ImGui::Combo( "Type", &Variables.Visuals.VisualsLocalChamsMaterial, ChamsMaterials, ARRAYSIZE( ChamsMaterials ) );
					ImGui::Text( "" );
					ImGui::Checkbox( "Desync Chams", &Variables.Visuals.desyncchamsenable );
					ImGui::SameLine( );
					ImGui::ColorEdit4( "##desynchjamzcol", Variables.Visuals.localdesynccol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar );
					ImGui::Combo( "Type##desyncchamstype", &Variables.Visuals.VisualsDesyncChamsMaterial, ChamsMaterials, ARRAYSIZE( ChamsMaterials ) );


				}
				if ( chamz == 2 )
				{
					ImGui::Checkbox( "Hand Chams", &Variables.Visuals.enablehandchams );
					ImGui::SameLine( );
					ImGui::ColorEdit4( "##Handchamzucol", Variables.Visuals.handchamscol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar );
					ImGui::Combo( "Type##ijosdfopi", &Variables.Visuals.VisualsHandChamsMaterial, ChamsMaterials, ARRAYSIZE( ChamsMaterials ) );
					ImGui::Text( "" );
					ImGui::Checkbox( "Weapon Chams", &Variables.Visuals.enableweaponchams );
					ImGui::SameLine( );
					ImGui::ColorEdit4( "##Weaponhjamzcol", Variables.Visuals.weaponchamscol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar );
					ImGui::Combo( "Type##Weaponchamstype", &Variables.Visuals.VisualsWeaponChamsMaterial, ChamsMaterials, ARRAYSIZE( ChamsMaterials ) );
				}

				if ( aaa22 == 0 )
				{
					ImGui::Text( "Glow" );
					static int glowzz = 0;
					if ( ImGui::Button( "Entities##1", ImVec2( 192, 22 ) ) )
						glowzz = 0;
					ImGui::SameLine( );
					if ( ImGui::Button( "Local##1", ImVec2( -1, 22 ) ) )
						glowzz = 1;
					if ( glowzz == 0 )
					{
						ImGui::Checkbox( "Enemy Glow", &Variables.Visuals.VisualsGlowEnabled );
						ImGui::SameLine( );
						ImGui::ColorEdit4( "##glowcolor", Variables.Visuals.VisualsGlowColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar );
						ImGui::Combo( "Style", &Variables.Visuals.VisualsGlowGlowstyle, GlowStyles, ARRAYSIZE( GlowStyles ) );
						//ImGui::SliderInt( "Alpha", &Variables.Visuals.VisualsGlowAlpha, 0, 255 );
					}
					if ( glowzz == 1 )
					{
						ImGui::Checkbox( "Local Glow", &Variables.Visuals.VisualsLocalGlowEnabled );
						ImGui::SameLine( );
						ImGui::ColorEdit4( "##glowlocalcolor", Variables.Visuals.VisualsLocalGlowColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar );
						ImGui::Combo( "Style", &Variables.Visuals.VisualsLocalGlowGlowstyle, GlowStyles, ARRAYSIZE( GlowStyles ) );
						//ImGui::SliderInt( "Alpha", &Variables.Visuals.VisualsLocalGlowAlphaz, 0, 255 );
					}


				}


			}

			if ( aaa22 == 1 )
			{

				ImGui::Checkbox( ("Keystrokes"), &Variables.Visuals.wasdindicator );
				ImGui::Checkbox( ("Kill Effect"), &Variables.Visuals.kill_effect );
				ImGui::Checkbox( ("Infobar"), &Variables.Visuals.infobar );
				ImGui::Spacing( );
				if ( Variables.Visuals.infobar )
				{
					ImGui::SliderInt( "Infobar X", &Variables.Visuals.infobarx, -5, 5, ("%.1f") );
					ImGui::SliderInt( "Infobar Y", &Variables.Visuals.infobary, -5, 5, ("%.1f") );
				}
				ImGui::Spacing( );
				ImGui::Checkbox( ("Misc Window"), &Variables.Visuals.miscbar );
				if ( Variables.Visuals.miscbar )
				{
					ImGui::SliderInt( "Misc Window X", &Variables.Visuals.miscbarx, -5, 5, ("%.1f") );
					ImGui::SliderInt( "Misc Window Y", &Variables.Visuals.miscbary, -5, 5, ("%.1f") );
				}
				ImGui::Checkbox( ("Preserve Killfeed"), &Variables.Visuals.preservekillfeed );



			}




		}ImGui::EndChild( );
		ImGui::Spacing( );
		ImGui::Spacing( );
		ImGui::Spacing( );
		ImGui::Spacing( );
		ImGui::BeginChild( "##raulenn", ImVec2( -1, 130 ), true );
		{
			if ( aaa22 == 0 )
			{
				ImGui::SliderFloat( "Field of View", &Variables.Visuals.fieldofview, 0.f, 150.f, ("%.1f") );
				ImGui::SliderFloat( "Viewmodel Fov", &Variables.Visuals.viewmodelfov, 0.f, 150.f, ("%.1f") );
				ImGui::SliderFloat( "View Offset X", &Variables.Visuals.viewmodeloffsetx, -30.f, 30.f, ("%.1f") );
				ImGui::SliderFloat( "View Offset Y", &Variables.Visuals.viewmodeloffsety, -30.f, 30.f, ("%.1f") );
				ImGui::SliderFloat( "View Offset Z", &Variables.Visuals.viewmodeloffsetz, -30.f, 30.f, ("%.1f") );
			}
			if ( aaa22 == 1 )
			{
				ImGui::Text( "Removals" );
				ImGui::Checkbox( "Visual Recoil", &Variables.Visuals.novisrecoil );
				ImGui::Checkbox( "Post Processing", &Variables.Visuals.nopostprocsess );
				ImGui::Checkbox( "Scope", &Variables.Visuals.VisualsNoScope );
				ImGui::Checkbox( "Smoke", &Variables.Visuals.nosmoke );
				ImGui::Checkbox( "Flash", &Variables.Visuals.noflash );
			}
		}ImGui::EndChild( );
	}
	void RenderMisc( )
	{//xd222
		ImGui::Columns( 2, NULL, false );
		ImGui::BeginChild( "##miscchild", ImVec2( 385, 600 ), true );
		{
			ImGui::Checkbox( "Bunnyhop", &Variables.Misc.bhop );
			ImGui::Checkbox( "AutoStrafe", &Variables.Misc.autostrafe );
			ImGui::Checkbox( "Server Hitboxes", &Variables.Misc.serverhitboxes );
			ImGui::Checkbox( "Events", &Variables.Misc.eventlogs );
			/*if ( ImGui::Button( "Rage quit", ImVec2( 137, 22 ) ) )
				Hooks::Shutdown( );*/
		}ImGui::EndChild( );

		ImGui::NextColumn( );

		ImGui::BeginChild( "##miscchild3", ImVec2( -1, 600 ), true );
		{
			static int extratab = 0;
			if ( ImGui::Button( "Config", ImVec2( -1, 22 ) ) )
				extratab = 0;
			if ( extratab == 0 )
			{
				using namespace ImGui;
				ImGui::Text( "Menu color" );
				ImGui::SameLine( );
				ImGui::ColorEdit3( "##menucol", Variables.menucolor, ImGuiColorEditFlags_NoInputs );
				//ImGui::Combo( "menu style##stylemenuiuaaa", &Variables.menustyle, styllamenu, ARRAYSIZE( styllamenu ) );
				getconfig( );
				ImGui::Spacing( );
				if ( ImGui::Combo( "cfg", &selectedcfg, [ ] ( void* data, int idx, const char** out_text )
					{
						*out_text = configs [ idx ].c_str( );
						return true;
					}, nullptr, configs.size( ), 10 ) )
				{
					cfgname = configs [ selectedcfg ];
					cfgname.erase( cfgname.length( ) - 4, 4 );
					strcpy( Variables.Misc.config_name, cfgname.c_str( ) );
				}

					ImGui::Spacing( );

					static bool create;
					if ( ImGui::Button( "Save" ) )
					{
						Config->Save( );
					}
					ImGui::SameLine( );
					if ( ImGui::Button( "Load" ) )
					{
						Config->Load( );

					}

					ImGui::Spacing( );

					if ( ImGui::Button( "New config", ImVec2( -1, 15 ) ) ) create = !create;
					if ( ImGui::Button( "Reset settings", ImVec2( -1, 15 ) ) ) Config->setup( );

					if ( create )
					{
						ImGui::Begin( "##create", &create, ImVec2( 160, 90 ), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar );
						ImGui::Text( "Config name:" );
						ImGui::InputText( "Name", Variables.Misc.config_name, 52 );
						if ( ImGui::Button( "Create & Save", ImVec2( -1, 15 ) ) )
						{
							Config->Save( );
							create = !create;
						}
						if ( ImGui::Button( "Cancel", ImVec2( -1, 15 ) ) )
							create = !create;
						ImGui::End( );
					}
			}
		}
		ImGui::EndChild( );

	}
	void RenderSkins( )
	{

	}
}
void Menu::RenderMenu( )
{
	if ( !Visible )
		return;

	ImGui_ImplDX9_NewFrame( );

	ImGui::GetIO( ).MouseDrawCursor = Visible;

	auto& style = ImGui::GetStyle( );
	if (ImGui::Begin("VERSAS.GG"), &Visible, ImVec2(1450, 359), 0.8f)
	{

		ImGui::SameLine();
	

		ImGui::SameLine();


		ImGui::BeginChild("vittu", ImVec2(350, 320), true);
		{
			ImGui::Text(("Ragebot"));
			ImGui::Text("General");
			ImGui::Checkbox("Enable", &Variables.rageaimbot.rageenable);
		
			ImGui::Checkbox("Resolver", &Variables.rageaimbot.resolverenable);
			ImGui::Checkbox("Resolver2", &Variables.rageaimbot.resolverenable2);
			ImGui::Checkbox("Pitch Resolver", &Variables.rageaimbot.pitchresolver);
			ImGui::Checkbox("Auto fire", &Variables.rageaimbot.autofire);




			ImGui::Combo("Double-Tap", &Variables.rageaimbot.doubletab, dttt, ARRAYSIZE(dttt));
			if (Variables.rageaimbot.doubletab == 1)
			{
				ImGui::Hotkey("##snekegay", &Variables.rageaimbot.fastshoot, ImVec2(40, 20));
			}
			ImGui::Text("Safety checks");
			ImGui::Checkbox("Safe point", &Variables.rageaimbot.safepoint);
			ImGui::Checkbox("Lethal", &Variables.rageaimbot.baimiflethal);
			ImGui::Checkbox("Baim After 3 Misses", &Variables.rageaimbot.baimafter3misses);
			ImGui::Hotkey("Baim key", &Variables.rageaimbot.baimkey);
			ImGui::Checkbox("Auto Zeus", &Variables.rageaimbot.autozeus);
			ImGui::Checkbox("Auto Knife", &Variables.rageaimbot.autoknife);
			ImGui::Checkbox("Auto R8", &Variables.rageaimbot.autorevolvo);
			ImGui::Checkbox("Auto Scope", &Variables.rageaimbot.rageautoscope);
			ImGui::Checkbox("Auto Stop", &Variables.rageaimbot.rageautostop);
			static int weapons = 0;

			ImGui::Text("Weapon Config");
			ImGui::Combo("Weapons", &weapons, wps, ARRAYSIZE(wps));
			if (weapons == 0)
			{
				ImGui::SliderInt("Hitchance", &Variables.rageaimbot.auto_hitchance, 0, 100);
				ImGui::SliderInt("Minimum Damage", &Variables.rageaimbot.auto_mindamage, 0, 100);
				ImGui::SliderInt("Visible Damage", &Variables.rageaimbot.auto_mindamagevisible, 0, 100);
				ImGui::Checkbox("multipoint##multipoint", &Variables.rageaimbot.auto_multipoint);
				if (Variables.rageaimbot.auto_multipoint)
				{
					ImGui::SliderInt("Head Scale", &Variables.rageaimbot.auto_headscale, 0.0, 1.0);
					ImGui::SliderInt("Body Scale", &Variables.rageaimbot.auto_bodyscale, 0.0, 1.0);
				}
				ImGui::ListBoxHeader(""); {
					ImGui::Selectable("Head", &Variables.rageaimbot.auto_head);
					ImGui::Selectable("Neck", &Variables.rageaimbot.auto_neck);
					ImGui::Selectable("Chest", &Variables.rageaimbot.auto_chest);
					ImGui::Selectable("Body", &Variables.rageaimbot.auto_body);
					ImGui::Selectable("Stomach", &Variables.rageaimbot.auto_stomach);
					ImGui::Selectable("Pelvis", &Variables.rageaimbot.auto_pelvis);
					ImGui::Selectable("Arms", &Variables.rageaimbot.auto_arms);
					ImGui::Selectable("Legs", &Variables.rageaimbot.auto_legs);
					ImGui::Selectable("Feet", &Variables.rageaimbot.auto_toes);
				}
				ImGui::ListBoxFooter();
			}
			if (weapons == 1)
			{
				ImGui::SliderInt("Hitchance", &Variables.rageaimbot.scout_hitchance, 0, 100);
				ImGui::SliderInt("Minimum Damage", &Variables.rageaimbot.scout_mindamage, 0, 100);
				ImGui::SliderInt("Visible Damage", &Variables.rageaimbot.scout_mindamagevisible, 0, 100);
				ImGui::Checkbox("multipoint##multipoint", &Variables.rageaimbot.scout_multipoint);
				if (Variables.rageaimbot.scout_multipoint)
				{
					ImGui::SliderInt("Head Scale", &Variables.rageaimbot.scout_headscale, 0.0, 1.0);
					ImGui::SliderInt("Body Scale", &Variables.rageaimbot.scout_bodyscale, 0.0, 1.0);
				}
				ImGui::ListBoxHeader(""); {
					ImGui::Selectable("Head", &Variables.rageaimbot.scout_head);
					ImGui::Selectable("Neck", &Variables.rageaimbot.scout_neck);
					ImGui::Selectable("Chest", &Variables.rageaimbot.scout_chest);
					ImGui::Selectable("Body", &Variables.rageaimbot.scout_body);
					ImGui::Selectable("Stomach", &Variables.rageaimbot.scout_stomach);
					ImGui::Selectable("Pelvis", &Variables.rageaimbot.scout_pelvis);
					ImGui::Selectable("Arms", &Variables.rageaimbot.scout_arms);
					ImGui::Selectable("Legs", &Variables.rageaimbot.scout_legs);
					ImGui::Selectable("Feet", &Variables.rageaimbot.scout_toes);
				}
				ImGui::ListBoxFooter();
			}
			if (weapons == 2)
			{
				ImGui::SliderInt("Hitchance", &Variables.rageaimbot.awp_hitchance, 0, 100);
				ImGui::SliderInt("Minimum Damage", &Variables.rageaimbot.awp_mindamage, 0, 100);
				ImGui::SliderInt("Visible Damage", &Variables.rageaimbot.awp_mindamagevisible, 0, 100);
				ImGui::Checkbox("multipoint##multipoint", &Variables.rageaimbot.awp_multipoint);
				if (Variables.rageaimbot.awp_multipoint)
				{
					ImGui::SliderInt("Head Scale", &Variables.rageaimbot.awp_headscale, 0.0, 1.0);
					ImGui::SliderInt("Body Scale", &Variables.rageaimbot.awp_bodyscale, 0.0, 1.0);
				}
				ImGui::ListBoxHeader(""); {
					ImGui::Selectable("Head", &Variables.rageaimbot.awp_head);
					ImGui::Selectable("Neck", &Variables.rageaimbot.awp_neck);
					ImGui::Selectable("Chest", &Variables.rageaimbot.awp_chest);
					ImGui::Selectable("Body", &Variables.rageaimbot.awp_body);
					ImGui::Selectable("Stomach", &Variables.rageaimbot.awp_stomach);
					ImGui::Selectable("Pelvis", &Variables.rageaimbot.awp_pelvis);
					ImGui::Selectable("Arms", &Variables.rageaimbot.awp_arms);
					ImGui::Selectable("Legs", &Variables.rageaimbot.awp_legs);
					ImGui::Selectable("Feet", &Variables.rageaimbot.awp_toes);
				}
				ImGui::ListBoxFooter();
			}
			if (weapons == 3)
			{
				ImGui::SliderInt("Hitchance", &Variables.rageaimbot.heavy_pistol_hitchance, 0, 100);
				ImGui::SliderInt("Minimum Damage", &Variables.rageaimbot.heavy_pistol_mindamage, 0, 100);
				ImGui::SliderInt("Visible Damage", &Variables.rageaimbot.heavy_pistol_mindamagevisible, 0, 100);
				ImGui::Checkbox("multipoint##multipoint", &Variables.rageaimbot.heavy_pistol_multipoint);
				if (Variables.rageaimbot.heavy_pistol_multipoint)
				{
					ImGui::SliderInt("Head Scale", &Variables.rageaimbot.heavy_pistol_headscale, 0.0, 1.0);
					ImGui::SliderInt("Body Scale", &Variables.rageaimbot.heavy_pistol_bodyscale, 0.0, 1.0);
				}
				ImGui::ListBoxHeader(""); {
					ImGui::Selectable("Head", &Variables.rageaimbot.heavy_pistol_head);
					ImGui::Selectable("Neck", &Variables.rageaimbot.heavy_pistol_neck);
					ImGui::Selectable("Chest", &Variables.rageaimbot.heavy_pistol_chest);
					ImGui::Selectable("Body", &Variables.rageaimbot.heavy_pistol_body);
					ImGui::Selectable("Stomach", &Variables.rageaimbot.heavy_pistol_stomach);
					ImGui::Selectable("Pelvis", &Variables.rageaimbot.heavy_pistol_pelvis);
					ImGui::Selectable("Arms", &Variables.rageaimbot.heavy_pistol_arms);
					ImGui::Selectable("Legs", &Variables.rageaimbot.heavy_pistol_legs);
					ImGui::Selectable("Feet", &Variables.rageaimbot.heavy_pistol_toes);
				}
				ImGui::ListBoxFooter();
			}
			if (weapons == 4)
			{
				ImGui::SliderInt("Hitchance", &Variables.rageaimbot.hitchance, 0, 100);
				ImGui::SliderInt("Minimum Damage", &Variables.rageaimbot.minimumdmage, 0, 100);
				ImGui::SliderInt("Visible Damage", &Variables.rageaimbot.minimumdmagevisible, 0, 100);
				ImGui::Checkbox("multipoint##multipoint", &Variables.rageaimbot.multipoint);
				if (Variables.rageaimbot.multipoint)
				{
					ImGui::SliderInt("Head Scale", &Variables.rageaimbot.headscale, 0.0, 1.0);
					ImGui::SliderInt("Body Scale", &Variables.rageaimbot.bodyscale, 0.0, 1.0);
				}
				ImGui::ListBoxHeader(""); {
					ImGui::Selectable("Head", &Variables.rageaimbot.head);
					ImGui::Selectable("Neck", &Variables.rageaimbot.neck);
					ImGui::Selectable("Chest", &Variables.rageaimbot.chest);
					ImGui::Selectable("Body", &Variables.rageaimbot.body);
					ImGui::Selectable("Stomach", &Variables.rageaimbot.stomach);
					ImGui::Selectable("Pelvis", &Variables.rageaimbot.pelvis);
					ImGui::Selectable("Arms", &Variables.rageaimbot.arms);
					ImGui::Selectable("Legs", &Variables.rageaimbot.legs);
					ImGui::Selectable("Feet", &Variables.rageaimbot.toes);
				}
				ImGui::ListBoxFooter();
			}
		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("vittu4", ImVec2(350, 320), true);
		{
			ImGui::Text("Antiaim");
			
			ImGui::Checkbox("enable##aaenable", &Variables.rageaimbot.antiaimenable);
			ImGui::Combo("pitch##pitchu", &Variables.rageaimbot.pitch, pitchzzz, ARRAYSIZE(pitchzzz));
			ImGui::Checkbox("AUTO DIRECTION", &Variables.rageaimbot.autodirection);
			static int aamode = 0;
			if (ImGui::Button("stand", ImVec2(89, 16)))
				aamode = 0;
			ImGui::SameLine();
			if (ImGui::Button("move", ImVec2(89, 16)))
				aamode = 1;
			ImGui::SameLine();
			if (ImGui::Button("air", ImVec2(89, 16)))
				aamode = 2;

			if (aamode == 0)
			{
				ImGui::Combo("stand yaw##standaa", &Variables.rageaimbot.standingaa, pitchzzz2, ARRAYSIZE(pitchzzz));
				ImGui::Checkbox("stand jitter##standhitterenable", &Variables.rageaimbot.jitterenablestanding);
				if (Variables.rageaimbot.standingaa == 2)
				{
					ImGui::Hotkey("Left", &Variables.rageaimbot.left);
					ImGui::Hotkey("Right", &Variables.rageaimbot.right);
					ImGui::Hotkey("Back", &Variables.rageaimbot.back);
					ImGui::Hotkey("Front", &Variables.rageaimbot.front);
				}
				if (Variables.rageaimbot.jitterenablestanding)
					ImGui::SliderInt("value##standjittervaluezz", &Variables.rageaimbot.jittervaluestanding, -100, 100);
			}
			if (aamode == 1)
			{
				ImGui::Combo("move yaw##niveaa", &Variables.rageaimbot.movingaa, pitchzzz2, ARRAYSIZE(pitchzzz));
				ImGui::Checkbox("move jitter##jittermovingenable", &Variables.rageaimbot.jitterenablemoving);
				if (Variables.rageaimbot.movingaa == 2)
				{
					ImGui::Hotkey("Left", &Variables.rageaimbot.left);
					ImGui::Hotkey("Right", &Variables.rageaimbot.right);
					ImGui::Hotkey("Back", &Variables.rageaimbot.back);
					ImGui::Hotkey("Front", &Variables.rageaimbot.front);
				}
				if (Variables.rageaimbot.jitterenablemoving)
					ImGui::SliderInt("value##jittervaluemoving", &Variables.rageaimbot.jittervaluemoving, -100, 100);
			}
			if (aamode == 2)
			{
				ImGui::Combo("air yaw##airaaa", &Variables.rageaimbot.airaa, pitchzzz2, ARRAYSIZE(pitchzzz));
				ImGui::Checkbox("air jitter##airjhitterenable", &Variables.rageaimbot.jitterenableair);
				if (Variables.rageaimbot.airaa == 2)
				{
					ImGui::Hotkey("Left", &Variables.rageaimbot.left);
					ImGui::Hotkey("Right", &Variables.rageaimbot.right);
					ImGui::Hotkey("Back", &Variables.rageaimbot.back);
					ImGui::Hotkey("Front", &Variables.rageaimbot.front);
				}
				if (Variables.rageaimbot.jitterenableair)
					ImGui::SliderInt("value##jittervalueeaiurrre", &Variables.rageaimbot.jittervalueair, -100, 100);

			}
			ImGui::Combo("Desync type", &Variables.rageaimbot.desynctype, desynbc, ARRAYSIZE(desynbc));
			if (Variables.rageaimbot.desynctype == 1)
			{
				ImGui::Hotkey("Desync Inverter", &Variables.rageaimbot.staticinverter, ImVec2(40, 20));
				ImGui::SliderInt("Bodylean", &Variables.rageaimbot.staticrightsidevalue, 0, 100);
				ImGui::SliderInt("Inverted Bodylean", &Variables.rageaimbot.staticleftsidevalue, 0, 100);
			}
			ImGui::Checkbox("Slowwalk", &Variables.Misc.slowwalk);
			if (Variables.Misc.slowwalk)
			{
				ImGui::SliderInt("Speed", &Variables.Misc.slowwalkspeed, 0, 100);
				ImGui::Hotkey("##tastafgm1", &Variables.rageaimbot.slowwalkkey, ImVec2(40, 20));
			}

			ImGui::Text("Fakelag");
			ImGui::SliderInt("Amount", &Variables.Misc.MiscFakelagChoke, 0, 14);
			ImGui::Spacing();

			ImGui::Checkbox("Fakeduck##1", &Variables.rageaimbot.fakeduckenable);
			if (Variables.Misc.slowwalk)
				ImGui::Hotkey("##tastafgm", &Variables.rageaimbot.fakeduckkey, ImVec2(40, 20));
			ImGui::Checkbox("Bunnyhop", &Variables.Misc.bhop);
			ImGui::Checkbox("AutoStrafe", &Variables.Misc.autostrafe);
			ImGui::Checkbox("Server Hitboxes", &Variables.Misc.serverhitboxes);
			ImGui::Checkbox("Events", &Variables.Misc.eventlogs);


		}ImGui::EndChild();

		ImGui::SameLine();

		ImGui::SameLine();
		ImGui::BeginChild("vittu2", ImVec2(350, 320), true);
		{
			static int aaa22 = 0;
			ImGui::Text("Visuals");
			if (ImGui::Button("players", ImVec2(135, 22)))
				aaa22 = 0;
			ImGui::SameLine();
			if (ImGui::Button("world", ImVec2(135, 22)))
				aaa22 = 1;

			if (aaa22 == 0)
			{
				ImGui::Checkbox("Box", &Variables.Visuals.VisualsBox);
				ImGui::SameLine();
				ImGui::ColorEdit3("##boxcolz", Variables.Visuals.boxcolor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Name", &Variables.Visuals.VisualsName);
				ImGui::SameLine();
				ImGui::ColorEdit3("##namecolz", Variables.Visuals.namecolor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Health", &Variables.Visuals.VisualsHealth);
				ImGui::SameLine();
				ImGui::ColorEdit3("##healthcolor", Variables.Visuals.healthcolor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Armor", &Variables.Visuals.VisualsArmor);
				ImGui::SameLine();
				ImGui::ColorEdit3("##armorcolz", Variables.Visuals.armorcolor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Weapon", &Variables.Visuals.VisualsWeapon);
				ImGui::SameLine();
				ImGui::ColorEdit3("##weaponcolz", Variables.Visuals.weaponcolor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Skeleton", &Variables.Visuals.VisualsSkeleton);
				ImGui::SameLine();
				ImGui::ColorEdit3("##skelecol", Variables.Visuals.skelecolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
				ImGui::Checkbox("History", &Variables.Visuals.VisualsSkeletonHistory);
				ImGui::SameLine();
				ImGui::ColorEdit3("##historyskelecol", Variables.Visuals.skelehistorycolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
				ImGui::Checkbox("Flags", &Variables.Visuals.drawflags);

			}

			if (aaa22 == 1)
			{
				ImGui::Checkbox("C4", &Variables.Visuals.drawc4);
				ImGui::Checkbox("Grenade", &Variables.Visuals.drawnades);
				ImGui::Checkbox("Dropped Weapons", &Variables.Visuals.droppedweapons);
				ImGui::Checkbox("Pov Arrows", &Variables.Visuals.povarrows);
				ImGui::SameLine();
				ImGui::ColorEdit3("##povawrroscol", Variables.Visuals.povarrowscol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
				ImGui::Checkbox("Aspect Ratio", &Variables.Visuals.aspectratioenable);
				ImGui::SliderInt("Aspect X", &Variables.Visuals.aspectratiox, 0, 1000, ("%.1f"));
				ImGui::SliderInt("Aspect Y", &Variables.Visuals.aspectratioxy, 0, 1000, ("%.1f"));
			}
			if (aaa22 == 0)
			{
				ImGui::Checkbox(("Keystrokes"), &Variables.Visuals.wasdindicator);
				ImGui::Checkbox(("Kill Effect"), &Variables.Visuals.kill_effect);
				ImGui::Checkbox(("Preserve Killfeed"), &Variables.Visuals.preservekillfeed);
				ImGui::SliderFloat("Field of View", &Variables.Visuals.fieldofview, 0.f, 150.f, ("%.1f"));
				ImGui::SliderFloat("Viewmodel Fov", &Variables.Visuals.viewmodelfov, 0.f, 150.f, ("%.1f"));
				ImGui::SliderFloat("View Offset X", &Variables.Visuals.viewmodeloffsetx, -30.f, 30.f, ("%.1f"));
				ImGui::SliderFloat("View Offset Y", &Variables.Visuals.viewmodeloffsety, -30.f, 30.f, ("%.1f"));
				ImGui::SliderFloat("View Offset Z", &Variables.Visuals.viewmodeloffsetz, -30.f, 30.f, ("%.1f"));
			}

			if (aaa22 == 1)
			{
				static const char* Skyboxmode[] =
				{
					"Off",
					"ymaja",
					"himalaya",
					"mijtm",
					"jungle",
					"new jok",
					"light",
					"night",
					"storm light",
					"galaxy"
				};

				ImGui::Combo("Sky Changer", &Variables.Visuals.skychangar, Skyboxmode, IM_ARRAYSIZE(Skyboxmode));
				ImGui::Checkbox("Nightmode", &Variables.Visuals.nightmode);
				ImGui::Checkbox("Indicator", &Variables.Visuals.indicator);
				ImGui::Checkbox("Cod Marker", &Variables.Visuals.playerhitmarker);
				ImGui::SameLine();
				ImGui::ColorEdit3("##markercol", Variables.Visuals.markercol, ImGuiColorEditFlags_NoInputs);
				ImGui::Combo("Hitsound", &Variables.Visuals.hitsound, hitsounds, ARRAYSIZE(hitsounds));
				ImGui::Checkbox("Grenade View", &Variables.Visuals.greane_prediction);
				ImGui::Checkbox("Beams", &Variables.Visuals.beams);
				ImGui::SameLine();
				ImGui::ColorEdit3("##beamcolor", Variables.Visuals.beamcolor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Lag Comp Hitbox", &Variables.Visuals.lagcompydady);
				//	ImGui::Checkbox( "Self Circle", &Variables.Visuals.selfcircle );
			}
			if (aaa22 == 0)
			{
				ImGui::Text("chams");
				static int chamz = 0;
				if (ImGui::Button("entities", ImVec2(89, 22)))
					chamz = 0;
				ImGui::SameLine();
				if (ImGui::Button("local", ImVec2(89, 22)))
					chamz = 1;
				ImGui::SameLine();
				if (ImGui::Button("other", ImVec2(89, 22)))
					chamz = 2;

				if (chamz == 0)
				{
					ImGui::Checkbox("Enable", &Variables.Visuals.VisualsChamsEnabled);

					ImGui::Combo("Type", &Variables.Visuals.VisualsChamsMaterial, ChamsMaterials, ARRAYSIZE(ChamsMaterials));

					ImGui::Text("Normal");
					ImGui::SameLine();
					ImGui::ColorEdit4("##chamscolor", Variables.Visuals.VisualsChamsColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
					ImGui::Checkbox("XQZ##chamsingorezenabled", &Variables.Visuals.VisualsChamsIgnoreZ);
					ImGui::SameLine();
					ImGui::ColorEdit4("##chamscolorignorez", Variables.Visuals.VisualsChamsColorIgnoreZ, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
					ImGui::Checkbox("Layer Chams", &Variables.Visuals.enemy_layer);
					ImGui::SameLine();
					ImGui::ColorEdit4("##enemylayeschams", Variables.Visuals.enemy_layer_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
					ImGui::Combo("Type Layer##enemylaer", &Variables.Visuals.enemy_layer_int, ChamsMaterials, ARRAYSIZE(ChamsMaterials));


				}
				if (chamz == 1)
				{
					ImGui::Checkbox("Local Chams", &Variables.Visuals.enablelocalchams);
					ImGui::SameLine();
					ImGui::ColorEdit4("##localchamzucol", Variables.Visuals.localchamscol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
					ImGui::Combo("Type", &Variables.Visuals.VisualsLocalChamsMaterial, ChamsMaterials, ARRAYSIZE(ChamsMaterials));

					ImGui::Checkbox("Local Layer", &Variables.Visuals.local_layer);
					ImGui::SameLine();
					ImGui::ColorEdit4("##lcoallauer", Variables.Visuals.local_layer_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
					ImGui::Combo("Type Layer##localclaer", &Variables.Visuals.local_layer_material, ChamsMaterials, ARRAYSIZE(ChamsMaterials));


					ImGui::Checkbox("Desync Chams", &Variables.Visuals.desyncchamsenable);
					ImGui::SameLine();
					ImGui::ColorEdit4("##desynchjamzcol", Variables.Visuals.localdesynccol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
					ImGui::Combo("Type##desyncchamstype", &Variables.Visuals.VisualsDesyncChamsMaterial, ChamsMaterials, ARRAYSIZE(ChamsMaterials));

					ImGui::Checkbox("Desync Layer", &Variables.Visuals.desync_layer);
					ImGui::SameLine();
					ImGui::ColorEdit4("##desynclaercolor", Variables.Visuals.desync_layer_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
					ImGui::Combo("Type Layer##desynclayer", &Variables.Visuals.desync_layer_material, ChamsMaterials, ARRAYSIZE(ChamsMaterials));

				}

				if (chamz == 2)
				{
					ImGui::Checkbox("Hand Chams", &Variables.Visuals.enablehandchams);
					ImGui::SameLine();
					ImGui::ColorEdit4("##Handchamzucol", Variables.Visuals.handchamscol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
					ImGui::Combo("Type##ijosdfopi", &Variables.Visuals.VisualsHandChamsMaterial, ChamsMaterials, ARRAYSIZE(ChamsMaterials));

					ImGui::Checkbox("Weapon Chams", &Variables.Visuals.enableweaponchams);
					ImGui::SameLine();
					ImGui::ColorEdit4("##Weaponhjamzcol", Variables.Visuals.weaponchamscol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
					ImGui::Combo("Type##Weaponchamstype", &Variables.Visuals.VisualsWeaponChamsMaterial, ChamsMaterials, ARRAYSIZE(ChamsMaterials));

				}

			}


			if (aaa22 == 1)
			{
				ImGui::Text("Removals");
				ImGui::Checkbox("Visual Recoil", &Variables.Visuals.novisrecoil);
				ImGui::Checkbox("Post Processing", &Variables.Visuals.nopostprocsess);
				ImGui::Checkbox("Scope", &Variables.Visuals.VisualsNoScope);
				ImGui::Checkbox("Smoke", &Variables.Visuals.nosmoke);
				ImGui::Checkbox("Flash", &Variables.Visuals.noflash);
			}
								if ( aaa22 == 0 )
					{
						ImGui::Text( "glow" );
						static int glowzz = 0;
						if ( ImGui::Button( "entities", ImVec2( 137, 22 ) ) )
							glowzz = 0;
						ImGui::SameLine( );
						if ( ImGui::Button( "local", ImVec2( 137, 22 ) ) )
							glowzz = 1;
						if ( glowzz == 0 )
						{
							ImGui::Checkbox( "Enemy Glow", &Variables.Visuals.VisualsGlowEnabled );
							ImGui::SameLine( );
							ImGui::ColorEdit4( "##glowcolor", Variables.Visuals.VisualsGlowColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar );
							ImGui::Combo( "Style", &Variables.Visuals.VisualsGlowGlowstyle, GlowStyles, ARRAYSIZE( GlowStyles ) );

						}
						if ( glowzz == 1 )
						{
							ImGui::Checkbox( "Local Glow", &Variables.Visuals.VisualsLocalGlowEnabled );
							ImGui::SameLine( );
							ImGui::ColorEdit4( "##glowlocalcolor", Variables.Visuals.VisualsLocalGlowColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar );
							ImGui::Combo( "Style", &Variables.Visuals.VisualsLocalGlowGlowstyle, GlowStyles, ARRAYSIZE( GlowStyles ) );

						}


					}

					if ( aaa22 == 1 )
					{
						//player
					}

				//
//////

			////////


		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("vittu1", ImVec2(350, 320), true);
		{
			ImGui::Text("Misc");
			static int extratab = 0;
			ImGui::SameLine();
			if (ImGui::Button("config", ImVec2(137, 22)))
				extratab = 1;
			if (extratab == 1)
			{
				using namespace ImGui;
				ImGui::Text("Menu color");
				ImGui::SameLine();
				ImGui::ColorEdit3("##menucol", Variables.menucolor, ImGuiColorEditFlags_NoInputs);
				//ImGui::Combo( "menu style##stylemenuiuaaa", &Variables.menustyle, styllamenu, ARRAYSIZE( styllamenu ) );
				getconfig();
				ImGui::Spacing();
				if (ImGui::Combo("cfg", &selectedcfg, [](void* data, int idx, const char** out_text)
					{
						*out_text = configs[idx].c_str();
						return true;
					}, nullptr, configs.size(), 10))
				{
					cfgname = configs[selectedcfg];
					cfgname.erase(cfgname.length() - 4, 4);
					strcpy(Variables.Misc.config_name, cfgname.c_str());
				}

					ImGui::Spacing();

					static bool create;
					if (ImGui::Button("Save"))
					{
						Config->Save();
					}
					ImGui::SameLine();
					if (ImGui::Button("Load"))
					{
						Config->Load();

					}

					ImGui::Spacing();


					if (ImGui::Button("Reset settings", ImVec2(-1, 15))) Config->setup();
					ImGui::Text("Config name:");
					ImGui::InputText("Name", Variables.Misc.config_name, 52);
					if (ImGui::Button("Create & Save", ImVec2(-1, 15)))
					{
						Config->Save();
						create = !create;
					}
					if (ImGui::Button("Cancel", ImVec2(-1, 15)))
						create = !create;

			}
		}ImGui::EndChild();

		ImGui::Separator();

		ImGui::SameLine();

		ImGui::SameLine();


		ImGui::SameLine();

	}






	ImGui::Render( );
	//ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}


void Menu::Show( )
{
	Visible = true;
}

void Menu::Hide( )
{
	Visible = false;
}

void Menu::Toggle( )
{
	Visible = !Visible;
}








void Menu::CreateStyle( )
{
	ImGui::GetIO( ).Fonts->AddFontFromMemoryCompressedTTF( Droid_compressed_data, Droid_compressed_size, 14.f, NULL, ImGui::GetIO( ).Fonts->GetGlyphRangesCyrillic( ) );
	ImGuiStyle& style = ImGui::GetStyle( );

	style.WindowPadding = ImVec2(15, 15);
	style.WindowRounding = 5.0f;
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 4.0f;
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 3.0f;

	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);


	style.Alpha = 1.0f;             // Global alpha applies to everything in ImGui
	style.WindowPadding = ImVec2( 8, 8 );      // Padding within a window
	style.WindowRounding = 0.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	style.WindowTitleAlign = ImVec2( 0.5f, 0.5f );// Alignment for title bar text
	style.FramePadding = ImVec2( 4, 1 );      // Padding within a framed rectangle (used by most widgets)
	style.FrameRounding = 0.0f;             // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
	style.ItemSpacing = ImVec2( 8, 4 );      // Horizontal and vertical spacing between widgets/lines
	style.ItemInnerSpacing = ImVec2( 4, 4 );      // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
	style.TouchExtraPadding = ImVec2( 0, 0 );      // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
	style.IndentSpacing = 21.0f;            // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	style.ColumnsMinSpacing = 6.0f;             // Minimum horizontal spacing between two columns
	style.ScrollbarSize = 10.0f;            // Width of the vertical scrollbar, Height of the horizontal scrollbar
	style.ScrollbarRounding = 3.0f;             // Radius of grab corners rounding for scrollbar
	style.GrabMinSize = 10.0f;            // Minimum width/height of a grab box for slider/scrollbar
	style.GrabRounding = 0.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	style.ButtonTextAlign = ImVec2( 0.5f, 0.5f );// Alignment of button text when button is larger than text.
	style.DisplayWindowPadding = ImVec2( 22, 22 );    // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular windows.
	style.DisplaySafeAreaPadding = ImVec2( 4, 4 );      // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
	style.AntiAliasedLines = true;             // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
	style.CurveTessellationTol = 1.25f;            // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.

	bigmenu_font = ImGui::GetIO( ).Fonts->AddFontFromMemoryCompressedBase85TTF( rawData_compressed_data_base85, 70 );
	menu_font = ImGui::GetIO( ).Fonts->AddFontFromMemoryCompressedBase85TTF( rawData_compressed_data_base85, 18 );
	smallmenu_font = ImGui::GetIO( ).Fonts->AddFontFromMemoryCompressedBase85TTF( smalll_compressed_data_base85, 13 );
}

















































