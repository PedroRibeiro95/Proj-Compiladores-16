// $Id: postfix_writer.h,v 1.23 2016/05/19 05:44:45 ist179055 Exp $ -*- c++ -*-
#ifndef __ZU_SEMANTICS_PF_WRITER_H__
#define __ZU_SEMANTICS_PF_WRITER_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/emitters/basic_postfix_emitter.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"
#include <set>

namespace zu {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class postfix_writer: public basic_ast_visitor {
    
    cdk::symbol_table<zu::symbol> &_symtab;
    cdk::basic_postfix_emitter &_pf;
    int _lbl;
    bool _arguments;
    
    int _posoffset = 4;
    int _offset = 0;
    
    std::string _lblinc = "";
    std::string _lblend = "";
    
    std::set<std::string> _extern;
    
    std::string _lblret = "";

  public:
    postfix_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<zu::symbol> &symtab,
                   cdk::basic_postfix_emitter &pf) :
        basic_ast_visitor(compiler), _symtab(symtab), _pf(pf), _lbl(0) {
    }

  public:
    ~postfix_writer() {
      os().flush();
    }

  private:
    /** Method used to generate sequential labels. */
    inline std::string mklbl(int lbl) {
      std::ostringstream oss;
      if (lbl < 0)
        oss << ".L" << -lbl;
      else
        oss << "_L" << lbl;
      return oss.str();
    }

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);
    void do_double_node(cdk::double_node * const node, int lvl);

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl);

  public:
    void do_add_node(cdk::add_node * const node, int lvl);
    void do_sub_node(cdk::sub_node * const node, int lvl);
    void do_mul_node(cdk::mul_node * const node, int lvl);
    void do_div_node(cdk::div_node * const node, int lvl);
    void do_mod_node(cdk::mod_node * const node, int lvl);
    void do_lt_node(cdk::lt_node * const node, int lvl);
    void do_le_node(cdk::le_node * const node, int lvl);
    void do_ge_node(cdk::ge_node * const node, int lvl);
    void do_gt_node(cdk::gt_node * const node, int lvl);
    void do_ne_node(cdk::ne_node * const node, int lvl);
    void do_eq_node(cdk::eq_node * const node, int lvl);
    
    void do_and_node(zu::and_node * const node, int lvl);
    void do_or_node(zu::or_node * const node, int lvl);

  public:
    void do_lvalue_node(zu::lvalue_node * const node, int lvl);
    void do_rvalue_node(zu::rvalue_node * const node, int lvl);
    
    void do_identifier_node(zu::identifier_node * const node, int lvl);
    void do_index_node(zu::index_node * const node, int lvl);

  public:
    void do_function_call_node(zu::function_call_node * const node, int lvl);
    void do_declaration_node(zu::declaration_node * const node, int lvl);
    void do_function_declaration_node(zu::function_declaration_node * const node, int lvl);
    void do_function_definition_node(zu::function_definition_node * const node, int lvl);
    
    void do_evaluation_node(zu::evaluation_node * const node, int lvl);
    void do_print_node(zu::print_node * const node, int lvl);
    void do_read_node(zu::read_node * const node, int lvl);
    void do_assignment_node(zu::assignment_node * const node, int lvl);
    
    void do_return_node(zu::return_node * const node, int lvl);
    void do_block_node(zu::block_node * const node, int lvl);
    void do_identity_node(zu::identity_node * const node, int lvl);
    void do_simetric_node(zu::simetric_node * const node, int lvl);
    void do_position_indicator_node(zu::position_indicator_node * const node, int lvl);
    void do_memory_reservation_node(zu::memory_reservation_node * const node, int lvl);

  public:
    void do_if_node(zu::if_node * const node, int lvl);
    void do_if_else_node(zu::if_else_node * const node, int lvl);

    void do_for_node(zu::for_node * const node, int lvl);
    void do_break_node(zu::break_node * const node, int lvl);
    void do_continue_node(zu::continue_node * const node, int lvl);
  };

} // zu

#endif
