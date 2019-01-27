#include "poker.h"

/*********************************************************************************
** Company: WSU CPTS 121
** Programmer: Jack 
**
** Create Date: 11/10/2018
** Design Name: Programming Assignment 07 - Poker
** Project Name: PA7_POKER
** Description: -
** Revision: -
** Additional Comments: With full card printout. 
**
**********************************************************************************/
int main(void)
{
	srand((unsigned int)time(0)); //seed rando
	const char *suit[NUMOFSUITS] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	const char *face[NUMOFCARDS] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };

	system("cls");
	int main_loop_status = READY;
	while (main_loop_status < EXIT) //MENU LOOP 
	{

		//call DoMainMenu()
		gameMenu(); //Print Options	
					//system("cls");//Clear Screen
		main_loop_status = getSelectOption(); //Get Input Choice(1, 2, 3), set mainLoopStatus
		system("cls");
		switch (main_loop_status) //SWITCH thru Input Choice
		{
		case RULES: //RULES
			printRules(); //call PrintRules()
			break;
		case PLAYGAME: //PLAYGAME
			playGame(deck, p1hand, p2hand, suit, face); //call PlayGame() - include *?
			system("cls"); //check 
			main_loop_status = EXIT; //send to exit message 
			//break;
		case EXIT: //EXIT
			text_color(RED);
			printf("\n               Thanks for playing!\n\n");
			text_color(WHITE);
			system("pause"); //waits after exit message 
			system("cls");
			main_loop_status = READY; //sets status to ready for menu loop repitition 
			break;
		}
	}
	return 0;
}
