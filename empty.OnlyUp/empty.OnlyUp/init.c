//Vanilla Banov Init.c
// Thank you for using my map
void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();
	
//Loot spawn Creator
//GetCEApi().ExportProxyData(vector.Zero, 100000); //Loot
//GetCEApi().ExportClusterData(); //Fruit	

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}

	// DEATH TRIGGER
	OnlyUpDeathTrigger trigger = OnlyUpDeathTrigger.Cast( GetGame().CreateObject( "OnlyUpDeathTrigger", Vector( 4914, 190, 4893 ), false, false, true ) );
	trigger.SetExtents( Vector( -1000, -20, -1000), Vector( 1000, 0, 1000) );
}
class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
    {
        EntityAI itemTop;
        EntityAI itemEnt;
        ItemBase itemBs;
        float rand;

        player.SetAllowDamage( false );
        player.RemoveAllItems();

            ref TStringArray topsArray = {"Only_UP_Tshirt"};
            ref TStringArray pantsArray = {"Only_UP_Jeans"};
            ref TStringArray helmArray = {"Only_UP_BaseballCap"};
			ref TStringArray shoesArray = {"Sneakers_White"};

            EntityAI item1 = player.GetInventory().CreateInInventory(topsArray.GetRandomElement());
            EntityAI item2 = player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
            EntityAI item3 = player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
            EntityAI item5 = player.GetInventory().CreateInInventory(helmArray.GetRandomElement());

        itemTop = player.FindAttachmentBySlotName("Body");

        if ( itemTop )
        {
            itemEnt = itemTop.GetInventory().CreateInInventory("Rag");
            if ( Class.CastTo(itemBs, itemEnt ) )
                itemBs.SetQuantity(5);
                itemBs.SetCleanness( 1 );


            string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
            int rndIndex = Math.RandomInt(0, 4);
            itemEnt = itemTop.GetInventory().CreateInInventory(chemlightArray[rndIndex]);
                SetRandomHealth(itemEnt);

            rand = Math.RandomFloatInclusive(0.0, 1.0);
            if ( rand < 0.35 )
                itemEnt = player.GetInventory().CreateInInventory("Potato");
            else if ( rand > 0.65 )
                itemEnt = player.GetInventory().CreateInInventory("Pear");
            else
                itemEnt = player.GetInventory().CreateInInventory("Zucchini");

            SetRandomHealth(itemEnt);
            player.GetInventory().CreateInInventory("SodaCan_Spite");
            player.GetInventory().CreateInInventory("TacticalBaconCan_Opened");
			player.GetStatWater().Set( 5000 );
			player.GetStatEnergy().Set( 20000 );
        }
    }
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
