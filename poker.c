#include "poker.h"

/************************************************************
* Function: text_color(int)
* Date Created: Nov. 10, 2018
* Date Last Modified: Nov. 10, 2018
* Description: Change Text Color
* Input parameters:  Enum Int #
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void text_color(i)
{
	printf("%c[%dm", 0x1B, i + 30);
}

/************************************************************
* Function: back_color(int)
* Date Created: Nov. 10, 2018
* Date Last Modified: Nov. 10, 2018
* Description: Change Background Color
* Input parameters: Enum Int #
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void back_color(i)
{
	printf("%c[%dm", 0x1B, i + 40);
}

/************************************************************
* Function: gameMenu()
* Date Created: Nov. 10, 2018
* Date Last Modified: Nov. 10, 2018
* Description: Main game menu.
* Input parameters: -
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void gameMenu()
{
	text_color(GREEN);
	//back_color(black);
	//_setmode(_fileno(stdout), _O_U16TEXT);

	printf(" *******************************************************************************************************\n");
	printf(" *                                           Welcome to Poker!                                         *\n");
	printf(" *                                            - 5 Card Draw -                                          *\n");
	printf(" *        -----------                                                             -----------          *\n");
	printf(" *        | A       |                                                             | K       |          *\n");
	printf(" *        |         |                  Select your option below                   |         |          *\n");
	printf(" *        |         |                                                             |         |          *\n");
	printf(" *        |         |                  1: Rules                                   |         |          *\n");
	printf(" *        |         |                  2: Play game                               |         |          *\n");
	printf(" *        |       A |                  3: Exit game                               |       K |          *\n");
	printf(" *        -----------                                                             -----------          *\n");
	printf(" *                                                                                                     *\n");
	printf(" *                                                                                                     *\n");
	printf(" *******************************************************************************************************\n");

	text_color(WHITE);
	//back_color(black);
	return;
}

/************************************************************
* Function: getSelectOption()
* Date Created: Nov. 10, 2018
* Date Last Modified: Nov. 10, 2018
* Description: Gathers player selection for main() loop. Whether they want to view the rules and play or leave.
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions:
*************************************************************/
int getSelectOption()
{
	int selection = 0;

	scanf("%d", &selection);

	return selection;
}

/************************************************************
* Function: printRules()
* Date Created: Nov. 10, 2018
* Date Last Modified: Nov. 10, 2018
* Description: Prints rules to 5 card draw. IN CYAN!!!
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void printRules(void)
{
	text_color(CYAN);

	printf("*******************************************************************************************************************************************\n\n");
	printf(" > Rules to 5 Card Draw:                                                                                                                    *\n");
	printf("                                                                                                                                            *\n");
	printf(" - This game facilitates one-on-one play against the dealer(system).                                                                        *\n");
	printf(" - To start, input the player name into the system.                                                                                         *\n");
	printf(" - Five cards will be dealt to you and the dealer, on at a time.                                                                            *\n");
	printf(" - You and the dealer will each have the opprotunity to select cards to remove from your hand for reshuffling, to better your hand.         *\n");
	printf(" - Once the selected cards have been removed from the deck and reshuffled, the respective hands will be presented and evaluated.            *\n");
	printf(" - A winner will be selected based upon the quality of the hands.                                                                           *\n");
	printf("                                                                                                                                            *\n");
	printf("*******************************************************************************************************************************************\n\n");

	text_color(WHITE);

	system("pause");
	system("cls");

	return;
}

/************************************************************
* Function: playGame()
* Date Created: Nov. 10, 2018
* Date Last Modified: Nov. 11, 2018
* Description: Heart of the game.
* Input parameters: int deck[NUMOFSUITS][NUMOFCARDS], int hand[NUMOFPLAYERS][5]
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void playGame(card deck[NUMOFCARDS], card p1hand[SIZEOFHAND], card p2hand[SIZEOFHAND], const char *suit[NUMOFSUITS], const char *face[NUMOFCARDS])
{
	int card_num = 1, player_status = PLAYGAME;
	resetDeck(deck);
	//------
	getPlayerName(playernames);
	while (player_status != EXIT) //Game Loop - Stay until player decides to EXIT
	{
		shuffleDeck(deck);
		dealHand(deck, *face, *suit, p1hand, p2hand);

		displayCards(p1hand, p2hand, 1 /*computer hand hidden*/);
		printf("The computer discarded %d cards.\n", ComputerTurn(p1hand, deck));
		doPlayerTurn(p2hand, deck);
		displayCards(p1hand, p2hand, 0 /*computer hand NOT hidden*/);
		declareWinner(p1hand, p2hand);
		if (!continuePlaying())
			player_status = EXIT;
	}
	return;
}

/************************************************************
* Function: continuePlaying()
* Date Created: Nov. 11, 2018
* Date Last Modified: Nov. 11, 2018
* Description: INITIALIZATION
* Input parameters: -
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
int continuePlaying()
{
	int flag = 0;
	printf("\nPress 1 to Continue. Otherwise, press 0 to return to the Menu.\n");
	scanf("%d", &flag);
	return flag;
}

/************************************************************
* Function: declareWinner(card hand1[] and hand2[])
* Date Created: Nov. 20, 2018
* Date Last Modified: Nov. 25, 2018
* Description: INITIALIZATION
* Input parameters: card hand1[], hand2[]
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void declareWinner(card hand1[SIZEOFHAND], card hand2[SIZEOFHAND])
{
	int card_num = 1, player_status = PLAYGAME, computerScore = 0, humanScore = 0;
	computerScore = evaluate(p1hand, COMPUTER);
	humanScore = evaluate(p2hand, PLAYER);
	printf("%s has ", playernames[COMPUTER]);
	writeHandCombination(computerScore);
	printf(".  %s has ", playernames[PLAYER]);
	writeHandCombination(humanScore);
	printf(".\n");
	computerScore = computerScore * 100;
	humanScore = humanScore * 100;
	if (computerScore == humanScore)
	{
		computerScore = computerScore + getHighestCardCombinationValue(p1hand);
		humanScore = humanScore + getHighestCardCombinationValue(p2hand);
	}
	printf("%s you are the winner!", (computerScore > humanScore) ? playernames[COMPUTER] : playernames[PLAYER]);	//print which is the Winner
	return;
}

/************************************************************
* Function: writeHandCombination(int combo)
* Date Created: Nov. 11, 2018
* Date Last Modified: Nov. 11, 2018
* Description: INITIALIZATION
* Input parameters: INTEGER - Enumeration for Hand Combo
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void writeHandCombination(int combo)
{
	switch (combo)
	{
	case NOHAND: printf("no hand"); break;
	case ONEPAIR: printf("a pair");  break;
	case TWOPAIR: printf("a two pair");  break;
	case THREEKIND: printf("a three-of-a-kind");  break;
	case STRAIGHT: printf("a straight");  break;
	case FLUSH: printf("a flush");  break;
	case FULLHOUSE: printf("a full-house");  break;
	case FOURKIND: printf("a four-of-a-kind");  break;
	default: printf("unknown"); break;
	}
	return;
}

/************************************************************
* Function: resetDeck()
* Date Created: Nov. 11, 2018
* Date Last Modified: Nov. 11, 2018
* Description: INITIALIZATION
* Input parameters: int deck[NUMOFSUITS][NUMOFCARDS]
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void resetDeck(card deck[NUMOFCARDS])
{
	for (int j = 0; j < NUMOFCARDS; j++)
	{
		deck[j].face = -1;
		deck[j].suit = -1;
	}
	return;
}//INITIALIZATION 

  /************************************************************
  * Function: resetHand()
  * Date Created: Nov. 11, 2018
  * Date Last Modified: Nov. 11, 2018
  * Description: INITIALIZATION
  * Input parameters: int hand[NUMOFPLAYERS][5]
  * Returns: -
  * Preconditions: -
  * Postconditions: -
  *************************************************************/
void resetHand(card hand[SIZEOFHAND])
{
	for (int j = 0; j < SIZEOFHAND; j++)
	{
		hand[j].face = -1;
		hand[j].suit = -1;
	}
	return;
}//INITIALIZATION

  /************************************************************
  * Function: getPlayerName()
  * Date Created: Nov. 11, 2018
  * Date Last Modified: Nov. 11, 2018
  * Description:
  * Input parameters:
  * Returns: -
  * Preconditions: -
  * Postconditions: -
  *************************************************************/
void getPlayerName(char playernames[][100]) 
{
	printf("\nInput player name: ");
	scanf("%s", ((char*)playernames[PLAYER]));
	strcpy(playernames[COMPUTER], "Dealer");
	return;
}

/************************************************************
* Function: dealHand()
* Date Created: Nov. 11, 2018
* Date Last Modified: Nov. 11, 2018
* Description:
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void dealHand(card wDeck[NUMOFCARDS], const char *wFace[], const char *wSuit[], card p1hand[SIZEOFHAND], card p2hand[SIZEOFHAND])
{
	resetHand(p1hand);
	resetHand(p2hand);
	for (int i = 0; i < SIZEOFHAND; i++)
	{
		p1hand[i].face = wDeck[getFreeCardLocation(wDeck)].face;
		p1hand[i].suit = wDeck[getFreeCardLocation(wDeck)].suit;

		wDeck[getFreeCardLocation(deck)].suit = -1;  
		wDeck[getFreeCardLocation(deck)].face = -1;

		p2hand[i].face = wDeck[getFreeCardLocation(wDeck)].face;
		p2hand[i].suit = wDeck[getFreeCardLocation(wDeck)].suit;

		wDeck[getFreeCardLocation(deck)].suit = -1;  
		wDeck[getFreeCardLocation(deck)].face = -1;
	}
	return;
}

/************************************************************
* Function: shuffleDeck()
* Date Created: Nov. 11, 2018
* Date Last Modified: Nov. 11, 2018
* Description:
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void shuffleDeck(card wDeck[NUMOFCARDS])
{
	int index = 0, card = 0;
	resetDeck(wDeck);
	for (card = 1; card <= NUMOFCARDS; card++)
	{
		do
		{
			index = (rand() % 52);
		} while (wDeck[index].face != -1);
		wDeck[index].suit = (card % NUMOFSUITS);
		wDeck[index].face = (card % NUMOFVALUES);
	}
	return;
}

/************************************************************
* Function: struct card of array[5]()
* Date Created: Nov. 11, 2018
* Date Last Modified: Nov. 11, 2018
* Description:
* Input parameters:struct card of array[5]
* Returns: INTEGER
* Preconditions: -
* Postconditions: -
*************************************************************/
int getHighestCardValue(card aHand[SIZEOFHAND])
{
	int max = -1;
	for (int i = 0; i < NUMOFVALUES; i++)
		if (aHand[i].face > max)
			max = aHand[i].face;
	return max;
}

/************************************************************
* Function: getHighestCardCombinationValue()
* Date Created: Nov. 11, 2018
* Date Last Modified: Nov. 11, 2018
* Description: Loops thru the 5 cards and finds the highest combination VALUE where the Count is > 1. Loop through possible values and find the maximum count by value 
* Input parameters: struct card of array[5]
* Returns: INTEGER
* Preconditions: -
* Postconditions: -
*************************************************************/
int getHighestCardCombinationValue(card aHand[SIZEOFHAND])
{
	int value = 0, combo = 1, flush_value = 0;
	for (int i = 0; i < NUMOFVALUES; i++)
	{
		if (getCountofValue(aHand, i) > combo)
		{
			combo = getCountofValue(aHand, i);
			value = i;
		}
		else if (getCountofValue(aHand, i) > 1
			&& i > value
			&& combo < 2)
			value = i;
	}
	//if a straight send back max value 
	for (int j = 1; j < 9; j++)
	{
		if (((getCountofValue(aHand, j) > 0)
			&& (getCountofValue(aHand, (j + 1)) > 0)
			&& (getCountofValue(aHand, (j + 2)) > 0)
			&& (getCountofValue(aHand, (j + 3)) > 0)
			&& (getCountofValue(aHand, (j + 4)) > 0)))
		{
			return value;
		}
	}
	//if a flush send back max value 
	for (int i = 0; i < SIZEOFHAND; i++)
	{
		flush_value += aHand[i].suit; //getCountofSuit() is alt
	}
	if (flush_value == 0 || flush_value == 5 || flush_value == 10 || flush_value == 15)
	{
		return value;
	}
	//if a combo send back max combo value //else send back max value
	return value;
}

/************************************************************
* Function: getCountofValue
* Date Created: Nov. 12, 2018
* Date Last Modified: Nov. 21, 2018
* Description: Loops thru the 5 cards and finds the COUNT of the VALUE. 
* Input parameters:  
* Returns: return the COUNT
* Preconditions: -
* Postconditions: -
*************************************************************/
int getCountofValue(card aHand[SIZEOFHAND], int Value)
{
	int count = 0;
	for (int i = 0; i < SIZEOFHAND; i++)
	{
		if (aHand[i].face == Value)
		{
			count++;
		}
	}
	return count;
}

/************************************************************
* Function: getCountofSuit
* Date Created: Nov. 12, 2018
* Date Last Modified: Nov. 21, 2018
* Description: Loops thru the 5 cards and finds the COUNT of the SUIT
* Input parameters:
* Returns: return the COUNT
* Preconditions: -
* Postconditions: -
*************************************************************/
int getCountofSuit(card aHand[SIZEOFHAND], int Suit)
{
	int count = 0;
	for (int i = 0; i < SIZEOFHAND; i++)
	{
		if (aHand[i].suit == Suit)
		{
			count++;
		}
	}
	return count;
}

/************************************************************
* Function: getArrayLocation
* Date Created: Nov. 24, 2018
* Date Last Modified: Nov. 25, 2018
* Description: Default if all spaces full 
* Input parameters:
* Returns: Free array location for writing, or -1 if array is full. 
* Preconditions: -
* Postconditions: -
*************************************************************/
int getArrayLocation(card localHand[SIZEOFHAND])
{
	for (int i = 0; i < SIZEOFHAND; i++)
	{
		if (localHand[i].face == -1)
		{
			return i;
		}
	}
	return -1; 
}

/************************************************************
* Function: getFreeCardLocation
* Date Created: Nov. 24, 2018
* Date Last Modified: Nov. 25, 2018
* Description: Default if all spaces full 
* Input parameters:
* Returns: Free array location for writing, or -1 if array is full, for deck.  
* Preconditions: -
* Postconditions: -
*************************************************************/
int getFreeCardLocation(card deck[NUMOFCARDS])
{
	for (int i = 0; i < NUMOFCARDS; i++)
	{
		if (deck[i].face != -1)
		{
			return i;
		}
	}
	return -1; 
}

/************************************************************
* Function: evaluate
* Date Created: Nov. 15, 2018
* Date Last Modified: Nov. 25, 2018
* Description: Evaluates cards to identify combination value. 
* Input parameters:
* Returns: Return an ENUM in order of value below	
* Preconditions: -
* Postconditions: -
*************************************************************/
int evaluate(card aHand[SIZEOFHAND], int PlayerIndex)
{
	int highNumIndex;
	card localHand[SIZEOFHAND];
	resetHand(localHand);
	//SORTING HAND IF COMPUTER PLAYER HAND----
	if (PlayerIndex == COMPUTER)
	{
		for (int i = NUMOFVALUES - 1; i > -1; i--) //is there a 4-of-a-kind ?
		{
			if (getCountofValue(aHand, i) == 4)
			{
				for (int j = 0; j < SIZEOFHAND; j++)
				{
					if (aHand[j].face == i)
					{
						localHand[getArrayLocation(localHand)].suit = aHand[j].suit;
						localHand[getArrayLocation(localHand)].face = aHand[j].face;
					}
				}
				for (int j = 0; j < SIZEOFHAND; j++)
				{
					if (aHand[j].face != i)
					{
						localHand[getArrayLocation(localHand)].suit = aHand[j].suit;
						localHand[getArrayLocation(localHand)].face = aHand[j].face;
					}
				}
			}
		}
		if (getArrayLocation(localHand) != -1)
		{
			for (int i = NUMOFVALUES - 1; i > -1; i--) //is there a 3-of-a-Kind?
			{
				if (getCountofValue(aHand, i) == 3)
				{
					for (int j = 0; j < SIZEOFHAND; j++)
					{
						if (aHand[j].face == i)
						{
							localHand[getArrayLocation(localHand)].suit = aHand[j].suit;
							localHand[getArrayLocation(localHand)].face = aHand[j].face;
						}
					}

					for (int i2 = NUMOFVALUES - 1; i2 > -1; i2--)
					{
						if (getCountofValue(aHand, i2) == 2)
						{
							for (int j2 = 0; j2 < SIZEOFHAND; j2++)
							{
								if (aHand[j2].face == i2)
								{
									localHand[getArrayLocation(localHand)].suit = aHand[j2].suit;
									localHand[getArrayLocation(localHand)].face = aHand[j2].face;
								}
							}
						}
					}
					int x = -1, y = -1;
					if (getArrayLocation(localHand) != -1)
					{
						for (int i3 = NUMOFVALUES - 1; i3 > -1; i3--)
						{
							if (localHand[i3].face != i)
							{
								if (x == -1)
									x = i3;
								else
									y = i3;
							}
						}
						if (localHand[x].face > localHand[y].face)
						{
							localHand[getArrayLocation(localHand)].suit = aHand[x].suit;
							localHand[getArrayLocation(localHand)].face = aHand[x].face;
							localHand[getArrayLocation(localHand)].suit = aHand[y].suit;
							localHand[getArrayLocation(localHand)].face = aHand[y].face;
						}
						else
						{
							localHand[getArrayLocation(localHand)].suit = aHand[y].suit;
							localHand[getArrayLocation(localHand)].face = aHand[y].face;
							localHand[getArrayLocation(localHand)].suit = aHand[x].suit;
							localHand[getArrayLocation(localHand)].face = aHand[x].face;
						}
					}
				}
			}
		}
		if (getArrayLocation(localHand) != -1)
		{
			for (int i = NUMOFVALUES - 1; i > -1; i--) //is there a pair?
			{
				if (getCountofValue(aHand, i) == 2)
				{
					for (int j = 0; j < SIZEOFHAND; j++)
					{
						if (aHand[j].face == i && aHand[j].face != -1)
						{
							localHand[getArrayLocation(localHand)].suit = aHand[j].suit;
							localHand[getArrayLocation(localHand)].face = aHand[j].face;
							aHand[j].suit = -1;
							aHand[j].face = -1;
						}
					}
					//Second Pair?
					for (int i2 = NUMOFVALUES - 1; i2 > -1; i2--)
					{
						if (i2 != i && getCountofValue(aHand, i2) == 2)
						{
							for (int j2 = 0; j2 < SIZEOFHAND; j2++)
							{
								if (aHand[j2].face == i2 && aHand[j2].face != -1)
								{
									localHand[getArrayLocation(localHand)].suit = aHand[j2].suit;
									localHand[getArrayLocation(localHand)].face = aHand[j2].face;
									aHand[j2].suit = -1;
									aHand[j2].face = -1;
								}
							}
						}
					}
				}
			}
		}
		while (getArrayLocation(localHand) != -1)
		{
			highNumIndex = 0;
			for (int i4 = 0; i4 < SIZEOFHAND; i4++)
			{
				if ((aHand[i4].face != -1) &&
					(aHand[i4].face > aHand[highNumIndex].face))
					highNumIndex = i4;
			}
			if (aHand[highNumIndex].face != -1)
			{
				localHand[getArrayLocation(localHand)].suit = aHand[highNumIndex].suit;
				localHand[getArrayLocation(localHand)].face = aHand[highNumIndex].face;
				aHand[highNumIndex].suit = -1;
				aHand[highNumIndex].face = -1;
			}
		}
		for (int j = 0; j < SIZEOFHAND; j++)
		{
			aHand[j].face = localHand[j].face;
			aHand[j].suit = localHand[j].suit;
		}
	}//END SORTING
	   //LOOKING FOR COMBINATIONS----
	for (int i = 1; i < NUMOFVALUES; i++) //is there a 4-of-a-kind ?
	{
		if (getCountofValue(aHand, i) == 4)
		{
			return FOURKIND; //there is a 4-of-a-kind
		}
	}
	for (int i = 1; i < NUMOFVALUES; i++) //is there a full house ? 
	{
		if (getCountofValue(aHand, i) == 3)
		{
			for (int j = 1; j < NUMOFVALUES; j++)
			{
				if ((j != i) && (getCountofValue(aHand, j) == 2))
				{
					return FULLHOUSE; //there is a fullhouse 
				}
			}
		}
	}
	for (int i = 1; i < NUMOFSUITS; i++) //is there a flush ? -- suit
	{
		if (getCountofSuit(aHand, i) == 5)
		{
			return FLUSH; //there is a flush
		}
	}
	for (int j = 1; j <= (NUMOFVALUES - SIZEOFHAND); j++) //is there a straight ? -- face
	{
		if (((getCountofValue(aHand, j) > 0)
			&& (getCountofValue(aHand, (j + 1)) > 0)
			&& (getCountofValue(aHand, (j + 2)) > 0)
			&& (getCountofValue(aHand, (j + 3)) > 0)
			&& (getCountofValue(aHand, (j + 4)) > 0)))
		{
			return STRAIGHT; //there is a STRAIGHT 
		}
	}
	for (int i = 1; i < NUMOFVALUES; i++)//is there a 3 - of - a - kind ?
	{
		if (getCountofValue(aHand, i) == 3)
		{
			return THREEKIND; //there is a 3-of-a-kind
		}
	}
	for (int i = 1; i < NUMOFVALUES; i++) //is there a pair ?
	{
		if (getCountofValue(aHand, i) == 2) // add logic 
		{
			for (int j = 1; j < NUMOFVALUES; j++)
			{
				if ((j != i) && (getCountofValue(aHand, j) == 2))
				{
					return TWOPAIR; //there is two pair
				}
			}
			return ONEPAIR; //there is a pair
		}
	}
	return NOHAND;
}

/************************************************************
* Function: ComputerTurn
* Date Created: Nov. 13, 2018
* Date Last Modified: Nov. 25, 2018
* Description: Returning how many cards were Discarded by computer/dealer. Full deck with -1 when card is taken. 
* Input parameters:
* Returns: Number of cards thrown away. 
* Preconditions: -
* Postconditions: -
*************************************************************/
int ComputerTurn(card aHand[SIZEOFHAND] /*playerComputerHand*/, card deck[NUMOFCARDS])
{
	int discard = 0;
	switch (evaluate(aHand, COMPUTER))
	{
	case ONEPAIR: //ONEPAIR: discard = 3
		discard = 3;
		break;
	case TWOPAIR: //TWOPAIR : discard = 1
		discard = 1;
		break;
	case THREEKIND: //THREEKIND : discard = 2
		discard = 2;
		break;
	case STRAIGHT: //STRAIGHT : discard = 0		
	case FLUSH: //FLUSH : discard 0 	
	case FULLHOUSE: // discard 0
		discard = 0;
		break;
	case FOURKIND: //FOURKIND : discard = 1
		discard = 1;
		break;
	case NOHAND:
	default:
		discard = 5;
		break;
	}

	for (int i = (SIZEOFHAND - discard); i < SIZEOFHAND; i++) 
	{
		aHand[i].face = deck[getFreeCardLocation(deck)].face;
		aHand[i].suit = deck[getFreeCardLocation(deck)].suit;
		deck[getFreeCardLocation(deck)].suit = -1;  
		deck[getFreeCardLocation(deck)].face = -1;

	}
	return discard;  
}

/************************************************************
* Function: doPlayerTurn
* Date Created: Nov. 13, 2018
* Date Last Modified: Nov. 25, 2018
* Description: Prompts player for cards to toss away. Doing suit before face as a flag
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void doPlayerTurn(card aHand[SIZEOFHAND], card deck[NUMOFCARDS])
{
	int num = 0, tens = 10000;

	printf("\nWhich cards to discard: ");
	scanf("%ld", &num);

	for (int m = 1; m < 6; m++)
	{
		if (((num / tens) <= 5) && ((num / tens) >= 1))
		{
			aHand[(num / tens) - 1].face = deck[getFreeCardLocation(deck)].face;
			aHand[(num / tens) - 1].suit = deck[getFreeCardLocation(deck)].suit;
			deck[getFreeCardLocation(deck)].suit = -1; 
			deck[getFreeCardLocation(deck)].face = -1;
		}
		num = num - (tens * (num / tens));
		tens = tens / 10;
	}
	return;
}

/************************************************************
* Function: displayCards
* Date Created: Nov. 19, 2018
* Date Last Modified: Nov. 25, 2018
* Description:
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void displayCards(card hand1[SIZEOFHAND], card hand2[SIZEOFHAND], int hideCompHand) /*computer hand hidden - (if '1' then, hidden)*/
{
	system("cls");
	int aColor = 0;
	int aSuit = 0; 
	card *tempHand;

	for (int p = 0; p < NUMOFPLAYERS; p++)
	{
		tempHand = (p == COMPUTER) ? (hand1) : (hand2);
		printf("                                       %s's hand \n", playernames[p]);
		for (int a = 1; a < 11; a++)
		{
			for (int b = 0; b < 5; b++)
			{
				aSuit = tempHand[b].suit;
				aColor = (aSuit == SPADE || aSuit == CLUB) ? (BLACK) : (RED);
				switch (a)
				{
				case 1:
				case 10:
					printCardTopBottom();
					break;
				case 2:
				case 9:
					if (hideCompHand == 1 && p == COMPUTER && DEBUG_MODE == 0)
						printCardBack();
					else
						printCardValue(aColor, tempHand[b].face, (a == 2) ? (0) : (1));  //0 it top, 1 is bottom
					break;
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
					if (hideCompHand == 1 && p == COMPUTER && DEBUG_MODE == 0)
						printCardBack();
					else
						printCardFiller(aColor, aSuit, a);
					break;
				default:
					break;
				}
			}
			printf("\n");
		}
	}
	printf("        1                  2                  3                   4                 5\n");
}

/************************************************************
* Function: printCardBack
* Date Created: Nov. 24, 2018
* Date Last Modified: Nov. 25, 2018
* Description: 15 chars wide with 2 spacers
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void printCardBack()
{
	text_color(GREY);
	back_color(WHITE);
	printf("#-+-+-+-+-+-+-+-#");
	text_color(WHITE);
	back_color(BLACK);
	printf("  ");
	return;
}

/************************************************************
* Function: printCardTopBottom
* Date Created: Nov. 19, 2018
* Date Last Modified: Nov. 25, 2018
* Description: 15 chars wide with 2 spacers
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void printCardTopBottom()
{
	text_color(GREY);
	back_color(WHITE);
	printf("#---------------#"); 
	text_color(WHITE);
	back_color(BLACK);
	printf("  ");
	return;
}

/************************************************************
* Function: printCardValue
* Date Created: Nov. 19, 2018
* Date Last Modified: Nov. 25, 2018
* Description:
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void printCardValue(int aColor, char initCardValue, int TopOrBottom)
{
	char CardValue;
	text_color(GREY);
	back_color(WHITE);
	printf("|  ");
	text_color(aColor);
	switch (initCardValue)
	{
	case  9: CardValue = 'J'; break;
	case 10: CardValue = 'Q'; break;
	case 11: CardValue = 'K'; break;
	case 12: CardValue = 'A'; break;
	default: CardValue = initCardValue + 50; break;
	}

	if (TopOrBottom == 0) //Top
	{
		//printf("%c          ", CardValue);
		//if (CardValue != 58) printf(" ");
		if (CardValue == 58)
			printf("10          ");
		else
			printf("%c           ", CardValue);
	}
	else
	{
		//		if (CardValue != 58) printf(" ");
		//		printf("         %c ", CardValue);
		if (CardValue == 58)
			printf("          10");
		else
			printf("           %c", CardValue);

	}
	text_color(GREY);
	printf(" |");
	text_color(WHITE);
	back_color(BLACK);
	printf("  ");

	return;
}

/************************************************************
* Function: printCardFiller
* Date Created: Nov. 19, 2018
* Date Last Modified: Nov. 25, 2018
* Description:
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void printCardFiller(int aColor, int suit, int lineNumber)
{
	text_color(GREY);
	back_color(WHITE);
	printf("|");
	text_color(aColor);
	switch (suit)
	{
	case SPADE:
		switch (lineNumber - 2)
		{
		case 1:	printf("       ^       "); break;
		case 2:	printf("      / \\      "); break;
		case 3:	printf("     /   \\     "); break;
		case 4:	printf("    (     )    "); break;
		case 5:	printf("      ) (      "); break;
		case 6:	printf("      ---      "); break;
		}
		break;
	case HEART:
		switch (lineNumber - 2)
		{
		case 1:	printf("     /\\  /\\    "); break;
		case 2:	printf("    (  \\/  )   "); break;
		case 3:	printf("     \\    /    "); break;
		case 4:	printf("      \\  /     "); break;
		case 5:	printf("       \\/      "); break;
		case 6:	printf("               "); break;
		}
		break;
	case CLUB:
		switch (lineNumber - 2)
		{
		case 1:	printf("       __      "); break;
		case 2:	printf("     _(  )_    "); break;
		case 3:	printf("    (__)(__)   "); break;
		case 4:	printf("       ||      "); break;
		case 5:	printf("      /__\\     "); break;
		case 6:	printf("               "); break;
		}
		break;
	case DIAMOND:
		switch (lineNumber - 2)
		{
		case 1:	printf("      /\\       "); break;
		case 2:	printf("     /  \\      "); break;
		case 3:	printf("    /    \\     "); break;
		case 4:	printf("    \\    /     "); break;
		case 5:	printf("     \\  /      "); break;
		case 6:	printf("      \\/       "); break;
		}
		break;
	}
	text_color(GREY);
	printf("|");
	text_color(WHITE);
	back_color(BLACK);
	printf("  ");
	return;
}
