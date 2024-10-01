// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TutorialCrafter/Public/TutorialValidator.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTutorialValidator() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UTutorialValidator();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UTutorialValidator_NoRegister();
UPackage* Z_Construct_UPackage__Script_TutorialCrafter();
// End Cross Module References

// Begin Class UTutorialValidator Function Check
struct Z_Construct_UFunction_UTutorialValidator_Check_Statics
{
	struct TutorialValidator_eventCheck_Parms
	{
		const UObject* WorldContextObject;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TutorialCrafter|Validator" },
		{ "ModuleRelativePath", "Public/TutorialValidator.h" },
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UTutorialValidator_Check_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialValidator_eventCheck_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldContextObject_MetaData), NewProp_WorldContextObject_MetaData) };
void Z_Construct_UFunction_UTutorialValidator_Check_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((TutorialValidator_eventCheck_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UTutorialValidator_Check_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(TutorialValidator_eventCheck_Parms), &Z_Construct_UFunction_UTutorialValidator_Check_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTutorialValidator_Check_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTutorialValidator_Check_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTutorialValidator_Check_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialValidator_Check_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTutorialValidator_Check_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTutorialValidator, nullptr, "Check", nullptr, nullptr, Z_Construct_UFunction_UTutorialValidator_Check_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialValidator_Check_Statics::PropPointers), sizeof(Z_Construct_UFunction_UTutorialValidator_Check_Statics::TutorialValidator_eventCheck_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialValidator_Check_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTutorialValidator_Check_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UTutorialValidator_Check_Statics::TutorialValidator_eventCheck_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTutorialValidator_Check()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTutorialValidator_Check_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTutorialValidator::execCheck)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->Check(Z_Param_WorldContextObject);
	P_NATIVE_END;
}
// End Class UTutorialValidator Function Check

// Begin Class UTutorialValidator
void UTutorialValidator::StaticRegisterNativesUTutorialValidator()
{
	UClass* Class = UTutorialValidator::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Check", &UTutorialValidator::execCheck },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTutorialValidator);
UClass* Z_Construct_UClass_UTutorialValidator_NoRegister()
{
	return UTutorialValidator::StaticClass();
}
struct Z_Construct_UClass_UTutorialValidator_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Base class for the creation of the validators that every TutorialAction can have, the validator only are meant to perform a \n * single check and return true or false, to decide if a TutorialActions should start\n */" },
#endif
		{ "IncludePath", "TutorialValidator.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/TutorialValidator.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Base class for the creation of the validators that every TutorialAction can have, the validator only are meant to perform a\nsingle check and return true or false, to decide if a TutorialActions should start" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UTutorialValidator_Check, "Check" }, // 3510734805
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTutorialValidator>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UTutorialValidator_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_TutorialCrafter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialValidator_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTutorialValidator_Statics::ClassParams = {
	&UTutorialValidator::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x003010A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialValidator_Statics::Class_MetaDataParams), Z_Construct_UClass_UTutorialValidator_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UTutorialValidator()
{
	if (!Z_Registration_Info_UClass_UTutorialValidator.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTutorialValidator.OuterSingleton, Z_Construct_UClass_UTutorialValidator_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTutorialValidator.OuterSingleton;
}
template<> TUTORIALCRAFTER_API UClass* StaticClass<UTutorialValidator>()
{
	return UTutorialValidator::StaticClass();
}
UTutorialValidator::UTutorialValidator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UTutorialValidator);
UTutorialValidator::~UTutorialValidator() {}
// End Class UTutorialValidator

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialValidator_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTutorialValidator, UTutorialValidator::StaticClass, TEXT("UTutorialValidator"), &Z_Registration_Info_UClass_UTutorialValidator, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTutorialValidator), 4131714864U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialValidator_h_2024821128(TEXT("/Script/TutorialCrafter"),
	Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialValidator_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialValidator_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
