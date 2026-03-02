#include "example/CrudeModel.h"
CrudeModel::CrudeModel(BranchingStrategy branching_strategy):STModel() {

    this->branching_strategy = branching_strategy;
    this->scenario_names = {ScenarioNames::SCENARIO1
        , ScenarioNames::SCENARIO2, ScenarioNames::SCENARIO3
        , ScenarioNames::SCENARIO4, ScenarioNames::SCENARIO5
    };
    this->scenario_name = ScenarioNames::SCENARIO1; //default
    this->probability = 0.2; //default


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
    this->second_stage_IX = {

        mc::Interval(0.0, 700.0), //0:blin_AGO_LG[1]
        mc::Interval(0.0, 700.0), //1:blin_AGO_LG[2]
        mc::Interval(0.0, 700.0), //2:blin_AGO_LG[3]
        mc::Interval(0.0, 700.0), //3:blin_AGO_LG[4]
        mc::Interval(0.0, 700.0), //4:blin_CDU_LG[1]
        mc::Interval(0.0, 700.0), //5:blin_CDU_LG[2]
        mc::Interval(0.0, 700.0), //6:blin_CDU_LG[3]
        mc::Interval(0.0, 700.0), //7:blin_CDU_LG[4]

        mc::Interval(0.0, 175.0), //8:blin_Cracker_AGO[1]
        mc::Interval(0.0, 175.0), //9:blin_Cracker_AGO[2]
        mc::Interval(0.0, 175.0), //10:blin_Cracker_AGO[3]
        mc::Interval(0.0, 175.0), //11:blin_Cracker_Mogas[1]
        mc::Interval(0.0, 175.0), //12:blin_Cracker_Mogas[2]
        mc::Interval(0.0, 175.0), //13:blin_Cracker_Mogas[3]

        mc::Interval(0.0, 700.0), //14:blin_Mogas_LG[1]
        mc::Interval(0.0, 700.0), //15:blin_Mogas_LG[2]
        mc::Interval(0.0, 700.0), //16:blin_Mogas_LG[3]
        mc::Interval(0.0, 700.0), //17:blin_Mogas_LG[4]
        mc::Interval(0.0, 700.0), //18:blin_AGO_LG[19]
        mc::Interval(0.0, 700.0), //19:blin_AGO_LG[20]
        mc::Interval(0.0, 700.0), //20:blin_AGO_LG[21]
        mc::Interval(0.0, 700.0), //21:blin_AGO_LG[22]
        mc::Interval(0.0, 700.0), //22:blin_AGO_LG[23]
        mc::Interval(0.0, 700.0), //23:blin_AGO_LG[24]
        mc::Interval(0.0, 700.0), //24:blin_AGO_LG[25]
        mc::Interval(0.0, 700.0), //25:blin_AGO_LG[26]
        mc::Interval(0.0, 201.29570747217807), //26:blin_AGO_LG[27]
        mc::Interval(0.0, 212.48012718600953), //27:blin_AGO_LG[28]
        mc::Interval(0.0, 201.29570747217807), //28:blin_AGO_LG[29]
        mc::Interval(0.0, 199.57869634340224), //29:blin_AGO_LG[30]
        mc::Interval(0.0, 210.54848966613673), //30:blin_AGO_LG[31]
        mc::Interval(0.0, 222.1383147853736), //31:blin_AGO_LG[32]
        mc::Interval(0.0, 196.7885532591415), //32:blin_AGO_LG[33]
        mc::Interval(0.0, 208.54531001589828), //33:blin_AGO_LG[34]
        mc::Interval(0.0, 204.3720190779014), //34:blin_AGO_LG[35]
        mc::Interval(0.0, 210.2623211446741), //35:blin_AGO_LG[36]


        mc::Interval(0.0, 125.0), //36:flow_AGO_2[1]
        mc::Interval(0.0, 125.0), //37:flow_AGO_2[2]
        mc::Interval(0.0, 125.0), //38:flow_AGO_2[3]
        mc::Interval(0.0, 125.0), //39:flow_AGO_2[4]
        mc::Interval(0.0, 125.0), //40:flow_AGO_2[5]
        mc::Interval(0.0, 125.0), //41:flow_AGO_2[6]
        mc::Interval(0.0, 125.0), //42:flow_AGO_2[7]
        mc::Interval(0.0, 125.0), //43:flow_AGO_2[8]
        mc::Interval(0.0, 125.0), //44:flow_AGO_2[9]
        mc::Interval(0.0, 125.0), //45:flow_AGO_2[10]

        mc::Interval(0.0, 700.0), //46:blin_AGO_3[1]
        mc::Interval(0.0, 175.0), //47:blin_AGO_3[2]
        mc::Interval(0.0, 175.0), //48:blin_AGO_3[3]

        mc::Interval(0.0, 700.0), //49:flow_Burn[1]
        mc::Interval(0.0, 700.0), //50:flow_Burn[2]
        mc::Interval(0.0, 700.0), //51:flow_Burn[3]

        mc::Interval(0.0, 175.0), //52:flow_Cracker_AGO
        mc::Interval(0.0, 175.0), //53:flow_Cracker_Mogas

        mc::Interval(0.0, 125.0), //54:flow_Desulphurisation_1[1]
        mc::Interval(0.0, 125.0), //55:flow_Desulphurisation_1[2]
        mc::Interval(0.0, 125.0), //56:flow_Desulphurisation_1[3]
        mc::Interval(0.0, 125.0), //57:flow_Desulphurisation_1[4]
        mc::Interval(0.0, 125.0), //58:flow_Desulphurisation_1[5]
        mc::Interval(0.0, 125.0), //59:flow_Desulphurisation_1[6]
        mc::Interval(0.0, 125.0), //60:flow_Desulphurisation_1[7]
        mc::Interval(0.0, 125.0), //61:flow_Desulphurisation_1[8]
        mc::Interval(0.0, 125.0), //62:flow_Desulphurisation_1[9]
        mc::Interval(0.0, 125.0), //63:flow_Desulphurisation_1[10]

        mc::Interval(0.0, 175.0), //64:flow_Desulphurisation_CGO

        mc::Interval(0.0, 700.0), //65:flow_ES95[1]
        mc::Interval(0.0, 700.0), //66:flow_ES95[2]
        mc::Interval(0.0, 700.0), //67:flow_ES95[3]
        mc::Interval(0.0, 700.0), //68:flow_ES95[4]
        mc::Interval(0.0, 700.0), //69:flow_ES95[5]
        mc::Interval(0.0, 700.0), //70:flow_ES95[6]

        mc::Interval(0.0, 201.29570747217807), //71:flow_HF_1[1]
        mc::Interval(0.0, 212.48012718600953), //72:flow_HF_1[2]
        mc::Interval(0.0, 201.29570747217807), //73:flow_HF_1[3]
        mc::Interval(0.0, 199.57869634340224), //74:flow_HF_1[4]
        mc::Interval(0.0, 210.54848966613673), //75:flow_HF_1[5]
        mc::Interval(0.0, 222.1383147853736), //76:flow_HF_1[6]
        mc::Interval(0.0, 196.7885532591415), //77:flow_HF_1[7]
        mc::Interval(0.0, 208.54531001589828), //78:flow_HF_1[8]
        mc::Interval(0.0, 204.3720190779014), //79:flow_HF_1[9]
        mc::Interval(0.0, 210.2623211446741), //80:flow_HF_1[10]

        mc::Interval(0.0, 175.0), //81:flow_HF_2

        mc::Interval(0.0, 201.29570747217807), //82:flow_HF_3[1]
        mc::Interval(0.0, 212.48012718600953), //83:flow_HF_3[2]
        mc::Interval(0.0, 201.29570747217807), //84:flow_HF_3[3]
        mc::Interval(0.0, 199.57869634340224), //85:flow_HF_3[4]
        mc::Interval(0.0, 210.54848966613673), //86:flow_HF_3[5]
        mc::Interval(0.0, 222.1383147853736), //87:flow_HF_3[6]
        mc::Interval(0.0, 196.7885532591415), //88:flow_HF_3[7]
        mc::Interval(0.0, 208.54531001589828), //89:flow_HF_3[8]
        mc::Interval(0.0, 204.3720190779014), //90:flow_HF_3[9]
        mc::Interval(0.0, 210.2623211446741), //91:flow_HF_3[10]

        mc::Interval(0.0, 0.0), //92:flow_Import[1]
        mc::Interval(0.0, 0.0), //93:flow_Import[2]
        mc::Interval(0.0, 0.0), //94:flow_Import[3]
        mc::Interval(0.0, 0.0), //95:flow_Import[4]
        mc::Interval(0.0, 0.0), //96:flow_Import[5]
        mc::Interval(0.0, 0.0), //97:flow_Import[6]
        mc::Interval(0.0, 0.0), //98:flow_Import[7]

        mc::Interval(0.0, 700.0), //99:flow_Isomerisation

        mc::Interval(0.0, 700.0), //100:flow_JPF[1]
        mc::Interval(0.0, 700.0), //101:flow_JPF[2]

        mc::Interval(0.0, 700.0), //102:flow_LG_producing
        mc::Interval(0.0, 700.0), //103:flow_LN_producing

        mc::Interval(0.0, 700.0), //104:flow_PG98[1]
        mc::Interval(0.0, 700.0), //105:flow_PG98[2]
        mc::Interval(0.0, 700.0), //106:flow_PG98[3]
        mc::Interval(0.0, 700.0), //107:flow_PG98[4]
        mc::Interval(0.0, 700.0), //108:flow_PG98[5]
        mc::Interval(0.0, 700.0), //109:flow_PG98[6]

        mc::Interval(0.0, 60.0), //110:flow_Reformer100
        mc::Interval(5.0, 65.0), //110:flow_Reformer95

        mc::Interval(0.0, 1.0), //111:fraction_CGO[1]
        mc::Interval(0.0, 1.0), //112:fraction_CGO[2]

        mc::Interval(0.0, 1.0), //113:fraction_LG[1]
        mc::Interval(0.0, 1.0), //114:fraction_LG[2]
        mc::Interval(0.0, 1.0), //115:fraction_LG[3]
        mc::Interval(0.0, 1.0), //116:fraction_LG[4]
        mc::Interval(0.0, 1.0), //117:fraction_LG[5]

        mc::Interval(0.0,1206.896551724138), //118:volume_ES95
        mc::Interval(0.0,832.9366968110423), //119:volume_HF
        mc::Interval(0.0,1206.896551724138) //120:volume_PG98
    };
    
        // this->first_stage_IX = {
        //     mc::Interval(0.0, 0.0),                                    // crudeQuantity[1]
        //     mc::Interval(0.0, 0.0),                                    // crudeQuantity[2]
        //     mc::Interval(0.0, 0.0),                                    // crudeQuantity[3]
        //     mc::Interval(0.0, 0.0),                                    // crudeQuantity[4]
        //     mc::Interval(0.0, 0.0),                                    // crudeQuantity[5]
        //     mc::Interval(0.0, 0.0),                                    // crudeQuantity[6]
        //     mc::Interval(0.0, 0.0),                                    // crudeQuantity[7]
        //     mc::Interval(0.0, 0.0),                                    // crudeQuantity[8]
        //     mc::Interval(0.0, 0.0),                                    // crudeQuantity[9]
        //     mc::Interval(0.0, 0.0),                                    // crudeQuantity[10]
        //     mc::Interval(0.0, 0.0),                                    // pickCrude[1]
        //     mc::Interval(1.0, 1.0),                                    // pickCrude[2]
        //     mc::Interval(1.0, 1.0),                                    // pickCrude[3]
        //     mc::Interval(1.0, 1.0),                                    // pickCrude[4]
        //     mc::Interval(0.0, 0.0),                                    // pickCrude[5]
        //     mc::Interval(0.0, 0.0),                                    // pickCrude[6]
        //     mc::Interval(0.0, 0.0),                                    // pickCrude[7]
        //     mc::Interval(1.0, 1.0),                                    // pickCrude[8]
        //     mc::Interval(0.0, 0.0),                                    // pickCrude[9]
        //     mc::Interval(1.0, 1.0)                                     // pickCrude[10]
        // };

        // this->second_stage_IX = {
        //     mc::Interval(0.0, 0.0),                                         // 0: blin_AGO_LG[1]
        //     mc::Interval(0.0, 0.0),                                         // 1: blin_AGO_LG[2]
        //     mc::Interval(0.0, 0.0),                                         // 2: blin_AGO_LG[3]
        //     mc::Interval(0.0, 0.0),                                         // 3: blin_AGO_LG[4]
        //     mc::Interval(0.0, 0.0),                                         // 4: blin_CDU_LG[1]
        //     mc::Interval(0.0, 0.0),                                         // 5: blin_CDU_LG[2]
        //     mc::Interval(0.0, 0.0),                                         // 6: blin_CDU_LG[3]
        //     mc::Interval(0.0, 0.0),                                         // 7: blin_CDU_LG[4]
        //     mc::Interval(0.0, 0.0),                                         // 8: blin_Cracker_AGO[1]
        //     mc::Interval(0.0, 0.0),                                         // 9: blin_Cracker_AGO[2]
        //     mc::Interval(0.0, 0.0),                                         // 10: blin_Cracker_AGO[3]
        //     mc::Interval(0.0, 0.0),                                         // 11: blin_Cracker_Mogas[1]
        //     mc::Interval(0.0, 0.0),                                         // 12: blin_Cracker_Mogas[2]
        //     mc::Interval(0.0, 0.0),                                         // 13: blin_Cracker_Mogas[3]
        //     mc::Interval(0.0, 0.0),                                         // 14: blin_Mogas_LG[1]
        //     mc::Interval(0.0, 0.0),                                         // 15: blin_Mogas_LG[2]
        //     mc::Interval(0.0, 0.0),                                         // 16: blin_Mogas_LG[3]
        //     mc::Interval(0.0, 0.0),                                         // 17: blin_Mogas_LG[4]
        //     mc::Interval(0.0, 0.0),                                         // 18: blin_Reformer100_LG[1]
        //     mc::Interval(0.0, 0.0),                                         // 19: blin_Reformer100_LG[2]
        //     mc::Interval(0.0, 0.0),                                         // 20: blin_Reformer100_LG[3]
        //     mc::Interval(0.0, 0.0),                                         // 21: blin_Reformer100_LG[4]
        //     mc::Interval(0.0, 0.0),                                         // 22: blin_Reformer95_LG[1]
        //     mc::Interval(0.0, 0.0),                                         // 23: blin_Reformer95_LG[2]
        //     mc::Interval(0.0, 0.0),                                         // 24: blin_Reformer95_LG[3]
        //     mc::Interval(0.0, 0.0),                                         // 25: blin_Reformer95_LG[4]
        //     mc::Interval(201.29570747217807, 201.29570747217807),           // 26: flow_AGO_1[1]
        //     mc::Interval(212.48012718600953, 212.48012718600953),           // 27: flow_AGO_1[2]
        //     mc::Interval(201.29570747217807, 201.29570747217807),           // 28: flow_AGO_1[3]
        //     mc::Interval(199.57869634340224, 199.57869634340224),           // 29: flow_AGO_1[4]
        //     mc::Interval(210.54848966613673, 210.54848966613673),           // 30: flow_AGO_1[5]
        //     mc::Interval(222.1383147853736, 222.1383147853736),             // 31: flow_AGO_1[6]
        //     mc::Interval(196.7885532591415, 196.7885532591415),             // 32: flow_AGO_1[7]
        //     mc::Interval(208.54531001589828, 208.54531001589828),           // 33: flow_AGO_1[8]
        //     mc::Interval(204.3720190779014, 204.3720190779014),             // 34: flow_AGO_1[9]
        //     mc::Interval(210.2623211446741, 210.2623211446741),             // 35: flow_AGO_1[10]
        //     mc::Interval(125.0, 125.0),                                     // 36: flow_AGO_2[1]
        //     mc::Interval(125.0, 125.0),                                     // 37: flow_AGO_2[2]
        //     mc::Interval(125.0, 125.0),                                     // 38: flow_AGO_2[3]
        //     mc::Interval(125.0, 125.0),                                     // 39: flow_AGO_2[4]
        //     mc::Interval(125.0, 125.0),                                     // 40: flow_AGO_2[5]
        //     mc::Interval(125.0, 125.0),                                     // 41: flow_AGO_2[6]
        //     mc::Interval(125.0, 125.0),                                     // 42: flow_AGO_2[7]
        //     mc::Interval(125.0, 125.0),                                     // 43: flow_AGO_2[8]
        //     mc::Interval(125.0, 125.0),                                     // 44: flow_AGO_2[9]
        //     mc::Interval(125.0, 125.0),                                     // 45: flow_AGO_2[10]
        //     mc::Interval(700.0, 700.0),                                     // 46: flow_AGO_3[1]
        //     mc::Interval(175.0, 175.0),                                     // 47: flow_AGO_3[2]
        //     mc::Interval(175.0, 175.0),                                     // 48: flow_AGO_3[3]
        //     mc::Interval(0.0, 0.0),                                         // 49: flow_Burn[1]
        //     mc::Interval(0.0, 0.0),                                         // 50: flow_Burn[2]
        //     mc::Interval(0.0, 0.0),                                         // 51: flow_Burn[3]
        //     mc::Interval(0.0, 0.0),                                         // 52: flow_Cracker_AGO
        //     mc::Interval(0.0, 0.0),                                         // 53: flow_Cracker_Mogas
        //     mc::Interval(0.0, 0.0),                                         // 54: flow_Desulphurisation_1[1]
        //     mc::Interval(0.0, 0.0),                                         // 55: flow_Desulphurisation_1[2]
        //     mc::Interval(0.0, 0.0),                                         // 56: flow_Desulphurisation_1[3]
        //     mc::Interval(0.0, 0.0),                                         // 57: flow_Desulphurisation_1[4]
        //     mc::Interval(0.0, 0.0),                                         // 58: flow_Desulphurisation_1[5]
        //     mc::Interval(0.0, 0.0),                                         // 59: flow_Desulphurisation_1[6]
        //     mc::Interval(0.0, 0.0),                                         // 60: flow_Desulphurisation_1[7]
        //     mc::Interval(0.0, 0.0),                                         // 61: flow_Desulphurisation_1[8]
        //     mc::Interval(0.0, 0.0),                                         // 62: flow_Desulphurisation_1[9]
        //     mc::Interval(0.0, 0.0),                                         // 63: flow_Desulphurisation_1[10]
        //     mc::Interval(0.0, 0.0),                                         // 64: flow_Desulphurisation_CGO
        //     mc::Interval(700.0, 700.0),                                     // 65: flow_ES95[1]
        //     mc::Interval(700.0, 700.0),                                     // 66: flow_ES95[2]
        //     mc::Interval(700.0, 700.0),                                     // 67: flow_ES95[3]
        //     mc::Interval(700.0, 700.0),                                     // 68: flow_ES95[4]
        //     mc::Interval(700.0, 700.0),                                     // 69: flow_ES95[5]
        //     mc::Interval(700.0, 700.0),                                     // 70: flow_ES95[6]
        //     mc::Interval(201.29570747217807, 201.29570747217807),           // 71: flow_HF_1[1]
        //     mc::Interval(212.48012718600953, 212.48012718600953),           // 72: flow_HF_1[2]
        //     mc::Interval(201.29570747217807, 201.29570747217807),           // 73: flow_HF_1[3]
        //     mc::Interval(199.57869634340224, 199.57869634340224),           // 74: flow_HF_1[4]
        //     mc::Interval(210.54848966613673, 210.54848966613673),           // 75: flow_HF_1[5]
        //     mc::Interval(222.1383147853736, 222.1383147853736),             // 76: flow_HF_1[6]
        //     mc::Interval(196.7885532591415, 196.7885532591415),             // 77: flow_HF_1[7]
        //     mc::Interval(208.54531001589828, 208.54531001589828),           // 78: flow_HF_1[8]
        //     mc::Interval(204.3720190779014, 204.3720190779014),             // 79: flow_HF_1[9]
        //     mc::Interval(210.2623211446741, 210.2623211446741),             // 80: flow_HF_1[10]
        //     mc::Interval(175.0, 175.0),                                     // 81: flow_HF_2
        //     mc::Interval(201.29570747217807, 201.29570747217807),           // 82: flow_HF_3[1]
        //     mc::Interval(212.48012718600953, 212.48012718600953),           // 83: flow_HF_3[2]
        //     mc::Interval(201.29570747217807, 201.29570747217807),           // 84: flow_HF_3[3]
        //     mc::Interval(199.57869634340224, 199.57869634340224),           // 85: flow_HF_3[4]
        //     mc::Interval(210.54848966613673, 210.54848966613673),           // 86: flow_HF_3[5]
        //     mc::Interval(222.1383147853736, 222.1383147853736),             // 87: flow_HF_3[6]
        //     mc::Interval(196.7885532591415, 196.7885532591415),             // 88: flow_HF_3[7]
        //     mc::Interval(208.54531001589828, 208.54531001589828),           // 89: flow_HF_3[8]
        //     mc::Interval(204.3720190779014, 204.3720190779014),             // 90: flow_HF_3[9]
        //     mc::Interval(210.2623211446741, 210.2623211446741),             // 91: flow_HF_3[10]
        //     mc::Interval(0.0, 0.0),                                         // 92: flow_Import[1]
        //     mc::Interval(0.0, 0.0),                                         // 93: flow_Import[2]
        //     mc::Interval(0.0, 0.0),                                         // 94: flow_Import[3]
        //     mc::Interval(0.0, 0.0),                                         // 95: flow_Import[4]
        //     mc::Interval(0.0, 0.0),                                         // 96: flow_Import[5]
        //     mc::Interval(0.0, 0.0),                                         // 97: flow_Import[6]
        //     mc::Interval(0.0, 0.0),                                         // 98: flow_Import[7]
        //     mc::Interval(0.0, 0.0),                                         // 99: flow_Isomerisation
        //     mc::Interval(700.0, 700.0),                                     // 100: flow_JPF[1]
        //     mc::Interval(700.0, 700.0),                                     // 101: flow_JPF[2]
        //     mc::Interval(700.0, 700.0),                                     // 102: flow_LG_producing
        //     mc::Interval(700.0, 700.0),                                     // 103: flow_LN_producing
        //     mc::Interval(700.0, 700.0),                                     // 104: flow_PG98[1]
        //     mc::Interval(700.0, 700.0),                                     // 105: flow_PG98[2]
        //     mc::Interval(700.0, 700.0),                                     // 106: flow_PG98[3]
        //     mc::Interval(700.0, 700.0),                                     // 107: flow_PG98[4]
        //     mc::Interval(700.0, 700.0),                                     // 108: flow_PG98[5]
        //     mc::Interval(700.0, 700.0),                                     // 109: flow_PG98[6]
        //     mc::Interval(0.0, 60.0),                                        // 110: flow_Reformer100
        //     mc::Interval(5.0, 65.0),                                        // 111: flow_Reformer95
        //     mc::Interval(0.0, 1.0),                                         // 112: fraction_CGO[1]
        //     mc::Interval(0.0, 1.0),                                         // 113: fraction_CGO[2]
        //     mc::Interval(0.0, 1.0),                                         // 114: fraction_LG[1]
        //     mc::Interval(0.0, 1.0),                                         // 115: fraction_LG[2]
        //     mc::Interval(0.0, 1.0),                                         // 116: fraction_LG[3]
        //     mc::Interval(0.0, 1.0),                                         // 117: fraction_LG[4]
        //     mc::Interval(0.0, 1.0),                                         // 118: fraction_LG[5]
        //     mc::Interval(0.0, 1206.896551724138),                           // 119: volume_ES95
        //     mc::Interval(0.0, 832.9366968110423),                           // 120: volume_HF
        //     mc::Interval(0.0, 1206.896551724138)                            // 121: volume_PG98
        // };
    
    
};

void CrudeModel::buildDAG() {
    for (auto& scenario_name : this->scenario_names) {
        int n_first_stage_vars = this->first_stage_IX.size();

        // Loop over each scenario to build subproblem

        const int nvars = n_first_stage_vars + this->second_stage_IX.size();

        this->X[scenario_name].resize(nvars);


        for (int i = 0; i < nvars; ++i) this->X[scenario_name][i].set(&this->DAG[scenario_name]);

        // scenario perturbation


        mc::FFVar g_0_0 = this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]] + this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]] + this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]] + this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]] + this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]] + this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]] + this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]] + this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]] + this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]] + this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]]-700;
        mc::FFVar g_0_1 = 13.419713831478537*this->X[scenario_name][this->first_stage_map["pickCrude[1]"]]-this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]];
        mc::FFVar g_0_2 = 14.165341812400635*this->X[scenario_name][this->first_stage_map["pickCrude[2]"]]-this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]];
        mc::FFVar g_0_3 = 13.419713831478537*this->X[scenario_name][this->first_stage_map["pickCrude[3]"]]-this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]];
        mc::FFVar g_0_4 = 13.305246422893482*this->X[scenario_name][this->first_stage_map["pickCrude[4]"]]-this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]];
        mc::FFVar g_0_5 = 14.036565977742448*this->X[scenario_name][this->first_stage_map["pickCrude[5]"]]-this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]];
        mc::FFVar g_0_6 = 14.809220985691574*this->X[scenario_name][this->first_stage_map["pickCrude[6]"]]-this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]];
        mc::FFVar g_0_7 = 13.119236883942767*this->X[scenario_name][this->first_stage_map["pickCrude[7]"]]-this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]];
        mc::FFVar g_0_8 = 13.903020667726551*this->X[scenario_name][this->first_stage_map["pickCrude[8]"]]-this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]];
        mc::FFVar g_0_9 = 13.624801271860093*this->X[scenario_name][this->first_stage_map["pickCrude[9]"]]-this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]];
        
        mc::FFVar g_0_10 = 14.017488076311606*this->X[scenario_name][this->first_stage_map["pickCrude[10]"]]-this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar g_0_11 = this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]]-201.29570747217807*this->X[scenario_name][this->first_stage_map["pickCrude[1]"]];
        mc::FFVar g_0_12 = this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]]-212.48012718600953*this->X[scenario_name][this->first_stage_map["pickCrude[2]"]];
        mc::FFVar g_0_13 = this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]]-201.29570747217807*this->X[scenario_name][this->first_stage_map["pickCrude[3]"]];
        mc::FFVar g_0_14 = this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]]-199.57869634340224*this->X[scenario_name][this->first_stage_map["pickCrude[4]"]];
        mc::FFVar g_0_15 = this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]]-210.54848966613673*this->X[scenario_name][this->first_stage_map["pickCrude[5]"]];
        mc::FFVar g_0_16 = this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]]-222.1383147853736*this->X[scenario_name][this->first_stage_map["pickCrude[6]"]];
        mc::FFVar g_0_17 = this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]]-196.7885532591415*this->X[scenario_name][this->first_stage_map["pickCrude[7]"]];
        mc::FFVar g_0_18 = this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]]-208.54531001589828*this->X[scenario_name][this->first_stage_map["pickCrude[8]"]];
        mc::FFVar g_0_19 = this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]]-204.3720190779014*this->X[scenario_name][this->first_stage_map["pickCrude[9]"]];
        mc::FFVar g_0_20 = this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]]-210.2623211446741*this->X[scenario_name][this->first_stage_map["pickCrude[10]"]];

        mc::FFVar g_1_0 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]]-125;
        mc::FFVar g_1_1 = 0.08*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0.09*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] + 0.015*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.012*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] + 0.03*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] + 0.04*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[1]"]] + 0.0020105335707024776*this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] + 0.002033729784573578*this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] + 0.002110066788923241*this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] + 0.003973905045918246*this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] + 0.0019988517589712403*this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] + 0.0008904820763900271*this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]] + 0.03*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] + 0.001991196321110873*this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]] + 0.03*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] + 0.0028411758274924682*this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]] + 0.04*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] + 0.004057963205263551*this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] + 0.00427501144267499*this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]] + 0.04*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]];
        mc::FFVar n_g_1_1 =-g_1_1;
        mc::FFVar g_1_2 = 0.09*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0.12*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] + 0.053*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.046*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_LG_producing"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]] + 0.009147927746696273*this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]] + 0.009050097541352423*this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]] + 0.008440267155692963*this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]] + 0.019869525229591227*this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]] + 0.011493397614084631*this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]] + 0.005699085288896173*this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]] + 0.015431771488609266*this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]] + 0.012736305433586925*this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]] + 0.01592750558065944*this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]] + 0.011435655609155597*this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_2 = - g_1_2;
        mc::FFVar g_1_3 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_LN_producing"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] - 0.05*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] - 0.035*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] + 0.07016762161751647*this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]] + 0.04880951482976587*this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]] + 0.06435703706215884*this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]] + 0.08454482985191068*this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]] + 0.05426882525606917*this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]] + 0.021905859079194668*this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]] + 0.09408402617248875*this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]] + 0.06387747032845136*this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]] + 0.07598536101855999*this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]] + 0.06455267278439235*this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_3 = - g_1_3;
        mc::FFVar g_1_4 = -0.1*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] - 0.065*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] + 0.16064163229912795*this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]] + 0.09751734317030307*this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]] + 0.1272370273720714*this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]] + 0.15220056325866882*this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]] + 0.10254109523522463*this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]] + 0.054052262036874646*this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]] + 0.165368854468258*this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]] + 0.11717400998899972*this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]] + 0.12853598452672302*this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]] + 0.12002094625310035*this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_4 = - g_1_4;
        mc::FFVar g_1_5 = -0.85*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] - 0.9*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_3[1]"]] + 0.10082825857072926*this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]] + 0.08094244542602841*this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]] + 0.0908383752631455*this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]] + 0.09408220196211448*this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]] + 0.07645607978064994*this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]] + 0.0461269715570034*this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]] + 0.11548938662443065*this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]] + 0.08210018425650649*this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]] + 0.09282590832040374*this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]] + 0.0837902242764298*this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_5= - g_1_5;
        mc::FFVar g_1_6 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] + 0.2696125518312022*this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]] + 0.27811254804043684*this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]] + 0.27916183617454476*this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]] + 0.25184623228506886*this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]] + 0.2693452745213747*this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]] + 0.26108934479755597*this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]] + 0.2306800938006946*this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]] + 0.23591556526213323*this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]] + 0.2546371911302879*this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]] + 0.266226337592585*this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_6 = - g_1_6;
        mc::FFVar g_1_7 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 0.28911472746701633*this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]];
        mc::FFVar n_g_1_7 = - g_1_7;
        mc::FFVar g_1_8 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 0.22869291427529884*this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]];
        mc::FFVar n_g_1_8 = - g_1_8;
        mc::FFVar g_1_9 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 0.25468506142303515*this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]];
        mc::FFVar n_g_1_9 = - g_1_9;
        mc::FFVar g_1_10 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[4]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 0.25224362278966067*this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]];
        mc::FFVar n_g_1_10 = - g_1_10;
        mc::FFVar g_1_11 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[5]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 0.22846875605041275*this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]];
        mc::FFVar n_g_1_11 = - g_1_11;
        mc::FFVar g_1_12 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[6]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 0.16919159451410512*this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]];
        mc::FFVar n_g_1_12 = - g_1_12;
        mc::FFVar g_1_13 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[7]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 0.26443087144352395*this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]];
        mc::FFVar n_g_1_13 = - g_1_13;
        mc::FFVar g_1_14 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[8]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 0.20838555120953378*this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]];
        mc::FFVar n_g_1_14 = - g_1_14;
        mc::FFVar g_1_15 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[9]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 0.2387096855496284*this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]];
        mc::FFVar n_g_1_15 = - g_1_15;
        mc::FFVar g_1_16 = - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[10]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] + 0.223583098451902*this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_16 = - g_1_16;
        mc::FFVar g_1_17 = 0.098476746897009*this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]];
        mc::FFVar n_g_1_17 = - g_1_17;
        mc::FFVar g_1_18 = 0.254841406932241*this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]];
        mc::FFVar n_g_1_18 = - g_1_18;
        mc::FFVar g_1_19 = 0.173170328760428*this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]];
        mc::FFVar n_g_1_19 = - g_1_19;
        mc::FFVar g_1_20 = 0.141239119577067*this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]];
        mc::FFVar n_g_1_20 = - g_1_20;


        mc::FFVar g_1_21 = 0.255427719783213*this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]];
        mc::FFVar n_g_1_21 = - g_1_21;
        mc::FFVar g_1_22 = 0.44104440064998*this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]];
        mc::FFVar n_g_1_22 = - g_1_22;
        mc::FFVar g_1_23 = 0.112523799680884*this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]];
        mc::FFVar n_g_1_23 = - g_1_23;
        mc::FFVar g_1_24 = 0.276969737693296*this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]];
        mc::FFVar n_g_1_24 = - g_1_24;
        mc::FFVar g_1_25 = 0.189320400668474*this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]];
        mc::FFVar n_g_1_25 = - g_1_25;
        mc::FFVar g_1_26 = 0.22611605358976*this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]];
        mc::FFVar n_g_1_26 = - g_1_26;
        mc::FFVar g_1_27 = 0.98*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[1]"]];
        mc::FFVar n_g_1_27 = - g_1_27;
        mc::FFVar g_1_28 = 0.98*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[2]"]];
        mc::FFVar n_g_1_28 = - g_1_28;
        mc::FFVar g_1_29 = 0.98*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[3]"]];
        mc::FFVar n_g_1_29 = - g_1_29;
        mc::FFVar g_1_30 = 0.98*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[4]"]];
        mc::FFVar n_g_1_30 = - g_1_30;
        mc::FFVar g_1_31 = 0.98*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[5]"]];
        mc::FFVar n_g_1_31 = - g_1_31;    
        mc::FFVar g_1_32 = 0.97*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[6]"]];
        mc::FFVar n_g_1_32 = - g_1_32;
        mc::FFVar g_1_33 = 0.97*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[7]"]];
        mc::FFVar n_g_1_33 = - g_1_33;
        mc::FFVar g_1_34 = 0.96*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[8]"]];
        mc::FFVar n_g_1_34 = - g_1_34;
        mc::FFVar g_1_35 = 0.98*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[9]"]];
        mc::FFVar n_g_1_35 = - g_1_35;
        mc::FFVar g_1_36 = 0.96*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[10]"]];
        mc::FFVar n_g_1_36 = - g_1_36;
        mc::FFVar g_1_37 = 0.83*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]];
        mc::FFVar n_g_1_37 = - g_1_37;
        mc::FFVar g_1_38 = 0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + 0.79*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]];
        mc::FFVar n_g_1_38 = - g_1_38;
        mc::FFVar g_1_39 = 0.97*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]];
        mc::FFVar n_g_1_39 = - g_1_39;
        mc::FFVar g_1_40 = 0.436*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.381*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]];
        mc::FFVar n_g_1_40 = - g_1_40;
        
        
        mc::FFVar g_1_41 = 0.446*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + 0.511*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_2"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
        mc::FFVar n_g_1_41 = - g_1_41;
        mc::FFVar g_1_42 = 0.96*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_3[3]"]];
        mc::FFVar n_g_1_42 = - g_1_42;
        mc::FFVar g_1_43 = -(this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] - 5.0);
        mc::FFVar g_1_44 = -(this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[2]"]]);
        mc::FFVar g_1_45 = -(this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_JPF[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_JPF[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[3]"]]);
        mc::FFVar g_1_46 = -(this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_3[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_3[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[5]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[5]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[6]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[6]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[7]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[7]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[8]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[8]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[9]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[9]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[10]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[10]"]] - 100.0);
        mc::FFVar g_1_47 = -(this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[5]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_2"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] - 100.0);
        mc::FFVar g_1_48 = -(this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[6]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_LG_producing"]]);
        mc::FFVar g_1_49 = -(this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[7]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_LN_producing"]]);
        mc::FFVar g_1_50 = 1.7241379310344829*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 1.5037593984962405*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 1.5384615384615383*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 1.2987012987012987*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 1.25*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 1.3333333333333333*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 1.2658227848101264*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_PG98"]];
        mc::FFVar n_g_1_50= - g_1_50;
        mc::FFVar g_1_51 = 1.7241379310344829*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 1.5037593984962405*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 1.5384615384615383*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 1.2987012987012987*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 1.25*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 1.3333333333333333*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 1.3157894736842106*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_ES95"]];
        mc::FFVar n_g_1_51 = - g_1_51;
        mc::FFVar g_1_52 = 1.7241379310344829*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 0.039473684210526314*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] - 0.05*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_ES95"]];
        mc::FFVar g_1_53 = 1.7241379310344829*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 0.039473684210526314*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] - 0.05*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_PG98"]];
        mc::FFVar g_1_54 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_54 = - g_1_54;
        mc::FFVar g_1_55 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_55 = - g_1_55;
        mc::FFVar g_1_56 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_56 = - g_1_56;
        mc::FFVar g_1_57 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[4]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_57 = - g_1_57;
        mc::FFVar g_1_58 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_58 = - g_1_58;
        mc::FFVar g_1_59 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_59 = - g_1_59;
        mc::FFVar g_1_60 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_60 = - g_1_60;
        
        
        mc::FFVar g_1_61 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[4]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_61 = - g_1_61;
        mc::FFVar g_1_62 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_62 = - g_1_62;
        mc::FFVar g_1_63 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_63 = - g_1_63;
        mc::FFVar g_1_64 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_64 = - g_1_64;
        mc::FFVar g_1_65 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[4]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_65 = - g_1_65;
        mc::FFVar g_1_66 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_66 = - g_1_66;
        mc::FFVar g_1_67 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_67 = - g_1_67;
        mc::FFVar g_1_68 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_68 = - g_1_68;
        mc::FFVar g_1_69 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[4]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_69 = - g_1_69;
        mc::FFVar g_1_70 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_70 = - g_1_70;
        mc::FFVar g_1_71 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_71 = - g_1_71;
        mc::FFVar g_1_72 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_72 = - g_1_72;
        mc::FFVar g_1_73 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[4]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_73 = - g_1_73;
        mc::FFVar g_1_74 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[4]"]] - (0.009147927746696273*this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]] + 0.009050097541352423*this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]] + 0.008440267155692963*this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]] + 0.019869525229591227*this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]] + 0.011493397614084631*this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]] + 0.005699085288896173*this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]] + 0.015431771488609266*this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]] + 0.012736305433586925*this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]] + 0.01592750558065944*this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]] + 0.011435655609155597*this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]]);
        mc::FFVar n_g_1_74 = - g_1_74;
        mc::FFVar g_1_75 = 0.09*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[4]"]];
        mc::FFVar n_g_1_75 = - g_1_75;
        mc::FFVar g_1_76 = 0.12*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[4]"]];
        mc::FFVar n_g_1_76 = - g_1_76;
        mc::FFVar g_1_77 = 0.053*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[4]"]];
        mc::FFVar n_g_1_77 = - g_1_77;
        mc::FFVar g_1_78 = 0.046*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[4]"]];
        mc::FFVar n_g_1_78 = - g_1_78;
        mc::FFVar g_1_79 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_79 = - g_1_79;
        mc::FFVar g_1_80 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_80 = - g_1_80;
        
        
        mc::FFVar g_1_81 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_81 = - g_1_81;
        mc::FFVar g_1_82 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[4]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_82 = - g_1_82;
        mc::FFVar g_1_83 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[4]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_LG[5]"]] - 1.0;
        mc::FFVar n_g_1_83 = - g_1_83;
        mc::FFVar g_1_84 = -(-0.45*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 0.8552631578947368*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 0.6015037593984962*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 1.2307692307692308*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 0.6493506493506493*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 0.625*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 0.8666666666666667*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 7.413793103448276*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 7.379310344827587*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 7.517241379310346*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 7.258620689655173*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 7.275862068965517*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]]);
        mc::FFVar g_1_85 = -0.8*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 0.8552631578947368*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 0.6015037593984962*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 1.2307692307692308*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 0.6493506493506493*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 0.625*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 0.8666666666666667*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 7.413793103448276*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 7.379310344827587*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 7.517241379310346*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 7.258620689655173*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 7.275862068965517*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]];
        mc::FFVar g_1_86 = -(-0.5*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 0.8227848101265822*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 0.6015037593984962*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 1.2307692307692308*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 0.6493506493506493*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 0.625*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 0.8666666666666667*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 7.413793103448276*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 7.379310344827587*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 7.517241379310346*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 7.258620689655173*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 7.275862068965517*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]]);
        mc::FFVar g_1_87 = -0.86*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 0.8227848101265822*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 0.6015037593984962*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 1.2307692307692308*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 0.6493506493506493*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 0.625*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 0.8666666666666667*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 7.413793103448276*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 7.379310344827587*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 7.517241379310346*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 7.258620689655173*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 7.275862068965517*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]];
        mc::FFVar g_1_88 = -(-98*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 132.91139240506328*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 136.8421052631579*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 109.23076923076923*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 123.37662337662337*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 125.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 124.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 160.34482758620692*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 159.48275862068968*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 161.3793103448276*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 159.82758620689657*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 161.89655172413796*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]]);
        mc::FFVar g_1_89 = -(-95*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 131.57894736842104*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 136.8421052631579*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 109.23076923076923*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 123.37662337662337*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 125.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 124.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 160.34482758620692*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 159.48275862068968*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 161.3793103448276*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 159.82758620689657*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 161.89655172413796*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]]);
        mc::FFVar g_1_90 = -10*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_PG98"]] + 6.329113924050633*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[1]"]] + 0.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[1]"]] + 7.518796992481203*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[2]"]] + 4.615384615384615*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[3]"]] + 11.688311688311687*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[4]"]] + 11.25*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[5]"]] + 14.666666666666666*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_PG98[6]"]] + 5.172413793103448*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[2]"]] + 5.00000000000001*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[2]"]] + 4.6551724137930846*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[2]"]] + 6.379310344827592*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[2]"]] + 6.379310344827592*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[2]"]];
        
        mc::FFVar g_1_91 = -10*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_ES95"]] + 5.2631578947368425*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[2]"]] + 0.0*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[1]"]] + 7.518796992481203*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[2]"]] + 4.615384615384615*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[3]"]] + 11.688311688311687*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[4]"]] + 11.25*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[5]"]] + 14.666666666666666*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_ES95[6]"]] + 5.172413793103448*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_CDU_LG[1]"]] + 5.00000000000001*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer95_LG[1]"]] + 4.6551724137930846*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Reformer100_LG[1]"]] + 6.379310344827592*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Mogas_LG[1]"]] + 6.379310344827592*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_AGO_LG[1]"]];
        mc::FFVar g_1_92 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
        mc::FFVar n_g_1_92 = - g_1_92;
        mc::FFVar g_1_93 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_2"]];
        mc::FFVar n_g_1_93 = - g_1_93;
        mc::FFVar g_1_94 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]];
        mc::FFVar n_g_1_94 = - g_1_94;
        mc::FFVar g_1_95 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
        mc::FFVar n_g_1_95 = - g_1_95;
        mc::FFVar g_1_96 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_2"]];
        mc::FFVar n_g_1_96 = - g_1_96;
        mc::FFVar g_1_97 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] * this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]];
        mc::FFVar n_g_1_97 = - g_1_97;
        mc::FFVar g_1_98 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] - 0.446*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]];
        mc::FFVar n_g_1_98 = - g_1_98;
        mc::FFVar g_1_99 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] - 0.511*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]];
        mc::FFVar n_g_1_99 = - g_1_99;
        mc::FFVar g_1_100 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_CGO[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["fraction_CGO[2]"]] - 1.0;
        mc::FFVar n_g_1_100 = - g_1_100;
        
        mc::FFVar g_1_101 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_3[2]"]];
        mc::FFVar n_g_1_101 = - g_1_101;
        mc::FFVar g_1_102 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_2"]];
        mc::FFVar n_g_1_102 = - g_1_102;
        mc::FFVar g_1_103 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] - this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]];
        mc::FFVar n_g_1_103 = - g_1_103;
        mc::FFVar g_1_104 = -this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_HF"]] + 1.0204081632653061*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[5]"]] + 1.0526315789473684*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_2"]] + 1.0655301012253595*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + 1.175640724194686*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 1.032844453625284*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + 1.1641443538998837*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 1.0612331529236974*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + 1.188636633781053*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 1.060108131029365*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + 1.183431952662722*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 1.0360547036883547*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + 1.166452816983553*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 1.0280662074637608*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + 1.1510128913443831*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 1.0559662090813096*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + 1.1899095668729176*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 1.020512297173181*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + 1.1810558639423645*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 1.0458063166701526*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + 1.1796626164916835*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 1.0325245224574084*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + 1.1684973124561813*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]];
        mc::FFVar n_g_1_104 = - g_1_104;
        mc::FFVar g_1_105 = -(34.629728289824186*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + 2.962614624970609*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 71.88597397231976*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + 3.39930151338766*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 40.53910644168524*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + 3.1023416141685485*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 45.26661719495389*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + 3.0295857988165684*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 89.61873186904269*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + 3.0910999650064155*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 77.61899866351393*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + 3.39548802946593*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 44.66737064413939*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + 2.974773917182294*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 45.92305337279314*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + 2.9644502184953345*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 55.95063794185317*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + 3.0907160552082105*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 56.99535363964894*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + 3.119887824258004*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] + (12.2*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + 11.65*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]])/0.95 - 30*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_HF"]]);
        mc::FFVar g_1_106 = 34.629728289824186*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[1]"]] + 2.962614624970609*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[1]"]] + 71.88597397231976*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[2]"]] + 3.39930151338766*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[2]"]] + 40.53910644168524*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[3]"]] + 3.1023416141685485*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[3]"]] + 45.26661719495389*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[4]"]] + 3.0295857988165684*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[4]"]] + 89.61873186904269*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[5]"]] + 3.0910999650064155*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[5]"]] + 77.61899866351393*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[6]"]] + 3.39548802946593*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[6]"]] + 44.66737064413939*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[7]"]] + 2.974773917182294*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[7]"]] + 45.92305337279314*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[8]"]] + 2.9644502184953345*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[8]"]] + 55.95063794185317*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[9]"]] + 3.0907160552082105*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[9]"]] + 56.99535363964894*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_1[10]"]] + 3.119887824258004*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_HF_3[10]"]] + (12.2*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[2]"]] + 11.65*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[2]"]])/0.95 - 33*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["volume_HF"]];
        mc::FFVar g_1_107 = -0.0015*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Import[4]"]] + 0.140588513077039*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[1]"]] - 0.000789557434614805*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[1]"]] + 0.309219599235616*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[2]"]] + 5.3597996178079976e-05*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[2]"]] + 0.16502807856732*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[3]"]] - 0.0006673596071634*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[3]"]] + 0.211405808207417*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[4]"]] - 0.000435470958962915*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[4]"]] + 0.264982491043895*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[5]"]] - 0.00016758754478052502*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[5]"]] + 0.7602297836086701*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[6]"]] + 0.0023086489180433505*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[6]"]] + 0.632862056891616*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[7]"]] + 0.0016718102844580796*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[7]"]] + 1.575235109424405*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[8]"]] + 0.006383675547122027*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[8]"]] + 0.289990315101932*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[9]"]] - 4.2548424490339905e-05*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[9]"]] + 1.087848038245218*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_1[10]"]] + 0.003946740191226091*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_2[10]"]] + 0.0985*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_3[1]"]] + 1.6784999999999999*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[1]"]] + 2.0985*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[1]"]] + 0.0084*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_AGO[3]"]] + 0.0105*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["blin_Cracker_Mogas[3]"]] - 0.0015*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_AGO_3[3]"]];
        mc::FFVar g_1_108 = -(1.3*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[1]"]] + 1.2*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[2]"]] + 1.1*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Burn[3]"]] - 0.019*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] - 0.026*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - 0.007*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] - 0.007*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - 0.04*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Isomerisation"]] - 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_CGO"]] - 15.2 - (0.018*this->X[scenario_name][this->first_stage_map["CrudeQuantity[1]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[1]"]] + 0.018*this->X[scenario_name][this->first_stage_map["CrudeQuantity[2]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[2]"]] + 0.018*this->X[scenario_name][this->first_stage_map["CrudeQuantity[3]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[3]"]] + 0.018*this->X[scenario_name][this->first_stage_map["CrudeQuantity[4]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[4]"]] + 0.018*this->X[scenario_name][this->first_stage_map["CrudeQuantity[5]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[5]"]] + 0.018*this->X[scenario_name][this->first_stage_map["CrudeQuantity[6]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[6]"]] + 0.018*this->X[scenario_name][this->first_stage_map["CrudeQuantity[7]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[7]"]] + 0.018*this->X[scenario_name][this->first_stage_map["CrudeQuantity[8]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[8]"]] + 0.018*this->X[scenario_name][this->first_stage_map["CrudeQuantity[9]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[9]"]] + 0.018*this->X[scenario_name][this->first_stage_map["CrudeQuantity[10]"]] + 0.02*this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Desulphurisation_1[10]"]]));
        mc::FFVar g_1_109 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_Mogas"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Cracker_AGO"]] - 175;
        mc::FFVar g_1_110 = this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer95"]] + this->X[scenario_name][n_first_stage_vars + this->second_stage_map["flow_Reformer100"]] - 65;
        



        mc::FFVar objective =
        this->probability*(
            3.2*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Cracker_Mogas")]
        + 3*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Cracker_AGO")]
        + 2.7*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Reformer95")]
        + 3.2*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Reformer100")]
        + 6*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Isomerisation")]
        + 3.345671410129097*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_CGO")]
        - 561.6*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_LG_producing")]
        - 1003*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_LN_producing")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_2")]
        + 2.3942543643299556*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[1]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[1]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[1]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[1]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[1]")]
        + 864.3999526122498*this->X[scenario_name][this->first_stage_map.at("CrudeQuantity[1]")]
        + 2.485328036981826*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[2]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[2]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[2]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[2]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[2]")]
        + 765.9539842873176*this->X[scenario_name][this->first_stage_map.at("CrudeQuantity[2]")]
        + 2.437662761144984*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[3]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[3]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[3]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[3]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[3]")]
        + 824.9058168463453*this->X[scenario_name][this->first_stage_map.at("CrudeQuantity[3]")]
        + 2.4589973078611767*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[4]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[4]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[4]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[4]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[4]")]
        + 839.5184609869758*this->X[scenario_name][this->first_stage_map.at("CrudeQuantity[4]")]
        + 2.460163454262119*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[5]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[5]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[5]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[5]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[5]")]
        + 779.3929097293013*this->X[scenario_name][this->first_stage_map.at("CrudeQuantity[5]")]
        + 2.760038638583934*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[6]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[6]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[6]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[6]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[6]")]
        + 692.8115942028985*this->X[scenario_name][this->first_stage_map.at("CrudeQuantity[6]")]
        + 2.7649237751065976*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[7]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[7]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[7]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[7]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[7]")]
        + 878.862094037809*this->X[scenario_name][this->first_stage_map.at("CrudeQuantity[7]")]
        + 3.39343900683156*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[8]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[8]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[8]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[8]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[8]")]
        + 735.8113207547168*this->X[scenario_name][this->first_stage_map.at("CrudeQuantity[8]")]
        + 2.5052287966283195*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[9]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[9]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[9]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[9]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[9]")]
        + 810.2870478413071*this->X[scenario_name][this->first_stage_map.at("CrudeQuantity[9]")]
        + 3.025222449696517*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[10]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[10]")]
        - 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[10]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[10]")]
        - 637*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[10]")]
        + 749.7063627084043*this->X[scenario_name][this->first_stage_map.at("CrudeQuantity[10]")]
        - (1231*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_PG98[1]")]
            + 1194*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_ES95[1]")]
            + 1231*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_PG98[2]")]
            + 1194*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_ES95[2]")]
            + 1231*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_PG98[3]")]
            + 1194*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_ES95[3]")]
            + 1231*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_PG98[4]")]
            + 1194*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_ES95[4]")]
            + 1231*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_PG98[5]")]
            + 1194*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_ES95[5]")]
            + 1231*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_PG98[6]")]
            + 1194*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_ES95[6]")])
        - (923*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_JPF[1]")]
            + 923*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_JPF[2]")])
        - (907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_3[1]")]
            + 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_3[2]")]
            + 907*this->X[scenario_name][n_first_stage_vars + this->second_stage_map.at("flow_AGO_3[3]")])
        );




        this->F[scenario_name] = {
            objective,
            g_0_0,g_0_1,g_0_2,g_0_3,g_0_4,g_0_5,g_0_6,g_0_7,g_0_8,g_0_9,
            
            g_0_10,g_0_11,g_0_12,g_0_13,g_0_14,g_0_15,
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
            n_g_1_101,n_g_1_102,n_g_1_103,n_g_1_104
            
            };
    }
};
void CrudeModel::buildFullModelDAG(){
    int n_first_stage_vars = this->first_stage_IX.size();
    int nvars = this->first_stage_IX.size()+this->second_stage_IX.size();
    int n_second_stage_vars = this->second_stage_IX.size()/this->scenario_names.size(); // number of second stage variables per scenario
    this->X[ScenarioNames::SCENARIO1].resize(this->first_stage_IX.size() +this->second_stage_IX.size());
    

    for (int i = 0; i < n_first_stage_vars; ++i) this->X[ScenarioNames::SCENARIO1][i].set(&this->DAG[ScenarioNames::SCENARIO1]);
    for (int s_idx=0; s_idx<this->scenario_names.size(); ++s_idx){
        int second_stage_start_idx = n_first_stage_vars + s_idx * n_second_stage_vars;
        for (int i = 0; i < n_second_stage_vars; ++i){
            this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+i].set(&this->DAG[ScenarioNames::SCENARIO1]);
        }
    }
    mc::FFVar objective=0;
    for (int s_idx=0; s_idx<this->scenario_names.size(); ++s_idx){
        int second_stage_start_idx = n_first_stage_vars + s_idx * n_second_stage_vars;


        mc::FFVar g_0_0 = this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]] + this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]] + this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]] + this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]] + this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]] + this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]] + this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]] + this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]] + this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]] + this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]]-700;
        mc::FFVar g_0_1 = 13.419713831478537*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[1]"]]-this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]];
        mc::FFVar g_0_2 = 14.165341812400635*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[2]"]]-this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]];
        mc::FFVar g_0_3 = 13.419713831478537*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[3]"]]-this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]];
        mc::FFVar g_0_4 = 13.305246422893482*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[4]"]]-this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]];
        mc::FFVar g_0_5 = 14.036565977742448*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[5]"]]-this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]];
        mc::FFVar g_0_6 = 14.809220985691574*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[6]"]]-this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]];
        mc::FFVar g_0_7 = 13.119236883942767*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[7]"]]-this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]];
        mc::FFVar g_0_8 = 13.903020667726551*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[8]"]]-this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]];
        mc::FFVar g_0_9 = 13.624801271860093*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[9]"]]-this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]];
        
        mc::FFVar g_0_10 = 14.017488076311606*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[10]"]]-this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar g_0_11 = this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]]-201.29570747217807*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[1]"]];
        mc::FFVar g_0_12 = this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]]-212.48012718600953*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[2]"]];
        mc::FFVar g_0_13 = this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]]-201.29570747217807*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[3]"]];
        mc::FFVar g_0_14 = this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]]-199.57869634340224*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[4]"]];
        mc::FFVar g_0_15 = this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]]-210.54848966613673*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[5]"]];
        mc::FFVar g_0_16 = this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]]-222.1383147853736*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[6]"]];
        mc::FFVar g_0_17 = this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]]-196.7885532591415*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[7]"]];
        mc::FFVar g_0_18 = this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]]-208.54531001589828*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[8]"]];
        mc::FFVar g_0_19 = this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]]-204.3720190779014*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[9]"]];
        mc::FFVar g_0_20 = this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]]-210.2623211446741*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["pickCrude[10]"]];


        mc::FFVar g_1_0 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[5]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[6]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[7]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[8]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[9]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[10]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_CGO"]]-125;
        mc::FFVar g_1_1 = 0.08*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer95"]] + 0.09*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer100"]] + 0.015*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_Mogas"]] + 0.012*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_AGO"]] + 0.03*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Isomerisation"]] + 0.04*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_CGO"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[1]"]] + 0.0020105335707024776*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[1]"]] + 0.002033729784573578*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[2]"]] + 0.002110066788923241*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[3]"]] + 0.003973905045918246*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[4]"]] + 0.0019988517589712403*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[5]"]] + 0.0008904820763900271*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]] + 0.03*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[6]"]] + 0.001991196321110873*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]] + 0.03*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[7]"]] + 0.0028411758274924682*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]] + 0.04*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[8]"]] + 0.004057963205263551*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[9]"]] + 0.00427501144267499*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]] + 0.04*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[10]"]];
        mc::FFVar n_g_1_1 =-g_1_1;
        mc::FFVar g_1_2 = 0.09*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer95"]] + 0.12*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer100"]] + 0.053*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_Mogas"]] + 0.046*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_AGO"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_LG_producing"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[2]"]] + 0.009147927746696273*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]] + 0.009050097541352423*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]] + 0.008440267155692963*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]] + 0.019869525229591227*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]] + 0.011493397614084631*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]] + 0.005699085288896173*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]] + 0.015431771488609266*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]] + 0.012736305433586925*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]] + 0.01592750558065944*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]] + 0.011435655609155597*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_2 = - g_1_2;
        mc::FFVar g_1_3 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_LN_producing"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Isomerisation"]] - 0.05*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_JPF[1]"]] - 0.035*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_JPF[2]"]] + 0.07016762161751647*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]] + 0.04880951482976587*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]] + 0.06435703706215884*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]] + 0.08454482985191068*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]] + 0.05426882525606917*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]] + 0.021905859079194668*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]] + 0.09408402617248875*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]] + 0.06387747032845136*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]] + 0.07598536101855999*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]] + 0.06455267278439235*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_3 = - g_1_3;
        mc::FFVar g_1_4 = -0.1*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_JPF[1]"]] - 0.065*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_JPF[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer95"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer100"]] + 0.16064163229912795*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]] + 0.09751734317030307*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]] + 0.1272370273720714*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]] + 0.15220056325866882*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]] + 0.10254109523522463*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]] + 0.054052262036874646*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]] + 0.165368854468258*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]] + 0.11717400998899972*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]] + 0.12853598452672302*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]] + 0.12002094625310035*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_4 = - g_1_4;
        mc::FFVar g_1_5 = -0.85*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_JPF[1]"]] - 0.9*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_JPF[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_3[1]"]] + 0.10082825857072926*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]] + 0.08094244542602841*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]] + 0.0908383752631455*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]] + 0.09408220196211448*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]] + 0.07645607978064994*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]] + 0.0461269715570034*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]] + 0.11548938662443065*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]] + 0.08210018425650649*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]] + 0.09282590832040374*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]] + 0.0837902242764298*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_5= - g_1_5;
        mc::FFVar g_1_6 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_Mogas"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_AGO"]] + 0.2696125518312022*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]] + 0.27811254804043684*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]] + 0.27916183617454476*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]] + 0.25184623228506886*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]] + 0.2693452745213747*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]] + 0.26108934479755597*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]] + 0.2306800938006946*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]] + 0.23591556526213323*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]] + 0.2546371911302879*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]] + 0.266226337592585*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_6 = - g_1_6;
        mc::FFVar g_1_7 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[1]"]] + 0.28911472746701633*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]];
        mc::FFVar n_g_1_7 = - g_1_7;
        mc::FFVar g_1_8 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[2]"]] + 0.22869291427529884*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]];
        mc::FFVar n_g_1_8 = - g_1_8;
        mc::FFVar g_1_9 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[3]"]] + 0.25468506142303515*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]];
        mc::FFVar n_g_1_9 = - g_1_9;
        mc::FFVar g_1_10 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[4]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[4]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[4]"]] + 0.25224362278966067*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]];
        mc::FFVar n_g_1_10 = - g_1_10;
        mc::FFVar g_1_11 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[5]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[5]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[5]"]] + 0.22846875605041275*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]];
        mc::FFVar n_g_1_11 = - g_1_11;
        mc::FFVar g_1_12 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[6]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[6]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[6]"]] + 0.16919159451410512*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]];
        mc::FFVar n_g_1_12 = - g_1_12;
        mc::FFVar g_1_13 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[7]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[7]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[7]"]] + 0.26443087144352395*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]];
        mc::FFVar n_g_1_13 = - g_1_13;
        mc::FFVar g_1_14 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[8]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[8]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[8]"]] + 0.20838555120953378*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]];
        mc::FFVar n_g_1_14 = - g_1_14;
        mc::FFVar g_1_15 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[9]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[9]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[9]"]] + 0.2387096855496284*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]];
        mc::FFVar n_g_1_15 = - g_1_15;
        mc::FFVar g_1_16 = - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[10]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[10]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[10]"]] + 0.223583098451902*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]];
        mc::FFVar n_g_1_16 = - g_1_16;
        mc::FFVar g_1_17 = 0.098476746897009*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[1]"]];
        mc::FFVar n_g_1_17 = - g_1_17;
        mc::FFVar g_1_18 = 0.254841406932241*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[2]"]];
        mc::FFVar n_g_1_18 = - g_1_18;
        mc::FFVar g_1_19 = 0.173170328760428*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[3]"]];
        mc::FFVar n_g_1_19 = - g_1_19;
        mc::FFVar g_1_20 = 0.141239119577067*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[4]"]];
        mc::FFVar n_g_1_20 = - g_1_20;


        mc::FFVar g_1_21 = 0.255427719783213*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[5]"]];
        mc::FFVar n_g_1_21 = - g_1_21;
        mc::FFVar g_1_22 = 0.44104440064998*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[6]"]];
        mc::FFVar n_g_1_22 = - g_1_22;
        mc::FFVar g_1_23 = 0.112523799680884*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[7]"]];
        mc::FFVar n_g_1_23 = - g_1_23;
        mc::FFVar g_1_24 = 0.276969737693296*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[8]"]];
        mc::FFVar n_g_1_24 = - g_1_24;
        mc::FFVar g_1_25 = 0.189320400668474*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[9]"]];
        mc::FFVar n_g_1_25 = - g_1_25;
        mc::FFVar g_1_26 = 0.22611605358976*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[10]"]];
        mc::FFVar n_g_1_26 = - g_1_26;
        mc::FFVar g_1_27 = 0.98*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[1]"]];
        mc::FFVar n_g_1_27 = - g_1_27;
        mc::FFVar g_1_28 = 0.98*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[2]"]];
        mc::FFVar n_g_1_28 = - g_1_28;
        mc::FFVar g_1_29 = 0.98*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[3]"]];
        mc::FFVar n_g_1_29 = - g_1_29;
        mc::FFVar g_1_30 = 0.98*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[4]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[4]"]];
        mc::FFVar n_g_1_30 = - g_1_30;
        mc::FFVar g_1_31 = 0.98*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[5]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[5]"]];
        mc::FFVar n_g_1_31 = - g_1_31;    
        mc::FFVar g_1_32 = 0.97*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[6]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[6]"]];
        mc::FFVar n_g_1_32 = - g_1_32;
        mc::FFVar g_1_33 = 0.97*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[7]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[7]"]];
        mc::FFVar n_g_1_33 = - g_1_33;
        mc::FFVar g_1_34 = 0.96*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[8]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[8]"]];
        mc::FFVar n_g_1_34 = - g_1_34;
        mc::FFVar g_1_35 = 0.98*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[9]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[9]"]];
        mc::FFVar n_g_1_35 = - g_1_35;
        mc::FFVar g_1_36 = 0.96*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[10]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[10]"]];
        mc::FFVar n_g_1_36 = - g_1_36;
        mc::FFVar g_1_37 = 0.83*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer95"]] + 0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer100"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[4]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[4]"]];
        mc::FFVar n_g_1_37 = - g_1_37;
        mc::FFVar g_1_38 = 0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer95"]] + 0.79*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer100"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[5]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[5]"]];
        mc::FFVar n_g_1_38 = - g_1_38;
        mc::FFVar g_1_39 = 0.97*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Isomerisation"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[2]"]];
        mc::FFVar n_g_1_39 = - g_1_39;
        mc::FFVar g_1_40 = 0.436*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_Mogas"]] + 0.381*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_AGO"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[6]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[6]"]];
        mc::FFVar n_g_1_40 = - g_1_40;
        
        
        mc::FFVar g_1_41 = 0.446*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_Mogas"]] + 0.511*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_AGO"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_CGO"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_2"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_3[2]"]];
        mc::FFVar n_g_1_41 = - g_1_41;
        mc::FFVar g_1_42 = 0.96*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_CGO"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_3[3]"]];
        mc::FFVar n_g_1_42 = - g_1_42;
        mc::FFVar g_1_43 = -(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[5]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[6]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[1]"]] - 5.0);
        mc::FFVar g_1_44 = -(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[5]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[6]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[2]"]]);
        mc::FFVar g_1_45 = -(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_JPF[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_JPF[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[3]"]]);
        mc::FFVar g_1_46 = -(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_3[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_3[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_3[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[5]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[5]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[6]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[6]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[7]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[7]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[8]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[8]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[9]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[9]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[10]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[10]"]] - 100.0);
        mc::FFVar g_1_47 = -(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[5]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_2"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[5]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[5]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[6]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[6]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[7]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[7]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[8]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[8]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[9]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[9]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[10]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[10]"]] - 100.0);
        mc::FFVar g_1_48 = -(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[6]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_LG_producing"]]);
        mc::FFVar g_1_49 = -(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[7]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_LN_producing"]]);
        mc::FFVar g_1_50 = 1.7241379310344829*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]] + 1.5037593984962405*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[2]"]] + 1.5384615384615383*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[3]"]] + 1.2987012987012987*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[4]"]] + 1.25*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[5]"]] + 1.3333333333333333*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[6]"]] + 1.2658227848101264*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_PG98"]];
        mc::FFVar n_g_1_50= - g_1_50;
        mc::FFVar g_1_51 = 1.7241379310344829*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]] + 1.5037593984962405*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[2]"]] + 1.5384615384615383*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[3]"]] + 1.2987012987012987*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[4]"]] + 1.25*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[5]"]] + 1.3333333333333333*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[6]"]] + 1.3157894736842106*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_ES95"]];
        mc::FFVar n_g_1_51 = - g_1_51;
        mc::FFVar g_1_52 = 1.7241379310344829*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]] + 0.039473684210526314*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[2]"]] - 0.05*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_ES95"]];
        mc::FFVar g_1_53 = 1.7241379310344829*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]] + 0.039473684210526314*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[1]"]] - 0.05*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_PG98"]];
        mc::FFVar g_1_54 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[1]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_54 = - g_1_54;
        mc::FFVar g_1_55 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[1]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_55 = - g_1_55;
        mc::FFVar g_1_56 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[1]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_56 = - g_1_56;
        mc::FFVar g_1_57 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[4]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[1]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_57 = - g_1_57;
        mc::FFVar g_1_58 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[2]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_58 = - g_1_58;
        mc::FFVar g_1_59 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[2]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_59 = - g_1_59;
        mc::FFVar g_1_60 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[2]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_60 = - g_1_60;
        
        
        mc::FFVar g_1_61 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[4]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[2]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_61 = - g_1_61;
        mc::FFVar g_1_62 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[3]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_62 = - g_1_62;
        mc::FFVar g_1_63 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[3]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_63 = - g_1_63;
        mc::FFVar g_1_64 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[3]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_64 = - g_1_64;
        mc::FFVar g_1_65 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[4]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[3]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_65 = - g_1_65;
        mc::FFVar g_1_66 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[4]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_66 = - g_1_66;
        mc::FFVar g_1_67 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[4]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_67 = - g_1_67;
        mc::FFVar g_1_68 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[4]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_68 = - g_1_68;
        mc::FFVar g_1_69 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[4]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[4]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_69 = - g_1_69;
        mc::FFVar g_1_70 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[5]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_70 = - g_1_70;
        mc::FFVar g_1_71 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[5]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_71 = - g_1_71;
        mc::FFVar g_1_72 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[5]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_72 = - g_1_72;
        mc::FFVar g_1_73 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[4]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[5]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_73 = - g_1_73;
        mc::FFVar g_1_74 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[4]"]] - (0.009147927746696273*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]] + 0.009050097541352423*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]] + 0.008440267155692963*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]] + 0.019869525229591227*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]] + 0.011493397614084631*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]] + 0.005699085288896173*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]] + 0.015431771488609266*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]] + 0.012736305433586925*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]] + 0.01592750558065944*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]] + 0.011435655609155597*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]]);
        mc::FFVar n_g_1_74 = - g_1_74;
        mc::FFVar g_1_75 = 0.09*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer95"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[4]"]];
        mc::FFVar n_g_1_75 = - g_1_75;
        mc::FFVar g_1_76 = 0.12*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer100"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[4]"]];
        mc::FFVar n_g_1_76 = - g_1_76;
        mc::FFVar g_1_77 = 0.053*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_Mogas"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[4]"]];
        mc::FFVar n_g_1_77 = - g_1_77;
        mc::FFVar g_1_78 = 0.046*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_AGO"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[4]"]];
        mc::FFVar n_g_1_78 = - g_1_78;
        mc::FFVar g_1_79 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]];
        mc::FFVar n_g_1_79 = - g_1_79;
        mc::FFVar g_1_80 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]];
        mc::FFVar n_g_1_80 = - g_1_80;
        
        
        mc::FFVar g_1_81 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[2]"]];
        mc::FFVar n_g_1_81 = - g_1_81;
        mc::FFVar g_1_82 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[4]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_LG_producing"]];
        mc::FFVar n_g_1_82 = - g_1_82;
        mc::FFVar g_1_83 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[4]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_LG[5]"]] - 1.0;
        mc::FFVar n_g_1_83 = - g_1_83;
        mc::FFVar g_1_84 = -(-0.45*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_ES95"]] + 0.8552631578947368*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[2]"]] + 0.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]] + 0.6015037593984962*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[2]"]] + 1.2307692307692308*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[3]"]] + 0.6493506493506493*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[4]"]] + 0.625*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[5]"]] + 0.8666666666666667*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[6]"]] + 7.413793103448276*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[1]"]] + 7.379310344827587*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[1]"]] + 7.517241379310346*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[1]"]] + 7.258620689655173*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[1]"]] + 7.275862068965517*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[1]"]]);
        mc::FFVar g_1_85 = -0.8*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_ES95"]] + 0.8552631578947368*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[2]"]] + 0.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]] + 0.6015037593984962*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[2]"]] + 1.2307692307692308*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[3]"]] + 0.6493506493506493*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[4]"]] + 0.625*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[5]"]] + 0.8666666666666667*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[6]"]] + 7.413793103448276*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[1]"]] + 7.379310344827587*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[1]"]] + 7.517241379310346*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[1]"]] + 7.258620689655173*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[1]"]] + 7.275862068965517*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[1]"]];
        mc::FFVar g_1_86 = -(-0.5*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_PG98"]] + 0.8227848101265822*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[1]"]] + 0.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]] + 0.6015037593984962*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[2]"]] + 1.2307692307692308*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[3]"]] + 0.6493506493506493*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[4]"]] + 0.625*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[5]"]] + 0.8666666666666667*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[6]"]] + 7.413793103448276*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[2]"]] + 7.379310344827587*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[2]"]] + 7.517241379310346*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[2]"]] + 7.258620689655173*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[2]"]] + 7.275862068965517*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[2]"]]);
        mc::FFVar g_1_87 = -0.86*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_PG98"]] + 0.8227848101265822*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[1]"]] + 0.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]] + 0.6015037593984962*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[2]"]] + 1.2307692307692308*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[3]"]] + 0.6493506493506493*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[4]"]] + 0.625*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[5]"]] + 0.8666666666666667*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[6]"]] + 7.413793103448276*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[2]"]] + 7.379310344827587*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[2]"]] + 7.517241379310346*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[2]"]] + 7.258620689655173*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[2]"]] + 7.275862068965517*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[2]"]];
        mc::FFVar g_1_88 = -(-98*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_PG98"]] + 132.91139240506328*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[1]"]] + 0.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]] + 136.8421052631579*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[2]"]] + 109.23076923076923*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[3]"]] + 123.37662337662337*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[4]"]] + 125.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[5]"]] + 124.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[6]"]] + 160.34482758620692*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[2]"]] + 159.48275862068968*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[2]"]] + 161.3793103448276*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[2]"]] + 159.82758620689657*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[2]"]] + 161.89655172413796*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[2]"]]);
        mc::FFVar g_1_89 = -(-95*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_ES95"]] + 131.57894736842104*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[2]"]] + 0.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]] + 136.8421052631579*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[2]"]] + 109.23076923076923*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[3]"]] + 123.37662337662337*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[4]"]] + 125.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[5]"]] + 124.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[6]"]] + 160.34482758620692*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[1]"]] + 159.48275862068968*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[1]"]] + 161.3793103448276*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[1]"]] + 159.82758620689657*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[1]"]] + 161.89655172413796*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[1]"]]);
        mc::FFVar g_1_90 = -10*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_PG98"]] + 6.329113924050633*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[1]"]] + 0.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[1]"]] + 7.518796992481203*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[2]"]] + 4.615384615384615*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[3]"]] + 11.688311688311687*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[4]"]] + 11.25*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[5]"]] + 14.666666666666666*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_PG98[6]"]] + 5.172413793103448*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[2]"]] + 5.00000000000001*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[2]"]] + 4.6551724137930846*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[2]"]] + 6.379310344827592*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[2]"]] + 6.379310344827592*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[2]"]];
        
        mc::FFVar g_1_91 = -10*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_ES95"]] + 5.2631578947368425*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[2]"]] + 0.0*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[1]"]] + 7.518796992481203*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[2]"]] + 4.615384615384615*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[3]"]] + 11.688311688311687*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[4]"]] + 11.25*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[5]"]] + 14.666666666666666*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_ES95[6]"]] + 5.172413793103448*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_CDU_LG[1]"]] + 5.00000000000001*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer95_LG[1]"]] + 4.6551724137930846*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Reformer100_LG[1]"]] + 6.379310344827592*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Mogas_LG[1]"]] + 6.379310344827592*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_AGO_LG[1]"]];
        mc::FFVar g_1_92 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_CGO[1]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_3[2]"]];
        mc::FFVar n_g_1_92 = - g_1_92;
        mc::FFVar g_1_93 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_CGO[1]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_2"]];
        mc::FFVar n_g_1_93 = - g_1_93;
        mc::FFVar g_1_94 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_CGO[1]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_CGO"]];
        mc::FFVar n_g_1_94 = - g_1_94;
        mc::FFVar g_1_95 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_CGO[2]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_3[2]"]];
        mc::FFVar n_g_1_95 = - g_1_95;
        mc::FFVar g_1_96 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_CGO[2]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_2"]];
        mc::FFVar n_g_1_96 = - g_1_96;
        mc::FFVar g_1_97 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_CGO[2]"]] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_CGO"]];
        mc::FFVar n_g_1_97 = - g_1_97;
        mc::FFVar g_1_98 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[3]"]] - 0.446*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_Mogas"]];
        mc::FFVar n_g_1_98 = - g_1_98;
        mc::FFVar g_1_99 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[3]"]] - 0.511*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_AGO"]];
        mc::FFVar n_g_1_99 = - g_1_99;
        mc::FFVar g_1_100 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_CGO[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["fraction_CGO[2]"]] - 1.0;
        mc::FFVar n_g_1_100 = - g_1_100;
        
        mc::FFVar g_1_101 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[1]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[1]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_3[2]"]];
        mc::FFVar n_g_1_101 = - g_1_101;
        mc::FFVar g_1_102 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[2]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[2]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_2"]];
        mc::FFVar n_g_1_102 = - g_1_102;
        mc::FFVar g_1_103 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[3]"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[3]"]] - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_CGO"]];
        mc::FFVar n_g_1_103 = - g_1_103;
        mc::FFVar g_1_104 = -this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_HF"]] + 1.0204081632653061*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[5]"]] + 1.0526315789473684*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_2"]] + 1.0655301012253595*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[1]"]] + 1.175640724194686*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[1]"]] + 1.032844453625284*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[2]"]] + 1.1641443538998837*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[2]"]] + 1.0612331529236974*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[3]"]] + 1.188636633781053*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[3]"]] + 1.060108131029365*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[4]"]] + 1.183431952662722*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[4]"]] + 1.0360547036883547*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[5]"]] + 1.166452816983553*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[5]"]] + 1.0280662074637608*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[6]"]] + 1.1510128913443831*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[6]"]] + 1.0559662090813096*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[7]"]] + 1.1899095668729176*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[7]"]] + 1.020512297173181*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[8]"]] + 1.1810558639423645*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[8]"]] + 1.0458063166701526*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[9]"]] + 1.1796626164916835*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[9]"]] + 1.0325245224574084*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[10]"]] + 1.1684973124561813*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[10]"]];
        mc::FFVar n_g_1_104 = - g_1_104;
        mc::FFVar g_1_105 = -(34.629728289824186*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[1]"]] + 2.962614624970609*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[1]"]] + 71.88597397231976*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[2]"]] + 3.39930151338766*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[2]"]] + 40.53910644168524*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[3]"]] + 3.1023416141685485*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[3]"]] + 45.26661719495389*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[4]"]] + 3.0295857988165684*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[4]"]] + 89.61873186904269*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[5]"]] + 3.0910999650064155*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[5]"]] + 77.61899866351393*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[6]"]] + 3.39548802946593*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[6]"]] + 44.66737064413939*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[7]"]] + 2.974773917182294*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[7]"]] + 45.92305337279314*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[8]"]] + 2.9644502184953345*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[8]"]] + 55.95063794185317*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[9]"]] + 3.0907160552082105*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[9]"]] + 56.99535363964894*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[10]"]] + 3.119887824258004*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[10]"]] + (12.2*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[2]"]] + 11.65*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[2]"]])/0.95 - 30*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_HF"]]);
        mc::FFVar g_1_106 = 34.629728289824186*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[1]"]] + 2.962614624970609*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[1]"]] + 71.88597397231976*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[2]"]] + 3.39930151338766*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[2]"]] + 40.53910644168524*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[3]"]] + 3.1023416141685485*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[3]"]] + 45.26661719495389*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[4]"]] + 3.0295857988165684*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[4]"]] + 89.61873186904269*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[5]"]] + 3.0910999650064155*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[5]"]] + 77.61899866351393*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[6]"]] + 3.39548802946593*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[6]"]] + 44.66737064413939*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[7]"]] + 2.974773917182294*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[7]"]] + 45.92305337279314*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[8]"]] + 2.9644502184953345*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[8]"]] + 55.95063794185317*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[9]"]] + 3.0907160552082105*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[9]"]] + 56.99535363964894*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_1[10]"]] + 3.119887824258004*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_HF_3[10]"]] + (12.2*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[2]"]] + 11.65*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[2]"]])/0.95 - 33*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["volume_HF"]];
        mc::FFVar g_1_107 = -0.0015*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Import[4]"]] + 0.140588513077039*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[1]"]] - 0.000789557434614805*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[1]"]] + 0.309219599235616*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[2]"]] + 5.3597996178079976e-05*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[2]"]] + 0.16502807856732*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[3]"]] - 0.0006673596071634*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[3]"]] + 0.211405808207417*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[4]"]] - 0.000435470958962915*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[4]"]] + 0.264982491043895*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[5]"]] - 0.00016758754478052502*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[5]"]] + 0.7602297836086701*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[6]"]] + 0.0023086489180433505*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[6]"]] + 0.632862056891616*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[7]"]] + 0.0016718102844580796*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[7]"]] + 1.575235109424405*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[8]"]] + 0.006383675547122027*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[8]"]] + 0.289990315101932*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[9]"]] - 4.2548424490339905e-05*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[9]"]] + 1.087848038245218*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_1[10]"]] + 0.003946740191226091*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_2[10]"]] + 0.0985*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_3[1]"]] + 1.6784999999999999*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[1]"]] + 2.0985*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[1]"]] + 0.0084*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_AGO[3]"]] + 0.0105*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["blin_Cracker_Mogas[3]"]] - 0.0015*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_AGO_3[3]"]];
        mc::FFVar g_1_108 = -(1.3*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[1]"]] + 1.2*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[2]"]] + 1.1*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Burn[3]"]] - 0.019*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer95"]] - 0.026*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer100"]] - 0.007*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_Mogas"]] - 0.007*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_AGO"]] - 0.04*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Isomerisation"]] - 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_CGO"]] - 15.2 - (0.018*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[1]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[1]"]] + 0.018*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[2]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[2]"]] + 0.018*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[3]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[3]"]] + 0.018*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[4]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[4]"]] + 0.018*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[5]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[5]"]] + 0.018*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[6]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[6]"]] + 0.018*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[7]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[7]"]] + 0.018*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[8]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[8]"]] + 0.018*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[9]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[9]"]] + 0.018*this->X[ScenarioNames::SCENARIO1][this->first_stage_map["CrudeQuantity[10]"]] + 0.02*this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Desulphurisation_1[10]"]]));
        mc::FFVar g_1_109 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_Mogas"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Cracker_AGO"]] - 175;
        mc::FFVar g_1_110 = this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer95"]] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx + this->second_stage_map["flow_Reformer100"]] - 65;
        




        objective +=
        this->probability*(
            3.2*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Cracker_Mogas")]
        + 3*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Cracker_AGO")]
        + 2.7*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Reformer95")]
        + 3.2*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Reformer100")]
        + 6*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Isomerisation")]
        + 3.345671410129097*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_CGO")]
        - 561.6*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_LG_producing")]
        - 1003*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_LN_producing")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_2")]
        + 2.3942543643299556*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[1]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[1]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[1]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[1]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[1]")]
        + 864.3999526122498*this->X[ScenarioNames::SCENARIO1][this->first_stage_map.at("CrudeQuantity[1]")]
        + 2.485328036981826*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[2]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[2]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[2]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[2]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[2]")]
        + 765.9539842873176*this->X[ScenarioNames::SCENARIO1][this->first_stage_map.at("CrudeQuantity[2]")]
        + 2.437662761144984*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[3]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[3]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[3]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[3]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[3]")]
        + 824.9058168463453*this->X[ScenarioNames::SCENARIO1][this->first_stage_map.at("CrudeQuantity[3]")]
        + 2.4589973078611767*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[4]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[4]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[4]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[4]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[4]")]
        + 839.5184609869758*this->X[ScenarioNames::SCENARIO1][this->first_stage_map.at("CrudeQuantity[4]")]
        + 2.460163454262119*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[5]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[5]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[5]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[5]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[5]")]
        + 779.3929097293013*this->X[ScenarioNames::SCENARIO1][this->first_stage_map.at("CrudeQuantity[5]")]
        + 2.760038638583934*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[6]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[6]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[6]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[6]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[6]")]
        + 692.8115942028985*this->X[ScenarioNames::SCENARIO1][this->first_stage_map.at("CrudeQuantity[6]")]
        + 2.7649237751065976*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[7]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[7]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[7]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[7]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[7]")]
        + 878.862094037809*this->X[ScenarioNames::SCENARIO1][this->first_stage_map.at("CrudeQuantity[7]")]
        + 3.39343900683156*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[8]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[8]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[8]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[8]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[8]")]
        + 735.8113207547168*this->X[ScenarioNames::SCENARIO1][this->first_stage_map.at("CrudeQuantity[8]")]
        + 2.5052287966283195*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[9]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[9]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[9]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[9]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[9]")]
        + 810.2870478413071*this->X[ScenarioNames::SCENARIO1][this->first_stage_map.at("CrudeQuantity[9]")]
        + 3.025222449696517*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_Desulphurisation_1[10]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_1[10]")]
        - 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_2[10]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_1[10]")]
        - 637*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_HF_3[10]")]
        + 749.7063627084043*this->X[ScenarioNames::SCENARIO1][this->first_stage_map.at("CrudeQuantity[10]")]
        - (1231*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_PG98[1]")]
            + 1194*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_ES95[1]")]
            + 1231*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_PG98[2]")]
            + 1194*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_ES95[2]")]
            + 1231*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_PG98[3]")]
            + 1194*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_ES95[3]")]
            + 1231*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_PG98[4]")]
            + 1194*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_ES95[4]")]
            + 1231*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_PG98[5]")]
            + 1194*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_ES95[5]")]
            + 1231*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_PG98[6]")]
            + 1194*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_ES95[6]")])
        - (923*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_JPF[1]")]
            + 923*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_JPF[2]")])
        - (907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_3[1]")]
            + 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_3[2]")]
            + 907*this->X[ScenarioNames::SCENARIO1][n_first_stage_vars + this->second_stage_map.at("flow_AGO_3[3]")])
        );


        std::vector<mc::FFVar> temp = {

            g_0_0,g_0_1,g_0_2,g_0_3,g_0_4,g_0_5,g_0_6,g_0_7,g_0_8,g_0_9,
            
            g_0_10,g_0_11,g_0_12,g_0_13,g_0_14,g_0_15,
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
            n_g_1_101,n_g_1_102,n_g_1_103,n_g_1_104
            
            };
        this->F[ScenarioNames::SCENARIO1].insert(this->F[ScenarioNames::SCENARIO1].end(), temp.begin(), temp.end());
        
    }
    this->F[ScenarioNames::SCENARIO1].insert(this->F[ScenarioNames::SCENARIO1].begin(), objective);
}


Ipopt::SmartPtr<STModel> CrudeModel::clone(solveFullmodel flag){
    Ipopt::SmartPtr<CrudeModel> p = new CrudeModel();

    p->scenario_name=this->scenario_name;
    p->first_stage_IX=this->first_stage_IX;
    p->second_stage_IX=this->second_stage_IX;
    p->perturb=this->perturb;
    p->scenario_names=this->scenario_names;
    p->probability=this->probability;
    p->first_stage_map=this->first_stage_map;
    p->second_stage_map=this->second_stage_map;
    p->clearDAG(); // clear the DAG of the cloned model
    if (flag == solveFullmodel::no){
        p->buildDAG(); // build the model for the cloned model
    }else{
        p->buildFullModelDAG(); // build the full model for the cloned model
    }

    return p;
}

