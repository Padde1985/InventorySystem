// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Interaction/Inv_HighlightableInterface.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeInv_HighlightableInterface() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
INVENTORY_API UClass* Z_Construct_UClass_UInv_HighlightableInterface();
INVENTORY_API UClass* Z_Construct_UClass_UInv_HighlightableInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_Inventory();
// ********** End Cross Module References **********************************************************

// ********** Begin Interface UInv_HighlightableInterface Function Highlight ***********************
void IInv_HighlightableInterface::Highlight()
{
	check(0 && "Do not directly call Event functions in Interfaces. Call Execute_Highlight instead.");
}
static FName NAME_UInv_HighlightableInterface_Highlight = FName(TEXT("Highlight"));
void IInv_HighlightableInterface::Execute_Highlight(UObject* O)
{
	check(O != NULL);
	check(O->GetClass()->ImplementsInterface(UInv_HighlightableInterface::StaticClass()));
	UFunction* const Func = O->FindFunction(NAME_UInv_HighlightableInterface_Highlight);
	if (Func)
	{
		O->ProcessEvent(Func, NULL);
	}
	else if (auto I = (IInv_HighlightableInterface*)(O->GetNativeInterfaceAddress(UInv_HighlightableInterface::StaticClass())))
	{
		I->Highlight_Implementation();
	}
}
struct Z_Construct_UFunction_UInv_HighlightableInterface_Highlight_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Interaction/Inv_HighlightableInterface.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function Highlight constinit property declarations *****************************
// ********** End Function Highlight constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInv_HighlightableInterface_Highlight_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInv_HighlightableInterface, nullptr, "Highlight", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInv_HighlightableInterface_Highlight_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInv_HighlightableInterface_Highlight_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UInv_HighlightableInterface_Highlight()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInv_HighlightableInterface_Highlight_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(IInv_HighlightableInterface::execHighlight)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Highlight_Implementation();
	P_NATIVE_END;
}
// ********** End Interface UInv_HighlightableInterface Function Highlight *************************

// ********** Begin Interface UInv_HighlightableInterface Function UnHighlight *********************
void IInv_HighlightableInterface::UnHighlight()
{
	check(0 && "Do not directly call Event functions in Interfaces. Call Execute_UnHighlight instead.");
}
static FName NAME_UInv_HighlightableInterface_UnHighlight = FName(TEXT("UnHighlight"));
void IInv_HighlightableInterface::Execute_UnHighlight(UObject* O)
{
	check(O != NULL);
	check(O->GetClass()->ImplementsInterface(UInv_HighlightableInterface::StaticClass()));
	UFunction* const Func = O->FindFunction(NAME_UInv_HighlightableInterface_UnHighlight);
	if (Func)
	{
		O->ProcessEvent(Func, NULL);
	}
	else if (auto I = (IInv_HighlightableInterface*)(O->GetNativeInterfaceAddress(UInv_HighlightableInterface::StaticClass())))
	{
		I->UnHighlight_Implementation();
	}
}
struct Z_Construct_UFunction_UInv_HighlightableInterface_UnHighlight_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Interaction/Inv_HighlightableInterface.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function UnHighlight constinit property declarations ***************************
// ********** End Function UnHighlight constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInv_HighlightableInterface_UnHighlight_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInv_HighlightableInterface, nullptr, "UnHighlight", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInv_HighlightableInterface_UnHighlight_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInv_HighlightableInterface_UnHighlight_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UInv_HighlightableInterface_UnHighlight()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInv_HighlightableInterface_UnHighlight_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(IInv_HighlightableInterface::execUnHighlight)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UnHighlight_Implementation();
	P_NATIVE_END;
}
// ********** End Interface UInv_HighlightableInterface Function UnHighlight ***********************

// ********** Begin Interface UInv_HighlightableInterface ******************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UInv_HighlightableInterface;
UClass* UInv_HighlightableInterface::GetPrivateStaticClass()
{
	using TClass = UInv_HighlightableInterface;
	if (!Z_Registration_Info_UClass_UInv_HighlightableInterface.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("Inv_HighlightableInterface"),
			Z_Registration_Info_UClass_UInv_HighlightableInterface.InnerSingleton,
			StaticRegisterNativesUInv_HighlightableInterface,
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
	return Z_Registration_Info_UClass_UInv_HighlightableInterface.InnerSingleton;
}
UClass* Z_Construct_UClass_UInv_HighlightableInterface_NoRegister()
{
	return UInv_HighlightableInterface::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInv_HighlightableInterface_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Interaction/Inv_HighlightableInterface.h" },
	};
#endif // WITH_METADATA

// ********** Begin Interface UInv_HighlightableInterface constinit property declarations **********
// ********** End Interface UInv_HighlightableInterface constinit property declarations ************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("Highlight"), .Pointer = &IInv_HighlightableInterface::execHighlight },
		{ .NameUTF8 = UTF8TEXT("UnHighlight"), .Pointer = &IInv_HighlightableInterface::execUnHighlight },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UInv_HighlightableInterface_Highlight, "Highlight" }, // 2701950880
		{ &Z_Construct_UFunction_UInv_HighlightableInterface_UnHighlight, "UnHighlight" }, // 3154460049
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IInv_HighlightableInterface>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UInv_HighlightableInterface_Statics
UObject* (*const Z_Construct_UClass_UInv_HighlightableInterface_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_Inventory,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInv_HighlightableInterface_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInv_HighlightableInterface_Statics::ClassParams = {
	&UInv_HighlightableInterface::StaticClass,
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
	0x000840A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInv_HighlightableInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_UInv_HighlightableInterface_Statics::Class_MetaDataParams)
};
void UInv_HighlightableInterface::StaticRegisterNativesUInv_HighlightableInterface()
{
	UClass* Class = UInv_HighlightableInterface::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UInv_HighlightableInterface_Statics::Funcs));
}
UClass* Z_Construct_UClass_UInv_HighlightableInterface()
{
	if (!Z_Registration_Info_UClass_UInv_HighlightableInterface.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInv_HighlightableInterface.OuterSingleton, Z_Construct_UClass_UInv_HighlightableInterface_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInv_HighlightableInterface.OuterSingleton;
}
UInv_HighlightableInterface::UInv_HighlightableInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UInv_HighlightableInterface);
// ********** End Interface UInv_HighlightableInterface ********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h__Script_Inventory_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInv_HighlightableInterface, UInv_HighlightableInterface::StaticClass, TEXT("UInv_HighlightableInterface"), &Z_Registration_Info_UClass_UInv_HighlightableInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInv_HighlightableInterface), 2698598848U) },
	};
}; // Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h__Script_Inventory_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h__Script_Inventory_748560905{
	TEXT("/Script/Inventory"),
	Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h__Script_Inventory_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_InventorySystem_Plugins_Inventory_Source_Inventory_Public_Interaction_Inv_HighlightableInterface_h__Script_Inventory_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
