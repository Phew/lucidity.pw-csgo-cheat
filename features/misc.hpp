#include "../options.hpp"
#include "../valve_sdk/csgostructs.hpp"
#include "../helpers/math.hpp"
#include "../helpers/utils.hpp"
#include "../singleton.hpp"


namespace Misc
{
	void ClampMovement(CUserCmd* pCommand, float fMaxSpeed);

	void FakeLag(CUserCmd* cmd);
	void Bhop(CUserCmd* userCMD);
	void AutoStrafeDirection(CUserCmd* userCMD);
	void AutoStrafe(CUserCmd* userCMD);
	void Init();

}
