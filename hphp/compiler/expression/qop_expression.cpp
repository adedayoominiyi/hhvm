/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-present Facebook, Inc. (http://www.facebook.com)  |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include "hphp/compiler/expression/qop_expression.h"
#include "hphp/compiler/analysis/code_error.h"

#include "hphp/runtime/base/type-variant.h"

using namespace HPHP;

///////////////////////////////////////////////////////////////////////////////
// constructors/destructors

QOpExpression::QOpExpression
(EXPRESSION_CONSTRUCTOR_PARAMETERS,
 ExpressionPtr condition, ExpressionPtr expYes, ExpressionPtr expNo)
  : Expression(EXPRESSION_CONSTRUCTOR_PARAMETER_VALUES(QOpExpression)),
    m_condition(condition), m_expYes(expYes), m_expNo(expNo) {
}

ExpressionPtr QOpExpression::clone() {
  QOpExpressionPtr exp(new QOpExpression(*this));
  Expression::deepCopy(exp);
  exp->m_condition = Clone(m_condition);
  exp->m_expYes = Clone(m_expYes);
  exp->m_expNo = Clone(m_expNo);
  return exp;
}

///////////////////////////////////////////////////////////////////////////////
// parser functions

///////////////////////////////////////////////////////////////////////////////
// static analysis functions

ConstructPtr QOpExpression::getNthKid(int n) const {
  switch (n) {
    case 0:
      return m_condition;
    case 1:
      return m_expYes;
    case 2:
      return m_expNo;
    default:
      assert(false);
      break;
  }
  return ConstructPtr();
}

int QOpExpression::getKidCount() const {
  return 3;
}

void QOpExpression::setNthKid(int n, ConstructPtr cp) {
  switch (n) {
    case 0:
      m_condition = dynamic_pointer_cast<Expression>(cp);
      break;
    case 1:
      m_expYes = dynamic_pointer_cast<Expression>(cp);
      break;
    case 2:
      m_expNo = dynamic_pointer_cast<Expression>(cp);
      break;
    default:
      assert(false);
      break;
  }
}

///////////////////////////////////////////////////////////////////////////////
// code generation functions

void QOpExpression::outputPHP(CodeGenerator &cg, AnalysisResultPtr ar) {
  m_condition->outputPHP(cg, ar);
  cg_printf(" ? ");
  if (m_expYes) {
    m_expYes->outputPHP(cg, ar);
  }
  cg_printf(" : ");
  m_expNo->outputPHP(cg, ar);
}
