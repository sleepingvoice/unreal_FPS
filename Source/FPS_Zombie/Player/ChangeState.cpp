#include "ChangeState.h"

bool ChangeState::ChangeToIdleMove(EAniState_Move& stateValue)
{
	switch (stateValue)
	{
	case EAniState_Move::Idle :
		return true;
	case EAniState_Move::Walk :
		return true;
	case EAniState_Move::Run :
		return true;
	case EAniState_Move::Fall :
		return true;
	default :
		return false;
	}
}

bool ChangeState::ChangeToWalkMove(EAniState_Move& stateValue)
{
	switch (stateValue)
	{
	case EAniState_Move::Idle :
		return true;
	case EAniState_Move::Walk :
		return true;
	case EAniState_Move::Run :
		return true;
	default :
		return false;
	}
}

bool ChangeState::ChangeToRunMove(EAniState_Move& stateValue)
{
	switch (stateValue)
	{
	case EAniState_Move::Idle :
		return true;
	case EAniState_Move::Walk :
		return true;
	case EAniState_Move::Run :
		return true;
	default :
		return false;
	}
}

bool ChangeState::ChangeToJumpMove(EAniState_Move& stateValue)
{
	switch (stateValue)
	{
	case EAniState_Move::Idle :
		return true;
	case EAniState_Move::Walk :
		return true;
	case EAniState_Move::Run :
		return true;
	case EAniState_Move::Jump :
		return true;
	default :
		return false;
	}
}

bool ChangeState::ChangeToFallMove(EAniState_Move& stateValue)
{
	switch (stateValue)
	{
	case EAniState_Move::Jump :
		return true;
	default :
		return false;
	}
}

bool ChangeState::ChangeMove(EAniState_Move& Before,const EAniState_Move& After)
{
	switch (After)
	{
	case EAniState_Move::Idle :
		return ChangeToIdleMove(Before);
	case EAniState_Move::Walk :
		return ChangeToWalkMove(Before);
	case EAniState_Move::Run :
		return ChangeToRunMove(Before);
	case EAniState_Move::Jump :
		return ChangeToJumpMove(Before);
	case EAniState_Move::Fall :
		return ChangeToFallMove(Before);
	default :
		return false;
	}
}


