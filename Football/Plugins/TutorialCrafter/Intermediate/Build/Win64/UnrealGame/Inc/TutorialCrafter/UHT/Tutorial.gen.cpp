// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TutorialCrafter/Public/Tutorial.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTutorial() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UTutorial();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UTutorial_NoRegister();
TUTORIALCRAFTER_API UClass* Z_Construct_UClass_UTutorialAction_NoRegister();
UPackage* Z_Construct_UPackage__Script_TutorialCrafter();
// End Cross Module References

// Begin Class UTutorial
void UTutorial::StaticRegisterNativesUTutorial()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTutorial);
UClass* Z_Construct_UClass_UTutorial_NoRegister()
{
	return UTutorial::StaticClass();
}
struct Z_Construct_UClass_UTutorial_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Class that contains all the actions necessary to complete a tutorial, this asset will be copied before runtime usage to avoid the permanent modification of \n * properties inside every TutorialAction\n */" },
#endif
		{ "IncludePath", "Tutorial.h" },
		{ "ModuleRelativePath", "Public/Tutorial.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Class that contains all the actions necessary to complete a tutorial, this asset will be copied before runtime usage to avoid the permanent modification of\nproperties inside every TutorialAction" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Actions_Inner_MetaData[] = {
		{ "Category", "TutorialCrafter|Tutorial" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*\n\x09* TODO Sergio Find if is possible to divide each tutorial action and validator between data and functionality to avoid the duplication of necessary data\n\x09*/" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Tutorial.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "* TODO Sergio Find if is possible to divide each tutorial action and validator between data and functionality to avoid the duplication of necessary data" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Actions_MetaData[] = {
		{ "Category", "TutorialCrafter|Tutorial" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*\n\x09* TODO Sergio Find if is possible to divide each tutorial action and validator between data and functionality to avoid the duplication of necessary data\n\x09*/" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Tutorial.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "* TODO Sergio Find if is possible to divide each tutorial action and validator between data and functionality to avoid the duplication of necessary data" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Actions_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Actions;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTutorial>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UTutorial_Statics::NewProp_Actions_Inner = { "Actions", nullptr, (EPropertyFlags)0x0002000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTutorialAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Actions_Inner_MetaData), NewProp_Actions_Inner_MetaData) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UTutorial_Statics::NewProp_Actions = { "Actions", nullptr, (EPropertyFlags)0x001000800020000d, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTutorial, Actions), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Actions_MetaData), NewProp_Actions_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTutorial_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTutorial_Statics::NewProp_Actions_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTutorial_Statics::NewProp_Actions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorial_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UTutorial_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_TutorialCrafter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorial_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTutorial_Statics::ClassParams = {
	&UTutorial::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UTutorial_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UTutorial_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTutorial_Statics::Class_MetaDataParams), Z_Construct_UClass_UTutorial_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UTutorial()
{
	if (!Z_Registration_Info_UClass_UTutorial.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTutorial.OuterSingleton, Z_Construct_UClass_UTutorial_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTutorial.OuterSingleton;
}
template<> TUTORIALCRAFTER_API UClass* StaticClass<UTutorial>()
{
	return UTutorial::StaticClass();
}
UTutorial::UTutorial(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UTutorial);
UTutorial::~UTutorial() {}
// End Class UTutorial

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_Tutorial_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTutorial, UTutorial::StaticClass, TEXT("UTutorial"), &Z_Registration_Info_UClass_UTutorial, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTutorial), 2957711281U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_Tutorial_h_2031622247(TEXT("/Script/TutorialCrafter"),
	Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_Tutorial_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_Tutorial_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
