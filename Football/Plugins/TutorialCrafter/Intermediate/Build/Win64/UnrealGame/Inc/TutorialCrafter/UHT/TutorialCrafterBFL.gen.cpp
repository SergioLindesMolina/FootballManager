// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TutorialCrafter/Public/TutorialCrafterBFL.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTutorialCrafterBFL() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UBlockToltip_NoRegister();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UTutorialCrafterBFL();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UTutorialCrafterBFL_NoRegister();
UMG_API UClass* Z_Construct_UClass_UWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_TutorialCrafter();
// End Cross Module References

// Begin Class UTutorialCrafterBFL Function DisplayBlockMessage
struct Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics
{
	struct TutorialCrafterBFL_eventDisplayBlockMessage_Parms
	{
		const UObject* WorldContextObject;
		UWidget* BlockedWidget;
		FText Message;
		TSubclassOf<UBlockToltip> BlockToltipClass;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/TutorialCrafterBFL.h" },
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlockedWidget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BlockedWidget;
	static const UECodeGen_Private::FTextPropertyParams NewProp_Message;
	static const UECodeGen_Private::FClassPropertyParams NewProp_BlockToltipClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialCrafterBFL_eventDisplayBlockMessage_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldContextObject_MetaData), NewProp_WorldContextObject_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::NewProp_BlockedWidget = { "BlockedWidget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialCrafterBFL_eventDisplayBlockMessage_Parms, BlockedWidget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlockedWidget_MetaData), NewProp_BlockedWidget_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialCrafterBFL_eventDisplayBlockMessage_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::NewProp_BlockToltipClass = { "BlockToltipClass", nullptr, (EPropertyFlags)0x0014000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TutorialCrafterBFL_eventDisplayBlockMessage_Parms, BlockToltipClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UBlockToltip_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::NewProp_BlockedWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::NewProp_Message,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::NewProp_BlockToltipClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTutorialCrafterBFL, nullptr, "DisplayBlockMessage", nullptr, nullptr, Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::PropPointers), sizeof(Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::TutorialCrafterBFL_eventDisplayBlockMessage_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::TutorialCrafterBFL_eventDisplayBlockMessage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTutorialCrafterBFL::execDisplayBlockMessage)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_OBJECT(UWidget,Z_Param_BlockedWidget);
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_Message);
	P_GET_OBJECT(UClass,Z_Param_BlockToltipClass);
	P_FINISH;
	P_NATIVE_BEGIN;
	UTutorialCrafterBFL::DisplayBlockMessage(Z_Param_WorldContextObject,Z_Param_BlockedWidget,Z_Param_Out_Message,Z_Param_BlockToltipClass);
	P_NATIVE_END;
}
// End Class UTutorialCrafterBFL Function DisplayBlockMessage

// Begin Class UTutorialCrafterBFL Function HideBlockMessage
struct Z_Construct_UFunction_UTutorialCrafterBFL_HideBlockMessage_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/TutorialCrafterBFL.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTutorialCrafterBFL_HideBlockMessage_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTutorialCrafterBFL, nullptr, "HideBlockMessage", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTutorialCrafterBFL_HideBlockMessage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTutorialCrafterBFL_HideBlockMessage_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UTutorialCrafterBFL_HideBlockMessage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTutorialCrafterBFL_HideBlockMessage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UTutorialCrafterBFL::execHideBlockMessage)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	UTutorialCrafterBFL::HideBlockMessage();
	P_NATIVE_END;
}
// End Class UTutorialCrafterBFL Function HideBlockMessage

// Begin Class UTutorialCrafterBFL
void UTutorialCrafterBFL::StaticRegisterNativesUTutorialCrafterBFL()
{
	UClass* Class = UTutorialCrafterBFL::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "DisplayBlockMessage", &UTutorialCrafterBFL::execDisplayBlockMessage },
		{ "HideBlockMessage", &UTutorialCrafterBFL::execHideBlockMessage },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTutorialCrafterBFL);
UClass* Z_Construct_UClass_UTutorialCrafterBFL_NoRegister()
{
	return UTutorialCrafterBFL::StaticClass();
}
struct Z_Construct_UClass_UTutorialCrafterBFL_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "TutorialCrafterBFL.h" },
		{ "ModuleRelativePath", "Public/TutorialCrafterBFL.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UTutorialCrafterBFL_DisplayBlockMessage, "DisplayBlockMessage" }, // 327896812
		{ &Z_Construct_UFunction_UTutorialCrafterBFL_HideBlockMessage, "HideBlockMessage" }, // 2011965222
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTutorialCrafterBFL>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UTutorialCrafterBFL_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_TutorialCrafter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialCrafterBFL_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTutorialCrafterBFL_Statics::ClassParams = {
	&UTutorialCrafterBFL::StaticClass,
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
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorialCrafterBFL_Statics::Class_MetaDataParams), Z_Construct_UClass_UTutorialCrafterBFL_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UTutorialCrafterBFL()
{
	if (!Z_Registration_Info_UClass_UTutorialCrafterBFL.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTutorialCrafterBFL.OuterSingleton, Z_Construct_UClass_UTutorialCrafterBFL_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTutorialCrafterBFL.OuterSingleton;
}
template<> TUTORIALCRAFTER_API UClass* StaticClass<UTutorialCrafterBFL>()
{
	return UTutorialCrafterBFL::StaticClass();
}
UTutorialCrafterBFL::UTutorialCrafterBFL(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UTutorialCrafterBFL);
UTutorialCrafterBFL::~UTutorialCrafterBFL() {}
// End Class UTutorialCrafterBFL

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialCrafterBFL_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTutorialCrafterBFL, UTutorialCrafterBFL::StaticClass, TEXT("UTutorialCrafterBFL"), &Z_Registration_Info_UClass_UTutorialCrafterBFL, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTutorialCrafterBFL), 4163578443U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialCrafterBFL_h_3134974771(TEXT("/Script/TutorialCrafter"),
	Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialCrafterBFL_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialCrafterBFL_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
