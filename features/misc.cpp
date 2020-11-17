#include "misc.hpp"
#include "..\globals\globals.hpp"


namespace Misc
{
	inline float FastSqrt222(float x)
	{
		unsigned int i = *(unsigned int*)&x;
		i += 127 << 23;
		i >>= 1;
		return *(float*)&i;
	}
#define square( x ) ( x * x )
	void ClampMovement(CUserCmd* pCommand, float fMaxSpeed)
	{
		if (fMaxSpeed <= 0.f)
			return;
		float fSpeed = (float)(FastSqrt222(square(pCommand->forwardmove) + square(pCommand->sidemove) + square(pCommand->upmove)));
		if (fSpeed <= 0.f)
			return;
		if (pCommand->buttons & IN_DUCK)
			fMaxSpeed *= 2.94117647f;
		if (fSpeed <= fMaxSpeed)
			return;
		float fRatio = fMaxSpeed / fSpeed;
		pCommand->forwardmove *= fRatio;
		pCommand->sidemove *= fRatio;
		pCommand->upmove *= fRatio;
	}
	template<class T, class U>
	T clamp(T in, U low, U high)
	{
		if (in <= low)
			return low;

		if (in >= high)
			return high;

		return in;
	}
	int32_t choked = 0;
	void FakeLag(CUserCmd* cmd)
	{
		if (g_EngineClient->IsVoiceRecording())
			return;
		if (!g_LocalPlayer)
			return;


		auto NetChannel = g_EngineClient->GetNetChannel();

		if (!NetChannel)
			return;
		globals::bSendPacket = true;

		if (GetAsyncKeyState(0x45))
		{
			globals::bSendPacket = (NetChannel->m_nChokedPackets >= 2);
		}
		else
		{
			if (GetAsyncKeyState(Variables.rageaimbot.fakeduckkey))
			{
				globals::bSendPacket = globals::chockepack > 15;
				globals::chockepack = globals::chockepack > 15 ? 0 : globals::chockepack + 1;

				cmd->buttons |= 0x400000;

				auto d = 15 / 2;

				if (globals::chockepack <= d)
					cmd->buttons &= ~0x4;
				else
					cmd->buttons |= 0x4;

			}
			else
			{
				globals::chockepack = Variables.Misc.MiscFakelagChoke;
				globals::bSendPacket = (NetChannel->m_nChokedPackets >= globals::chockepack);
			}
		}
		
	
	}
	void Bhop(CUserCmd* userCMD)
	{
		if (!g_LocalPlayer)
			return;

		if (g_LocalPlayer->m_nMoveType() == MOVETYPE_NOCLIP || g_LocalPlayer->m_nMoveType() == MOVETYPE_LADDER) return;
		if (userCMD->buttons & IN_JUMP && !(g_LocalPlayer->m_fFlags() & FL_ONGROUND)) {
			userCMD->buttons &= ~IN_JUMP;
		}
	}


	void AutoStrafeDirection(CUserCmd* userCMD)
	{
		if (!g_LocalPlayer) return;
		if (g_LocalPlayer->m_fFlags() & FL_ONGROUND && !(userCMD->buttons & IN_JUMP)) return;
		if (g_LocalPlayer->m_nMoveType() & (MOVETYPE_LADDER | MOVETYPE_NOCLIP)) return;

		/*						W						A							S						D*/
		if (GetAsyncKeyState(0x57) || GetAsyncKeyState(0x41) || GetAsyncKeyState(0x53) || GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_SHIFT))
			return;

		if (!(g_LocalPlayer->m_fFlags() & FL_ONGROUND)) {
			if (userCMD->mousedx > 1 || userCMD->mousedx < -1) {
				userCMD->sidemove = clamp(userCMD->mousedx < 0.f ? -450.0f : 450.0f, -450.0f, 450.0f);
			}
			else {
				userCMD->forwardmove = 10000.f / g_LocalPlayer->m_vecVelocity().Length();
				userCMD->sidemove = (userCMD->command_number % 2) == 0 ? -450.0f : 450.0f;
				if (userCMD->forwardmove > 450.0f)
					userCMD->forwardmove = 450.0f;
			}
		}
	}
	void AutoStrafe(CUserCmd* userCMD)
	{
		if (!g_LocalPlayer)
			return;
		if (g_LocalPlayer->m_nMoveType() == MOVETYPE_NOCLIP || g_LocalPlayer->m_nMoveType() == MOVETYPE_LADDER || !g_LocalPlayer->IsAlive()) return;

		// If we're not jumping or want to manually move out of the way/jump over an obstacle don't strafe.
		if (!g_InputSystem->IsButtonDown(ButtonCode_t::KEY_SPACE) ||
			g_InputSystem->IsButtonDown(ButtonCode_t::KEY_A) ||
			g_InputSystem->IsButtonDown(ButtonCode_t::KEY_D) ||
			g_InputSystem->IsButtonDown(ButtonCode_t::KEY_S) ||
			g_InputSystem->IsButtonDown(ButtonCode_t::KEY_W))
			return;

		if (!(g_LocalPlayer->m_fFlags() & FL_ONGROUND)) {
			if (userCMD->mousedx > 1 || userCMD->mousedx < -1) {
				userCMD->sidemove = clamp(userCMD->mousedx < 0.f ? -400.f : 400.f, -400, 400);
			}
			else {
				if (g_LocalPlayer->m_vecVelocity().Length2D() == 0 || g_LocalPlayer->m_vecVelocity().Length2D() == NAN || g_LocalPlayer->m_vecVelocity().Length2D() == INFINITE)
				{
					userCMD->forwardmove = 400;
					return;
				}
				userCMD->forwardmove = clamp(5850.f / g_LocalPlayer->m_vecVelocity().Length2D(), -400, 400);
				if (userCMD->forwardmove < -400 || userCMD->forwardmove > 400)
					userCMD->forwardmove = 0;
				userCMD->sidemove = clamp((userCMD->command_number % 2) == 0 ? -400.f : 400.f, -400, 400);
				if (userCMD->sidemove < -400 || userCMD->sidemove > 400)
					userCMD->sidemove = 0;
			}
		}
	}

	void Init()
	{
		if (globals::pCmd)
		{
			if (Variables.Misc.bhop)
				Misc::Bhop(globals::pCmd);

			if (Variables.Misc.autostrafe && g_LocalPlayer->IsAlive())
				Misc::AutoStrafeDirection(globals::pCmd);

			Misc::FakeLag(globals::pCmd);
		}

	}
}




















































