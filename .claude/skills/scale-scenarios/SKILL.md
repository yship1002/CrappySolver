---
name: scale-scenarios
description: Stress-test CrappySolver's two-stage stochastic branch-and-bound algorithm by artificially growing the number of scenarios in any model of Crappy_Fuzzy_Problem_Library (ProcessModel, Ex844, CrudeModel, Ex722, CHPModel, EDUnits, ...) and re-deriving the new optimal objective. Use this whenever the user asks to increase, add, or scale up scenarios for a model, wants to see how the algorithm's iteration count/wall time scales with problem size, or asks to "rerun with more scenarios" / "test the algorithm's effectiveness" on this repo. Scale-ups must always be reversible (original scenarios kept intact, new ones in a marked block that can be commented out to scale back down). If the user doesn't name a model, use the one instantiated in test.cpp's main().
---

# Scale scenarios in a Crappy_Fuzzy_Problem_Library model

## Why this procedure exists

Every model in `Crappy_Fuzzy_Problem_Library/` is a two-stage stochastic problem with a fixed
scenario set. Adding scenarios changes the true optimal objective, so two things have to happen
together: the new scenarios need to be genuinely different from the existing ones (not
near-duplicates, or the test doesn't exercise anything new), and the outer branch-and-bound's
initial upper bound (`provided_UBD` in `test.cpp`) needs to be recomputed for the new scenario
count — an upper bound valid for the old count can cause the B&B to prune the true optimum and
silently report a wrong answer.

The models do **not** share a common scenario-data layout, so Step 0 (discover the layout) is
mandatory. Don't assume any line numbers or field names from a previous run on another model.

## Step 0 — Identify the model and its scenario data

1. Find the model in `test.cpp`'s `main()` (e.g. `Ex844Model model(...)`, `ProcessModel model(...)`)
   and open the matching `Crappy_Fuzzy_Problem_Library/<Model>.cpp` constructor. Beware of large
   commented-out older copies of the constructor (Ex844.cpp and Ex722.cpp have them) — edit the
   live one only.
2. In the constructor, list everything indexed by scenario. Always present:
   - `this->scenario_names` (vector of `ScenarioNames`) — the `ScenarioNames` enum in
     `STModel.h` defines `SCENARIO1`…`SCENARIO100`, so no enum edits are needed for ≤100.
   - `this->probability` — usually one shared scalar (equal weighting).
   Model-specific scenario data varies. Examples seen so far:
   - ProcessModel: maps `perturb`, `price` keyed by `ScenarioNames`.
   - Ex844: maps such as `perturb_a` (and others) keyed by `ScenarioNames`.
   - Ex722: `perturb` map, hard-coded `probability = 0.2`.
   - CHPModel: `CHP_SCENARIO_DATA[s]` array indexed by position, copied into
     `perturb_coeffs[...]`; probability is already `1/scenario_names.size()`.
   - CrudeModel: `perturb_coeffs = {...}` (vector per scenario); probability hard-coded 0.3333.
   - EDUnits: probability `1.0` (check whether the objective is a sum or an average before
     touching it).
   Grep the constructor for every use of `scenario_names`/`ScenarioNames::SCENARIO` to make sure
   you find *all* per-scenario tables. A missed table means an out-of-range lookup or a
   default-initialised (zero) parameter for the new scenarios.
3. Check how `probability` enters the objective (`buildDAG`, `buildFullModelDAG`). If it's a
   shared scalar, set it to `1.0 / <new total>`. If the model uses per-scenario probabilities
   or a different normalisation, adjust accordingly so they still sum to 1.
4. Check that `buildDAG()`, `buildFullModelDAG()` and `clone()` are generic in
   `scenario_names.size()`. Usually they are (they loop over `scenario_names`), but grep for
   hard-coded counts or comments like `// 10`, `// 8`, `// 4 + 2*5 = 14` — these are usually
   just comments, but a literal in code would need updating. Also look at `clone()`: it must
   copy every per-scenario table you touched.
   Do not "fix" divisions like `second_stage_IX.size() / scenario_names.size()` — they are
   intentional: `insideAlgo`'s constructor calls `model->convertToCentralizedModel()` before
   `buildFullModelDAG()` when `solvefullModel=true`, which pre-expands `second_stage_IX` by a
   factor of `n_scenarios`, and the division recovers the per-scenario count.
5. Note the current scenario count and the model's *existing envelope* for every scenario
   parameter (min/max of each table).

## Step 1 — Add N new scenarios (reversibly)

**Hard requirement: scaling up must be trivially reversible.** The user must be able to return to
the original problem by commenting out/deleting a small, clearly marked piece of code — never by
hand-reconstructing old values. This applies to every model you are given, so design the edit
around it from the start.

Edit the constructor. Leave every existing entry untouched; only append.

1. Keep the original scenario list intact and add the new scenarios as a separate, clearly marked
   block that can be disabled on its own. Example (10 → 20):
   ```cpp
   this->scenario_names = { SCENARIO1, ..., SCENARIO10 };            // ORIGINAL (N=10)
   // ===== SCALE-UP BEGIN (N=10 -> 20): comment out this block to revert =====
   for (auto s : { SCENARIO11, ..., SCENARIO20 }) this->scenario_names.push_back(s);
   // ===== SCALE-UP END =====
   ```
   Do not rewrite the original initializer to contain all 20 names.
2. Put the new entries of **every** per-scenario table found in Step 0 in the same marked
   SCALE-UP block (e.g. `perturb[SCENARIO11] = ...;` statements or `insert`s after the original
   map initializer), not spliced into the original initializer lists. For position-indexed arrays
   (e.g. CHP's `CHP_SCENARIO_DATA[s]`), keep the original array and add a separate array/appended
   rows in the block, so the original data stays byte-for-byte unchanged.
3. Make `probability` depend on the count so it reverts automatically, e.g.
   `this->probability = 1.0 / this->scenario_names.size();` placed after the block, with the
   original literal kept in a comment. If the model has per-scenario probabilities, do the same.
   If the block is commented out, every table and the probability must again describe exactly the
   original problem — check this explicitly.
4. If a single switch is cleaner (e.g. one `constexpr int N_SCENARIOS` or a `#define SCALE_UP`),
   you may use it, but it must still default to the scaled-up state and revert to the exact
   original with one edit.
5. Any per-scenario tables in `clone()`/serialization must be covered by the same mechanism.

Tell the user in the report exactly which lines to comment out to scale back down.

**Picking parameter values for the new scenarios:** don't interpolate the existing range — a
scenario whose parameters sit between two existing scenarios will usually just have a recourse
solution that's a blend of theirs, which tells you nothing new about how the algorithm scales.
Instead pick values outside the existing envelope, and where the model has two or more
correlated parameters, cross-pair them against the existing pattern (e.g. if existing scenarios
pair high-perturb with high-price, give some new scenarios high-perturb with low-price) so the
new scenarios' optimal decisions are qualitatively different rather than an extension of the
same trend.

**Feasibility guard rails** — these are model-specific, so look for them:
- Read comments near the scenario data in the constructor; some record magnitude limits (e.g.
  ProcessModel documents `|perturb|` ≥ ~18 as breaking full-model feasibility: it forces the
  shared first-stage variable to satisfy every scenario at once, which is only reachable at
  extreme throughput and can make the recourse net-positive-cost so the relative gap becomes
  ill-defined).
- If no limit is documented, extend the envelope moderately (roughly 1.5× the existing range,
  not 10×) and rely on the UBD sanity check in Step 2 to catch infeasibility.
- Keep values physically sensible for the model (non-negative prices/demands/capacities where
  the existing ones are non-negative, etc.).

**Worked example** (ProcessModel, 10→20 scenarios, validated end-to-end): existing `perturb` in
[-2.7, 2.7] and `price` in [0.02, 0.26]; the 10 new scenarios used `perturb` up to ±4.5 and
`price` both below (~0.005-0.015) and above (~0.32-0.40) the existing range, crossed against
perturb sign in both directions.

## Step 2 — Recompute the initial UBD (phase A build/run)

`test.cpp`'s `main()` has two blocks side by side, toggled by comments — never delete either,
just swap which one is active:

- The **solve block**: `outsideAlgo CZalgo(&model, <UBD literal>, UBDSolver::GUROBI);
  CZalgo.bestUBDforInfinity=true; CZalgo.solve(<n>);`
- The **UBD-computation block** (marked between `// *************uncooment this part...` and
  `// ***********************`):
  `insideAlgo CZalgo(&model,ScenarioNames::SCENARIO1,INFINITY,true,UBDSolver::GUROBI);
  std::cout << "UBD is: "<<CZalgo.calculateUBD(&(CZalgo.activeNodes[0]), 1)<<std::endl;`

Keep whatever `solve(<n>)` argument and model constructor arguments (e.g. branching strategy)
are already in `test.cpp`; only change what this workflow needs. Make sure `test.cpp` includes
the header and instantiates the model you're scaling.

To get a UBD valid for the new scenario count:

1. Comment out the solve block, uncomment the UBD-computation block.
2. Rebuild from the repo root: `cmake --build build -j 4` (the `build/` directory is already
   configured with CPLEX/Gurobi/IPOPT paths in `build/CMakeCache.txt` — don't reconfigure from
   scratch). Note the executable name (`EXECUTABLE_NAME` in `CMakeLists.txt`; `./build/process`
   has been used so far) — all models share the one executable, selected by what `test.cpp`
   instantiates.
3. Run the binary and capture stdout. It should print a single finite line,
   `UBD is: <value>`. If it prints `inf` or doesn't terminate quickly, the new scenario set is
   likely infeasible as a combined extensive-form problem — go back to Step 1 and narrow the
   new parameter values (this is the fast way to sanity-check feasibility before committing to
   the long B&B solve in Step 3).

Never fabricate this value — it must come from actually running the compiled binary.

## Step 3 — Solve with the new UBD (phase B build/run)

1. In `test.cpp`, replace the old UBD literal in the solve block's `outsideAlgo CZalgo(&model,
   <old value>, UBDSolver::GUROBI);` line with the value printed in Step 2. Also update the
   "known objective" comment list at the top of `main()` if the user wants (it records the
   optimum per model and scenario count, e.g. `ProcessMode: -1060.14(10s) -4422.39(20s)`).
2. Swap the comment state back: uncomment the solve block, re-comment the UBD-computation block.
3. Rebuild (`cmake --build build -j 4`) and run the binary.

This is the real solve and can take a while — it prints one line per B&B iteration
(`Current UBD: ..., LBD: ..., Gap: ... Total Wall Time: ... seconds`) until it converges to the
tolerance set by `CZalgo.solve(<n>)`, ending with `Best Solution: <value>`. Run it with a
generous timeout or in the background rather than assuming it finishes quickly — warn the user
up front if you're about to kick off a long run. Never fabricate the final objective, iteration
count, or wall time; they must come from the actual run output.

## Step 4 — Report

Tell the user: model name, old → new scenario count, the new `Best Solution` objective, how
many iterations it took, and the wall time, compared against the previous scenario count's run
(if known — the comment list at the top of `test.cpp` often has it), so they can judge how the
algorithm scales with problem size. Mention any model-specific tables you extended and the
parameter ranges you chose.

## Notes

- **Scaling down:** when asked to scale back down, just comment out the SCALE-UP block (and
  restore the original UBD literal in `test.cpp`, which is recorded in the top-of-`main()` comment
  list — keep both the old and new UBD there, e.g. `Ex844: 583.156(10s) 748.34(20s)`). Don't
  touch the original data.
- When the user hands over a model that was scaled up *before* this rule existed (original data
  merged into the initializer), first refactor it into original + SCALE-UP block form, using git
  history of the submodule to recover the original values, and verify the reverted model
  reproduces the recorded original objective.

- Edits happen in two places: `Crappy_Fuzzy_Problem_Library/<Model>.cpp` (a git submodule) and
  `test.cpp` (repo root). No commits are needed as part of this workflow — just edit, build,
  run, report.
- If a run's UBD or objective looks off relative to a previous run, re-check the parameter
  values chosen in Step 1 before assuming an algorithm bug.
- For a model you haven't scaled before, do a quick sanity check that the *unchanged* model
  still reproduces the objective recorded in `test.cpp`'s comment list before adding scenarios,
  if time allows — it separates "my edit broke something" from "the build is stale".
