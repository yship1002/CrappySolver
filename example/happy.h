// #include "example/STModel.h"
// class HappyModel:public STModel {
//     public:
//         HappyModel(BranchingStrategy branching_strategy);
//         HappyModel(const HappyModel& other)=default;
//         HappyModel()=default;
//         double probability;
//         Ipopt::SmartPtr<STModel> clone() override;
//         void buildDAG() override;
//         void buildFullModelDAG() override;
//         template<class Archive>
//         void serialize(Archive& ar) {
//             CEREAL_NVP(first_stage_IX), CEREAL_NVP(second_stage_IX);
//         }
// };

// Constraint	What differs
// g_1_1 / g_2_1	Perturb coeff on CrudeQuantity[2]: 0.002033... → 0.001978... (all 10 crude sulfur yields differ)
// g_1_2 / g_2_2	All 10 CrudeQuantity LG-yield coefficients differ
// g_1_3	Placeholder — Pyomo output was truncated; uses old SCENARIO1 LN-yield values
// g_1_4	Placeholder — heavy naphtha yield per crude; values unknown for SCENARIO2
// g_1_5	Placeholder — AGO production yield; values unknown for SCENARIO2
// g_1_6	Placeholder — cracker feed yield; values unknown for SCENARIO2
// g_1_7, g_1_8, g_1_9	Placeholders — crude 1–3 atmospheric fraction; Pyomo was truncated before these
// g_1_10 → g_1_16	All 7 crude 4–10 atmospheric fractions differ (e.g. crude 4: 0.25224 → 0.25716)
// g_1_17 → g_1_26	All 10 HF_1 yield coefficients differ (e.g. crude 1: 0.09848 → 0.11791)
// g_1_74	CDU LG balance — uses same coefficients as g_1_2, so also differs
// g_1_107	AGO cetane/sulphur quality — all flow_AGO_1[i] and flow_AGO_2[i] coefficients differ
// objective	All 10 flow_Desulphurisation_1[i] cost coefficients differ