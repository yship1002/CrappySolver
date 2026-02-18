#include "example/CrudeModel.h"
CrudeModel::CrudeModel(BranchingStrategy branching_strategy):STModel() {

    this->branching_strategy = branching_strategy;
    this->scenario_names = {ScenarioNames::SCENARIO1, ScenarioNames::SCENARIO2, ScenarioNames::SCENARIO3,ScenarioNames::SCENARIO4, ScenarioNames::SCENARIO5};
    this->scenario_name = ScenarioNames::SCENARIO1; //default
    std::vector<double> scenario_1_params = {
        // --- g_1_1 Coefficients (Burn/Waste Yields) [Indices 0-9] ---
        0.0020105335707024776,  // Crude 1
        0.002033729784573578,   // Crude 2
        0.002110066788923241,   // Crude 3
        0.003973905045918246,   // Crude 4
        0.0019988517589712403,  // Crude 5
        0.0008904820763900271,  // Crude 6
        0.001991196321110873,   // Crude 7
        0.0028411758274924682,  // Crude 8
        0.004057963205263551,   // Crude 9
        0.00427501144267499,    // Crude 10

        // --- g_1_2 Coefficients (Light Gas Yields) [Indices 10-19] ---
        0.009147927746696273,   // Crude 1
        0.009050097541352423,   // Crude 2
        0.008440267155692963,   // Crude 3
        0.019869525229591227,   // Crude 4
        0.011493397614084631,   // Crude 5
        0.005699085288896173,   // Crude 6
        0.015431771488609266,   // Crude 7
        0.012736305433586925,   // Crude 8
        0.01592750558065944,    // Crude 9
        0.011435655609155597,   // Crude 10

        // --- g_1_3 Coefficients (Intermediate Yields A) [Indices 20-29] ---
        0.07016762161751647,    // Crude 1
        0.04880951482976587,    // Crude 2
        0.06435703706215884,    // Crude 3
        0.08454482985191068,    // Crude 4
        0.05426882525606917,    // Crude 5
        0.021905859079194668,   // Crude 6
        0.09408402617248875,    // Crude 7
        0.06387747032845136,    // Crude 8
        0.07598536101855999,    // Crude 9
        0.06455267278439235,    // Crude 10

        // --- g_1_4 Coefficients (Reformer Feed Yields) [Indices 30-39] ---
        0.16064163229912795,    // Crude 1
        0.09751734317030307,    // Crude 2
        0.1272370273720714,     // Crude 3
        0.15220056325866882,    // Crude 4
        0.10254109523522463,    // Crude 5
        0.054052262036874646,   // Crude 6
        0.165368854468258,      // Crude 7
        0.11717400998899972,    // Crude 8
        0.12853598452672302,    // Crude 9
        0.12002094625310035,    // Crude 10

        // --- g_1_5 Coefficients (JPF Yields) [Indices 40-49] ---
        0.10082825857072926,    // Crude 1
        0.08094244542602841,    // Crude 2
        0.0908383752631455,     // Crude 3
        0.09408220196211448,    // Crude 4
        0.07645607978064994,    // Crude 5
        0.0461269715570034,     // Crude 6
        0.11548938662443065,    // Crude 7
        0.08210018425650649,    // Crude 8
        0.09282590832040374,    // Crude 9
        0.0837902242764298,     // Crude 10

        // --- g_1_6 Coefficients (Cracker Feed Yields) [Indices 50-59] ---
        0.2696125518312022,     // Crude 1
        0.27811254804043684,    // Crude 2
        0.27916183617454476,    // Crude 3
        0.25184623228506886,    // Crude 4
        0.2693452745213747,     // Crude 5
        0.26108934479755597,    // Crude 6
        0.2306800938006946,     // Crude 7
        0.23591556526213323,    // Crude 8
        0.2546371911302879,     // Crude 9
        0.266226337592585,      // Crude 10

        // --- g_1_7 to g_1_16 Coefficients (AGO Yields) [Indices 60-69] ---
        0.28911472746701633,    // Crude 1
        0.22869291427529884,    // Crude 2
        0.25468506142303515,    // Crude 3
        0.25224362278966067,    // Crude 4
        0.22846875605041275,    // Crude 5
        0.16919159451410512,    // Crude 6
        0.26443087144352395,    // Crude 7
        0.20838555120953378,    // Crude 8
        0.2387096855496284,     // Crude 9
        0.223583098451902,      // Crude 10

        // --- g_1_17 to g_1_26 Coefficients (Heavy Fuel Yields) [Indices 70-79] ---
        0.098476746897009,      // Crude 1
        0.254841406932241,      // Crude 2
        0.173170328760428,      // Crude 3
        0.141239119577067,      // Crude 4
        0.255427719783213,      // Crude 5
        0.44104440064998,       // Crude 6
        0.112523799680884,      // Crude 7
        0.276969737693296,      // Crude 8
        0.189320400668474,      // Crude 9
        0.22611605358976        // Crude 10
    };
    std::vector<double> scenario_2_params = {
        // --- g_1_1 Coefficients (Burn/Waste Yields) [Indices 0-9] ---
        0.00196718459212556,    // Crude 1
        0.0019780917512787033,  // Crude 2
        0.001948311531034133,   // Crude 3
        0.0040513823031822814,  // Crude 4
        0.002003681936860048,   // Crude 5
        0.0009320096990179594,  // Crude 6
        0.00202756729630744,    // Crude 7
        0.0027912050487304647,  // Crude 8
        0.0039794012455976625,  // Crude 9
        0.004065682907216727,   // Crude 10

        // --- g_1_2 Coefficients (Light Gas Yields) [Indices 10-19] ---
        // (Also used in g_1_74)
        0.008950689894171297,   // Crude 1
        0.008802508293190231,   // Crude 2
        0.007793246124136532,   // Crude 3
        0.020256911515911406,   // Crude 4
        0.011521171136945278,   // Crude 5
        0.00596486207371494,    // Crude 6
        0.015713646546382663,   // Crude 7
        0.012512298494308977,   // Crude 8
        0.015619149888970823,   // Crude 9
        0.010875701776804744,   // Crude 10

        // --- g_1_3 Coefficients (Intermediate Yields A) [Indices 20-29] ---
        0.06865474226518203,    // Crude 1
        0.04747420203068888,    // Crude 2
        0.059423501696541044,   // Crude 3
        0.08619315850020302,    // Crude 4
        0.05439996458575031,    // Crude 5
        0.022927438595841804,   // Crude 6
        0.09580255475052654,    // Crude 7
        0.06275398937145733,    // Crude 8
        0.07451428832381622,    // Crude 9
        0.06139181189897258,    // Crude 10

        // --- g_1_4 Coefficients (Reformer Feed Yields) [Indices 30-39] ---
        0.1571780489108322,     // Crude 1
        0.09484949947381384,    // Crude 2
        0.11748318532135821,    // Crude 3
        0.15516794221188138,    // Crude 4
        0.10278888336092049,    // Crude 5
        0.056572988730390135,   // Crude 6
        0.1683894639583329,     // Crude 7
        0.1151131461476426,     // Crude 8
        0.12604753445430597,    // Crude 9
        0.11414404762010961,    // Crude 10

        // --- g_1_5 Coefficients (JPF Yields) [Indices 40-49] ---
        0.09865430729509682,    // Crude 1
        0.0787280517008924,     // Crude 2
        0.0838748114110194,     // Crude 3
        0.09591647602784051,    // Crude 4
        0.07664083408489684,    // Crude 5
        0.048278102409130295,   // Crude 6
        0.11759890318583154,    // Crude 7
        0.0806562010633148,     // Crude 8
        0.09102880349304653,    // Crude 9
        0.07968738498144785,    // Crude 10

        // --- g_1_6 Coefficients (Cracker Feed Yields) [Indices 50-59] ---
        0.2637994538040375,     // Crude 1
        0.27050404698736275,    // Crude 2
        0.2577616155558158,     // Crude 3
        0.2567563534641771,     // Crude 4
        0.26999614099189156,    // Crude 5
        0.27326524375206573,    // Crude 6
        0.23489367127721691,    // Crude 7
        0.23176626749458476,    // Crude 8
        0.24970742816125333,    // Crude 9
        0.2531904030469217,     // Crude 10

        // --- g_1_7 to g_1_16 Coefficients (AGO Yields) [Indices 60-69] ---
        0.28288114434765554,    // Crude 1
        0.2224364174312902,     // Crude 2
        0.2351612017958198,     // Crude 3
        0.2571614916944953,     // Crude 4
        0.22902084538310352,    // Crude 5
        0.17708184281341227,    // Crude 6
        0.26926093694962805,    // Crude 7
        0.20472045305688613,    // Crude 8
        0.23408827827228249,    // Crude 9
        0.21263521604743485,    // Crude 10

        // --- g_1_17 to g_1_26 Coefficients (Heavy Fuel Yields) [Indices 70-79] ---
        0.117914428890899,      // Crude 1
        0.275227182331483,      // Crude 2
        0.236554126564275,      // Crude 3
        0.124496284282309,      // Crude 4
        0.253628478519632,      // Crude 5
        0.414977511926427,      // Crude 6
        0.096313256035774,      // Crude 7
        0.289686439323075,      // Crude 8
        0.205015116160727,      // Crude 9
        0.264009751721092       // Crude 10
    };

    this->first_stage_map = {
        {"CrudeQuantity[1]",0},
        {"CrudeQuantity[2]",1},
        {"CrudeQuantity[3]",2},
        {"CrudeQuantity[4]",3},
        {"CrudeQuantity[5]",4},
        {"CrudeQuantity[6]",5},
        {"CrudeQuantity[7]",6},
        {"CrudeQuantity[8]",7},
        {"CrudeQuantity[9]",8},
        {"CrudeQuantity[10]",9},
        {"pickCrude[1]",10},
        {"pickCrude[2]",11},
        {"pickCrude[3]",12},
        {"pickCrude[4]",13},
        {"pickCrude[5]",14},
        {"pickCrude[6]",15},
        {"pickCrude[7]",16},
        {"pickCrude[8]",17},
        {"pickCrude[9]",18},
        {"pickCrude[10]",19}

    };
    this->second_stage_map={
        {"blin_AGO_LG[1]",0},
        {"blin_AGO_LG[2]",1},
        {"blin_AGO_LG[3]",2},
        {"blin_AGO_LG[4]",3},
        {"blin_CDU_LG[1]",4},
        {"blin_CDU_LG[2]",5},
        {"blin_CDU_LG[3]",6},
        {"blin_CDU_LG[4]",7},
        {"blin_Cracker_AGO[1]",8},
        {"blin_Cracker_AGO[2]",9},
        {"blin_Cracker_AGO[3]",10},
        {"blin_Cracker_Mogas[1]",11},
        {"blin_Cracker_Mogas[2]",12},
        {"blin_Cracker_Mogas[3]",13},
        {"blin_Mogas_LG[1]",14},
        {"blin_Mogas_LG[2]",15},
        {"blin_Mogas_LG[3]",16},
        {"blin_Mogas_LG[4]",17},
        {"blin_Reformer100_LG[1]",18},
        {"blin_Reformer100_LG[2]",19},
        {"blin_Reformer100_LG[3]",20},
        {"blin_Reformer100_LG[4]",21},
        {"blin_Reformer95_LG[1]",22},
        {"blin_Reformer95_LG[2]",23},
        {"blin_Reformer95_LG[3]",24},
        {"blin_Reformer95_LG[4]",25},
        {"flow_AGO_1[1]",26},
        {"flow_AGO_1[2]",27},
        {"flow_AGO_1[3]",28},
        {"flow_AGO_1[4]",29},
        {"flow_AGO_1[5]",30},
        {"flow_AGO_1[6]",31},
        {"flow_AGO_1[7]",32},
        {"flow_AGO_1[8]",33},
        {"flow_AGO_1[9]",34},
        {"flow_AGO_1[10]",35},
        {"flow_AGO_2[1]",36},
        {"flow_AGO_2[2]",37},
        {"flow_AGO_2[3]",38},
        {"flow_AGO_2[4]",39},
        {"flow_AGO_2[5]",40},
        {"flow_AGO_2[6]",41},
        {"flow_AGO_2[7]",42},
        {"flow_AGO_2[8]",43},
        {"flow_AGO_2[9]",44},
        {"flow_AGO_2[10]",45},
        {"flow_AGO_3[1]",46},
        {"flow_AGO_3[2]",47},
        {"flow_AGO_3[3]",48},
        {"flow_Burn[1]",49},
        {"flow_Burn[2]",50},
        {"flow_Burn[3]",51},
        {"flow_Cracker_AGO",52},
        {"flow_Cracker_Mogas",53},
        {"flow_Desulphurisation_1[1]",54},
        {"flow_Desulphurisation_1[2]",55},
        {"flow_Desulphurisation_1[3]",56},
        {"flow_Desulphurisation_1[4]",57},
        {"flow_Desulphurisation_1[5]",58},
        {"flow_Desulphurisation_1[6]",59},
        {"flow_Desulphurisation_1[7]",60},
        {"flow_Desulphurisation_1[8]",61},
        {"flow_Desulphurisation_1[9]",62},
        {"flow_Desulphurisation_1[10]",63},
        {"flow_Desulphurisation_CGO",64},
        {"flow_ES95[1]",65},
        {"flow_ES95[2]",66},
        {"flow_ES95[3]",67},
        {"flow_ES95[4]",68},
        {"flow_ES95[5]",69},
        {"flow_ES95[6]",70},
        {"flow_HF_1[1]",71},
        {"flow_HF_1[2]",72},
        {"flow_HF_1[3]",73},
        {"flow_HF_1[4]",74},
        {"flow_HF_1[5]",75},
        {"flow_HF_1[6]",76},
        {"flow_HF_1[7]",77},
        {"flow_HF_1[8]",78},
        {"flow_HF_1[9]",79},
        {"flow_HF_1[10]",80},
        {"flow_HF_2",81},
        {"flow_HF_3[1]",82},
        {"flow_HF_3[2]",83},
        {"flow_HF_3[3]",84},
        {"flow_HF_3[4]",85},
        {"flow_HF_3[5]",86},
        {"flow_HF_3[6]",87},
        {"flow_HF_3[7]",88},
        {"flow_HF_3[8]",89},
        {"flow_HF_3[9]",90},
        {"flow_HF_3[10]",91},
        {"flow_Import[1]",92},
        {"flow_Import[2]",93},
        {"flow_Import[3]",94},
        {"flow_Import[4]",95},
        {"flow_Import[5]",96},
        {"flow_Import[6]",97},
        {"flow_Import[7]",98},
        {"flow_Isomerisation",99},
        {"flow_JPF[1]",100},
        {"flow_JPF[2]",101},
        {"flow_LG_producing",102},
        {"flow_LN_producing",103},
        {"flow_PG98[1]",104},
        {"flow_PG98[2]",105},
        {"flow_PG98[3]",106},
        {"flow_PG98[4]",107},
        {"flow_PG98[5]",108},
        {"flow_PG98[6]",109},
        {"flow_Reformer100",110},
        {"flow_Reformer95",111},
        {"fraction_CGO[1]",112},
        {"fraction_CGO[2]",113},
        {"fraction_LG[1]",114},
        {"fraction_LG[2]",115},
        {"fraction_LG[3]",116},
        {"fraction_LG[4]",117},
        {"fraction_LG[5]",118},
        {"volume_ES95",119},
        {"volume_HF",120},
        {"volume_PG98",121}
    };

    this->first_stage_IX = {
        mc::Interval(0.0, 201.29570747217807),    // CrudeQuantity[1]
        mc::Interval(0.0, 212.48012718600953),  //CrudeQuantity[2]
        mc::Interval(0.0, 201.29570747217807),   //CrudeQuantity[3]
        mc::Interval(0.0, 199.57869634340224),   //CrudeQuantity[4]
        mc::Interval(0.0, 210.54848966613673),   //CrudeQuantity[5]
        mc::Interval(0.0, 222.1383147853736),    //CrudeQuantity[6]
        mc::Interval(0.0, 196.7885532591415),     //CrudeQuantity[7]
        mc::Interval(0.0, 208.54531001589828),   //CrudeQuantity[8]
        mc::Interval(0.0, 204.3720190779014),    //CrudeQuantity[9]
        mc::Interval(0.0, 210.2623211446741),    //CrudeQuantity[10]
        mc::Interval(0.0, 0.0),    //PickCrude[1]
        mc::Interval(1.0, 1.0),   //PickCrude[2]
        mc::Interval(1.0, 1.0),  //PickCrude[3]
        mc::Interval(1.0, 1.0),   //PickCrude[4]
        mc::Interval(0.0, 0.0),   //PickCrude[5]
        mc::Interval(0.0, 0.0),   //PickCrude[6]
        mc::Interval(0.0, 0.0),   //PickCrude[7]
        mc::Interval(1.0, 1.0),   //PickCrude[8]
        mc::Interval(0.0, 0.0),   //PickCrude[9]
        mc::Interval(1.0, 1.0)    //PickCrude[10]
    }; 

    // this->first_stage_IX = {
    //     mc::Interval(0.0, 0),
    //     mc::Interval(212.4801280860051, 212.48012718600953),
    //     mc::Interval(169.2074211392293,169.2074211392293),
    //     mc::Interval(13.3052462898513,13.3052462898513),
    //     mc::Interval(0.0, 0),
    //     mc::Interval(0.0, 0),
    //     mc::Interval(0.0, 0),
    //     mc::Interval(197.03623279726904, 197.03623279726904),
    //     mc::Interval(0.0, 0),
    //     mc::Interval(31.948424989867178, 31.948424989867178),
    //     mc::Interval(0.0, 0.0),
    //     mc::Interval(1.0, 1.0),
    //     mc::Interval(1.0, 1.0),
    //     mc::Interval(1.0, 1.0),
    //     mc::Interval(0.0, 0.0),
    //     mc::Interval(0.0, 0.0),
    //     mc::Interval(0.0, 0.0),
    //     mc::Interval(1.0, 1.0),
    //     mc::Interval(0.0, 0.0),
    //     mc::Interval(1.0, 1.0)
    // };

    // this->second_stage_IX = {
    //     mc::Interval(0.0, 0.0),                                         // 0: blin_AGO_LG[1]
    //     mc::Interval(0.0, 0.0),                                         // 1: blin_AGO_LG[2]
    //     mc::Interval(0.0, 0.0),                                         // 2: blin_AGO_LG[3]
    //     mc::Interval(0.0, 0.0),                                         // 3: blin_AGO_LG[4]
    //     mc::Interval(1.4827728451272297, 1.4827728451272297),           // 4: blin_CDU_LG[1]
    //     mc::Interval(0.0528236602701349, 0.0528236602701349),           // 5: blin_CDU_LG[2]
    //     mc::Interval(3.7135429027408575, 3.7135429027408575),           // 6: blin_CDU_LG[3]
    //     mc::Interval(1.241215724891861, 1.241215724891861),             // 7: blin_CDU_LG[4]
    //     mc::Interval(0.0, 0.0),                                         // 8: blin_Cracker_AGO[1]
    //     mc::Interval(0.0, 0.0),                                         // 9: blin_Cracker_AGO[2]
    //     mc::Interval(0.0, 0.0),                                         // 10: blin_Cracker_AGO[3]
    //     mc::Interval(0.0, 0.0),                                         // 11: blin_Cracker_Mogas[1]
    //     mc::Interval(73.44279546893651, 73.44279546893651),             // 12: blin_Cracker_Mogas[2]
    //     mc::Interval(0.0, 0.0),                                         // 13: blin_Cracker_Mogas[3]
    //     mc::Interval(1.9938678617520469, 1.9938678617520469),           // 14: blin_Mogas_LG[1]
    //     mc::Interval(0.07103137806903466, 0.07103137806903466),         // 15: blin_Mogas_LG[2]
    //     mc::Interval(4.993559108763604, 4.993559108763604),             // 16: blin_Mogas_LG[3]
    //     mc::Interval(1.6690487362889348, 1.6690487362889348),           // 17: blin_Mogas_LG[4]
    //     mc::Interval(1.644896814749778, 1.644896814749778),             // 18: blin_Reformer100_LG[1]
    //     mc::Interval(0.058599313311751645, 0.058599313311751645),       // 19: blin_Reformer100_LG[2]
    //     mc::Interval(4.119575639808097, 4.119575639808097),             // 20: blin_Reformer100_LG[3]
    //     mc::Interval(1.3769282321303722, 1.3769282321303722),           // 21: blin_Reformer100_LG[4]
    //     mc::Interval(0.10280605092186111, 0.10280605092186111),         // 22: blin_Reformer95_LG[1]
    //     mc::Interval(0.003662457081984535, 0.003662457081984535),       // 23: blin_Reformer95_LG[2]
    //     mc::Interval(0.25747347748800603, 0.25747347748800603),         // 24: blin_Reformer95_LG[3]
    //     mc::Interval(0.08605801450814865, 0.08605801450814865),         // 25: blin_Reformer95_LG[4]
    //     mc::Interval(0.0, 0.0),                                         // 26: flow_AGO_1[1]
    //     mc::Interval(0.0, 0.0),                                         // 27: flow_AGO_1[2]
    //     mc::Interval(0.0, 0.0),                                         // 28: flow_AGO_1[3]
    //     mc::Interval(0.0, 0.0),                                         // 29: flow_AGO_1[4]
    //     mc::Interval(0.0, 0.0),                                         // 30: flow_AGO_1[5]
    //     mc::Interval(0.0, 0.0),                                         // 31: flow_AGO_1[6]
    //     mc::Interval(0.0, 0.0),                                         // 32: flow_AGO_1[7]
    //     mc::Interval(0.0, 0.0),                                         // 33: flow_AGO_1[8]
    //     mc::Interval(0.0, 0.0),                                         // 34: flow_AGO_1[9]
    //     mc::Interval(0.0, 0.0),                                         // 35: flow_AGO_1[10]
    //     mc::Interval(0.0, 0.0),                                         // 36: flow_AGO_2[1]
    //     mc::Interval(47.62084552151957, 47.62084552151957),             // 37: flow_AGO_2[2]
    //     mc::Interval(42.23272914485028, 42.23272914485028),             // 38: flow_AGO_2[3]
    //     mc::Interval(3.2890402886234287, 3.2890402886234287),           // 39: flow_AGO_2[4]
    //     mc::Interval(0.0, 0.0),                                         // 40: flow_AGO_2[5]
    //     mc::Interval(0.0, 0.0),                                         // 41: flow_AGO_2[6]
    //     mc::Interval(0.0, 0.0),                                         // 42: flow_AGO_2[7]
    //     mc::Interval(0.0, 0.0),                                         // 43: flow_AGO_2[8]
    //     mc::Interval(0.0, 0.0),                                         // 44: flow_AGO_2[9]
    //     mc::Interval(6.857385045006712, 6.857385045006712),             // 45: flow_AGO_2[10]
    //     mc::Interval(0.0, 0.0),                                         // 46: flow_AGO_3[1]
    //     mc::Interval(0.0, 0.0),                                         // 47: flow_AGO_3[2]
    //     mc::Interval(0.0, 0.0),                                         // 48: flow_AGO_3[3]
    //     mc::Interval(12.342073340140763, 12.342073340140763),           // 49: flow_Burn[1]
    //     mc::Interval(13.084151128800565, 13.084151128800565),           // 50: flow_Burn[2]
    //     mc::Interval(0.0, 0.0),                                         // 51: flow_Burn[3]
    //     mc::Interval(0.0, 0.0),                                         // 52: flow_Cracker_AGO
    //     mc::Interval(164.6699449976155, 164.6699449976155),             // 53: flow_Cracker_Mogas
    //     mc::Interval(0.0, 0.0),                                         // 54: flow_Desulphurisation_1[1]
    //     mc::Interval(48.59269951175467, 48.59269951175467),             // 55: flow_Desulphurisation_1[2]
    //     mc::Interval(43.09462157637783, 43.09462157637783),             // 56: flow_Desulphurisation_1[3]
    //     mc::Interval(3.3561635598198256, 3.3561635598198256),           // 57: flow_Desulphurisation_1[4]
    //     mc::Interval(0.0, 0.0),                                         // 58: flow_Desulphurisation_1[5]
    //     mc::Interval(0.0, 0.0),                                         // 59: flow_Desulphurisation_1[6]
    //     mc::Interval(0.0, 0.0),                                         // 60: flow_Desulphurisation_1[7]
    //     mc::Interval(0.0, 0.0),                                         // 61: flow_Desulphurisation_1[8]
    //     mc::Interval(0.0, 0.0),                                         // 62: flow_Desulphurisation_1[9]
    //     mc::Interval(7.1431094218819915, 7.1431094218819915),           // 63: flow_Desulphurisation_1[10]
    //     mc::Interval(0.0, 0.0),                                         // 64: flow_Desulphurisation_CGO
    //     mc::Interval(5.224343572550916, 5.224343572550916),             // 65: flow_ES95[1]
    //     mc::Interval(11.21953484637532, 11.21953484637532),             // 66: flow_ES95[2]
    //     mc::Interval(0.0, 0.0),                                         // 67: flow_ES95[3]
    //     mc::Interval(2.5160404488473724, 2.5160404488473724),           // 68: flow_ES95[4]
    //     mc::Interval(44.220076359885546, 44.220076359885546),           // 69: flow_ES95[5]
    //     mc::Interval(71.79609601896037, 71.79609601896037),             // 70: flow_ES95[6]
    //     mc::Interval(0.0, 0.0),                                         // 71: flow_HF_1[1]
    //     mc::Interval(54.148734557224174, 54.148734557224174),           // 72: flow_HF_1[2]
    //     mc::Interval(29.301717754823187, 29.301717754823187),           // 73: flow_HF_1[3]
    //     mc::Interval(1.8792212905253955, 1.8792212905253955),           // 74: flow_HF_1[4]
    //     mc::Interval(0.0, 0.0),                                         // 75: flow_HF_1[5]
    //     mc::Interval(0.0, 0.0),                                         // 76: flow_HF_1[6]
    //     mc::Interval(0.0, 0.0),                                         // 77: flow_HF_1[7]
    //     mc::Interval(54.57307302905045, 54.57307302905045),             // 78: flow_HF_1[8]
    //     mc::Interval(0.0, 0.0),                                         // 79: flow_HF_1[9]
    //     mc::Interval(7.22403314033708, 7.22403314033708),               // 80: flow_HF_1[10]
    //     mc::Interval(73.44279546893651, 73.44279546893651),             // 81: flow_HF_2
    //     mc::Interval(0.0, 0.0),                                         // 82: flow_HF_3[1]
    //     mc::Interval(0.0, 0.0),                                         // 83: flow_HF_3[2]
    //     mc::Interval(0.0, 0.0),                                         // 84: flow_HF_3[3]
    //     mc::Interval(0.0, 0.0),                                         // 85: flow_HF_3[4]
    //     mc::Interval(0.0, 0.0),                                         // 86: flow_HF_3[5]
    //     mc::Interval(0.0, 0.0),                                         // 87: flow_HF_3[6]
    //     mc::Interval(0.0, 0.0),                                         // 88: flow_HF_3[7]
    //     mc::Interval(41.05950346441795, 41.05950346441795),             // 89: flow_HF_3[8]
    //     mc::Interval(0.0, 0.0),                                         // 90: flow_HF_3[9]
    //     mc::Interval(0.0, 0.0),                                         // 91: flow_HF_3[10]
    //     mc::Interval(0.0, 0.0),                                         // 92: flow_Import[1]
    //     mc::Interval(0.0, 0.0),                                         // 93: flow_Import[2]
    //     mc::Interval(0.0, 0.0),                                         // 94: flow_Import[3]
    //     mc::Interval(0.0, 0.0),                                         // 95: flow_Import[4]
    //     mc::Interval(0.0, 0.0),                                         // 96: flow_Import[5]
    //     mc::Interval(0.0, 0.0),                                         // 97: flow_Import[6]
    //     mc::Interval(0.0, 0.0),                                         // 98: flow_Import[7]
    //     mc::Interval(11.566530769459092, 11.566530769459092),           // 99: flow_Isomerisation
    //     mc::Interval(61.970178383363944, 61.970178383363944),           // 100: flow_JPF[1]
    //     mc::Interval(0.0, 0.0),                                         // 101: flow_JPF[2]
    //     mc::Interval(4.373250707819317, 4.373250707819317),             // 102: flow_LG_producing
    //     mc::Interval(22.369121992800203, 22.369121992800203),           // 103: flow_LN_producing
    //     mc::Interval(0.18611680873290667, 0.18611680873290667),         // 104: flow_PG98[1]
    //     mc::Interval(0.0, 0.0),                                         // 105: flow_PG98[2]
    //     mc::Interval(0.0, 0.0),                                         // 106: flow_PG98[3]
    //     mc::Interval(1.6339595511526313, 1.6339595511526313),           // 107: flow_PG98[4]
    //     mc::Interval(3.1799236401144624, 3.1799236401144624),           // 108: flow_PG98[5]
    //     mc::Interval(0.0, 0.0),                                         // 109: flow_PG98[6]
    //     mc::Interval(60.0, 60.0),                                       // 110: flow_Reformer100
    //     mc::Interval(5.0, 5.0),                                         // 111: flow_Reformer95
    //     mc::Interval(1.0, 1.0),                                         // 112: fraction_CGO[1]
    //     mc::Interval(0.0, 0.0),                                         // 113: fraction_CGO[2]
    //     mc::Interval(0.28381993345878453, 0.28381993345878453),         // 114: fraction_LG[1]
    //     mc::Interval(0.019678271441030723, 0.019678271441030723),       // 115: fraction_LG[2]
    //     mc::Interval(0.3148523430564916, 0.3148523430564916),           // 116: fraction_LG[3]
    //     mc::Interval(0.38164945204369305, 0.38164945204369305),         // 117: fraction_LG[4]
    //     mc::Interval(0.0, 0.0),                                         // 118: fraction_LG[5]
    //     mc::Interval(180.14977836382468, 180.14977836382468),           // 119: volume_ES95
    //     mc::Interval(277.9686088304845, 277.9686088304845),             // 120: volume_HF
    //     mc::Interval(6.417820990789885, 6.417820990789885)              // 121: volume_PG98
    // };

    this->second_stage_IX = {
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 201.29570747217807),
        mc::Interval(0.0, 212.48012718600953),
        mc::Interval(0.0, 201.29570747217807),
        mc::Interval(0.0, 199.57869634340224),
        mc::Interval(0.0, 210.54848966613673),
        mc::Interval(0.0, 222.1383147853736),
        mc::Interval(0.0, 196.7885532591415),
        mc::Interval(0.0, 208.54531001589828),
        mc::Interval(0.0, 204.3720190779014),
        mc::Interval(0.0, 210.2623211446741),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 125),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 201.29570747217807),
        mc::Interval(0.0, 212.48012718600953),
        mc::Interval(0.0, 201.29570747217807),
        mc::Interval(0.0, 199.57869634340224),
        mc::Interval(0.0, 210.54848966613673),
        mc::Interval(0.0, 222.1383147853736),
        mc::Interval(0.0, 196.7885532591415),
        mc::Interval(0.0, 208.54531001589828),
        mc::Interval(0.0, 204.3720190779014),
        mc::Interval(0.0, 210.2623211446741),
        mc::Interval(0.0, 175),
        mc::Interval(0.0, 201.29570747217807),
        mc::Interval(0.0, 212.48012718600953),
        mc::Interval(0.0, 201.29570747217807),
        mc::Interval(0.0, 199.57869634340224),
        mc::Interval(0.0, 210.54848966613673),
        mc::Interval(0.0, 222.1383147853736),
        mc::Interval(0.0, 196.7885532591415),
        mc::Interval(0.0, 208.54531001589828),
        mc::Interval(0.0, 204.3720190779014),
        mc::Interval(0.0, 210.2623211446741),
        mc::Interval(0.0, 0.0),
        mc::Interval(0.0, 0.0),
        mc::Interval(0.0, 0.0),
        mc::Interval(0.0, 0.0),
        mc::Interval(0.0, 0.0),
        mc::Interval(0.0, 0.0),
        mc::Interval(0.0, 0.0),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 700),
        mc::Interval(0.0, 60),
        mc::Interval(5.0, 65),
        mc::Interval(0.0, 1.0),
        mc::Interval(0.0, 1.0),
        mc::Interval(0.0, 1.0),
        mc::Interval(0.0, 1.0),
        mc::Interval(0.0, 1.0),
        mc::Interval(0.0, 1.0),
        mc::Interval(0.0, 1.0),
        mc::Interval(0.0,1206.896551724138),
        mc::Interval(0.0,832.9366968110423),
        mc::Interval(0.0,1206.896551724138)
    };
};

void CrudeModel::generateLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) {
    int n_first_stage_vars = this->first_stage_IX.size();

    // Loop over each scenario to build subproblem

    const int nvars = n_first_stage_vars + this->second_stage_IX.size();
    mc::FFGraph DAG;
    mc::FFVar X[nvars];


    for (int i = 0; i < nvars; ++i) X[i].set(&DAG);

    // scenario perturbation


    mc::FFVar g_0_0 = X[this->first_stage_map["CrudeQuantity[1]"]] + X[this->first_stage_map["CrudeQuantity[2]"]] + X[this->first_stage_map["CrudeQuantity[3]"]] + X[this->first_stage_map["CrudeQuantity[4]"]] + X[this->first_stage_map["CrudeQuantity[5]"]] + X[this->first_stage_map["CrudeQuantity[6]"]] + X[this->first_stage_map["CrudeQuantity[7]"]] + X[this->first_stage_map["CrudeQuantity[8]"]] + X[this->first_stage_map["CrudeQuantity[9]"]] + X[this->first_stage_map["CrudeQuantity[10]"]]-700;
    mc::FFVar g_0_1 = 13.419713831478537*X[this->first_stage_map["pickCrude[1]"]]-X[this->first_stage_map["CrudeQuantity[1]"]];
    mc::FFVar g_0_2 = 14.165341812400635*X[this->first_stage_map["pickCrude[2]"]]-X[this->first_stage_map["CrudeQuantity[2]"]];
    mc::FFVar g_0_3 = 13.419713831478537*X[this->first_stage_map["pickCrude[3]"]]-X[this->first_stage_map["CrudeQuantity[3]"]];
    mc::FFVar g_0_4 = 13.305246422893482*X[this->first_stage_map["pickCrude[4]"]]-X[this->first_stage_map["CrudeQuantity[4]"]];
    mc::FFVar g_0_5 = 14.036565977742448*X[this->first_stage_map["pickCrude[5]"]]-X[this->first_stage_map["CrudeQuantity[5]"]];
    mc::FFVar g_0_6 = 14.809220985691574*X[this->first_stage_map["pickCrude[6]"]]-X[this->first_stage_map["CrudeQuantity[6]"]];
    mc::FFVar g_0_7 = 13.119236883942767*X[this->first_stage_map["pickCrude[7]"]]-X[this->first_stage_map["CrudeQuantity[7]"]];
    mc::FFVar g_0_8 = 13.903020667726551*X[this->first_stage_map["pickCrude[8]"]]-X[this->first_stage_map["CrudeQuantity[8]"]];
    mc::FFVar g_0_9 = 13.624801271860093*X[this->first_stage_map["pickCrude[9]"]]-X[this->first_stage_map["CrudeQuantity[9]"]];
    mc::FFVar g_0_10 = 14.017488076311606*X[this->first_stage_map["pickCrude[10]"]]-X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar g_0_11 = X[this->first_stage_map["CrudeQuantity[1]"]]-201.29570747217807*X[this->first_stage_map["pickCrude[1]"]];
    mc::FFVar g_0_12 = X[this->first_stage_map["CrudeQuantity[2]"]]-212.48012718600953*X[this->first_stage_map["pickCrude[2]"]];
    mc::FFVar g_0_13 = X[this->first_stage_map["CrudeQuantity[3]"]]-201.29570747217807*X[this->first_stage_map["pickCrude[3]"]];
    mc::FFVar g_0_14 = X[this->first_stage_map["CrudeQuantity[4]"]]-199.57869634340224*X[this->first_stage_map["pickCrude[4]"]];
    mc::FFVar g_0_15 = X[this->first_stage_map["CrudeQuantity[5]"]]-210.54848966613673*X[this->first_stage_map["pickCrude[5]"]];
    mc::FFVar g_0_16 = X[this->first_stage_map["CrudeQuantity[6]"]]-222.1383147853736*X[this->first_stage_map["pickCrude[6]"]];
    mc::FFVar g_0_17 = X[this->first_stage_map["CrudeQuantity[7]"]]-196.7885532591415*X[this->first_stage_map["pickCrude[7]"]];
    mc::FFVar g_0_18 = X[this->first_stage_map["CrudeQuantity[8]"]]-208.54531001589828*X[this->first_stage_map["pickCrude[8]"]];
    mc::FFVar g_0_19 = X[this->first_stage_map["CrudeQuantity[9]"]]-204.3720190779014*X[this->first_stage_map["pickCrude[9]"]];
    mc::FFVar g_0_20 = X[this->first_stage_map["CrudeQuantity[10]"]]-210.2623211446741*X[this->first_stage_map["pickCrude[10]"]];

    mc::FFVar g_1_0 = X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]]-125;
    mc::FFVar g_1_1 = 0.08*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0.09*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] + 0.015*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.012*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] + 0.03*X[n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] + 0.04*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_Burn[1]"]] + 0.0020105335707024776*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] + 0.002033729784573578*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] + 0.002110066788923241*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] + 0.003973905045918246*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] + 0.0019988517589712403*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] + 0.0008904820763900271*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.03*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] + 0.001991196321110873*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.03*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] + 0.0028411758274924682*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.04*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] + 0.004057963205263551*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] + 0.00427501144267499*X[this->first_stage_map["CrudeQuantity[10]"]] + 0.04*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]];
    mc::FFVar n_g_1_1 =-g_1_1;
    mc::FFVar g_1_2 = 0.09*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0.12*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] + 0.053*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.046*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]] + 0.009147927746696273*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.009050097541352423*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.008440267155692963*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.019869525229591227*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.011493397614084631*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.005699085288896173*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.015431771488609266*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.012736305433586925*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.01592750558065944*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.011435655609155597*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_2 = - g_1_2;
    mc::FFVar g_1_3 = - X[n_first_stage_vars + this->second_stage_map["flow_LN_producing"]] - X[n_first_stage_vars + this->second_stage_map["flow_Burn[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] - 0.05*X[n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] - 0.035*X[n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] + 0.07016762161751647*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.04880951482976587*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.06435703706215884*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.08454482985191068*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.05426882525606917*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.021905859079194668*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.09408402617248875*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.06387747032845136*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.07598536101855999*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.06455267278439235*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_3 = - g_1_3;
    mc::FFVar g_1_4 = -0.1*X[n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] - 0.065*X[n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] - X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] + 0.16064163229912795*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.09751734317030307*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.1272370273720714*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.15220056325866882*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.10254109523522463*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.054052262036874646*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.165368854468258*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.11717400998899972*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.12853598452672302*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.12002094625310035*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_4 = - g_1_4;
    mc::FFVar g_1_5 = -0.85*X[n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] - 0.9*X[n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[1]"]] + 0.10082825857072926*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.08094244542602841*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.0908383752631455*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.09408220196211448*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.07645607978064994*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.0461269715570034*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.11548938662443065*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.08210018425650649*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.09282590832040374*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.0837902242764298*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_5= - g_1_5;
    mc::FFVar g_1_6 = - X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] - X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] + 0.2696125518312022*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.27811254804043684*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.27916183617454476*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.25184623228506886*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.2693452745213747*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.26108934479755597*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.2306800938006946*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.23591556526213323*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.2546371911302879*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.266226337592585*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_6 = - g_1_6;
    mc::FFVar g_1_7 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 0.28911472746701633*X[this->first_stage_map["CrudeQuantity[1]"]];
    mc::FFVar n_g_1_7 = - g_1_7;
    mc::FFVar g_1_8 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 0.22869291427529884*X[this->first_stage_map["CrudeQuantity[2]"]];
    mc::FFVar n_g_1_8 = - g_1_8;
    mc::FFVar g_1_9 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 0.25468506142303515*X[this->first_stage_map["CrudeQuantity[3]"]];
    mc::FFVar n_g_1_9 = - g_1_9;
    mc::FFVar g_1_10 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 0.25224362278966067*X[this->first_stage_map["CrudeQuantity[4]"]];
    mc::FFVar n_g_1_10 = - g_1_10;
    mc::FFVar g_1_11 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[5]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 0.22846875605041275*X[this->first_stage_map["CrudeQuantity[5]"]];
    mc::FFVar n_g_1_11 = - g_1_11;
    mc::FFVar g_1_12 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[6]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 0.16919159451410512*X[this->first_stage_map["CrudeQuantity[6]"]];
    mc::FFVar n_g_1_12 = - g_1_12;
    mc::FFVar g_1_13 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[7]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 0.26443087144352395*X[this->first_stage_map["CrudeQuantity[7]"]];
    mc::FFVar n_g_1_13 = - g_1_13;
    mc::FFVar g_1_14 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[8]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 0.20838555120953378*X[this->first_stage_map["CrudeQuantity[8]"]];
    mc::FFVar n_g_1_14 = - g_1_14;
    mc::FFVar g_1_15 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[9]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 0.2387096855496284*X[this->first_stage_map["CrudeQuantity[9]"]];
    mc::FFVar n_g_1_15 = - g_1_15;
    mc::FFVar g_1_16 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[10]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] + 0.223583098451902*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_16 = - g_1_16;
    mc::FFVar g_1_17 = 0.098476746897009*X[this->first_stage_map["CrudeQuantity[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]];
    mc::FFVar n_g_1_17 = - g_1_17;
    mc::FFVar g_1_18 = 0.254841406932241*X[this->first_stage_map["CrudeQuantity[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]];
    mc::FFVar n_g_1_18 = - g_1_18;
    mc::FFVar g_1_19 = 0.173170328760428*X[this->first_stage_map["CrudeQuantity[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]];
    mc::FFVar n_g_1_19 = - g_1_19;
    mc::FFVar g_1_20 = 0.141239119577067*X[this->first_stage_map["CrudeQuantity[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]];
    mc::FFVar n_g_1_20 = - g_1_20;


    // mc::FFVar g_1_21 = 0.255427719783213*X[this->first_stage_map["CrudeQuantity[5]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]];
    // mc::FFVar n_g_1_21 = - g_1_21;
    // mc::FFVar g_1_22 = 0.44104440064998*X[this->first_stage_map["CrudeQuantity[6]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]];
    // mc::FFVar n_g_1_22 = - g_1_22;
    // mc::FFVar g_1_23 = 0.112523799680884*X[this->first_stage_map["CrudeQuantity[7]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]];
    // mc::FFVar n_g_1_23 = - g_1_23;
    // mc::FFVar g_1_24 = 0.276969737693296*X[this->first_stage_map["CrudeQuantity[8]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]];
    // mc::FFVar n_g_1_24 = - g_1_24;
    // mc::FFVar g_1_25 = 0.189320400668474*X[this->first_stage_map["CrudeQuantity[9]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]];
    // mc::FFVar n_g_1_25 = - g_1_25;
    // mc::FFVar g_1_26 = 0.22611605358976*X[this->first_stage_map["CrudeQuantity[10]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]];
    // mc::FFVar n_g_1_26 = - g_1_26;
    // mc::FFVar g_1_27 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[1]"]];
    // mc::FFVar n_g_1_27 = - g_1_27;
    // mc::FFVar g_1_28 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[2]"]];
    // mc::FFVar n_g_1_28 = - g_1_28;
    // mc::FFVar g_1_29 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[3]"]];
    // mc::FFVar n_g_1_29 = - g_1_29;
    // mc::FFVar g_1_30 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[4]"]];
    // mc::FFVar n_g_1_30 = - g_1_30;
    // mc::FFVar g_1_31 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[5]"]];
    // mc::FFVar n_g_1_31 = - g_1_31;    
    // mc::FFVar g_1_32 = 0.97*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[6]"]];
    // mc::FFVar n_g_1_32 = - g_1_32;
    // mc::FFVar g_1_33 = 0.97*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[7]"]];
    // mc::FFVar n_g_1_33 = - g_1_33;
    // mc::FFVar g_1_34 = 0.96*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[8]"]];
    // mc::FFVar n_g_1_34 = - g_1_34;
    // mc::FFVar g_1_35 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[9]"]];
    // mc::FFVar n_g_1_35 = - g_1_35;
    // mc::FFVar g_1_36 = 0.96*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[10]"]];
    // mc::FFVar n_g_1_36 = - g_1_36;
    // mc::FFVar g_1_37 = 0.83*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]];
    // mc::FFVar n_g_1_37 = - g_1_37;
    // mc::FFVar g_1_38 = 0*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0.79*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]];
    // mc::FFVar n_g_1_38 = - g_1_38;
    // mc::FFVar g_1_39 = 0.97*X[n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]];
    // mc::FFVar n_g_1_39 = - g_1_39;
    // mc::FFVar g_1_40 = 0.436*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.381*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]];
    // mc::FFVar n_g_1_40 = - g_1_40;
    
    
    // mc::FFVar g_1_41 = 0.446*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.511*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
    // mc::FFVar n_g_1_41 = - g_1_41;
    // mc::FFVar g_1_42 = 0.96*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[3]"]];
    // mc::FFVar n_g_1_42 = - g_1_42;
    // mc::FFVar g_1_43 = -(X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] - 5.0);
    // mc::FFVar g_1_44 = -(X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]]);
    // mc::FFVar g_1_45 = -(X[n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Import[3]"]]);
    // mc::FFVar g_1_46 = -(X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Import[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[8]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[8]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[9]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[9]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[10]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[10]"]] - 100.0);
    // mc::FFVar g_1_47 = -(X[n_first_stage_vars + this->second_stage_map["flow_Import[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] - 100.0);
    // mc::FFVar g_1_48 = -(X[n_first_stage_vars + this->second_stage_map["flow_Import[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]]);
    // mc::FFVar g_1_49 = -(X[n_first_stage_vars + this->second_stage_map["flow_Import[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_LN_producing"]]);
    // mc::FFVar g_1_50 = 1.7241379310344829*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 1.5037593984962405*X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 1.5384615384615383*X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 1.2987012987012987*X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 1.25*X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 1.3333333333333333*X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 1.2658227848101264*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] - X[n_first_stage_vars + this->second_stage_map["volume_PG98"]];
    // mc::FFVar n_g_1_50= - g_1_50;
    // mc::FFVar g_1_51 = 1.7241379310344829*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 1.5037593984962405*X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 1.5384615384615383*X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 1.2987012987012987*X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 1.25*X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 1.3333333333333333*X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 1.3157894736842106*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] - X[n_first_stage_vars + this->second_stage_map["volume_ES95"]];
    // mc::FFVar n_g_1_51 = - g_1_51;
    // mc::FFVar g_1_52 = 1.7241379310344829*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 0.039473684210526314*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] - 0.05*X[n_first_stage_vars + this->second_stage_map["volume_ES95"]];
    // mc::FFVar g_1_53 = 1.7241379310344829*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 0.039473684210526314*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] - 0.05*X[n_first_stage_vars + this->second_stage_map["volume_PG98"]];
    // mc::FFVar g_1_54 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    // mc::FFVar n_g_1_54 = - g_1_54;
    // mc::FFVar g_1_55 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    // mc::FFVar n_g_1_55 = - g_1_55;
    // mc::FFVar g_1_56 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    // mc::FFVar n_g_1_56 = - g_1_56;
    // mc::FFVar g_1_57 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    // mc::FFVar n_g_1_57 = - g_1_57;
    // mc::FFVar g_1_58 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    // mc::FFVar n_g_1_58 = - g_1_58;
    // mc::FFVar g_1_59 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    // mc::FFVar n_g_1_59 = - g_1_59;
    // mc::FFVar g_1_60 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    // mc::FFVar n_g_1_60 = - g_1_60;
    
    
    // mc::FFVar g_1_61 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    // mc::FFVar n_g_1_61 = - g_1_61;
    // mc::FFVar g_1_62 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    // mc::FFVar n_g_1_62 = - g_1_62;
    // mc::FFVar g_1_63 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    // mc::FFVar n_g_1_63 = - g_1_63;
    // mc::FFVar g_1_64 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    // mc::FFVar n_g_1_64 = - g_1_64;
    // mc::FFVar g_1_65 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    // mc::FFVar n_g_1_65 = - g_1_65;
    // mc::FFVar g_1_66 = X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    // mc::FFVar n_g_1_66 = - g_1_66;
    // mc::FFVar g_1_67 = X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    // mc::FFVar n_g_1_67 = - g_1_67;
    // mc::FFVar g_1_68 = X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    // mc::FFVar n_g_1_68 = - g_1_68;
    // mc::FFVar g_1_69 = X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    // mc::FFVar n_g_1_69 = - g_1_69;
    // mc::FFVar g_1_70 = X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    // mc::FFVar n_g_1_70 = - g_1_70;
    // mc::FFVar g_1_71 = X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    // mc::FFVar n_g_1_71 = - g_1_71;
    // mc::FFVar g_1_72 = X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    // mc::FFVar n_g_1_72 = - g_1_72;
    // mc::FFVar g_1_73 = X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    // mc::FFVar n_g_1_73 = - g_1_73;
    // mc::FFVar g_1_74 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[4]"]] - (0.009147927746696273*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.009050097541352423*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.008440267155692963*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.019869525229591227*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.011493397614084631*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.005699085288896173*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.015431771488609266*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.012736305433586925*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.01592750558065944*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.011435655609155597*X[this->first_stage_map["CrudeQuantity[10]"]]);
    // mc::FFVar n_g_1_74 = - g_1_74;
    // mc::FFVar g_1_75 = 0.09*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[4]"]];
    // mc::FFVar n_g_1_75 = - g_1_75;
    // mc::FFVar g_1_76 = 0.12*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[4]"]];
    // mc::FFVar n_g_1_76 = - g_1_76;
    // mc::FFVar g_1_77 = 0.053*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] - X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[4]"]];
    // mc::FFVar n_g_1_77 = - g_1_77;
    // mc::FFVar g_1_78 = 0.046*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[4]"]];
    // mc::FFVar n_g_1_78 = - g_1_78;
    // mc::FFVar g_1_79 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    // mc::FFVar n_g_1_79 = - g_1_79;
    // mc::FFVar g_1_80 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    // mc::FFVar n_g_1_80 = - g_1_80;
    
    
    // mc::FFVar g_1_81 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    // mc::FFVar n_g_1_81 = - g_1_81;
    // mc::FFVar g_1_82 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[4]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[4]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[4]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[4]"]] + X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    // mc::FFVar n_g_1_82 = - g_1_82;
    // mc::FFVar g_1_83 = X[n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] + X[n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] - 1.0;
    // mc::FFVar n_g_1_83 = - g_1_83;
    // mc::FFVar g_1_84 = -(-0.45*X[n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 0.8552631578947368*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 0.6015037593984962*X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 1.2307692307692308*X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 0.6493506493506493*X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 0.625*X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 0.8666666666666667*X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 7.413793103448276*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 7.379310344827587*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 7.517241379310346*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 7.258620689655173*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 7.275862068965517*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]]);
    // mc::FFVar g_1_85 = -0.8*X[n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 0.8552631578947368*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 0.6015037593984962*X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 1.2307692307692308*X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 0.6493506493506493*X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 0.625*X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 0.8666666666666667*X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 7.413793103448276*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 7.379310344827587*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 7.517241379310346*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 7.258620689655173*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 7.275862068965517*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]];
    // mc::FFVar g_1_86 = -(-0.5*X[n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 0.8227848101265822*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 0.6015037593984962*X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 1.2307692307692308*X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 0.6493506493506493*X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 0.625*X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 0.8666666666666667*X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 7.413793103448276*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 7.379310344827587*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 7.517241379310346*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 7.258620689655173*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 7.275862068965517*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]]);
    // mc::FFVar g_1_87 = -0.86*X[n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 0.8227848101265822*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 0.6015037593984962*X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 1.2307692307692308*X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 0.6493506493506493*X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 0.625*X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 0.8666666666666667*X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 7.413793103448276*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 7.379310344827587*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 7.517241379310346*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 7.258620689655173*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 7.275862068965517*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]];
    // mc::FFVar g_1_88 = -(-98*X[n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 132.91139240506328*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 136.8421052631579*X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 109.23076923076923*X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 123.37662337662337*X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 125.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 124.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 160.34482758620692*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 159.48275862068968*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 161.3793103448276*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 159.82758620689657*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 161.89655172413796*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]]);
    // mc::FFVar g_1_89 = -(-95*X[n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 131.57894736842104*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 136.8421052631579*X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 109.23076923076923*X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 123.37662337662337*X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 125.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 124.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 160.34482758620692*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 159.48275862068968*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 161.3793103448276*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 159.82758620689657*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 161.89655172413796*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]]);
    // mc::FFVar g_1_90 = -10*X[n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 6.329113924050633*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 7.518796992481203*X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 4.615384615384615*X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 11.688311688311687*X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 11.25*X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 14.666666666666666*X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 5.172413793103448*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 5.00000000000001*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 4.6551724137930846*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 6.379310344827592*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 6.379310344827592*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]];
    
    // mc::FFVar g_1_91 = -10*X[n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 5.2631578947368425*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 7.518796992481203*X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 4.615384615384615*X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 11.688311688311687*X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 11.25*X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 14.666666666666666*X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 5.172413793103448*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 5.00000000000001*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 4.6551724137930846*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 6.379310344827592*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 6.379310344827592*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]];
    // mc::FFVar g_1_92 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
    // mc::FFVar n_g_1_92 = - g_1_92;
    // mc::FFVar g_1_93 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]];
    // mc::FFVar n_g_1_93 = - g_1_93;
    // mc::FFVar g_1_94 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]];
    // mc::FFVar n_g_1_94 = - g_1_94;
    // mc::FFVar g_1_95 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
    // mc::FFVar n_g_1_95 = - g_1_95;
    // mc::FFVar g_1_96 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]];
    // mc::FFVar n_g_1_96 = - g_1_96;
    // mc::FFVar g_1_97 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]];
    // mc::FFVar n_g_1_97 = - g_1_97;
    // mc::FFVar g_1_98 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] - 0.446*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]];
    // mc::FFVar n_g_1_98 = - g_1_98;
    // mc::FFVar g_1_99 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] - 0.511*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]];
    // mc::FFVar n_g_1_99 = - g_1_99;
    // mc::FFVar g_1_100 = X[n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] + X[n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] - 1.0;
    // mc::FFVar n_g_1_100 = - g_1_100;
    
    // mc::FFVar g_1_101 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
    // mc::FFVar n_g_1_101 = - g_1_101;
    // mc::FFVar g_1_102 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]];
    // mc::FFVar n_g_1_102 = - g_1_102;
    // mc::FFVar g_1_103 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]];
    // mc::FFVar n_g_1_103 = - g_1_103;
    // mc::FFVar g_1_104 = -X[n_first_stage_vars + this->second_stage_map["volume_HF"]] + 1.0204081632653061*X[n_first_stage_vars + this->second_stage_map["flow_Import[5]"]] + 1.0526315789473684*X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]] + 1.0655301012253595*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + 1.175640724194686*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 1.032844453625284*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + 1.1641443538998837*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 1.0612331529236974*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + 1.188636633781053*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 1.060108131029365*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + 1.183431952662722*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 1.0360547036883547*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + 1.166452816983553*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 1.0280662074637608*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + 1.1510128913443831*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 1.0559662090813096*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + 1.1899095668729176*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 1.020512297173181*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + 1.1810558639423645*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 1.0458063166701526*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + 1.1796626164916835*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 1.0325245224574084*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + 1.1684973124561813*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]];
    // mc::FFVar n_g_1_104 = - g_1_104;
    // mc::FFVar g_1_105 = -(34.629728289824186*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + 2.962614624970609*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 71.88597397231976*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + 3.39930151338766*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 40.53910644168524*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + 3.1023416141685485*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 45.26661719495389*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + 3.0295857988165684*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 89.61873186904269*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + 3.0910999650064155*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 77.61899866351393*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + 3.39548802946593*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 44.66737064413939*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + 2.974773917182294*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 45.92305337279314*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + 2.9644502184953345*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 55.95063794185317*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + 3.0907160552082105*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 56.99535363964894*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + 3.119887824258004*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] + (12.2*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + 11.65*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]])/0.95 - 30*X[n_first_stage_vars + this->second_stage_map["volume_HF"]]);
    // mc::FFVar g_1_106 = 34.629728289824186*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + 2.962614624970609*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 71.88597397231976*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + 3.39930151338766*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 40.53910644168524*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + 3.1023416141685485*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 45.26661719495389*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + 3.0295857988165684*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 89.61873186904269*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + 3.0910999650064155*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 77.61899866351393*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + 3.39548802946593*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 44.66737064413939*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + 2.974773917182294*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 45.92305337279314*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + 2.9644502184953345*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 55.95063794185317*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + 3.0907160552082105*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 56.99535363964894*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + 3.119887824258004*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] + (12.2*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + 11.65*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]])/0.95 - 33*X[n_first_stage_vars + this->second_stage_map["volume_HF"]];
    // mc::FFVar g_1_107 = -0.0015*X[n_first_stage_vars + this->second_stage_map["flow_Import[4]"]] + 0.140588513077039*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[1]"]] - 0.000789557434614805*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[1]"]] + 0.309219599235616*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[2]"]] + 5.3597996178079976e-05*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[2]"]] + 0.16502807856732*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[3]"]] - 0.0006673596071634*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[3]"]] + 0.211405808207417*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[4]"]] - 0.000435470958962915*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[4]"]] + 0.264982491043895*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[5]"]] - 0.00016758754478052502*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[5]"]] + 0.7602297836086701*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[6]"]] + 0.0023086489180433505*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[6]"]] + 0.632862056891616*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[7]"]] + 0.0016718102844580796*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[7]"]] + 1.575235109424405*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[8]"]] + 0.006383675547122027*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[8]"]] + 0.289990315101932*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[9]"]] - 4.2548424490339905e-05*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[9]"]] + 1.087848038245218*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[10]"]] + 0.003946740191226091*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[10]"]] + 0.0985*X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[1]"]] + 1.6784999999999999*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] + 2.0985*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] + 0.0084*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] + 0.0105*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] - 0.0015*X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[3]"]];
    // mc::FFVar g_1_108 = -(1.3*X[n_first_stage_vars + this->second_stage_map["flow_Burn[1]"]] + 1.2*X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]] + 1.1*X[n_first_stage_vars + this->second_stage_map["flow_Burn[3]"]] - 0.019*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] - 0.026*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - 0.007*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] - 0.007*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - 0.04*X[n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] - 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - 15.2 - (0.018*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[10]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]]));
    // mc::FFVar g_1_109 = X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - 175;
    // mc::FFVar g_1_110 = X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - 65;
    
    mc::FFVar objective=0.2 * (
        /* global flows (t = 1) */
        3.2 * X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]]
        + 3.0 * X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]]
        + 2.7 * X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]]
        + 3.2 * X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]]
        + 6.0 * X[n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]]
        + 3.345671410129097 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]]

        - 561.6 *
            X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]]
        - 1003.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_LN_producing"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]]

        /* crude 1 */
        + 2.3942543643299556 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[1]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[1]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]]
        + 864.3999526122498 *
            X[this->first_stage_map["CrudeQuantity[1]"]]

        /* crude 2 */
        + 2.485328036981826 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[2]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[2]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]]
        + 765.9539842873176 *
            X[this->first_stage_map["CrudeQuantity[2]"]]

        /* crude 3 */
        + 2.437662761144984 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[3]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[3]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]]
        + 824.9058168463453 *
            X[this->first_stage_map["CrudeQuantity[3]"]]

        /* crude 4 */
        + 2.4589973078611767 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[4]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[4]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]]
        + 839.5184609869758 *
            X[this->first_stage_map["CrudeQuantity[4]"]]

        /* crude 5 */
        + 2.460163454262119 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[5]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[5]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]]
        + 779.3929097293013 *
            X[this->first_stage_map["CrudeQuantity[5]"]]

        /* crude 6 */
        + 2.760038638583934 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[6]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[6]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]]
        + 692.8115942028985 *
            X[this->first_stage_map["CrudeQuantity[6]"]]

        /* crude 7 */
        + 2.7649237751065976 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[7]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[7]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]]
        + 878.862094037809 *
            X[this->first_stage_map["CrudeQuantity[7]"]]

        /* crude 8 */
        + 3.39343900683156 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[8]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[8]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]]
        + 735.8113207547168 *
            X[this->first_stage_map["CrudeQuantity[8]"]]

        /* crude 9 */
        + 2.5052287966283195 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[9]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[9]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]]
        + 810.2870478413071 *
            X[this->first_stage_map["CrudeQuantity[9]"]]

        /* crude 10 */
        + 3.025222449696517 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[10]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[10]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]]
        + 749.7063627084043 *
            X[this->first_stage_map["CrudeQuantity[10]"]]

        /* product penalties (t = 1) */
        - 1231.0 *
            ( X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] )

        - 1194.0 *
            ( X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] )

        - 923.0 *
            ( X[n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] )

        - 907.0 *
            ( X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[1]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[3]"]] )
    );
    


    // Evaluate constraints and objective
    mc::PolImg<mc::Interval> Env;
    mc::PolVar<mc::Interval> PX[nvars];

    for (int i = 0; i < n_first_stage_vars; ++i) PX[i].set(&Env, X[i], this->first_stage_IX[i]);
    for (int i = n_first_stage_vars; i < nvars; ++i) PX[i].set(&Env, X[i], this->second_stage_IX[i - n_first_stage_vars]);
    
    std::vector<mc::FFVar> F = {
        g_0_0,g_0_1,g_0_2,g_0_3,g_0_4,g_0_5,g_0_6,g_0_7,g_0_8,g_0_9,g_0_10,
        
        // g_0_11,g_0_12,g_0_13,g_0_14,g_0_15,
        // g_0_16,g_0_17,g_0_18,g_0_19,g_0_20, 
        // g_1_0,g_1_1,g_1_2,g_1_3,g_1_4,g_1_5,g_1_6,g_1_7,g_1_8,g_1_9,g_1_10,g_1_11,g_1_12,g_1_13,g_1_14,g_1_15,g_1_16,g_1_17,g_1_18,g_1_19,g_1_20,
        // n_g_1_1,n_g_1_2,n_g_1_3,n_g_1_4,n_g_1_5,n_g_1_6,n_g_1_7,n_g_1_8,n_g_1_9,n_g_1_10,n_g_1_11,n_g_1_12,n_g_1_13,n_g_1_14,n_g_1_15,n_g_1_16,
        // n_g_1_17,n_g_1_18,n_g_1_19,n_g_1_20,
        
        // g_1_21,g_1_22,g_1_23,g_1_24,g_1_25,g_1_26,g_1_27,g_1_28,g_1_29,g_1_30,g_1_31,g_1_32,g_1_33,g_1_34,g_1_35,g_1_36,g_1_37,g_1_38,g_1_39,g_1_40,
        // n_g_1_21,n_g_1_22,n_g_1_23,n_g_1_24,n_g_1_25,n_g_1_26,n_g_1_27,n_g_1_28,n_g_1_29,n_g_1_30,n_g_1_31,n_g_1_32, n_g_1_33, n_g_1_34, n_g_1_35,n_g_1_36,n_g_1_37,n_g_1_38,n_g_1_39,n_g_1_40,
        
        // g_1_41,g_1_42,g_1_43,g_1_44,g_1_45,g_1_46,g_1_47,g_1_48,g_1_49,g_1_50,g_1_51,g_1_52,g_1_53,g_1_54,g_1_55,g_1_56,g_1_57,g_1_58,g_1_59,g_1_60,
        // n_g_1_41,n_g_1_42,n_g_1_50,n_g_1_51,n_g_1_54,n_g_1_55,n_g_1_56,n_g_1_57,n_g_1_58,n_g_1_59,n_g_1_60,

        // g_1_61,g_1_62,g_1_63,g_1_64,g_1_65,g_1_66,g_1_67,g_1_68,g_1_69,g_1_70,g_1_71,g_1_72,g_1_73,g_1_74,g_1_75,g_1_76,g_1_77,g_1_78,g_1_79,g_1_80,
        // n_g_1_61,n_g_1_62,n_g_1_63,n_g_1_64,n_g_1_65,n_g_1_66,n_g_1_67,n_g_1_68,n_g_1_69,n_g_1_70,n_g_1_71,n_g_1_72,n_g_1_73,n_g_1_74,n_g_1_75,n_g_1_76,n_g_1_77,n_g_1_78,n_g_1_79,n_g_1_80,

        // g_1_81,g_1_82,g_1_83,g_1_84,g_1_85,g_1_86,g_1_87,g_1_88,g_1_89,g_1_90,
        // g_1_91,g_1_92,g_1_93,g_1_94,g_1_95,
        // g_1_96,g_1_97,g_1_98,g_1_99,g_1_100,
        // n_g_1_81,n_g_1_82,n_g_1_83,
        // n_g_1_92,n_g_1_93,n_g_1_94,n_g_1_95,
        // n_g_1_96,n_g_1_97,n_g_1_98,n_g_1_99,n_g_1_100,
        
        // g_1_101,g_1_102,g_1_103,g_1_104,g_1_105,g_1_106,g_1_107,g_1_108,g_1_109,g_1_110,
        // n_g_1_101,n_g_1_102,n_g_1_103,n_g_1_104,
        
        objective};


 
    mc::PolVar<mc::Interval> PF[F.size()];
    DAG.eval(F.size(), F.data(), PF, nvars, X, PX);
    

    Env.generate_cuts(F.size(), PF);

    // Extract LP data from Env Don't touch below this line
    auto c = Env.Cuts();
    int after_nvars = Env.Vars().size();
    std::vector<mc::Interval> var_bound(after_nvars);
    for (auto v : Env.Vars()) { // Note: Env.Vars() ordering is not v1,v2, ... rather based on z1,z2 so we need to get indices
        int v_idx=v.second->id().second;
        var_bound[v_idx]=mc::Interval(v.second->range().l(),v.second->range().u());
    }
    // Add variables to cplex in order of their IDs to match indexing
    for (int i = 0; i < after_nvars; ++i) {
        cplex_x->add(IloNumVar((*cplex_env), var_bound[i].l(), var_bound[i].u()));
    }
    

    // Loop over cuts to build Ax<=b
    int row_idx=0;
    for (const auto& pc : c) {
        const double* coeffs = pc->coef();    // get pointer to coefficients
        int n = pc->nvar();  // number of variables in this constraint
        auto v = pc->var();              // get variable names that appear in this constraint
        IloExpr expr(*cplex_env);
        for (int i = 0; i < n; ++i){
            int col_idx = std::stoi(v[i].name().substr(1));
            if (col_idx >= 0 && col_idx < cplex_x->getSize()){
                expr += coeffs[i] * (*cplex_x)[col_idx];
            }else{
                throw std::runtime_error("Error in generating constraints from cuts.");
            }
        }
        if (pc->type() == 1) { // <=
            cplex_constraints->add(expr <= pc->rhs());
        }else if (pc->type() == 2) { // >=
            cplex_constraints->add(expr >= pc->rhs());
        }else { // ==
            cplex_constraints->add(expr == pc->rhs());
        }
        expr.end();
    }
    IloExpr objExpr(*cplex_env);
    objExpr+=(*cplex_x)[after_nvars-1];
    *(cplex_obj) = IloMinimize(*cplex_env, objExpr);
    objExpr.end();
    
    for (size_t i = 0; i < sizeof(PF)/sizeof(PF[0])-1; ++i) {
        int pf_idx = PF[i].id().second;
        if (pf_idx >= 0 && pf_idx < cplex_x->getSize()) {
            IloExpr expr(*cplex_env);
            expr+=(*cplex_x)[pf_idx];
            cplex_constraints->add(expr <= 0);
            expr.end();
        }else{
            throw std::runtime_error("Error in generating constraints from cuts.");
        }
    }

    cplexmodel->add(*cplex_x);
    cplexmodel->add(*cplex_constraints);
    cplexmodel->add(*cplex_obj);
};

void CrudeModel::generateMINLP(GRBModel* grbmodel) {

    // Loop over each scenario to build subproblem

    int n_first_stage_vars = this->first_stage_IX.size();
    int n_second_stage_vars = this->second_stage_IX.size();
    int nvars = n_first_stage_vars + n_second_stage_vars;

    mc::FFGraph DAG;
    std::vector<mc::FFVar> X(nvars);
    for (int i = 0; i < nvars; ++i) X[i].set(&DAG);

    

    // scenario perturbation


    mc::FFVar g_0_0 = X[this->first_stage_map["CrudeQuantity[1]"]] + X[this->first_stage_map["CrudeQuantity[2]"]] + X[this->first_stage_map["CrudeQuantity[3]"]] + X[this->first_stage_map["CrudeQuantity[4]"]] + X[this->first_stage_map["CrudeQuantity[5]"]] + X[this->first_stage_map["CrudeQuantity[6]"]] + X[this->first_stage_map["CrudeQuantity[7]"]] + X[this->first_stage_map["CrudeQuantity[8]"]] + X[this->first_stage_map["CrudeQuantity[9]"]] + X[this->first_stage_map["CrudeQuantity[10]"]]-700;
    mc::FFVar g_0_1 = 13.419713831478537*X[this->first_stage_map["pickCrude[1]"]]-X[this->first_stage_map["CrudeQuantity[1]"]];
    mc::FFVar g_0_2 = 14.165341812400635*X[this->first_stage_map["pickCrude[2]"]]-X[this->first_stage_map["CrudeQuantity[2]"]];
    mc::FFVar g_0_3 = 13.419713831478537*X[this->first_stage_map["pickCrude[3]"]]-X[this->first_stage_map["CrudeQuantity[3]"]];
    mc::FFVar g_0_4 = 13.305246422893482*X[this->first_stage_map["pickCrude[4]"]]-X[this->first_stage_map["CrudeQuantity[4]"]];
    mc::FFVar g_0_5 = 14.036565977742448*X[this->first_stage_map["pickCrude[5]"]]-X[this->first_stage_map["CrudeQuantity[5]"]];
    mc::FFVar g_0_6 = 14.809220985691574*X[this->first_stage_map["pickCrude[6]"]]-X[this->first_stage_map["CrudeQuantity[6]"]];
    mc::FFVar g_0_7 = 13.119236883942767*X[this->first_stage_map["pickCrude[7]"]]-X[this->first_stage_map["CrudeQuantity[7]"]];
    mc::FFVar g_0_8 = 13.903020667726551*X[this->first_stage_map["pickCrude[8]"]]-X[this->first_stage_map["CrudeQuantity[8]"]];
    mc::FFVar g_0_9 = 13.624801271860093*X[this->first_stage_map["pickCrude[9]"]]-X[this->first_stage_map["CrudeQuantity[9]"]];
    mc::FFVar g_0_10 = 14.017488076311606*X[this->first_stage_map["pickCrude[10]"]]-X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar g_0_11 = X[this->first_stage_map["CrudeQuantity[1]"]]-201.29570747217807*X[this->first_stage_map["pickCrude[1]"]];
    mc::FFVar g_0_12 = X[this->first_stage_map["CrudeQuantity[2]"]]-212.48012718600953*X[this->first_stage_map["pickCrude[2]"]];
    mc::FFVar g_0_13 = X[this->first_stage_map["CrudeQuantity[3]"]]-201.29570747217807*X[this->first_stage_map["pickCrude[3]"]];
    mc::FFVar g_0_14 = X[this->first_stage_map["CrudeQuantity[4]"]]-199.57869634340224*X[this->first_stage_map["pickCrude[4]"]];
    mc::FFVar g_0_15 = X[this->first_stage_map["CrudeQuantity[5]"]]-210.54848966613673*X[this->first_stage_map["pickCrude[5]"]];
    mc::FFVar g_0_16 = X[this->first_stage_map["CrudeQuantity[6]"]]-222.1383147853736*X[this->first_stage_map["pickCrude[6]"]];
    mc::FFVar g_0_17 = X[this->first_stage_map["CrudeQuantity[7]"]]-196.7885532591415*X[this->first_stage_map["pickCrude[7]"]];
    mc::FFVar g_0_18 = X[this->first_stage_map["CrudeQuantity[8]"]]-208.54531001589828*X[this->first_stage_map["pickCrude[8]"]];
    mc::FFVar g_0_19 = X[this->first_stage_map["CrudeQuantity[9]"]]-204.3720190779014*X[this->first_stage_map["pickCrude[9]"]];
    mc::FFVar g_0_20 = X[this->first_stage_map["CrudeQuantity[10]"]]-210.2623211446741*X[this->first_stage_map["pickCrude[10]"]];

    mc::FFVar g_1_0 = X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]]-125;
    mc::FFVar g_1_1 = 0.08*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0.09*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] + 0.015*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.012*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] + 0.03*X[n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] + 0.04*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_Burn[1]"]] + 0.0020105335707024776*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] + 0.002033729784573578*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] + 0.002110066788923241*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] + 0.003973905045918246*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] + 0.0019988517589712403*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] + 0.0008904820763900271*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.03*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] + 0.001991196321110873*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.03*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] + 0.0028411758274924682*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.04*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] + 0.004057963205263551*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] + 0.00427501144267499*X[this->first_stage_map["CrudeQuantity[10]"]] + 0.04*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]];
    mc::FFVar n_g_1_1 =-g_1_1;
    mc::FFVar g_1_2 = 0.09*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0.12*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] + 0.053*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.046*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]] + 0.009147927746696273*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.009050097541352423*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.008440267155692963*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.019869525229591227*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.011493397614084631*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.005699085288896173*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.015431771488609266*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.012736305433586925*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.01592750558065944*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.011435655609155597*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_2 = - g_1_2;
    mc::FFVar g_1_3 = - X[n_first_stage_vars + this->second_stage_map["flow_LN_producing"]] - X[n_first_stage_vars + this->second_stage_map["flow_Burn[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] - 0.05*X[n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] - 0.035*X[n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] + 0.07016762161751647*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.04880951482976587*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.06435703706215884*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.08454482985191068*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.05426882525606917*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.021905859079194668*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.09408402617248875*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.06387747032845136*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.07598536101855999*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.06455267278439235*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_3 = - g_1_3;
    mc::FFVar g_1_4 = -0.1*X[n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] - 0.065*X[n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] - X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] + 0.16064163229912795*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.09751734317030307*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.1272370273720714*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.15220056325866882*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.10254109523522463*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.054052262036874646*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.165368854468258*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.11717400998899972*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.12853598452672302*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.12002094625310035*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_4 = - g_1_4;
    mc::FFVar g_1_5 = -0.85*X[n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] - 0.9*X[n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[1]"]] + 0.10082825857072926*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.08094244542602841*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.0908383752631455*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.09408220196211448*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.07645607978064994*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.0461269715570034*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.11548938662443065*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.08210018425650649*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.09282590832040374*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.0837902242764298*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_5= - g_1_5;
    mc::FFVar g_1_6 = - X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] - X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] + 0.2696125518312022*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.27811254804043684*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.27916183617454476*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.25184623228506886*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.2693452745213747*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.26108934479755597*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.2306800938006946*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.23591556526213323*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.2546371911302879*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.266226337592585*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_6 = - g_1_6;
    mc::FFVar g_1_7 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 0.28911472746701633*X[this->first_stage_map["CrudeQuantity[1]"]];
    mc::FFVar n_g_1_7 = - g_1_7;
    mc::FFVar g_1_8 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 0.22869291427529884*X[this->first_stage_map["CrudeQuantity[2]"]];
    mc::FFVar n_g_1_8 = - g_1_8;
    mc::FFVar g_1_9 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 0.25468506142303515*X[this->first_stage_map["CrudeQuantity[3]"]];
    mc::FFVar n_g_1_9 = - g_1_9;
    mc::FFVar g_1_10 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 0.25224362278966067*X[this->first_stage_map["CrudeQuantity[4]"]];
    mc::FFVar n_g_1_10 = - g_1_10;
    mc::FFVar g_1_11 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[5]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 0.22846875605041275*X[this->first_stage_map["CrudeQuantity[5]"]];
    mc::FFVar n_g_1_11 = - g_1_11;
    mc::FFVar g_1_12 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[6]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 0.16919159451410512*X[this->first_stage_map["CrudeQuantity[6]"]];
    mc::FFVar n_g_1_12 = - g_1_12;
    mc::FFVar g_1_13 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[7]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 0.26443087144352395*X[this->first_stage_map["CrudeQuantity[7]"]];
    mc::FFVar n_g_1_13 = - g_1_13;
    mc::FFVar g_1_14 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[8]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 0.20838555120953378*X[this->first_stage_map["CrudeQuantity[8]"]];
    mc::FFVar n_g_1_14 = - g_1_14;
    mc::FFVar g_1_15 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[9]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 0.2387096855496284*X[this->first_stage_map["CrudeQuantity[9]"]];
    mc::FFVar n_g_1_15 = - g_1_15;
    mc::FFVar g_1_16 = - X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[10]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] + 0.223583098451902*X[this->first_stage_map["CrudeQuantity[10]"]];
    mc::FFVar n_g_1_16 = - g_1_16;
    mc::FFVar g_1_17 = 0.098476746897009*X[this->first_stage_map["CrudeQuantity[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]];
    mc::FFVar n_g_1_17 = - g_1_17;
    mc::FFVar g_1_18 = 0.254841406932241*X[this->first_stage_map["CrudeQuantity[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]];
    mc::FFVar n_g_1_18 = - g_1_18;
    mc::FFVar g_1_19 = 0.173170328760428*X[this->first_stage_map["CrudeQuantity[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]];
    mc::FFVar n_g_1_19 = - g_1_19;
    mc::FFVar g_1_20 = 0.141239119577067*X[this->first_stage_map["CrudeQuantity[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]];
    mc::FFVar n_g_1_20 = - g_1_20;


    mc::FFVar g_1_21 = 0.255427719783213*X[this->first_stage_map["CrudeQuantity[5]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]];
    mc::FFVar n_g_1_21 = - g_1_21;
    mc::FFVar g_1_22 = 0.44104440064998*X[this->first_stage_map["CrudeQuantity[6]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]];
    mc::FFVar n_g_1_22 = - g_1_22;
    mc::FFVar g_1_23 = 0.112523799680884*X[this->first_stage_map["CrudeQuantity[7]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]];
    mc::FFVar n_g_1_23 = - g_1_23;
    mc::FFVar g_1_24 = 0.276969737693296*X[this->first_stage_map["CrudeQuantity[8]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]];
    mc::FFVar n_g_1_24 = - g_1_24;
    mc::FFVar g_1_25 = 0.189320400668474*X[this->first_stage_map["CrudeQuantity[9]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]];
    mc::FFVar n_g_1_25 = - g_1_25;
    mc::FFVar g_1_26 = 0.22611605358976*X[this->first_stage_map["CrudeQuantity[10]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]];
    mc::FFVar n_g_1_26 = - g_1_26;
    mc::FFVar g_1_27 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[1]"]];
    mc::FFVar n_g_1_27 = - g_1_27;
    mc::FFVar g_1_28 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[2]"]];
    mc::FFVar n_g_1_28 = - g_1_28;
    mc::FFVar g_1_29 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[3]"]];
    mc::FFVar n_g_1_29 = - g_1_29;
    mc::FFVar g_1_30 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[4]"]];
    mc::FFVar n_g_1_30 = - g_1_30;
    mc::FFVar g_1_31 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[5]"]];
    mc::FFVar n_g_1_31 = - g_1_31;    
    mc::FFVar g_1_32 = 0.97*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[6]"]];
    mc::FFVar n_g_1_32 = - g_1_32;
    mc::FFVar g_1_33 = 0.97*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[7]"]];
    mc::FFVar n_g_1_33 = - g_1_33;
    mc::FFVar g_1_34 = 0.96*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[8]"]];
    mc::FFVar n_g_1_34 = - g_1_34;
    mc::FFVar g_1_35 = 0.98*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[9]"]];
    mc::FFVar n_g_1_35 = - g_1_35;
    mc::FFVar g_1_36 = 0.96*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[10]"]];
    mc::FFVar n_g_1_36 = - g_1_36;
    mc::FFVar g_1_37 = 0.83*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]];
    mc::FFVar n_g_1_37 = - g_1_37;
    mc::FFVar g_1_38 = 0*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0.79*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]];
    mc::FFVar n_g_1_38 = - g_1_38;
    mc::FFVar g_1_39 = 0.97*X[n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]];
    mc::FFVar n_g_1_39 = - g_1_39;
    mc::FFVar g_1_40 = 0.436*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.381*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]];
    mc::FFVar n_g_1_40 = - g_1_40;


    mc::FFVar g_1_41 = 0.446*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.511*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
    mc::FFVar n_g_1_41 = - g_1_41;
    mc::FFVar g_1_42 = 0.96*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[3]"]];
    mc::FFVar n_g_1_42 = - g_1_42;
    mc::FFVar g_1_43 = -(X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] - 5.0);
    mc::FFVar g_1_44 = -(X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]]);
    mc::FFVar g_1_45 = -(X[n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Import[3]"]]);
    mc::FFVar g_1_46 = -(X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_Import[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[8]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[8]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[9]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[9]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[10]"]] + X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[10]"]] - 100.0);
    mc::FFVar g_1_47 = -(X[n_first_stage_vars + this->second_stage_map["flow_Import[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] - 100.0);
    mc::FFVar g_1_48 = -(X[n_first_stage_vars + this->second_stage_map["flow_Import[6]"]] + X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]]);
    mc::FFVar g_1_49 = -(X[n_first_stage_vars + this->second_stage_map["flow_Import[7]"]] + X[n_first_stage_vars + this->second_stage_map["flow_LN_producing"]]);
    mc::FFVar g_1_50 = 1.7241379310344829*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 1.5037593984962405*X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 1.5384615384615383*X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 1.2987012987012987*X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 1.25*X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 1.3333333333333333*X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 1.2658227848101264*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] - X[n_first_stage_vars + this->second_stage_map["volume_PG98"]];
    mc::FFVar n_g_1_50= - g_1_50;
    mc::FFVar g_1_51 = 1.7241379310344829*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 1.5037593984962405*X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 1.5384615384615383*X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 1.2987012987012987*X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 1.25*X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 1.3333333333333333*X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 1.3157894736842106*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] - X[n_first_stage_vars + this->second_stage_map["volume_ES95"]];
    mc::FFVar n_g_1_51 = - g_1_51;
    mc::FFVar g_1_52 = 1.7241379310344829*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 0.039473684210526314*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] - 0.05*X[n_first_stage_vars + this->second_stage_map["volume_ES95"]];
    mc::FFVar g_1_53 = 1.7241379310344829*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 0.039473684210526314*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] - 0.05*X[n_first_stage_vars + this->second_stage_map["volume_PG98"]];
    mc::FFVar g_1_54 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    mc::FFVar n_g_1_54 = - g_1_54;
    mc::FFVar g_1_55 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    mc::FFVar n_g_1_55 = - g_1_55;
    mc::FFVar g_1_56 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    mc::FFVar n_g_1_56 = - g_1_56;
    mc::FFVar g_1_57 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    mc::FFVar n_g_1_57 = - g_1_57;
    mc::FFVar g_1_58 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    mc::FFVar n_g_1_58 = - g_1_58;
    mc::FFVar g_1_59 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    mc::FFVar n_g_1_59 = - g_1_59;
    mc::FFVar g_1_60 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    mc::FFVar n_g_1_60 = - g_1_60;


    mc::FFVar g_1_61 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    mc::FFVar n_g_1_61 = - g_1_61;
    mc::FFVar g_1_62 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    mc::FFVar n_g_1_62 = - g_1_62;
    mc::FFVar g_1_63 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    mc::FFVar n_g_1_63 = - g_1_63;
    mc::FFVar g_1_64 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    mc::FFVar n_g_1_64 = - g_1_64;
    mc::FFVar g_1_65 = X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    mc::FFVar n_g_1_65 = - g_1_65;
    mc::FFVar g_1_66 = X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    mc::FFVar n_g_1_66 = - g_1_66;
    mc::FFVar g_1_67 = X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    mc::FFVar n_g_1_67 = - g_1_67;
    mc::FFVar g_1_68 = X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    mc::FFVar n_g_1_68 = - g_1_68;
    mc::FFVar g_1_69 = X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    mc::FFVar n_g_1_69 = - g_1_69;
    mc::FFVar g_1_70 = X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    mc::FFVar n_g_1_70 = - g_1_70;
    mc::FFVar g_1_71 = X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    mc::FFVar n_g_1_71 = - g_1_71;
    mc::FFVar g_1_72 = X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    mc::FFVar n_g_1_72 = - g_1_72;
    mc::FFVar g_1_73 = X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    mc::FFVar n_g_1_73 = - g_1_73;
    mc::FFVar g_1_74 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[4]"]] - (0.009147927746696273*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.009050097541352423*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.008440267155692963*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.019869525229591227*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.011493397614084631*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.005699085288896173*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.015431771488609266*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.012736305433586925*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.01592750558065944*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.011435655609155597*X[this->first_stage_map["CrudeQuantity[10]"]]);
    mc::FFVar n_g_1_74 = - g_1_74;
    mc::FFVar g_1_75 = 0.09*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[4]"]];
    mc::FFVar n_g_1_75 = - g_1_75;
    mc::FFVar g_1_76 = 0.12*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[4]"]];
    mc::FFVar n_g_1_76 = - g_1_76;
    mc::FFVar g_1_77 = 0.053*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] - X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[4]"]];
    mc::FFVar n_g_1_77 = - g_1_77;
    mc::FFVar g_1_78 = 0.046*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[4]"]];
    mc::FFVar n_g_1_78 = - g_1_78;
    mc::FFVar g_1_79 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
    mc::FFVar n_g_1_79 = - g_1_79;
    mc::FFVar g_1_80 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
    mc::FFVar n_g_1_80 = - g_1_80;


    mc::FFVar g_1_81 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
    mc::FFVar n_g_1_81 = - g_1_81;
    mc::FFVar g_1_82 = X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[4]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[4]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[4]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[4]"]] + X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[4]"]] - X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
    mc::FFVar n_g_1_82 = - g_1_82;
    mc::FFVar g_1_83 = X[n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] + X[n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] + X[n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] + X[n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] + X[n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] - 1.0;
    mc::FFVar n_g_1_83 = - g_1_83;
    mc::FFVar g_1_84 = -(-0.45*X[n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 0.8552631578947368*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 0.6015037593984962*X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 1.2307692307692308*X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 0.6493506493506493*X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 0.625*X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 0.8666666666666667*X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 7.413793103448276*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 7.379310344827587*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 7.517241379310346*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 7.258620689655173*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 7.275862068965517*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]]);
    mc::FFVar g_1_85 = -0.8*X[n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 0.8552631578947368*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 0.6015037593984962*X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 1.2307692307692308*X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 0.6493506493506493*X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 0.625*X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 0.8666666666666667*X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 7.413793103448276*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 7.379310344827587*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 7.517241379310346*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 7.258620689655173*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 7.275862068965517*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]];
    mc::FFVar g_1_86 = -(-0.5*X[n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 0.8227848101265822*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 0.6015037593984962*X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 1.2307692307692308*X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 0.6493506493506493*X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 0.625*X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 0.8666666666666667*X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 7.413793103448276*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 7.379310344827587*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 7.517241379310346*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 7.258620689655173*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 7.275862068965517*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]]);
    mc::FFVar g_1_87 = -0.86*X[n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 0.8227848101265822*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 0.6015037593984962*X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 1.2307692307692308*X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 0.6493506493506493*X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 0.625*X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 0.8666666666666667*X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 7.413793103448276*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 7.379310344827587*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 7.517241379310346*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 7.258620689655173*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 7.275862068965517*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]];
    mc::FFVar g_1_88 = -(-98*X[n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 132.91139240506328*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 136.8421052631579*X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 109.23076923076923*X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 123.37662337662337*X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 125.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 124.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 160.34482758620692*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 159.48275862068968*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 161.3793103448276*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 159.82758620689657*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 161.89655172413796*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]]);
    mc::FFVar g_1_89 = -(-95*X[n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 131.57894736842104*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 136.8421052631579*X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 109.23076923076923*X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 123.37662337662337*X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 125.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 124.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 160.34482758620692*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 159.48275862068968*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 161.3793103448276*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 159.82758620689657*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 161.89655172413796*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]]);
    mc::FFVar g_1_90 = -10*X[n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 6.329113924050633*X[n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 7.518796992481203*X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 4.615384615384615*X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 11.688311688311687*X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 11.25*X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 14.666666666666666*X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 5.172413793103448*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 5.00000000000001*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 4.6551724137930846*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 6.379310344827592*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 6.379310344827592*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]];

    mc::FFVar g_1_91 = -10*X[n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 5.2631578947368425*X[n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 7.518796992481203*X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 4.615384615384615*X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 11.688311688311687*X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 11.25*X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 14.666666666666666*X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 5.172413793103448*X[n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 5.00000000000001*X[n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 4.6551724137930846*X[n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 6.379310344827592*X[n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 6.379310344827592*X[n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]];
    mc::FFVar g_1_92 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
    mc::FFVar n_g_1_92 = - g_1_92;
    mc::FFVar g_1_93 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]];
    mc::FFVar n_g_1_93 = - g_1_93;
    mc::FFVar g_1_94 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]];
    mc::FFVar n_g_1_94 = - g_1_94;
    mc::FFVar g_1_95 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
    mc::FFVar n_g_1_95 = - g_1_95;
    mc::FFVar g_1_96 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]];
    mc::FFVar n_g_1_96 = - g_1_96;
    mc::FFVar g_1_97 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] - X[n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] * X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]];
    mc::FFVar n_g_1_97 = - g_1_97;
    mc::FFVar g_1_98 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] - 0.446*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]];
    mc::FFVar n_g_1_98 = - g_1_98;
    mc::FFVar g_1_99 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] - 0.511*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]];
    mc::FFVar n_g_1_99 = - g_1_99;
    mc::FFVar g_1_100 = X[n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] + X[n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] - 1.0;
    mc::FFVar n_g_1_100 = - g_1_100;

    mc::FFVar g_1_101 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] - X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
    mc::FFVar n_g_1_101 = - g_1_101;
    mc::FFVar g_1_102 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]] - X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]];
    mc::FFVar n_g_1_102 = - g_1_102;
    mc::FFVar g_1_103 = X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] + X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] - X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]];
    mc::FFVar n_g_1_103 = - g_1_103;
    mc::FFVar g_1_104 = -X[n_first_stage_vars + this->second_stage_map["volume_HF"]] + 1.0204081632653061*X[n_first_stage_vars + this->second_stage_map["flow_Import[5]"]] + 1.0526315789473684*X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]] + 1.0655301012253595*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + 1.175640724194686*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 1.032844453625284*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + 1.1641443538998837*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 1.0612331529236974*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + 1.188636633781053*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 1.060108131029365*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + 1.183431952662722*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 1.0360547036883547*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + 1.166452816983553*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 1.0280662074637608*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + 1.1510128913443831*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 1.0559662090813096*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + 1.1899095668729176*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 1.020512297173181*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + 1.1810558639423645*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 1.0458063166701526*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + 1.1796626164916835*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 1.0325245224574084*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + 1.1684973124561813*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]];
    mc::FFVar n_g_1_104 = - g_1_104;
    mc::FFVar g_1_105 = -(34.629728289824186*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + 2.962614624970609*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 71.88597397231976*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + 3.39930151338766*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 40.53910644168524*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + 3.1023416141685485*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 45.26661719495389*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + 3.0295857988165684*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 89.61873186904269*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + 3.0910999650064155*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 77.61899866351393*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + 3.39548802946593*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 44.66737064413939*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + 2.974773917182294*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 45.92305337279314*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + 2.9644502184953345*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 55.95063794185317*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + 3.0907160552082105*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 56.99535363964894*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + 3.119887824258004*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] + (12.2*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + 11.65*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]])/0.95 - 30*X[n_first_stage_vars + this->second_stage_map["volume_HF"]]);
    mc::FFVar g_1_106 = 34.629728289824186*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + 2.962614624970609*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 71.88597397231976*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + 3.39930151338766*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 40.53910644168524*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + 3.1023416141685485*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 45.26661719495389*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + 3.0295857988165684*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 89.61873186904269*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + 3.0910999650064155*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 77.61899866351393*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + 3.39548802946593*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 44.66737064413939*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + 2.974773917182294*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 45.92305337279314*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + 2.9644502184953345*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 55.95063794185317*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + 3.0907160552082105*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 56.99535363964894*X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + 3.119887824258004*X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] + (12.2*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + 11.65*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]])/0.95 - 33*X[n_first_stage_vars + this->second_stage_map["volume_HF"]];
    mc::FFVar g_1_107 = -0.0015*X[n_first_stage_vars + this->second_stage_map["flow_Import[4]"]] + 0.140588513077039*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[1]"]] - 0.000789557434614805*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[1]"]] + 0.309219599235616*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[2]"]] + 5.3597996178079976e-05*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[2]"]] + 0.16502807856732*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[3]"]] - 0.0006673596071634*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[3]"]] + 0.211405808207417*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[4]"]] - 0.000435470958962915*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[4]"]] + 0.264982491043895*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[5]"]] - 0.00016758754478052502*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[5]"]] + 0.7602297836086701*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[6]"]] + 0.0023086489180433505*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[6]"]] + 0.632862056891616*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[7]"]] + 0.0016718102844580796*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[7]"]] + 1.575235109424405*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[8]"]] + 0.006383675547122027*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[8]"]] + 0.289990315101932*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[9]"]] - 4.2548424490339905e-05*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[9]"]] + 1.087848038245218*X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[10]"]] + 0.003946740191226091*X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[10]"]] + 0.0985*X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[1]"]] + 1.6784999999999999*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] + 2.0985*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] + 0.0084*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] + 0.0105*X[n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] - 0.0015*X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[3]"]];
    mc::FFVar g_1_108 = -(1.3*X[n_first_stage_vars + this->second_stage_map["flow_Burn[1]"]] + 1.2*X[n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]] + 1.1*X[n_first_stage_vars + this->second_stage_map["flow_Burn[3]"]] - 0.019*X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] - 0.026*X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - 0.007*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] - 0.007*X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - 0.04*X[n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] - 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - 15.2 - (0.018*X[this->first_stage_map["CrudeQuantity[1]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[2]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[3]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[4]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[5]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[6]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[7]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[8]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[9]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] + 0.018*X[this->first_stage_map["CrudeQuantity[10]"]] + 0.02*X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]]));
    mc::FFVar g_1_109 = X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - 175;
    mc::FFVar g_1_110 = X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - 65;


    mc::FFVar objective=0.2 * (
        /* global flows (t = 1) */
        3.2 * X[n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]]
        + 3.0 * X[n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]]
        + 2.7 * X[n_first_stage_vars + this->second_stage_map["flow_Reformer95"]]
        + 3.2 * X[n_first_stage_vars + this->second_stage_map["flow_Reformer100"]]
        + 6.0 * X[n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]]
        + 3.345671410129097 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]]

        - 561.6 *
            X[n_first_stage_vars + this->second_stage_map["flow_LG_producing"]]
        - 1003.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_LN_producing"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_2"]]

        /* crude 1 */
        + 2.3942543643299556 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[1]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[1]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]]
        + 864.3999526122498 *
            X[this->first_stage_map["CrudeQuantity[1]"]]

        /* crude 2 */
        + 2.485328036981826 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[2]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[2]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]]
        + 765.9539842873176 *
            X[this->first_stage_map["CrudeQuantity[2]"]]

        /* crude 3 */
        + 2.437662761144984 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[3]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[3]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]]
        + 824.9058168463453 *
            X[this->first_stage_map["CrudeQuantity[3]"]]

        /* crude 4 */
        + 2.4589973078611767 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[4]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[4]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]]
        + 839.5184609869758 *
            X[this->first_stage_map["CrudeQuantity[4]"]]

        /* crude 5 */
        + 2.460163454262119 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[5]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[5]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]]
        + 779.3929097293013 *
            X[this->first_stage_map["CrudeQuantity[5]"]]

        /* crude 6 */
        + 2.760038638583934 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[6]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[6]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]]
        + 692.8115942028985 *
            X[this->first_stage_map["CrudeQuantity[6]"]]

        /* crude 7 */
        + 2.7649237751065976 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[7]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[7]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]]
        + 878.862094037809 *
            X[this->first_stage_map["CrudeQuantity[7]"]]

        /* crude 8 */
        + 3.39343900683156 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[8]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[8]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]]
        + 735.8113207547168 *
            X[this->first_stage_map["CrudeQuantity[8]"]]

        /* crude 9 */
        + 2.5052287966283195 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[9]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[9]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]]
        + 810.2870478413071 *
            X[this->first_stage_map["CrudeQuantity[9]"]]

        /* crude 10 */
        + 3.025222449696517 *
            X[n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_1[10]"]]
        - 907.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_AGO_2[10]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]]
        - 637.0 *
            X[n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]]
        + 749.7063627084043 *
            X[this->first_stage_map["CrudeQuantity[10]"]]

        /* product penalties (t = 1) */
        - 1231.0 *
            ( X[n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] )

        - 1194.0 *
            ( X[n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] )

        - 923.0 *
            ( X[n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] )

        - 907.0 *
            ( X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[1]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]]
            + X[n_first_stage_vars + this->second_stage_map["flow_AGO_3[3]"]] )
    );
    
    std::vector<mc::FFVar> F = {
        g_0_0,g_0_1,g_0_2,g_0_3,g_0_4,g_0_5,g_0_6,g_0_7,g_0_8,g_0_9,g_0_10,
        g_0_11,g_0_12,g_0_13,g_0_14,g_0_15,
        g_0_16,g_0_17,g_0_18,g_0_19,g_0_20, 

        g_1_0,g_1_1,g_1_2,g_1_3,g_1_4,g_1_5,g_1_6,g_1_7,g_1_8,g_1_9,g_1_10,g_1_11,g_1_12,g_1_13,g_1_14,g_1_15,g_1_16,g_1_17,g_1_18,g_1_19,g_1_20,
        n_g_1_1,n_g_1_2,n_g_1_3,n_g_1_4,n_g_1_5,n_g_1_6,n_g_1_7,n_g_1_8,n_g_1_9,n_g_1_10,n_g_1_11,n_g_1_12,n_g_1_13,n_g_1_14,n_g_1_15,n_g_1_16,
        n_g_1_17,n_g_1_18,n_g_1_19,n_g_1_20,


        g_1_21,g_1_22,g_1_23,g_1_24,g_1_25,g_1_26,g_1_27,g_1_28,g_1_29,g_1_30,g_1_31,g_1_32,g_1_33,g_1_34,g_1_35,g_1_36,g_1_37,g_1_38,g_1_39,g_1_40,
        n_g_1_21,n_g_1_22,n_g_1_23,n_g_1_24,n_g_1_25,n_g_1_26,n_g_1_27,n_g_1_28,n_g_1_29,n_g_1_30,n_g_1_31,n_g_1_32, n_g_1_33, n_g_1_34, n_g_1_35,n_g_1_36,n_g_1_37,n_g_1_38,n_g_1_39,n_g_1_40,
        
        g_1_41,g_1_42,g_1_43,g_1_44,g_1_45,g_1_46,g_1_47,g_1_48,g_1_49,g_1_50,g_1_51,g_1_52,g_1_53,g_1_54,g_1_55,g_1_56,g_1_57,g_1_58,g_1_59,g_1_60,
        n_g_1_41,n_g_1_42,n_g_1_50,n_g_1_51,n_g_1_54,n_g_1_55,n_g_1_56,n_g_1_57,n_g_1_58,n_g_1_59,n_g_1_60,

        g_1_61,g_1_62,g_1_63,g_1_64,g_1_65,g_1_66,g_1_67,g_1_68,g_1_69,g_1_70,g_1_71,g_1_72,g_1_73,g_1_74,g_1_75,g_1_76,g_1_77,g_1_78,g_1_79,g_1_80,
        n_g_1_61,n_g_1_62,n_g_1_63,n_g_1_64,n_g_1_65,n_g_1_66,n_g_1_67,n_g_1_68,n_g_1_69,n_g_1_70,n_g_1_71,n_g_1_72,n_g_1_73,n_g_1_74,n_g_1_75,n_g_1_76,n_g_1_77,n_g_1_78,n_g_1_79,n_g_1_80,

        g_1_81,g_1_82,g_1_83,g_1_84,g_1_85,g_1_86,g_1_87,g_1_88,g_1_89,g_1_90,
        g_1_91,g_1_92,g_1_93,g_1_94,g_1_95,
        g_1_96,g_1_97,g_1_98,g_1_99,g_1_100,
        n_g_1_81,n_g_1_82,n_g_1_83,
        n_g_1_92,n_g_1_93,n_g_1_94,n_g_1_95,
        n_g_1_96,n_g_1_97,n_g_1_98,n_g_1_99,n_g_1_100,
        
        g_1_101,g_1_102,g_1_103,g_1_104,g_1_105,g_1_106,g_1_107,g_1_108,g_1_109,g_1_110,
        n_g_1_101,n_g_1_102,n_g_1_103,n_g_1_104,
        
        objective};
    grbmodel->set(GRB_DoubleParam_MIPGap, 0.00001);

    for (int i = 0; i < n_first_stage_vars; ++i) {
        grbmodel->addVar(this->first_stage_IX[i].l(), this->first_stage_IX[i].u(), 0.0, GRB_CONTINUOUS, ("x" + std::to_string(i)));
    }
    for (int i = 0; i < n_second_stage_vars; ++i) {
        grbmodel->addVar(this->second_stage_IX[i].l(), this->second_stage_IX[i].u(), 0.0, GRB_CONTINUOUS, ("x" + std::to_string(i+n_first_stage_vars)));
    }

    grbmodel->update();

    for (int i = 0; i < F.size(); ++i) {
            mc::FFSubgraph subgraph = DAG.subgraph(std::vector<mc::FFVar> {F[i]});
            for (auto op : subgraph.l_op) {
                if (op->varin.size()==0) continue;
                if (op->varout[0]->id().first == mc::FFVar::CINT || op->varout[0]->id().first == mc::FFVar::CREAL || op->varout[0]->id().first == mc::FFVar::VAR) continue;
                // now we have an aux variable as output
                if (op->varout[0]->id().second == F[i].id().second) { //if either object or constraint
                    if (i == F.size()-1) { // objective
                        grbmodel->addVar(-GRB_INFINITY, GRB_INFINITY, 1.0, GRB_CONTINUOUS, "aux_"+std::to_string(op->varout[0]->id().second));
                    } else {
                        grbmodel->addVar(-GRB_INFINITY, 0, 0.0, GRB_CONTINUOUS, "aux_"+std::to_string(op->varout[0]->id().second)); // this is final output
                    }
                    grbmodel->update();
                }else{
                    grbmodel->addVar(-GRB_INFINITY, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "aux_"+std::to_string(op->varout[0]->id().second));
                    grbmodel->update();
                }
                if (op->varin.size()==1){ // one input -> one output aux var
                    // check if power then need speical handle

                    std::vector<int >opcode1;
                    opcode1.push_back(this->map_ffop_to_grb(op->type));

                    std::vector<double> data1;
                    data1.push_back(-1.0);

                    std::vector<int> parent1;
                    parent1.push_back(-1); 

                    switch (op->varin[0]->id().first){
                        case mc::FFVar::VAR:
                            data1.push_back(grbmodel->getVarByName("x"+std::to_string(op->varin[0]->id().second)).index());
                            opcode1.push_back(GRB_OPCODE_VARIABLE);
                            parent1.push_back(0);

                        break;
                        case mc::FFVar::AUX:
                            data1.push_back(grbmodel->getVarByName("aux_"+std::to_string(op->varin[0]->id().second)).index());
                            opcode1.push_back(GRB_OPCODE_VARIABLE);
                            parent1.push_back(0);
                        break;
                        case mc::FFVar::CINT:
                            data1.push_back(op->varin[0]->num().val());
                            opcode1.push_back(GRB_OPCODE_CONSTANT);
                            parent1.push_back(0);
                        break;
                        case mc::FFVar::CREAL:
                            data1.push_back(op->varin[0]->num().val());
                            opcode1.push_back(GRB_OPCODE_CONSTANT);
                            parent1.push_back(0);
                        break;
                        default:
                            throw std::runtime_error("Unsupported input var type for NL constraint");
                    }
                    if (op->type==mc::FFOp::SQR){
                        data1.push_back(2.0); // exponent 2 for SQR
                        opcode1.push_back(GRB_OPCODE_CONSTANT);
                        parent1.push_back(0);
                    }
                    grbmodel->addGenConstrNL(
                        grbmodel->getVarByName("aux_"+std::to_string(op->varout[0]->id().second)),
                        data1.size(),
                        opcode1.data(),
                        data1.data(),
                        parent1.data());
                    grbmodel->update();

                }
                else{ // two input -> one output aux var
                    std::vector<int >opcode2;
                    opcode2.push_back(this->map_ffop_to_grb(op->type));

                    std::vector<double> data2;
                    data2.push_back(-1.0); 

                    std::vector<int> parent2;
                    parent2.push_back(-1);


                    switch (op->varin[0]->id().first){
                        case mc::FFVar::VAR:
                            data2.push_back(grbmodel->getVarByName("x"+std::to_string(op->varin[0]->id().second)).index());
                            opcode2.push_back(GRB_OPCODE_VARIABLE);
                            parent2.push_back(0);

                        break;
                        case mc::FFVar::AUX:
                            data2.push_back(grbmodel->getVarByName("aux_"+std::to_string(op->varin[0]->id().second)).index());
                            opcode2.push_back(GRB_OPCODE_VARIABLE);
                            parent2.push_back(0);

                        break;
                        case mc::FFVar::CINT:
                            data2.push_back(op->varin[0]->num().val());
                            opcode2.push_back(GRB_OPCODE_CONSTANT);
                            parent2.push_back(0);
                        break;
                        case mc::FFVar::CREAL:
                            data2.push_back(op->varin[0]->num().val());
                            opcode2.push_back(GRB_OPCODE_CONSTANT);
                            parent2.push_back(0);
                        break;
                        default:
                            throw std::runtime_error("Unsupported input var type for NL constraint");
                    }
                    switch (op->varin[1]->id().first){
                        case mc::FFVar::VAR:
                            data2.push_back(grbmodel->getVarByName("x"+std::to_string(op->varin[1]->id().second)).index());
                            opcode2.push_back(GRB_OPCODE_VARIABLE);
                            parent2.push_back(0);
                        break;
                        case mc::FFVar::AUX:
                            data2.push_back(grbmodel->getVarByName("aux_"+std::to_string(op->varin[1]->id().second)).index());
                            opcode2.push_back(GRB_OPCODE_VARIABLE);
                            parent2.push_back(0);
                        break;
                        case mc::FFVar::CINT:
                            data2.push_back(op->varin[1]->num().val());
                            opcode2.push_back(GRB_OPCODE_CONSTANT);
                            parent2.push_back(0);
                        break;
                        case mc::FFVar::CREAL:
                            data2.push_back(op->varin[1]->num().val());
                            opcode2.push_back(GRB_OPCODE_CONSTANT);
                            parent2.push_back(0);
                        break;
                        default:
                            throw std::runtime_error("Unsupported input var type for NL constraint");
                    }
                    grbmodel->addGenConstrNL(
                        grbmodel->getVarByName("aux_"+std::to_string(op->varout[0]->id().second)),
                        data2.size(),
                        opcode2.data(),
                        data2.data(),
                        parent2.data());
                    grbmodel->update();
                }

            }
    }
    grbmodel->write("model.lp");
}
void CrudeModel::generateFullLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) {};
Ipopt::SmartPtr<STModel> CrudeModel::clone(){
    Ipopt::SmartPtr<CrudeModel> p = new CrudeModel();

    p->scenario_name=this->scenario_name;
    p->first_stage_IX=this->first_stage_IX;
    p->second_stage_IX=this->second_stage_IX;

    p->scenario_names=this->scenario_names;
    p->generateIpoptModel();
};
void CrudeModel::generateIpoptModel() {
    int a1 = 0;
};

bool CrudeModel::get_nlp_info(
            Ipopt::Index& n,
            Ipopt::Index& m,
            Ipopt::Index& nnz_jac_g,
            Ipopt::Index& nnz_h_lag,
            Ipopt::TNLP::IndexStyleEnum& index_style
        )
{   


    // number of variables
    n = this->first_stage_IX.size() + this->second_stage_IX.size();

    // one equality constraint and one inequality constraint
    m = this->F.size()-1; // w

    // in this example the jacobian is dense and contains 8 nonzeros
    nnz_jac_g = n*m;

    // the Hessian is also dense and has 16 total nonzeros, but we
    // only need the lower left corner (since it is symmetric)
    nnz_h_lag = 0;

    // use the C style indexing (0-based)
    index_style = TNLP::C_STYLE;
    return true;
};
bool CrudeModel::get_bounds_info(
            Ipopt::Index   n,
            Ipopt::Number* x_l,
            Ipopt::Number* x_u,
            Ipopt::Index   m,
            Ipopt::Number* g_l,
            Ipopt::Number* g_u
        )
{
    assert(n == (Ipopt::Index)(this->first_stage_IX.size()+this->second_stage_IX.size()));
    assert(m == (Ipopt::Index)(F.size()-1));
    // the variables have lower bounds of 1
    for( Ipopt::Index i = 0; i < this->first_stage_IX.size(); i++ )
    {
        x_l[i] = this->first_stage_IX[i].l(); // for first stage variables
        x_u[i] = this->first_stage_IX[i].u();
    }
    for( Ipopt::Index i = 0; i < this->second_stage_IX.size(); i++ )
    {
        x_l[i + this->first_stage_IX.size()] = this->second_stage_IX[i].l(); // for second stage variables
        x_u[i + this->first_stage_IX.size()] = this->second_stage_IX[i].u(); // for second stage variables
    }
    for (Ipopt::Index i = 0; i < m; ++i) {
        g_l[i] = -2e19;
        g_u[i] = 0.0;
    }


    return true;
}

bool CrudeModel::get_starting_point(
            Ipopt::Index   n,
            bool    init_x,
            Ipopt::Number* x,
            bool    init_z,
            Ipopt::Number* z_L,
            Ipopt::Number* z_U,
            Ipopt::Index   m,
            bool    init_lambda,
            Ipopt::Number* lambda
        ) 
{

    // initialize to the given starting point
    for (Ipopt::Index i = 0; i < this->first_stage_IX.size(); ++i) {
        x[i] =0.5*(this->first_stage_IX[i].l() + this->first_stage_IX[i].u()); // for first stage variables
    }
    for (Ipopt::Index i = 0; i < this->second_stage_IX.size(); ++i) {
        x[i + this->first_stage_IX.size()] =0.5*(this->second_stage_IX[i].l() + this->second_stage_IX[i].u()); // for second stage variables
    }

    return true;
};
bool CrudeModel::eval_f(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Number&       obj_value
        )
{


    mc::FFSubgraph   op_f= this->DAG.subgraph(std::vector<mc::FFVar> {F[0]});
    std::vector<double> dwk;
    std::vector<mc::FFVar>  Fvar;

    this->DAG.eval(op_f, dwk, 1, &(F[0]), &obj_value,
             n,this->X.data(), x);

    return true;
};
bool CrudeModel::eval_grad_f(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Number*       grad_f
        )
{
    std::vector<fadbad::B<double>> BXval(n);
    fadbad::B<double>   BCval;
    std::vector<fadbad::B<double>> Bwk;
    mc::FFSubgraph   op_f= this->DAG.subgraph(std::vector<mc::FFVar> {F[0]});
    for( Ipopt::Index i=0; i<n; i++ ){
          BXval[i] = x[i];
    }
    this->DAG.eval( op_f, Bwk, 1, &(F[0]), &BCval, n, this->X.data(), BXval.data() );
        
    Bwk.clear();
    BCval.diff( 0, 1 );
    // Gather derivatives
    for( Ipopt::Index i=0; i<n; i++ ){
        grad_f[i] = BXval[i].d(0);
    }
    return true;
};
bool CrudeModel::eval_g(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Index         m,
            Ipopt::Number*       g
        )
{
    std::vector<double> dwk;
    mc::FFSubgraph   op_g= this->DAG.subgraph(m,this->F.data()+1);
    // skipping the first one since it's the objective
    this->DAG.eval( op_g, dwk, m, this->F.data()+1, g, n, this->X.data(), x );

    return true;
}
bool CrudeModel::eval_jac_g(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Index         m,
            Ipopt::Index         nele_jac,
            Ipopt::Index*        iRow,
            Ipopt::Index*        jCol,
            Ipopt::Number*       values
        ) 
{

    // Dense pattern: row-major (constraint-major)
    if (values == nullptr) {
        Ipopt::Index k = 0;
        for (Ipopt::Index row = 0; row < m; ++row) {
            for (Ipopt::Index col = 0; col < n; ++col) {
                iRow[k] = row;
                jCol[k] = col;
                ++k;
            }
        }
        assert(k == nele_jac);
        return true;
    }
    std::vector<fadbad::B<double>> BXval(n);
    std::vector<fadbad::B<double>> BFval(m);
    fadbad::B<double>   BCval;
    std::vector<fadbad::B<double>> Bwk;
    mc::FFSubgraph   op_g= this->DAG.subgraph(m,this->F.data()+1);

    // Initialize participating variables in fadbad::B<double>
    for( Ipopt::Index i=0; i<n; i++ ){
        BXval[i] = x[i];
    }

    this->DAG.eval( op_g, Bwk, m, this->F.data()+1, BFval.data(), n, this->X.data(), BXval.data() );

    Bwk.clear();
    for( Ipopt::Index j=0; j<m; j++ ){
        BFval[j].diff( j, m );
    }
    // Gather derivatives

    for (Ipopt::Index row=0; row<m; ++row) {
        BFval[row].diff(row, m);
    }
    Ipopt::Index k = 0;
    for (Ipopt::Index row = 0; row < m; ++row) {
        for (Ipopt::Index col = 0; col < n; ++col) {
            values[k++] = BXval[col].d(row);   // <-- key
        }
    }
    return true;

};
void CrudeModel::finalize_solution(
        Ipopt::SolverReturn               status,
        Ipopt::Index                      n,
        const Ipopt::Number*              x,
        const Ipopt::Number*              z_L,
        const Ipopt::Number*              z_U,
        Ipopt::Index                      m,
        const Ipopt::Number*              g,
        const Ipopt::Number*              lambda,
        Ipopt::Number                     obj_value,
        const Ipopt::IpoptData*           ip_data,
        Ipopt::IpoptCalculatedQuantities* ip_cq
    ) 
{
    std::vector<double> Pval;
    this->solution.stat    = status;
    this->solution.p       = Pval;
    this->solution.x.assign( x, x+n );
    this->solution.ux.resize( n );
    for( int i=0; i<n; i++ ) this->solution.ux[i] = z_L[i] - z_U[i];  
    this->solution.f.assign( 1, obj_value );
    this->solution.f.insert( this->solution.f.end() , g, g+m );
    this->solution.uf.assign( 1, -1. );
    this->solution.uf.resize( m+1 );
    for( int j=0; j<m; j++ ) this->solution.uf[1+j] = - lambda[j];
};