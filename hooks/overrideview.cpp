
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


namespace Hooks
{

	float __fastcall GetViewModelFov_h(void* ECX, void* EDX)
	{
		return Variables.Visuals.viewmodelfov + o_GetViewmodelFov(ECX);
	}

	void __fastcall hkOverrideView(void* _this, int edx, CViewSetup* vsView)
	{
		static auto ofunc = clientmode_hook.get_original<decltype(&hkOverrideView)>(index::OverrideView);
		if (!g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
		{
			ofunc(g_ClientMode, edx, vsView);
			return;
		}


		CCSGrenadeHint::Get().View();

		if (g_LocalPlayer && g_LocalPlayer->m_iHealth() > 0)
		{
			if (!g_LocalPlayer->m_bIsScoped())
			{
				vsView->fov = 90 + Variables.Visuals.fieldofview;
			}
			else
			{
				if (Variables.Visuals.VisualsNoScope)
					vsView->fov = 90 + Variables.Visuals.fieldofview;
				else {

				}
			}
		}

		if (GetAsyncKeyState(Variables.rageaimbot.fakeduckkey) && g_LocalPlayer)
			vsView->origin.z = g_LocalPlayer->GetAbsOrigin().z + 64.f;

		ofunc(g_ClientMode, edx, vsView);
	}
}



















