// $Id: block_node.h,v 1.1 2016/03/16 21:57:24 ist179055 Exp $ -*- c++ -*-
#ifndef __ZU__BLOCK_NODE_H__
#define __ZU__BLOCK_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing block nodes.
   */
  class block_node: public cdk::basic_node {
    cdk::sequence_node *_declarations;
    cdk::sequence_node *_instructions;

  public:
    inline block_node(int lineno, cdk::sequence_node *declarations, cdk::sequence_node *instructions) :
        basic_node(lineno), _declarations(declarations), _instructions(instructions){}

  public:
    inline cdk::sequence_node *declarations() {
      return _declarations;
    }
    inline cdk::sequence_node *instructions() {
      return _instructions;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_block_node(this, level);
    }

  };

} // zu

#endif
