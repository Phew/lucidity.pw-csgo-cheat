#include "hooks.hpp"
#include <intrin.h>  
#include "../helpers/input.hpp"
#include "../options.hpp"
#include "../helpers/utils.hpp"
#include "../features/visuals.hpp"
#include "../features/ragebot.hpp"
#include "../menu/menu.hpp"
#include "../features/misc.hpp"
#include "../globals/globals.hpp"
#include "../features/resolver.hpp"
#include "../features/animfix.h"
#include "../features/events.h"
#include "../features/bullettracers.hpp"
#include "../features/grenadepred.h"
#include "../features/legitbot.hpp"
#include "../features/lagcomp.h"
#include "../features/codmarker.h"
#include "../features/Skinchanger.hpp"
#include "../features/antiaim.h"
#include "../features/predictionsystem.h"
namespace Hooks
{

	bool __fastcall hkCreateMove( PVOID _this, DWORD edx, float flInputSampleTime, CUserCmd* pCmd)
	{
		auto oCreateMove = clientmode_hook.get_original<CreateMove>(index::CreateMove);

		if (!g_LocalPlayer->IsAlive())
		{
			globals::last_doubletap = pCmd->tick_count;
			globals::doubletap_delta = 0;
		}
		if (!g_LocalPlayer)
		{
			globals::doubletap_delta = 0;
			globals::last_doubletap = 0;
			return oCreateMove( _this, flInputSampleTime, pCmd);
		}
		if (!g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
		{
			globals::doubletap_delta = 0;
			globals::last_doubletap = 0;
			return oCreateMove( _this, flInputSampleTime, pCmd);
		}
		if (!g_EngineClient->IsInGame() && !g_EngineClient->IsConnected() && !g_LocalPlayer)
			return oCreateMove( _this, flInputSampleTime, pCmd);

		if (!pCmd || !pCmd->command_number)
			return oCreateMove( _this, flInputSampleTime, pCmd);

		C_BaseCombatWeapon* Weapon = g_LocalPlayer->m_hActiveWeapon();
		if (!Weapon)
			return oCreateMove( _this, flInputSampleTime, pCmd);

		uintptr_t* framePtr;
		__asm mov framePtr, ebp;
		globals::pCmd = pCmd;
		CUserCmd origCmd = *pCmd;

		if (Menu::Get().IsVisible())
			pCmd->buttons &= ~IN_ATTACK;

		CCSGrenadeHint::Get().Tick(pCmd->buttons);
		Misc::Init();
		Vector wish_angle = pCmd->viewangles;

		Prediction::StartPrediction(pCmd, g_LocalPlayer);
		if (Variables.rageaimbot.rageenable)
		{
			//LagComp::StoreRecords();
			Aimbot_R::create_move(pCmd);
			Aimbot_R::dt(pCmd);
			if (Variables.rageaimbot.antiaimenable)
			 AntiAim::DoAntiaim(pCmd, Weapon);
			Aimbot_R::autor8();
			AntiAim::slowwalk();
			AntiAim::smallmovements();
		}
		if (Variables.enablelgit)
		{
			Legitbot::Do(pCmd, Weapon);
			if (Variables.aimbot.Backtrack)
				Backtrack::Get().Do(pCmd);
		}
	Prediction::EndPrediction(g_LocalPlayer);

		AntiAim::MovementFix(wish_angle);
		auto local_player = g_LocalPlayer;

		if (!globals::bSendPacket) {
			Hooks::RealAngle = pCmd->viewangles;
			globals::realAngle = pCmd->viewangles;
			AntiAim::LbyUpdate();
		}
		else {
			Hooks::FakeAngle = pCmd->viewangles.y;
			globals::fakeAngle = pCmd->viewangles;
		}
		Math::Normalize3(pCmd->viewangles);
		Math::ClampAngles(pCmd->viewangles);


		AntiAim::desynchams();
		*(bool*)(*framePtr - 0x1C) = globals::bSendPacket;




		return false;
	}
}





















