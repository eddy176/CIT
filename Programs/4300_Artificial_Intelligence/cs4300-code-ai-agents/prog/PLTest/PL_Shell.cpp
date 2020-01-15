#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cstring>
#include <cctype>
#include "Agent/FileDescriptor.h"
#include "ai_pl.h"

#define BUF_SIZE 2048
int process_file(ai::PL::KnowledgeBase &kb, char *buf, std::istream &in, std::ostream &out);

char *trim_whitespace(char *buf)
{
  int i;
  // skip leading white space
  while(*buf && std::isspace(*buf)) 
    { 
      buf++; 
    }

  // remove trailing white space
  i = std::strlen(buf) - 1;
  while(i >= 0 && std::isspace(buf[i]))
    {
      buf[i] = 0; 
      i--; 
    }

  return buf;
}

int do_ask(ai::PL::KnowledgeBase &kb, int interactive, char *buf, std::istream &in, std::ostream &out, const char *prompt)
{
  ai::PL::Symbol::State rval;
  ai::PL::KnowledgeBase question;
  char *q = 0;
  unsigned int len = strlen(prompt);
  
  if(strlen(buf) > len)
    {
      q = &buf[len];
    }
  else
    {
      if(interactive)
        {
          out << prompt << "> " << std::flush;
        }
      in.getline(buf, BUF_SIZE);
      q = buf;
    }

  q = trim_whitespace(q);
  question.AddSentence(q);
  if(!interactive)
    {
      out << prompt << " " << *(question.GetSentences()[0]) << std::endl << std::flush;
    }
  if(strcmp(prompt, "dpll") == 0)
    {
      rval = kb.DPLL_Entails(question);
    }
  else if(strcmp(prompt, "ask2") == 0)
    {
      rval = kb.TT_Entails_Pruned(question);
    }
  else if(strcmp(prompt, "ask") == 0)
    {
      rval = kb.TT_Entails(question);
    }
  else
    {
      out << "Unknown ask mode: " << prompt << std::endl;
      rval = ai::PL::Symbol::UNKNOWN;
    }
  if(rval == ai::PL::Symbol::KNOWN_TRUE)
    {
      out << "YES, " << q << " is entailed." << std::endl;
    }
  else
    {
      out << "NO, " << q << " is not entailed." << std::endl;
    }
  out << kb.GetCount() << " evaluations."  << std::endl;
  return 0;
}

int do_tell(ai::PL::KnowledgeBase &kb, int interactive, char *buf, std::istream &in, std::ostream &out)
{
  char * sentence = 0;
  if(strlen(buf) > 4)
    {
      sentence = &buf[4];
    }
  else
    {
      if(interactive)
        {
          out << "tell> " << std::flush;
        }
      in.getline(buf, BUF_SIZE);
      sentence = buf;
    }
  sentence = trim_whitespace(sentence);
  kb.AddSentence(sentence);
  if(!interactive)
    {
      out << "tell " << sentence << std::endl << std::flush;
    }
  return 0;
}

int do_list(ai::PL::KnowledgeBase &kb, int interactive, char *buf, std::istream &in, std::ostream &out)
{
  const std::vector<ai::PL::Sentence *>       &sentences = kb.GetSentences();
  std::vector<ai::PL::Sentence *>::const_iterator sen_it = sentences.begin();
  while(sen_it != sentences.end())
    {
      out << *(*sen_it) << std::endl;
      sen_it ++;
    }
  return 0;
}

int do_cnf(ai::PL::KnowledgeBase &kb, int interactive, char *buf, std::istream &in, std::ostream &out)
{
  const std::vector<ai::PL::Sentence *>          &sentences = kb.GetSentences();
  std::vector<ai::PL::Sentence *>::const_iterator sen_it = sentences.begin();
  while(sen_it != sentences.end())
    {
      ai::PL::Sentence *s_tmp = new ai::PL::Sentence(*(*sen_it));
      s_tmp->CNF();
      out << *(s_tmp) << std::endl;
      sen_it ++;
      delete s_tmp;
    }
  return 0;
}

int do_load(ai::PL::KnowledgeBase &kb, int interactive, char *buf, std::istream &in, std::ostream &out)
{
  char *filename = buf;
  if(strlen(buf) > 4)
    {
      filename = &buf[4];
    }
  filename = trim_whitespace(filename);
  std::ifstream fin(filename);
  if(!fin)
    {
      out << "Unknown file: '" << filename << "'." << std::endl;
    }
  else
    {
      process_file(kb, buf, fin, out);
      fin.close();
    }
  return 0;
}

int do_echo(ai::PL::KnowledgeBase &kb, int interactive, char *buf, std::istream &in, std::ostream &out)
{
  buf = trim_whitespace(&buf[4]);
  out << buf << std::endl;
  return 0;
}

int process_line(ai::PL::KnowledgeBase &kb, int interactive, char *buf, std::istream &in, std::ostream &out)
{
  buf = trim_whitespace(buf);
  
  if(strncmp(buf, "tell", 4) == 0)
    {
      do_tell(kb, interactive, buf, in, out);
    }
  else if(strncmp(buf, "ask2", 4) == 0)
    {
      do_ask(kb, interactive, buf, in, out, "ask2");
    }
  else if(strncmp(buf, "dpll", 4) == 0)
    {
      do_ask(kb, interactive, buf, in, out, "dpll");
    }
  else if(strncmp(buf, "ask", 3) == 0)
    {
      do_ask(kb, interactive, buf, in, out, "ask");
    }
  else if(strncmp(buf, "list", 4) == 0)
    {
      do_list(kb, interactive, buf, in, out);
    }
  else if(strncmp(buf, "cnf", 3) == 0)
    {
      do_cnf(kb, interactive, buf, in, out);
    }
  else if(strncmp(buf, "quit", 4) == 0)
    {
      return 1;
    }
  else if(strncmp(buf, "load", 4) == 0)
    {
      do_load(kb, interactive, buf, in, out);
    }
  else if(strncmp(buf, "echo", 4) == 0)
    {
      do_echo(kb, interactive, buf, in, out);
    }
  else if(strncmp(buf, "help", 4) == 0)
    {
      out << "known commands" << std::endl
          << "help  - this message" << std::endl
          << "tell  - prompt for new statement" << std::endl
          << "ask   - prompt for statement to check for entailment" << std::endl
          << "ask2  - prompt for statement to check for entailment (pruned)" << std::endl
          << "dpll  - prompt for statement to check for entailment (dpll)" << std::endl
          << "list  - display known statements" << std::endl
          << "cnf   - display known statements in CNF" << std::endl
          << "load  - load statements from file" << std::endl
          << "echo  - display text to output stream" << std::endl
          << "quit  - end session" << std::endl << std::flush;
    }
  else if(strncmp(buf, "#", 1) == 0)
    {
      // comment, skip it
    }
  else if(strlen(buf) == 0)
    {
      // empty line, skip it
    }
  else
    {
      out << "Unknown command. Use help to list known commands." << std::endl;
      out << "Bad command: " << buf << std::endl;
    }
  return 0;
}

int process_file(ai::PL::KnowledgeBase &kb, char *buf, std::istream &in, std::ostream &out)
{
  int done = 0;
  int interactive = 0;
  
#if !defined(__clang__) // 
  if(isatty(fileno(in)))
    {
      interactive = 1;
    }
#else
  out << "Can't test for interactive." << std::endl;
  interactive = 1;
#endif
  
  while(in.good() && !done)
    {
      if(interactive)
        {
          out << "> " << std::flush;
        }
      in.getline(buf, BUF_SIZE);
      if((strlen(buf) == 0) && !in.good())
        { // end of file without any data
          out << std::endl;
          continue;
        }
      done = process_line(kb, interactive, buf, in, out);
    }
  return 0;
}

int main()
{
  ai::PL::KnowledgeBase kb;
  char buf[BUF_SIZE];
  process_file(kb, buf, std::cin, std::cout);
  return 0;
}
