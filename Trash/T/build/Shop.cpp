#include"Shop.h"
void Shop::DisplayShop()
{
    cout<<"\t                              SHOP\t\n";
    cout<<"\t    Item Available:\t\n";
    cout<<"\tName                     Price                            Effect\t\n";
    cout<<"\t1.Health potion         20 gold                           +10 hp\t\n";
    cout<<"\t2.Sword                 50 gold                           +3 atk\t\n";
    cout<<"\t3.Greatsword            100 gold                          +6 atk\t\n";
    cout<<"\t4.Excalibur             200 gold                          +9 atk\t\n";
    cout<<"\t5.Shield                30 gold                           +2 def\t\n";
    cout<<"\t6.Knight's shield       70 gold                           +4 def\t\n";
    cout<<"\t7.Hero's shield         175 gold                          +6 def\t\n";
}
int Shop::Choices(int choices)
{
    cout<<"What do you want"
    cin<<choices
    switch (choices)
    {
    case 1:
        //Buy Health potion
        break;
    case 2:
        //Sword
        break;
    case 3:
        //Great Sword
        break;
    case 4:
        //Excalibur
        break;
    case 5:
       //Shield
        break;
    case 6:
       //Knight's shield
        break;
    case 7:
       //Hero's shield
       break;
    case 0:
       //Quit Shop
       break; 
    default:
        break;
    }
}

