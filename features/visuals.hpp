#pragma once
#include "../options.hpp"
#include "../valve_sdk/csgostructs.hpp"
#include "../helpers/math.hpp"
#include "../helpers/utils.hpp"
#include "../singleton.hpp"


class Render
	: public Singleton<Render>
{
	friend class Singleton<Render>;
private:

public:

	vgui::HFont namefont;
	vgui::HFont weaponfont;
	vgui::HFont flagfont;


	vgui::HFont eventesp;
	vgui::HFont esp_font;
	vgui::HFont bombtimerfont;
	vgui::HFont ui_font;
	vgui::HFont wasdindicator2;
	vgui::HFont infobaryas;
	vgui::HFont infobaryas2;
	vgui::HFont weapon_font;
	vgui::HFont indicators2;
	void CreateFonts( );
	void Text( int X, int Y, const char* Text, vgui::HFont Font, Color DrawColor, bool Center );

	void TextSize( int& Width, int& Height, const char* Text, vgui::HFont Font );
	Vector2D GetTextSize( unsigned int Font, std::string Input, ... );
	void FilledRectange( int X1, int Y1, int X2, int Y2, Color DrawColor );
	void OutlinedRectange( int X1, int Y1, int X2, int Y2, Color DrawColor );
	void Line( int X1, int Y1, int X2, int Y2, Color DrawColor );
	void DrawString( unsigned long font, int x, int y, Color color, unsigned long alignment, const char* msg, ... );
	void TexturedPolygon( int n, std::vector<Vertex_t> vertice, Color color );
};
class Chams
	: public Singleton<Chams>
{
	friend class Singleton<Chams>;
	Chams( );
	~Chams( );

public:
	void OnDrawModelExecute(
		IMatRenderContext* ctx,
		const DrawModelState_t& state,
		const ModelRenderInfo_t& pInfo,
		matrix3x4_t* pCustomBoneToWorld );
private:

	IMaterial* materialRegular = nullptr;
	IMaterial* materialRegularIgnoreZ = nullptr;
	IMaterial* materialFlat = nullptr;
	IMaterial* materialFlatIgnoreZ = nullptr;
	IMaterial* materialMetallic = nullptr;
	IMaterial* materialMetallicIgnoreZ = nullptr;
	IMaterial* materialDogtag = nullptr;
	IMaterial* materialGlowArmsrace = nullptr;
	IMaterial* materialEsoGlow = nullptr;
};

class Glow
	: public Singleton<Glow>
{
	friend class Singleton<Glow>;

	Glow( );
	~Glow( );

public:
	void Run( );
	void Shutdown( );
};

class Visuals
	: public Singleton<Visuals>
{
	friend class Singleton<Visuals>;
private:
	RECT GetBBox( C_BasePlayer* Player, Vector TransformedPoints[ ] );

	struct
	{
		C_BasePlayer* Player;
		RECT Box;
		Vector HeadPos;
		Vector Origin;
	} Context;
public:
	void Draw3dCube( float scalar, Vector angles, Vector middle_origin, Color outline );
	bool Begin( C_BasePlayer* Player );
	void Box( );
	void Name( );
	void Weapon( );
	void Health( );
	void DrawWatermark( );
	void RenderArmour( );
	
	void RenderSkelet( );
	void RenderSkeletBacktrack( C_BasePlayer* player );

	struct inferno_t : public C_BasePlayer
	{
		float get_spawn_time( )
		{
			return *reinterpret_cast< float* >( uintptr_t( this ) + 0x20 );
		}

		static float get_expiry_time( )
		{
			return 7.f;
		}
	};
	void drawbombplanetd( C_BasePlayer* entity );
	void MolotovTimer( C_BasePlayer* entity );
	void RenderWeapon( C_BasePlayer* entity );
	void RenderNadeEsp( C_BasePlayer* nade );


	void DrawFovArrows( C_BasePlayer* entity );

	void debugshotsmissed( C_BasePlayer* entity );

	void indcators( );

	void aaindicator( );

	void DrawFlags( );

	void drawcirclearoundlocal( );

	void run_viewmodel( );
	void DrawPoV( );
};