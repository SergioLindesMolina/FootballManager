// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TutorialCrafter/Public/TutorialHub.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTutorialHub() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_ATutorialHub();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_ATutorialHub_NoRegister();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UTutorial_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_TutorialCrafter();
// End Cross Module References

// Begin Class ATutorialHub Function Add
struct Z_Construct_UFunction_ATutorialHub_Add_Statics
{
	struct TutorialHub_eventAdd_Parms
	{
		FName Name;
		UTutorial* Tutorial;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TutorialCrafter|CrafterActions" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Add a tutorial object to the current map of tutorials of this actor using the name as the key \n" },
#endif
		{ "ModuleRelativePath", "Public/TutorialHub.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Add a tutorial object to the current map of tutorials of this actor using the name as the key" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_Name;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Tutorial;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_ATutorialHub_Add_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialHub_eventAdd_Parms, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ATutorialHub_Add_Statics::NewProp_Tutorial = { "Tutorial", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialHub_eventAdd_Parms, Tutorial), Z_Construct_UClass_UTutorial_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_ATutorialHub_Add_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((TutorialHub_eventAdd_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ATutorialHub_Add_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(TutorialHub_eventAdd_Parms), &Z_Construct_UFunction_ATutorialHub_Add_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATutorialHub_Add_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATutorialHub_Add_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATutorialHub_Add_Statics::NewProp_Tutorial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATutorialHub_Add_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_Add_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATutorialHub_Add_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATutorialHub, nullptr, "Add", nullptr, nullptr, Z_Construct_UFunction_ATutorialHub_Add_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_Add_Statics::PropPointers), sizeof(Z_Construct_UFunction_ATutorialHub_Add_Statics::TutorialHub_eventAdd_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_Add_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATutorialHub_Add_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ATutorialHub_Add_Statics::TutorialHub_eventAdd_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATutorialHub_Add()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATutorialHub_Add_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATutorialHub::execAdd)
{
	P_GET_PROPERTY_REF(FNameProperty,Z_Param_Out_Name);
	P_GET_OBJECT(UTutorial,Z_Param_Tutorial);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->Add(Z_Param_Out_Name,Z_Param_Tutorial);
	P_NATIVE_END;
}
// End Class ATutorialHub Function Add

// Begin Class ATutorialHub Function ClearPlayingTutorial
struct Z_Construct_UFunction_ATutorialHub_ClearPlayingTutorial_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TutorialCrafter|CrafterActions" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Stop and clears the current playing tutorial\n" },
#endif
		{ "ModuleRelativePath", "Public/TutorialHub.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stop and clears the current playing tutorial" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATutorialHub_ClearPlayingTutorial_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATutorialHub, nullptr, "ClearPlayingTutorial", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_ClearPlayingTutorial_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATutorialHub_ClearPlayingTutorial_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_ATutorialHub_ClearPlayingTutorial()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATutorialHub_ClearPlayingTutorial_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATutorialHub::execClearPlayingTutorial)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClearPlayingTutorial();
	P_NATIVE_END;
}
// End Class ATutorialHub Function ClearPlayingTutorial

// Begin Class ATutorialHub Function OnValidatorWidget
struct TutorialHub_eventOnValidatorWidget_Parms
{
	bool Result;
	UUserWidget* WidgetContainer;
};
static FName NAME_ATutorialHub_OnValidatorWidget = FName(TEXT("OnValidatorWidget"));
void ATutorialHub::OnValidatorWidget(bool Result, UUserWidget* WidgetContainer)
{
	TutorialHub_eventOnValidatorWidget_Parms Parms;
	Parms.Result=Result ? true : false;
	Parms.WidgetContainer=WidgetContainer;
	ProcessEvent(FindFunctionChecked(NAME_ATutorialHub_OnValidatorWidget),&Parms);
}
struct Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/TutorialHub.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WidgetContainer_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static void NewProp_Result_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_Result;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WidgetContainer;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::NewProp_Result_SetBit(void* Obj)
{
	((TutorialHub_eventOnValidatorWidget_Parms*)Obj)->Result = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::NewProp_Result = { "Result", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(TutorialHub_eventOnValidatorWidget_Parms), &Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::NewProp_Result_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::NewProp_WidgetContainer = { "WidgetContainer", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialHub_eventOnValidatorWidget_Parms, WidgetContainer), Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WidgetContainer_MetaData), NewProp_WidgetContainer_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::NewProp_Result,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::NewProp_WidgetContainer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATutorialHub, nullptr, "OnValidatorWidget", nullptr, nullptr, Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::PropPointers), sizeof(TutorialHub_eventOnValidatorWidget_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::Function_MetaDataParams) };
static_assert(sizeof(TutorialHub_eventOnValidatorWidget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATutorialHub_OnValidatorWidget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATutorialHub_OnValidatorWidget_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class ATutorialHub Function OnValidatorWidget

// Begin Class ATutorialHub Function Play
struct Z_Construct_UFunction_ATutorialHub_Play_Statics
{
	struct TutorialHub_eventPlay_Parms
	{
		FName Name;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TutorialCrafter|CrafterActions" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Tries to play a tutorial from the map of tutorials of this actor\n" },
#endif
		{ "ModuleRelativePath", "Public/TutorialHub.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tries to play a tutorial from the map of tutorials of this actor" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_Name;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_ATutorialHub_Play_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialHub_eventPlay_Parms, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
void Z_Construct_UFunction_ATutorialHub_Play_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((TutorialHub_eventPlay_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ATutorialHub_Play_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(TutorialHub_eventPlay_Parms), &Z_Construct_UFunction_ATutorialHub_Play_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATutorialHub_Play_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATutorialHub_Play_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATutorialHub_Play_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_Play_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATutorialHub_Play_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATutorialHub, nullptr, "Play", nullptr, nullptr, Z_Construct_UFunction_ATutorialHub_Play_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_Play_Statics::PropPointers), sizeof(Z_Construct_UFunction_ATutorialHub_Play_Statics::TutorialHub_eventPlay_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_Play_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATutorialHub_Play_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ATutorialHub_Play_Statics::TutorialHub_eventPlay_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATutorialHub_Play()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATutorialHub_Play_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATutorialHub::execPlay)
{
	P_GET_PROPERTY_REF(FNameProperty,Z_Param_Out_Name);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->Play(Z_Param_Out_Name);
	P_NATIVE_END;
}
// End Class ATutorialHub Function Play

// Begin Class ATutorialHub Function Remove
struct Z_Construct_UFunction_ATutorialHub_Remove_Statics
{
	struct TutorialHub_eventRemove_Parms
	{
		FName Name;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TutorialCrafter|CrafterActions" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Remove a tutorial object of the current map of tutorials of this actor\n" },
#endif
		{ "ModuleRelativePath", "Public/TutorialHub.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Remove a tutorial object of the current map of tutorials of this actor" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_Name;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_ATutorialHub_Remove_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialHub_eventRemove_Parms, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
void Z_Construct_UFunction_ATutorialHub_Remove_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((TutorialHub_eventRemove_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ATutorialHub_Remove_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(TutorialHub_eventRemove_Parms), &Z_Construct_UFunction_ATutorialHub_Remove_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATutorialHub_Remove_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATutorialHub_Remove_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATutorialHub_Remove_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_Remove_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATutorialHub_Remove_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATutorialHub, nullptr, "Remove", nullptr, nullptr, Z_Construct_UFunction_ATutorialHub_Remove_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_Remove_Statics::PropPointers), sizeof(Z_Construct_UFunction_ATutorialHub_Remove_Statics::TutorialHub_eventRemove_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATutorialHub_Remove_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATutorialHub_Remove_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ATutorialHub_Remove_Statics::TutorialHub_eventRemove_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ATutorialHub_Remove()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATutorialHub_Remove_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ATutorialHub::execRemove)
{
	P_GET_PROPERTY_REF(FNameProperty,Z_Param_Out_Name);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->Remove(Z_Param_Out_Name);
	P_NATIVE_END;
}
// End Class ATutorialHub Function Remove

// Begin Class ATutorialHub
void ATutorialHub::StaticRegisterNativesATutorialHub()
{
	UClass* Class = ATutorialHub::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Add", &ATutorialHub::execAdd },
		{ "ClearPlayingTutorial", &ATutorialHub::execClearPlayingTutorial },
		{ "Play", &ATutorialHub::execPlay },
		{ "Remove", &ATutorialHub::execRemove },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATutorialHub);
UClass* Z_Construct_UClass_ATutorialHub_NoRegister()
{
	return ATutorialHub::StaticClass();
}
struct Z_Construct_UClass_ATutorialHub_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*\n* Level Actor that manage all the tutorials in a given map, the tutorials are duplicated at runtime to ensure that the modifications are temporary\n*/" },
#endif
		{ "IncludePath", "TutorialHub.h" },
		{ "ModuleRelativePath", "Public/TutorialHub.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "* Level Actor that manage all the tutorials in a given map, the tutorials are duplicated at runtime to ensure that the modifications are temporary" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tutorials_MetaData[] = {
		{ "ModuleRelativePath", "Public/TutorialHub.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayingTutorial_MetaData[] = {
		{ "Category", "TutorialCrafter|CrafterHub" },
		{ "ModuleRelativePath", "Public/TutorialHub.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Tutorials_ValueProp;
	static const UECodeGen_Private::FNamePropertyParams NewProp_Tutorials_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_Tutorials;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayingTutorial;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ATutorialHub_Add, "Add" }, // 2647904593
		{ &Z_Construct_UFunction_ATutorialHub_ClearPlayingTutorial, "ClearPlayingTutorial" }, // 4055857923
		{ &Z_Construct_UFunction_ATutorialHub_OnValidatorWidget, "OnValidatorWidget" }, // 478654041
		{ &Z_Construct_UFunction_ATutorialHub_Play, "Play" }, // 3235625835
		{ &Z_Construct_UFunction_ATutorialHub_Remove, "Remove" }, // 1705736746
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATutorialHub>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATutorialHub_Statics::NewProp_Tutorials_ValueProp = { "Tutorials", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UClass_UTutorial_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_ATutorialHub_Statics::NewProp_Tutorials_Key_KeyProp = { "Tutorials_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_ATutorialHub_Statics::NewProp_Tutorials = { "Tutorials", nullptr, (EPropertyFlags)0x0020080000002000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialHub, Tutorials), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tutorials_MetaData), NewProp_Tutorials_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATutorialHub_Statics::NewProp_PlayingTutorial = { "PlayingTutorial", nullptr, (EPropertyFlags)0x0020080000000004, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATutorialHub, PlayingTutorial), Z_Construct_UClass_UTutorial_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayingTutorial_MetaData), NewProp_PlayingTutorial_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATutorialHub_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialHub_Statics::NewProp_Tutorials_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialHub_Statics::NewProp_Tutorials_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialHub_Statics::NewProp_Tutorials,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATutorialHub_Statics::NewProp_PlayingTutorial,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialHub_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ATutorialHub_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TutorialCrafter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialHub_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ATutorialHub_Statics::ClassParams = {
	&ATutorialHub::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ATutorialHub_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialHub_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATutorialHub_Statics::Class_MetaDataParams), Z_Construct_UClass_ATutorialHub_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ATutorialHub()
{
	if (!Z_Registration_Info_UClass_ATutorialHub.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATutorialHub.OuterSingleton, Z_Construct_UClass_ATutorialHub_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATutorialHub.OuterSingleton;
}
template<> TUTORIALCRAFTER_API UClass* StaticClass<ATutorialHub>()
{
	return ATutorialHub::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ATutorialHub);
ATutorialHub::~ATutorialHub() {}
// End Class ATutorialHub

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATutorialHub, ATutorialHub::StaticClass, TEXT("ATutorialHub"), &Z_Registration_Info_UClass_ATutorialHub, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATutorialHub), 1626528287U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_79249907(TEXT("/Script/TutorialCrafter"),
	Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
