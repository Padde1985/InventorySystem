// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Interaction/Inv_HighlightableInterface.h"

#ifdef INVENTORY_Inv_HighlightableInterface_generated_h
#error "Inv_HighlightableInterface.generated.h already included, missing '#pragma once' in Inv_HighlightableInterface.h"
#endif
#define INVENTORY_Inv_HighlightableInterface_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Interface UInv_HighlightableInterface ******************************************
#define FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void UnHighlight_Implementation() {}; \
	virtual void Highlight_Implementation() {}; \
	DECLARE_FUNCTION(execUnHighlight); \
	DECLARE_FUNCTION(execHighlight);


#define FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_11_CALLBACK_WRAPPERS
struct Z_Construct_UClass_UInv_HighlightableInterface_Statics;
INVENTORY_API UClass* Z_Construct_UClass_UInv_HighlightableInterface_NoRegister();

#define FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_11_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	INVENTORY_API UInv_HighlightableInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UInv_HighlightableInterface(UInv_HighlightableInterface&&) = delete; \
	UInv_HighlightableInterface(const UInv_HighlightableInterface&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(INVENTORY_API, UInv_HighlightableInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInv_HighlightableInterface); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInv_HighlightableInterface) \
	virtual ~UInv_HighlightableInterface() = default;


#define FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_11_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUInv_HighlightableInterface(); \
	friend struct ::Z_Construct_UClass_UInv_HighlightableInterface_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend INVENTORY_API UClass* ::Z_Construct_UClass_UInv_HighlightableInterface_NoRegister(); \
public: \
	DECLARE_CLASS2(UInv_HighlightableInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/Inventory"), Z_Construct_UClass_UInv_HighlightableInterface_NoRegister) \
	DECLARE_SERIALIZER(UInv_HighlightableInterface)


#define FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_11_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_11_GENERATED_UINTERFACE_BODY() \
	FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_11_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_11_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IInv_HighlightableInterface() {} \
public: \
	typedef UInv_HighlightableInterface UClassType; \
	typedef IInv_HighlightableInterface ThisClass; \
	static void Execute_Highlight(UObject* O); \
	static void Execute_UnHighlight(UObject* O); \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_8_PROLOG
#define FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_11_CALLBACK_WRAPPERS \
	FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h_11_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UInv_HighlightableInterface;

// ********** End Interface UInv_HighlightableInterface ********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
