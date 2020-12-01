#include <iostream>
#include <ostream>
#include <sstream>

#include <stdlib.h>
#include "lang_grammar.pb.h"
#include "port/protobuf.h"
#include "src/libfuzzer/libfuzzer_macro.h"

std::ostream &operator<<(std::ostream &os, const LG::BinaryOp& psn);
std::ostream &operator<<(std::ostream &os, const LG::Rvalue& rval);
std::ostream &operator<<(std::ostream &os, const LG::VarRef var_ref);
std::ostream &operator<<(std::ostream &os, const LG::AssignmentStmt assign_stmt);
std::ostream &operator<<(std::ostream &os, const LG::Cond cond);
std::ostream &operator<<(std::ostream &os, const LG::IfCond if_cond);
std::ostream &operator<<(std::ostream &os, const LG::ElseCond else_cond);

std::ostream &operator<<(std::ostream &os, const LG::Stmt stmt);
std::ostream &operator<<(std::ostream &os, const LG::StmtSeq stmt_seq);

#define MAX_VAR 3
int static depth = 0;

// BinaryOp converter
std::ostream &operator<<(std::ostream &os, const LG::BinaryOp& psn) {
    // Increase depth to ensure we dont reach a stack-overflow.
    depth += 1;

    os << psn.left();
    switch(psn.op())
    {
        case LG::BinaryOp::PLUS:   os << "+"; break;
        case LG::BinaryOp::MINUS:  os << "-"; break;
        case LG::BinaryOp::MUL:    os << "*"; break;
        case LG::BinaryOp::DIV:    os << "/"; break;
        default:
            abort();
    }
    os << psn.right();
    return os;
}

// Rvalue converter
std::ostream &operator<<(std::ostream &os, const LG::Rvalue& rval) {
    if (rval.has_cons()) {
        os << rval.cons().val();
    }
    else if (depth < 10) {
        os << rval.binop();
    }
    else {
        os << "123";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const LG::VarRef var_ref) {
   return os << "var" << abs((var_ref.varnum() % MAX_VAR));
}

std::ostream &operator<<(std::ostream &os, const LG::AssignmentStmt assign_stmt) {
   os << assign_stmt.lvalue() << " = " << assign_stmt.rvalue();
   return os;
}

std::ostream &operator<<(std::ostream &os, const LG::Cond cond) {
   return os << cond.rval();
}

std::ostream &operator<<(std::ostream &os, const LG::IfCond if_cond) {
   os << "if (" << if_cond.cond() << ")" << "\n";
   os << "{\n";
   os << if_cond.body();
   os << "}";
   return os;
}


std::ostream &operator<<(std::ostream &os, const LG::ElseCond else_cond) {
   os << "else {" << else_cond.body() << "}" << "\n";
   os << "{\n";
   os << else_cond.body();
   os << "}";
   return os;
}




std::ostream &operator<<(std::ostream &os, const LG::Stmt stmt) {
   if (stmt.stmt_var_case() == LG::Stmt::StmtVarCase::kAssignmt) {
       os << stmt.assignmt() << ";\n";
   }
   else if (stmt.stmt_var_case() == LG::Stmt::StmtVarCase::kIfCond) {
       os << stmt.if_cond() << "\n";
   }
   else if(stmt.stmt_var_case() == LG::Stmt::StmtVarCase::kElseCond){
       os << stmt.else_cond() << "\n";
   }

   return os;
}

std::ostream &operator<<(std::ostream &os, const LG::StmtSeq stmt_seq) {
   for (const LG::Stmt &stmt : stmt_seq.stmts()) {
      os << stmt;
   }
   return os;
}

DEFINE_PROTO_FUZZER(const LG::StmtSeq& inp) {
    depth = 0;
    std::ostringstream os;
    for (int i = 0; i  < MAX_VAR; i++) {
       os << "var" << i << ";\n";
    }
    os << inp;
    std::string lang_string = os.str();

    // Print the string for convenience
    std::cout << "----------------------------" << std::endl;
    std::cout << lang_string << std::endl;
}
