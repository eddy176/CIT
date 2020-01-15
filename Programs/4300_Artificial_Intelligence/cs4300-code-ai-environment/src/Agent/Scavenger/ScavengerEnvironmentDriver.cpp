#include <ai_scavenger.h>
#include <fstream>
#include <iomanip>
#include <unistd.h>

namespace ai
{
  namespace Scavenger
  {
    static struct ai::Agent::Option options[] =
      {
        {"filename",               'f', "scav_world.txt", "World filename"},
        {"tourney",                'T', "0",              "Enable/disable tournament mode"},
        {"fully-observable",       'O', "0",              "Make the world fully observable"},
        {"object-learning",        'L', "0",              "Learning percepts for objects"},
        {"skip-object-count",      'C', "0",              "First number of objects don't count in score"},
        {"max-object-count",       'M', "100000",         "Maximum number of objects accepted in score"},
        {"max-hopper-volume",      'V', "100",            "Maximum volume of the robot's hopper"},
        {"max-robot-charge",       'Q', "100.",           "Maximum charge of the robot's battery"},
        {"recharge-amount",        'U', "25.",            "Amount of battery recharge per turn"},
        {"max-robot-hit-points",   'P', "100.",           "Maximum hit points of the robot's health"},
        {"fall-damage",            'F', "0.5",            "HP damage per meter of fall"},
        {"horizontal-charge-cost", 'H', "0.001",          "Charge cost per meter of horizontal travel"},
        {"vertical-charge-cost",   'Z', "0.001",          "Charge cost per meter of vertical travel"},
        {"look-charge-cost",       'I', "0.25",           "Charge cost per LOOK action"},
        {"pickup-charge-cost",     'K', "0.25",           "Charge cost per PICKUP action"},
        {"drop-charge-cost",       'G', "0.25",           "Charge cost per DROP action"},
        {"deposit-charge-cost",    'B', "0.25",           "Charge cost per DEPOSIT action"},
        {"examine-charge-cost",    'E', "0.25",           "Charge cost per EXAMINE action"},
        /* unused
         * letters *bc*e*ghijklmno*qr**uvwxy*
         * LETTERS A********J***N********WXY*
         */
        {"", 0, "", ""}
      };

    EnvironmentDriver::EnvironmentDriver(int argc, char **argv, bool init_options) : ai::Agent::EnvironmentDriver(argc, argv, false)
    {
      mOptions.AddOptions(options);
      if(init_options)
        {
          mOptions.Initialize(argc, argv);
          InitRand();
        }
    }

    void EnvironmentDriver::Run()
    {
      std::string filename = mOptions.GetArg("filename");
      {
        std::ifstream fin(filename.c_str());
        if(!fin)
          {
            std::cerr << "Unable to open Scavenger world file: " << filename << std::endl;
            exit(1);
          }
        fin.close();
      }

      int num_agents = mOptions.GetArgInt("agents");
      InitSockets(num_agents, mOptions.GetArgInt("displays"));

      int runs = mOptions.GetArgInt("runs");
      bool tourney = mOptions.GetArgInt("tourney");
      bool fully_observable = mOptions.GetArgInt("fully-observable");
      bool object_learning = mOptions.GetArgInt("object-learning");
      unsigned int skip_object_count = mOptions.GetArgUnsignedInt("skip-object-count");
      unsigned int max_object_count  = mOptions.GetArgUnsignedInt("max-object-count");
      unsigned int max_hopper_volume = mOptions.GetArgUnsignedInt("max-hopper-volume");
      double max_robot_charge = mOptions.GetArgFlt("max-robot-charge");
      double recharge_amount = mOptions.GetArgFlt("recharge-amount");
      double max_robot_hit_points = mOptions.GetArgFlt("max-robot-hit-points");
      double fall_damage = mOptions.GetArgFlt("fall-damage");
      double horizontal_charge_cost = mOptions.GetArgFlt("horizontal-charge-cost");
      double vertical_charge_cost = mOptions.GetArgFlt("vertical-charge-cost");
      double look_charge_cost = mOptions.GetArgFlt("look-charge-cost");
      double pickup_charge_cost = mOptions.GetArgFlt("pickup-charge-cost");
      double drop_charge_cost = mOptions.GetArgFlt("drop-charge-cost");
      double deposit_charge_cost = mOptions.GetArgFlt("deposit-charge-cost");
      double examine_charge_cost = mOptions.GetArgFlt("examine-charge-cost");

      if(tourney)
        {
          runs *= num_agents;
        }
      for(int r = 0; r < runs; r++)
        {
          Environment *env = new Environment(mRandomNumber, &mDisplaySockets, filename);
          env->SetFullyObservable(fully_observable);
          env->SetObjectLearning(object_learning);
          env->SetMaxCharge(max_robot_charge);
          env->SetRechargePerTurn(recharge_amount);
          env->SetMaxHitPoints(max_robot_hit_points);
          env->SetMaxBinVolume(max_hopper_volume);
          env->SetMaxArmMass(25.);
          env->SetLiftDamage(5.);
          env->SetFallDamagePerMeter(fall_damage);
          env->SetRechargeDamage(5.);
          env->SetRechargeCharge(1.);
          env->SetVChargePerMeter(horizontal_charge_cost);
          env->SetHChargePerMeter(vertical_charge_cost);
          env->SetLookCharge(look_charge_cost);
          env->SetPickupCharge(pickup_charge_cost);
          env->SetDropCharge(drop_charge_cost);
          env->SetDepositCharge(deposit_charge_cost);
          env->SetExamineCharge(examine_charge_cost);
          env->SetSkipObjectCount(skip_object_count);
          env->SetMaxObjectCount(max_object_count);

          if(!env->MakeEnoughBases(num_agents))
            {
              DBGP_E(LOG_STREAM(std::cerr) << "Could not make enough bases for " << num_agents << " agents." << std::endl);
              exit(1);
            }

          int i;
          for(i = 0; i < num_agents; i++)
            {
              Agent *agent = new Agent(mAgentSockets[i]);
              if(mOptions.GetArgInt("trace"))
                {
                  agent->Trace();
                }
              else
                {
                  agent->NoTrace();
                }
              env->AddAgent(agent, 0);
            }

          env->SetDelay(mOptions.GetArgInt("delay"));
          env->Run(mOptions.GetArgInt("steps"));

          for(i = 0; i < num_agents; i++)
            {
              Agent *agent = dynamic_cast<Agent *>(env->GetAgent(i));

              std::cout << agent->GetName() << ": Charge "
                        << agent->GetCharge() << " HitPoints "
                        << agent->GetHitPoints() << " QuitTime "
                        << agent->GetQuitTimeStep() << " LastTime "
                        << agent->GetLastTimeStep() << " VisitedCells "
                        << agent->GetNumVisitedCells() << " Score "
                        << agent->GetPerformance() << " "
                        << std::endl;
            }

          mRandomNumber = env->GetRandomNumber();
          sleep(mOptions.GetArgInt("sleep"));
          delete env;
        }
    }
  }
}
