// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Widgets/HUD/Inv_HUDWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeInv_HUDWidget() {}

// ********** Begin Cross Module References ********************************************************
INVENTORY_API UClass* Z_Construct_UClass_UInv_HUDWidget();
INVENTORY_API UClass* Z_Construct_UClass_UInv_HUDWidget_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Inventory();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UInv_HUDWidget Function HidePickupMessage ********************************
static FName NAME_UInv_HUDWidget_HidePickupMessage = FName(TEXT("HidePickupMessage"));
void UInv_HUDWidget::HidePickupMessage()
{
	UFunction* Func = FindFunctionChecked(NAME_UInv_HUDWidget_HidePickupMessage);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_UInv_HUDWidget_HidePickupMessage_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/Widgets/HUD/Inv_HUDWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function HidePickupMessage constinit property declarations *********************
// ********** End Function HidePickupMessage constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInv_HUDWidget_HidePickupMessage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInv_HUDWidget, nullptr, "HidePickupMessage", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInv_HUDWidget_HidePickupMessage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInv_HUDWidget_HidePickupMessage_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UInv_HUDWidget_HidePickupMessage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInv_HUDWidget_HidePickupMessage_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class UInv_HUDWidget Function HidePickupMessage **********************************

// ********** Begin Class UInv_HUDWidget Function ShowPickupMessage ********************************
struct Inv_HUDWidget_eventShowPickupMessage_Parms
{
	FString Message;
};
static FName NAME_UInv_HUDWidget_ShowPickupMessage = FName(TEXT("ShowPickupMessage"));
void UInv_HUDWidget::ShowPickupMessage(const FString& Message)
{
	Inv_HUDWidget_eventShowPickupMessage_Parms Parms;
	Parms.Message=Message;
	UFunction* Func = FindFunctionChecked(NAME_UInv_HUDWidget_ShowPickupMessage);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Inventory" },
		{ "ModuleRelativePath", "Public/Widgets/HUD/Inv_HUDWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ShowPickupMessage constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ShowPickupMessage constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ShowPickupMessage Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage_Statics::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Inv_HUDWidget_eventShowPickupMessage_Parms, Message), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Message_MetaData), NewProp_Message_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage_Statics::NewProp_Message,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage_Statics::PropPointers) < 2048);
// ********** End Function ShowPickupMessage Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInv_HUDWidget, nullptr, "ShowPickupMessage", 	Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage_Statics::PropPointers), 
sizeof(Inv_HUDWidget_eventShowPickupMessage_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Inv_HUDWidget_eventShowPickupMessage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class UInv_HUDWidget Function ShowPickupMessage **********************************

// ********** Begin Class UInv_HUDWidget ***********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UInv_HUDWidget;
UClass* UInv_HUDWidget::GetPrivateStaticClass()
{
	using TClass = UInv_HUDWidget;
	if (!Z_Registration_Info_UClass_UInv_HUDWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("Inv_HUDWidget"),
			Z_Registration_Info_UClass_UInv_HUDWidget.InnerSingleton,
			StaticRegisterNativesUInv_HUDWidget,
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
	return Z_Registration_Info_UClass_UInv_HUDWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_UInv_HUDWidget_NoRegister()
{
	return UInv_HUDWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInv_HUDWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Widgets/HUD/Inv_HUDWidget.h" },
		{ "ModuleRelativePath", "Public/Widgets/HUD/Inv_HUDWidget.h" },
		{ "PrioritizeCategories", "Inventory" },
	};
#endif // WITH_METADATA

// ********** Begin Class UInv_HUDWidget constinit property declarations ***************************
// ********** End Class UInv_HUDWidget constinit property declarations *****************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UInv_HUDWidget_HidePickupMessage, "HidePickupMessage" }, // 3506868387
		{ &Z_Construct_UFunction_UInv_HUDWidget_ShowPickupMessage, "ShowPickupMessage" }, // 2339206594
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInv_HUDWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UInv_HUDWidget_Statics
UObject* (*const Z_Construct_UClass_UInv_HUDWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Inventory,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInv_HUDWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInv_HUDWidget_Statics::ClassParams = {
	&UInv_HUDWidget::StaticClass,
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
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInv_HUDWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UInv_HUDWidget_Statics::Class_MetaDataParams)
};
void UInv_HUDWidget::StaticRegisterNativesUInv_HUDWidget()
{
}
UClass* Z_Construct_UClass_UInv_HUDWidget()
{
	if (!Z_Registration_Info_UClass_UInv_HUDWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInv_HUDWidget.OuterSingleton, Z_Construct_UClass_UInv_HUDWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInv_HUDWidget.OuterSingleton;
}
UInv_HUDWidget::UInv_HUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UInv_HUDWidget);
UInv_HUDWidget::~UInv_HUDWidget() {}
// ********** End Class UInv_HUDWidget *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Widgets_HUD_Inv_HUDWidget_h__Script_Inventory_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInv_HUDWidget, UInv_HUDWidget::StaticClass, TEXT("UInv_HUDWidget"), &Z_Registration_Info_UClass_UInv_HUDWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInv_HUDWidget), 3101814061U) },
	};
}; // Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Widgets_HUD_Inv_HUDWidget_h__Script_Inventory_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Widgets_HUD_Inv_HUDWidget_h__Script_Inventory_2582390279{
	TEXT("/Script/Inventory"),
	Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Widgets_HUD_Inv_HUDWidget_h__Script_Inventory_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Widgets_HUD_Inv_HUDWidget_h__Script_Inventory_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
