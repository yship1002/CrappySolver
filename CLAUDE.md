# CrappySolver context

## LG method (Lagrangean decomposition-based spatial branch and bound)

Source: Li & Grossmann, "A generalized Benders decomposition-based branch and cut algorithm for two-stage stochastic programs with nonconvex constraints and mixed-binary first and second stage variables" (7065.pdf). The Benders part of that paper is not convergence-critical; the notes below describe the LG-only method (the branch `LG-noMPI` is the LG variant).

### Implementation status on this branch (LG-noMPI)

`src/` is taken from `crappy-noMPI` (inner reliability branching, pseudocost outer/inner weights, strong branching). The LG layer is added on top, without touching `Crappy_Fuzzy_Problem_Library`:

- `outsideAlgo::calculateLBD` (`src/Algo.tpp`) is the LG node bound: up to `lg_iterations_root` (root) or `lg_iterations_node` (other nodes) subgradient iterations. Each iteration solves every scenario globally with `insideAlgo::solve`, with multipliers `mu[s]` set. Node LBD = max(best sum over iterations, parent LBD). `lg_iterations=1` is the plain CZ bound.
- Multiplier update: subgradient = x_w* minus the scenario mean (keeps sum_w mu_w = 0), Polyak step `theta*(bestUBD - L)/||g||^2` with the user-provided UBD. `lg_theta` starts at 1 and is halved after 2 non-improving iterations. The loop stops early if scenario solutions agree or the node can be fathomed.
- x_w* is `insideAlgo::root_UBD_solution`, the first-stage part of the root UBD solve of the scenario subproblem (Gurobi or Ipopt).
- `BBNode::mu` stores the best multipliers of a node. Children copy them (warm start).
- The term `mu^T x` is added to the objective with `insideAlgo::applyLagrangeanTerm`: `F[0] = F[0] + mu_i*X[i]` after every `buildDAG()` in the inner LBD and UBD paths (and again on the Ipopt clone, since `clone()` rebuilds the DAG). It uses only the public `F`/`X`/`DAG` members, so the model library is untouched.
- The outer UBD is the user-provided `provided_UBD` (`outsideAlgo::calculateUBD` just returns it). The paper's UB heuristic (fix x~, solve second stages) is deliberately not implemented.
- Branching is the `crappy-noMPI` one: outer pseudocost branching with strong branching on the first-stage variables, inner reliability branching (`reliabilityProbe`).
- `test.cpp` runs `outsideAlgo LGalgo` with `lg_iterations_root=10`, `lg_iterations_node=3`.

### Problem (P)

Two-stage stochastic MINLP:

    min  c^T x + sum_w tau_w d_w^T y_w
    s.t. A0 x >= b0, g0(x) <= 0
         A1_w x + g1_w(y_w) <= b1_w   for all w
         x in X (mixed-binary, bounded), y_w in Y (mixed-binary, bounded)

g0, g1_w may be smooth nonconvex. Assumptions: relatively complete recourse, compact feasible region, finite bounds on x and y.

### Single node q (solvenode)

1. Give each scenario its own copy x_w and add nonanticipativity constraints (NACs) x_w1 = x_w for all w. The paper uses the form where every NAC contains x_w1.
2. Dualize the NACs with multipliers pi. Set mu_w1 = sum(pi) and mu_w+1 = -pi. This splits the problem into one Lagrangean subproblem per scenario:

       min tau_w (c^T x_w + d_w^T y_w) + mu_w^T x_w
       s.t. A0 x_w >= b0, g0(x_w) <= 0, A1_w x_w + g1_w(y_w) <= b1_w, x_w in X_q, y_w in Y

   Each one is a small nonconvex MINLP solved globally (X_q is the node's box).
3. Lower bound: LB_q = sum_w z*_SL,w. It is valid for any mu. Keep the best value over iterations.
4. Update mu with the subgradient method. The subgradient is the NAC violation. Run up to |L| iterations.
5. Upper bound: fix x~ and solve each scenario's second-stage problem UB_w separately (tau_w d_w^T y_w s.t. g1_w(y_w) <= b1_w - A1_w x~, y_w in Y). Choices of x~:
   - the scenario Lagrangean solution x_w* closest (scaled by the variable ranges) to the probability-weighted average of all x_w*;
   - a randomly chosen scenario's x_w*.
6. Return [LB_q, UB_q].

### Branch and bound (Algorithm 2)

- Init: UB = +inf, LB = -inf, all mu = 0, solve the root node, active set Gamma = {root}.
- Node selection: the active node with the smallest LB_q.
- Branch on first-stage variables only, creating two children:
  - Rule 1: bisect the variable with the largest normalized relative diameter, (xub_q - xlb_q)_i / (root range)_i * delta_i, at the midpoint.
  - Rule 2: split at the value of the best feasible first-stage solution (the average solution).
  - Rule 1 must be applied at least once after any finite number of iterations. The convergence proof needs this.
- Solve both children. They may be warm-started with the parent's multipliers (the ones that gave the tightest parent LB) or with zero.
- UB = min UB_q and LB = min LB_q over the active nodes.
- Fathom a node if UB_q - LB_q <= eps (optimal) or LB_q - UB >= eps (bound).
- Stop when the active set is empty.

### Convergence

Rule 1 gives exhaustive bisection, so the boxes X_q shrink to a point. At a point, all x_w copies are forced equal, so the NACs hold and the Lagrangean bound equals the true objective. LB and UB therefore meet in the limit. This is convergence in the limit, not finite eps-convergence (unlike Cao & Zavala, and Kannan & Barton).

### Related prior work

- Cao & Zavala: branch and bound with perfect-information bounds (Lagrangean relaxation with mu = 0).
- Kannan & Barton (MLR): dualizes only the NACs of the continuous first-stage variables.
- Carøe & Schultz: dual decomposition branch and bound.

### Benders part (optional accelerator, for reference only)

Each node can add a Benders master over x, with Lagrangean cuts eta_w >= z*_SL,w - mu_w^T x for every iteration l, plus Benders cuts from subproblems. The subproblems are the second-stage problems with nonconvex g1_w relaxed (e.g. McCormick) and convexified with rank-one lift-and-project cuts, so that valid duals exist. The Lagrangean cuts keep the master bound at least as tight as Lagrangean decomposition. The Benders cuts only reduce the number of nodes. Dropping them leaves a valid Lagrangean-bounded branch and bound.
