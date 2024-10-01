// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TutorialHub.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UTutorial;
class UUserWidget;
#ifdef TUTORIALCRAFTER_TutorialHub_generated_h
#error "TutorialHub.generated.h already included, missing '#pragma once' in TutorialHub.h"
#endif
#define TUTORIALCRAFTER_TutorialHub_generated_h

#define FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execClearPlayingTutorial); \
	DECLARE_FUNCTION(execPlay); \
	DECLARE_FUNCTION(execRemove); \
	DECLARE_FUNCTION(execAdd);


#define FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_19_CALLBACK_WRAPPERS
#define FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATutorialHub(); \
	friend struct Z_Construct_UClass_ATutorialHub_Statics; \
public: \
	DECLARE_CLASS(ATutorialHub, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TutorialCrafter"), NO_API) \
	DECLARE_SERIALIZER(ATutorialHub)


#define FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_19_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ATutorialHub(ATutorialHub&&); \
	ATutorialHub(const ATutorialHub&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATutorialHub); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATutorialHub); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATutorialHub) \
	NO_API virtual ~ATutorialHub();


#define FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_16_PROLOG
#define FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_19_CALLBACK_WRAPPERS \
	FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_19_INCLASS_NO_PURE_DECLS \
	FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TUTORIALCRAFTER_API UClass* StaticClass<class ATutorialHub>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_smlin_Documents_NimbleProjects_Football_Plugins_TutorialCrafter_Source_TutorialCrafter_Public_TutorialHub_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
