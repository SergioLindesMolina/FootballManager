// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TutorialCrafter/Public/TutorialAction.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTutorialAction() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UTutorialAction();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UTutorialAction_NoRegister();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UTutorialValidator_NoRegister();
UPackage* Z_Construct_UPackage__Script_TutorialCrafter();
// End Cross Module References

// Begin Class UTutorialAction Function CheckValidators
struct Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics
{
	struct TutorialAction_eventCheckValidators_Parms
	{
		const UObject* WorldContextObject;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TutorialCrafter|Actions" },
		{ "ModuleRelativePath", "Public/TutorialAction.h" },
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialAction_eventCheckValidators_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldContextObject_MetaData), NewProp_WorldContextObject_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::NewProp_WorldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTutorialAction, nullptr, "CheckValidators", nullptr, nullptr, Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::PropPointers), sizeof(Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::TutorialAction_eventCheckValidators_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::TutorialAction_eventCheckValidators_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTutorialAction_CheckValidators()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTutorialAction_CheckValidators_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTutorialAction::execCheckValidators)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CheckValidators(Z_Param_WorldContextObject);
	P_NATIVE_END;
}
// End Class UTutorialAction Function CheckValidators

// Begin Class UTutorialAction Function Clear
struct Z_Construct_UFunction_UTutorialAction_Clear_Statics
{
	struct TutorialAction_eventClear_Parms
	{
		const UObject* WorldContextObject;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TutorialCrafter|Actions" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*\n\x09* In case that the action gets stopped without finishing , \n\x09* this function will clean all the resources that may have used the action\n\x09* and finish the action\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/TutorialAction.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "* In case that the action gets stopped without finishing ,\n* this function will clean all the resources that may have used the action\n* and finish the action" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UTutorialAction_Clear_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialAction_eventClear_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldContextObject_MetaData), NewProp_WorldContextObject_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTutorialAction_Clear_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTutorialAction_Clear_Statics::NewProp_WorldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialAction_Clear_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTutorialAction_Clear_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTutorialAction, nullptr, "Clear", nullptr, nullptr, Z_Construct_UFunction_UTutorialAction_Clear_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialAction_Clear_Statics::PropPointers), sizeof(Z_Construct_UFunction_UTutorialAction_Clear_Statics::TutorialAction_eventClear_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialAction_Clear_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTutorialAction_Clear_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UTutorialAction_Clear_Statics::TutorialAction_eventClear_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTutorialAction_Clear()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTutorialAction_Clear_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTutorialAction::execClear)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Clear(Z_Param_WorldContextObject);
	P_NATIVE_END;
}
// End Class UTutorialAction Function Clear

// Begin Class UTutorialAction Function Do
struct Z_Construct_UFunction_UTutorialAction_Do_Statics
{
	struct TutorialAction_eventDo_Parms
	{
		const UObject* WorldContextObject;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TutorialCrafter|Actions" },
		{ "ModuleRelativePath", "Public/TutorialAction.h" },
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UTutorialAction_Do_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialAction_eventDo_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldContextObject_MetaData), NewProp_WorldContextObject_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTutorialAction_Do_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTutorialAction_Do_Statics::NewProp_WorldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialAction_Do_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTutorialAction_Do_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTutorialAction, nullptr, "Do", nullptr, nullptr, Z_Construct_UFunction_UTutorialAction_Do_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialAction_Do_Statics::PropPointers), sizeof(Z_Construct_UFunction_UTutorialAction_Do_Statics::TutorialAction_eventDo_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialAction_Do_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTutorialAction_Do_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UTutorialAction_Do_Statics::TutorialAction_eventDo_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTutorialAction_Do()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTutorialAction_Do_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTutorialAction::execDo)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Do(Z_Param_WorldContextObject);
	P_NATIVE_END;
}
// End Class UTutorialAction Function Do

// Begin Class UTutorialAction
void UTutorialAction::StaticRegisterNativesUTutorialAction()
{
	UClass* Class = UTutorialAction::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "CheckValidators", &UTutorialAction::execCheckValidators },
		{ "Clear", &UTutorialAction::execClear },
		{ "Do", &UTutorialAction::execDo },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTutorialAction);
UClass* Z_Construct_UClass_UTutorialAction_NoRegister()
{
	return UTutorialAction::StaticClass();
}
struct Z_Construct_UClass_UTutorialAction_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Base class used to define every action that a tutorial can make, before starting the action all the TutorialValidators must return true\n */" },
#endif
		{ "IncludePath", "TutorialAction.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/TutorialAction.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Base class used to define every action that a tutorial can make, before starting the action all the TutorialValidators must return true" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCompleted_MetaData[] = {
		{ "ModuleRelativePath", "Public/TutorialAction.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bValidatorsCompleted_MetaData[] = {
		{ "ModuleRelativePath", "Public/TutorialAction.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentValidatorIndex_MetaData[] = {
		{ "ModuleRelativePath", "Public/TutorialAction.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Validators_Inner_MetaData[] = {
		{ "Category", "TutorialCrafter|Actions" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TutorialAction.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Validators_MetaData[] = {
		{ "Category", "TutorialCrafter|Actions" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/TutorialAction.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bCompleted_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCompleted;
	static void NewProp_bValidatorsCompleted_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bValidatorsCompleted;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentValidatorIndex;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Validators_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Validators;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UTutorialAction_CheckValidators, "CheckValidators" }, // 2654810087
		{ &Z_Construct_UFunction_UTutorialAction_Clear, "Clear" }, // 3178734417
		{ &Z_Construct_UFunction_UTutorialAction_Do, "Do" }, // 2208603072
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTutorialAction>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
void Z_Construct_UClass_UTutorialAction_Statics::NewProp_bCompleted_SetBit(void* Obj)
{
	((UTutorialAction*)Obj)->bCompleted = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UTutorialAction_Statics::NewProp_bCompleted = { "bCompleted", nullptr, (EPropertyFlags)0x0010000000002000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UTutorialAction), &Z_Construct_UClass_UTutorialAction_Statics::NewProp_bCompleted_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCompleted_MetaData), NewProp_bCompleted_MetaData) };
void Z_Construct_UClass_UTutorialAction_Statics::NewProp_bValidatorsCompleted_SetBit(void* Obj)
{
	((UTutorialAction*)Obj)->bValidatorsCompleted = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UTutorialAction_Statics::NewProp_bValidatorsCompleted = { "bValidatorsCompleted", nullptr, (EPropertyFlags)0x0010000000002000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UTutorialAction), &Z_Construct_UClass_UTutorialAction_Statics::NewProp_bValidatorsCompleted_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bValidatorsCompleted_MetaData), NewProp_bValidatorsCompleted_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UTutorialAction_Statics::NewProp_CurrentValidatorIndex = { "CurrentValidatorIndex", nullptr, (EPropertyFlags)0x0010000000002000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTutorialAction, CurrentValidatorIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentValidatorIndex_MetaData), NewProp_CurrentValidatorIndex_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UTutorialAction_Statics::NewProp_Validators_Inner = { "Validators", nullptr, (EPropertyFlags)0x0002000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTutorialValidator_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Validators_Inner_MetaData), NewProp_Validators_Inner_MetaData) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UTutorialAction_Statics::NewProp_Validators = { "Validators", nullptr, (EPropertyFlags)0x001000800020000d, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTutorialAction, Validators), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Validators_MetaData), NewProp_Validators_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTutorialAction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTutorialAction_Statics::NewProp_bCompleted,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTutorialAction_Statics::NewProp_bValidatorsCompleted,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTutorialAction_Statics::NewProp_CurrentValidatorIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTutorialAction_Statics::NewProp_Validators_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTutorialAction_Statics::NewProp_Validators,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAction_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UTutorialAction_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_TutorialCrafter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAction_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTutorialAction_Statics::ClassParams = {
	&UTutorialAction::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UTutorialAction_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAction_Statics::PropPointers),
	0,
	0x00B010A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialAction_Statics::Class_MetaDataParams), Z_Construct_UClass_UTutorialAction_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UTutorialAction()
{
	if (!Z_Registration_Info_UClass_UTutorialAction.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTutorialAction.OuterSingleton, Z_Construct_UClass_UTutorialAction_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTutorialAction.OuterSingleton;
}
template<> TUTORIALCRAFTER_API UClass* StaticClass<UTutorialAction>()
{
	return UTutorialAction::StaticClass();
}
UTutorialAction::UTutorialAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UTutorialAction);
UTutorialAction::~UTutorialAction() {}
// End Class UTutorialAction

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTutorialAction, UTutorialAction::StaticClass, TEXT("UTutorialAction"), &Z_Registration_Info_UClass_UTutorialAction, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTutorialAction), 2279240938U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_2856953973(TEXT("/Script/TutorialCrafter"),
	Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
