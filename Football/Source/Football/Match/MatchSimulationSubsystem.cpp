// Copyright, 2023, by NGD Studios AB. All rights reserved.


#include "MatchSimulationSubsystem.h"
#include "Football/Team/TeamGenerator.h"

const FVector2D UMatchSimulationSubsystem::PitchField = { 100.6, 64 };
const FVector2D UMatchSimulationSubsystem::GoalArea = { 7.32, 2.44 };
const FVector2D UMatchSimulationSubsystem::SmallArea = { 5.5, 18.32 };
const FVector2D UMatchSimulationSubsystem::BigArea = { 16.5, 40.3 };

static FVector GetFinalLocationFromPosition(EFieldPosition PlayingPosition, ELocalOrVisitor Place)
{
	//Diffs from starting pos
	FVector LocalToLocation[] = {
		FVector::ZeroVector, //0
		FVector::ZeroVector, //GK
		FVector(500.0f, -100.0f, 0.0f), //DL
		FVector(300.0f, 0.0f, 0.0f), //DC
		FVector(500.0f, 100.0f, 0.0f), //DR
		FVector(1700.0f, 0.0f, 0.0f),	//DM
		FVector(1800, 0.0f, 0.0f), //ML,
		FVector(2000, 0.0f, 0.0f), //MC,
		FVector(1800, 0.0f, 0.0f), ////MR,
		FVector(2400, 200.0f, 0.0f),	////AML,
		FVector(2800, 0.0f, 0.0f),	//AMC,
		FVector(2200, -200.0f, 0.0f),//AMR,
		FVector(3300, 0.0f, 0.0f),//ST,
	};

	if (Place == ELocalOrVisitor::Local)
	{
		return LocalToLocation[static_cast<int32>(PlayingPosition)];
	}
	else
	{
		FVector Location = LocalToLocation[static_cast<int32>(PlayingPosition)];
		Location.X *= -1;
		Location.Y *= -1;
		return Location;
	}
}

static FVector GetLocationFromPosition(EFieldPosition PlayingPosition, ELocalOrVisitor Place)
{
	FVector LocalToLocation[] = {
		FVector::ZeroVector, //0
		FVector(-5000.0f, 0.0f, 0.0f), //GK
		FVector(-3500.0f, 2500.0f, 0.0f), //DL
		FVector(-4000.0f, 0.0f, 0.0f), //DC
		FVector(-3500.0f, -2500.0f, 0.0f), //DR
		FVector(-2700.0f, 0.0f, 0.0f),	//DM
		FVector(-1800, 1500.0f, 0.0f), //ML,
		FVector(-2000, 0.0f, 0.0f), //MC,
		FVector(-1800, -1500.0f, 0.0f), //MR,
		FVector(-1100, -1200.0f, 0.0f),	//AML,
		FVector(-1100, 0.0f, 0.0f),	////AMC,
		FVector(-1100, 1200.0f, 0.0f),//AMR,
		FVector(-400, 0.0f, 0.0f),//ST,
	};

	if (Place == ELocalOrVisitor::Local)
	{
		return LocalToLocation[static_cast<int32>(PlayingPosition)];
	}
	else
	{
		FVector Location = LocalToLocation[static_cast<int32>(PlayingPosition)];
		Location.X *= -1;
		Location.Y *= -1;
		return Location;
	}
}

static void InitFootballer(FFootballerAgent* Agent, UFootballerObject* Footballer, ELocalOrVisitor Place)
{
	Agent->Footballer = Footballer;
	Agent->Location = GetLocationFromPosition(Footballer->Data.SelectedFieldPosition, Place);
}

static void SetDestination(FFootballerAgent* Agent, ELocalOrVisitor Place)
{
	FVector Destination = GetFinalLocationFromPosition(Agent->Footballer->Data.SelectedFieldPosition, ELocalOrVisitor::Local);
	if (Place != ELocalOrVisitor::Local)
	{
		Destination.X *= -1;
		Destination.Y *= -1;
	}
	Agent->State = EAgentState::Moving;
	Agent->Destination = Agent->Location + Destination;

}

TArray<FFootballerAgent*> UMatchSimulationSubsystem::GetFootballersAtPos(TStaticArray<FFootballerAgent, MaxStarters>& Footballers, EFieldPosition FieldPos)
{
	TArray<FFootballerAgent*> Ret;
	for (FFootballerAgent& Agent : Footballers)
	{
		if (Agent.Footballer->Data.SelectedFieldPosition == FieldPos)
		{
			Ret.Add(&Agent);
		}
	}

	return Ret;
}

static void FixUpPositions(const TArray<FFootballerAgent*>& Footballers, EFieldPosition Pos)
{
	if (Footballers.Num() > 1)
	{
		if (Pos == EFieldPosition::DC)
		{
			if (Footballers.Num() == 2)
			{
				Footballers[0]->Location.Y += 500;
				Footballers[1]->Location.Y -= 500;
			}
			else if (Footballers.Num() == 3)
			{
				Footballers[0]->Location.Y += 800;
				Footballers[2]->Location.Y -= 800;
			}
		}
		else if (Pos == EFieldPosition::DM)
		{
			Footballers[0]->Location.Y += 700;
			Footballers[1]->Location.Y -= 700;
		}
		else if (Pos == EFieldPosition::MC)
		{
			Footballers[0]->Location.Y += 400;
			Footballers[1]->Location.Y -= 400;
		}
		else if (Pos == EFieldPosition::AMC)
		{
			Footballers[0]->Location.Y += 300;
			Footballers[1]->Location.Y -= 300;
		}
		else if (Pos == EFieldPosition::ST)
		{
			Footballers[0]->Location.Y += 200;
			Footballers[1]->Location.Y -= 200;
		}
	}
}

void UMatchSimulationSubsystem::SetTeams(UTeam_Deprecated* PlayerTeam, UTeam_Deprecated* OpTeam)
{
	LocalTeam = PlayerTeam;
	VisitorTeam = OpTeam;

	//Set Initial positions
	for (int i=0; i<MaxStarters; ++i)
	{
		FFootballerAgent* Agent = LocalFootballers.GetData() + i;
		InitFootballer(Agent, LocalTeam->Starters[i], ELocalOrVisitor::Local);

		Agent = VisitorsFootballers.GetData() + i;
		InitFootballer(Agent, VisitorTeam->Starters[i], ELocalOrVisitor::Visitor);
	}

	//Set Striker near the ball
	TArray<FFootballerAgent*> Strikers = GetFootballersAtPos(LocalFootballers, EFieldPosition::ST);
	if (Strikers.Num() == 0)
	{
		Strikers = GetFootballersAtPos(LocalFootballers, EFieldPosition::AMC);
	}
	Strikers[0]->Location.X = -50;
	Strikers[0]->Location.Y = 0;

	//Fix duplicate locations
	//TODO: Remove me when data is pulled from the line up screen
	for (EFieldPosition Pos : TEnumRange<EFieldPosition>())
	{
		TArray<FFootballerAgent*> FootballersAtPos = GetFootballersAtPos(LocalFootballers, Pos);
		FixUpPositions(FootballersAtPos, Pos);

		FootballersAtPos = GetFootballersAtPos(VisitorsFootballers, Pos);
		FixUpPositions(FootballersAtPos, Pos);
	}

	//Set Destinations
	for (int i=0; i<MaxStarters; ++i)
	{
		FFootballerAgent* Agent = LocalFootballers.GetData() + i;
		SetDestination(Agent, ELocalOrVisitor::Local);

		Agent = VisitorsFootballers.GetData() + i;
		SetDestination(Agent, ELocalOrVisitor::Visitor);
	}

	VisitorsFootballers[10].Location.X = -50;
	VisitorsFootballers[10].Location.Y = 0;
}

//Stolen and adapted from VRand
static FVector2D RandomVec2()
{
	FVector2D Result;
	FVector2D::FReal L;

	do
	{
		// Check random vectors in the unit circle so result is statistically uniform.
		Result.X = FMath::FRand() * 2.f - 1.f;
		Result.Y = FMath::FRand() * 2.f - 1.f;
		L = Result.SizeSquared();
	} while (L > 1.0f || L < UE_KINDA_SMALL_NUMBER);

	return Result * (1.0f / FMath::Sqrt(L));
}

static int32 GetNearestFootballer(const FFootballerAgent *Agent, const TStaticArray<FFootballerAgent, UMatchSimulationSubsystem::MaxStarters>& LocalFootballers)
{
	int32 NearestIndex = 0;
	float MinDistSq = std::numeric_limits<float>::max();

	for (int32 i=0; i<LocalFootballers.Num(); ++i)
	{
		if (LocalFootballers[i].Footballer == Agent->Footballer)
			continue;

		float DistSq = FVector::DistSquared2D(Agent->Location, LocalFootballers[i].Location);
		if (DistSq < MinDistSq)
		{
			MinDistSq = DistSq;
			NearestIndex = i;
		}
	}

	return NearestIndex;
}

static TArray<FFootballerAgent*> SortFootballersByNearest(FFootballerAgent* Agent, TStaticArray<FFootballerAgent, UMatchSimulationSubsystem::MaxStarters> &AgentLocalFootballers)
{
	struct NearestPredicate
	{
		NearestPredicate(FVector InLocation):Location(InLocation){}
		bool operator()(const FFootballerAgent& A, const FFootballerAgent& B) const {
			return FVector::DistSquared2D(Location, A.Location) < FVector::DistSquared2D(Location, B.Location);
		}
	private:
		FVector Location;
	};

	TArray<FFootballerAgent*> Footballers;
	for (int32 i=0; i<AgentLocalFootballers.Num(); ++i)
	{
		FFootballerAgent* F = AgentLocalFootballers.GetData() + i;
		if (Agent->Footballer == F->Footballer)
			continue;

		Footballers.Add(F);
	}

	Footballers.Sort(std::move(NearestPredicate(Agent->Location)));

	return Footballers;
}

static TArray<FFootballerAgent*> GetFootballersInLocation(const FVector& Location, TStaticArray<FFootballerAgent, UMatchSimulationSubsystem::MaxStarters>& AgentLocalFootballers, TFunction<bool (float, float)> CompareFn)
{
	TArray<FFootballerAgent*> Result;

	for (int32 i = 0; i < AgentLocalFootballers.Num(); ++i)
	{
		FFootballerAgent* Agent = AgentLocalFootballers.GetData() + i;

		if (CompareFn(Agent->Location.X, Location.X))
		{
			Result.Add(Agent);
		}
	}

	return Result;
}

void UMatchSimulationSubsystem::ProcessAgent(FFootballerAgent* Agent, TStaticArray<FFootballerAgent, MaxStarters> &AgentLocalFootballers, const TStaticArray<FFootballerAgent, MaxStarters> &OtherFootballers, ELocalOrVisitor Place)
{
	float DistanceToBallSq = FVector::DistSquared(Ball.Location, Agent->Location);
	if (DistanceToBallSq < 100*100)
	{
		Agent->State = EAgentState::Moving;
		TArray<FFootballerAgent*> AttackingFootballers;
		if (Place == ELocalOrVisitor::Local)
		{
			AttackingFootballers = GetFootballersInLocation(Agent->Location, AgentLocalFootballers, [](float AgentLocX, float LocX) {return AgentLocX > LocX; });
		}
		else
		{
			AttackingFootballers = GetFootballersInLocation(Agent->Location, AgentLocalFootballers, [](float AgentLocX, float LocX) {return AgentLocX < LocX; });
		}

		FFootballerAgent* IntercepingAgent = nullptr;
		FVector GoalLocation;

		if (AttackingFootballers.Num() > 0)
		{
			int32 RIndex = FMath::RandRange(0, AttackingFootballers.Num()-1);
			IntercepingAgent = AttackingFootballers[RIndex];
		}
		else
		{
			if (Place == ELocalOrVisitor::Local)
				GoalLocation.X = 5000;
			else
				GoalLocation.X = -5000;

			float DistanceToGoal = FVector::DistSquared2D(Agent->Location, GoalLocation);
			if (DistanceToGoal < 2300*2300)
			{
				float GoalWidth = 732;
				//Shoot!
				GoalLocation.Y = FMath::RandRange(-GoalWidth / 2, GoalWidth / 2);
			}
			else
			{
				TArray<FFootballerAgent*> SortedAgents = SortFootballersByNearest(Agent, AgentLocalFootballers);
				int32 RandomNear = FMath::RandRange(0, 2);
				IntercepingAgent = SortedAgents[RandomNear];
			}
		}
		
		if (IntercepingAgent)
		{
			IntercepingAgent->State = EAgentState::InterceptingPass;
			FVector Dir = (IntercepingAgent->Location - Agent->Location).GetSafeNormal2D();
			Ball.Velocity = Dir * 6;
		}
		else
		{
			FVector Dir = (GoalLocation - Agent->Location).GetSafeNormal2D();
			Ball.Velocity = Dir * 14;
		}
	}

	if (Agent->State == EAgentState::Moving)
	{
		float DistanceSq = FVector::DistSquared2D(Agent->Location, Agent->Destination);
		if (DistanceSq < 50 * 50)
		{
			//Find new destination that makes sense.
			Agent->State = EAgentState::Idle;
		}
		else
		{
			Agent->Location += (Agent->Destination - Agent->Location).GetSafeNormal2D() * Agent->Footballer->Data.Attributes[static_cast<int32>(EFootballerAttributes::Speed)] * 0.05;
		}
	}
}

void UMatchSimulationSubsystem::SimulateUpdate(float DeltaTimeSeconds)
{
	//Internal tick time is always one second
	constexpr float InternalTickTime = 1.0f;

	//Convert real time and tick correctly
	Timer -= DeltaTimeSeconds;

	if (Timer < 0)
	{
		//Math end
	}

	constexpr float SpeedMul = 0.05f;

	ELocalOrVisitor Place = ELocalOrVisitor::Local;
	//Tick Agents
	//All Distances are in cms
	for (FFootballerAgent &Agent : LocalFootballers)
	{
		ProcessAgent(&Agent, LocalFootballers, VisitorsFootballers, Place);
	}

	Place = ELocalOrVisitor::Visitor;
	for (FFootballerAgent &Visitor : VisitorsFootballers)
	{
		ProcessAgent(&Visitor, VisitorsFootballers, LocalFootballers, Place);
	}

	Ball.Location += Ball.Velocity;
	if (Ball.Location.X > 5000 || Ball.Location.X < -5000)
	{
		//Goal or whatever, please reset
		Ball.Location = FVector::Zero();
		SetTeams(LocalTeam, VisitorTeam);
	}
}

//TODO (David.Roguin): How bad is this to performance?
void UMatchSimulationSubsystem::GetFootballerAgents(TArray<FFootballerAgent>& OutAgents, FBall& OutBall)
{
	TArray<FFootballerAgent> Agents;
	Agents.Reserve(MaxStarters * 2);

	for (FFootballerAgent &Agent : LocalFootballers)
	{
		Agents.Add(Agent);
	}

	for (FFootballerAgent &Agent : VisitorsFootballers)
	{
		Agents.Add(Agent);
	}

	OutAgents = Agents;
	OutBall = Ball;
}

void UMatchSimulationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Timer = 45*60;
}


