// EnergyPlus::FluidCoolers Unit Tests

// Google Test Headers
#include <gtest/gtest.h>

// EnergyPlus Headers
#include <EnergyPlus/FluidCoolers.hh>
#include <DataSizing.hh>


using namespace EnergyPlus;
using namespace EnergyPlus::FluidCoolers;
using namespace DataGlobals;
using namespace EnergyPlus::DataSizing;
using namespace ObjexxFCL;

TEST( TwoSpeedFluidCoolerInput, Test1 )
{
	using DataSizing::AutoSize;
	int StringArraySize = 20;
	FArray1D_string cNumericFieldNames;
	cNumericFieldNames.allocate( StringArraySize );
	FArray1D_string cAlphaFieldNames;
	cAlphaFieldNames.allocate( StringArraySize );
	FArray1D_string AlphArray;
	AlphArray.allocate( StringArraySize );
	for ( int i = 1; i <= StringArraySize; ++i ){
		cAlphaFieldNames( i ) = "AlphaField";
		cNumericFieldNames( i ) = "NumerField";
		AlphArray( i ) = "FieldValues";
	}
	std::string const cCurrentModuleObject( "FluidCooler:TwoSpeed" );
	int FluidCoolerNum( 1 );
	bool ErrrorsFound( false );
	SimpleFluidCooler.allocate( FluidCoolerNum );

	SimpleFluidCooler( FluidCoolerNum ).Name = "Test";
	SimpleFluidCooler( FluidCoolerNum ).FluidCoolerMassFlowRateMultiplier = 2.5;
	SimpleFluidCooler( FluidCoolerNum ).PerformanceInputMethod_Num = PIM_NominalCapacity;
	SimpleFluidCooler( FluidCoolerNum ).WaterInletNodeNum = 1;
	SimpleFluidCooler( FluidCoolerNum ).WaterOutletNodeNum = 1;
	SimpleFluidCooler( FluidCoolerNum ).FluidCoolerNominalCapacity = 50000;
	SimpleFluidCooler( FluidCoolerNum ).DesignEnteringWaterTemp = 52;
	SimpleFluidCooler( FluidCoolerNum ).DesignEnteringAirTemp = 35;
	SimpleFluidCooler( FluidCoolerNum ).DesignEnteringAirWetBulbTemp = 25;
	SimpleFluidCooler( FluidCoolerNum ).DesignWaterFlowRate = AutoSize;
	SimpleFluidCooler( FluidCoolerNum ).HighSpeedAirFlowRate = AutoSize;
	SimpleFluidCooler( FluidCoolerNum ).HighSpeedFanPower = AutoSize;
	SimpleFluidCooler( FluidCoolerNum ).LowSpeedAirFlowRate = AutoSize;
	SimpleFluidCooler( FluidCoolerNum ).LowSpeedFanPower = AutoSize;
	SimpleFluidCooler( FluidCoolerNum ).FluidCoolerLowSpeedNomCap = 30000;


	AlphArray( 4 ) = "NominalCapacity";
	SimpleFluidCooler( FluidCoolerNum ).HighSpeedFluidCoolerUA = 0;
	SimpleFluidCooler( FluidCoolerNum ).LowSpeedFluidCoolerUA = 0;
	SimpleFluidCooler( 1 ).DesignEnteringWaterTemp = 50;
	bool testResult = TestFluidCoolerTwoSpeedInputForDesign( cCurrentModuleObject, AlphArray, cNumericFieldNames, cAlphaFieldNames, FluidCoolerNum );
	EXPECT_FALSE( testResult ); // no error message triggered

	SimpleFluidCooler( 1 ).DesignEnteringWaterTemp = -10;
	testResult = TestFluidCoolerTwoSpeedInputForDesign( cCurrentModuleObject, AlphArray, cNumericFieldNames, cAlphaFieldNames, FluidCoolerNum );
	EXPECT_TRUE( testResult ); // error message triggered

	SimpleFluidCooler( 1 ).DesignEnteringWaterTemp = 50;
	SimpleFluidCooler( 1 ).FluidCoolerLowSpeedNomCap = AutoSize;
	testResult = TestFluidCoolerTwoSpeedInputForDesign( cCurrentModuleObject, AlphArray, cNumericFieldNames, cAlphaFieldNames, FluidCoolerNum );
	EXPECT_FALSE( testResult ); // no error message triggered

	SimpleFluidCooler( 1 ).FluidCoolerLowSpeedNomCap = 0; // this should trigger the original error condition 
	testResult = TestFluidCoolerTwoSpeedInputForDesign( cCurrentModuleObject, AlphArray, cNumericFieldNames, cAlphaFieldNames, FluidCoolerNum );
	EXPECT_TRUE( testResult ); // error message triggered

}
