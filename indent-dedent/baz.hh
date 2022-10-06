#ifndef _BAZ_HH
#define _BAZ_HH

#include <iostream>

#include <vector>

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

namespace baz {
class Lexer : public yyFlexLexer {
public:
  Lexer(std::istream *in)
      : yyFlexLexer{in}, line{1}, column{1}, start_line{1},
        start_column{1}, spaces{0}, at_sol{true}, indents{} {}
  virtual ~Lexer() {}

  // get rid of override virtual function warning
  using FlexLexer::yylex;

  // Critical method for supporting Bison parsing.
  virtual int yylex(void);
  // YY_DECL defined in .ll
  // Method body created by flex in .cc

private:
  // Token location information. Advanced by advance_location.
  int line, column;
  int start_line, start_column;

  bool at_sol;

  int spaces;

  std::vector<int> indents;

  // Bump the line/column according to the given text.
  void advance_location(std::string txt);

  // Put back the recently matched text, rewinding line/column.
  void unchomp(void);

  int current_spaces();

  // if nonzero, return that
  int handle_indentation();
};

} // namespace baz

#endif
