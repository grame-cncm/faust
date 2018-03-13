/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

/* compiler/patternmatcher/patternmatcher.cpp: implementation of the Faust
   rewriting engine */

#include "tlib.hh"
#include "list.hh"
#include "boxes.hh"
#include "ppbox.hh"
#include "eval.hh"
#include "patternmatcher.hh"

using namespace std;
#include <vector>
#include <list>
#include <set>
#include <utility>
#include "exception.hh"
#include "global.hh"
#include "garbageable.hh"

/* Uncomment for debugging output. */
//#define DEBUG

/* Additional Tree deconstruction operations. */

/* Check for cons (nonempty list) nodes. */

static inline bool isCons(Tree x, Tree& h, Tree& t)
{
  if (isList(x)) {
    h = hd(x); t = tl(x);
    return true;
  } else
    return false;
}

/* Deconstruct a (BDA) op pattern (YO). */

static inline bool isBoxPatternOp(Tree box, Node& n, Tree& t1, Tree& t2)
{
    if (    isBoxPar(box, t1, t2) ||
            isBoxSeq(box, t1, t2) ||
            isBoxSplit(box, t1, t2) ||
            isBoxMerge(box, t1, t2) ||
            isBoxHGroup(box, t1, t2) ||
            isBoxVGroup(box, t1, t2) ||
            isBoxTGroup(box, t1, t2) ||
            isBoxRec(box, t1, t2)    )
    {
        n = box->node();
        return true;
    } else {
        return false;
    }
}

/* TA data structures. */

/* subterm paths */

typedef vector<int> Path;

/* Subterm at given path in given term tree. */

static Tree subtree(Tree X, int i, const Path& p)
{
  int n = (int)p.size();
  Node op(0);
  Tree x0, x1;
  if (i < n && isBoxPatternOp(X, op, x0, x1))
    return subtree((p[i]==0)?x0:x1, i+1, p);
  else
    return X;
}

/* rule markers */

struct Rule : public virtual Garbageable {
  int r; // rule number
  Tree id; // matched variable (NULL if none)
  Path p; // subterm path indicating where variable value is found

  Rule(int _r, Tree _id) : r(_r), id(_id), p(Path()) {}
  Rule(int _r, Tree _id, const Path& _p) : r(_r), id(_id), p(_p) {}
  Rule(const Rule& rule) : r(rule.r), id(rule.id), p(rule.p) {}

  Rule& operator = (const Rule& rule)
  { r = rule.r; id = rule.id; p = rule.p; return *this; }

  bool operator == (const Rule& rule) const
  { return r == rule.r; }
  bool operator < (const Rule& rule) const
  { return r < rule.r; }

#ifdef DEBUG
  ostream& print(ostream& fout) const;
#endif
};

struct State;

/* transitions */

struct Trans : public virtual Garbageable {
  Tree x; // symbol or constant (NULL for variable)
  Node n; // operator symbol (if arity>0)
  int arity; // symbol arity
  State *state; // successor state

  Trans(Tree _x);
  Trans(const Node& _n, int _arity);
  Trans(const Trans& trans);
  ~Trans();

  Trans& operator = (const Trans& trans);

  bool is_var_trans() const { return arity == 0 && x == NULL; }
  bool is_cst_trans(Tree &_x) const { _x = x; return arity == 0 && x != NULL; }
  bool is_op_trans(Node &_n) const { _n = n; return arity > 0; }

  bool operator == (const Trans& trans) const
  { return arity == trans.arity && x == trans.x && n == trans.n; }
  bool operator < (const Trans& trans) const
  { return (arity < trans.arity) ? 1 :
      (arity > trans.arity) ? 0 :
      (arity == 0) ? (x < trans.x) :
      (n.getSym() < trans.n.getSym()); }

#ifdef DEBUG
  ostream& print(ostream& fout) const;
#endif
};

/* states */

struct State : public virtual Garbageable {
  int s; // state number
  bool match_num; // whether state has a transition on a numeric constant
  list<Rule> rules; // rule markers
  list<Trans> trans; // transitions (1st transition is on variable if available)
  State() :
    s(0), match_num(false), rules(list<Rule>()), trans(list<Trans>()) {}
  State(const State& state) :
    s(state.s), match_num(state.match_num),
    rules(state.rules), trans(state.trans) {}

  State& operator = (const State& state)
  { s = state.s; match_num = state.match_num;
    rules = state.rules; trans = state.trans;
	return *this;
  }

#ifdef DEBUG
  ostream& print(ostream& fout) const;
#endif
};

// these need to come here so that the storage size of struct State is known

Trans::Trans(Tree _x) :
  x(_x), n(0), arity(0), state(new State)
{
}

Trans::Trans(const Node& _n, int _arity) :
  x(NULL), n(_n), arity(_arity), state(new State)
{
}

Trans::Trans(const Trans& trans) :
  x(trans.x), n(trans.n), arity(trans.arity)
{
  state = new State(*trans.state);
}

Trans::~Trans()
{}

Trans& Trans::operator = (const Trans& trans)
{
  x = trans.x; n = trans.n; arity = trans.arity;
  state = new State(*trans.state);
  return *this;
}

/* the automaton */

struct Automaton : public virtual Garbageable {
  vector<State*> state;
  vector<Tree> rhs;

  Automaton() : state(vector<State*>()), rhs(vector<Tree>()), s(0) {}

  // number of rules
  int n_rules() { return (int)rhs.size(); }
  // markers of rules still active in state s
  const list<Rule>& rules(int s) { return state[s]->rules; }
  // transitions in state s
  const list<Trans>& trans(int s) { return state[s]->trans; }
  // is s a final state?
  bool final(int s) { return trans(s).empty(); }

  // assign state numbers and build the state table
  int s;
  void build(State *st);

#ifdef DEBUG
  ostream& print(ostream& fout) const;
#endif
};

void Automaton::build(State *st)
{
  state.push_back(st);
  st->s = s++;
  list<Trans>::const_iterator t;
  for (t = st->trans.begin(); t != st->trans.end(); t++) {
    Tree x;
    double f;
    int i;
    if (t->is_cst_trans(x) &&
	(isBoxInt(x, &i) || isBoxReal(x, &f)))
      st->match_num = true;
    build(t->state);
  }
}

/* Debugging output. */

#ifdef DEBUG
inline ostream& operator << (ostream& s, const Rule& x)
{ return x.print(s); }
inline ostream& operator << (ostream& s, const Trans& x)
{ return x.print(s); }
inline ostream& operator << (ostream& s, const State& x)
{ return x.print(s); }
inline ostream& operator << (ostream& s, const Automaton& x)
{ return x.print(s); }

ostream& Rule::print(ostream& fout) const
{
  if (id != NULL)
    fout << "#" << r << "(" << *id << ")";
  else
    fout << "#" << r;
  return fout;
}

ostream& Trans::print(ostream& fout) const
{
  if (arity > 0)
    fout << "\top  " << n << ": state " << state->s << endl;
  else if (x == NULL)
    fout << "\tvar _: state " << state->s << endl;
  else
    fout << "\tcst " << *x << ": state " << state->s << endl;
  return fout;
}

ostream& State::print(ostream& fout) const
{
  fout << "state " << s << ":";
  list<Rule>::const_iterator r;
  for (r = rules.begin(); r != rules.end(); r++)
    fout << " " << *r;
  fout << endl;
  list<Trans>::const_iterator t;
  for (t = trans.begin(); t != trans.end(); t++)
    fout << *t;
  return fout;
}

ostream& Automaton::print(ostream& fout) const
{
  int i, n = rhs.size();
  for (i = 0; i < n; i++)
    fout << "rule #" << i << ": " << *rhs[i] << endl;
  n = state.size();
  for (i = 0; i < n; i++)
    fout << *state[i];
  return fout;
}
#endif

/* Construction algorithm for the pattern matching automaton.
 *
 * We employ the incremental technique described in Graef: Left-To-Right Tree
 * Pattern Matching, Proc. RTA 1991, Springer 1991 (LNCS 488) to construct a
 * tree automaton (TA) for the given patterns. The basic outline of the
 * technique is as follows. Initially, the automaton is empty. From each
 * pattern we produce a trie (considering the pattern as a string of variable
 * and function symbols and constants). This trie is then merged with the TA
 * obtained so far. The latter process is similar to merging two deterministic
 * finite automata, but it also takes into account the variables (see the
 * merge_state() routine below).
 */

/* Construct a trie from a term tree. Takes the "start" and returns the "end"
   state of the (sub-)trie. */

static State *make_state(State *state, int r, Tree x, Path& p)
{
  Tree id, x0, x1;
  Node op(0);
  if (isBoxPatternVar(x, id)) {
    /* variable */
    Rule rule(r, id, p);
    state->rules.push_back(rule);
    Trans trans(NULL);
    state->trans.push_back(trans);
    return state->trans.begin()->state;
  } else if (isBoxPatternOp(x, op, x0, x1)) {
    /* composite pattern */
    Rule rule(r, NULL);
    state->rules.push_back(rule);
    Trans trans(op, 2);
    state->trans.push_back(trans);
    State *next = state->trans.begin()->state;
    p.push_back(0);
    next = make_state(next, r, x0, p);
    p.pop_back();
    p.push_back(1);
    next = make_state(next, r, x1, p);
    p.pop_back();
    return next;
  } else {
    /* constant */
    Rule rule(r, NULL);
    state->rules.push_back(rule);
    Trans trans(x);
    state->trans.push_back(trans);
    return state->trans.begin()->state;
  }
}

/* Take a copy of a state and prefix it with n variable transitions. */

static State *make_var_state(int n, State *state)
{
  if (n <= 0)
    return new State(*state);
  list<Rule>rules = state->rules;
  list<Rule>::iterator r;
  for (r = rules.begin(); r != rules.end(); r++) {
    r->id = NULL; r->p = Path();
  }
  State *prefix = new State, *current = prefix;
  while (n-- > 0) {
    current->rules = rules;
    Trans trans(NULL);
    current->trans.push_back(trans);
    current = current->trans.begin()->state;
  }
  *current = *state;
  return prefix;
}

/* Merge two tree automata. Merges the tree automaton rooted at state2 into
   the automaton rooted at state1. We assume that state2 is in "trie" form,
   i.e., each state has at most one transition, which is always guaranteed
   here and simplifies the algorithm. */

static void merge_state(State *state1, State *state2);

static void inline merge_rules(list<Rule>& rules1, list<Rule>& rules2)
{
  list<Rule> cprules2 = rules2;
  rules1.merge(cprules2);
}

static void merge_trans_var(list<Trans>& trans, State *state)
{
  if (!trans.begin()->is_var_trans()) {
    /* If we don't have a variable transition in this state yet then create a
       new one. */
    Trans tr(NULL);
    trans.push_front(tr);
  }
  list<Trans>::const_iterator t;
  Tree x;
  Node op(0);
  for (t = trans.begin(); t != trans.end(); t++) {
    if (t->is_var_trans())
      merge_state(t->state, state);
    else if (t->is_cst_trans(x)) {
      /* add the completion of the given state for a constant */
      merge_state(t->state, state);
    } else if (t->is_op_trans(op)) {
      /* add the completion of the given state for an arity>0 op */
      State *state1 = make_var_state(t->arity, state);
      merge_state(t->state, state1);
    }
  }
}

static void merge_trans_cst(list<Trans>& trans, Tree x, State *state)
{
  list<Trans>::iterator t0 = trans.begin(), t1 = t0, t;
  Tree x1;
  if (t0->is_var_trans()) t1++;
  for (t = t1; t != trans.end(); t++) {
    if (t->is_cst_trans(x1)) {
      if (x == x1) {
	merge_state(t->state, state);
	return;
      } else if (x < x1)
	break;
    }
  }
  /* no matching transition has been found; add a new one */
  Trans tr(x);
  trans.insert(t, tr); t--;
  State *state1 = t->state;
  *state1 = *state;
  if (t1 != t0) {
    /* if we have a variable transition in the current state, we also need to
       merge its completion for the current symbol/constant */
    merge_state(state1, t0->state);
  }
}

static void merge_trans_op(list<Trans>& trans, const Node& op,
			   int arity, State *state)
{
  /* analogous to merge_trans_cst above, but handles the arity>0 case */
  list<Trans>::iterator t0 = trans.begin(), t1 = t0, t;
  Node op1(0);
  if (t0->is_var_trans()) t1++;
  for (t = t1; t != trans.end(); t++) {
    if (t->is_op_trans(op1)) {
      if (op == op1) {
	merge_state(t->state, state);
	return;
      } else if (op.getSym() < op1.getSym())
	break;
    }
  }
  Trans tr(op, arity);
  trans.insert(t, tr); t--;
  State *state1 = t->state;
  *state1 = *state;
  if (t1 != t0) {
    State *state2 = make_var_state(arity, t0->state);
    merge_state(state1, state2);
  }
}

static void merge_trans(list<Trans>& trans1, list<Trans>& trans2)
{
  Tree x;
  Node op(0);
  if (trans2.empty())
    ;
  else if (trans1.empty()) {
    list<Trans> cptrans2 = trans2;
    /* append a copy of trans2 to trans1 */
    trans1.splice(trans1.end(), cptrans2);
  } else if (trans2.begin()->is_var_trans())
    /* merge a variable transition */
    merge_trans_var(trans1, trans2.begin()->state);
  else if (trans2.begin()->is_cst_trans(x))
    /* merge a constant transition */
    merge_trans_cst(trans1, x, trans2.begin()->state);
  else if (trans2.begin()->is_op_trans(op))
    /* merge a BDA op transition */
    merge_trans_op(trans1, op, trans2.begin()->arity, trans2.begin()->state);
}

static void merge_state(State *state1, State *state2)
{
  merge_rules(state1->rules, state2->rules);
  merge_trans(state1->trans, state2->trans);
}

/* Take the rules of a BoxCase expression and return a pointer to the
   corresponding TA automaton (interface operation). */

Automaton *make_pattern_matcher(Tree R)
/* Tree R encodes the rules of a case box expressions as a Tree object, as
   follows:

   Rules	::= cons Rule (cons Rule ... nil)
   Rule		::= cons Lhs Rhs
   Lhs		::= cons Pattern (cons Pattern ... nil)
   Pattern	::= Tree (parameter pattern)
   Rhs		::= Tree

   NOTE: The lists of rules and patterns are actually delivered in reverse
   order by the parser, so we have to reverse them on the fly. */
{
  Automaton *A = new Automaton;
  int n = len(R), r = n;
  State *start = new State;
  Tree rule, rest;
  vector<Tree> rules(n, (Tree)NULL);
  vector< vector<Tree> > testpats(n);
  while (isCons(R, rule, rest)) {
    rules[--r] = rule;
    R = rest;
  }
  for (r = 0; r < n; r++) {
    Tree lhs, rhs;
    if (isCons(rules[r], lhs, rhs)) {
      Tree pat, rest;
      int m = len(lhs), i = m;
      vector<Tree> pats(len(lhs), (Tree)NULL);
      State *state0 = new State, *state = state0;
      A->rhs.push_back(rhs);
      while (isCons(lhs, pat, rest)) {
        pats[--i] = pat;
        lhs = rest;
      }
      testpats[r] = pats;
      for (i = 0; i < m; i++) {
        Path p;
        state = make_state(state, r, pats[i], p);
      }
      Rule rule(r, NULL);
      state->rules.push_back(rule);
      merge_state(start, state0);
    }
  }
  A->build(start);
  /* Check for shadowed rules. Note that because of potential nonlinearities
     it is *not* enough to just check the rule lists of final states and
     determine whether they have multiple matched rules. */
  for (r = 0; r < n; r++) {
    int s = 0, m = (int)testpats[r].size();
    Tree C;
    vector<Tree> E(n, gGlobal->nil);
    /* try to match the lhs of rule #r */
    for (int i = 0; i < m; i++) {
      s = apply_pattern_matcher(A, s, testpats[r][i], C, E);
      if (s < 0) break;
    }
    if (A->final(s)) {
      list<Rule>::const_iterator ru;
      for (ru = A->rules(s).begin(); ru != A->rules(s).end(); ru++)
      if (!isBoxError(E[ru->r])) {
          if (ru->r < r) {
            /* Lhs of rule #r matched a higher-priority rule, so rule #r may
               be shadowed. */
            Tree lhs1, rhs1, lhs2, rhs2;
            if (isCons(rules[ru->r], lhs1, rhs1) &&  isCons(rules[r], lhs2, rhs2)) {
                cerr << "WARNING : shadowed pattern-matching rule: "
                    << boxpp(reverse(lhs2)) << " => " << boxpp(rhs2) << ";"
                    << " previous rule was: "
                    << boxpp(reverse(lhs1)) << " => " << boxpp(rhs1) << ";"
                    << endl;
            } else {
                stringstream error;
                error << "ERROR : " << __FILE__ << ":" << __LINE__ << endl;
                throw faustexception(error.str());
            }
          } else if (ru->r >= r) {
              break;
          }
       }
    }
  }
#ifdef DEBUG
  cerr << "automaton " << A << endl << *A << "end automaton" << endl;
#endif
  return A;
}

/* Helper type to represent variable substitutions which are recorded during
   matching. Each variable is associated with the path pointing at the subterm
   of the argument where the substitution of the matched variable is to be
   found. */

struct Assoc : public virtual Garbageable {
  Tree id;
  Path p;
  Assoc(Tree _id, const Path& _p) : id(_id), p(_p) {}
};
typedef list<Assoc> Subst;

/* add all substitutions for a given state */

static void add_subst(vector<Subst>& subst, Automaton *A, int s)
{
  list<Rule> rules = A->rules(s);
  list<Rule>::const_iterator r;
  for (r = rules.begin(); r != rules.end(); r++)
    if (r->id != NULL)
      subst[r->r].push_back(Assoc(r->id, r->p));
}

/* Process a given term tree X starting from state s, modify variable
   substitutions accordingly. Returns the resulting state, or -1 if no
   match. This does all the grunt work of matching. */

static int apply_pattern_matcher_internal(Automaton *A, int s, Tree X,
					  vector<Subst>& subst)
{
  /* FIXME: rewrite this non-recursively? */
  if (s >= 0) {
    list<Trans>::const_iterator t;
    if (A->state[s]->match_num)
      /* simplify possible numeric argument on the fly */
      X = simplifyPattern(X);
    /* first check for applicable non-variable transitions */
    for (t = A->trans(s).begin(); t != A->trans(s).end(); t++) {
      Tree x;
      Node op(0), op1(0);
      if (t->is_var_trans())
	continue;
      else if (t->is_cst_trans(x)) {
	if (X==x) {
	  /* transition on constant */
#ifdef DEBUG
      cerr << "state " << s << ", " << *x << ": goto state " << t->state->s << endl;
#endif
	  add_subst(subst, A, s);
	  s = t->state->s;
	  return s;
	}
      } else if (t->is_op_trans(op)) {
        Tree x0, x1;
        if (isBoxPatternOp(X, op1, x0, x1) && op == op1) {
          /* transition on operation symbol */
    #ifdef DEBUG
          cerr << "state " << s << ", " << op << ": goto state " << t->state->s << endl;
    #endif
          add_subst(subst, A, s);
          s = t->state->s;
          if (s >= 0)
            s = apply_pattern_matcher_internal(A, s, x0, subst);
          if (s >= 0)
            s = apply_pattern_matcher_internal(A, s, x1, subst);
          return s;
        }
      }
    }
    /* check for variable transition (is always first in the list of
       transitions) */
    t = A->trans(s).begin();
    if (t->is_var_trans()) {
#ifdef DEBUG
      cerr << "state " << s << ", _: goto state " << t->state->s << endl;
#endif
      add_subst(subst, A, s);
      s = t->state->s;
    } else {
#ifdef DEBUG
      cerr << "state " << s << ", *** match failed ***" << endl;
#endif
      s = -1;
    }
  }
  return s;
}

/* Apply the pattern matcher to a single argument, starting from a given state
   (interface operation). Returns the resulting state, modifies the variable
   bindings E accordingly, and sets C to the resulting closure if a final
   state is reached. Result will be -1 to indicate a matching failure, and C
   will be set to nil if no final state has been reached yet. */

int apply_pattern_matcher(Automaton *A,	// automaton
                        int s,          // start state
                        Tree X,         // arg to be matched
                        Tree& C,        // output closure (if any)
                        vector<Tree>& E)// modified output environments
{
  int n = A->n_rules();
  vector<Subst> subst(n, Subst());
  /* perform matching, record variable substitutions */
#ifdef DEBUG
  cerr << "automaton " << A << ", state " << s << ", start match on arg: " << *X << endl;
#endif
  s = apply_pattern_matcher_internal(A, s, X, subst);
  C = gGlobal->nil;
  if (s < 0)
    /* failed match */
    return s;
  /* process variable substitutions */
  list<Rule>::const_iterator r;
  for (r = A->rules(s).begin(); r != A->rules(s).end(); r++) {
    // all rules still active in state s
    if (!isBoxError(E[r->r])) { // and still viable
      Subst::const_iterator assoc;
      for (assoc = subst[r->r].begin(); assoc != subst[r->r].end(); assoc++) {
	Tree Z, Z1 = subtree(X, 0, assoc->p);
	if (searchIdDef(assoc->id, Z, E[r->r])) {
	  if (Z != Z1) {
	    /* failed nonlinearity, add to the set of nonviable rules */
#ifdef DEBUG
      cerr << "state " << s << ", rule #" << r->r << ": " <<
	    *assoc->id << " := " << *Z1 << " *** failed *** old value: " <<
	    *Z << endl;
#endif
	    E[r->r] = boxError();
	  }
	} else {
	  /* bind a variable for the current rule */
#ifdef DEBUG
      cerr << "state " << s << ", rule #" << r->r << ": " <<
	    *assoc->id << " := " << *Z1 << endl;
#endif
	  E[r->r] = pushValueDef(assoc->id, Z1, E[r->r]);
	}
      }
    }
  }
  if (A->final(s)) {
    /* if in a final state then return the right-hand side together with the
       corresponding variable environment */
    for (r = A->rules(s).begin(); r != A->rules(s).end(); r++) // all rules matched in state s
      if (!isBoxError(E[r->r])) { // and still viable
        /* return the rhs of the matched rule */
        C = closure(A->rhs[r->r], gGlobal->nil, gGlobal->nil, E[r->r]);
    #ifdef DEBUG
        cerr << "state " << s << ", complete match yields rhs #" << r->r <<
          ": " << *A->rhs[r->r] << endl;
    #endif
        return s;
      }
    /* if none of the rules were matched then declare a failed match */
#ifdef DEBUG
    cerr << "state " << s << ", *** match failed ***" << endl;
#endif
    return -1;
  }
#ifdef DEBUG
  cerr << "state " << s << ", successful incomplete match" << endl;
#endif
  return s;
}
