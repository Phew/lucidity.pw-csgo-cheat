#pragma once
#include "../valve_sdk/csgostructs.hpp"
class CCSGrenadeHint : public Singleton<CCSGrenadeHint>
{
public:
	void Tick(int buttons);
	void View();
	void Paint();

	void Setup(C_BasePlayer* pl, Vector& vecSrc, Vector& vecThrow, const Vector& angEyeAngles);
	void Simulate(Vector& Angles, C_BasePlayer* pLocal);
	int Step(Vector& vecSrc, Vector& vecThrow, int tick, float interval);
	bool CheckDetonate(const Vector& vecThrow, const trace_t& tr, int tick, float interval);
	void TraceHull(Vector& src, Vector& end, trace_t& tr);
	void AddGravityMove(Vector& move, Vector& vel, float frametime, bool onground);
	void PushEntity(Vector& src, const Vector& move, trace_t& tr);
	void ResolveFlyCollisionCustom(trace_t& tr, Vector& vecVelocity, float interval);
	int PhysicsClipVelocity(const Vector& in, const Vector& normal, Vector& out, float overbounce);

	enum
	{
		ACT_NONE,
		ACT_LOB,
		ACT_DROP,
		ACT_THROW
	};

	int act = 0;
	int type = 0;
	std::vector<Vector> path;
	std::vector<std::pair<Vector, Vector>> OtherCollisions;
	Color TracerColor = Color(255, 255, 0, 255);
	bool firegrenade_didnt_hit = false;
};