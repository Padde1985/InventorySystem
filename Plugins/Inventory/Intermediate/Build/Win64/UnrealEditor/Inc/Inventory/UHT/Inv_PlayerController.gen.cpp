// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Player/Inv_PlayerController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeInv_PlayerController() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
ENGINE_API UEnum* Z_Construct_UEnum_Engine_ECollisionChannel();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
INVENTORY_API UClass* Z_Construct_UClass_AInv_PlayerController();
INVENTORY_API UClass* Z_Construct_UClass_AInv_PlayerController_NoRegister();
INVENTORY_API UClass* Z_Construct_UClass_UInv_HUDWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_Inventory();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AInv_PlayerController ****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AInv_PlayerController;
UClass* AInv_PlayerController::GetPrivateStaticClass()
{
	using TClass = AInv_PlayerController;
	if (!Z_Registration_Info_UClass_AInv_PlayerController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("Inv_PlayerController"),
			Z_Registration_Info_UClass_AInv_PlayerController.InnerSingleton,
			StaticRegisterNativesAInv_PlayerController,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AInv_PlayerController.InnerSingleton;
}
UClass* Z_Construct_UClass_AInv_PlayerController_NoRegister()
{
	return AInv_PlayerController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AInv_PlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Player/Inv_PlayerController.h" },
		{ "ModuleRelativePath", "Public/Player/Inv_PlayerController.h" },
		{ "PrioritizeCategories", "Inventory" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultIMCs_MetaData[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/Player/Inv_PlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PrimaryInteractAction_MetaData[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/Player/Inv_PlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HUDWidgetClass_MetaData[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/Player/Inv_PlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HUDWidget_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Player/Inv_PlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TraceLength_MetaData[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/Player/Inv_PlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemTraceChannel_MetaData[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/Player/Inv_PlayerController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AInv_PlayerController constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultIMCs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DefaultIMCs;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PrimaryInteractAction;
	static const UECodeGen_Private::FClassPropertyParams NewProp_HUDWidgetClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HUDWidget;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_TraceLength;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ItemTraceChannel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AInv_PlayerController constinit property declarations **********************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AInv_PlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AInv_PlayerController_Statics

// ********** Begin Class AInv_PlayerController Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_DefaultIMCs_Inner = { "DefaultIMCs", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_DefaultIMCs = { "DefaultIMCs", nullptr, (EPropertyFlags)0x0144000000010001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInv_PlayerController, DefaultIMCs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultIMCs_MetaData), NewProp_DefaultIMCs_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_PrimaryInteractAction = { "PrimaryInteractAction", nullptr, (EPropertyFlags)0x0144000000010001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInv_PlayerController, PrimaryInteractAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PrimaryInteractAction_MetaData), NewProp_PrimaryInteractAction_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_HUDWidgetClass = { "HUDWidgetClass", nullptr, (EPropertyFlags)0x0044000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInv_PlayerController, HUDWidgetClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UInv_HUDWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HUDWidgetClass_MetaData), NewProp_HUDWidgetClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_HUDWidget = { "HUDWidget", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInv_PlayerController, HUDWidget), Z_Construct_UClass_UInv_HUDWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HUDWidget_MetaData), NewProp_HUDWidget_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_TraceLength = { "TraceLength", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInv_PlayerController, TraceLength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TraceLength_MetaData), NewProp_TraceLength_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_ItemTraceChannel = { "ItemTraceChannel", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AInv_PlayerController, ItemTraceChannel), Z_Construct_UEnum_Engine_ECollisionChannel, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemTraceChannel_MetaData), NewProp_ItemTraceChannel_MetaData) }; // 838391399
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AInv_PlayerController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_DefaultIMCs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_DefaultIMCs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_PrimaryInteractAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_HUDWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_HUDWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_TraceLength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInv_PlayerController_Statics::NewProp_ItemTraceChannel,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInv_PlayerController_Statics::PropPointers) < 2048);
// ********** End Class AInv_PlayerController Property Definitions *********************************
UObject* (*const Z_Construct_UClass_AInv_PlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_Inventory,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AInv_PlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AInv_PlayerController_Statics::ClassParams = {
	&AInv_PlayerController::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AInv_PlayerController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AInv_PlayerController_Statics::PropPointers),
	0,
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AInv_PlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AInv_PlayerController_Statics::Class_MetaDataParams)
};
void AInv_PlayerController::StaticRegisterNativesAInv_PlayerController()
{
}
UClass* Z_Construct_UClass_AInv_PlayerController()
{
	if (!Z_Registration_Info_UClass_AInv_PlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AInv_PlayerController.OuterSingleton, Z_Construct_UClass_AInv_PlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AInv_PlayerController.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AInv_PlayerController);
AInv_PlayerController::~AInv_PlayerController() {}
// ********** End Class AInv_PlayerController ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Player_Inv_PlayerController_h__Script_Inventory_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AInv_PlayerController, AInv_PlayerController::StaticClass, TEXT("AInv_PlayerController"), &Z_Registration_Info_UClass_AInv_PlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AInv_PlayerController), 1113555058U) },
	};
}; // Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Player_Inv_PlayerController_h__Script_Inventory_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Player_Inv_PlayerController_h__Script_Inventory_356273014{
	TEXT("/Script/Inventory"),
	Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Player_Inv_PlayerController_h__Script_Inventory_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Player_Inv_PlayerController_h__Script_Inventory_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
