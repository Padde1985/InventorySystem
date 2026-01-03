// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInventory_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Inventory;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Inventory()
	{
		if (!Z_Registration_Info_UPackage__Script_Inventory.OuterSingleton)
		{
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/Inventory",
			nullptr,
			0,
			PKG_CompiledIn | 0x00000000,
			0x3979A585,
			0xE2B09405,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Inventory.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_Inventory.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Inventory(Z_Construct_UPackage__Script_Inventory, TEXT("/Script/Inventory"), Z_Registration_Info_UPackage__Script_Inventory, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x3979A585, 0xE2B09405));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
