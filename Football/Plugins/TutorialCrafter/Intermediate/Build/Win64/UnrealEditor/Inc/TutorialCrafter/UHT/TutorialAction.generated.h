// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TutorialAction.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
#ifdef TUTORIALCRAFTER_TutorialAction_generated_h
#error "TutorialAction.generated.h already included, missing '#pragma once' in TutorialAction.h"
#endif
#define TUTORIALCRAFTER_TutorialAction_generated_h

#define FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execCheckValidators); \
	DECLARE_FUNCTION(execClear); \
	DECLARE_FUNCTION(execDo);


#define FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUTutorialAction(); \
	friend struct Z_Construct_UClass_UTutorialAction_Statics; \
public: \
	DECLARE_CLASS(UTutorialAction, UObject, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/TutorialCrafter"), NO_API) \
	DECLARE_SERIALIZER(UTutorialAction)


#define FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UTutorialAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UTutorialAction(UTutorialAction&&); \
	UTutorialAction(const UTutorialAction&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UTutorialAction); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UTutorialAction); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UTutorialAction) \
	NO_API virtual ~UTutorialAction();


#define FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_14_PROLOG
#define FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_17_INCLASS_NO_PURE_DECLS \
	FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TUTORIALCRAFTER_API UClass* StaticClass<class UTutorialAction>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialAction_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
