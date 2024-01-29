#pragma once
#include "Player_Enum.h"

class ChangeState
{
private:
	bool ChangeToIdleMove(EAniState_Move& stateValue);

	bool ChangeToWalkMove(EAniState_Move& stateValue);

	bool ChangeToRunMove(EAniState_Move& stateValue);

	bool ChangeToJumpMove(EAniState_Move& stateValue);

	bool ChangeToFallMove(EAniState_Move& stateValue);
	
public:
	bool ChangeMove(EAniState_Move& Before,const EAniState_Move& After);
};
