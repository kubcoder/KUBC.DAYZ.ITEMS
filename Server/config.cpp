class CfgPatches
{
	class KUBCItems
	{
		units[]= {};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]= {"KUBCconsole","DZ_Characters"};
	};
};
class CfgMods 
{
	class KUBCItems
	{
		name = "KUBC.DAYZ.ITEMS";
		author = "kubcoder";
		version = 2.0;
		type = "mod";
		class defs 
		{
			class missionScriptModule
			{
				value="";
				files[]={"KUBC.DAYZ.ITEMS\5_Mission"};
			};
		}; 
	};
};