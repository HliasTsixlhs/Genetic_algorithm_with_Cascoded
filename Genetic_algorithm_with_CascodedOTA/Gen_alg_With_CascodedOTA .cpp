#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include <time.h>
#include <limits.h>
#include <float.h>

// functions Declaration

//Functios For Simple_OTA
void Generate_Randoms(int lowerLength, int upperLength,double lowerIC,double upperIC,int lowerIbias,int upperIbias,struct device Mosfets[],double *Ibias);
void Initialize_TypeDevices(struct device Mosfets[]);
void Calculate_Mosfets_Parameters(struct device Mosfets[],double Ibias);
double Transconductance_Calc(double Ibias,double IC);
double OutputResistance_Calc(double L4,double L6,double Ibias);
double VoltageGain_Calc(double GM,double Rout);
double FrequencyResponse_Calc(struct device Mosfets[]);
double PhaseMargin_Calc(struct device Mosfets[]);
double Thermal_Noise_Calc(struct device Mosfets[]);
double Flicker_Noise_Calc(struct device Mosfets[]);
double Offset_Voltage_input_DueTo_Mismatch_Calc(struct device Mosfets[]);
void Create_Genocide(int lowerLength, int upperLength,int lowerIC,int upperIC,int IndextFirstParent,int IndexSecondParent,struct SimpleOTA SimpleOTA_Designs[],int NumberOfChilds);
double Input_Capacitance_Calc(struct device Mosfets[]);
double Output_Capacitance_Calc(struct device Mosfets[]);
double Slew_Rate_Calc(double COUT,double Ibias);
double VINCM_Plus_Calc(struct device Mosfets[]);
double VINCM_Minus_Calc(struct device Mosfets[]);
double Maximun_Output_Voltage_Calc(struct device Mosfets[]);
double Minimum_Output_Voltage_Calc(struct device Mosfets[]);
double Power_Consumption_Calc(double Ibias);
void Create_new_Generation(int IndextFirstParent,int IndexSecondParent,	struct SimpleOTA SimpleOTA_Designs[],int NumberOfChilds,int lowerIbias,int upperIbias,int lowerLength, int upperLength,double lowerIC,double upperIC);
void Create_txt_data (struct SimpleOTA Best_Design);
struct data_sheet Initialize_data_sheet(struct data_sheet data_sheet);
void Create_and_Calculate_txt_data_for_FOMs (struct SimpleOTA Best_SimpleOTA_Designs[],int Length);
void Generate_Randoms_with_different_ICs(int lowerLength, int upperLength,double IC_Ranges_CurrentMirrorOTA[],int lowerIbias,int upperIbias,struct device Mosfets[],double *Ibias);
void Create_new_Generation_with_different_ICs(int IndextFirstParent,int IndexSecondParent,	struct SimpleOTA SimpleOTA_Designs[],int NumberOfChilds,int lowerIbias,int upperIbias,int lowerLength, int upperLength,double IC_Ranges_CurrentMirrorOTA[]);



//Functios For Casoced_OTA
void Generate_Randoms_CascodedOTA(int lowerLength, int upperLength,double lowerIC,double upperIC,int lowerIbias,int upperIbias,struct device Mosfets[],double *Ibias); 
void Initialize_TypeDevices_CascodedOTA(struct device Mosfets[]);
void Calculate_Mosfets_Parameters_CascodedOTA(struct device Mosfets[],double Ibias);
double Transconductance_Calc_CascodedOTA(double Ibias,double IC1);
double OutputResistance_Calc_CascodedOTA(struct device Mosfets[],double Ibias);
double VoltageGain_Calc_CascodedOTA(double GM,double Rout);
double Thermal_Noise_Calc_CascodedOTA(struct device Mosfets[]);
double Flicker_Noise_Calc_CascodedOTA(struct device Mosfets[]);
double Offset_Voltage_input_DueTo_Mismatch_Calc_CascodedOTA(struct device Mosfets[]);
double VINCM_Plus_Calc_CascodedOTA(struct device Mosfets[]);
double VINCM_Minus_Calc_CascodedOTA(struct device Mosfets[]);
double Maximun_Output_Voltage_Calc_CascodedOTA(struct device Mosfets[]);
double Minimum_Output_Voltage_Calc_CascodedOTA(struct device Mosfets[]);
double Power_Consumption_Calc_CascodedOTA(double Ibias);
double Input_Capacitance_Calc_CascodedOTA(struct device Mosfets[]);
double Output_Capacitance_Calc_CascodedOTA(struct device Mosfets[]);
double Slew_Rate_Calc_CascodedOTA(double COUT,double Ibias);
double FrequencyResponse_Calc_CascodedOTA(struct device Mosfets[]);
double PhaseMargin_Calc_CascodedOTA(struct device Mosfets[]);
void Create_new_Generation_CascodedOTA(int IndextFirstParent,int IndexSecondParent,	struct CascodedOTA CascodedOTA_Designs[],int NumberOfChilds,int lowerIbias,int upperIbias,int lowerLength, int upperLength,double lowerIC,double upperIC);
void Create_txt_data_CascodedOTA (struct CascodedOTA Best_Design);
void Create_and_Calculate_txt_data_for_FOMs_CascodedOTA(struct CascodedOTA Best_CascodedOTA_Designs[],int Length);
void Generate_Randoms_CascodedOTA_with_different_ICs(int lowerLength, int upperLength,double IC_Ranges_CascodedOTA[],int lowerIbias,int upperIbias,struct device Mosfets[],double *Ibias);
void Create_new_Generation_CascodedOTA_with_different_ICs(int IndextFirstParent,int IndexSecondParent,	struct CascodedOTA CascodedOTA_Designs[],int NumberOfChilds,int lowerIbias,int upperIbias,int lowerLength, int upperLength,double IC_Ranges_CurrentMirrorOTA[]);
	
	
	
	struct data_sheet{
		double n0_nmos;
		double n0_pmos;
		double Ut;
		double Lsat;
		double Val_nmos; // 8 V/um   
		double Val_pmos; // 8 V/um 
		double Cox; //0.0069 F/m^2 => 6.9 ff/um^2
		double u0_nmos; // cm^2/V*s
		double u0_pmos; // cm^2/V*s
		double Io_nmos; // 0.539252351227600e-06 A or 0.539252351227600 uA
		double Io_pmos; // 0.164269005014000e-06 A or 0.164269005014000 uA
		double T; // temperature at 300 K
		double k; // Boltzmann's constant , J/K 
		double VT_nmos; // 200mV //Prepei na to kanw extaction apo device me L=2000nm
		double VT_pmos; // 200mV //Prepei na to kanw extaction apo device me L=2000nm
		double KF_nmos;
	  	double KF_nmos_hand_sqr;
	    double AF_nmos;
	    double KF_pmos; 
		double KF_pmos_hand_sqr;
		double AF_pmos;
		double AVTO_nmos; //V*um //Autes oi times einai apo thn texnologia twn 0.5um toy Binkley !!!
		double AVTO_pmos; //V*um //Autes oi times einai apo thn texnologia twn 0.5um toy Binkley !!!
		
		double CJ_nmos; // ff/um^2    // process area capacitance
		double CJ_pmos; // ff/um^2   //process perimeter capacitance
		double CJSW_nmos; // ff/um
		double CJSW_pmos; // ff/um
		double Wdif; // Assumeing 25nm !!! // Wdif : is the process width of drain fingers.
		
		// For all designs  
		double VDD; // (Volts)
		double VSS; // (Volts)
		double CL; // Load capacitance (f)
		
		//powers for FOM
		double a0;
		double a1;
		double a2;
		double a3;
		double a4;
		double a5;
		double a6;
		double a7;
		double a8;
		double a9;
		
		//IC_Ranges_for_Current_Mirror_Load_OTA
		double IC_Ranges_CurrentMirrorOTA[10];
		//IC_Ranges_for_Cascoded_OTA
		double IC_Ranges_CascodedOTA[12];
		
	}data_sheet = Initialize_data_sheet(data_sheet);
    


//Global Variables
	double n0_nmos = data_sheet.n0_nmos;
	double n0_pmos = data_sheet.n0_pmos;
	double Lsat = data_sheet.Lsat;
	double Ut = data_sheet.Ut;
	double Val_nmos = data_sheet.Val_nmos; // 8 V/um   
	double Val_pmos = data_sheet.Val_pmos; // 8 V/um 
	double Cox = data_sheet.Cox; //0.0069 F/m^2 => 6.9 ff/um^2
	double u0_nmos = data_sheet.u0_nmos; // cm^2/V*s
	double u0_pmos = data_sheet.u0_pmos; // cm^2/V*s
	double Io_nmos = data_sheet.Io_nmos; // 0.539252351227600e-06 A or 0.539252351227600 uA
	double Io_pmos = data_sheet.Io_pmos; // 0.164269005014000e-06 A or 0.164269005014000 uA
	double T = data_sheet.T; // temperature at 300 K
	double k = data_sheet.k; // Boltzmann's constant , J/K 
	double VT_nmos = data_sheet.VT_nmos; // 200mV //Prepei na to kanw extaction apo device me L=2000nm
	double VT_pmos = data_sheet.VT_pmos; // 200mV //Prepei na to kanw extaction apo device me L=2000nm
	//double KF_nmos = 2.7e-25; // C^2/cm^2 h' C^2/um^2 ?? -- upothetw um^2  // Prepei na elenksw tis monades!!! Egw to thelw se KF_hand = KF/Cox (nV)^2*um^2 
	double KF_nmos = pow(data_sheet.KF_nmos_hand_sqr,2); // (nV)^2*um^2 -- Auto einai to KF_hand_nmos
    double AF_nmos = data_sheet.AF_nmos;
    //double KF_pmos = 0.9e-25; // C^2/cm^2 h' C^2/m^2 ?? -- upothetw m^2  // Prepei na elenksw tis monades!!! Egw to thelw se KF_hand = KF/Cox (nV)^2*um^2 
    double KF_pmos = pow(data_sheet.KF_pmos_hand_sqr,2); // (nV)^2*um^2 -- Auto einai to KF_hand_pmos
	double AF_pmos = data_sheet.AF_pmos;
	double AVTO_nmos = data_sheet.AVTO_nmos; //V*um //Autes oi times einai apo thn texnologia twn 0.5um toy Binkley !!!
	double AVTO_pmos = data_sheet.AVTO_pmos; //V*um //Autes oi times einai apo thn texnologia twn 0.5um toy Binkley !!!
	
	//Autes oi times prepei na elenxthoun me ton Niko :O
	double CJ_nmos  = data_sheet.CJ_nmos; // ff/um^2    // process area capacitance
	double CJ_pmos = data_sheet.CJ_pmos; // ff/um^2   //process perimeter capacitance
	double CJSW_nmos = data_sheet.CJSW_nmos; // ff/um
	double CJSW_pmos = data_sheet.CJSW_pmos; // ff/um
	double Wdif = data_sheet.Wdif; // Assumeing 25nm !!! // Wdif : is the process width of drain fingers.
	
	// For all designs  
	double VDD = data_sheet.VDD; // (Volts)
	double VSS = data_sheet.VSS; // (Volts)
	double C_LOAD = data_sheet.CL;
	
	//Powers for FOM    
	//Must be in Range [0.2-1.8] 
	double a0_OTA_VoltageGain = data_sheet.a0; 
	double a1_OTA_FrequencyResponse = data_sheet.a1;
	double a2_OTA_Thermal_Noise = data_sheet.a2;
	double a3_OTA_Flicker_Noise = data_sheet.a3;
	double a4_OTA_Offset_Voltage_input_DueTo_Mismatch = data_sheet.a4;
	double a5_OTA_Slew_Rate = data_sheet.a5;
	double a6_OTA_Input_Voltage_Range = data_sheet.a6;
	double a7_OTA_Output_Voltage_Range = data_sheet.a7;
	double a8_OTA_PhaseMargin = data_sheet.a8;
	double a9_OTA_Power_Consumption = data_sheet.a9;
	
	
	struct device
	{
		double L;
		double IC;
		double IC_WithOutVS;
		double lamdaC; //Velociry Saturation and VFMR factor
		//These parameters will be initialized for the type of the devices ( nmos - pmos )
		double n0;
		double u0;
		double Io;
		double VT;
		double KF;	 
		double AF;
		double AVTO;
		double CJ;
		double CJSW;
		// These parameters will not be initialized ( They will be calculated )
		double W; 
		double Thermal_noise_factor;
		double gm;
		double VDSsat;
		
		
	};
	
		struct SimpleOTA
	{
		double Ibias;
		struct device Mosfets[10];
		//OTA specs
		double OTA_Transconductance;
		double OTA_OutputResistance;
		double OTA_VoltageGain;
		double OTA_FrequencyResponse;
		double OTA_PhaseMargin;
		double OTA_Thermal_Noise;
		double OTA_Flicker_Noise;
		double OTA_Offset_Voltage_input_DueTo_Mismatch;
		double OTA_Input_Capacitance;
		double OTA_Output_Capacitance;
		double OTA_Slew_Rate;
		double OTA_VINCM_Plus;
		double OTA_VINCM_Minus;
		double OTA_Maximun_Output_Voltage;
		double OTA_Minimum_Output_Voltage;
		double OTA_Power_Consumption;
		
	};
	
		struct CascodedOTA
	{
		double Ibias;
		struct device Mosfets[17];
		//OTA specs
		double OTA_Transconductance;
		double OTA_OutputResistance;
		double OTA_VoltageGain;
		double OTA_FrequencyResponse;
		double OTA_PhaseMargin;
		double OTA_Thermal_Noise;
		double OTA_Flicker_Noise;
		double OTA_Offset_Voltage_input_DueTo_Mismatch;
		double OTA_Input_Capacitance;
		double OTA_Output_Capacitance;
		double OTA_Slew_Rate;
		double OTA_VINCM_Plus;
		double OTA_VINCM_Minus;
		double OTA_Maximun_Output_Voltage;
		double OTA_Minimum_Output_Voltage;
		double OTA_Power_Consumption;
		
	};
	



int main()
{

    
	//Pick Mode Type	
	printf("For Curent_Mirror_Load_OTA with global range in ICs: Mode == 0");
	printf("\nFor Folded_Cascode_OTA  with global range in ICs: Mode == 1");
	printf("\nFor Curent_Mirror_Load_OTA with different ranges in ICs: Mode == 2");
	printf("\nFor Folded_Cascode_OTA with different ranges in ICs: Mode == 3");
	int Mode;   
    printf("\n\nPlease Pick a Mode: ");
    while(scanf("%d",&Mode) != 1 || Mode > 3 || Mode < 0 )
    {
        printf("\nWrong!!Please Pick a Mode: ");
        while(getchar() != '\n');
    }
    printf("You entered: %d\n",Mode);
    
   	//Pick The Lowest Length for the Design
	int Lowest_Length;
	printf("\n\nPick The Lowest Length for the Design");
	printf("\nPlease enter an integer equal or greater than 250 (it will be converted in nm): ");
    while(scanf("%d",&Lowest_Length) != 1 || Lowest_Length < 250)
    {
        printf("\nWrong!!\nPlease enter an integer equal or greater than 250 (it will be converted in nm): ");
        while(getchar() != '\n');
    }
    printf("You entered: %d\n",Lowest_Length);
    
   	//Pick The Highest_Length for the Design
   	int Highest_Length;
	printf("\n\nPick The Highest Length for the Design");
	printf("\nPlease enter an integer greater than Lowest Length (it will be converted in nm): ");
    while(scanf("%d",&Highest_Length) != 1 || Highest_Length <= Lowest_Length)
    {
        printf("\nWrong!!\nPlease enter an integer greater than Lowest Length (it will be converted in nm): ");
        while(getchar() != '\n');
    }
    printf("You entered: %d\n",Highest_Length);
    
    
    double Lowest_IC;
    double Highest_IC;
    
	if(Mode == 0 || Mode == 1){
   	//Pick The Lowest IC for the Design
	printf("\n\nPick The Lowest IC for the Design");
	printf("\nPlease enter a number equal or greater than 0.001 : ");
    while((scanf("%lf",&Lowest_IC) != 1 || Lowest_IC < 0.001))
    {	
        printf("\nPlease enter a number equal or greater than  0.001 : ");
         while(getchar() != '\n');
    }
    printf("You entered: %lf\n",Lowest_IC);
   
   	//Pick The Highest_IC for the Design
	printf("\n\nPick The Highest_IC for the Design");
	printf("\nPlease enter a number greater than Lowest IC : ");
    while(scanf("%lf",&Highest_IC) != 1 || Highest_IC <= Lowest_IC)
    {
        printf("\nPlease enter a number greater than Lowest IC : ");
        while(getchar() != '\n');
    }
    printf("You entered: %lf\n",Highest_IC);
	}

	//Pick the Number of childs 
	int NumberOfChilds;
	printf("\n\nPick the Number Of Childs for the Genetic Algorithm");
	printf("\nPlease enter an integer in Range 1-2000: ");
    while(scanf("%d",&NumberOfChilds) != 1 || NumberOfChilds > 2000 || NumberOfChilds < 1)
    {
        printf("\nWrong!!\nPlease enter an integer in Range 1-2000: ");
        while(getchar() != '\n');
    }
    printf("You entered: %d\n",NumberOfChilds);
	
	
	//Pick How many generations will be created

	int Number_Of_generation;
	printf("\n\nHow many generations you want to create ???");
	printf("\nPlease enter a positive integer: ");
    while(scanf("%d",&Number_Of_generation) != 1 || Number_Of_generation < 1)
    {
        printf("\nWrong!!\nPlease enter a positive integer: ");
        while(getchar() != '\n');
    }
    printf("You entered: %d\n",Number_Of_generation);
	
	
	
	

double Ibias_Table[1];	
	
	int Step;
	struct SimpleOTA SimpleOTA_Designs[NumberOfChilds];
	struct SimpleOTA Best_Design;
	struct SimpleOTA Pre_Last_Parent_Design;
//	printf("SimpleOTA_Designs's length:%d\n",sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA));
	struct SimpleOTA Best_SimpleOTA_Designs[sizeof(Ibias_Table)/sizeof(Ibias_Table[0])];

	struct CascodedOTA CascodedOTA_Designs[NumberOfChilds];
	struct CascodedOTA Best_Design_CascodedOTA;
	struct CascodedOTA Pre_Last_Parent_Design_CascodedOTA;
//	printf("CascodedOTA_Designs's length:%d\n",sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA));
	struct CascodedOTA Best_CascodedOTA_Designs[sizeof(Ibias_Table)/sizeof(Ibias_Table[0])];




int index_Ibias;
int j;
int i;
for (index_Ibias=0 ; index_Ibias < sizeof(Ibias_Table)/sizeof(Ibias_Table[0]) ; index_Ibias++){
	
    Step = 0;	
	//Ibias_Table[index_Ibias] = index_Ibias*2 + 2;
	Ibias_Table[index_Ibias] = 150;
		
	srand(time(0));	
		
//-----------------------------------------------------SimpleOTA--------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// initialize SimpleOTA Designs
	    
		// Use current time as  
    	// seed for random generator 
    	
		
		
		for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
			
			if(Mode == 0){
				//Generate Random numbers for Length and ICs for a design (1st two:Range for L in nanometers || 2nd two:Range for IC || 3rd two:Range for Ibias in uA)
				Generate_Randoms(Lowest_Length,Highest_Length,Lowest_IC,Highest_IC,Ibias_Table[index_Ibias],Ibias_Table[index_Ibias],SimpleOTA_Designs[i].Mosfets,&(SimpleOTA_Designs[i].Ibias));
			}
			else if(Mode == 2){
				//Generate Random numbers for Length and ICs for a design (1st two:Range for L in nanometers || 2nd two:Range for IC || 3rd two:Range for Ibias in uA)
				Generate_Randoms_with_different_ICs(Lowest_Length,Highest_Length,data_sheet.IC_Ranges_CurrentMirrorOTA,Ibias_Table[index_Ibias],Ibias_Table[index_Ibias],SimpleOTA_Designs[i].Mosfets,&(SimpleOTA_Designs[i].Ibias));
			}
			
			//Initialize_TypeDevices for each Design
			Initialize_TypeDevices(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Mosfets Parameters for each design  ( Calculate_Mosfets_Parameters(struct device Mosfets[],double Ibias) )
			Calculate_Mosfets_Parameters(SimpleOTA_Designs[i].Mosfets,SimpleOTA_Designs[i].Ibias);
			printf("\n");
		}
		

		
/*		//test print for initialization and Parameters Calculations
		
		for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
			printf("\nFor Design:%d\n",i);
			printf("Ibias:%g\n",SimpleOTA_Designs[i].Ibias);
			for (j=0;j<10;j++){
				printf("L%d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].L);
				printf("IC%d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].IC);
				
				printf("W%d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].W);
				printf("Thermal_noise_factor%d:%g ",j,SimpleOTA_Designs[i].Mosfets[j].Thermal_noise_factor);
				printf("gm%d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].gm);
				printf("u0 %d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].u0);
				printf("n0 %d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].n0);
				printf("Io %d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].Io);
				printf("\n"); 
			}
		}
*/

// Calculate Specs For each OTA
		for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
			//Calculate Transconductance (GM) for each Design {Transconductance_Calc(int Ibias,double IC1)}
			SimpleOTA_Designs[i].OTA_Transconductance = Transconductance_Calc(SimpleOTA_Designs[i].Ibias,SimpleOTA_Designs[i].Mosfets[0].IC);
			
			//Calculate OutputResistance (Rout) for each Design {OutputResistance_Calc(double L4,double L6,double Ibias)}
			SimpleOTA_Designs[i].OTA_OutputResistance = OutputResistance_Calc(SimpleOTA_Designs[i].Mosfets[3].L,SimpleOTA_Designs[i].Mosfets[5].L,SimpleOTA_Designs[i].Ibias);
			
			//Calculate VoltageGain (Av) for each Design {VoltageGain_Calc(double GM,double Rout)}
			SimpleOTA_Designs[i].OTA_VoltageGain = VoltageGain_Calc(SimpleOTA_Designs[i].OTA_Transconductance,SimpleOTA_Designs[i].OTA_OutputResistance);
			
			//Calculate FrequencyResponse (f-3dB) for each Design {FrequencyResponse_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_FrequencyResponse = FrequencyResponse_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate PhaseMargin (PM) for each Design {PhaseMargin_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_PhaseMargin = PhaseMargin_Calc(SimpleOTA_Designs[i].Mosfets);
					
			//Calculate ThermalNoise (Svin(thermal)) for each Design {double Thermal_Noise_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Thermal_Noise = Thermal_Noise_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate FlickerNoise (Svin(flicker)) for each Design {double Flicker_Noise_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Flicker_Noise = Flicker_Noise_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Offset_Voltage due to Local-Area Mismatch (Vsquare_InOffset) for each Design {Offset_Voltage_input_DueTo_Mismatch_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch = Offset_Voltage_input_DueTo_Mismatch_Calc(SimpleOTA_Designs[i].Mosfets);
		
			//Calculate Input_Capacitance (Cindif) for each Design {Input_Capacitance_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Input_Capacitance = Input_Capacitance_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Output_Capacitance (COUT) for each Design {Output_Capacitance_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Output_Capacitance = Output_Capacitance_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Slew_Rate (SR) for each Design {Slew_Rate_Calc(double COUT,double Ibias)}
			SimpleOTA_Designs[i].OTA_Slew_Rate = Slew_Rate_Calc(SimpleOTA_Designs[i].OTA_Output_Capacitance,SimpleOTA_Designs[i].Ibias);
			
			// Calculate VINCM_Plus (VINCM+) for each Design  {VINCM_Plus_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_VINCM_Plus = VINCM_Plus_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate VINCM_Minus (VINCM-) for each Design {VINCM_Minus_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_VINCM_Minus = VINCM_Minus_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Maximun_Output_Voltage (Vout+) for each Design {Maximun_Output_Voltage_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage = Maximun_Output_Voltage_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Minimum_Output_Voltage (Vout-) for each Design {Minimum_Output_Voltage_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage = Minimum_Output_Voltage_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Power_Consumption (PC) for each Design {Power_Consumption_Calc(double Ibias)}
			SimpleOTA_Designs[i].OTA_Power_Consumption = Power_Consumption_Calc(SimpleOTA_Designs[i].Ibias);	
		}
		
	/*	//test print for Specs Calculation
		for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
			printf("\nFor Design:%d\n",i);
			printf("Ibias:%g\n",SimpleOTA_Designs[i].Ibias);
			printf("OTA_Transconductance:%g\n",SimpleOTA_Designs[i].OTA_Transconductance);
			printf("OTA_OutputResistance:%g\n",SimpleOTA_Designs[i].OTA_OutputResistance);
			printf("OTA_VoltageGain:%g\n",SimpleOTA_Designs[i].OTA_VoltageGain);
			printf("OTA_FrequencyResponse:%g\n",SimpleOTA_Designs[i].OTA_FrequencyResponse);
			printf("OTA_PhaseMargin:%g\n",SimpleOTA_Designs[i].OTA_PhaseMargin);
			printf("OTA_Thermal_Noise:%g\n",SimpleOTA_Designs[i].OTA_Thermal_Noise);
			printf("OTA_Flicker_Noise:%g\n",SimpleOTA_Designs[i].OTA_Flicker_Noise);
			printf("OTA_Offset_Voltage due to Local-Area Mismatch:%g",SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch);
			printf("OTA_Input_Capacitance:%g",SimpleOTA_Designs[i].OTA_Input_Capacitance);
			
			
			printf("OTA_Output_Capacitance:%g",SimpleOTA_Designs[i].OTA_Output_Capacitance);
			printf("OTA_Slew_Rate:%g",SimpleOTA_Designs[i].OTA_Slew_Rate);
			printf("OTA_VINCM_Plus:%g",SimpleOTA_Designs[i].OTA_VINCM_Plus);
			printf("OTA_VINCM_Minus:%g",SimpleOTA_Designs[i].OTA_VINCM_Minus);
			printf("OTA_Maximun_Output_Voltage:%g",SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage);
			printf("OTA_Minimum_Output_Voltage:%g",SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage);
			printf("OTA_Power_Consumption:%g",SimpleOTA_Designs[i].OTA_Power_Consumption);	
			printf("\n");
		}*/
		
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------





//-----------------------------------------------------Cascoded_OTA-----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------




// initialize Cascoded_OTA Designs
	    
		// Use current time as  
    	// seed for random generator 
    	
		for (i=0;i<sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA);i++){
			if(Mode == 1){
				//Generate Random numbers for Length and ICs for a design (1st two:Range for L in nanometers || 2nd two:Range for IC || 3rd two:Range for Ibias in uA)
				Generate_Randoms_CascodedOTA(Lowest_Length,Highest_Length,Lowest_IC,Highest_IC,Ibias_Table[index_Ibias],Ibias_Table[index_Ibias],CascodedOTA_Designs[i].Mosfets,&(CascodedOTA_Designs[i].Ibias));
			}
			else if(Mode == 3){
				//Generate Random numbers for Length and ICs for a design (1st two:Range for L in nanometers || 2nd two:Range for IC || 3rd two:Range for Ibias in uA)
				Generate_Randoms_CascodedOTA_with_different_ICs(Lowest_Length,Highest_Length,data_sheet.IC_Ranges_CascodedOTA,Ibias_Table[index_Ibias],Ibias_Table[index_Ibias],CascodedOTA_Designs[i].Mosfets,&(CascodedOTA_Designs[i].Ibias)); 
			}
			
    		//{Calculate_Mosfets_Parameters_CascodedOTA(struct device Mosfets[],double Ibias)}
    		Calculate_Mosfets_Parameters_CascodedOTA(CascodedOTA_Designs[i].Mosfets,CascodedOTA_Designs[i].Ibias);
			

			printf("\n");
		}

		//test print for initialization and Parameters Calculations
		
		for (i=0;i<sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA);i++){
			printf("\nFor Design:%d\n",i);
			printf("Ibias:%g\n",CascodedOTA_Designs[i].Ibias);
			for (j=0;j<17;j++){
				printf("L%d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].L);
				printf("IC%d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].IC);
				printf("IC_WithOutVS%d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS);
				
				printf("W%d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].W);
				printf("Thermal_noise_factor%d:%g ",j,CascodedOTA_Designs[i].Mosfets[j].Thermal_noise_factor);
				printf("gm%d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].gm);
				printf("u0 %d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].u0);
				printf("n0 %d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].n0);
				printf("Io %d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].Io);
				printf("\n"); 
			}
		}



// Calculate Specs For each CascodedOTA 
		for (i=0;i<sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA);i++){
			//Calculate Transconductance (GM) for each Design {Transconductance_Calc_CascodedOTA(double Ibias,double IC1)}
			CascodedOTA_Designs[i].OTA_Transconductance = Transconductance_Calc_CascodedOTA(CascodedOTA_Designs[i].Ibias,CascodedOTA_Designs[i].Mosfets[0].IC);
			
			//Calculate OutputResistance (Rout) for each Design {OutputResistance_Calc_CascodedOTA(struct device Mosfets[],double Ibias)}
			CascodedOTA_Designs[i].OTA_OutputResistance = OutputResistance_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets,CascodedOTA_Designs[i].Ibias);
			
			//Calculate VoltageGain (Av) for each Design {VoltageGain_Calc_CascodedOTA(double GM,double Rout)}
			CascodedOTA_Designs[i].OTA_VoltageGain = VoltageGain_Calc_CascodedOTA(CascodedOTA_Designs[i].OTA_Transconductance,CascodedOTA_Designs[i].OTA_OutputResistance);
			
			//Calculate FrequencyResponse (f-3dB) for each Design {FrequencyResponse_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_FrequencyResponse = FrequencyResponse_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate PhaseMargin (PM) for each Design {PhaseMargin_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_PhaseMargin = PhaseMargin_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
					
			//Calculate ThermalNoise (Svin(thermal)) for each Design {Thermal_Noise_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Thermal_Noise = Thermal_Noise_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate FlickerNoise (Svin(flicker)) for each Design {Flicker_Noise_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Flicker_Noise = Flicker_Noise_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Offset_Voltage due to Local-Area Mismatch (Vsquare_InOffset) for each Design {Offset_Voltage_input_DueTo_Mismatch_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch = Offset_Voltage_input_DueTo_Mismatch_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
		
			//Calculate Input_Capacitance (Cindif) for each Design {Input_Capacitance_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Input_Capacitance = Input_Capacitance_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Output_Capacitance (COUT) for each Design {Output_Capacitance_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Output_Capacitance = Output_Capacitance_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Slew_Rate (SR) for each Design {Slew_Rate_Calc_CascodedOTA(double COUT,double Ibias)}
			CascodedOTA_Designs[i].OTA_Slew_Rate = Slew_Rate_Calc_CascodedOTA(CascodedOTA_Designs[i].OTA_Output_Capacitance,CascodedOTA_Designs[i].Ibias);
			
			// Calculate VINCM_Plus (VINCM+) for each Design  {VINCM_Plus_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_VINCM_Plus = VINCM_Plus_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate VINCM_Minus (VINCM-) for each Design {VINCM_Minus_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_VINCM_Minus = VINCM_Minus_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Maximun_Output_Voltage (Vout+) for each Design {Maximun_Output_Voltage_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage = Maximun_Output_Voltage_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Minimum_Output_Voltage (Vout-) for each Design {Minimum_Output_Voltage_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage = Minimum_Output_Voltage_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Power_Consumption (PC) for each Design {Power_Consumption_Calc_CascodedOTA(double Ibias)}
			CascodedOTA_Designs[i].OTA_Power_Consumption = Power_Consumption_Calc_CascodedOTA(CascodedOTA_Designs[i].Ibias);	
		}


		//test print for Specs Calculation CascodedOTA_Designs
		for (i=0;i<sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA);i++){
			printf("\nFor Design:%d\n",i);
			printf("Ibias:%g\n",CascodedOTA_Designs[i].Ibias);
			printf("OTA_Transconductance:%g\n",CascodedOTA_Designs[i].OTA_Transconductance);
			printf("OTA_OutputResistance:%g\n",CascodedOTA_Designs[i].OTA_OutputResistance);
			printf("OTA_VoltageGain:%g\n",CascodedOTA_Designs[i].OTA_VoltageGain);
			printf("OTA_FrequencyResponse:%g\n",CascodedOTA_Designs[i].OTA_FrequencyResponse);
			printf("OTA_PhaseMargin:%g\n",CascodedOTA_Designs[i].OTA_PhaseMargin);
			printf("OTA_Thermal_Noise:%g\n",CascodedOTA_Designs[i].OTA_Thermal_Noise);
			printf("OTA_Flicker_Noise:%g\n",CascodedOTA_Designs[i].OTA_Flicker_Noise);
			printf("OTA_Offset_Voltage due to Local-Area Mismatch:%g\n",CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch);
			printf("OTA_Input_Capacitance:%g\n",CascodedOTA_Designs[i].OTA_Input_Capacitance);		
			printf("OTA_Output_Capacitance:%g\n",CascodedOTA_Designs[i].OTA_Output_Capacitance);
			printf("OTA_Slew_Rate:%g\n",CascodedOTA_Designs[i].OTA_Slew_Rate);
			printf("OTA_VINCM_Plus:%g\n",CascodedOTA_Designs[i].OTA_VINCM_Plus);
			printf("OTA_VINCM_Minus:%g\n",CascodedOTA_Designs[i].OTA_VINCM_Minus);
			printf("OTA_Maximun_Output_Voltage:%g\n",CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage);
			printf("OTA_Minimum_Output_Voltage:%g\n",CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage);
			printf("OTA_Power_Consumption:%g\n",CascodedOTA_Designs[i].OTA_Power_Consumption);	
			printf("\n");
		}



//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------------------		
		
		
	
	
	int Times_Same_Parents = 0; 
	int temp_firstParent;
	int temp_secondParent;
	int old_temp_firstParent = -1;
	int old_temp_secondParent = -1;
		
	double norm_OTA_VoltageGain_competitor;
	double norm_OTA_FrequencyResponse_competitor;
	double norm_OTA_Thermal_Noise_competitor;
	double norm_OTA_Flicker_Noise_competitor;
	double norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor;
	double norm_OTA_Slew_Rate_competitor;
	double norm_OTA_Input_Voltage_Range_competitor;
	double norm_OTA_Output_Voltage_Range_competitor;
	double norm_OTA_PhaseMargin_competitor;
	double norm_OTA_Power_Consumption_competitor;
	double FOM_competitor;
	
	double norm_OTA_VoltageGain_first;
	double norm_OTA_FrequencyResponse_first;
	double norm_OTA_Thermal_Noise_first;
	double norm_OTA_Flicker_Noise_first;
	double norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first;
	double norm_OTA_Slew_Rate_first;
	double norm_OTA_Input_Voltage_Range_first;
	double norm_OTA_Output_Voltage_Range_first;
	double norm_OTA_PhaseMargin_first;
	double norm_OTA_Power_Consumption_first;
	double FOM_first;
	
	double norm_OTA_VoltageGain_second;
	double norm_OTA_FrequencyResponse_second;
	double norm_OTA_Thermal_Noise_second;
	double norm_OTA_Flicker_Noise_second;
	double norm_OTA_Offset_Voltage_input_DueTo_Mismatch_second;
	double norm_OTA_Slew_Rate_second;
	double norm_OTA_Input_Voltage_Range_second;
	double norm_OTA_Output_Voltage_Range_second;
	double norm_OTA_PhaseMargin_second;
	double norm_OTA_Power_Consumption_second;
	double FOM_second;
	
	double norm_OTA_VoltageGain_best;
	double norm_OTA_FrequencyResponse_best;
	double norm_OTA_Thermal_Noise_best;
	double norm_OTA_Flicker_Noise_best;
	double norm_OTA_Offset_Voltage_input_DueTo_Mismatch_best;
	double norm_OTA_Slew_Rate_best;
	double norm_OTA_Input_Voltage_Range_best;
	double norm_OTA_Output_Voltage_Range_best;
	double norm_OTA_PhaseMargin_best;
	double norm_OTA_Power_Consumption_best;
	double FOM_best;
	

   
	do{
	
	
			if(Mode == 0 || Mode == 2){
			//Pick Parents For SimpleOTA
				//Initialize Temps for Parents
				temp_firstParent = 0 ;	
				temp_secondParent = 1 ;
				
				//find first Parent
				//temp_firstParent = 0 ;	
				for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
					// normalization of the characteristics for the first parent (compare to competitor) 
					norm_OTA_VoltageGain_first = SimpleOTA_Designs[temp_firstParent].OTA_VoltageGain/ ( (SimpleOTA_Designs[temp_firstParent].OTA_VoltageGain + SimpleOTA_Designs[i].OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_first = SimpleOTA_Designs[temp_firstParent].OTA_FrequencyResponse/ ( (SimpleOTA_Designs[temp_firstParent].OTA_FrequencyResponse + SimpleOTA_Designs[i].OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_first = SimpleOTA_Designs[temp_firstParent].OTA_Thermal_Noise/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Thermal_Noise + SimpleOTA_Designs[i].OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_first = SimpleOTA_Designs[temp_firstParent].OTA_Flicker_Noise/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Flicker_Noise + SimpleOTA_Designs[i].OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first = SimpleOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch + SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_first = SimpleOTA_Designs[temp_firstParent].OTA_Slew_Rate/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Slew_Rate + SimpleOTA_Designs[i].OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_first = (SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Plus-SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Minus)/ ( ((SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Plus-SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Minus) + (SimpleOTA_Designs[i].OTA_VINCM_Plus-SimpleOTA_Designs[i].OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_first = (SimpleOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage)/ ( ((SimpleOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage) + (SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_first = SimpleOTA_Designs[temp_firstParent].OTA_PhaseMargin/ ( (SimpleOTA_Designs[temp_firstParent].OTA_PhaseMargin + SimpleOTA_Designs[i].OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_first = SimpleOTA_Designs[temp_firstParent].OTA_Power_Consumption/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Power_Consumption + SimpleOTA_Designs[i].OTA_Power_Consumption)/2 );
										
					// normalization of the characteristics for the competitor parent (compare to first) 
					norm_OTA_VoltageGain_competitor = SimpleOTA_Designs[i].OTA_VoltageGain/ ( (SimpleOTA_Designs[temp_firstParent].OTA_VoltageGain + SimpleOTA_Designs[i].OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_competitor = SimpleOTA_Designs[i].OTA_FrequencyResponse/ ( (SimpleOTA_Designs[temp_firstParent].OTA_FrequencyResponse + SimpleOTA_Designs[i].OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_competitor = SimpleOTA_Designs[i].OTA_Thermal_Noise/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Thermal_Noise + SimpleOTA_Designs[i].OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_competitor = SimpleOTA_Designs[i].OTA_Flicker_Noise/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Flicker_Noise + SimpleOTA_Designs[i].OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor = SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch + SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_competitor = SimpleOTA_Designs[i].OTA_Slew_Rate/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Slew_Rate + SimpleOTA_Designs[i].OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_competitor = (SimpleOTA_Designs[i].OTA_VINCM_Plus-SimpleOTA_Designs[i].OTA_VINCM_Minus)/ ( ((SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Plus-SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Minus) + (SimpleOTA_Designs[i].OTA_VINCM_Plus-SimpleOTA_Designs[i].OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_competitor = (SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage)/ ( ((SimpleOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage) + (SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_competitor = SimpleOTA_Designs[i].OTA_PhaseMargin/ ( (SimpleOTA_Designs[temp_firstParent].OTA_PhaseMargin + SimpleOTA_Designs[i].OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_competitor = SimpleOTA_Designs[i].OTA_Power_Consumption/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Power_Consumption + SimpleOTA_Designs[i].OTA_Power_Consumption)/2 );
					
					//Calculate FOM for first parent and competitor parent ( Positive specs get plus(+) , Negative specs get minus(-) )
					//FOM_first = norm_OTA_VoltageGain_first*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_first*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_first*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_first*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_first*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_first*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_first*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_first*(FOM_percent_OTA_PhaseMargin);
					//FOM_competitor = norm_OTA_VoltageGain_competitor*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_competitor*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_competitor*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_competitor*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_competitor*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_competitor*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_competitor*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_competitor*(FOM_percent_OTA_PhaseMargin);
					FOM_first = ( pow(norm_OTA_VoltageGain_first,a0_OTA_VoltageGain) * pow(norm_OTA_FrequencyResponse_first,a1_OTA_FrequencyResponse) * pow(norm_OTA_Slew_Rate_first,a5_OTA_Slew_Rate) * pow(norm_OTA_Input_Voltage_Range_first,a6_OTA_Input_Voltage_Range) * pow(norm_OTA_Output_Voltage_Range_first,a7_OTA_Output_Voltage_Range) *pow(norm_OTA_PhaseMargin_first,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_first,a2_OTA_Thermal_Noise) * pow(norm_OTA_Flicker_Noise_first,a3_OTA_Flicker_Noise) * pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) * pow(norm_OTA_Power_Consumption_first,a9_OTA_Power_Consumption)); 
					FOM_competitor = ( pow(norm_OTA_VoltageGain_competitor,a0_OTA_VoltageGain) * pow(norm_OTA_FrequencyResponse_competitor,a1_OTA_FrequencyResponse) * pow(norm_OTA_Slew_Rate_competitor,a5_OTA_Slew_Rate) * pow(norm_OTA_Input_Voltage_Range_competitor,a6_OTA_Input_Voltage_Range) * pow(norm_OTA_Output_Voltage_Range_competitor,a7_OTA_Output_Voltage_Range) *pow(norm_OTA_PhaseMargin_competitor,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_competitor,a2_OTA_Thermal_Noise) * pow(norm_OTA_Flicker_Noise_competitor,a3_OTA_Flicker_Noise) * pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) * pow(norm_OTA_Power_Consumption_competitor,a9_OTA_Power_Consumption)); 

					
					if(FOM_first < FOM_competitor ){
						temp_firstParent = i;
					}
				}
				
			    //find second Parent
				//if(temp_firstParent == 0){
				//	temp_secondParent = 1 ;
				//}
				//else{
				//	temp_secondParent = 0;
				//}
			 	for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
			 		// normalization of the characteristics for the second parent (compare to competitor) 
					norm_OTA_VoltageGain_second = SimpleOTA_Designs[temp_secondParent].OTA_VoltageGain/ ( (SimpleOTA_Designs[temp_secondParent].OTA_VoltageGain + SimpleOTA_Designs[i].OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_second = SimpleOTA_Designs[temp_secondParent].OTA_FrequencyResponse/ ( (SimpleOTA_Designs[temp_secondParent].OTA_FrequencyResponse + SimpleOTA_Designs[i].OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_second = SimpleOTA_Designs[temp_secondParent].OTA_Thermal_Noise/ ( (SimpleOTA_Designs[temp_secondParent].OTA_Thermal_Noise + SimpleOTA_Designs[i].OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_second = SimpleOTA_Designs[temp_secondParent].OTA_Flicker_Noise/ ( (SimpleOTA_Designs[temp_secondParent].OTA_Flicker_Noise + SimpleOTA_Designs[i].OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_second = SimpleOTA_Designs[temp_secondParent].OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (SimpleOTA_Designs[temp_secondParent].OTA_Offset_Voltage_input_DueTo_Mismatch + SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_second = SimpleOTA_Designs[temp_secondParent].OTA_Slew_Rate/ ( (SimpleOTA_Designs[temp_secondParent].OTA_Slew_Rate + SimpleOTA_Designs[i].OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_second = (SimpleOTA_Designs[temp_secondParent].OTA_VINCM_Plus-SimpleOTA_Designs[temp_secondParent].OTA_VINCM_Minus)/ ( ((SimpleOTA_Designs[temp_secondParent].OTA_VINCM_Plus-SimpleOTA_Designs[temp_secondParent].OTA_VINCM_Minus) + (SimpleOTA_Designs[i].OTA_VINCM_Plus-SimpleOTA_Designs[i].OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_second = (SimpleOTA_Designs[temp_secondParent].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[temp_secondParent].OTA_Minimum_Output_Voltage)/ ( ((SimpleOTA_Designs[temp_secondParent].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[temp_secondParent].OTA_Minimum_Output_Voltage) + (SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_second = SimpleOTA_Designs[temp_secondParent].OTA_PhaseMargin/ ( (SimpleOTA_Designs[temp_secondParent].OTA_PhaseMargin + SimpleOTA_Designs[i].OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_second = SimpleOTA_Designs[temp_secondParent].OTA_Power_Consumption/ ( (SimpleOTA_Designs[temp_secondParent].OTA_Power_Consumption + SimpleOTA_Designs[i].OTA_Power_Consumption)/2 );
					
					// normalization of the characteristics for the competitor parent (compare to second) 
					norm_OTA_VoltageGain_competitor = SimpleOTA_Designs[i].OTA_VoltageGain/ ( (SimpleOTA_Designs[temp_secondParent].OTA_VoltageGain + SimpleOTA_Designs[i].OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_competitor = SimpleOTA_Designs[i].OTA_FrequencyResponse/ ( (SimpleOTA_Designs[temp_secondParent].OTA_FrequencyResponse + SimpleOTA_Designs[i].OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_competitor = SimpleOTA_Designs[i].OTA_Thermal_Noise/ ( (SimpleOTA_Designs[temp_secondParent].OTA_Thermal_Noise + SimpleOTA_Designs[i].OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_competitor = SimpleOTA_Designs[i].OTA_Flicker_Noise/ ( (SimpleOTA_Designs[temp_secondParent].OTA_Flicker_Noise + SimpleOTA_Designs[i].OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor = SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (SimpleOTA_Designs[temp_secondParent].OTA_Offset_Voltage_input_DueTo_Mismatch + SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_competitor = SimpleOTA_Designs[i].OTA_Slew_Rate/ ( (SimpleOTA_Designs[temp_secondParent].OTA_Slew_Rate + SimpleOTA_Designs[i].OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_competitor = (SimpleOTA_Designs[i].OTA_VINCM_Plus-SimpleOTA_Designs[i].OTA_VINCM_Minus)/ ( ((SimpleOTA_Designs[temp_secondParent].OTA_VINCM_Plus-SimpleOTA_Designs[temp_secondParent].OTA_VINCM_Minus) + (SimpleOTA_Designs[i].OTA_VINCM_Plus-SimpleOTA_Designs[i].OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_competitor = (SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage)/ ( ((SimpleOTA_Designs[temp_secondParent].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[temp_secondParent].OTA_Minimum_Output_Voltage) + (SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_competitor = SimpleOTA_Designs[i].OTA_PhaseMargin/ ( (SimpleOTA_Designs[temp_secondParent].OTA_PhaseMargin + SimpleOTA_Designs[i].OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_competitor = SimpleOTA_Designs[i].OTA_Power_Consumption/ ( (SimpleOTA_Designs[temp_secondParent].OTA_Power_Consumption + SimpleOTA_Designs[i].OTA_Power_Consumption)/2 );
					
					//Calculate FOM for first parent and competitor parent (sum all normilized values)
					//FOM_second = norm_OTA_VoltageGain_second*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_second*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_second*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_second*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_second*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_second*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_second*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_second*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_second*(FOM_percent_OTA_PhaseMargin);
					//FOM_competitor = norm_OTA_VoltageGain_competitor*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_competitor*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_competitor*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_competitor*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_competitor*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_competitor*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_competitor*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_competitor*(FOM_percent_OTA_PhaseMargin);
					FOM_second = ( pow(norm_OTA_VoltageGain_second,a0_OTA_VoltageGain) * pow(norm_OTA_FrequencyResponse_second,a1_OTA_FrequencyResponse) * pow(norm_OTA_Slew_Rate_second,a5_OTA_Slew_Rate) * pow(norm_OTA_Input_Voltage_Range_second,a6_OTA_Input_Voltage_Range) * pow(norm_OTA_Output_Voltage_Range_second,a7_OTA_Output_Voltage_Range) *pow(norm_OTA_PhaseMargin_second,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_second,a2_OTA_Thermal_Noise) * pow(norm_OTA_Flicker_Noise_second,a3_OTA_Flicker_Noise) * pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_second,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) * pow(norm_OTA_Power_Consumption_second,a9_OTA_Power_Consumption)); 
					FOM_competitor = ( pow(norm_OTA_VoltageGain_competitor,a0_OTA_VoltageGain) * pow(norm_OTA_FrequencyResponse_competitor,a1_OTA_FrequencyResponse) * pow(norm_OTA_Slew_Rate_competitor,a5_OTA_Slew_Rate) * pow(norm_OTA_Input_Voltage_Range_competitor,a6_OTA_Input_Voltage_Range) * pow(norm_OTA_Output_Voltage_Range_competitor,a7_OTA_Output_Voltage_Range) *pow(norm_OTA_PhaseMargin_competitor,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_competitor,a2_OTA_Thermal_Noise) * pow(norm_OTA_Flicker_Noise_competitor,a3_OTA_Flicker_Noise) * pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) * pow(norm_OTA_Power_Consumption_competitor,a9_OTA_Power_Consumption));	
			 		
					if((FOM_second < FOM_competitor) && i!=temp_firstParent){
						temp_secondParent = i;
					}
				}
				
				//initialize the best design (when step == 0),pick new best_parent if firstparent is better.
				if(Step == 0 ){
					Best_Design = SimpleOTA_Designs[temp_firstParent];
					Pre_Last_Parent_Design = SimpleOTA_Designs[temp_firstParent];
				}
				else{
					// normalization of the characteristics for the best parent (compare to first)
					norm_OTA_VoltageGain_best = Best_Design.OTA_VoltageGain/ ( (SimpleOTA_Designs[temp_firstParent].OTA_VoltageGain + Best_Design.OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_best = Best_Design.OTA_FrequencyResponse/ ( (SimpleOTA_Designs[temp_firstParent].OTA_FrequencyResponse + Best_Design.OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_best = Best_Design.OTA_Thermal_Noise/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Thermal_Noise + Best_Design.OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_best = Best_Design.OTA_Flicker_Noise/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Flicker_Noise + Best_Design.OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_best = Best_Design.OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch +Best_Design.OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_best = Best_Design.OTA_Slew_Rate/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Slew_Rate + Best_Design.OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_best = (Best_Design.OTA_VINCM_Plus-Best_Design.OTA_VINCM_Minus)/ ( ((SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Plus-SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Minus) + (Best_Design.OTA_VINCM_Plus-Best_Design.OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_best = (Best_Design.OTA_Maximun_Output_Voltage-Best_Design.OTA_Minimum_Output_Voltage)/ ( ((SimpleOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage) + (Best_Design.OTA_Maximun_Output_Voltage-Best_Design.OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_best = Best_Design.OTA_PhaseMargin/ ( (SimpleOTA_Designs[temp_firstParent].OTA_PhaseMargin + Best_Design.OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_best = Best_Design.OTA_Power_Consumption/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Power_Consumption + Best_Design.OTA_Power_Consumption)/2 );
					
					// normalization of the characteristics for the first parent (compare to best)
					norm_OTA_VoltageGain_first = SimpleOTA_Designs[temp_firstParent].OTA_VoltageGain/ ( (SimpleOTA_Designs[temp_firstParent].OTA_VoltageGain + Best_Design.OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_first = SimpleOTA_Designs[temp_firstParent].OTA_FrequencyResponse/ ( (SimpleOTA_Designs[temp_firstParent].OTA_FrequencyResponse + Best_Design.OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_first = SimpleOTA_Designs[temp_firstParent].OTA_Thermal_Noise/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Thermal_Noise + Best_Design.OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_first = SimpleOTA_Designs[temp_firstParent].OTA_Flicker_Noise/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Flicker_Noise + Best_Design.OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first = SimpleOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch + Best_Design.OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_first = SimpleOTA_Designs[temp_firstParent].OTA_Slew_Rate/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Slew_Rate + Best_Design.OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_first = (SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Plus-SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Minus)/ ( ((SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Plus-SimpleOTA_Designs[temp_firstParent].OTA_VINCM_Minus) + (Best_Design.OTA_VINCM_Plus-Best_Design.OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_first = (SimpleOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage)/ ( ((SimpleOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-SimpleOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage) + (Best_Design.OTA_Maximun_Output_Voltage-Best_Design.OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_first = SimpleOTA_Designs[temp_firstParent].OTA_PhaseMargin/ ( (SimpleOTA_Designs[temp_firstParent].OTA_PhaseMargin + Best_Design.OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_first = SimpleOTA_Designs[temp_firstParent].OTA_Power_Consumption/ ( (SimpleOTA_Designs[temp_firstParent].OTA_Power_Consumption + Best_Design.OTA_Power_Consumption)/2 );
					
					//Calculate FOM for first parent and Best parent ( Positive specs get plus(+) , Negative specs get minus(-) )
					//FOM_first = norm_OTA_VoltageGain_first*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_first*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_first*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_first*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_first*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_first*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_first*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_first*(FOM_percent_OTA_PhaseMargin);
					//FOM_best = norm_OTA_VoltageGain_best*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_best*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_best*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_best*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_best*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_best*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_best*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_best*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_best*(FOM_percent_OTA_PhaseMargin);
					FOM_first = ( pow(norm_OTA_VoltageGain_first,a0_OTA_VoltageGain) * pow(norm_OTA_FrequencyResponse_first,a1_OTA_FrequencyResponse) * pow(norm_OTA_Slew_Rate_first,a5_OTA_Slew_Rate) * pow(norm_OTA_Input_Voltage_Range_first,a6_OTA_Input_Voltage_Range) * pow(norm_OTA_Output_Voltage_Range_first,a7_OTA_Output_Voltage_Range) *pow(norm_OTA_PhaseMargin_first,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_first,a2_OTA_Thermal_Noise) * pow(norm_OTA_Flicker_Noise_first,a3_OTA_Flicker_Noise) * pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) * pow(norm_OTA_Power_Consumption_first,a9_OTA_Power_Consumption));
					FOM_best = ( pow(norm_OTA_VoltageGain_best,a0_OTA_VoltageGain) * pow(norm_OTA_FrequencyResponse_best,a1_OTA_FrequencyResponse) * pow(norm_OTA_Slew_Rate_best,a5_OTA_Slew_Rate) * pow(norm_OTA_Input_Voltage_Range_best,a6_OTA_Input_Voltage_Range) * pow(norm_OTA_Output_Voltage_Range_best,a7_OTA_Output_Voltage_Range) *pow(norm_OTA_PhaseMargin_best,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_best,a2_OTA_Thermal_Noise) * pow(norm_OTA_Flicker_Noise_best,a3_OTA_Flicker_Noise) * pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_best,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) * pow(norm_OTA_Power_Consumption_best,a9_OTA_Power_Consumption)); 
					
					if(FOM_best < FOM_first ){
						Best_Design = SimpleOTA_Designs[temp_firstParent];
					}
					Pre_Last_Parent_Design = SimpleOTA_Designs[temp_firstParent];
					 
				}
				
				
			
			
			
			
		//printf(" \n %d %d",temp_firstParent,temp_secondParent);
		
		//Create Next Generation from parents with IDs temp_firstParent and temp_secondParent   
		//{Create_new_Generation(int IndextFirstParent,int IndexSecondParent,	struct SimpleOTA SimpleOTA_Designs[],int NumberOfChilds,int lowerIbias,int upperIbias,int lowerLength, int upperLength,int lowerIC,int upperIC)}
		int NumberOfChilds = sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA) ; 
		if(Mode == 0){
			Create_new_Generation(temp_firstParent,temp_secondParent,SimpleOTA_Designs,NumberOfChilds,Ibias_Table[index_Ibias],Ibias_Table[index_Ibias],Lowest_Length,Highest_Length,Lowest_IC,Highest_IC);
		}
		else if (Mode == 2){
			Create_new_Generation_with_different_ICs(temp_firstParent,temp_secondParent,SimpleOTA_Designs,NumberOfChilds,Ibias_Table[index_Ibias],Ibias_Table[index_Ibias],Lowest_Length,Highest_Length,data_sheet.IC_Ranges_CurrentMirrorOTA);
		}
		

		
		//for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
		//	Calculate_Mosfets_Parameters(SimpleOTA_Designs[i].Mosfets,SimpleOTA_Designs[i].Ibias);  !! MALLON DEN XRIAZETE !!
		//}
		
	/*	//Test print for new Generation for SimpleOTA
		printf("\nGeneration Number : %d\n",Step+1);
		for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
			printf("\nIbias Design%d :%g\n",i,SimpleOTA_Designs[i].Ibias);
			for (j=0;j<10;j++){
				printf("L%d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].L);
				printf("IC%d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].IC);
				
				printf("W%d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].W);
				printf("u0 %d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].u0);
				printf("n0 %d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].n0);
				printf("Io %d:%g ",j,(double) SimpleOTA_Designs[i].Mosfets[j].Io);
				printf("\n"); 
			}
			
			
		}*/
		
	//	//Test print before Calculations (New Generation)	
	//	for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
	//		printf("\nVoltageGain Design%d :%g\n",i,SimpleOTA_Designs[i].OTA_VoltageGain);
	//		printf("\nFrequencyResponse Design%d :%g\n",i,SimpleOTA_Designs[i].OTA_FrequencyResponse);
	//	}
	
		// Calculate Specs For each OTA for the new Generation !!!
		for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
			//Calculate Transconductance (GM) for each Design {Transconductance_Calc(int Ibias,double IC1)}
			SimpleOTA_Designs[i].OTA_Transconductance = Transconductance_Calc(SimpleOTA_Designs[i].Ibias,SimpleOTA_Designs[i].Mosfets[0].IC);
			
			//Calculate OutputResistance (Rout) for each Design {OutputResistance_Calc(double L4,double L6,double Ibias)}
			SimpleOTA_Designs[i].OTA_OutputResistance = OutputResistance_Calc(SimpleOTA_Designs[i].Mosfets[3].L,SimpleOTA_Designs[i].Mosfets[5].L,SimpleOTA_Designs[i].Ibias);
			
			//Calculate VoltageGain (Av) for each Design {VoltageGain_Calc(double GM,double Rout)}
			SimpleOTA_Designs[i].OTA_VoltageGain = VoltageGain_Calc(SimpleOTA_Designs[i].OTA_Transconductance,SimpleOTA_Designs[i].OTA_OutputResistance);
			
			//Calculate FrequencyResponse (f-3dB) for each Design  {double FrequencyResponse_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_FrequencyResponse = FrequencyResponse_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate PhaseMargin (PM) for each Design {PhaseMargin_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_PhaseMargin = PhaseMargin_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate ThermalNoise (Svin(thermal)) for each Design {double Thermal_Noise_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Thermal_Noise = Thermal_Noise_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate FlickerNoise (Svin(flicker)) for each Design {double Flicker_Noise_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Flicker_Noise = Flicker_Noise_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Offset_Voltage due to Local-Area Mismatch (Vsquare_InOffset) {Offset_Voltage_input_DueTo_Mismatch_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch = Offset_Voltage_input_DueTo_Mismatch_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Input_Capacitance (Cindif) for each Design {Input_Capacitance_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Input_Capacitance = Input_Capacitance_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Output_Capacitance (COUT) for each Design {Output_Capacitance_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Output_Capacitance = Output_Capacitance_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Slew_Rate (SR) for each Design {Slew_Rate_Calc(double COUT,double Ibias)}
			SimpleOTA_Designs[i].OTA_Slew_Rate = Slew_Rate_Calc(SimpleOTA_Designs[i].OTA_Output_Capacitance,SimpleOTA_Designs[i].Ibias);
			
			// Calculate VINCM_Plus (VINCM+) for each Design  {VINCM_Plus_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_VINCM_Plus = VINCM_Plus_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate VINCM_Minus (VINCM-) for each Design {VINCM_Minus_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_VINCM_Minus = VINCM_Minus_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Maximun_Output_Voltage (Vout+) for each Design {Maximun_Output_Voltage_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage = Maximun_Output_Voltage_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Minimum_Output_Voltage (Vout-) for each Design {Minimum_Output_Voltage_Calc(struct device Mosfets[])}
			SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage = Minimum_Output_Voltage_Calc(SimpleOTA_Designs[i].Mosfets);
			
			//Calculate Power_Consumption (PC) for each Design {Power_Consumption_Calc(double Ibias)}
			SimpleOTA_Designs[i].OTA_Power_Consumption = Power_Consumption_Calc(SimpleOTA_Designs[i].Ibias);
		}
		
	/*	//Test print after Calculations (New Generation)	SimpleOTA
		printf("\n\n\n");
		for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
			printf("\nVoltageGain Design%d :%g\n",i,SimpleOTA_Designs[i].OTA_VoltageGain);
			printf("\nFrequencyResponse Design%d :%g\n",i,SimpleOTA_Designs[i].OTA_FrequencyResponse);
			printf("\nPhaseMargin Design%d :%g\n",i,SimpleOTA_Designs[i].OTA_PhaseMargin);
			printf("\nFrequencyResponse*nVoltageGain Design%d :%g\n",i,(SimpleOTA_Designs[i].OTA_FrequencyResponse)*(SimpleOTA_Designs[i].OTA_VoltageGain));
			printf("\n\tThermal_Noise Design%d :%g",i,SimpleOTA_Designs[i].OTA_Thermal_Noise);
			printf("\n\tFlicker_Noise Design%d :%g",i,SimpleOTA_Designs[i].OTA_Flicker_Noise);
			printf("\n\tOffset_Voltage due to Local-Area Mismatch Design%d :%g",i,SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch);
			printf("\n\tInput_Capacitance Design%d :%g",i,SimpleOTA_Designs[i].OTA_Input_Capacitance);
			printf("\n\tOutput_Capacitance Design%d :%g",i,SimpleOTA_Designs[i].OTA_Output_Capacitance);
			printf("\n\tSlew_Rate Design%d :%g",i,SimpleOTA_Designs[i].OTA_Slew_Rate);
			printf("\n\tVINCM_Plus Design%d :%g",i,SimpleOTA_Designs[i].OTA_VINCM_Plus);
			printf("\n\tVINCM_Minus Design%d :%g",i,SimpleOTA_Designs[i].OTA_VINCM_Minus);
			printf("\n\tMaximun_Output_Voltage Design%d :%g",i,SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage);
			printf("\n\tMinimun_Output_Voltage Design%d :%g",i,SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage);
			printf("\n\tPower_Consumption Design%d :%g",i,SimpleOTA_Designs[i].OTA_Power_Consumption);
		}*/
	}
	
	else if(Mode == 1 || Mode == 3){ 
		//Pick Parents for Cascode_OTA
			//Initialize Temps for Parents
				temp_firstParent = 0 ;	
				temp_secondParent = 1 ;
				
				//find first Parent
				//temp_firstParent = 0 ;	
				for (i=0;i<sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA);i++){
					// normalization of the characteristics for the first parent (compare to competitor) 
					norm_OTA_VoltageGain_first = CascodedOTA_Designs[temp_firstParent].OTA_VoltageGain/ ( (CascodedOTA_Designs[temp_firstParent].OTA_VoltageGain + CascodedOTA_Designs[i].OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_first = CascodedOTA_Designs[temp_firstParent].OTA_FrequencyResponse/ ( (CascodedOTA_Designs[temp_firstParent].OTA_FrequencyResponse + CascodedOTA_Designs[i].OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_first = CascodedOTA_Designs[temp_firstParent].OTA_Thermal_Noise/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Thermal_Noise + CascodedOTA_Designs[i].OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_first = CascodedOTA_Designs[temp_firstParent].OTA_Flicker_Noise/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Flicker_Noise + CascodedOTA_Designs[i].OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first = CascodedOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch + CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_first = CascodedOTA_Designs[temp_firstParent].OTA_Slew_Rate/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Slew_Rate + CascodedOTA_Designs[i].OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_first = (CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Plus-CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Minus)/ ( ((CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Plus-CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Minus) + (CascodedOTA_Designs[i].OTA_VINCM_Plus-CascodedOTA_Designs[i].OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_first = (CascodedOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage)/ ( ((CascodedOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage) + (CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_first = CascodedOTA_Designs[temp_firstParent].OTA_PhaseMargin/ ( (CascodedOTA_Designs[temp_firstParent].OTA_PhaseMargin + CascodedOTA_Designs[i].OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_first = CascodedOTA_Designs[temp_firstParent].OTA_Power_Consumption/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Power_Consumption + CascodedOTA_Designs[i].OTA_Power_Consumption)/2 );
										
					// normalization of the characteristics for the competitor parent (compare to first) 
					norm_OTA_VoltageGain_competitor = CascodedOTA_Designs[i].OTA_VoltageGain/ ( (CascodedOTA_Designs[temp_firstParent].OTA_VoltageGain + CascodedOTA_Designs[i].OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_competitor = CascodedOTA_Designs[i].OTA_FrequencyResponse/ ( (CascodedOTA_Designs[temp_firstParent].OTA_FrequencyResponse + CascodedOTA_Designs[i].OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_competitor = CascodedOTA_Designs[i].OTA_Thermal_Noise/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Thermal_Noise + CascodedOTA_Designs[i].OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_competitor = CascodedOTA_Designs[i].OTA_Flicker_Noise/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Flicker_Noise + CascodedOTA_Designs[i].OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor = CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch + CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_competitor = CascodedOTA_Designs[i].OTA_Slew_Rate/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Slew_Rate + CascodedOTA_Designs[i].OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_competitor = (CascodedOTA_Designs[i].OTA_VINCM_Plus-CascodedOTA_Designs[i].OTA_VINCM_Minus)/ ( ((CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Plus-CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Minus) + (CascodedOTA_Designs[i].OTA_VINCM_Plus-CascodedOTA_Designs[i].OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_competitor = (CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage)/ ( ((CascodedOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage) + (CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_competitor = CascodedOTA_Designs[i].OTA_PhaseMargin/ ( (CascodedOTA_Designs[temp_firstParent].OTA_PhaseMargin + CascodedOTA_Designs[i].OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_competitor = CascodedOTA_Designs[i].OTA_Power_Consumption/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Power_Consumption + CascodedOTA_Designs[i].OTA_Power_Consumption)/2 );
					
					//Calculate FOM for first parent and competitor parent ( Positive specs get plus(+) , Negative specs get minus(-) )
					//FOM_first = norm_OTA_VoltageGain_first*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_first*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_first*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_first*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_first*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_first*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_first*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_first*(FOM_percent_OTA_PhaseMargin);
					//FOM_competitor = norm_OTA_VoltageGain_competitor*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_competitor*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_competitor*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_competitor*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_competitor*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_competitor*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_competitor*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_competitor*(FOM_percent_OTA_PhaseMargin);
					FOM_first = ( pow(norm_OTA_VoltageGain_first,a0_OTA_VoltageGain) + pow(norm_OTA_FrequencyResponse_first,a1_OTA_FrequencyResponse) + pow(norm_OTA_Slew_Rate_first,a5_OTA_Slew_Rate) + pow(norm_OTA_Input_Voltage_Range_first,a6_OTA_Input_Voltage_Range) + pow(norm_OTA_Output_Voltage_Range_first,a7_OTA_Output_Voltage_Range) + pow(norm_OTA_PhaseMargin_first,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_first,a2_OTA_Thermal_Noise) + pow(norm_OTA_Flicker_Noise_first,a3_OTA_Flicker_Noise) + pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) + pow(norm_OTA_Power_Consumption_first,a9_OTA_Power_Consumption)); 
					FOM_competitor = ( pow(norm_OTA_VoltageGain_competitor,a0_OTA_VoltageGain) + pow(norm_OTA_FrequencyResponse_competitor,a1_OTA_FrequencyResponse) + pow(norm_OTA_Slew_Rate_competitor,a5_OTA_Slew_Rate) + pow(norm_OTA_Input_Voltage_Range_competitor,a6_OTA_Input_Voltage_Range) + pow(norm_OTA_Output_Voltage_Range_competitor,a7_OTA_Output_Voltage_Range) + pow(norm_OTA_PhaseMargin_competitor,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_competitor,a2_OTA_Thermal_Noise) + pow(norm_OTA_Flicker_Noise_competitor,a3_OTA_Flicker_Noise) + pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) + pow(norm_OTA_Power_Consumption_competitor,a9_OTA_Power_Consumption)); 

					
					if(FOM_first < FOM_competitor ){
						temp_firstParent = i;
					}
				}
				
			    //find second Parent
				//if(temp_firstParent == 0){
				//	temp_secondParent = 1 ;
				//}
				//else{
				//	temp_secondParent = 0;
				//}
			 	for (i=0;i<sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA);i++){
			 		// normalization of the characteristics for the second parent (compare to competitor) 
					norm_OTA_VoltageGain_second = CascodedOTA_Designs[temp_secondParent].OTA_VoltageGain/ ( (CascodedOTA_Designs[temp_secondParent].OTA_VoltageGain + CascodedOTA_Designs[i].OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_second = CascodedOTA_Designs[temp_secondParent].OTA_FrequencyResponse/ ( (CascodedOTA_Designs[temp_secondParent].OTA_FrequencyResponse + CascodedOTA_Designs[i].OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_second = CascodedOTA_Designs[temp_secondParent].OTA_Thermal_Noise/ ( (CascodedOTA_Designs[temp_secondParent].OTA_Thermal_Noise + CascodedOTA_Designs[i].OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_second = CascodedOTA_Designs[temp_secondParent].OTA_Flicker_Noise/ ( (CascodedOTA_Designs[temp_secondParent].OTA_Flicker_Noise + CascodedOTA_Designs[i].OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_second = CascodedOTA_Designs[temp_secondParent].OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (CascodedOTA_Designs[temp_secondParent].OTA_Offset_Voltage_input_DueTo_Mismatch + CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_second = CascodedOTA_Designs[temp_secondParent].OTA_Slew_Rate/ ( (CascodedOTA_Designs[temp_secondParent].OTA_Slew_Rate + CascodedOTA_Designs[i].OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_second = (CascodedOTA_Designs[temp_secondParent].OTA_VINCM_Plus-CascodedOTA_Designs[temp_secondParent].OTA_VINCM_Minus)/ ( ((CascodedOTA_Designs[temp_secondParent].OTA_VINCM_Plus-CascodedOTA_Designs[temp_secondParent].OTA_VINCM_Minus) + (CascodedOTA_Designs[i].OTA_VINCM_Plus-CascodedOTA_Designs[i].OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_second = (CascodedOTA_Designs[temp_secondParent].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[temp_secondParent].OTA_Minimum_Output_Voltage)/ ( ((CascodedOTA_Designs[temp_secondParent].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[temp_secondParent].OTA_Minimum_Output_Voltage) + (CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_second = CascodedOTA_Designs[temp_secondParent].OTA_PhaseMargin/ ( (CascodedOTA_Designs[temp_secondParent].OTA_PhaseMargin + CascodedOTA_Designs[i].OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_second = CascodedOTA_Designs[temp_secondParent].OTA_Power_Consumption/ ( (CascodedOTA_Designs[temp_secondParent].OTA_Power_Consumption + CascodedOTA_Designs[i].OTA_Power_Consumption)/2 );
					
					// normalization of the characteristics for the competitor parent (compare to second) 
					norm_OTA_VoltageGain_competitor = CascodedOTA_Designs[i].OTA_VoltageGain/ ( (CascodedOTA_Designs[temp_secondParent].OTA_VoltageGain + CascodedOTA_Designs[i].OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_competitor = CascodedOTA_Designs[i].OTA_FrequencyResponse/ ( (CascodedOTA_Designs[temp_secondParent].OTA_FrequencyResponse + CascodedOTA_Designs[i].OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_competitor = CascodedOTA_Designs[i].OTA_Thermal_Noise/ ( (CascodedOTA_Designs[temp_secondParent].OTA_Thermal_Noise + CascodedOTA_Designs[i].OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_competitor = CascodedOTA_Designs[i].OTA_Flicker_Noise/ ( (CascodedOTA_Designs[temp_secondParent].OTA_Flicker_Noise + CascodedOTA_Designs[i].OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor = CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (CascodedOTA_Designs[temp_secondParent].OTA_Offset_Voltage_input_DueTo_Mismatch + CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_competitor = CascodedOTA_Designs[i].OTA_Slew_Rate/ ( (CascodedOTA_Designs[temp_secondParent].OTA_Slew_Rate + CascodedOTA_Designs[i].OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_competitor = (CascodedOTA_Designs[i].OTA_VINCM_Plus-CascodedOTA_Designs[i].OTA_VINCM_Minus)/ ( ((CascodedOTA_Designs[temp_secondParent].OTA_VINCM_Plus-CascodedOTA_Designs[temp_secondParent].OTA_VINCM_Minus) + (CascodedOTA_Designs[i].OTA_VINCM_Plus-CascodedOTA_Designs[i].OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_competitor = (CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage)/ ( ((CascodedOTA_Designs[temp_secondParent].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[temp_secondParent].OTA_Minimum_Output_Voltage) + (CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_competitor = CascodedOTA_Designs[i].OTA_PhaseMargin/ ( (CascodedOTA_Designs[temp_secondParent].OTA_PhaseMargin + CascodedOTA_Designs[i].OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_competitor = CascodedOTA_Designs[i].OTA_Power_Consumption/ ( (CascodedOTA_Designs[temp_secondParent].OTA_Power_Consumption + CascodedOTA_Designs[i].OTA_Power_Consumption)/2 );
					
					//Calculate FOM for first parent and competitor parent (sum all normilized values)
					//FOM_second = norm_OTA_VoltageGain_second*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_second*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_second*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_second*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_second*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_second*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_second*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_second*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_second*(FOM_percent_OTA_PhaseMargin);
					//FOM_competitor = norm_OTA_VoltageGain_competitor*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_competitor*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_competitor*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_competitor*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_competitor*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_competitor*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_competitor*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_competitor*(FOM_percent_OTA_PhaseMargin);
					FOM_second = ( pow(norm_OTA_VoltageGain_second,a0_OTA_VoltageGain) + pow(norm_OTA_FrequencyResponse_second,a1_OTA_FrequencyResponse) + pow(norm_OTA_Slew_Rate_second,a5_OTA_Slew_Rate) + pow(norm_OTA_Input_Voltage_Range_second,a6_OTA_Input_Voltage_Range) + pow(norm_OTA_Output_Voltage_Range_second,a7_OTA_Output_Voltage_Range) + pow(norm_OTA_PhaseMargin_second,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_second,a2_OTA_Thermal_Noise) + pow(norm_OTA_Flicker_Noise_second,a3_OTA_Flicker_Noise) + pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_second,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) + pow(norm_OTA_Power_Consumption_second,a9_OTA_Power_Consumption)); 
					FOM_competitor = ( pow(norm_OTA_VoltageGain_competitor,a0_OTA_VoltageGain) + pow(norm_OTA_FrequencyResponse_competitor,a1_OTA_FrequencyResponse) + pow(norm_OTA_Slew_Rate_competitor,a5_OTA_Slew_Rate) + pow(norm_OTA_Input_Voltage_Range_competitor,a6_OTA_Input_Voltage_Range) + pow(norm_OTA_Output_Voltage_Range_competitor,a7_OTA_Output_Voltage_Range) + pow(norm_OTA_PhaseMargin_competitor,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_competitor,a2_OTA_Thermal_Noise) + pow(norm_OTA_Flicker_Noise_competitor,a3_OTA_Flicker_Noise) + pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_competitor,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) + pow(norm_OTA_Power_Consumption_competitor,a9_OTA_Power_Consumption));	
			 		
					if((FOM_second < FOM_competitor) && i!=temp_firstParent){
						temp_secondParent = i;
					}
				}
				
				//initialize the best design (when step == 0),pick new best_parent if firstparent is better.
				if(Step == 0 ){
					Best_Design_CascodedOTA = CascodedOTA_Designs[temp_firstParent];
					Pre_Last_Parent_Design_CascodedOTA = CascodedOTA_Designs[temp_firstParent];
				}
				else{
					// normalization of the characteristics for the best parent (compare to first)
					norm_OTA_VoltageGain_best = Best_Design_CascodedOTA.OTA_VoltageGain/ ( (CascodedOTA_Designs[temp_firstParent].OTA_VoltageGain + Best_Design_CascodedOTA.OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_best = Best_Design_CascodedOTA.OTA_FrequencyResponse/ ( (CascodedOTA_Designs[temp_firstParent].OTA_FrequencyResponse + Best_Design_CascodedOTA.OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_best = Best_Design_CascodedOTA.OTA_Thermal_Noise/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Thermal_Noise + Best_Design_CascodedOTA.OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_best = Best_Design_CascodedOTA.OTA_Flicker_Noise/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Flicker_Noise + Best_Design_CascodedOTA.OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_best = Best_Design_CascodedOTA.OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch +Best_Design_CascodedOTA.OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_best = Best_Design_CascodedOTA.OTA_Slew_Rate/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Slew_Rate + Best_Design_CascodedOTA.OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_best = (Best_Design_CascodedOTA.OTA_VINCM_Plus-Best_Design_CascodedOTA.OTA_VINCM_Minus)/ ( ((CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Plus-CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Minus) + (Best_Design_CascodedOTA.OTA_VINCM_Plus-Best_Design_CascodedOTA.OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_best = (Best_Design_CascodedOTA.OTA_Maximun_Output_Voltage-Best_Design_CascodedOTA.OTA_Minimum_Output_Voltage)/ ( ((CascodedOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage) + (Best_Design_CascodedOTA.OTA_Maximun_Output_Voltage-Best_Design_CascodedOTA.OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_best = Best_Design_CascodedOTA.OTA_PhaseMargin/ ( (CascodedOTA_Designs[temp_firstParent].OTA_PhaseMargin + Best_Design_CascodedOTA.OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_best = Best_Design_CascodedOTA.OTA_Power_Consumption/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Power_Consumption + Best_Design_CascodedOTA.OTA_Power_Consumption)/2 );
					
					// normalization of the characteristics for the first parent (compare to best)
					norm_OTA_VoltageGain_first = CascodedOTA_Designs[temp_firstParent].OTA_VoltageGain/ ( (CascodedOTA_Designs[temp_firstParent].OTA_VoltageGain + Best_Design_CascodedOTA.OTA_VoltageGain)/2 );
					norm_OTA_FrequencyResponse_first = CascodedOTA_Designs[temp_firstParent].OTA_FrequencyResponse/ ( (CascodedOTA_Designs[temp_firstParent].OTA_FrequencyResponse + Best_Design_CascodedOTA.OTA_FrequencyResponse)/2 );
					norm_OTA_Thermal_Noise_first = CascodedOTA_Designs[temp_firstParent].OTA_Thermal_Noise/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Thermal_Noise + Best_Design_CascodedOTA.OTA_Thermal_Noise)/2 );
					norm_OTA_Flicker_Noise_first = CascodedOTA_Designs[temp_firstParent].OTA_Flicker_Noise/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Flicker_Noise + Best_Design_CascodedOTA.OTA_Flicker_Noise)/2 );
					norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first = CascodedOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Offset_Voltage_input_DueTo_Mismatch + Best_Design_CascodedOTA.OTA_Offset_Voltage_input_DueTo_Mismatch)/2 );
					norm_OTA_Slew_Rate_first = CascodedOTA_Designs[temp_firstParent].OTA_Slew_Rate/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Slew_Rate + Best_Design_CascodedOTA.OTA_Slew_Rate)/2 );
					norm_OTA_Input_Voltage_Range_first = (CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Plus-CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Minus)/ ( ((CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Plus-CascodedOTA_Designs[temp_firstParent].OTA_VINCM_Minus) + (Best_Design_CascodedOTA.OTA_VINCM_Plus-Best_Design_CascodedOTA.OTA_VINCM_Minus))/2 );
					norm_OTA_Output_Voltage_Range_first = (CascodedOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage)/ ( ((CascodedOTA_Designs[temp_firstParent].OTA_Maximun_Output_Voltage-CascodedOTA_Designs[temp_firstParent].OTA_Minimum_Output_Voltage) + (Best_Design_CascodedOTA.OTA_Maximun_Output_Voltage-Best_Design_CascodedOTA.OTA_Minimum_Output_Voltage))/2 );
					norm_OTA_PhaseMargin_first = CascodedOTA_Designs[temp_firstParent].OTA_PhaseMargin/ ( (CascodedOTA_Designs[temp_firstParent].OTA_PhaseMargin + Best_Design_CascodedOTA.OTA_PhaseMargin)/2 );
					norm_OTA_Power_Consumption_first = CascodedOTA_Designs[temp_firstParent].OTA_Power_Consumption/ ( (CascodedOTA_Designs[temp_firstParent].OTA_Power_Consumption + Best_Design_CascodedOTA.OTA_Power_Consumption)/2 );
					
					//Calculate FOM for first parent and Best parent ( Positive specs get plus(+) , Negative specs get minus(-) )
					//FOM_first = norm_OTA_VoltageGain_first*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_first*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_first*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_first*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_first*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_first*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_first*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_first*(FOM_percent_OTA_PhaseMargin);
					//FOM_best = norm_OTA_VoltageGain_best*(FOM_percent_OTA_VoltageGain) + norm_OTA_FrequencyResponse_best*(FOM_percent_OTA_FrequencyResponse) - norm_OTA_Thermal_Noise_best*(FOM_percent_OTA_Thermal_Noise) - norm_OTA_Flicker_Noise_best*(FOM_percent_OTA_Flicker_Noise) - norm_OTA_Offset_Voltage_input_DueTo_Mismatch_best*(FOM_percent_OTA_Offset_Voltage_input_DueTo_Mismatch) + norm_OTA_Slew_Rate_best*(FOM_percent_OTA_Slew_Rate) + norm_OTA_Input_Voltage_Range_best*(FOM_percent_OTA_Input_Voltage_Range) + norm_OTA_Output_Voltage_Range_best*(FOM_percent_OTA_Output_Voltage_Range) + norm_OTA_PhaseMargin_best*(FOM_percent_OTA_PhaseMargin);
					FOM_first = ( pow(norm_OTA_VoltageGain_first,a0_OTA_VoltageGain) + pow(norm_OTA_FrequencyResponse_first,a1_OTA_FrequencyResponse) + pow(norm_OTA_Slew_Rate_first,a5_OTA_Slew_Rate) + pow(norm_OTA_Input_Voltage_Range_first,a6_OTA_Input_Voltage_Range) + pow(norm_OTA_Output_Voltage_Range_first,a7_OTA_Output_Voltage_Range) + pow(norm_OTA_PhaseMargin_first,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_first,a2_OTA_Thermal_Noise) + pow(norm_OTA_Flicker_Noise_first,a3_OTA_Flicker_Noise) + pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_first,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) + pow(norm_OTA_Power_Consumption_first,a9_OTA_Power_Consumption));
					FOM_best = ( pow(norm_OTA_VoltageGain_best,a0_OTA_VoltageGain) + pow(norm_OTA_FrequencyResponse_best,a1_OTA_FrequencyResponse) + pow(norm_OTA_Slew_Rate_best,a5_OTA_Slew_Rate) + pow(norm_OTA_Input_Voltage_Range_best,a6_OTA_Input_Voltage_Range) + pow(norm_OTA_Output_Voltage_Range_best,a7_OTA_Output_Voltage_Range) + pow(norm_OTA_PhaseMargin_best,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise_best,a2_OTA_Thermal_Noise) + pow(norm_OTA_Flicker_Noise_best,a3_OTA_Flicker_Noise) + pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch_best,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) + pow(norm_OTA_Power_Consumption_best,a9_OTA_Power_Consumption)); 
					
					if(FOM_best < FOM_first ){
						Best_Design_CascodedOTA = CascodedOTA_Designs[temp_firstParent];
					}
					Pre_Last_Parent_Design_CascodedOTA = CascodedOTA_Designs[temp_firstParent];
					 
				}
				
				
		//printf(" \n %d %d",temp_firstParent,temp_secondParent);
		
		//Create Next Generation from parents with IDs temp_firstParent and temp_secondParent   
		//{Create_new_Generation(int IndextFirstParent,int IndexSecondParent,	struct SimpleOTA SimpleOTA_Designs[],int NumberOfChilds,int lowerIbias,int upperIbias,int lowerLength, int upperLength,int lowerIC,int upperIC)}
		int NumberOfChilds = sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA) ; 
		
		if(Mode == 1){
			Create_new_Generation_CascodedOTA(temp_firstParent,temp_secondParent,CascodedOTA_Designs,NumberOfChilds,Ibias_Table[index_Ibias],Ibias_Table[index_Ibias],Lowest_Length,Highest_Length,Lowest_IC,Highest_IC);
		}
		else if(Mode == 3){
			Create_new_Generation_CascodedOTA_with_different_ICs(temp_firstParent,temp_secondParent,CascodedOTA_Designs,NumberOfChilds,Ibias_Table[index_Ibias],Ibias_Table[index_Ibias],Lowest_Length,Highest_Length,data_sheet.IC_Ranges_CascodedOTA);
		}
		

		
		//for (i=0;i<sizeof(SimpleOTA_Designs)/sizeof(SimpleOTA);i++){
		//	Calculate_Mosfets_Parameters(SimpleOTA_Designs[i].Mosfets,SimpleOTA_Designs[i].Ibias);  !! MALLON DEN XRIAZETE !!
		//}
		
	/*	//Test print for new Generation for SimpleOTA
		printf("\nGeneration Number : %d\n",Step+1);
		for (i=0;i<sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA);i++){
			printf("\nIbias Design%d :%g\n",i,CascodedOTA_Designs[i].Ibias);
			for (j=0;j<17;j++){
				printf("L%d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].L);
				printf("IC%d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].IC);
				
				printf("W%d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].W);
				printf("u0 %d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].u0);
				printf("n0 %d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].n0);
				printf("Io %d:%g ",j,(double) CascodedOTA_Designs[i].Mosfets[j].Io);
				printf("\n"); 
			}
			
			
		}
		
		//Test print before Calculations (New Generation)	
		for (i=0;i<sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA);i++){
			printf("\nVoltageGain Design%d :%g\n",i,CascodedOTA_Designs[i].OTA_VoltageGain);
			printf("\nFrequencyResponse Design%d :%g\n",i,CascodedOTA_Designs[i].OTA_FrequencyResponse);
		}*/
	
	
	// Calculate Specs For each CascodedOTA 
		for (i=0;i<sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA);i++){
			//Calculate Transconductance (GM) for each Design {Transconductance_Calc_CascodedOTA(double Ibias,double IC1)}
			CascodedOTA_Designs[i].OTA_Transconductance = Transconductance_Calc_CascodedOTA(CascodedOTA_Designs[i].Ibias,CascodedOTA_Designs[i].Mosfets[0].IC);
			
			//Calculate OutputResistance (Rout) for each Design {OutputResistance_Calc_CascodedOTA(struct device Mosfets[],double Ibias)}
			CascodedOTA_Designs[i].OTA_OutputResistance = OutputResistance_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets,CascodedOTA_Designs[i].Ibias);
			
			//Calculate VoltageGain (Av) for each Design {VoltageGain_Calc_CascodedOTA(double GM,double Rout)}
			CascodedOTA_Designs[i].OTA_VoltageGain = VoltageGain_Calc_CascodedOTA(CascodedOTA_Designs[i].OTA_Transconductance,CascodedOTA_Designs[i].OTA_OutputResistance);
			
			//Calculate FrequencyResponse (f-3dB) for each Design {FrequencyResponse_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_FrequencyResponse = FrequencyResponse_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate PhaseMargin (PM) for each Design {PhaseMargin_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_PhaseMargin = PhaseMargin_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
					
			//Calculate ThermalNoise (Svin(thermal)) for each Design {Thermal_Noise_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Thermal_Noise = Thermal_Noise_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate FlickerNoise (Svin(flicker)) for each Design {Flicker_Noise_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Flicker_Noise = Flicker_Noise_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Offset_Voltage due to Local-Area Mismatch (Vsquare_InOffset) for each Design {Offset_Voltage_input_DueTo_Mismatch_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch = Offset_Voltage_input_DueTo_Mismatch_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
		
			//Calculate Input_Capacitance (Cindif) for each Design {Input_Capacitance_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Input_Capacitance = Input_Capacitance_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Output_Capacitance (COUT) for each Design {Output_Capacitance_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Output_Capacitance = Output_Capacitance_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Slew_Rate (SR) for each Design {Slew_Rate_Calc_CascodedOTA(double COUT,double Ibias)}
			CascodedOTA_Designs[i].OTA_Slew_Rate = Slew_Rate_Calc_CascodedOTA(CascodedOTA_Designs[i].OTA_Output_Capacitance,CascodedOTA_Designs[i].Ibias);
			
			// Calculate VINCM_Plus (VINCM+) for each Design  {VINCM_Plus_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_VINCM_Plus = VINCM_Plus_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate VINCM_Minus (VINCM-) for each Design {VINCM_Minus_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_VINCM_Minus = VINCM_Minus_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Maximun_Output_Voltage (Vout+) for each Design {Maximun_Output_Voltage_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage = Maximun_Output_Voltage_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Minimum_Output_Voltage (Vout-) for each Design {Minimum_Output_Voltage_Calc_CascodedOTA(struct device Mosfets[])}
			CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage = Minimum_Output_Voltage_Calc_CascodedOTA(CascodedOTA_Designs[i].Mosfets);
			
			//Calculate Power_Consumption (PC) for each Design {Power_Consumption_Calc_CascodedOTA(double Ibias)}
			CascodedOTA_Designs[i].OTA_Power_Consumption = Power_Consumption_Calc_CascodedOTA(CascodedOTA_Designs[i].Ibias);	
	
		}
		
	/*			//Test print after Calculations (New Generation)	SimpleOTA
		printf("\n\n\n");
		for (i=0;i<sizeof(CascodedOTA_Designs)/sizeof(CascodedOTA);i++){
			printf("\n\tVoltageGain Design%d :%g\n",i,CascodedOTA_Designs[i].OTA_VoltageGain);
			printf("\n\tFrequencyResponse Design%d :%g\n",i,CascodedOTA_Designs[i].OTA_FrequencyResponse);
			printf("\n\tPhaseMargin Design%d :%g\n",i,CascodedOTA_Designs[i].OTA_PhaseMargin);
			printf("\n\tFrequencyResponse*nVoltageGain Design%d :%g\n",i,(CascodedOTA_Designs[i].OTA_FrequencyResponse)*(CascodedOTA_Designs[i].OTA_VoltageGain));
			printf("\n\tThermal_Noise Design%d :%g",i,CascodedOTA_Designs[i].OTA_Thermal_Noise);
			printf("\n\tFlicker_Noise Design%d :%g",i,CascodedOTA_Designs[i].OTA_Flicker_Noise);
			printf("\n\tOffset_Voltage due to Local-Area Mismatch Design%d :%g",i,CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch);
			printf("\n\tInput_Capacitance Design%d :%g",i,CascodedOTA_Designs[i].OTA_Input_Capacitance);
			printf("\n\tOutput_Capacitance Design%d :%g",i,CascodedOTA_Designs[i].OTA_Output_Capacitance);
			printf("\n\tSlew_Rate Design%d :%g",i,CascodedOTA_Designs[i].OTA_Slew_Rate);
			printf("\n\tVINCM_Plus Design%d :%g",i,CascodedOTA_Designs[i].OTA_VINCM_Plus);
			printf("\n\tVINCM_Minus Design%d :%g",i,CascodedOTA_Designs[i].OTA_VINCM_Minus);
			printf("\n\tMaximun_Output_Voltage Design%d :%g",i,CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage);
			printf("\n\tMinimun_Output_Voltage Design%d :%g",i,CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage);
			printf("\n\tPower_Consumption Design%d :%g",i,CascodedOTA_Designs[i].OTA_Power_Consumption);
		}
	*/
	
		
	}
	
		old_temp_firstParent=temp_firstParent;
		old_temp_secondParent=temp_secondParent;
		Step = Step+1;
		
	}while(Step < Number_Of_generation);   //Here we declare the number of Generations that will be created.
	
	
	
	//Save Best_SimpleOTA_Design for each Ibias !!!
	if(Mode == 0 || Mode == 2){
		Best_SimpleOTA_Designs[index_Ibias]	= Best_Design;
	}
	else if(Mode == 1 || Mode == 3){
		Best_CascodedOTA_Designs[index_Ibias]= Best_Design_CascodedOTA;
	}

} // End of Table_Ibias


if(Mode == 0 || Mode == 2){	
	//Here we Create the txt with Ibias and FoMs for Matlabs {Create_and_Calculate_txt_data_for_FOMs (struct SimpleOTA Best_SimpleOTA_Designs[],int Length)}
	Create_and_Calculate_txt_data_for_FOMs(Best_SimpleOTA_Designs,sizeof(Ibias_Table)/sizeof(Ibias_Table[0]));
}
else if(Mode == 1 || Mode == 3){
	Create_and_Calculate_txt_data_for_FOMs_CascodedOTA(Best_CascodedOTA_Designs,sizeof(Ibias_Table)/sizeof(Ibias_Table[0]));
}
	

if(Mode == 0 || Mode == 2){	
	//Print the Pre_last first parent design Calculations for SimpleOTA.	
	printf("\n\n\nPre_Last first Parent design's Specs:\n");
	printf("\n\tIbias :%g",Pre_Last_Parent_Design.Ibias);
	printf("\n\tVoltageGain :%g",Pre_Last_Parent_Design.OTA_VoltageGain);
	printf("\n\tFrequencyResponse (Hz) :%g",Pre_Last_Parent_Design.OTA_FrequencyResponse);
	printf("\n\tPhaseMargin (degrees) :%g",Pre_Last_Parent_Design.OTA_PhaseMargin);
	printf("\n\tFrequencyResponse*nVoltageGain :%g",(Pre_Last_Parent_Design.OTA_FrequencyResponse)*(Pre_Last_Parent_Design.OTA_VoltageGain));
	printf("\n\tThermal_Noise (joule*Ohm) :%g",Pre_Last_Parent_Design.OTA_Thermal_Noise);
	printf("\n\tFlicker_Noise (Volts^2) :%g",Pre_Last_Parent_Design.OTA_Flicker_Noise);
	printf("\n\tOffset_Voltage due to Local-Area Mismatch (mV^2):%g",Pre_Last_Parent_Design.OTA_Offset_Voltage_input_DueTo_Mismatch);
	printf("\n\tInput_Capacitance (ff):%g",Pre_Last_Parent_Design.OTA_Input_Capacitance);
	printf("\n\tOutput_Capacitance (ff):%g",Pre_Last_Parent_Design.OTA_Output_Capacitance);
	printf("\n\tSlew_Rate (uA/ff):%g",Pre_Last_Parent_Design.OTA_Slew_Rate);
	printf("\n\tVINCM_Plus (Volts):%g",Pre_Last_Parent_Design.OTA_VINCM_Plus);
	printf("\n\tVINCM_Minus (Volts):%g",Pre_Last_Parent_Design.OTA_VINCM_Minus);
	printf("\n\tMaximun_Output_Voltage (Volts):%g",Pre_Last_Parent_Design.OTA_Maximun_Output_Voltage);
	printf("\n\tMinimun_Output_Voltage (Volts):%g",Pre_Last_Parent_Design.OTA_Minimum_Output_Voltage);
	printf("\n\tPower_Consumption(uWatts):%g",Pre_Last_Parent_Design.OTA_Power_Consumption);
	printf("\n\nBest Design characteristics:\n");
	for (j=0;j<10;j++){
		printf("L%d:%g ",j,(double) Pre_Last_Parent_Design.Mosfets[j].L);
		printf("IC%d:%g ",j,(double) Pre_Last_Parent_Design.Mosfets[j].IC);
		printf("IC_WithOutVS%d:%g ",j,(double) Pre_Last_Parent_Design.Mosfets[j].IC_WithOutVS);
				
		printf("W%d:%g ",j,(double) Pre_Last_Parent_Design.Mosfets[j].W);
		printf("Thermal_noise_factor%d:%g ",j,Pre_Last_Parent_Design.Mosfets[j].Thermal_noise_factor);
		printf("gm%d:%g ",j,(double) Pre_Last_Parent_Design.Mosfets[j].gm);
		printf("u0 %d:%g ",j,(double) Pre_Last_Parent_Design.Mosfets[j].u0);
		printf("n0 %d:%g ",j,(double) Pre_Last_Parent_Design.Mosfets[j].n0);
		printf("Io %d:%g ",j,(double) Pre_Last_Parent_Design.Mosfets[j].Io);
		printf("KF %d:%g ",j,(double) Pre_Last_Parent_Design.Mosfets[j].KF);
		printf("AF %d:%g ",j,(double) Pre_Last_Parent_Design.Mosfets[j].AF);
		printf("AVTO %d:%g ",j,(double) Pre_Last_Parent_Design.Mosfets[j].AVTO);
		printf("VT %d:%g(V) ",j,(double) Pre_Last_Parent_Design.Mosfets[j].VT);
		printf("\n"); 
		}
		
	//Print the best design Calculations for Simple_OTA.	
	printf("\n\n\nBest design's Specs:\n");
	printf("\n\tIbias :%g",Best_Design.Ibias);
	printf("\n\tVoltageGain :%g",Best_Design.OTA_VoltageGain);
	printf("\n\tFrequencyResponse (Hz) :%g",Best_Design.OTA_FrequencyResponse);
	printf("\n\tPhaseMargin (degrees) :%g",Best_Design.OTA_PhaseMargin);
	printf("\n\tFrequencyResponse*nVoltageGain :%g",(Best_Design.OTA_FrequencyResponse)*(Best_Design.OTA_VoltageGain));
	printf("\n\tThermal_Noise (joule*Ohm) :%g",Best_Design.OTA_Thermal_Noise);
	printf("\n\tFlicker_Noise (Volts^2) :%g",Best_Design.OTA_Flicker_Noise);
	printf("\n\tOffset_Voltage due to Local-Area Mismatch (mV^2):%g",Best_Design.OTA_Offset_Voltage_input_DueTo_Mismatch);
	printf("\n\tInput_Capacitance (ff):%g",Best_Design.OTA_Input_Capacitance);
	printf("\n\tOutput_Capacitance (ff):%g",Best_Design.OTA_Output_Capacitance);
	printf("\n\tSlew_Rate (uA/ff):%g",Best_Design.OTA_Slew_Rate);
	printf("\n\tVINCM_Plus (Volts):%g",Best_Design.OTA_VINCM_Plus);
	printf("\n\tVINCM_Minus (Volts):%g",Best_Design.OTA_VINCM_Minus);
	printf("\n\tMaximun_Output_Voltage (Volts):%g",Best_Design.OTA_Maximun_Output_Voltage);
	printf("\n\tMinimun_Output_Voltage (Volts):%g",Best_Design.OTA_Minimum_Output_Voltage);
	printf("\n\tPower_Consumption(uWatts):%g",Best_Design.OTA_Power_Consumption);
	printf("\n\nBest Design characteristics:\n");
	for (j=0;j<10;j++){
		printf("L%d:%g ",j,(double) Best_Design.Mosfets[j].L);
		printf("IC%d:%g ",j,(double) Best_Design.Mosfets[j].IC);
		printf("IC_WithOutVS%d:%g ",j,(double) Best_Design.Mosfets[j].IC_WithOutVS);

				
		printf("W%d:%g ",j,(double) Best_Design.Mosfets[j].W);
		printf("Thermal_noise_factor%d:%g ",j,Best_Design.Mosfets[j].Thermal_noise_factor);
		printf("gm%d:%g ",j,(double) Best_Design.Mosfets[j].gm);
		printf("u0 %d:%g ",j,(double) Best_Design.Mosfets[j].u0);
		printf("n0 %d:%g ",j,(double) Best_Design.Mosfets[j].n0);
		printf("Io %d:%g ",j,(double) Best_Design.Mosfets[j].Io);
		printf("KF %d:%g ",j,(double) Best_Design.Mosfets[j].KF);
		printf("AF %d:%g ",j,(double) Best_Design.Mosfets[j].AF);
		printf("AVTO %d:%g ",j,(double) Best_Design.Mosfets[j].AVTO);
		printf("VT %d:%g(V) ",j,(double) Best_Design.Mosfets[j].VT);
		printf("\n"); 
		}
	
	
}
else if(Mode == 1 || Mode == 3){	
	//Print the Pre_last first parent design Calculations for CascodedOTA.	
	printf("\n\n\nPre_Last first Parent design's Specs:\n");
	printf("\n\tIbias :%g",Pre_Last_Parent_Design_CascodedOTA.Ibias);
	printf("\n\tVoltageGain :%g",Pre_Last_Parent_Design_CascodedOTA.OTA_VoltageGain);
	printf("\n\tFrequencyResponse (Hz) :%g",Pre_Last_Parent_Design_CascodedOTA.OTA_FrequencyResponse);
	printf("\n\tPhaseMargin (degrees) :%g",Pre_Last_Parent_Design_CascodedOTA.OTA_PhaseMargin);
	printf("\n\tFrequencyResponse*nVoltageGain :%g",(Pre_Last_Parent_Design_CascodedOTA.OTA_FrequencyResponse)*(Pre_Last_Parent_Design_CascodedOTA.OTA_VoltageGain));
	printf("\n\tThermal_Noise (joule*Ohm) :%g",Pre_Last_Parent_Design_CascodedOTA.OTA_Thermal_Noise);
	printf("\n\tFlicker_Noise (Volts^2) :%g",Pre_Last_Parent_Design_CascodedOTA.OTA_Flicker_Noise);
	printf("\n\tOffset_Voltage due to Local-Area Mismatch (mV^2):%g",Pre_Last_Parent_Design_CascodedOTA.OTA_Offset_Voltage_input_DueTo_Mismatch);
	printf("\n\tInput_Capacitance (ff):%g",Pre_Last_Parent_Design_CascodedOTA.OTA_Input_Capacitance);
	printf("\n\tOutput_Capacitance (ff):%g",Pre_Last_Parent_Design_CascodedOTA.OTA_Output_Capacitance);
	printf("\n\tSlew_Rate (uA/ff):%g",Pre_Last_Parent_Design_CascodedOTA.OTA_Slew_Rate);
	printf("\n\tVINCM_Plus (Volts):%g",Pre_Last_Parent_Design_CascodedOTA.OTA_VINCM_Plus);
	printf("\n\tVINCM_Minus (Volts):%g",Pre_Last_Parent_Design_CascodedOTA.OTA_VINCM_Minus);
	printf("\n\tMaximun_Output_Voltage (Volts):%g",Pre_Last_Parent_Design_CascodedOTA.OTA_Maximun_Output_Voltage);
	printf("\n\tMinimun_Output_Voltage (Volts):%g",Pre_Last_Parent_Design_CascodedOTA.OTA_Minimum_Output_Voltage);
	printf("\n\tPower_Consumption(uWatts):%g",Pre_Last_Parent_Design_CascodedOTA.OTA_Power_Consumption);
	printf("\n\nBest Design characteristics:\n");
	for (j=0;j<17;j++){
		printf("L%d:%g ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].L);
		printf("IC%d:%g ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].IC);
		printf("IC_WithOutVS%d:%g ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].IC_WithOutVS);
				
		printf("W%d:%g ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].W);
		printf("Thermal_noise_factor%d:%g ",j,Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].Thermal_noise_factor);
		printf("gm%d:%g ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].gm);
		printf("u0 %d:%g ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].u0);
		printf("n0 %d:%g ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].n0);
		printf("Io %d:%g ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].Io);
		printf("KF %d:%g ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].KF);
		printf("AF %d:%g ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].AF);
		printf("AVTO %d:%g ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].AVTO);
		printf("VT %d:%g(V) ",j,(double) Pre_Last_Parent_Design_CascodedOTA.Mosfets[j].VT);
		printf("\n"); 
		}
		
	//Print the best design Calculations for CascodedOTA.	
	printf("\n\n\nBest design's Specs:\n");
	printf("\n\tIbias :%g",Best_Design_CascodedOTA.Ibias);
	printf("\n\tVoltageGain :%g",Best_Design_CascodedOTA.OTA_VoltageGain);
	printf("\n\tFrequencyResponse (Hz) :%g",Best_Design_CascodedOTA.OTA_FrequencyResponse);
	printf("\n\tPhaseMargin (degrees) :%g",Best_Design_CascodedOTA.OTA_PhaseMargin);
	printf("\n\tFrequencyResponse*nVoltageGain :%g",(Best_Design_CascodedOTA.OTA_FrequencyResponse)*(Best_Design_CascodedOTA.OTA_VoltageGain));
	printf("\n\tThermal_Noise (joule*Ohm) :%g",Best_Design_CascodedOTA.OTA_Thermal_Noise);
	printf("\n\tFlicker_Noise (Volts^2) :%g",Best_Design_CascodedOTA.OTA_Flicker_Noise);
	printf("\n\tOffset_Voltage due to Local-Area Mismatch (mV^2):%g",Best_Design_CascodedOTA.OTA_Offset_Voltage_input_DueTo_Mismatch);
	printf("\n\tInput_Capacitance (ff):%g",Best_Design_CascodedOTA.OTA_Input_Capacitance);
	printf("\n\tOutput_Capacitance (ff):%g",Best_Design_CascodedOTA.OTA_Output_Capacitance);
	printf("\n\tSlew_Rate (uA/ff):%g",Best_Design_CascodedOTA.OTA_Slew_Rate);
	printf("\n\tVINCM_Plus (Volts):%g",Best_Design_CascodedOTA.OTA_VINCM_Plus);
	printf("\n\tVINCM_Minus (Volts):%g",Best_Design_CascodedOTA.OTA_VINCM_Minus);
	printf("\n\tMaximun_Output_Voltage (Volts):%g",Best_Design_CascodedOTA.OTA_Maximun_Output_Voltage);
	printf("\n\tMinimun_Output_Voltage (Volts):%g",Best_Design_CascodedOTA.OTA_Minimum_Output_Voltage);
	printf("\n\tPower_Consumption(uWatts):%g",Best_Design_CascodedOTA.OTA_Power_Consumption);
	printf("\n\nBest Design characteristics:\n");
	for (j=0;j<17;j++){
		printf("L%d:%g ",j,(double) Best_Design_CascodedOTA.Mosfets[j].L);
		printf("IC%d:%g ",j,(double) Best_Design_CascodedOTA.Mosfets[j].IC);
		printf("IC_WithOutVS%d:%g ",j,(double) Best_Design_CascodedOTA.Mosfets[j].IC_WithOutVS);

				
		printf("W%d:%g ",j,(double) Best_Design_CascodedOTA.Mosfets[j].W);
		printf("Thermal_noise_factor%d:%g ",j,Best_Design_CascodedOTA.Mosfets[j].Thermal_noise_factor);
		printf("gm%d:%g ",j,(double) Best_Design_CascodedOTA.Mosfets[j].gm);
		printf("u0 %d:%g ",j,(double) Best_Design_CascodedOTA.Mosfets[j].u0);
		printf("n0 %d:%g ",j,(double) Best_Design_CascodedOTA.Mosfets[j].n0);
		printf("Io %d:%g ",j,(double) Best_Design_CascodedOTA.Mosfets[j].Io);
		printf("KF %d:%g ",j,(double) Best_Design_CascodedOTA.Mosfets[j].KF);
		printf("AF %d:%g ",j,(double) Best_Design_CascodedOTA.Mosfets[j].AF);
		printf("AVTO %d:%g ",j,(double) Best_Design_CascodedOTA.Mosfets[j].AVTO);
		printf("VT %d:%g(V) ",j,(double) Best_Design_CascodedOTA.Mosfets[j].VT);
		printf("\n"); 
		}
	
	
}


	//Creating file.txt with Sizes.
	if(Mode == 0 || Mode == 2){	
		Create_txt_data(Best_Design);
	}
	else if(Mode == 1 || Mode == 3){
		 Create_txt_data_CascodedOTA(Best_Design_CascodedOTA);
	}

	
    // printf() displays the string inside quotation
    printf("\nHello, World!");
    
    //TestPirntForDataSheet
    printf("\n\ndata_sheet.n0_nmos:%lf\n",data_sheet.n0_nmos); 
    printf("\n\ndata_sheet.n0_pmos:%lf\n",data_sheet.n0_pmos);
    printf("\n\ndata_sheet.Ut:%lf\n",data_sheet.Ut); 
    printf("\n\ndata_sheet.Lsat:%g\n",data_sheet.Lsat); 
    printf("\n\ndata_sheet.Val_nmos:%lf\n",data_sheet.Val_nmos);
    printf("\n\ndata_sheet.Val_pmos:%lf\n",data_sheet.Val_pmos); 
    
    printf("\n\ndata_sheet.Cox:%lf\n",data_sheet.Cox); 
    printf("\n\ndata_sheet.u0_nmos:%lf\n",data_sheet.u0_nmos); 
	printf("\n\ndata_sheet.u0_pmos:%lf\n",data_sheet.u0_pmos); 
	
	printf("\n\ndata_sheet.Io_nmos:%g\n",data_sheet.Io_nmos); 
	printf("\n\ndata_sheet.Io_pmos:%g\n",data_sheet.Io_pmos); 
	printf("\n\ndata_sheet.T:%lf\n",data_sheet.T); 
	printf("\n\ndata_sheet.k:%g\n",data_sheet.k); 
	printf("\n\ndata_sheet.VT_nmos:%g\n",data_sheet.VT_nmos); 
	printf("\n\ndata_sheet.VT_pmos:%g\n",data_sheet.VT_pmos);
	
	printf("\n\ndata_sheet.KF_nmos:%g\n",data_sheet.KF_nmos); 
	printf("\n\ndata_sheet.KF_nmos:%g\n",data_sheet.KF_nmos_hand_sqr); 
	printf("\n\ndata_sheet.AF_nmos:%g\n",data_sheet.AF_nmos); 
	printf("\n\ndata_sheet.KF_pmos:%g\n",data_sheet.KF_pmos);
	printf("\n\ndata_sheet.KF_nmos:%g\n",data_sheet.KF_pmos_hand_sqr);  
	printf("\n\ndata_sheet.AF_pmos:%g\n",data_sheet.AF_pmos); 

	printf("\n\ndata_sheet.AVTO_nmos:%g\n",data_sheet.AVTO_nmos); 
	printf("\n\ndata_sheet.AVTO_pmos:%g\n",data_sheet.AVTO_pmos); 
	
	printf("\n\ndata_sheet.CJ_nmos:%g\n",data_sheet.CJ_nmos); 
	printf("\n\ndata_sheet.CJ_pmos:%g\n",data_sheet.CJ_pmos); 
	printf("\n\ndata_sheet.CJSW_nmos:%g\n",data_sheet.CJSW_nmos); 
	printf("\n\ndata_sheet.CJSW_pmos:%g\n",data_sheet.CJSW_pmos); 
	printf("\n\ndata_sheet.Wdif:%g\n",data_sheet.Wdif); 
	
	printf("\n\ndata_sheet.VDD:%g\n",data_sheet.VDD); 
	printf("\n\ndata_sheet.VSS:%g\n",data_sheet.VSS); 
	printf("\n\ndata_sheet.CL:%g\n",data_sheet.CL); 
	
	printf("\n\ndata_sheet.a0:%g\n",data_sheet.a0);
	printf("\n\ndata_sheet.a1:%g\n",data_sheet.a1); 
	printf("\n\ndata_sheet.a2:%g\n",data_sheet.a2); 
	printf("\n\ndata_sheet.a3:%g\n",data_sheet.a3); 
	printf("\n\ndata_sheet.a4:%g\n",data_sheet.a4); 
	printf("\n\ndata_sheet.a5:%g\n",data_sheet.a5); 
	printf("\n\ndata_sheet.a6:%g\n",data_sheet.a6); 
	printf("\n\ndata_sheet.a7:%g\n",data_sheet.a7);
	printf("\n\ndata_sheet.a8:%g\n",data_sheet.a8);
	printf("\n\ndata_sheet.a9:%g\n",data_sheet.a9);  
	for(i=0;i<10;i++){
		printf("\n\ndata_sheet.IC_Ranges_CurrentMirrorOTA[%d]:%g\n",i+1,data_sheet.IC_Ranges_CurrentMirrorOTA[i]); 
	} 
	 
	for(i=0;i<12;i++){
		printf("\n\ndata_sheet.IC_Ranges_CascodedOTA[%d]:%g\n",i+1,data_sheet.IC_Ranges_CascodedOTA[i]); 
	} 

	system("pause");
    return 0;
}


//----------------------Functions-----------------------------------


//------------------------SimpleOTA_SpecsCalculate_functions---------------------------

double Transconductance_Calc(double Ibias,double IC1){
	
	double GM;
	GM =  Ibias/(n0_nmos*Ut*(sqrt(IC1+0.25)+0.5));
	return GM;
}

double OutputResistance_Calc(double L4,double L6,double Ibias){
	
	double rds4,rds6,Rout;
	//Convert L4 and l6 from m to um !!!
	L4 = L4*1e6;
	L6 = L6*1e6;
	
	rds4 = (Val_nmos*L4)/Ibias;
	rds6 = (Val_pmos*L6)/Ibias;
		//Rout = rds4||rds6
	Rout = (rds4*rds6)/(rds4+rds6);
	
	return Rout;
}

double VoltageGain_Calc(double GM,double Rout){
	
	double VoltGain;
	
	VoltGain = GM*Rout;
	
	return VoltGain;
}

double FrequencyResponse_Calc(struct device Mosfets[]){
	
//	double CGOX;//Gate-oxide capacitance 
//	double Cgsi5,Cgbi5,Cgsi5_ton,Cgbi5_ton;
	//Conver W and L from Meters to um
//	W5 = Mosfets5.W*1e6;
//	L5 = Mosfets5.L*1e6;
//	CGOX = W5*L5*Cox ; // ff

	double FreqResponse;
	double Cgsi5_ton,Cgbi5_ton;
	
	if(Mosfets[4].IC < 10 ){
		// we are in Moderate Inversion : M.I.
		Cgsi5_ton = 0.3333; 
		Cgbi5_ton = 0.6666*(Mosfets[4].n0-1)/Mosfets[4].n0 ;
	}
	else{
		// we are in Strong Inversion : S.I.
		Cgsi5_ton = 0.6666;
		Cgbi5_ton = 0.3333*(Mosfets[4].n0-1)/Mosfets[4].n0 ;
		
	}	
	
//	printf("\n\n %lf %lf %lf %lf %lf %lf %lf\n\n:",k,Cgsi5_ton,Cgbi5_ton,Mosfets[4].IC,sqrt(Mosfets[4].IC+0.25)+0.5,Mosfets[4].u0*Ut,(3.14*(Cgsi5_ton+Cgbi5_ton)));
//	printf("\n %g \n",(0.5)*(Mosfets[4].IC/sqrt(Mosfets[4].IC+0.25)+0.5)*( (Mosfets[4].u0*Ut)/(3.14*(Cgsi5_ton+Cgbi5_ton))));
 	
 	//*1e-2 for better results (Cause Pole for diode is greater than the real Pole)
	FreqResponse = (0.5)*(Mosfets[4].IC/sqrt(Mosfets[4].IC+0.25)+0.5)*( (Mosfets[4].u0*Ut*0.0001)/(3.14*(Cgsi5_ton+Cgbi5_ton)*(pow(Mosfets[4].L,2)) ))*1e-2; // Here we must Convert u0 from Cm^2/V*s to m^2/V*s ,So we multi with 0.0001
	
	return FreqResponse;
}

double PhaseMargin_Calc(struct device Mosfets[]){
	
	double PM;
	double CL = C_LOAD; // 5 pf
	double w_GBW;
	
	double dominant_pole;
	double Cgsi5_ton,Cgbi5_ton;
	
	//Calculate first pole
	if(Mosfets[4].IC < 10 ){
		// we are in Moderate Inversion : M.I.
		Cgsi5_ton = 0.3333; 
		Cgbi5_ton = 0.6666*(Mosfets[4].n0-1)/Mosfets[4].n0 ;
	}
	else{
		// we are in Strong Inversion : S.I.
		Cgsi5_ton = 0.6666;
		Cgbi5_ton = 0.3333*(Mosfets[4].n0-1)/Mosfets[4].n0 ;
		
	}
	//*1e-2 for better results (Cause Pole for diode is greater than the real Pole)
	dominant_pole = (0.5)*(Mosfets[4].IC/sqrt(Mosfets[4].IC+0.25)+0.5)*( (Mosfets[4].u0*Ut*0.0001)/(3.14*(Cgsi5_ton+Cgbi5_ton)*(pow(Mosfets[4].L,2)) )); // Here we must Convert u0 from Cm^2/V*s to m^2/V*s ,So we multi with 0.0001
	
	//Calculate second pole
	double second_pole;
	double Cgsi3_ton,Cgbi3_ton;
	
	if(Mosfets[2].IC < 10 ){
		// we are in Moderate Inversion : M.I.
		Cgsi3_ton = 0.3333; 
		Cgbi3_ton = 0.6666*(Mosfets[2].n0-1)/Mosfets[2].n0 ;
	}
	else{
		// we are in Strong Inversion : S.I.
		Cgsi3_ton = 0.6666;
		Cgbi3_ton = 0.3333*(Mosfets[2].n0-1)/Mosfets[2].n0 ;
		
	}
	
	//*1e-2 for better results (Cause Pole for diode is greater than the real Pole)	
	second_pole = (0.5)*(Mosfets[2].IC/sqrt(Mosfets[2].IC+0.25)+0.5)*( (Mosfets[2].u0*Ut*0.0001)/(3.14*(Cgsi3_ton+Cgbi3_ton)*(pow(Mosfets[3].L,2)) ));    // Here we must Convert u0 from Cm^2/V*s to m^2/V*s ,So we multi with 0.0001
 	
 	
 	w_GBW = Mosfets[1].gm / CL*1e3 ;    // w_GBW // Converting CL to ff
 	
 	PM = 180 -  ( (atan(w_GBW/dominant_pole)*180 )/3.14 )*0.75   - ( (atan(w_GBW/second_pole)*180 )/3.14 )*0.75  ; //*0.75  
	return PM;
}

double Thermal_Noise_Calc(struct device Mosfets[]){
	
	double SVin_thermal;
	double RNP1,RNP3,RNP5,RNP7;
	
	RNP1 = (Mosfets[0].n0*Mosfets[0].Thermal_noise_factor)/Mosfets[0].gm; // M1
	
	RNP3 = (Mosfets[2].n0*Mosfets[2].Thermal_noise_factor*Mosfets[2].gm)/pow((Mosfets[0].gm),2); // M3
	RNP5 = (Mosfets[4].n0*Mosfets[4].Thermal_noise_factor*Mosfets[4].gm)/pow((Mosfets[0].gm),2); // M5
	RNP7 = (Mosfets[6].n0*Mosfets[6].Thermal_noise_factor*Mosfets[6].gm)/pow((Mosfets[0].gm),2); // M7
	
	SVin_thermal = 2*4*k*T*(RNP1+RNP3+RNP5+RNP7);
	return SVin_thermal;
}


double Flicker_Noise_Calc(struct device Mosfets[]){
	
	double SVin_flicker = 0 , sum = 0 ;
	double RNP1,RNP3,RNP5,RNP7;
	int i,frequency = 50;
	
	
	
	for(i=1;i<2;i++){
		frequency = frequency*i;
		RNP1 = 1;	 // Converting to 1e18
		RNP3 = (Mosfets[2].KF/Mosfets[0].KF) * ( ( (Mosfets[0].W)*(Mosfets[0].L) ) / ( (Mosfets[2].W)*(Mosfets[2].L) ) ) * pow((Mosfets[2].gm/Mosfets[0].gm),2) * pow(frequency,Mosfets[0].AF-Mosfets[2].AF); 
		RNP5 = (Mosfets[4].KF/Mosfets[0].KF) * ( ( (Mosfets[0].W)*(Mosfets[0].L) ) / ( (Mosfets[4].W)*(Mosfets[4].L) ) ) * pow((Mosfets[4].gm/Mosfets[0].gm),2) * pow(frequency,Mosfets[0].AF-Mosfets[4].AF);
		RNP7 = (Mosfets[6].KF/Mosfets[0].KF) * ( ( (Mosfets[0].W)*(Mosfets[0].L) ) / ( (Mosfets[6].W)*(Mosfets[6].L) ) ) * pow((Mosfets[6].gm/Mosfets[0].gm),2) * pow(frequency,Mosfets[0].AF-Mosfets[6].AF);
	
		sum =  2*( (Mosfets[0].KF)/ ( (Mosfets[0].W*1e6) * (Mosfets[0].L*1e6) * pow(frequency,Mosfets[0].AF) ) ) * (RNP1 + RNP3 + RNP5 + RNP7);
	
		if (sum > 0){
			SVin_flicker = SVin_flicker + sum ;
		}
	}
	return SVin_flicker*1e-18;
	
}

double Offset_Voltage_input_DueTo_Mismatch_Calc(struct device Mosfets[]){
	
	double Vsquare_InOffset = 0;
	double RNP1,RNP3,RNP5,RNP7;
	
	RNP1 = 1;
	RNP3 = pow((Mosfets[2].AVTO/(Mosfets[0].AVTO )),2) * ((Mosfets[0].W*1e6*Mosfets[0].L*1e6)/(Mosfets[2].W*1e6*Mosfets[2].L*1e6)) * pow((Mosfets[2].gm/(Mosfets[0].gm )),2);
	RNP5 = pow((Mosfets[4].AVTO/(Mosfets[0].AVTO )),2) * ((Mosfets[0].W*1e6*Mosfets[0].L*1e6)/(Mosfets[4].W*1e6*Mosfets[4].L*1e6)) * pow((Mosfets[4].gm/(Mosfets[0].gm )),2);
	RNP7 = pow((Mosfets[6].AVTO/(Mosfets[0].AVTO )),2) * ((Mosfets[0].W*1e6*Mosfets[0].L*1e6)/(Mosfets[6].W*1e6*Mosfets[6].L*1e6)) * pow((Mosfets[6].gm/(Mosfets[0].gm )),2);
	
	Vsquare_InOffset = ( pow(Mosfets[0].AVTO,2) / (Mosfets[0].W*1e6*Mosfets[0].L*1e6) ) * (RNP1 + RNP3 + RNP5 + RNP7);
	return Vsquare_InOffset;
	
}

double Input_Capacitance_Calc(struct device Mosfets[]){
	
	double Cindiff = 0;
	double Cgsi1_ton,Cgbi1_ton;
	
	if(Mosfets[0].IC < 10 ){
		// we are in Moderate Inversion : M.I.
		Cgsi1_ton = 0.3333; 
		Cgbi1_ton = 0.6666*(Mosfets[0].n0-1)/Mosfets[0].n0 ;
	}
	else{
		// we are in Strong Inversion : S.I.
		Cgsi1_ton = 0.6666;
		Cgbi1_ton = 0.3333*(Mosfets[0].n0-1)/Mosfets[0].n0 ;
	}
	// Cox :ff/um^2
	Cindiff = 0.5 * (Mosfets[0].W*1e6*Mosfets[0].L*1e6 ) * Cox * ( Cgsi1_ton+Cgbi1_ton ); // ff
	
	return Cindiff;
	
}


double Output_Capacitance_Calc(struct device Mosfets[]){
		double COUT = 0;
		
		COUT = (Mosfets[3].W*1e6) * (0.5*Wdif*Mosfets[3].CJ + Mosfets[3].CJSW ) + (Mosfets[5].W*1e6) * (0.5*Wdif*Mosfets[5].CJ + Mosfets[5].CJSW );
		
		return COUT;
}


double Slew_Rate_Calc(double COUT,double Ibias){
	
	double SlewRate;
	double CL =C_LOAD; // 5pf
	
	SlewRate = 2*Ibias*1e6/(COUT + CL*1e3); // *1e6 : Converting Ibias to uA , *1e3 : Converting CL to ff
	return SlewRate;
	
}


double VINCM_Plus_Calc(struct device Mosfets[]){
	
	double VINCM_Plus;
	
	VINCM_Plus=VDD+2*Ut*(Mosfets[0].n0*sqrt(Mosfets[0].IC)-Mosfets[4].n0*sqrt(Mosfets[4].IC))+(Mosfets[0].VT-Mosfets[4].VT)-(2*Ut*sqrt(Mosfets[0].IC+0.25)+3*Ut);
	
	return VINCM_Plus;

}


double VINCM_Minus_Calc(struct device Mosfets[]){
	
	double VINCM_Minus;
	
	VINCM_Minus=VSS+(2*Mosfets[0].n0*Ut*sqrt(Mosfets[0].IC)+Mosfets[0].VT)+Mosfets[8].VDSsat;
	
	return VINCM_Minus;

}


double Maximun_Output_Voltage_Calc(struct device Mosfets[]){
	
	double VOUT_plus;
			
	VOUT_plus = VDD - Mosfets[5].VDSsat;
	
	return VOUT_plus;

}


double Minimum_Output_Voltage_Calc(struct device Mosfets[]){
	
	double VOUT_Minus;
	
	VOUT_Minus = VSS + Mosfets[3].VDSsat;
		
	return VOUT_Minus;

}


double Power_Consumption_Calc(double Ibias){
	double Power_Consumption;
	Power_Consumption = (VDD - VSS) * 4 * Ibias*1e6; 
	return Power_Consumption;
}
//--------------------------------------------------------------------------------------




//------------------------CascodeOTA_SpecsCalculate_functions---------------------------

double Transconductance_Calc_CascodedOTA(double Ibias,double IC1){
	
	double GM;
	GM =  ((Ibias*2)/3)/(n0_nmos*Ut*(sqrt(IC1+0.25)+0.5));
	return GM;
}


double OutputResistance_Calc_CascodedOTA(struct device Mosfets[],double Ibias){
	
	double Rout;
	
	double routD8;
	double rds2,rds4,rds8;
	//Convert L4 and l6 from m to um !!!
	rds2 = (Val_nmos*Mosfets[1].L*1e6)/((Ibias*2)/3);
	rds4 = (Val_pmos*Mosfets[3].L*1e6)/Ibias;
	rds8 = (Val_pmos*Mosfets[7].L*1e6)/(Ibias/3);
	
	//routD8 = (nAvi8)*(rds2//rds4)
	routD8 = rds8 * Mosfets[7].n0 * Mosfets[7].gm *((rds2*rds4)/(rds2+rds4));
	
	
	double routD10;
	double rds6,rds10;
	rds6 = (Val_nmos*Mosfets[5].L*1e6)/(Ibias/3);
	rds10 = (Val_nmos*Mosfets[9].L*1e6)/(Ibias/3);
	
	//routD10 = (nAvi10)*(rds6)
	routD10 = rds10 * Mosfets[9].n0 * Mosfets[0].gm * rds6;
	
	//Rout = routD8||routD10
	Rout = (routD8*routD10)/(routD8+routD10);
	
	return Rout;
}


double VoltageGain_Calc_CascodedOTA(double GM,double Rout){
	
	double VoltGain;
	
	VoltGain = GM*Rout;
	
	return VoltGain;
}


double FrequencyResponse_Calc_CascodedOTA(struct device Mosfets[]){
	
	double FreqResponse;
	double Cgsi5_ton,Cgbi5_ton;
	
	if(Mosfets[6].IC < 10 ){
		// we are in Moderate Inversion : M.I.
		Cgsi5_ton = 0.3333; 
		Cgbi5_ton = 0.6666*(Mosfets[6].n0-1)/Mosfets[6].n0 ;
	}
	else{
		// we are in Strong Inversion : S.I.
		Cgsi5_ton = 0.6666;
		Cgbi5_ton = 0.3333*(Mosfets[6].n0-1)/Mosfets[6].n0 ;
		
	}	
	
 	//*1e-4 for better results (Cause Pole for diode is greater than the real Pole)
	FreqResponse = (0.5)*(Mosfets[6].IC/sqrt(Mosfets[6].IC+0.25)+0.5)*( (Mosfets[6].u0*Ut*0.0001)/(3.14*(Cgsi5_ton+Cgbi5_ton)*(pow(Mosfets[6].L,2)) ))*1e-4; // Here we must Convert u0 from Cm^2/V*s to m^2/V*s ,So we multi with 0.0001
	
	return FreqResponse;
}


double PhaseMargin_Calc_CascodedOTA(struct device Mosfets[]){
	
	double PM;
	double CL = C_LOAD; // 5 pf
	double w_GBW;
	
	double dominant_pole;
	double Cgsi5_ton,Cgbi5_ton;
	
	//Calculate first pole
	if(Mosfets[6].IC < 10 ){
		// we are in Moderate Inversion : M.I.
		Cgsi5_ton = 0.3333; 
		Cgbi5_ton = 0.6666*(Mosfets[6].n0-1)/Mosfets[6].n0 ;
	}
	else{
		// we are in Strong Inversion : S.I.
		Cgsi5_ton = 0.6666;
		Cgbi5_ton = 0.3333*(Mosfets[6].n0-1)/Mosfets[6].n0 ;
		
	}
	//*1e-4 for better results (Cause Pole for diode is greater than the real Pole)
	dominant_pole = (0.5)*(Mosfets[4].IC/sqrt(Mosfets[4].IC+0.25)+0.5)*( (Mosfets[4].u0*Ut*0.0001)/(3.14*(Cgsi5_ton+Cgbi5_ton)*(pow(Mosfets[4].L,2)) )); // Here we must Convert u0 from Cm^2/V*s to m^2/V*s ,So we multi with 0.0001
	
	//Calculate second pole
	double second_pole;
	double Cgsi3_ton,Cgbi3_ton;
	
	if(Mosfets[2].IC < 10 ){
		// we are in Moderate Inversion : M.I.
		Cgsi3_ton = 0.3333; 
		Cgbi3_ton = 0.6666*(Mosfets[2].n0-1)/Mosfets[2].n0 ;
	}
	else{
		// we are in Strong Inversion : S.I.
		Cgsi3_ton = 0.6666;
		Cgbi3_ton = 0.3333*(Mosfets[2].n0-1)/Mosfets[2].n0 ;
		
	}
	
	//*1e-2 for better results (Cause Pole for diode is greater than the real Pole)	
	//second_pole = (0.5)*(Mosfets[2].IC/sqrt(Mosfets[2].IC+0.25)+0.5)*( (Mosfets[2].u0*Ut*0.0001)/(3.14*(Cgsi3_ton+Cgbi3_ton)*(pow(Mosfets[3].L,2)) ));    // Here we must Convert u0 from Cm^2/V*s to m^2/V*s ,So we multi with 0.0001
 	second_pole = 2*dominant_pole;
 	
 	w_GBW = Mosfets[1].gm / CL*1e3 ;    // w_GBW // Converting CL to ff
 	
 	PM = 180 -  ( (atan(w_GBW/dominant_pole)*180 )/3.14 )*0.75   - ( (atan(w_GBW/second_pole)*180 )/3.14 )*0.75  ; //*0.75  
	return PM;
}



double Thermal_Noise_Calc_CascodedOTA(struct device Mosfets[]){
	
	double SVin_thermal;
	double RNP1,RNP3,RNP5;
	
	RNP1 = (Mosfets[0].n0*Mosfets[0].Thermal_noise_factor)/Mosfets[0].gm; // M1
	
	RNP3 = (Mosfets[2].n0*Mosfets[2].Thermal_noise_factor*Mosfets[2].gm)/pow((Mosfets[0].gm),2); // M3
	RNP5 = (Mosfets[4].n0*Mosfets[4].Thermal_noise_factor*Mosfets[4].gm)/pow((Mosfets[0].gm),2); // M5
	
	SVin_thermal = 2*4*k*T*(RNP1+RNP3+RNP5);
	return SVin_thermal;
}


double Flicker_Noise_Calc_CascodedOTA(struct device Mosfets[]){
	
	double SVin_flicker = 0 , sum = 0 ;
	double RNP1,RNP3,RNP5;
	int i,frequency = 50;
	
	
	
	for(i=1;i<2;i++){
		frequency = frequency*i;
		RNP1 = 1;	 // Converting to 1e18
		RNP3 = (Mosfets[2].KF/Mosfets[0].KF) * ( ( (Mosfets[0].W)*(Mosfets[0].L) ) / ( (Mosfets[2].W)*(Mosfets[2].L) ) ) * pow((Mosfets[2].gm/Mosfets[0].gm),2) * pow(frequency,Mosfets[0].AF-Mosfets[2].AF); 
		RNP5 = (Mosfets[4].KF/Mosfets[0].KF) * ( ( (Mosfets[0].W)*(Mosfets[0].L) ) / ( (Mosfets[4].W)*(Mosfets[4].L) ) ) * pow((Mosfets[4].gm/Mosfets[0].gm),2) * pow(frequency,Mosfets[0].AF-Mosfets[4].AF);
	
		sum =  2*( (Mosfets[0].KF)/ ( (Mosfets[0].W*1e6) * (Mosfets[0].L*1e6) * pow(frequency,Mosfets[0].AF) ) ) * (RNP1 + RNP3 + RNP5);
	
		if (sum > 0){
			SVin_flicker = SVin_flicker + sum ;
		}
	}
	return SVin_flicker*1e-18;
	
}


double Offset_Voltage_input_DueTo_Mismatch_Calc_CascodedOTA(struct device Mosfets[]){
	
	double Vsquare_InOffset = 0;
	double RNP1,RNP3,RNP5;
	
	RNP1 = 1;
	RNP3 = pow((Mosfets[2].AVTO/(Mosfets[0].AVTO )),2) * ((Mosfets[0].W*1e6*Mosfets[0].L*1e6)/(Mosfets[2].W*1e6*Mosfets[2].L*1e6)) * pow((Mosfets[2].gm/(Mosfets[0].gm )),2);
	RNP5 = pow((Mosfets[4].AVTO/(Mosfets[0].AVTO )),2) * ((Mosfets[0].W*1e6*Mosfets[0].L*1e6)/(Mosfets[4].W*1e6*Mosfets[4].L*1e6)) * pow((Mosfets[4].gm/(Mosfets[0].gm )),2);
	
	Vsquare_InOffset = ( pow(Mosfets[0].AVTO,2) / (Mosfets[0].W*1e6*Mosfets[0].L*1e6) ) * (RNP1 + RNP3 + RNP5);
	return Vsquare_InOffset;
	
}


double Input_Capacitance_Calc_CascodedOTA(struct device Mosfets[]){
	
	double Cindiff = 0;
	double Cgsi1_ton,Cgbi1_ton;
	
	if(Mosfets[0].IC < 10 ){
		// we are in Moderate Inversion : M.I.
		Cgsi1_ton = 0.3333; 
		Cgbi1_ton = 0.6666*(Mosfets[0].n0-1)/Mosfets[0].n0 ;
	}
	else{
		// we are in Strong Inversion : S.I.
		Cgsi1_ton = 0.6666;
		Cgbi1_ton = 0.3333*(Mosfets[0].n0-1)/Mosfets[0].n0 ;
	}
	// Cox :ff/um^2
	Cindiff = 0.5 * (Mosfets[0].W*1e6*Mosfets[0].L*1e6 ) * Cox * ( Cgsi1_ton+Cgbi1_ton ); // ff
	
	return Cindiff;
	
}


double Output_Capacitance_Calc_CascodedOTA(struct device Mosfets[]){
		double COUT = 0;
		
		COUT = (Mosfets[7].W*1e6) * (0.5*Wdif*Mosfets[7].CJ + Mosfets[7].CJSW ) + (Mosfets[9].W*1e6) * (0.5*Wdif*Mosfets[9].CJ + Mosfets[9].CJSW );
		
		return COUT;
}


double Slew_Rate_Calc_CascodedOTA(double COUT,double Ibias){
	
	double SlewRate;
	double CL =C_LOAD; // 5pf
	
	SlewRate = 2*(Ibias/3)*1e6/(COUT + CL*1e3); // *1e6 : Converting Ibias to uA , *1e3 : Converting CL to ff
	return SlewRate;
	
}


double VINCM_Plus_Calc_CascodedOTA(struct device Mosfets[]){
	
	double VINCM_Plus,VDS3;
	
	VDS3 = 0.4; //Volts (Vdssat3 = 0.3 for IC =16)
	VINCM_Plus = VDD - VDS3 + (2*Ut*Mosfets[0].n0*sqrt(Mosfets[0].IC) + Mosfets[0].VT) - ( 2*Ut*sqrt(Mosfets[0].IC+0.25) + 3*Ut );
	
	return VINCM_Plus;

}


double VINCM_Minus_Calc_CascodedOTA(struct device Mosfets[]){
	
	double VINCM_Minus;
	
	VINCM_Minus=VSS+(2*Mosfets[0].n0*Ut*sqrt(Mosfets[0].IC)+Mosfets[0].VT)+Mosfets[14].VDSsat;
	
	return VINCM_Minus;

}


double Maximun_Output_Voltage_Calc_CascodedOTA(struct device Mosfets[]){
	
	double VOUT_plus,VDS4;
	
	VDS4 = 0.4; //Volts (Vdssat4 = 0.3 for IC =16)		
	VOUT_plus = VDD - VDS4 - Mosfets[7].VDSsat;
	
	return VOUT_plus;

}


double Minimum_Output_Voltage_Calc_CascodedOTA(struct device Mosfets[]){
	
	double VOUT_Minus,VDS6;
	
	VDS6 = 0.4; //Volts (Vdssat4 = 0.3 for IC =16)	
	VOUT_Minus = VSS + VDS6 + Mosfets[9].VDSsat;
		
	return VOUT_Minus;

}


double Power_Consumption_Calc_CascodedOTA(double Ibias){
	double Power_Consumption;
	Power_Consumption = (VDD - VSS) *  ((8*Ibias)/3)*1e6; 
	return Power_Consumption;
}
//--------------------------------------------------------------------------------------



//---------------------------------------------Generate_Randmoms-------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------

void Generate_Randoms(int lowerLength, int upperLength,double lowerIC,double upperIC,int lowerIbias,int upperIbias,struct device Mosfets[],double *Ibias) 
{ 
// Generates and prints 'count' random 
// numbers in range [lower, upper].
    int i; 
    double lowerVp ;
    double upperVp ;
    double StepVp;
    double Vp;
    
    for (i = 0; i < 10; i=i+2) { 
        double num = (rand()%(upperLength - lowerLength + 1)) + lowerLength; 
        num = num*1e-9;
        Mosfets[i].L = num;
        Mosfets[i].lamdaC = Lsat/Mosfets[i].L;
        Mosfets[i+1].L = num;
        Mosfets[i+1].lamdaC = Lsat/Mosfets[i+1].L;
        //printf("%g ",(double) Mosfets[i].L); 
    } 
    
    for (i = 0; i < 10; i=i+2) { 
    //Calculate PinchOff_Voltages from lowerIC,upperIC
    	lowerVp = 2*log(pow(2.71828,(sqrt(lowerIC))) - 1);
    	upperVp = 2*log(pow(2.71828,(sqrt(upperIC))) - 1);
    	StepVp = (upperVp - lowerVp)/1000;
    
		double num = (rand()%(1000 - 0 + 1)) + 0;
		Vp = lowerVp + num*StepVp;
		//Converting Vp to IC
		
		Mosfets[i].IC_WithOutVS = pow(log(1+exp(Vp/2)),2);
		Mosfets[i].IC = Mosfets[i].IC_WithOutVS * ( 1 + Mosfets[i].IC_WithOutVS*pow(Mosfets[i].lamdaC,2) );  // With Velocity Sat IC = IC(1 + IC*lamdaC^2)
    	Mosfets[i+1].IC_WithOutVS = pow(log(1+exp(Vp/2)),2);
    	Mosfets[i+1].IC = Mosfets[i+1].IC_WithOutVS * ( 1 + Mosfets[i+1].IC_WithOutVS*pow(Mosfets[i+1].lamdaC,2) );  // With Velocity Sat IC = IC(1 + IC*lamdaC^2)
    	
	}

    double num = (rand()%(upperIbias - lowerIbias + 1)) + lowerIbias;
	num = num*1e-6;
    *Ibias = num;
} 


void Generate_Randoms_with_different_ICs(int lowerLength, int upperLength,double IC_Ranges_CurrentMirrorOTA[],int lowerIbias,int upperIbias,struct device Mosfets[],double *Ibias) 
{ 
// Generates and prints 'count' random 
// numbers in range [lower, upper].
    int i; 
    double lowerVp ;
    double upperVp ;
    double StepVp;
    double Vp;
    
    for (i = 0; i < 10; i=i+2) { 
        double num = (rand()%(upperLength - lowerLength + 1)) + lowerLength; 
        num = num*1e-9;
        Mosfets[i].L = num;
        Mosfets[i].lamdaC = Lsat/Mosfets[i].L;
        Mosfets[i+1].L = num;
        Mosfets[i+1].lamdaC = Lsat/Mosfets[i+1].L;
        //printf("%g ",(double) Mosfets[i].L); 
    } 
    
    for (i = 0; i < 10; i=i+2) { 
    //Calculate PinchOff_Voltages from lowerIC,upperIC
    	lowerVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CurrentMirrorOTA[i]))) - 1);
    	upperVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CurrentMirrorOTA[i+1]))) - 1);
    	StepVp = (upperVp - lowerVp)/1000;
    
		double num = (rand()%(1000 - 0 + 1)) + 0;
		Vp = lowerVp + num*StepVp;
		//Converting Vp to IC
		
		Mosfets[i].IC_WithOutVS = pow(log(1+exp(Vp/2)),2);
		Mosfets[i].IC = Mosfets[i].IC_WithOutVS * ( 1 + Mosfets[i].IC_WithOutVS*pow(Mosfets[i].lamdaC,2) );  // With Velocity Sat IC = IC(1 + IC*lamdaC^2)
    	Mosfets[i+1].IC_WithOutVS = pow(log(1+exp(Vp/2)),2);
    	Mosfets[i+1].IC = Mosfets[i+1].IC_WithOutVS * ( 1 + Mosfets[i+1].IC_WithOutVS*pow(Mosfets[i+1].lamdaC,2) );  // With Velocity Sat IC = IC(1 + IC*lamdaC^2)
    	
	}

    double num = (rand()%(upperIbias - lowerIbias + 1)) + lowerIbias;
	num = num*1e-6;
    *Ibias = num;
} 


void Generate_Randoms_CascodedOTA(int lowerLength, int upperLength,double lowerIC,double upperIC,int lowerIbias,int upperIbias,struct device Mosfets[],double *Ibias) 
{ 
	//Init Types for CascodedOTA_Mosfets 
	Initialize_TypeDevices_CascodedOTA(Mosfets);
	
    int i; 
    double lowerVp ;
    double upperVp ;
    double StepVp;
    double Vp;
    
    //------------------Initialize M15---------------------------------------
    	//Random Length for M15
        double num = (rand()%(upperLength - lowerLength + 1)) + lowerLength; 
        num = num*1e-9;
        Mosfets[14].L = num;
        Mosfets[14].lamdaC = Lsat/Mosfets[14].L;
        
        //Random IC for M15
    	lowerVp = 2*log(pow(2.71828,(sqrt(lowerIC))) - 1);
    	upperVp = 2*log(pow(2.71828,(sqrt(upperIC))) - 1);
    	StepVp = (upperVp - lowerVp)/1000;
    
		 num = (rand()%(1000 - 0 + 1)) + 0;
		Vp = lowerVp + num*StepVp;
		//Converting Vp to IC
		
		Mosfets[14].IC_WithOutVS = pow(log(1+exp(Vp/2)),2);
		Mosfets[14].IC = Mosfets[14].IC_WithOutVS * ( 1 + Mosfets[14].IC_WithOutVS*pow(Mosfets[14].lamdaC,2) );  // With Velocity Sat IC = IC(1 + IC*lamdaC^2)
    
    //-------------------------------------------------------------------------
    
    for (i = 0; i < 10; i=i+2) { 
        double num = (rand()%(upperLength - lowerLength + 1)) + lowerLength; 
        num = num*1e-9;
        Mosfets[i].L = num;
        Mosfets[i].lamdaC = Lsat/Mosfets[i].L;
        Mosfets[i+1].L = num;
        Mosfets[i+1].lamdaC = Lsat/Mosfets[i+1].L;
        //printf("%g ",(double) Mosfets[i].L); 
    }

	
	for (i = 0; i < 10; i=i+2) { 
    //Calculate PinchOff_Voltages from lowerIC,upperIC
    	lowerVp = 2*log(pow(2.71828,(sqrt(lowerIC))) - 1);
    	upperVp = 2*log(pow(2.71828,(sqrt(upperIC))) - 1);
    	StepVp = (upperVp - lowerVp)/1000;
    
		double num = (rand()%(1000 - 0 + 1)) + 0;
		Vp = lowerVp + num*StepVp;
		//Converting Vp to IC
		
		Mosfets[i].IC_WithOutVS = pow(log(1+exp(Vp/2)),2);
		Mosfets[i].IC = Mosfets[i].IC_WithOutVS * ( 1 + Mosfets[i].IC_WithOutVS*pow(Mosfets[i].lamdaC,2) );  // With Velocity Sat IC = IC(1 + IC*lamdaC^2)
    	Mosfets[i+1].IC_WithOutVS = pow(log(1+exp(Vp/2)),2);
    	Mosfets[i+1].IC = Mosfets[i+1].IC_WithOutVS * ( 1 + Mosfets[i+1].IC_WithOutVS*pow(Mosfets[i+1].lamdaC,2) );  // With Velocity Sat IC = IC(1 + IC*lamdaC^2)
    	
	}
	
	//------------------Initialize M11----------------------------------------
	//M11 = (1/3)M3
		Mosfets[10].L = Mosfets[2].L;
        Mosfets[10].lamdaC = Mosfets[2].lamdaC;
       	Mosfets[10].IC_WithOutVS = Mosfets[2].IC_WithOutVS;
		Mosfets[10].IC = Mosfets[2].IC;
	
	//------------------------------------------------------------------------
	
		
	//------------------Initialize M12---------------------------------------- 
	 //M12 = M7
	 	Mosfets[11].L = Mosfets[6].L;
        Mosfets[11].lamdaC = Mosfets[6].lamdaC;
       	Mosfets[11].IC_WithOutVS = Mosfets[6].IC_WithOutVS;
		Mosfets[11].IC = 	Mosfets[6].IC;
	
	//------------------------------------------------------------------------
	
	
	//------------------Initialize M13-M14------------------------------------
	 //M13 = M14 = (1/4)M15
	 	Mosfets[12].L = Mosfets[14].L;
        Mosfets[12].lamdaC = Mosfets[14].lamdaC;
       	Mosfets[12].IC_WithOutVS = Mosfets[14].IC_WithOutVS;
		Mosfets[12].IC = 	Mosfets[14].IC;
	
		Mosfets[13].L = Mosfets[14].L;
        Mosfets[13].lamdaC = Mosfets[14].lamdaC;
       	Mosfets[13].IC_WithOutVS = Mosfets[14].IC_WithOutVS;
		Mosfets[13].IC = 	Mosfets[14].IC;
	//------------------------------------------------------------------------
	
	//------------------Initialize M16-M17------------------------------------
	 //M16 = M17 = (1/2)M1
	 	Mosfets[15].L = Mosfets[0].L;
        Mosfets[15].lamdaC = Mosfets[0].lamdaC;
       	Mosfets[15].IC_WithOutVS = Mosfets[0].IC_WithOutVS;
		Mosfets[15].IC = 	Mosfets[0].IC;
	
		Mosfets[16].L = Mosfets[0].L;
        Mosfets[16].lamdaC = Mosfets[0].lamdaC;
       	Mosfets[16].IC_WithOutVS = Mosfets[0].IC_WithOutVS;
		Mosfets[16].IC = 	Mosfets[0].IC;
	//------------------------------------------------------------------------
	
	
	
	
	 num = (rand()%(upperIbias - lowerIbias + 1)) + lowerIbias;
	num = num*1e-6;
    *Ibias = num; 
    

}

void Generate_Randoms_CascodedOTA_with_different_ICs(int lowerLength, int upperLength,double IC_Ranges_CascodedOTA[],int lowerIbias,int upperIbias,struct device Mosfets[],double *Ibias) 
{ 
	//Init Types for CascodedOTA_Mosfets 
	Initialize_TypeDevices_CascodedOTA(Mosfets);
	
    int i; 
    double lowerVp ;
    double upperVp ;
    double StepVp;
    double Vp;
    
    //------------------Initialize M15---------------------------------------
    	//Random Length for M15
        double num = (rand()%(upperLength - lowerLength + 1)) + lowerLength; 
        num = num*1e-9;
        Mosfets[14].L = num;
        Mosfets[14].lamdaC = Lsat/Mosfets[14].L;
        
        //Random IC for M15
    	lowerVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CascodedOTA[10]))) - 1);
    	upperVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CascodedOTA[11]))) - 1);
    	StepVp = (upperVp - lowerVp)/1000;
    
		 num = (rand()%(1000 - 0 + 1)) + 0;
		Vp = lowerVp + num*StepVp;
		//Converting Vp to IC
		
		Mosfets[14].IC_WithOutVS = pow(log(1+exp(Vp/2)),2);
		Mosfets[14].IC = Mosfets[14].IC_WithOutVS * ( 1 + Mosfets[14].IC_WithOutVS*pow(Mosfets[14].lamdaC,2) );  // With Velocity Sat IC = IC(1 + IC*lamdaC^2)
    
    //-------------------------------------------------------------------------
    
    for (i = 0; i < 10; i=i+2) { 
        double num = (rand()%(upperLength - lowerLength + 1)) + lowerLength; 
        num = num*1e-9;
        Mosfets[i].L = num;
        Mosfets[i].lamdaC = Lsat/Mosfets[i].L;
        Mosfets[i+1].L = num;
        Mosfets[i+1].lamdaC = Lsat/Mosfets[i+1].L;
        //printf("%g ",(double) Mosfets[i].L); 
    }

	
	for (i = 0; i < 10; i=i+2) { 
    //Calculate PinchOff_Voltages from lowerIC,upperIC
    	lowerVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CascodedOTA[i]))) - 1);
    	upperVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CascodedOTA[i+1]))) - 1);
    	StepVp = (upperVp - lowerVp)/1000;
    
		double num = (rand()%(1000 - 0 + 1)) + 0;
		Vp = lowerVp + num*StepVp;
		//Converting Vp to IC
		
		Mosfets[i].IC_WithOutVS = pow(log(1+exp(Vp/2)),2);
		Mosfets[i].IC = Mosfets[i].IC_WithOutVS * ( 1 + Mosfets[i].IC_WithOutVS*pow(Mosfets[i].lamdaC,2) );  // With Velocity Sat IC = IC(1 + IC*lamdaC^2)
    	Mosfets[i+1].IC_WithOutVS = pow(log(1+exp(Vp/2)),2);
    	Mosfets[i+1].IC = Mosfets[i+1].IC_WithOutVS * ( 1 + Mosfets[i+1].IC_WithOutVS*pow(Mosfets[i+1].lamdaC,2) );  // With Velocity Sat IC = IC(1 + IC*lamdaC^2)
    	
	}
	
	//------------------Initialize M11----------------------------------------
	//M11 = (1/3)M3
		Mosfets[10].L = Mosfets[2].L;
        Mosfets[10].lamdaC = Mosfets[2].lamdaC;
       	Mosfets[10].IC_WithOutVS = Mosfets[2].IC_WithOutVS;
		Mosfets[10].IC = Mosfets[2].IC;
	
	//------------------------------------------------------------------------
	
		
	//------------------Initialize M12---------------------------------------- 
	 //M12 = M7
	 	Mosfets[11].L = Mosfets[6].L;
        Mosfets[11].lamdaC = Mosfets[6].lamdaC;
       	Mosfets[11].IC_WithOutVS = Mosfets[6].IC_WithOutVS;
		Mosfets[11].IC = 	Mosfets[6].IC;
	
	//------------------------------------------------------------------------
	
	
	//------------------Initialize M13-M14------------------------------------
	 //M13 = M14 = (1/4)M15
	 	Mosfets[12].L = Mosfets[14].L;
        Mosfets[12].lamdaC = Mosfets[14].lamdaC;
       	Mosfets[12].IC_WithOutVS = Mosfets[14].IC_WithOutVS;
		Mosfets[12].IC = 	Mosfets[14].IC;
	
		Mosfets[13].L = Mosfets[14].L;
        Mosfets[13].lamdaC = Mosfets[14].lamdaC;
       	Mosfets[13].IC_WithOutVS = Mosfets[14].IC_WithOutVS;
		Mosfets[13].IC = 	Mosfets[14].IC;
	//------------------------------------------------------------------------
	
	//------------------Initialize M16-M17------------------------------------
	 //M16 = M17 = (1/2)M1
	 	Mosfets[15].L = Mosfets[0].L;
        Mosfets[15].lamdaC = Mosfets[0].lamdaC;
       	Mosfets[15].IC_WithOutVS = Mosfets[0].IC_WithOutVS;
		Mosfets[15].IC = 	Mosfets[0].IC;
	
		Mosfets[16].L = Mosfets[0].L;
        Mosfets[16].lamdaC = Mosfets[0].lamdaC;
       	Mosfets[16].IC_WithOutVS = Mosfets[0].IC_WithOutVS;
		Mosfets[16].IC = 	Mosfets[0].IC;
	//------------------------------------------------------------------------
	
	
	
	
	 num = (rand()%(upperIbias - lowerIbias + 1)) + lowerIbias;
	num = num*1e-6;
    *Ibias = num; 
    

}


//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------Initialize---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------
void Initialize_TypeDevices(struct device Mosfets[]){
		int i;
	for(i = 0;i < 10; i=i+2){
		// for nMOS : 
		if( i==0 || i==2 || i==8 ){
			Mosfets[i].n0 = n0_nmos;
			Mosfets[i+1].n0 = n0_nmos;
			
			Mosfets[i].u0 = u0_nmos;
			Mosfets[i+1].u0 = u0_nmos;
			
			Mosfets[i].Io = Io_nmos;//*1e6 ; //Convert Io from A to uA ---not
			Mosfets[i+1].Io = Io_nmos;//*1e6 ; //Convert Io from A to uA ---not
			
			Mosfets[i].KF = KF_nmos;
			Mosfets[i+1].KF = KF_nmos;
			
			Mosfets[i].AF = AF_nmos;
			Mosfets[i+1].AF = AF_nmos;
			
			Mosfets[i].AVTO = AVTO_nmos;
			Mosfets[i+1].AVTO = AVTO_nmos;
			
			Mosfets[i].CJ = CJ_nmos;
			Mosfets[i+1].CJ = CJ_nmos;
			
			Mosfets[i].CJSW = CJSW_nmos;
			Mosfets[i+1].CJSW = CJSW_nmos;
			
			Mosfets[i].VT = VT_nmos;
			Mosfets[i+1].VT = VT_nmos;
			
		}
		// for pMOS:
		if( i==4 || i==6 ){
			Mosfets[i].n0 = n0_pmos;
			Mosfets[i+1].n0 = n0_pmos;
			
			Mosfets[i].u0 = u0_pmos;
			Mosfets[i+1].u0 = u0_pmos;
			
			Mosfets[i].Io = Io_pmos ;  //*1e6 ; //Convert Io from A to uA ---not
			Mosfets[i+1].Io = Io_pmos ; //*1e6 ; //Convert Io from A to uA ---not
			
			Mosfets[i].KF = KF_pmos;
			Mosfets[i+1].KF = KF_pmos;
			
			Mosfets[i].AVTO = AVTO_pmos;
			Mosfets[i+1].AVTO = AVTO_pmos;
			
			Mosfets[i].CJ = CJ_pmos;
			Mosfets[i+1].CJ = CJ_pmos;
			
			Mosfets[i].CJSW = CJSW_pmos;
			Mosfets[i+1].CJSW = CJSW_pmos;
			
			Mosfets[i].VT = VT_pmos;
			Mosfets[i+1].VT = VT_pmos;
			
		}
		
	}
}


void Initialize_TypeDevices_CascodedOTA(struct device Mosfets[]){
	
		int i;
		Mosfets[14].n0 = n0_nmos;
		Mosfets[14].u0 = u0_nmos;
		Mosfets[14].Io = Io_nmos;//*1e6 ; //Convert Io from A to uA ---not	
		Mosfets[14].KF = KF_nmos;
		Mosfets[14].AF = AF_nmos;
		Mosfets[14].AVTO = AVTO_nmos;
		Mosfets[14].CJ = CJ_nmos;
		Mosfets[14].CJSW = CJSW_nmos;
		Mosfets[14].VT = VT_nmos;
			
	for(i = 0;i < 17; i++){
		// for nMOS : 
		
		if( i==0 || i==4 || i==8 || i==12 || i==15 ){
			Mosfets[i].n0 = n0_nmos;
			Mosfets[i+1].n0 = n0_nmos;
			
			Mosfets[i].u0 = u0_nmos;
			Mosfets[i+1].u0 = u0_nmos;
			
			Mosfets[i].Io = Io_nmos;//*1e6 ; //Convert Io from A to uA ---not
			Mosfets[i+1].Io = Io_nmos;//*1e6 ; //Convert Io from A to uA ---not
			
			Mosfets[i].KF = KF_nmos;
			Mosfets[i+1].KF = KF_nmos;
			
			Mosfets[i].AF = AF_nmos;
			Mosfets[i+1].AF = AF_nmos;
			
			Mosfets[i].AVTO = AVTO_nmos;
			Mosfets[i+1].AVTO = AVTO_nmos;
			
			Mosfets[i].CJ = CJ_nmos;
			Mosfets[i+1].CJ = CJ_nmos;
			
			Mosfets[i].CJSW = CJSW_nmos;
			Mosfets[i+1].CJSW = CJSW_nmos;
			
			Mosfets[i].VT = VT_nmos;
			Mosfets[i+1].VT = VT_nmos;
			
		}
		// for pMOS:
		if( i==2 || i==6 || i==10 ){
			Mosfets[i].n0 = n0_pmos;
			Mosfets[i+1].n0 = n0_pmos;
			
			Mosfets[i].u0 = u0_pmos;
			Mosfets[i+1].u0 = u0_pmos;
			
			Mosfets[i].Io = Io_pmos ;  //*1e6 ; //Convert Io from A to uA ---not
			Mosfets[i+1].Io = Io_pmos ; //*1e6 ; //Convert Io from A to uA ---not
			
			Mosfets[i].KF = KF_pmos;
			Mosfets[i+1].KF = KF_pmos;
			
			Mosfets[i].AVTO = AVTO_pmos;
			Mosfets[i+1].AVTO = AVTO_pmos;
			
			Mosfets[i].CJ = CJ_pmos;
			Mosfets[i+1].CJ = CJ_pmos;
			
			Mosfets[i].CJSW = CJSW_pmos;
			Mosfets[i+1].CJSW = CJSW_pmos;
			
			Mosfets[i].VT = VT_pmos;
			Mosfets[i+1].VT = VT_pmos;
			
		}
		
	}


}


//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------Calculate_Mosfets_Parameters=--------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------


void Calculate_Mosfets_Parameters(struct device Mosfets[],double Ibias){

	int i;
	//Calculate W for each mosfet ( W =(L/IC)*(ID/Io) )
	
	// M0-M7 have Ibias
	for(i = 0;i < 8; i++){
		Mosfets[i].W = (Mosfets[i].L/Mosfets[i].IC)*(Ibias/Mosfets[i].Io);
		Mosfets[i].Thermal_noise_factor = ( 1/(1+Mosfets[i].IC) )*(0.5 + 0.6666*Mosfets[i].IC);
		Mosfets[i].gm = Ibias*(1/(Mosfets[i].n0*Ut))*(1/(0.5 + sqrt(0.25 + Mosfets[i].IC)));
		Mosfets[i].VDSsat = 2*Ut* ((sqrt(Mosfets[i].IC + 0.25) + 0.5) + 1);
		
		
	}
	
	// M8-M9 have 2*Ibias
	for(i = 8;i < 10; i++){
		Mosfets[i].W = (Mosfets[i].L/Mosfets[i].IC)*((2*Ibias)/Mosfets[i].Io);
		Mosfets[i].Thermal_noise_factor = ( 1/(1+Mosfets[i].IC) )*(0.5 + 0.6666*Mosfets[i].IC);
		Mosfets[i].gm = 2*Ibias*(1/(Mosfets[i].n0*Ut))*(1/(0.5 + sqrt(0.25 + Mosfets[i].IC)));
	    Mosfets[i].VDSsat = 2*Ut* ((sqrt(Mosfets[i].IC + 0.25) + 0.5) + 1);
	    
	}
	
}


void Calculate_Mosfets_Parameters_CascodedOTA(struct device Mosfets[],double Ibias){
		int i;
		//M0-M1 habe ((Ibias*2)/3)
		Mosfets[0].W = (Mosfets[0].L/Mosfets[0].IC)*(((Ibias*2)/3)/Mosfets[0].Io);
		Mosfets[1].W = (Mosfets[1].L/Mosfets[1].IC)*(((Ibias*2)/3)/Mosfets[1].Io);
		Mosfets[0].Thermal_noise_factor = ( 1/(1+Mosfets[0].IC) )*(0.5 + 0.6666*Mosfets[0].IC);
		Mosfets[1].Thermal_noise_factor = ( 1/(1+Mosfets[1].IC) )*(0.5 + 0.6666*Mosfets[1].IC);
		Mosfets[0].gm = ((Ibias*2)/3)*(1/(Mosfets[0].n0*Ut))*(1/(0.5 + sqrt(0.25 + Mosfets[0].IC)));
		Mosfets[1].gm = ((Ibias*2)/3)*(1/(Mosfets[1].n0*Ut))*(1/(0.5 + sqrt(0.25 + Mosfets[1].IC)));
		Mosfets[0].VDSsat = 2*Ut* ((sqrt(Mosfets[0].IC + 0.25) + 0.5) + 1);
		Mosfets[1].VDSsat = 2*Ut* ((sqrt(Mosfets[1].IC + 0.25) + 0.5) + 1);
		
		//M14 have ((Ibias*4)/3)
		Mosfets[14].W = (Mosfets[14].L/Mosfets[14].IC)*(((Ibias*4)/3)/Mosfets[14].Io);
		Mosfets[14].Thermal_noise_factor = ( 1/(1+Mosfets[14].IC) )*(0.5 + 0.6666*Mosfets[14].IC);
		Mosfets[14].gm = ((Ibias*4)/3)*(1/(Mosfets[14].n0*Ut))*(1/(0.5 + sqrt(0.25 + Mosfets[14].IC)));
		Mosfets[14].VDSsat = 2*Ut* ((sqrt(Mosfets[14].IC + 0.25) + 0.5) + 1);
		
		// M3-M4 have Ibias
		for(i = 2;i < 4; i++){
		Mosfets[i].W = (Mosfets[i].L/Mosfets[i].IC)*(Ibias/Mosfets[i].Io);
		Mosfets[i].Thermal_noise_factor = 	( 1/(1+Mosfets[i].IC) )*(0.5 + 0.6666*Mosfets[i].IC);
		Mosfets[i].gm = Ibias*(1/(Mosfets[i].n0*Ut))*(1/(0.5 + sqrt(0.25 + Mosfets[i].IC)));
		Mosfets[i].VDSsat = 2*Ut* ((sqrt(Mosfets[i].IC + 0.25) + 0.5) + 1);
		}
		
		// M5-M6 and M7-M8 and M9-M10 and M11-M12 and M13-M14  have (Ibias/3)
		for(i = 4;i < 10; i++){
		Mosfets[i].W = (Mosfets[i].L/Mosfets[i].IC)*((Ibias/3)/Mosfets[i].Io);
		Mosfets[i].Thermal_noise_factor = ( 1/(1+Mosfets[i].IC) )*(0.5 + 0.6666*Mosfets[i].IC);
		Mosfets[i].gm = (Ibias/3)*(1/(Mosfets[i].n0*Ut))*(1/(0.5 + sqrt(0.25 + Mosfets[i].IC)));
		Mosfets[i].VDSsat = 2*Ut* ((sqrt(Mosfets[i].IC + 0.25) + 0.5) + 1);
		}
		
		for(i = 10;i < 14; i++){
		Mosfets[i].W = (Mosfets[i].L/Mosfets[i].IC)*((Ibias/3)/Mosfets[i].Io);
		Mosfets[i].Thermal_noise_factor = ( 1/(1+Mosfets[i].IC) )*(0.5 + 0.6666*Mosfets[i].IC);
		Mosfets[i].gm = (Ibias/3)*(1/(Mosfets[i].n0*Ut))*(1/(0.5 + sqrt(0.25 + Mosfets[i].IC)));
		Mosfets[i].VDSsat = 2*Ut* ((sqrt(Mosfets[i].IC + 0.25) + 0.5) + 1);
		}
		
		// M16-M17  have (Ibias/3)
		for(i = 15;i < 17; i++){
		Mosfets[i].W = (Mosfets[i].L/Mosfets[i].IC)*((Ibias/3)/Mosfets[i].Io);
		Mosfets[i].Thermal_noise_factor = ( 1/(1+Mosfets[i].IC) )*(0.5 + 0.6666*Mosfets[i].IC);
		Mosfets[i].gm = (Ibias/3)*(1/(Mosfets[i].n0*Ut))*(1/(0.5 + sqrt(0.25 + Mosfets[i].IC)));
		Mosfets[i].VDSsat = 2*Ut* ((sqrt(Mosfets[i].IC + 0.25) + 0.5) + 1);
		}
		
		
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------Create_new_Generation----------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------

void Create_new_Generation(int IndextFirstParent,int IndexSecondParent,	struct SimpleOTA SimpleOTA_Designs[],int NumberOfChilds,int lowerIbias,int upperIbias,int lowerLength, int upperLength,double lowerIC,double upperIC){
		
	int i,j;
	double *Ibias;
	

	
	for (i=0;i<NumberOfChilds;i++){
		
			
			// the probability to pick a chromosome from a parrent (50% first parent // 49.09% second parent // 0.01% mutation )
			double Propability = (rand()%(100 - 0 + 1)) + 0; 
			double Propability_for_Mutation; 
		//	printf("\n Propability :%lf",Propability);
			
			// Here we birth Ibias for each child
			if(Propability<50){
				SimpleOTA_Designs[i].Ibias = SimpleOTA_Designs[IndextFirstParent].Ibias;
					}
			else if(Propability<=97){
				SimpleOTA_Designs[i].Ibias = SimpleOTA_Designs[IndexSecondParent].Ibias;
			}
			else{
				Propability_for_Mutation = (rand()%(100 - 0 + 1)) + 0;
				
				if(Propability_for_Mutation < 150){
				
				double mutation_Ibias = (rand()%(upperIbias - lowerIbias + 1)) + lowerIbias;
					mutation_Ibias = mutation_Ibias*1e-6;
					SimpleOTA_Designs[i].Ibias = mutation_Ibias;
					
				}
				else{
					SimpleOTA_Designs[i].Ibias = SimpleOTA_Designs[IndexSecondParent].Ibias;
				}
			}
		
			
	
	
			// Here we birth Mosfets (Length and IC) for each child
			int flagForMutation = 0;
			for (j=0;j<9;j=j+2){
				Propability = (rand()%(100 - 0 + 1)) + 0; 
				
				if(Propability<50){
					SimpleOTA_Designs[i].Mosfets[j].L = SimpleOTA_Designs[IndextFirstParent].Mosfets[j].L;
					SimpleOTA_Designs[i].Mosfets[j].lamdaC = SimpleOTA_Designs[IndextFirstParent].Mosfets[j].lamdaC;
					SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS = SimpleOTA_Designs[IndextFirstParent].Mosfets[j].IC_WithOutVS;
					SimpleOTA_Designs[i].Mosfets[j].IC = SimpleOTA_Designs[IndextFirstParent].Mosfets[j].IC;
					
					SimpleOTA_Designs[i].Mosfets[j+1].L = SimpleOTA_Designs[IndextFirstParent].Mosfets[j+1].L;
					SimpleOTA_Designs[i].Mosfets[j+1].lamdaC = SimpleOTA_Designs[IndextFirstParent].Mosfets[j+1].lamdaC;
					SimpleOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = SimpleOTA_Designs[IndextFirstParent].Mosfets[j+1].IC_WithOutVS;
					SimpleOTA_Designs[i].Mosfets[j+1].IC = SimpleOTA_Designs[IndextFirstParent].Mosfets[j+1].IC;
						}
				else if(Propability<=87){
					SimpleOTA_Designs[i].Mosfets[j].L = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].L;
					SimpleOTA_Designs[i].Mosfets[j].lamdaC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].lamdaC;
					SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].IC_WithOutVS;
					SimpleOTA_Designs[i].Mosfets[j].IC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].IC;
					
					SimpleOTA_Designs[i].Mosfets[j+1].L = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].L;
					SimpleOTA_Designs[i].Mosfets[j+1].lamdaC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].lamdaC;
					SimpleOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].IC_WithOutVS;
					SimpleOTA_Designs[i].Mosfets[j+1].IC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].IC;
				}
				else{
					Propability_for_Mutation = (rand()%(100 - 0 + 1)) + 0;
					
					
						
					double mutation_L = (rand()%(upperLength - lowerLength + 1)) + lowerLength; 
					mutation_L = mutation_L*1e-9; //Convert mutation_L from nm to m
					double mutation_IC;// = (rand()%(upperIC - lowerIC + 1)) + lowerIC;					     
					//Calculate PinchOff_Voltages from lowerIC,upperIC
					double lowerVp = 2*log(pow(2.71828,(sqrt(lowerIC)) ) - 1);
					double upperVp = 2*log(pow(2.71828,(sqrt(upperIC))) - 1);
					double StepVp = (upperVp - lowerVp)/1000;
					
					double num = (rand()%(1000 - 0 + 1)) + 0;
					double Vp = lowerVp + num*StepVp;
						//Converting Vp to IC
						mutation_IC = pow(log(1+exp(Vp/2)),2);		
					if(Propability_for_Mutation < 50 && flagForMutation == 0 ){
						SimpleOTA_Designs[i].Mosfets[j].L = mutation_L ;
						SimpleOTA_Designs[i].Mosfets[j].lamdaC = Lsat/mutation_L ;
						SimpleOTA_Designs[i].Mosfets[j].IC = SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS*(1+SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS*pow(SimpleOTA_Designs[i].Mosfets[j].lamdaC,2)) ;
						
						SimpleOTA_Designs[i].Mosfets[j+1].L = mutation_L ;
						SimpleOTA_Designs[i].Mosfets[j+1].lamdaC =  Lsat/mutation_L ;
						SimpleOTA_Designs[i].Mosfets[j+1].IC = SimpleOTA_Designs[i].Mosfets[j+1].IC_WithOutVS*(1+SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS*pow(SimpleOTA_Designs[i].Mosfets[j+1].lamdaC,2)) ;
						flagForMutation = 1;
							
					}
					else if(Propability_for_Mutation < 100 && flagForMutation == 0 ){
						SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS = mutation_IC;
						SimpleOTA_Designs[i].Mosfets[j].IC = mutation_IC*(1+mutation_IC*pow(SimpleOTA_Designs[i].Mosfets[j].lamdaC,2)) ;
						SimpleOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = mutation_IC;
						SimpleOTA_Designs[i].Mosfets[j+1].IC = mutation_IC*(1+mutation_IC*pow(SimpleOTA_Designs[i].Mosfets[j+1].lamdaC,2)) ;
						flagForMutation = 1;
						
					}
					else{
						SimpleOTA_Designs[i].Mosfets[j].L = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].L;
						SimpleOTA_Designs[i].Mosfets[j].lamdaC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].lamdaC;
						SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].IC_WithOutVS;
						SimpleOTA_Designs[i].Mosfets[j].IC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].IC;
						
						SimpleOTA_Designs[i].Mosfets[j+1].L = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].L;
						SimpleOTA_Designs[i].Mosfets[j+1].lamdaC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].lamdaC;
						SimpleOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].IC_WithOutVS;
						SimpleOTA_Designs[i].Mosfets[j+1].IC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].IC;
					}
				}
			
			}
			
	
			
			//calculate Mosfets Parameters For new Child {Calculate_Mosfets_Parameters(struct device Mosfets[],double Ibias)	
			Calculate_Mosfets_Parameters(SimpleOTA_Designs[i].Mosfets,SimpleOTA_Designs[i].Ibias);
		
	
	}
	
}


void Create_new_Generation_with_different_ICs(int IndextFirstParent,int IndexSecondParent,	struct SimpleOTA SimpleOTA_Designs[],int NumberOfChilds,int lowerIbias,int upperIbias,int lowerLength, int upperLength,double IC_Ranges_CurrentMirrorOTA[]){
		
	int i,j;
	double *Ibias;
	

	
	for (i=0;i<NumberOfChilds;i++){
		
			
			// the probability to pick a chromosome from a parrent (50% first parent // 49.09% second parent // 0.01% mutation )
			double Propability = (rand()%(100 - 0 + 1)) + 0; 
			double Propability_for_Mutation; 
		//	printf("\n Propability :%lf",Propability);
			
			// Here we birth Ibias for each child
			if(Propability<50){
				SimpleOTA_Designs[i].Ibias = SimpleOTA_Designs[IndextFirstParent].Ibias;
					}
			else if(Propability<=97){
				SimpleOTA_Designs[i].Ibias = SimpleOTA_Designs[IndexSecondParent].Ibias;
			}
			else{
				Propability_for_Mutation = (rand()%(100 - 0 + 1)) + 0;
				
				if(Propability_for_Mutation < 150){
				
				double mutation_Ibias = (rand()%(upperIbias - lowerIbias + 1)) + lowerIbias;
					mutation_Ibias = mutation_Ibias*1e-6;
					SimpleOTA_Designs[i].Ibias = mutation_Ibias;
					
				}
				else{
					SimpleOTA_Designs[i].Ibias = SimpleOTA_Designs[IndexSecondParent].Ibias;
				}
			}
		
			
	
	
			// Here we birth Mosfets (Length and IC) for each child
			int flagForMutation = 0;
			for (j=0;j<9;j=j+2){
				Propability = (rand()%(100 - 0 + 1)) + 0; 
				
				if(Propability<50){
					SimpleOTA_Designs[i].Mosfets[j].L = SimpleOTA_Designs[IndextFirstParent].Mosfets[j].L;
					SimpleOTA_Designs[i].Mosfets[j].lamdaC = SimpleOTA_Designs[IndextFirstParent].Mosfets[j].lamdaC;
					SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS = SimpleOTA_Designs[IndextFirstParent].Mosfets[j].IC_WithOutVS;
					SimpleOTA_Designs[i].Mosfets[j].IC = SimpleOTA_Designs[IndextFirstParent].Mosfets[j].IC;
					
					SimpleOTA_Designs[i].Mosfets[j+1].L = SimpleOTA_Designs[IndextFirstParent].Mosfets[j+1].L;
					SimpleOTA_Designs[i].Mosfets[j+1].lamdaC = SimpleOTA_Designs[IndextFirstParent].Mosfets[j+1].lamdaC;
					SimpleOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = SimpleOTA_Designs[IndextFirstParent].Mosfets[j+1].IC_WithOutVS;
					SimpleOTA_Designs[i].Mosfets[j+1].IC = SimpleOTA_Designs[IndextFirstParent].Mosfets[j+1].IC;
						}
				else if(Propability<=87){
					SimpleOTA_Designs[i].Mosfets[j].L = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].L;
					SimpleOTA_Designs[i].Mosfets[j].lamdaC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].lamdaC;
					SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].IC_WithOutVS;
					SimpleOTA_Designs[i].Mosfets[j].IC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].IC;
					
					SimpleOTA_Designs[i].Mosfets[j+1].L = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].L;
					SimpleOTA_Designs[i].Mosfets[j+1].lamdaC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].lamdaC;
					SimpleOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].IC_WithOutVS;
					SimpleOTA_Designs[i].Mosfets[j+1].IC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].IC;
				}
				else{
					Propability_for_Mutation = (rand()%(100 - 0 + 1)) + 0;
					
					
						
					double mutation_L = (rand()%(upperLength - lowerLength + 1)) + lowerLength; 
					mutation_L = mutation_L*1e-9; //Convert mutation_L from nm to m
					double mutation_IC;// = (rand()%(upperIC - lowerIC + 1)) + lowerIC;					     
					//Calculate PinchOff_Voltages from lowerIC,upperIC
					double lowerVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CurrentMirrorOTA[j])) ) - 1);
					double upperVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CurrentMirrorOTA[j+1]))) - 1);
					double StepVp = (upperVp - lowerVp)/1000;
					
					double num = (rand()%(1000 - 0 + 1)) + 0;
					double Vp = lowerVp + num*StepVp;
						//Converting Vp to IC
						mutation_IC = pow(log(1+exp(Vp/2)),2);		
					if(Propability_for_Mutation < 50 && flagForMutation == 0 ){
						SimpleOTA_Designs[i].Mosfets[j].L = mutation_L ;
						SimpleOTA_Designs[i].Mosfets[j].lamdaC = Lsat/mutation_L ;
						SimpleOTA_Designs[i].Mosfets[j].IC = SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS*(1+SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS*pow(SimpleOTA_Designs[i].Mosfets[j].lamdaC,2)) ;
						
						SimpleOTA_Designs[i].Mosfets[j+1].L = mutation_L ;
						SimpleOTA_Designs[i].Mosfets[j+1].lamdaC =  Lsat/mutation_L ;
						SimpleOTA_Designs[i].Mosfets[j+1].IC = SimpleOTA_Designs[i].Mosfets[j+1].IC_WithOutVS*(1+SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS*pow(SimpleOTA_Designs[i].Mosfets[j+1].lamdaC,2)) ;
						flagForMutation = 1;
							
					}
					else if(Propability_for_Mutation < 100 && flagForMutation == 0 ){
						SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS = mutation_IC;
						SimpleOTA_Designs[i].Mosfets[j].IC = mutation_IC*(1+mutation_IC*pow(SimpleOTA_Designs[i].Mosfets[j].lamdaC,2)) ;
						SimpleOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = mutation_IC;
						SimpleOTA_Designs[i].Mosfets[j+1].IC = mutation_IC*(1+mutation_IC*pow(SimpleOTA_Designs[i].Mosfets[j+1].lamdaC,2)) ;
						flagForMutation = 1;
						
					}
					else{
						SimpleOTA_Designs[i].Mosfets[j].L = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].L;
						SimpleOTA_Designs[i].Mosfets[j].lamdaC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].lamdaC;
						SimpleOTA_Designs[i].Mosfets[j].IC_WithOutVS = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].IC_WithOutVS;
						SimpleOTA_Designs[i].Mosfets[j].IC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j].IC;
						
						SimpleOTA_Designs[i].Mosfets[j+1].L = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].L;
						SimpleOTA_Designs[i].Mosfets[j+1].lamdaC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].lamdaC;
						SimpleOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].IC_WithOutVS;
						SimpleOTA_Designs[i].Mosfets[j+1].IC = SimpleOTA_Designs[IndexSecondParent].Mosfets[j+1].IC;
					}
				}
			
			}
			
	
			
			//calculate Mosfets Parameters For new Child {Calculate_Mosfets_Parameters(struct device Mosfets[],double Ibias)	
			Calculate_Mosfets_Parameters(SimpleOTA_Designs[i].Mosfets,SimpleOTA_Designs[i].Ibias);
		
	
	}
	
}




void Create_new_Generation_CascodedOTA(int IndextFirstParent,int IndexSecondParent,	struct CascodedOTA CascodedOTA_Designs[],int NumberOfChilds,int lowerIbias,int upperIbias,int lowerLength, int upperLength,double lowerIC,double upperIC){
		
	int i,j;
	double *Ibias;
	

	
	for (i=0;i<NumberOfChilds;i++){
					
			// the probability to pick a chromosome from a parrent (50% first parent // 49.09% second parent // 0.01% mutation )
			double Propability = (rand()%(100 - 0 + 1)) + 0; 
			double Propability_for_Mutation; 
			
			// Here we birth Ibias for each child
			if(Propability<50){
				CascodedOTA_Designs[i].Ibias = CascodedOTA_Designs[IndextFirstParent].Ibias;
					}
			else if(Propability<=97){
				CascodedOTA_Designs[i].Ibias = CascodedOTA_Designs[IndexSecondParent].Ibias;
			}
			else{
				Propability_for_Mutation = (rand()%(100 - 0 + 1)) + 0;
				
				if(Propability_for_Mutation < 150){
				
				double mutation_Ibias = (rand()%(upperIbias - lowerIbias + 1)) + lowerIbias;
					mutation_Ibias = mutation_Ibias*1e-6;
					CascodedOTA_Designs[i].Ibias = mutation_Ibias;
					
				}
				else{
					CascodedOTA_Designs[i].Ibias = CascodedOTA_Designs[IndexSecondParent].Ibias;
				}
			}
		
			
	
	
			// Here we birth Mosfets (Length and IC) for each child
			int flagForMutation = 0;
			for (j=0;j<15;j=j+2){
				if(j==10){
					j=14;
				}
				Propability = (rand()%(100 - 0 + 1)) + 0; 
				
				if(Propability<50){
					CascodedOTA_Designs[i].Mosfets[j].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[j].L;
					CascodedOTA_Designs[i].Mosfets[j].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[j].lamdaC;
					CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[j].IC_WithOutVS;
					CascodedOTA_Designs[i].Mosfets[j].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[j].IC;
					
					CascodedOTA_Designs[i].Mosfets[j+1].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[j+1].L;
					CascodedOTA_Designs[i].Mosfets[j+1].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[j+1].lamdaC;
					CascodedOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[j+1].IC_WithOutVS;
					CascodedOTA_Designs[i].Mosfets[j+1].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[j+1].IC;
					
					if(j==0){
						CascodedOTA_Designs[i].Mosfets[15].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
						CascodedOTA_Designs[i].Mosfets[15].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
						CascodedOTA_Designs[i].Mosfets[15].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[15].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
						
						CascodedOTA_Designs[i].Mosfets[16].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
						CascodedOTA_Designs[i].Mosfets[16].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
						CascodedOTA_Designs[i].Mosfets[16].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[16].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
					}
					else if(j==2){
						CascodedOTA_Designs[i].Mosfets[10].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].L;
						CascodedOTA_Designs[i].Mosfets[10].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].lamdaC;
						CascodedOTA_Designs[i].Mosfets[10].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[10].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC;
					}
					else if(j==6){
						CascodedOTA_Designs[i].Mosfets[11].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].L;
						CascodedOTA_Designs[i].Mosfets[11].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].lamdaC;
						CascodedOTA_Designs[i].Mosfets[11].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[11].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC;
					}
					else if(j==14){
						CascodedOTA_Designs[i].Mosfets[12].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].L;
						CascodedOTA_Designs[i].Mosfets[12].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].lamdaC;
						CascodedOTA_Designs[i].Mosfets[12].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[12].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC;
						
						CascodedOTA_Designs[i].Mosfets[13].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].L;
						CascodedOTA_Designs[i].Mosfets[13].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].lamdaC;
						CascodedOTA_Designs[i].Mosfets[13].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[13].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC;
					}
					
					
						}
				else if(Propability<=87){
					CascodedOTA_Designs[i].Mosfets[j].L = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].L;
					CascodedOTA_Designs[i].Mosfets[j].lamdaC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].lamdaC;
					CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].IC_WithOutVS;
					CascodedOTA_Designs[i].Mosfets[j].IC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].IC;
					
					CascodedOTA_Designs[i].Mosfets[j+1].L = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].L;
					CascodedOTA_Designs[i].Mosfets[j+1].lamdaC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].lamdaC;
					CascodedOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].IC_WithOutVS;
					CascodedOTA_Designs[i].Mosfets[j+1].IC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].IC;
					if(j==0){
						CascodedOTA_Designs[i].Mosfets[15].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
						CascodedOTA_Designs[i].Mosfets[15].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
						CascodedOTA_Designs[i].Mosfets[15].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[15].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
						
						CascodedOTA_Designs[i].Mosfets[16].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
						CascodedOTA_Designs[i].Mosfets[16].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
						CascodedOTA_Designs[i].Mosfets[16].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[16].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
					}
					else if(j==2){
						CascodedOTA_Designs[i].Mosfets[10].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].L;
						CascodedOTA_Designs[i].Mosfets[10].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].lamdaC;
						CascodedOTA_Designs[i].Mosfets[10].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[10].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC;
					}
					else if(j==6){
						CascodedOTA_Designs[i].Mosfets[11].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].L;
						CascodedOTA_Designs[i].Mosfets[11].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].lamdaC;
						CascodedOTA_Designs[i].Mosfets[11].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[11].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC;
					}
					else if(j==14){
						CascodedOTA_Designs[i].Mosfets[12].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].L;
						CascodedOTA_Designs[i].Mosfets[12].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].lamdaC;
						CascodedOTA_Designs[i].Mosfets[12].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[12].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC;
						
						CascodedOTA_Designs[i].Mosfets[13].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].L;
						CascodedOTA_Designs[i].Mosfets[13].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].lamdaC;
						CascodedOTA_Designs[i].Mosfets[13].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[13].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC;
					}
				}
				else{
					Propability_for_Mutation = (rand()%(100 - 0 + 1)) + 0;
						
					double mutation_L = (rand()%(upperLength - lowerLength + 1)) + lowerLength; 
					mutation_L = mutation_L*1e-9; //Convert mutation_L from nm to m
					double mutation_IC;// = (rand()%(upperIC - lowerIC + 1)) + lowerIC;					     
					//Calculate PinchOff_Voltages from lowerIC,upperIC
					double lowerVp = 2*log(pow(2.71828,(sqrt(lowerIC)) ) - 1);
					double upperVp = 2*log(pow(2.71828,(sqrt(upperIC))) - 1);
					double StepVp = (upperVp - lowerVp)/1000;
					
					double num = (rand()%(1000 - 0 + 1)) + 0;
					double Vp = lowerVp + num*StepVp;
						//Converting Vp to IC
						mutation_IC = pow(log(1+exp(Vp/2)),2);		
					if(Propability_for_Mutation < 50 && flagForMutation == 0 ){
						CascodedOTA_Designs[i].Mosfets[j].L = mutation_L ;
						CascodedOTA_Designs[i].Mosfets[j].lamdaC = Lsat/mutation_L ;
						CascodedOTA_Designs[i].Mosfets[j].IC = CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS*(1+CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS*pow(CascodedOTA_Designs[i].Mosfets[j].lamdaC,2)) ;
						
						CascodedOTA_Designs[i].Mosfets[j+1].L = mutation_L ;
						CascodedOTA_Designs[i].Mosfets[j+1].lamdaC =  Lsat/mutation_L ;
						CascodedOTA_Designs[i].Mosfets[j+1].IC = CascodedOTA_Designs[i].Mosfets[j+1].IC_WithOutVS*(1+CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS*pow(CascodedOTA_Designs[i].Mosfets[j+1].lamdaC,2)) ;
						flagForMutation = 1;
						
						if(j==0){
							//M16 = M17 = (1/2)M1
						 	CascodedOTA_Designs[i].Mosfets[15].L = CascodedOTA_Designs[i].Mosfets[0].L;
					        CascodedOTA_Designs[i].Mosfets[15].lamdaC = CascodedOTA_Designs[i].Mosfets[0].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[15].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[0].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[15].IC = CascodedOTA_Designs[i].Mosfets[0].IC;
						
							CascodedOTA_Designs[i].Mosfets[16].L = CascodedOTA_Designs[i].Mosfets[0].L;
					        CascodedOTA_Designs[i].Mosfets[16].lamdaC = CascodedOTA_Designs[i].Mosfets[0].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[16].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[0].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[16].IC = CascodedOTA_Designs[i].Mosfets[0].IC;
						}
						else if(j==2){
							//M11 = (1/3)M3
							CascodedOTA_Designs[i].Mosfets[10].L = CascodedOTA_Designs[i].Mosfets[2].L;
					        CascodedOTA_Designs[i].Mosfets[10].lamdaC = CascodedOTA_Designs[i].Mosfets[2].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[10].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[2].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[10].IC = CascodedOTA_Designs[i].Mosfets[2].IC;
						}
						else if(j==6){
							 //M12 = M7
						 	CascodedOTA_Designs[i].Mosfets[11].L = CascodedOTA_Designs[i].Mosfets[6].L;
					        CascodedOTA_Designs[i].Mosfets[11].lamdaC = CascodedOTA_Designs[i].Mosfets[6].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[11].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[6].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[11].IC = CascodedOTA_Designs[i].Mosfets[6].IC;
						}
						else if(j==14){
								 //M13 = M14 = (1/4)M15
						 	CascodedOTA_Designs[i].Mosfets[12].L = CascodedOTA_Designs[i].Mosfets[14].L;
					        CascodedOTA_Designs[i].Mosfets[12].lamdaC = CascodedOTA_Designs[i].Mosfets[14].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[12].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[14].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[12].IC = CascodedOTA_Designs[i].Mosfets[14].IC;
						
							CascodedOTA_Designs[i].Mosfets[13].L = CascodedOTA_Designs[i].Mosfets[14].L;
					        CascodedOTA_Designs[i].Mosfets[13].lamdaC = CascodedOTA_Designs[i].Mosfets[14].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[13].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[14].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[13].IC = CascodedOTA_Designs[i].Mosfets[14].IC;
	
						}
							
					}
					else if(Propability_for_Mutation < 100 && flagForMutation == 0 ){
						CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS = mutation_IC;
						CascodedOTA_Designs[i].Mosfets[j].IC = mutation_IC*(1+mutation_IC*pow(CascodedOTA_Designs[i].Mosfets[j].lamdaC,2)) ;
						CascodedOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = mutation_IC;
						CascodedOTA_Designs[i].Mosfets[j+1].IC = mutation_IC*(1+mutation_IC*pow(CascodedOTA_Designs[i].Mosfets[j+1].lamdaC,2)) ;
						flagForMutation = 1;
						
						if(j==0){
							//M16 = M17 = (1/2)M1
						 	CascodedOTA_Designs[i].Mosfets[15].L = CascodedOTA_Designs[i].Mosfets[0].L;
					        CascodedOTA_Designs[i].Mosfets[15].lamdaC = CascodedOTA_Designs[i].Mosfets[0].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[15].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[0].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[15].IC = CascodedOTA_Designs[i].Mosfets[0].IC;
						
							CascodedOTA_Designs[i].Mosfets[16].L = CascodedOTA_Designs[i].Mosfets[0].L;
					        CascodedOTA_Designs[i].Mosfets[16].lamdaC = CascodedOTA_Designs[i].Mosfets[0].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[16].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[0].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[16].IC = CascodedOTA_Designs[i].Mosfets[0].IC;
						}
						else if(j==2){
							//M11 = (1/3)M3
							CascodedOTA_Designs[i].Mosfets[10].L = CascodedOTA_Designs[i].Mosfets[2].L;
					        CascodedOTA_Designs[i].Mosfets[10].lamdaC = CascodedOTA_Designs[i].Mosfets[2].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[10].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[2].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[10].IC = CascodedOTA_Designs[i].Mosfets[2].IC;
						}
						else if(j==6){
							 //M12 = M7
						 	CascodedOTA_Designs[i].Mosfets[11].L = CascodedOTA_Designs[i].Mosfets[6].L;
					        CascodedOTA_Designs[i].Mosfets[11].lamdaC = CascodedOTA_Designs[i].Mosfets[6].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[11].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[6].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[11].IC = CascodedOTA_Designs[i].Mosfets[6].IC;
						}
						else if(j==14){
								 //M13 = M14 = (1/4)M15
						 	CascodedOTA_Designs[i].Mosfets[12].L = CascodedOTA_Designs[i].Mosfets[14].L;
					        CascodedOTA_Designs[i].Mosfets[12].lamdaC = CascodedOTA_Designs[i].Mosfets[14].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[12].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[14].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[12].IC = CascodedOTA_Designs[i].Mosfets[14].IC;
						
							CascodedOTA_Designs[i].Mosfets[13].L = CascodedOTA_Designs[i].Mosfets[14].L;
					        CascodedOTA_Designs[i].Mosfets[13].lamdaC = CascodedOTA_Designs[i].Mosfets[14].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[13].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[14].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[13].IC = CascodedOTA_Designs[i].Mosfets[14].IC;
	
						}
						
					}
					else{
						CascodedOTA_Designs[i].Mosfets[j].L = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].L;
						CascodedOTA_Designs[i].Mosfets[j].lamdaC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].lamdaC;
						CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[j].IC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].IC;
						
						CascodedOTA_Designs[i].Mosfets[j+1].L = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].L;
						CascodedOTA_Designs[i].Mosfets[j+1].lamdaC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].lamdaC;
						CascodedOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[j+1].IC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].IC;
						if(j==0){
							CascodedOTA_Designs[i].Mosfets[15].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
							CascodedOTA_Designs[i].Mosfets[15].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
							CascodedOTA_Designs[i].Mosfets[15].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[15].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
							
							CascodedOTA_Designs[i].Mosfets[16].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
							CascodedOTA_Designs[i].Mosfets[16].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
							CascodedOTA_Designs[i].Mosfets[16].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[16].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
						}
						else if(j==2){
							CascodedOTA_Designs[i].Mosfets[10].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].L;
							CascodedOTA_Designs[i].Mosfets[10].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].lamdaC;
							CascodedOTA_Designs[i].Mosfets[10].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[10].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC;
						}
						else if(j==6){
							CascodedOTA_Designs[i].Mosfets[11].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].L;
							CascodedOTA_Designs[i].Mosfets[11].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].lamdaC;
							CascodedOTA_Designs[i].Mosfets[11].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[11].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC;
						}
						else if(j==14){
							CascodedOTA_Designs[i].Mosfets[12].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].L;
							CascodedOTA_Designs[i].Mosfets[12].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].lamdaC;
							CascodedOTA_Designs[i].Mosfets[12].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[12].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC;
							
							CascodedOTA_Designs[i].Mosfets[13].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].L;
							CascodedOTA_Designs[i].Mosfets[13].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].lamdaC;
							CascodedOTA_Designs[i].Mosfets[13].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[13].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC;
						}
					}
				}
			}
			
			//Calculate Mosfets Parameters For new Child {Calculate_Mosfets_Parameters_CascodedOTA(struct device Mosfets[],double Ibias)]
			Calculate_Mosfets_Parameters_CascodedOTA(CascodedOTA_Designs[i].Mosfets,CascodedOTA_Designs[i].Ibias);
		
	
	}
	

}

void Create_new_Generation_CascodedOTA_with_different_ICs(int IndextFirstParent,int IndexSecondParent,	struct CascodedOTA CascodedOTA_Designs[],int NumberOfChilds,int lowerIbias,int upperIbias,int lowerLength, int upperLength,double IC_Ranges_CascodedOTA[]){
		
	int i,j;
	double *Ibias;
	

	
	for (i=0;i<NumberOfChilds;i++){
					
			// the probability to pick a chromosome from a parrent (50% first parent // 49.09% second parent // 0.01% mutation )
			double Propability = (rand()%(100 - 0 + 1)) + 0; 
			double Propability_for_Mutation; 
			
			// Here we birth Ibias for each child
			if(Propability<50){
				CascodedOTA_Designs[i].Ibias = CascodedOTA_Designs[IndextFirstParent].Ibias;
					}
			else if(Propability<=97){
				CascodedOTA_Designs[i].Ibias = CascodedOTA_Designs[IndexSecondParent].Ibias;
			}
			else{
				Propability_for_Mutation = (rand()%(100 - 0 + 1)) + 0;
				
				if(Propability_for_Mutation < 150){
				
				double mutation_Ibias = (rand()%(upperIbias - lowerIbias + 1)) + lowerIbias;
					mutation_Ibias = mutation_Ibias*1e-6;
					CascodedOTA_Designs[i].Ibias = mutation_Ibias;
					
				}
				else{
					CascodedOTA_Designs[i].Ibias = CascodedOTA_Designs[IndexSecondParent].Ibias;
				}
			}
		
			
	
	
			// Here we birth Mosfets (Length and IC) for each child
			int flagForMutation = 0;
			for (j=0;j<15;j=j+2){
				if(j==10){
					j=14;
				}
				Propability = (rand()%(100 - 0 + 1)) + 0; 
				
				if(Propability<50){
					CascodedOTA_Designs[i].Mosfets[j].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[j].L;
					CascodedOTA_Designs[i].Mosfets[j].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[j].lamdaC;
					CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[j].IC_WithOutVS;
					CascodedOTA_Designs[i].Mosfets[j].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[j].IC;
					
					CascodedOTA_Designs[i].Mosfets[j+1].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[j+1].L;
					CascodedOTA_Designs[i].Mosfets[j+1].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[j+1].lamdaC;
					CascodedOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[j+1].IC_WithOutVS;
					CascodedOTA_Designs[i].Mosfets[j+1].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[j+1].IC;
					
					if(j==0){
						CascodedOTA_Designs[i].Mosfets[15].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
						CascodedOTA_Designs[i].Mosfets[15].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
						CascodedOTA_Designs[i].Mosfets[15].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[15].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
						
						CascodedOTA_Designs[i].Mosfets[16].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
						CascodedOTA_Designs[i].Mosfets[16].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
						CascodedOTA_Designs[i].Mosfets[16].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[16].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
					}
					else if(j==2){
						CascodedOTA_Designs[i].Mosfets[10].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].L;
						CascodedOTA_Designs[i].Mosfets[10].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].lamdaC;
						CascodedOTA_Designs[i].Mosfets[10].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[10].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC;
					}
					else if(j==6){
						CascodedOTA_Designs[i].Mosfets[11].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].L;
						CascodedOTA_Designs[i].Mosfets[11].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].lamdaC;
						CascodedOTA_Designs[i].Mosfets[11].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[11].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC;
					}
					else if(j==14){
						CascodedOTA_Designs[i].Mosfets[12].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].L;
						CascodedOTA_Designs[i].Mosfets[12].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].lamdaC;
						CascodedOTA_Designs[i].Mosfets[12].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[12].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC;
						
						CascodedOTA_Designs[i].Mosfets[13].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].L;
						CascodedOTA_Designs[i].Mosfets[13].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].lamdaC;
						CascodedOTA_Designs[i].Mosfets[13].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[13].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC;
					}
					
					
						}
				else if(Propability<=87){
					CascodedOTA_Designs[i].Mosfets[j].L = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].L;
					CascodedOTA_Designs[i].Mosfets[j].lamdaC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].lamdaC;
					CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].IC_WithOutVS;
					CascodedOTA_Designs[i].Mosfets[j].IC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].IC;
					
					CascodedOTA_Designs[i].Mosfets[j+1].L = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].L;
					CascodedOTA_Designs[i].Mosfets[j+1].lamdaC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].lamdaC;
					CascodedOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].IC_WithOutVS;
					CascodedOTA_Designs[i].Mosfets[j+1].IC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].IC;
					if(j==0){
						CascodedOTA_Designs[i].Mosfets[15].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
						CascodedOTA_Designs[i].Mosfets[15].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
						CascodedOTA_Designs[i].Mosfets[15].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[15].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
						
						CascodedOTA_Designs[i].Mosfets[16].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
						CascodedOTA_Designs[i].Mosfets[16].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
						CascodedOTA_Designs[i].Mosfets[16].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[16].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
					}
					else if(j==2){
						CascodedOTA_Designs[i].Mosfets[10].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].L;
						CascodedOTA_Designs[i].Mosfets[10].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].lamdaC;
						CascodedOTA_Designs[i].Mosfets[10].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[10].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC;
					}
					else if(j==6){
						CascodedOTA_Designs[i].Mosfets[11].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].L;
						CascodedOTA_Designs[i].Mosfets[11].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].lamdaC;
						CascodedOTA_Designs[i].Mosfets[11].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[11].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC;
					}
					else if(j==14){
						CascodedOTA_Designs[i].Mosfets[12].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].L;
						CascodedOTA_Designs[i].Mosfets[12].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].lamdaC;
						CascodedOTA_Designs[i].Mosfets[12].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[12].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC;
						
						CascodedOTA_Designs[i].Mosfets[13].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].L;
						CascodedOTA_Designs[i].Mosfets[13].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].lamdaC;
						CascodedOTA_Designs[i].Mosfets[13].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[13].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC;
					}
				}
				else{
					Propability_for_Mutation = (rand()%(100 - 0 + 1)) + 0;
						
					double mutation_L = (rand()%(upperLength - lowerLength + 1)) + lowerLength; 
					mutation_L = mutation_L*1e-9; //Convert mutation_L from nm to m
					double mutation_IC;// = (rand()%(upperIC - lowerIC + 1)) + lowerIC;					     
					//Calculate PinchOff_Voltages from lowerIC,upperIC
					double lowerVp;
					double upperVp;
					if(j!=14){
						lowerVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CascodedOTA[j])) ) - 1);
						upperVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CascodedOTA[j+1]))) - 1);
					}
					else{
						lowerVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CascodedOTA[j-4])) ) - 1);
						upperVp = 2*log(pow(2.71828,(sqrt(IC_Ranges_CascodedOTA[j-3]))) - 1);
					}
					double StepVp = (upperVp - lowerVp)/1000;
					
					double num = (rand()%(1000 - 0 + 1)) + 0;
					double Vp = lowerVp + num*StepVp;
						//Converting Vp to IC
						mutation_IC = pow(log(1+exp(Vp/2)),2);		
					if(Propability_for_Mutation < 50 && flagForMutation == 0 ){
						CascodedOTA_Designs[i].Mosfets[j].L = mutation_L ;
						CascodedOTA_Designs[i].Mosfets[j].lamdaC = Lsat/mutation_L ;
						CascodedOTA_Designs[i].Mosfets[j].IC = CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS*(1+CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS*pow(CascodedOTA_Designs[i].Mosfets[j].lamdaC,2)) ;
						
						CascodedOTA_Designs[i].Mosfets[j+1].L = mutation_L ;
						CascodedOTA_Designs[i].Mosfets[j+1].lamdaC =  Lsat/mutation_L ;
						CascodedOTA_Designs[i].Mosfets[j+1].IC = CascodedOTA_Designs[i].Mosfets[j+1].IC_WithOutVS*(1+CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS*pow(CascodedOTA_Designs[i].Mosfets[j+1].lamdaC,2)) ;
						flagForMutation = 1;
						
						if(j==0){
							//M16 = M17 = (1/2)M1
						 	CascodedOTA_Designs[i].Mosfets[15].L = CascodedOTA_Designs[i].Mosfets[0].L;
					        CascodedOTA_Designs[i].Mosfets[15].lamdaC = CascodedOTA_Designs[i].Mosfets[0].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[15].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[0].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[15].IC = CascodedOTA_Designs[i].Mosfets[0].IC;
						
							CascodedOTA_Designs[i].Mosfets[16].L = CascodedOTA_Designs[i].Mosfets[0].L;
					        CascodedOTA_Designs[i].Mosfets[16].lamdaC = CascodedOTA_Designs[i].Mosfets[0].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[16].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[0].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[16].IC = CascodedOTA_Designs[i].Mosfets[0].IC;
						}
						else if(j==2){
							//M11 = (1/3)M3
							CascodedOTA_Designs[i].Mosfets[10].L = CascodedOTA_Designs[i].Mosfets[2].L;
					        CascodedOTA_Designs[i].Mosfets[10].lamdaC = CascodedOTA_Designs[i].Mosfets[2].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[10].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[2].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[10].IC = CascodedOTA_Designs[i].Mosfets[2].IC;
						}
						else if(j==6){
							 //M12 = M7
						 	CascodedOTA_Designs[i].Mosfets[11].L = CascodedOTA_Designs[i].Mosfets[6].L;
					        CascodedOTA_Designs[i].Mosfets[11].lamdaC = CascodedOTA_Designs[i].Mosfets[6].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[11].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[6].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[11].IC = CascodedOTA_Designs[i].Mosfets[6].IC;
						}
						else if(j==14){
								 //M13 = M14 = (1/4)M15
						 	CascodedOTA_Designs[i].Mosfets[12].L = CascodedOTA_Designs[i].Mosfets[14].L;
					        CascodedOTA_Designs[i].Mosfets[12].lamdaC = CascodedOTA_Designs[i].Mosfets[14].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[12].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[14].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[12].IC = CascodedOTA_Designs[i].Mosfets[14].IC;
						
							CascodedOTA_Designs[i].Mosfets[13].L = CascodedOTA_Designs[i].Mosfets[14].L;
					        CascodedOTA_Designs[i].Mosfets[13].lamdaC = CascodedOTA_Designs[i].Mosfets[14].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[13].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[14].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[13].IC = CascodedOTA_Designs[i].Mosfets[14].IC;
	
						}
							
					}
					else if(Propability_for_Mutation < 100 && flagForMutation == 0 ){
						CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS = mutation_IC;
						CascodedOTA_Designs[i].Mosfets[j].IC = mutation_IC*(1+mutation_IC*pow(CascodedOTA_Designs[i].Mosfets[j].lamdaC,2)) ;
						CascodedOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = mutation_IC;
						CascodedOTA_Designs[i].Mosfets[j+1].IC = mutation_IC*(1+mutation_IC*pow(CascodedOTA_Designs[i].Mosfets[j+1].lamdaC,2)) ;
						flagForMutation = 1;
						
						if(j==0){
							//M16 = M17 = (1/2)M1
						 	CascodedOTA_Designs[i].Mosfets[15].L = CascodedOTA_Designs[i].Mosfets[0].L;
					        CascodedOTA_Designs[i].Mosfets[15].lamdaC = CascodedOTA_Designs[i].Mosfets[0].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[15].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[0].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[15].IC = CascodedOTA_Designs[i].Mosfets[0].IC;
						
							CascodedOTA_Designs[i].Mosfets[16].L = CascodedOTA_Designs[i].Mosfets[0].L;
					        CascodedOTA_Designs[i].Mosfets[16].lamdaC = CascodedOTA_Designs[i].Mosfets[0].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[16].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[0].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[16].IC = CascodedOTA_Designs[i].Mosfets[0].IC;
						}
						else if(j==2){
							//M11 = (1/3)M3
							CascodedOTA_Designs[i].Mosfets[10].L = CascodedOTA_Designs[i].Mosfets[2].L;
					        CascodedOTA_Designs[i].Mosfets[10].lamdaC = CascodedOTA_Designs[i].Mosfets[2].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[10].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[2].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[10].IC = CascodedOTA_Designs[i].Mosfets[2].IC;
						}
						else if(j==6){
							 //M12 = M7
						 	CascodedOTA_Designs[i].Mosfets[11].L = CascodedOTA_Designs[i].Mosfets[6].L;
					        CascodedOTA_Designs[i].Mosfets[11].lamdaC = CascodedOTA_Designs[i].Mosfets[6].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[11].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[6].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[11].IC = CascodedOTA_Designs[i].Mosfets[6].IC;
						}
						else if(j==14){
								 //M13 = M14 = (1/4)M15
						 	CascodedOTA_Designs[i].Mosfets[12].L = CascodedOTA_Designs[i].Mosfets[14].L;
					        CascodedOTA_Designs[i].Mosfets[12].lamdaC = CascodedOTA_Designs[i].Mosfets[14].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[12].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[14].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[12].IC = CascodedOTA_Designs[i].Mosfets[14].IC;
						
							CascodedOTA_Designs[i].Mosfets[13].L = CascodedOTA_Designs[i].Mosfets[14].L;
					        CascodedOTA_Designs[i].Mosfets[13].lamdaC = CascodedOTA_Designs[i].Mosfets[14].lamdaC;
					       	CascodedOTA_Designs[i].Mosfets[13].IC_WithOutVS = CascodedOTA_Designs[i].Mosfets[14].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[13].IC = CascodedOTA_Designs[i].Mosfets[14].IC;
	
						}
						
					}
					else{
						CascodedOTA_Designs[i].Mosfets[j].L = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].L;
						CascodedOTA_Designs[i].Mosfets[j].lamdaC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].lamdaC;
						CascodedOTA_Designs[i].Mosfets[j].IC_WithOutVS = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[j].IC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j].IC;
						
						CascodedOTA_Designs[i].Mosfets[j+1].L = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].L;
						CascodedOTA_Designs[i].Mosfets[j+1].lamdaC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].lamdaC;
						CascodedOTA_Designs[i].Mosfets[j+1].IC_WithOutVS = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].IC_WithOutVS;
						CascodedOTA_Designs[i].Mosfets[j+1].IC = CascodedOTA_Designs[IndexSecondParent].Mosfets[j+1].IC;
						if(j==0){
							CascodedOTA_Designs[i].Mosfets[15].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
							CascodedOTA_Designs[i].Mosfets[15].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
							CascodedOTA_Designs[i].Mosfets[15].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[15].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
							
							CascodedOTA_Designs[i].Mosfets[16].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].L;
							CascodedOTA_Designs[i].Mosfets[16].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].lamdaC;
							CascodedOTA_Designs[i].Mosfets[16].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[16].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[15].IC;
						}
						else if(j==2){
							CascodedOTA_Designs[i].Mosfets[10].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].L;
							CascodedOTA_Designs[i].Mosfets[10].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].lamdaC;
							CascodedOTA_Designs[i].Mosfets[10].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[10].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[10].IC;
						}
						else if(j==6){
							CascodedOTA_Designs[i].Mosfets[11].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].L;
							CascodedOTA_Designs[i].Mosfets[11].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].lamdaC;
							CascodedOTA_Designs[i].Mosfets[11].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[11].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[11].IC;
						}
						else if(j==14){
							CascodedOTA_Designs[i].Mosfets[12].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].L;
							CascodedOTA_Designs[i].Mosfets[12].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].lamdaC;
							CascodedOTA_Designs[i].Mosfets[12].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[12].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[12].IC;
							
							CascodedOTA_Designs[i].Mosfets[13].L = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].L;
							CascodedOTA_Designs[i].Mosfets[13].lamdaC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].lamdaC;
							CascodedOTA_Designs[i].Mosfets[13].IC_WithOutVS = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC_WithOutVS;
							CascodedOTA_Designs[i].Mosfets[13].IC = CascodedOTA_Designs[IndextFirstParent].Mosfets[13].IC;
						}
					}
				}
			}
			
			//Calculate Mosfets Parameters For new Child {Calculate_Mosfets_Parameters_CascodedOTA(struct device Mosfets[],double Ibias)]
			Calculate_Mosfets_Parameters_CascodedOTA(CascodedOTA_Designs[i].Mosfets,CascodedOTA_Designs[i].Ibias);
		
	
	}
	

}


//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------Initialize_data_sheet------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------
struct data_sheet Initialize_data_sheet(struct data_sheet data_sheet){
	
	FILE *f = fopen("Input_data_Sheet.txt","r");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fscanf(f,"%*s %*s [%lf]\n",&(data_sheet.n0_nmos));
	fscanf(f,"%*s %*s [%lf]\n",&(data_sheet.n0_pmos));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.Ut));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.Lsat));
	data_sheet.Lsat = data_sheet.Lsat*1e-9;		//Converting from nm to m 
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.Val_nmos));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.Val_pmos));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.Cox));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.u0_nmos));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.u0_pmos));
	
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.Io_nmos));
	data_sheet.Io_nmos = data_sheet.Io_nmos*1e-9;		//Converting from nA to A 
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.Io_pmos));
	data_sheet.Io_pmos = data_sheet.Io_pmos*1e-9;		//Converting from nA to A 

	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.T));
    data_sheet.k = 1.3806e-23 ; // J/K 
    
    fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.VT_nmos));
    data_sheet.VT_nmos = data_sheet.VT_nmos*1e-3;	//Converting from mV to V 
    fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.VT_pmos));
    data_sheet.VT_pmos = data_sheet.VT_pmos*1e-3;		//Converting from mV to V 

	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.KF_nmos));
	data_sheet.KF_nmos = data_sheet.KF_nmos*1e-25;
	data_sheet.KF_nmos_hand_sqr = 7529 ;
	fscanf(f,"%*s %*s [%lf]\n",&(data_sheet.AF_nmos));
	
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.KF_pmos));
	data_sheet.KF_pmos = data_sheet.KF_pmos*1e-25;
	data_sheet.KF_pmos_hand_sqr = 4347 ;
	fscanf(f,"%*s %*s [%lf]\n",&(data_sheet.AF_pmos));	
	
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.AVTO_nmos));
	data_sheet.AVTO_nmos = data_sheet.AVTO_nmos*1e-3;	//Converting from mV to V 
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.AVTO_pmos));
	data_sheet.AVTO_pmos = data_sheet.AVTO_pmos*1e-3;	//Converting from mV to V 
	
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.CJ_nmos));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.CJ_pmos));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.CJSW_nmos));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.CJSW_pmos));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.Wdif));
	data_sheet.Wdif = data_sheet.Wdif*1e-9;	//Converting from nm to m
	
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.VDD));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.VSS));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.CL));
	data_sheet.CL = data_sheet.CL*1e-12;	//Converting from nm to m
	
	//Powers For FOM
	fscanf(f,"\n%*s\n%*s\n%*s %*s [%lf] %*s\n",&(data_sheet.a0));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.a1));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.a2));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.a3));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.a4));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.a5));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.a6));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.a7));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.a8));
	fscanf(f,"%*s %*s [%lf] %*s\n",&(data_sheet.a9));
	
	int i;
	//IC_Ranges_for_Curent_Mirror_Load_OTA
	fscanf(f,"\n\n%*s\n%*s\n");
	for(i=0;i<9;i=i+2){
	fscanf(f,"%*s %*s [%lf]   %*s %*s [%lf] %*s\n",&(data_sheet.IC_Ranges_CurrentMirrorOTA[i]),&(data_sheet.IC_Ranges_CurrentMirrorOTA[i+1]));	
	}

	//IC_Ranges_for_Cascoded_OTA
	fscanf(f,"\n\n%*s\n%*s\n");
	for(i=0;i<11;i=i+2){
	fscanf(f,"%*s %*s [%lf]   %*s %*s [%lf] %*s\n",&(data_sheet.IC_Ranges_CascodedOTA[i]),&(data_sheet.IC_Ranges_CascodedOTA[i+1]));	
	}
	




	fclose(f);
	return data_sheet;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------Create_txt_data(For Best Design)----------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------

void Create_txt_data (struct SimpleOTA Best_Design){

	FILE *f = fopen("Size_data_Sheet.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	
	int i;
	int k;


	for( i=0 ; i<10; i++){
		
			k =  (Best_Design.Mosfets[i].W)/250e-9;
			if( (k+0.5)*250e-9 > Best_Design.Mosfets[i].W ){		
				fprintf(f,"W%d: %g",i+1,k*250e-9);
			}
			else{
				fprintf(f,"W%d: %g",i+1,(k+1)*250e-9);
			}
			
			
			k =  (Best_Design.Mosfets[i].L)/250e-9;
			if( (k+0.5)*250e-9 > Best_Design.Mosfets[i].L ){		
				fprintf(f," L%d: %g",i+1,k*250e-9);
			}
			else{
				fprintf(f," L%d: %g",i+1,(k+1)*250e-9);
			}

		    k=0;
			
			//Write Gm and VDSsat
			fprintf(f,"    VDSsat%d: %g",i+1,Best_Design.Mosfets[i].VDSsat);
			fprintf(f,"    gm%d: %g",i+1,Best_Design.Mosfets[i].gm);
			fprintf(f,"\n");
		}
	
		fclose(f);
}


void Create_txt_data_CascodedOTA (struct CascodedOTA Best_Design){

	FILE *f = fopen("Size_data_Sheet.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	
	int i;
	int k;


	for( i=0 ; i<17; i++){
		
			k =  (Best_Design.Mosfets[i].W)/250e-9;
			if( (k+0.5)*250e-9 > Best_Design.Mosfets[i].W ){		
				fprintf(f,"W%d: %g",i+1,k*250e-9);
			}
			else{
				fprintf(f,"W%d: %g",i+1,(k+1)*250e-9);
			}
			
			
			k =  (Best_Design.Mosfets[i].L)/250e-9;
			if( (k+0.5)*250e-9 > Best_Design.Mosfets[i].L ){		
				fprintf(f," L%d: %g",i+1,k*250e-9);
			}
			else{
				fprintf(f," L%d: %g",i+1,(k+1)*250e-9);
			}
	
			k=0;
			//Write Gm and VDSsat
			fprintf(f,"    IC%d: %g",i+1,Best_Design.Mosfets[i].IC_WithOutVS);
			fprintf(f,"    VDSsat%d: %g",i+1,Best_Design.Mosfets[i].VDSsat);
			fprintf(f,"    gm%d: %g",i+1,Best_Design.Mosfets[i].gm);
			fprintf(f,"\n");
		}
	
		fclose(f);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------



//--------------------------------------------Create_and_Calculate_txt_data_for_FOMs-----------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------

void Create_and_Calculate_txt_data_for_FOMs(struct SimpleOTA Best_SimpleOTA_Designs[],int Length){
//Calculate Normilize Values for each spec
	//Calculate Means for each spec
	int i;
	double Table_FOMs[Length];
	
	double average_OTA_VoltageGain=0 , average_OTA_FrequencyResponse=0 , average_OTA_Thermal_Noise=0 , average_OTA_Flicker_Noise=0 , average_OTA_Offset_Voltage_input_DueTo_Mismatch=0 , average_OTA_Slew_Rate=0 , average_OTA_Input_Voltage_Range=0 ,  average_OTA_Output_Voltage_Range=0 , average_OTA_PhaseMargin=0 , average_OTA_Power_Consumption=0 ;
	for (i=0 ; i<Length ; i++){
		average_OTA_VoltageGain = average_OTA_VoltageGain + Best_SimpleOTA_Designs[i].OTA_VoltageGain;		
		average_OTA_FrequencyResponse = average_OTA_FrequencyResponse + Best_SimpleOTA_Designs[i].OTA_FrequencyResponse;		
		average_OTA_Thermal_Noise = average_OTA_Thermal_Noise + Best_SimpleOTA_Designs[i].OTA_Thermal_Noise;		
		average_OTA_Flicker_Noise = average_OTA_Flicker_Noise + Best_SimpleOTA_Designs[i].OTA_Flicker_Noise;		
		average_OTA_Offset_Voltage_input_DueTo_Mismatch = average_OTA_Offset_Voltage_input_DueTo_Mismatch + Best_SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch;	
		average_OTA_Slew_Rate = average_OTA_Slew_Rate + Best_SimpleOTA_Designs[i].OTA_Slew_Rate;		
		average_OTA_Input_Voltage_Range = average_OTA_Input_Voltage_Range + (Best_SimpleOTA_Designs[i].OTA_VINCM_Plus-Best_SimpleOTA_Designs[i].OTA_VINCM_Minus);		
		average_OTA_Output_Voltage_Range = average_OTA_Output_Voltage_Range + (Best_SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage-Best_SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage);		
		average_OTA_PhaseMargin = average_OTA_PhaseMargin + Best_SimpleOTA_Designs[i].OTA_PhaseMargin;		
		average_OTA_Power_Consumption = average_OTA_Power_Consumption + Best_SimpleOTA_Designs[i].OTA_Power_Consumption;
	}
	average_OTA_VoltageGain = average_OTA_VoltageGain / Length;
	average_OTA_FrequencyResponse = average_OTA_FrequencyResponse / Length;
	average_OTA_Thermal_Noise = average_OTA_Thermal_Noise / Length;
	average_OTA_Flicker_Noise = average_OTA_Flicker_Noise / Length;
	average_OTA_Offset_Voltage_input_DueTo_Mismatch = average_OTA_Offset_Voltage_input_DueTo_Mismatch / Length;
	average_OTA_Slew_Rate = average_OTA_Slew_Rate / Length;
	average_OTA_Input_Voltage_Range = average_OTA_Input_Voltage_Range / Length;
	average_OTA_Output_Voltage_Range = average_OTA_Output_Voltage_Range / Length;
	average_OTA_PhaseMargin = average_OTA_PhaseMargin / Length;
	average_OTA_Power_Consumption = average_OTA_Power_Consumption / Length;

	double norm_OTA_VoltageGain , norm_OTA_FrequencyResponse , norm_OTA_Thermal_Noise , norm_OTA_Flicker_Noise , norm_OTA_Offset_Voltage_input_DueTo_Mismatch , norm_OTA_Slew_Rate , norm_OTA_Input_Voltage_Range ,  norm_OTA_Output_Voltage_Range , norm_OTA_PhaseMargin , norm_OTA_Power_Consumption;
	for (i=0 ; i<Length ; i++){
		norm_OTA_VoltageGain = Best_SimpleOTA_Designs[i].OTA_VoltageGain / average_OTA_VoltageGain;
		norm_OTA_FrequencyResponse = Best_SimpleOTA_Designs[i].OTA_FrequencyResponse / average_OTA_FrequencyResponse;
		norm_OTA_Thermal_Noise = Best_SimpleOTA_Designs[i].OTA_Thermal_Noise / average_OTA_Thermal_Noise;
		norm_OTA_Flicker_Noise = Best_SimpleOTA_Designs[i].OTA_Flicker_Noise / average_OTA_Flicker_Noise;
		norm_OTA_Offset_Voltage_input_DueTo_Mismatch = Best_SimpleOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch / average_OTA_Offset_Voltage_input_DueTo_Mismatch;
		norm_OTA_Slew_Rate = Best_SimpleOTA_Designs[i].OTA_Slew_Rate / average_OTA_Slew_Rate;
		norm_OTA_Input_Voltage_Range = (Best_SimpleOTA_Designs[i].OTA_VINCM_Plus-Best_SimpleOTA_Designs[i].OTA_VINCM_Minus) / average_OTA_Input_Voltage_Range;
		norm_OTA_Output_Voltage_Range = (Best_SimpleOTA_Designs[i].OTA_Maximun_Output_Voltage-Best_SimpleOTA_Designs[i].OTA_Minimum_Output_Voltage) / average_OTA_Output_Voltage_Range;
		norm_OTA_PhaseMargin = Best_SimpleOTA_Designs[i].OTA_PhaseMargin / average_OTA_PhaseMargin;
		norm_OTA_Power_Consumption = Best_SimpleOTA_Designs[i].OTA_Power_Consumption / average_OTA_Power_Consumption;
		
		//Calculate FOM For each one Of the bests
		Table_FOMs[i]  = ( pow(norm_OTA_VoltageGain,a0_OTA_VoltageGain) * pow(norm_OTA_FrequencyResponse,a1_OTA_FrequencyResponse) * pow(norm_OTA_Slew_Rate,a5_OTA_Slew_Rate) * pow(norm_OTA_Input_Voltage_Range,a6_OTA_Input_Voltage_Range) * pow(norm_OTA_Output_Voltage_Range,a7_OTA_Output_Voltage_Range) *pow(norm_OTA_PhaseMargin,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise,a2_OTA_Thermal_Noise) * pow(norm_OTA_Flicker_Noise,a3_OTA_Flicker_Noise) * pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) * pow(norm_OTA_Power_Consumption,a9_OTA_Power_Consumption)); 
			
	}
	
	//Create txt for matlab
	FILE *f = fopen("FoMs_data_for_Matlab.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	
 	for (i=0 ; i<Length ; i++){
		fprintf(f,"  %g  %g\n",Best_SimpleOTA_Designs[i].Ibias,Table_FOMs[i]);
	}
	
	
	fclose(f);
}


void Create_and_Calculate_txt_data_for_FOMs_CascodedOTA(struct CascodedOTA Best_CascodedOTA_Designs[],int Length){
//Calculate Normilize Values for each spec
	//Calculate Means for each spec
	int i;
	double Table_FOMs[Length];
	
	double average_OTA_VoltageGain=0 , average_OTA_FrequencyResponse=0 , average_OTA_Thermal_Noise=0 , average_OTA_Flicker_Noise=0 , average_OTA_Offset_Voltage_input_DueTo_Mismatch=0 , average_OTA_Slew_Rate=0 , average_OTA_Input_Voltage_Range=0 ,  average_OTA_Output_Voltage_Range=0 , average_OTA_PhaseMargin=0 , average_OTA_Power_Consumption=0 ;
	for (i=0 ; i<Length ; i++){
		average_OTA_VoltageGain = average_OTA_VoltageGain + Best_CascodedOTA_Designs[i].OTA_VoltageGain;		
		average_OTA_FrequencyResponse = average_OTA_FrequencyResponse + Best_CascodedOTA_Designs[i].OTA_FrequencyResponse;		
		average_OTA_Thermal_Noise = average_OTA_Thermal_Noise + Best_CascodedOTA_Designs[i].OTA_Thermal_Noise;		
		average_OTA_Flicker_Noise = average_OTA_Flicker_Noise + Best_CascodedOTA_Designs[i].OTA_Flicker_Noise;		
		average_OTA_Offset_Voltage_input_DueTo_Mismatch = average_OTA_Offset_Voltage_input_DueTo_Mismatch + Best_CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch;	
		average_OTA_Slew_Rate = average_OTA_Slew_Rate + Best_CascodedOTA_Designs[i].OTA_Slew_Rate;		
		average_OTA_Input_Voltage_Range = average_OTA_Input_Voltage_Range + (Best_CascodedOTA_Designs[i].OTA_VINCM_Plus-Best_CascodedOTA_Designs[i].OTA_VINCM_Minus);		
		average_OTA_Output_Voltage_Range = average_OTA_Output_Voltage_Range + (Best_CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage-Best_CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage);		
		average_OTA_PhaseMargin = average_OTA_PhaseMargin + Best_CascodedOTA_Designs[i].OTA_PhaseMargin;		
		average_OTA_Power_Consumption = average_OTA_Power_Consumption + Best_CascodedOTA_Designs[i].OTA_Power_Consumption;
	}
	average_OTA_VoltageGain = average_OTA_VoltageGain / Length;
	average_OTA_FrequencyResponse = average_OTA_FrequencyResponse / Length;
	average_OTA_Thermal_Noise = average_OTA_Thermal_Noise / Length;
	average_OTA_Flicker_Noise = average_OTA_Flicker_Noise / Length;
	average_OTA_Offset_Voltage_input_DueTo_Mismatch = average_OTA_Offset_Voltage_input_DueTo_Mismatch / Length;
	average_OTA_Slew_Rate = average_OTA_Slew_Rate / Length;
	average_OTA_Input_Voltage_Range = average_OTA_Input_Voltage_Range / Length;
	average_OTA_Output_Voltage_Range = average_OTA_Output_Voltage_Range / Length;
	average_OTA_PhaseMargin = average_OTA_PhaseMargin / Length;
	average_OTA_Power_Consumption = average_OTA_Power_Consumption / Length;

	double norm_OTA_VoltageGain , norm_OTA_FrequencyResponse , norm_OTA_Thermal_Noise , norm_OTA_Flicker_Noise , norm_OTA_Offset_Voltage_input_DueTo_Mismatch , norm_OTA_Slew_Rate , norm_OTA_Input_Voltage_Range ,  norm_OTA_Output_Voltage_Range , norm_OTA_PhaseMargin , norm_OTA_Power_Consumption;
	for (i=0 ; i<Length ; i++){
		norm_OTA_VoltageGain = Best_CascodedOTA_Designs[i].OTA_VoltageGain / average_OTA_VoltageGain;
		norm_OTA_FrequencyResponse = Best_CascodedOTA_Designs[i].OTA_FrequencyResponse / average_OTA_FrequencyResponse;
		norm_OTA_Thermal_Noise = Best_CascodedOTA_Designs[i].OTA_Thermal_Noise / average_OTA_Thermal_Noise;
		norm_OTA_Flicker_Noise = Best_CascodedOTA_Designs[i].OTA_Flicker_Noise / average_OTA_Flicker_Noise;
		norm_OTA_Offset_Voltage_input_DueTo_Mismatch = Best_CascodedOTA_Designs[i].OTA_Offset_Voltage_input_DueTo_Mismatch / average_OTA_Offset_Voltage_input_DueTo_Mismatch;
		norm_OTA_Slew_Rate = Best_CascodedOTA_Designs[i].OTA_Slew_Rate / average_OTA_Slew_Rate;
		norm_OTA_Input_Voltage_Range = (Best_CascodedOTA_Designs[i].OTA_VINCM_Plus-Best_CascodedOTA_Designs[i].OTA_VINCM_Minus) / average_OTA_Input_Voltage_Range;
		norm_OTA_Output_Voltage_Range = (Best_CascodedOTA_Designs[i].OTA_Maximun_Output_Voltage-Best_CascodedOTA_Designs[i].OTA_Minimum_Output_Voltage) / average_OTA_Output_Voltage_Range;
		norm_OTA_PhaseMargin = Best_CascodedOTA_Designs[i].OTA_PhaseMargin / average_OTA_PhaseMargin;
		norm_OTA_Power_Consumption = Best_CascodedOTA_Designs[i].OTA_Power_Consumption / average_OTA_Power_Consumption;
		
		//Calculate FOM For each one Of the bests
		Table_FOMs[i]  = ( pow(norm_OTA_VoltageGain,a0_OTA_VoltageGain) * pow(norm_OTA_FrequencyResponse,a1_OTA_FrequencyResponse) * pow(norm_OTA_Slew_Rate,a5_OTA_Slew_Rate) * pow(norm_OTA_Input_Voltage_Range,a6_OTA_Input_Voltage_Range) * pow(norm_OTA_Output_Voltage_Range,a7_OTA_Output_Voltage_Range) *pow(norm_OTA_PhaseMargin,a8_OTA_PhaseMargin) ) / (pow(norm_OTA_Thermal_Noise,a2_OTA_Thermal_Noise) * pow(norm_OTA_Flicker_Noise,a3_OTA_Flicker_Noise) * pow(norm_OTA_Offset_Voltage_input_DueTo_Mismatch,a4_OTA_Offset_Voltage_input_DueTo_Mismatch) * pow(norm_OTA_Power_Consumption,a9_OTA_Power_Consumption)); 
			
	}
	
	//Create txt for matlab
	FILE *f = fopen("FoMs_data_for_Matlab.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	
 	for (i=0 ; i<Length ; i++){
		fprintf(f,"  %g  %g\n",Best_CascodedOTA_Designs[i].Ibias,Table_FOMs[i]);
	}
	
	
	fclose(f);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------










