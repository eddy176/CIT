#include "starterGimliKnowledgeBase.h"
#include <cstdio>
#include <cstring>
#include <sstream>

namespace starter {

GimliKnowledgeBase::GimliKnowledgeBase()
    : ai::PL::KnowledgeBase(), width(4), height(4) {
  // nothing here
}
GimliKnowledgeBase::~GimliKnowledgeBase() {
  // nothing here
}

void GimliKnowledgeBase::SetSize(int width_in, int height_in) {
  width = width_in;
  height = height_in;
}

bool GimliKnowledgeBase::AskGold(int x_in, int y_in) {
  // bool rval;
  KnowledgeBase question;
  std::stringstream ss;
  ss << "GOLD_" << x_in << '_' << y_in;
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
} // done?

bool GimliKnowledgeBase::AskNoPit(int x_in, int y_in) {
  KnowledgeBase question;
  std::stringstream ss;
  ss << "(!PIT_" << x_in << '_' << y_in << ')';
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

bool GimliKnowledgeBase::AskPit(int x_in, int y_in) {
  KnowledgeBase question;
  std::stringstream ss;
  ss << "PIT_" << x_in << '_' << y_in;
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

bool GimliKnowledgeBase::AskB1(int x_in, int y_in) {
  KnowledgeBase question;
  std::stringstream ss;
  ss << "B1_" << x_in << '_' << y_in;
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

bool GimliKnowledgeBase::AskB2(int x_in, int y_in) {
  KnowledgeBase question;
  std::stringstream ss;
  ss << "B2_" << x_in << '_' << y_in;
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

bool GimliKnowledgeBase::AskNoWumpus(int x_in, int y_in) {
  KnowledgeBase question;
  std::stringstream ss;
  ss << "!WUMPUS_" << x_in << '_' << y_in;
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

bool GimliKnowledgeBase::AskWumpus(int x_in, int y_in) {
  KnowledgeBase question;
  std::stringstream ss;
  ss << "WUMPUS_" << x_in << '_' << y_in;
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

bool GimliKnowledgeBase::AskNotSafe(int x_in, int y_in) {
  KnowledgeBase question;
  std::stringstream ss;
  ss << "(!SAFE_" << x_in << '_' << y_in << ')';
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

bool GimliKnowledgeBase::AskSafe(int x_in, int y_in) {
  KnowledgeBase question;
  std::stringstream ss;
  ss << "SAFE_" << x_in << '_' << y_in;
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

bool GimliKnowledgeBase::AskVisited(int x_in, int y_in) {
  KnowledgeBase question;
  std::stringstream ss;
  ss << "VISITED_" << x_in << '_' << y_in;
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

bool GimliKnowledgeBase::AskBreeze(int x_in, int y_in) {
  KnowledgeBase question;
  std::stringstream ss;
  ss << "BREEZE_" << x_in << '_' << y_in;
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

bool GimliKnowledgeBase::AskStench(int x_in, int y_in) {
  KnowledgeBase question;
  std::stringstream ss;
  ss << "STENCH_" << x_in << '_' << y_in;
  question.AddSentence(ss.str());
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

bool GimliKnowledgeBase::AskAimedAtWumpus(int x_in, int y_in,int direction_in) {    // check x and y directions
  if (direction_in == 0) { // facing east
    for (int i = x_in; i <= width; i++) {
      if (AskWumpus(i, y_in)) {
        return true;
      }
    }
  } else if (direction_in == 90) { // facing north
    for (int i = y_in; i <= height; i++) {
      if (AskWumpus(x_in, i)) {
        return true;
      }
    }
  } else if (direction_in == 180) { // facing west
    for (int i = x_in - 1; i >= 0; i--) {
      if (AskWumpus(i, y_in)) {
        return true;
      }
    }
  } else { // facing south
    for (int i = y_in - 1; i >= 0; i--) {
      if (AskWumpus(x_in, i)) {
        return true;
      }
    }
  }
  return false;
} // working in at least one situation

bool GimliKnowledgeBase::AskWumpusAlive() {
  KnowledgeBase question;
  question.AddSentence("!WUMPUS_DEAD");
  ai::PL::Symbol::State state = DPLL_Entails(question);
  return state == ai::PL::Symbol::KNOWN_TRUE;
}

void GimliKnowledgeBase::TellNoGlitter(int x_in, int y_in) {
  std::stringstream ss;
  ss << "!GLITTER_" << x_in << '_' << y_in;
  AddSentence(ss.str());
}
void GimliKnowledgeBase::TellGlitter(int x_in, int y_in) {
  std::stringstream ss;
  ss << "GLITTER_" << x_in << '_' << y_in;
  AddSentence(ss.str());
}
void GimliKnowledgeBase::TellNoBreeze(int x_in, int y_in) {
  std::stringstream ss;
  ss << "!BREEZE_" << x_in << '_' << y_in;
  AddSentence(ss.str());
}
void GimliKnowledgeBase::TellBreeze(int x_in, int y_in) {
  std::stringstream ss;
  ss << "BREEZE_" << x_in << '_' << y_in;
  AddSentence(ss.str());
}
void GimliKnowledgeBase::TellNoStench(int x_in, int y_in) {
  std::stringstream ss;
  ss << "!STENCH_" << x_in << '_' << y_in;
  AddSentence(ss.str());
}
void GimliKnowledgeBase::TellStench(int x_in, int y_in) {
  std::stringstream ss;
  ss << "STENCH_" << x_in << '_' << y_in;
  AddSentence(ss.str());
}
void GimliKnowledgeBase::TellNoPit(int x_in, int y_in) {
  std::stringstream ss;
  ss << "!PIT_" << x_in << '_' << y_in;
  AddSentence(ss.str());
}
void GimliKnowledgeBase::TellWumpusDead() {
  std::stringstream ss;
  ss << "WUMPUS_DEAD";
  AddSentence(ss.str());
}

void GimliKnowledgeBase::TellNoWumpus(int x_in, int y_in) {
  std::stringstream ss;
  ss << "!WUMPUS_" << x_in << '_' << y_in;
  AddSentence(ss.str());
}
void GimliKnowledgeBase::TellWumpus(int x_in, int y_in) {
  std::stringstream ss;
  ss << "WUMPUS_" << x_in << '_' << y_in;
  AddSentence(ss.str());
}

void GimliKnowledgeBase::TellVisited(int x_in, int y_in) {
  std::stringstream ss;
  ss << "VISITED_" << x_in << '_' << y_in;
  AddSentence(ss.str());
}

void GimliKnowledgeBase::TellShot(){
  std::stringstream ss;
  ss << "SHOT";
  AddSentence(ss.str());
}

void GimliKnowledgeBase::TellShotRules() {
  std::stringstream ss;
  ss << "(SHOT & (!WUMPUSDEAD)) <=> WUMPUS_1_2";
  AddSentence(ss.str());
}


void GimliKnowledgeBase::TellGlitterRules() {
  std::stringstream nss;
  for (int i = 1; i <= width; i++) {
    for (int j = 1; j <= height; j++) {
      if (j == 1 && i == 1) {
        continue;
      }
      std::stringstream ss;
      ss << "(GOLD_" << i << '_' << j << ") <=> (GLITTER_" << i << '_' << j
         << ')';
      AddSentence(ss.str());

      if (i == 1 && j == 2) { // if in the first square not at beginning
        nss << "GOLD_" << i << '_' << j;
      } else {
        nss << " | GOLD_" << i << '_' << j;
      }
    }
  }
  AddSentence(nss.str());
}

// pits aren't assumed outside of bounds
void GimliKnowledgeBase::TellBreezeRules() {
  // std::stringstream nss;
  for (int i = 1; i <= width; i++) {
    for (int j = 1; j <= height; j++) {
      if ((i + 1 <= width) && (j + 1 <= height) && (i - 1 > 0) &&
          (j - 1 > 0)) { // could be surrounded
        std::stringstream ss0;
        ss0 << "BREEZE_" << i << "_" << j << " <=> PIT_" << i + 1 << '_' << j
            << " | PIT_" << i - 1 << '_' << j << " | PIT_" << i << '_' << j + 1
            << " | PIT_" << i << '_' << j - 1;
        AddSentence(ss0.str());
      } else if ((i + 1 <= width) && (j + 1 <= height) &&
                 (i - 1 > 0)) { // could be up left or right
        std::stringstream ss1;
        ss1 << "BREEZE_" << i << "_" << j << " <=> PIT_" << i + 1 << '_' << j
            << " | PIT_" << i - 1 << '_' << j << " | PIT_" << i << '_' << j + 1;
        AddSentence(ss1.str());
      } else if ((i + 1 <= width) && (j + 1 <= height) &&
                 (j - 1 > 0)) { // could be up down or right
        std::stringstream ss2;
        ss2 << "BREEZE_" << i << "_" << j << " <=> PIT_" << i + 1 << '_' << j
            << " | PIT_" << i << '_' << j - 1 << " | PIT_" << i << '_' << j + 1;
        AddSentence(ss2.str());
      } else if ((i - 1 > 0) && (j + 1 <= height) &&
                 (j - 1 > 0)) { // could be up down or left
          std::stringstream ss3;
          ss3 << "BREEZE_" << i << "_" << j << " <=> PIT_" << i - 1 << '_' << j
            << " | PIT_" << i << '_' << j - 1 << " | PIT_" << i << '_' << j + 1;
        AddSentence(ss3.str());
      } else if ((i + 1 <= width) && (j - 1 > 0) &&
                 (i - 1 > 0)) { // could be down left or right
        std::stringstream ss4;
        ss4 << "BREEZE_" << i << "_" << j << " <=> PIT_" << i + 1 << '_' << j
            << " | PIT_" << i << '_' << j - 1 << " | PIT_" << i << '_' << j + 1;
        AddSentence(ss4.str());
      } else if ((i + 1 <= width) && (j + 1 <= height)) { // bottom right corner
        std::stringstream ss5;
        ss5 << "BREEZE_" << i << "_" << j << " <=> PIT_" << i + 1 << '_' << j
            << " | PIT_" << i << '_' << j + 1;
        AddSentence(ss5.str());
      } else if ((i - 1 > 0) && (j - 1 > 0)) { // top right corner
        std::stringstream ss6;
        ss6 << "BREEZE_" << i << "_" << j << " <=> PIT_" << i - 1 << '_' << j
            << " | PIT_" << i << '_' << j - 1;
        AddSentence(ss6.str());
      } else if ((i - 1 > 0) && (j + 1 <= height)) { // bottom right corner
        std::stringstream ss7;
        ss7 << "BREEZE_" << i << "_" << j << " <=> PIT_" << i - 1 << '_' << j
            << " | PIT_" << i << '_' << j + 1;
        AddSentence(ss7.str());
      } else if ((i + 1 <= width) && (j - 1 > 0)) { // top left corner
        std::stringstream ss8;
        ss8 << "BREEZE_" << i << "_" << j << " <=> PIT_" << i + 1 << '_' << j
            << " | PIT_" << i << '_' << j - 1;
        AddSentence(ss8.str());
      }
      // AddSentence(nss.str());
    }
  }
}

void GimliKnowledgeBase::TellStenchRules() {
  std::stringstream nss;
  for (int i = 1; i <= width; i++) {
    for (int j = 1; j <= height; j++) {
      if ((i + 1 <= width) && (j + 1 <= height)) {
        std::stringstream ss0;
        ss0 << "(STENCH_" << i << "_" << j << " & STENCH_" << i + 1 << '_'
            << j + 1 << ") <=> (WUMPUS_" << i + 1 << '_' << j << " | WUMPUS_"
            << i << '_' << j + 1 << ')';
        AddSentence(ss0.str());
      } else if ((i - 1 > 0) && (j - 1 > 0)) {
        std::stringstream ss2;
        ss2 << "(STENCH_" << i << "_" << j << " & STENCH_" << i - 1 << '_'
            << j - 1 << ") <=> (WUMPUS_" << i << '_' << j - 1 << " | WUMPUS_"
            << i - 1 << '_' << j << ')';
        AddSentence(ss2.str());
      }
      if ((i - 1 > 0) && (j + 1 <= height)) {
        std::stringstream ss1;
        ss1 << "(STENCH_" << i << "_" << j << " & STENCH_" << i - 1 << '_'
            << j + 1 << ") <=> (WUMPUS_" << i - 1 << '_' << j << " | WUMPUS_"
            << i << '_' << j + 1 << ')';
        AddSentence(ss1.str());
      } else if ((i + 1 <= width) && (j - 1 > 0)) {
        std::stringstream ss3;
        ss3 << "(STENCH_" << i << "_" << j << " & STENCH_" << i + 1 << '_'
            << j - 1 << ") <=> (WUMPUS_" << i << '_' << j - 1 << " | WUMPUS_"
            << i + 1 << '_' << j << ')';
        AddSentence(ss3.str());
      }
      if (i == 1 && j == 1) { // if in the first square
        nss << "WUMPUS_" << i << '_' << j;
      } else {
        nss << " | WUMPUS_" << i << '_' << j;
      }

      // ///////////////////////
      if (j == height && i >= 2 && i < width) {
        std::stringstream noss;
        noss << "STENCH_" << i << '_' << j << " & (!STENCH_" << i - 1 << '_' << j - 1 << ") <=> WUMPUS_" << i + 1 << '_' << j;  
        AddSentence(noss.str());
      } 
      else if (i == width && j >= 2 && j < height) {
        std::stringstream toss;
        toss << "STENCH_" << i << '_' << j << " & (!STENCH_" << i - 1 << '_' << j - 1 << ") <=> WUMPUS_" << i << '_' << j + 1;  
        AddSentence(toss.str());
      }
      // ///////////////////////
      std::stringstream ss4;
      ss4 << "WUMPUS_" << i << '_' << j << " <=> (";
      bool first = true;
      for (int x = 1; x <= width; x++) {
        for (int y = 1; y <= height; y++) {
          if (x == i && y == j){
            continue; // skip
          }
          if (first) {
            first = false;
            ss4 << "(!WUMPUS_" << x << '_' << y << ')';
          }
          else {
            ss4 << " & (!WUMPUS_" << x << '_' << y << ")";
          }
        }
      }
      ss4 << ')';
      // std::cout << "ss4: " << ss4.str() << std::endl;
      AddSentence(ss4.str());
      // std::cout << "Added sentence." << std::endl;
      /////////////////////////

    }
  }
  AddSentence(nss.str());
}

void GimliKnowledgeBase::TellSafeRules() {
  for (int i = 1; i <= width; i++) {
    for (int j = 1; j <= height; j++) {
      // std::stringstream nss;
      // nss << "VISITED_" << i << '_' << j << " <=> SAFE_" << i << '_' << j;

      std::stringstream ss;
      ss << "(((!WUMPUS_" << i << '_' << j << ") | WUMPUS_DEAD) & (!PIT_"
         << i << '_' << j << ")) <=> (SAFE_" << i << '_' << j << ')';
      AddSentence(ss.str());
    }
  }
}

void GimliKnowledgeBase::TellB1Rules() {
  for (int i = 1; i < width; i++) {
    for (int j = 1; j < height; j++) {
      std::stringstream nss;
      nss << "(VISITED_" << i << '_' << j << " & BREEZE_" << i << '_' << j + 1 << " & BREEZE_" << i + 1 << '_' << j << ") <=> B1_" << i << '_' << j + 1;
      AddSentence(nss.str());
    }
  }
}

void GimliKnowledgeBase::TellB2Rules() {
  for (int i = 1; i < width; i++) {
    for (int j = 1; j < height; j++) {
      ///////////////////////
      std::stringstream tss;
      tss << "(VISITED_" << i + 1 << '_' << j << " & BREEZE_" << i << '_' << j << " & BREEZE_" << i + 1 << '_' << j + 1<< ") <=> B2_" << i << '_' << j;
      AddSentence(tss.str());
      ///////////////////////
    }
  }
}

void GimliKnowledgeBase::TellSafe(int x_in, int y_in) {
  std::stringstream ss;
  ss << "SAFE_" << x_in << '_' << y_in;
  AddSentence(ss.str());
}

}; // namespace starter
