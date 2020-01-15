#include <ai_pl.h>
#include <string>
#include <iostream>

class DragonKnowledgeBase : public ai::PL::KnowledgeBase {
public:
  void addDragon(const std::string& dragon_name);
  void dragonSaid(const std::string& dragon_name, const std::string& statement);
  bool dragonIsPredator(const std::string& dragon_name);
  bool dragonIsRational(const std::string& dragon_name);
};

void DragonKnowledgeBase::addDragon(const std::string& dragon_name) {
  std::string red = dragon_name + "isRed";
  std::string predator = dragon_name + "isPredator";
  std::string truth_teller = dragon_name + "isTruthTeller";
  
  this->AddSentence("(" + red + " & (!" + predator + ")) => (!" + truth_teller + ")");
  this->AddSentence("((!" + red + ") & (!" + predator + ")) => " + truth_teller + "");
  this->AddSentence("(" + red + " & " + predator + ") => " + truth_teller + "");
  this->AddSentence("((!" + red + ") & " + predator + ") => (!" + truth_teller + ")");
  this->AddSentence("(!" + truth_teller + ") => ( ( " + red + " & (!" + predator + ") ) | ( (!" + red + ") & " + predator + " ) )");
  this->AddSentence(truth_teller + " => ( ( (!" + red + ") & (!" + predator + ") ) | ( " + red + " & " + predator + " ) )");

}

void DragonKnowledgeBase::dragonSaid(const std::string& dragon_name, const std::string& statement) {
  std::string truth_teller = dragon_name + "isTruthTeller";
  this->AddSentence(truth_teller + " <=> (" + statement + ")");
}

bool DragonKnowledgeBase::dragonIsPredator(const std::string& dragon_name) {
  KnowledgeBase Q;
  Q.AddSentence(dragon_name + "isPredator");
  ai::PL::Symbol::State state = this->DPLL_Entails(Q);
  return state == ai::PL::Symbol::State::KNOWN_TRUE;
}

bool DragonKnowledgeBase::dragonIsRational(const std::string& dragon_name) {
  KnowledgeBase Q;
  Q.AddSentence("(!" + dragon_name + "isPredator)");
  ai::PL::Symbol::State state = this->DPLL_Entails(Q);
  return state == ai::PL::Symbol::State::KNOWN_TRUE;
}

void test_problem4() {
  std::cout << "Problem 4" << std::endl;
  DragonKnowledgeBase kb;
  // physics
  kb.addDragon("A");
  kb.addDragon("B");
  kb.addDragon("C");
  
  // instance data
  kb.dragonSaid("A", "( (!AisPredator) & AisPredator )");
  kb.dragonSaid("A", "( BisPredator & CisPredator )");
  kb.dragonSaid("B", "( (!AisPredator) & (!AisTruthTeller) )");
  kb.dragonSaid("B", "( (!BisPredator) )");
  kb.dragonSaid("C", "( AisPredator & BisPredator )");
  kb.dragonSaid("C", "( (!CisRed) & (!CisPredator) )");
  kb.dragonSaid("C", "( !( BisPredator & CisPredator ) )");

  // ask questions
  if(kb.dragonIsPredator("A")) {
    std::cout << "Choose to kill A." << std::endl;
  } else if(kb.dragonIsRational("A")) {
    std::cout << "Choose not to kill A." << std::endl;
  } else {
    std::cout << "Be wary of A.  We don't know if it is a predator or rational." << std::endl;
  }

  if(kb.dragonIsPredator("B")) {
    std::cout << "Choose to kill B." << std::endl;
  } else if(kb.dragonIsRational("B")) {
    std::cout << "Choose not to kill B." << std::endl;
  } else {
    std::cout << "Be wary of B.  We don't know if it is a predator or rational." << std::endl;
  }

  if(kb.dragonIsPredator("C")) {
    std::cout << "Choose to kill C." << std::endl;
  } else if(kb.dragonIsRational("C")) {
    std::cout << "Choose not to kill C." << std::endl;
  } else {
    std::cout << "Be wary of C.  We don't know if it is a predator or rational." << std::endl;
  }
}

void test_problem1() {
  std::cout << "Problem 1" << std::endl;
  DragonKnowledgeBase kb;
  // physics
  kb.addDragon("A");
  kb.addDragon("B");
  
  // instance data
  kb.dragonSaid("A", "(!AisRed)");
  kb.dragonSaid("A", "BisPredator");
  kb.dragonSaid("B", "AisPredator");
  kb.dragonSaid("B", "(!BisPredator)");

  // ask questions
  if(kb.dragonIsPredator("A")) {
    std::cout << "Choose to kill A." << std::endl;
  } else if(kb.dragonIsRational("A")) {
    std::cout << "Choose not to kill A." << std::endl;
  } else {
    std::cout << "Be wary of A.  We don't know if it is a predator or rational." << std::endl;
  }

  if(kb.dragonIsPredator("B")) {
    std::cout << "Choose to kill B." << std::endl;
  } else if(kb.dragonIsRational("B")) {
    std::cout << "Choose not to kill B." << std::endl;
  } else {
    std::cout << "Be wary of B.  We don't know if it is a predator or rational." << std::endl;
  }
}

int main(int argc, char **argv)
{
  test_problem1();
  test_problem4();
  return 0;
}
