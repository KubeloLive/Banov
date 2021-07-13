void main()
{
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	Weather weather = g_Game.GetWeather();

	weather.MissionWeather(false);    // false = use weather controller from Weather.c

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	weather.GetRain().Set( 0, 0, 1);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();
	
     //DEV
	//GetCEApi().ExportProxyData("7680 0 7680", 16384);	// standard map groups (buildings) export, terrain center and radius needs to be specified
	//GetCEApi().ExportClusterData();

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
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			int rndHlt = Math.RandomInt(55,100);
			itemEnt.SetHealth("","",rndHlt);
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
    {
        Entity playerEnt;
        playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
        Class.CastTo(m_player, playerEnt);
 
        GetGame().SelectPlayer(identity, m_player);
 
        return m_player;
    }
 
    override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
    {
        EntityAI itemTop;
        EntityAI itemEnt;
        ItemBase itemBs;
        float rand;
 
        itemTop = player.FindAttachmentBySlotName("Body");
 
        if ( itemTop )
        {
            /*
            itemEnt = itemTop.GetInventory().CreateInInventory("Rag");
            if ( Class.CastTo(itemBs, itemEnt ) )
                itemBs.SetQuantity(6);
 
            SetRandomHealth(itemEnt);
 
            string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
            int rndIndex = Math.RandomInt(0, 4);
            itemEnt = itemTop.GetInventory().CreateInInventory(chemlightArray[rndIndex]);
            SetRandomHealth(itemEnt);
 
            rand = Math.RandomFloatInclusive(0.0, 1.0);
            if ( rand < 0.35 )
                itemEnt = player.GetInventory().CreateInInventory("Apple");
            else if ( rand > 0.65 )
                itemEnt = player.GetInventory().CreateInInventory("Pear");
            else
                itemEnt = player.GetInventory().CreateInInventory("Plum");
 
            SetRandomHealth(itemEnt);
            */
            player.RemoveAllItems();
           
            itemEnt = player.GetInventory().CreateInInventory("Shirt_BlueCheckBright");
            itemEnt = player.GetInventory().CreateInInventory("Jeans_Blue");
            itemEnt = player.GetInventory().CreateInInventory("WorkingBoots_Grey");
			itemEnt = player.GetInventory().CreateInInventory("Rag");
			itemEnt = player.GetInventory().CreateInInventory("Apple");
		//Item in hands
		EntityAI knife;
		knife = player.GetHumanInventory().CreateInHands("Pear"); 
	
		//batery in hands
		EntityAI baterka;
		baterka = player.GetInventory().CreateInInventory("Flashlight");
		baterka.GetInventory().CreateAttachment("Battery9V");

     }
    }
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}