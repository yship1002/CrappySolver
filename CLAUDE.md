# CrappySolver context (branch LG-noMPI)

Research code: global solver for two-stage stochastic nonconvex MINLP. This branch implements the **LG method** (Lagrangean decomposition-based spatial branch and bound, Benders part deliberately left out) on top of the `crappy-noMPI` code base. Paper: Li & Grossmann, "A generalized Benders decomposition-based branch and cut algorithm for two-stage stochastic programs with nonconvex constraints and mixed-binary first and second stage variables" (`../7065.pdf`).

## Where things stand (last updated 2026-10-06)

### Rules from the user
- Free to change anything on branch `LG-noMPI`, but **do not touch `Crappy_Fuzzy_Problem_Library/` (submodule) or any other branch.**
- **For all testing use `BranchingStrategy::relwidth`** (outside and inside), never pseudocost.
- The outer UBD is **user-provided** (`provided_UBD`). Do not implement an outer UB heuristic.
- Do not implement the Benders part (no Benders cuts, no Lagrangean cuts, no master problem, no lift-and-project).

### Git state
- Branch `LG-noMPI` at `92c58b7`, which is an ancestor of `crappy-noMPI` (that branch has everything here plus the reliability branching, OBBT, strong-branching counters, split pseudocost weights).
- I ran `git checkout crappy-noMPI -- src CMakeLists.txt test.cpp`, so those files are staged with the `crappy-noMPI` content plus my LG edits on top. **Nothing is committed.** `CLAUDE.md` is untracked. The `Crappy_Fuzzy_Problem_Library` and `mcpp` submodules show as modified; that was already the case before this work.
- To discard the LG work: `git checkout HEAD -- src CMakeLists.txt test.cpp`.
- `crappy-noMPI` has its own `CLAUDE.md` (CZ architecture) and a `scale-scenarios` skill in `.claude/skills/`. Do not copy them blindly, the two CLAUDE.md files will conflict on merge.

### What was implemented (files: `src/Algo.h`, `src/Algo.tpp`, `src/BBNode.h`, `test.cpp`)
- `outsideAlgo::calculateLBD` is the LG node bound (details below).
- `BBNode::mu` : per-scenario multipliers `mu[scenario][first-stage var]`, best ones of the node, copied to children (warm start).
- `insideAlgo::mu`, `insideAlgo::root_UBD_solution`, `insideAlgo::applyLagrangeanTerm(STModel*)`.
- `applyLagrangeanTerm` adds the term to the objective in the DAG: `F[0] = F[0] + mu[i]*X[i]`. It is called right after `buildDAG()` in `insideAlgo::calculateLBD` and `calculateUBD`, and again on the Ipopt clone (because `clone()` rebuilds the DAG and would drop the term). It only uses public members of `STModel`.
- `root_UBD_solution` is set in `insideAlgo::solve` right after the root `calculateUBD`. It is the subgradient point x_s*.
- `outsideAlgo` members: `lg_iterations_root=10`, `lg_iterations_node=3`, `lg_theta=1.0`.
- `test.cpp` is reorganised like branch `central-withouUBD`: one model header uncommented, a `USER CONFIG` block (`MODEL_TYPE`, `NUM_SCENARIOS`, `BRANCHING`, `UBD_SOLVER`, `TOLERANCE`, `PROVIDED_UBD`, `LG_ITERATIONS_ROOT`, `LG_ITERATIONS_NODE`), model built generically with an `if constexpr (is_constructible<MODEL_TYPE,BranchingStrategy,int>)` guard (Crude, EDUnits, EDUnits_nocp have no scenario-count constructor). Only the Ex722 path has been compiled and run. The guard's other path is untested. Currently: Ex722, 5 scenarios, `relwidth`, Gurobi, tol 92, UBD -92551.4.

### Node bound algorithm (`outsideAlgo::calculateLBD`)
1. `node->mu` is zero at the root, otherwise inherited. `parent_LBD` = -inf at the root, else the node's existing LBD (valid for a child since its box is a subset).
2. Loop l = 0..max_iter-1 (`lg_iterations_root` at node_id==1, else `lg_iterations_node`):
   - For each scenario s: build `insideAlgo`, set `mu = node->mu[s]`, `solve(tol/(2S))`. Any scenario infeasible -> node LBD = inf, return (mu does not affect feasibility).
   - total = sum of scenario LBDs (valid for any mu with sum_s mu_s = 0). Keep the best total with its mu and per-scenario LBDs. After 2 non-improving iterations, `theta *= 0.5`.
   - Stop early if `max(best, parent_LBD) >= bestUBD`, on the last iteration, or if a scenario returned no first-stage solution.
   - Subgradient: `g[s][i] = x_s*[i] - mean_s x*[i]` (keeps sum mu = 0). Stop if `||g||^2 < 1e-10`.
   - Polyak step: `step = theta*(bestUBD - total)/||g||^2` (fallback `max(1, 0.05|total|)` if bestUBD is not finite; stop if the target gap <= 0). `mu[s][i] += step*g[s][i]`.
3. After the loop: `node->mu = best_mu`, `node->scenario_LBDs = best`, `node->LBD = max(best_total, parent_LBD)`.
- `lg_iterations = 1` reproduces the plain CZ bound (mu = 0).
- The old per-scenario "LBD must not decrease" check was removed (scenario LBDs under different mu are not comparable).
- The subgradient update itself is plain arithmetic, no extra solve. The cost is S inner global solves per iteration. x_s* comes from the inner root UBD solve (Gurobi global within 60 s, or Ipopt local), which the inner algorithm already runs.

### Test results so far
Ex722, 5 scenarios, `relwidth`, Gurobi, tol 92, provided UBD -92551.4:
- Root Lagrangean bound by iteration: -207691 (mu=0, CZ), -121269, -100956, -97881.2, -97304.1, -96068.3, -95603.1, -95594.7, **-94389.4 (best)**, -95658.5.
- Outer iterations (LBD / gap / wall time): 0: -93457.9 / 906.5 / 35 s; 1: -93129.8 / 578.4 / 47 s; 2: -92832 / 280.6 / 62 s; 3: -92671 / 119.6 / 68 s; final: **-92642.8 / 91.41 / 73.6 s**, terminated after 6 outer iterations, 153,281 inner LP solves.
- Child node with inherited mu starts at or above the root's best (warm start works). The global LBD rose at every outer iteration and stayed below the provided UBD.
- One child had bound -31252.1 (> UBD) and was fathomed after 1 iteration; **not verified** (suggested check: rerun that box with `lg_iterations=1` and compare).
- ProcessModel (40 scenarios) was started once (iteration 0 root bound -21195.2 pseudo / -21195.5 relwidth, UBD -7264.69, tol 7.2) but killed before finishing.

### Known issues / open questions
- Iteration 1 after a warm start often dips below iteration 0 (step too large once mu is near-optimal); recovered by iteration 2. Untested idea: smaller `lg_theta` (0.2 to 0.5) for non-root nodes or a faster halving rule.
- Iteration counts (10/3), the Polyak step, the halving rule and the 1e-10 threshold are my choices, not from the paper.
- **No CZ baseline comparison yet** (run with both `LG_ITERATIONS_*` = 1 on the same model to see how much LG helps in nodes/time).
- **Stats reporting was not updated for LG.** Only console lines `LG iteration l scenario s LBD` and `LG iteration l Lagrangean bound` were added. The existing per-iteration counters and recorded vectors (`LBD_calculation_records`, `LBD_values_records`, ...) are filled per node and now sum over all LG iterations of a node. Nothing records per-LG-iteration bounds, iterations run, best iteration, step size or subgradient norm, and `serialize` is unchanged. Offered to add this, not done.
- Outer strong branching (only in `pseudo` mode) still probes with mu = 0 (`cheatstrongbranching` uses plain `calculateUBD`).
- `weirdstrongbranching`/`OBBT` are not used by `solve` and do not apply mu.
- Only Ex722 5-scenario was run to completion; other models untested with LG.

### Possible next steps
1. Compare against the CZ baseline (`LG_ITERATIONS_ROOT = LG_ITERATIONS_NODE = 1`) on Ex722 5s, then on larger models (Ex722 20s, ProcessModel).
2. Tune `lg_theta` / iteration counts; consider a smaller step for child nodes.
3. Add LG statistics (per-iteration bounds etc.) to the console summary and `serialize`.
4. Investigate the -31252.1 fathomed child.
5. Commit the work (nothing committed yet).

### How to build and run
- Build: `cmake --build build` (macOS arm64, CMake, C++17, `-O2`). Executable: `build/process`.
- Edit only the `USER CONFIG` block and the single model `#include` in `test.cpp` to switch models.
- macOS has no `timeout`; run long jobs in the background, redirect output to a log and grep it. Stop with `pkill -x process`.
- Useful log lines: `LG iteration l Lagrangean bound`, `Current UBD ... LBD ... Gap`, `Algorithm terminated`.

## LG method (from the paper, Benders part ignored)

### Problem (P)
Two-stage stochastic MINLP: `min c^T x + sum_w tau_w d_w^T y_w` s.t. `A0 x >= b0, g0(x) <= 0`, `A1_w x + g1_w(y_w) <= b1_w`, `x in X`, `y_w in Y` (mixed-binary, bounded), g0, g1_w possibly nonconvex. Assumptions: relatively complete recourse, compact feasible region, finite variable bounds.

### Single node
1. One copy x_w per scenario plus NACs `x_w1 = x_w`. Dualize the NACs (`mu_w1 = sum(pi)`, `mu_w+1 = -pi`), giving one subproblem per scenario: `min tau_w(c^T x_w + d_w^T y_w) + mu_w^T x_w` s.t. the scenario constraints, `x_w in X_q`, `y_w in Y`.
2. `LB_q = sum_w z*_SL,w` is valid for any mu with sum_w mu_w = 0. Update mu by the subgradient method over |L| iterations.
3. Upper bound in the paper: fix x~ (scenario solution closest to the weighted average, or random scenario's x_w*) and solve each scenario's second stage. **Not implemented here: the UBD is user-provided.**

### Branch and bound (paper Algorithm 2)
Select the node with the smallest LB, bisect a first-stage variable (rule 1: largest normalized relative diameter at the midpoint; rule 2: split at the best feasible solution; rule 1 must be applied at least once after finitely many iterations for the convergence proof), solve both children (warm start from the parent's mu), fathom when `UB_q - LB_q <= eps` or `LB_q - UB >= eps`, stop when no nodes remain. Here the branching rules are the `crappy-noMPI` heuristics instead (relwidth for testing, pseudocost with strong branching otherwise).

### Convergence
Exhaustive bisection (rule 1) shrinks the boxes to a point where all x_w copies are equal, so the Lagrangean bound equals the true objective. Convergence in the limit, not finite eps-convergence (unlike Cao & Zavala, and Kannan & Barton).

### Related work
Cao & Zavala (branch and bound with perfect-information bound = mu 0), Kannan & Barton (MLR, only dualizes continuous first-stage NACs), Carøe & Schultz (dual decomposition B&B).

### Benders part of the paper (NOT implemented, reference only)
Each node adds a Benders master over x with Lagrangean cuts `eta_w >= z*_SL,w - mu_w^T x` for every Lagrangean iteration plus Benders cuts from convexified subproblems (nonconvex g1_w relaxed e.g. by McCormick, convexified with rank-one lift-and-project cuts). It tightens the node bound and reduces the number of nodes, but is not needed for convergence.

## Library notes
- Models in `Crappy_Fuzzy_Problem_Library/` (submodule, do not edit): `ProcessModel` (1..40 scenarios), `Ex722Model` (1..20), `Ex844Model` (1..20), `CHPModel` (1..8), `CrudeModel`, `EDUnits`, `EDUnits_nocp`, `NFUnit`, `TTT` (last five have no scenario-count argument).
- Known provided UBDs (from `test.cpp` comments): ProcessModel 20s -4422.39, 40s -7264.69 (tol 7.2); Ex722 5s -92551.4 (tol 92), 20s -37283.5; Ex844 10s 583.156, 20s 748.34; CrudeModel -18502.5 (3 scenarios); CHP 3.03e3; EDUnits 58240; EDUnits_nocp 56844.
- `STModel` objective is `F[scenario][0]`, first-stage variables are `X[scenario][0..n1-1]`, and each model's objective already includes `probability`.
- Recompute `provided_UBD` after changing a model (commented block at the end of `main()` in `test.cpp`).
