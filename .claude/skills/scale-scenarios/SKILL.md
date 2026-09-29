---
name: scale-scenarios
description: Stress-test CrappySolver's two-stage stochastic branch-and-bound algorithm by artificially growing the number of scenarios in ProcessModel (Crappy_Fuzzy_Problem_Library/ProcessModel.cpp) and re-deriving the new optimal objective. Use this whenever the user asks to increase, add, or scale up scenarios for ProcessModel, wants to see how the algorithm's iteration count/wall time scales with problem size, or asks to "rerun with more scenarios" / "test the algorithm's effectiveness" on this repo. Do not use for other models in the library (Ex844, CrudeModel, Ex722, CHPModel, EDUnits) unless the user explicitly says so — the file paths and line ranges below are ProcessModel-specific.
---

# Scale scenarios in ProcessModel

## Why this procedure exists

`ProcessModel` (`Crappy_Fuzzy_Problem_Library/ProcessModel.cpp`) is a two-stage stochastic
problem with a fixed scenario set. Adding scenarios changes the true optimal objective, so two
things have to happen together: the new scenarios need to be genuinely different from the
existing ones (not near-duplicates, or the test doesn't exercise anything new), and the outer
branch-and-bound's initial upper bound (`provided_UBD` in `test.cpp`) needs to be recomputed for
the new scenario count — an upper bound valid for the old count can cause the B&B to prune the
true optimum and silently report a wrong answer.

## Step 1 — Add N new scenarios to `ProcessModel.cpp`

Edit `ProcessModel::ProcessModel` in `Crappy_Fuzzy_Problem_Library/ProcessModel.cpp` (currently
around line 429-493). Three maps/lists to touch, all keyed by `ScenarioNames`:

1. **`this->scenario_names`** — append the new names. The `ScenarioNames` enum
   (`Crappy_Fuzzy_Problem_Library/STModel.h`) already defines `SCENARIO1` through `SCENARIO100`,
   so just reference `ScenarioNames::SCENARIO<N>` — no enum edits needed. Leave every existing
   entry untouched.
2. **`this->perturb`** — add a `{ScenarioNames::SCENARIO<N>, <value>}` entry per new scenario.
3. **`this->price`** — same, per new scenario.
4. **`this->probability`** — update to `1.0 / <new total scenario count>`. The model uses one
   shared probability scalar for every scenario (equal weighting by design), so this is the only
   change needed to keep it a valid probability distribution.

**Picking `perturb`/`price` values for the new scenarios:** don't interpolate the existing
range — a scenario whose parameters sit between two existing scenarios will usually just have a
recourse solution that's a blend of theirs, which doesn't tell you anything new about how the
algorithm scales. Instead pick values outside the existing envelope, and ideally cross-paired in
the opposite correlation from the existing pattern (e.g. if existing scenarios pair high-perturb
with high-price, give some new scenarios high-perturb with low-price), so the new scenarios'
optimal decisions are qualitatively different rather than an extension of the same trend. Read
the existing `perturb`/`price` values in the file to see the current envelope before picking new
ones. One hard constraint: keep `|perturb|` comfortably below 18 — a comment already in the file
documents that magnitude as breaking full-model feasibility (it forces the shared first-stage
acid-rate variable to satisfy every scenario at once, which is only reachable at extreme
throughput and can make the recourse problem net-positive-cost, at which point the relative gap
stops being well-defined).

**Example** (from a 10→20 scenario run already validated end-to-end): existing scenarios spanned
`perturb` in [-2.7, 2.7] and `price` in [0.02, 0.26]. The 10 new scenarios used `perturb` up to
±4.5 and `price` both below (~0.005-0.015) and above (~0.32-0.40) the existing range, crossed
against perturb sign in both directions.

**Nothing else in `ProcessModel.cpp` needs to change.** `buildDAG()`, `buildFullModelDAG()`, and
`clone()` are all written generically in terms of `scenario_names.size()` and map lookups — they
automatically pick up however many scenarios are in `scenario_names`. In particular, don't "fix"
the division by `n_scenarios` inside `buildFullModelDAG()` — it looks suspicious in isolation
(dividing a small fixed-size template by scenario count) but it's correct: `insideAlgo`'s
constructor calls `model->convertToCentralizedModel()` before `buildFullModelDAG()` runs
whenever `solvefullModel=true` (see step 2), which pre-expands `second_stage_IX` by a factor of
`n_scenarios`, making the division recover the right per-scenario count. This was verified by
tracing the call path, not assumed.

## Step 2 — Recompute the initial UBD (phase A build/run)

`test.cpp`'s `main()` has two blocks side by side, toggled by comments — never delete either,
just swap which one is active:

- The **solve block** (currently active): `outsideAlgo CZalgo(&model, <UBD literal>,
  UBDSolver::GUROBI); CZalgo.bestUBDforInfinity=true; CZalgo.solve(1);`
- The **UBD-computation block** (currently commented out, marked between
  `// *************uncooment this part...` and `// ***********************`):
  `insideAlgo CZalgo(&model,ScenarioNames::SCENARIO1,INFINITY,true,UBDSolver::GUROBI);
  std::cout << "UBD is: "<<CZalgo.calculateUBD(&(CZalgo.activeNodes[0]), 1)<<std::endl;`

To get a UBD valid for the new scenario count:

1. Comment out the solve block, uncomment the UBD-computation block.
2. Rebuild from the repo root: `cmake --build build -j 4` (the `build/` directory is already
   configured with CPLEX/Gurobi/IPOPT paths in `build/CMakeCache.txt` — don't reconfigure from
   scratch).
3. Run `./build/process` and capture stdout. It should print a single finite line,
   `UBD is: <value>`. If it prints `inf` or doesn't terminate quickly, the new scenario set is
   likely infeasible as a combined extensive-form problem — go back to step 1 and narrow the new
   `perturb`/`price` values (this is the fast way to sanity-check feasibility before committing
   to the long B&B solve in step 3).

Never fabricate this value — it must come from actually running the compiled binary.

## Step 3 — Solve with the new UBD (phase B build/run)

1. In `test.cpp`, replace the old UBD literal in the solve block's `outsideAlgo CZalgo(&model,
   <old value>, UBDSolver::GUROBI);` line with the value printed in step 2.
2. Swap the comment state back: uncomment the solve block, re-comment the UBD-computation block.
3. Rebuild (`cmake --build build -j 4`) and run `./build/process`.

This is the real solve and can take a while — it prints one line per B&B iteration
(`Current UBD: ..., LBD: ..., Gap: ... Total Wall Time: ... seconds`) until it converges to the
0.1%-relative/1-absolute tolerance set by `CZalgo.solve(1)`, ending with `Best Solution: <value>`.
Run it with a generous timeout or in the background rather than assuming it finishes quickly —
warn the user up front if you're about to kick off a long run. Never fabricate the final
objective, iteration count, or wall time; they must come from the actual run output.

## Step 4 — Report

Tell the user: the new `Best Solution` objective, how many iterations it took, and the wall
time, compared against the previous scenario count's run (if known), so they can judge how the
algorithm scales with problem size.

## Notes

- Edits happen in two places: `Crappy_Fuzzy_Problem_Library/ProcessModel.cpp` (a git submodule)
  and `test.cpp` (repo root). No commits are needed as part of this workflow — just edit, build,
  run, report.
- If a run's UBD or objective looks off relative to a previous run, re-check the `perturb`/
  `price` values chosen in step 1 before assuming an algorithm bug.
