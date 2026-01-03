// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Items/Components/Inv_HighlightableStaticMeshComp.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeInv_HighlightableStaticMeshComp() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent();
INVENTORY_API UClass* Z_Construct_UClass_UInv_HighlightableInterface_NoRegister();
INVENTORY_API UClass* Z_Construct_UClass_UInv_HighlightableStaticMeshComp();
INVENTORY_API UClass* Z_Construct_UClass_UInv_HighlightableStaticMeshComp_NoRegister();
UPackage* Z_Construct_UPackage__Script_Inventory();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UInv_HighlightableStaticMeshComp *****************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UInv_HighlightableStaticMeshComp;
UClass* UInv_HighlightableStaticMeshComp::GetPrivateStaticClass()
{
	using TClass = UInv_HighlightableStaticMeshComp;
	if (!Z_Registration_Info_UClass_UInv_HighlightableStaticMeshComp.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("Inv_HighlightableStaticMeshComp"),
			Z_Registration_Info_UClass_UInv_HighlightableStaticMeshComp.InnerSingleton,
			StaticRegisterNativesUInv_HighlightableStaticMeshComp,
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
	return Z_Registration_Info_UClass_UInv_HighlightableStaticMeshComp.InnerSingleton;
}
UClass* Z_Construct_UClass_UInv_HighlightableStaticMeshComp_NoRegister()
{
	return UInv_HighlightableStaticMeshComp::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Object Activation Components|Activation Trigger" },
		{ "IncludePath", "Items/Components/Inv_HighlightableStaticMeshComp.h" },
		{ "ModuleRelativePath", "Public/Items/Components/Inv_HighlightableStaticMeshComp.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HighlightMaterial_MetaData[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/Items/Components/Inv_HighlightableStaticMeshComp.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UInv_HighlightableStaticMeshComp constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HighlightMaterial;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UInv_HighlightableStaticMeshComp constinit property declarations ***********
	static UObject* (*const DependentSingletons[])();
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInv_HighlightableStaticMeshComp>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics

// ********** Begin Class UInv_HighlightableStaticMeshComp Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::NewProp_HighlightMaterial = { "HighlightMaterial", nullptr, (EPropertyFlags)0x0144000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInv_HighlightableStaticMeshComp, HighlightMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HighlightMaterial_MetaData), NewProp_HighlightMaterial_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::NewProp_HighlightMaterial,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::PropPointers) < 2048);
// ********** End Class UInv_HighlightableStaticMeshComp Property Definitions **********************
UObject* (*const Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UStaticMeshComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_Inventory,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UInv_HighlightableInterface_NoRegister, (int32)VTABLE_OFFSET(UInv_HighlightableStaticMeshComp, IInv_HighlightableInterface), false },  // 2698598848
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::ClassParams = {
	&UInv_HighlightableStaticMeshComp::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x00B010A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::Class_MetaDataParams), Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::Class_MetaDataParams)
};
void UInv_HighlightableStaticMeshComp::StaticRegisterNativesUInv_HighlightableStaticMeshComp()
{
}
UClass* Z_Construct_UClass_UInv_HighlightableStaticMeshComp()
{
	if (!Z_Registration_Info_UClass_UInv_HighlightableStaticMeshComp.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInv_HighlightableStaticMeshComp.OuterSingleton, Z_Construct_UClass_UInv_HighlightableStaticMeshComp_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInv_HighlightableStaticMeshComp.OuterSingleton;
}
UInv_HighlightableStaticMeshComp::UInv_HighlightableStaticMeshComp(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UInv_HighlightableStaticMeshComp);
UInv_HighlightableStaticMeshComp::~UInv_HighlightableStaticMeshComp() {}
// ********** End Class UInv_HighlightableStaticMeshComp *******************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Items_Components_Inv_HighlightableStaticMeshComp_h__Script_Inventory_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInv_HighlightableStaticMeshComp, UInv_HighlightableStaticMeshComp::StaticClass, TEXT("UInv_HighlightableStaticMeshComp"), &Z_Registration_Info_UClass_UInv_HighlightableStaticMeshComp, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInv_HighlightableStaticMeshComp), 2269560666U) },
	};
}; // Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Items_Components_Inv_HighlightableStaticMeshComp_h__Script_Inventory_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Items_Components_Inv_HighlightableStaticMeshComp_h__Script_Inventory_3943931227{
	TEXT("/Script/Inventory"),
	Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Items_Components_Inv_HighlightableStaticMeshComp_h__Script_Inventory_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Items_Components_Inv_HighlightableStaticMeshComp_h__Script_Inventory_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
