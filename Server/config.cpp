class CfgPatches
{
	class KUBCItems
	{
		units[]= {};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]= 
		{
			"KUBCconsole"
		};
	};
};
class CfgMods 
{
	class KUBCItems
	{
		name = "KUBC.DAYZ.ITEMS";
		author = "kubcoder";
		version = 2.4;
		type = "mod";
		class defs 
		{
			class worldScriptModule {
				value = "";
				files[] = {"KUBC.DAYZ.ITEMS\4_World"};
			};
			class missionScriptModule
			{
				value="";
				files[]={"KUBC.DAYZ.ITEMS\5_Mission"};
			};
		}; 
	};
};