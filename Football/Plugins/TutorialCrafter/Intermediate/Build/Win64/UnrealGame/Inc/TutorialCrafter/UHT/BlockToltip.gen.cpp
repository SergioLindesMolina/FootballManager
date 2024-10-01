// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TutorialCrafter/Public/UserWidget/BlockMessage/BlockToltip.h"
#include "Runtime/Engine/Classes/Engine/TimerHandle.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBlockToltip() {}

// Begin Cross Module References
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTimerHandle();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UBlockToltip();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UBlockToltip_NoRegister();
UMG_API UClass* Z_Construct_UClass_URichTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UMG_API UEnum* Z_Construct_UEnum_UMG_ESlateVisibility();
UPackage* Z_Construct_UPackage__Script_TutorialCrafter();
// End Cross Module References

// Begin Class UBlockToltip Function OnWidgetBlockedVisibilityChanged
struct Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics
{
	struct BlockToltip_eventOnWidgetBlockedVisibilityChanged_Parms
	{
		ESlateVisibility NewVisibility;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/UserWidget/BlockMessage/BlockToltip.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewVisibility_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewVisibility;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::NewProp_NewVisibility_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::NewProp_NewVisibility = { "NewVisibility", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BlockToltip_eventOnWidgetBlockedVisibilityChanged_Parms, NewVisibility), Z_Construct_UEnum_UMG_ESlateVisibility, METADATA_PARAMS(0, nullptr) }; // 2974316103
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::NewProp_NewVisibility_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::NewProp_NewVisibility,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBlockToltip, nullptr, "OnWidgetBlockedVisibilityChanged", nullptr, nullptr, Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::BlockToltip_eventOnWidgetBlockedVisibilityChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::BlockToltip_eventOnWidgetBlockedVisibilityChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBlockToltip::execOnWidgetBlockedVisibilityChanged)
{
	P_GET_ENUM(ESlateVisibility,Z_Param_NewVisibility);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnWidgetBlockedVisibilityChanged(ESlateVisibility(Z_Param_NewVisibility));
	P_NATIVE_END;
}
// End Class UBlockToltip Function OnWidgetBlockedVisibilityChanged

// Begin Class UBlockToltip
void UBlockToltip::StaticRegisterNativesUBlockToltip()
{
	UClass* Class = UBlockToltip::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnWidgetBlockedVisibilityChanged", &UBlockToltip::execOnWidgetBlockedVisibilityChanged },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBlockToltip);
UClass* Z_Construct_UClass_UBlockToltip_NoRegister()
{
	return UBlockToltip::StaticClass();
}
struct Z_Construct_UClass_UBlockToltip_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "UserWidget/BlockMessage/BlockToltip.h" },
		{ "ModuleRelativePath", "Public/UserWidget/BlockMessage/BlockToltip.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RichTextBlockMessage_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UserWidget/BlockMessage/BlockToltip.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MessageTimer_MetaData[] = {
		{ "ModuleRelativePath", "Public/UserWidget/BlockMessage/BlockToltip.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MessageLifeTime_MetaData[] = {
		{ "Category", "BlockToltip" },
		{ "ModuleRelativePath", "Public/UserWidget/BlockMessage/BlockToltip.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RichTextBlockMessage;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MessageTimer;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MessageLifeTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBlockToltip_OnWidgetBlockedVisibilityChanged, "OnWidgetBlockedVisibilityChanged" }, // 3972488190
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBlockToltip>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBlockToltip_Statics::NewProp_RichTextBlockMessage = { "RichTextBlockMessage", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBlockToltip, RichTextBlockMessage), Z_Construct_UClass_URichTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RichTextBlockMessage_MetaData), NewProp_RichTextBlockMessage_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBlockToltip_Statics::NewProp_MessageTimer = { "MessageTimer", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBlockToltip, MessageTimer), Z_Construct_UScriptStruct_FTimerHandle, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MessageTimer_MetaData), NewProp_MessageTimer_MetaData) }; // 756291145
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UBlockToltip_Statics::NewProp_MessageLifeTime = { "MessageLifeTime", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBlockToltip, MessageLifeTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MessageLifeTime_MetaData), NewProp_MessageLifeTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBlockToltip_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBlockToltip_Statics::NewProp_RichTextBlockMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBlockToltip_Statics::NewProp_MessageTimer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBlockToltip_Statics::NewProp_MessageLifeTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBlockToltip_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBlockToltip_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_TutorialCrafter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBlockToltip_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBlockToltip_Statics::ClassParams = {
	&UBlockToltip::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UBlockToltip_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UBlockToltip_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBlockToltip_Statics::Class_MetaDataParams), Z_Construct_UClass_UBlockToltip_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBlockToltip()
{
	if (!Z_Registration_Info_UClass_UBlockToltip.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBlockToltip.OuterSingleton, Z_Construct_UClass_UBlockToltip_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBlockToltip.OuterSingleton;
}
template<> TUTORIALCRAFTER_API UClass* StaticClass<UBlockToltip>()
{
	return UBlockToltip::StaticClass();
}
UBlockToltip::UBlockToltip(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBlockToltip);
UBlockToltip::~UBlockToltip() {}
// End Class UBlockToltip

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_UserWidget_BlockMessage_BlockToltip_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBlockToltip, UBlockToltip::StaticClass, TEXT("UBlockToltip"), &Z_Registration_Info_UClass_UBlockToltip, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBlockToltip), 1994032634U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_UserWidget_BlockMessage_BlockToltip_h_1909175455(TEXT("/Script/TutorialCrafter"),
	Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_UserWidget_BlockMessage_BlockToltip_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_UserWidget_BlockMessage_BlockToltip_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
