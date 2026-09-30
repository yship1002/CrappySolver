# CrappySolver

Research code (Jingzhi Yang): a decomposition-based global solver for **two-stage stochastic (non-convex) MINLP/NLP** problems.

## Algorithm

- The problem is decomposed into **scenario subproblems**; each is solved **globally** by its own spatial branch-and-bound.
- Two nested B&B layers:
  - **Outer** (`outsideAlgo`, nodes = `BBNode`): branches on the **first-stage** variable box. Its lower bound (LBD) is the sum of the scenario LBDs computed by the inner solver on that box (`scenario_LBDs`).
  - **Inner** (`insideAlgo`, nodes = `xBBNode`): per-scenario global B&B over first- and second-stage variables of that scenario.
- **Lower bounds**: polyhedral (convex/concave) relaxations built with **MC++ (`mcpp/`)** (`mc::Interval`, `ffunc`, `polimage`), solved as LPs with CPLEX or Gurobi.
- **Upper bounds**: local solves of the original problem with **Ipopt** or **Gurobi** (`UBDSolver`).
- **Branching**: **reliability branching** in the inner solver (`insideAlgo::reliabilityBranching`, `reliability_eta`, `probe_all`, `reliabilityProbe`). Variables with unreliable pseudocosts (fewer than `reliability_eta` samples, or pseudocost == 0) are strong-branch probed. Probed variables are ranked by their fresh probe score. `BranchingStrategy` (e.g. `pseudo`) is set on the model.
- Other inner-solver features: OBBT (`OBBT`, `getOBBTbounds_lower/upper`), weird strong branching, and pseudocost/strong-branching history in `BBHeuristic`.
- The outer layer takes a `provided_UBD` (known best objective) and a tolerance; see `test.cpp`.

## Layout

- `src/Algo.h`, `src/Algo.tpp`: `Algo<T>` base template, `outsideAlgo`, `insideAlgo`. Most of the logic lives in `Algo.tpp` (~1500 lines).
- `src/BBNode.*`: node types (`Node` → `BBNode`, `xBBNode`). Box bounds are `mc::Interval` vectors (`first_stage_IX`, `second_stage_IX`).
- `src/BBHeuristic.*`: branching heuristics (pseudocost, etc.).
- `Crappy_Fuzzy_Problem_Library/`: test problems, each subclassing `STModel` (`ProcessModel`, `Ex844`, `Ex722`, `CrudeModel`, `CHPModel`, `EDUnits`, `EDUnits_nocp`, `NFUnit`, `TTT`). Scenarios are listed in `ScenarioNames` and `perturb_coeffs`.
- `test.cpp`: driver. It instantiates one model and runs `outsideAlgo::solve(tol)`. Known optimal objectives are recorded as comments at the top of `main()`.
- `mcpp/`, `cereal/`, `eigen/`: vendored third-party libraries. Do not edit them.
- `analysis.ipynb`, `visual.ipynb`: post-processing of the JSON records serialized with cereal.

## Build

CMake (C++17, `-w -g`, no optimization). You must supply `CPLEX_ROOT_DIR`, `GUROBI_ROOT_DIR` and `IPOPT_ROOT_DIR`, plus `IS_ARM64_OSX` (macOS arm64 links `gurobi130`, Linux links `gurobi120`). Build output is in `build/`. Sources are globbed from `src/*.cpp` and `Crappy_Fuzzy_Problem_Library/*.cpp`, so rerun cmake after adding files.

## Conventions and notes

- "Scaling up scenarios" must stay reversible: keep the original scenarios and put new ones in a marked block (see the `scale-scenarios` skill).
- When a model changes, its reference UBD in `test.cpp` (`provided_UBD`) must be recomputed (see the commented-out block in `main()`).
- Tolerances are passed in absolute terms to `solve(tol)`.
- Prefer fixing the algorithm's logic over loosening tolerances. Report LBD/UBD, iteration count and wall time when comparing changes.
