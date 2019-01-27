#ifndef POKER_H
#define POKER_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <fcntl.h>
#include <io.h>

#define NUMOFSUITS 4
#define NUMOFVALUES 13
#define NUMOFPLAYERS 2 
#define NUMOFCARDS 52
#define SIZEOFHAND 5
#define COMPUTER 0
#define PLAYER 1
#define DEBUG_MODE 0 //For debug (see computer boats for faster debugging)
//declarations

enum colors { BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE, GREY = 60 };
enum game_statuses { READY, RULES, PLAYGAME, EXIT };
enum suits { SPADE, HEART, CLUB, DIAMOND };
enum score { NOHAND, ONEPAIR, TWOPAIR, THREEKIND, STRAIGHT, FLUSH, FULLHOUSE, FOURKIND };
char playernames[NUMOFPLAYERS][100]; //NUMOFPLAYERS

typedef struct card
{
	int suit;
	int face;
} card;
struct card deck[NUMOFCARDS];
card p1hand[SIZEOFHAND];  //Dealer
card p2hand[SIZEOFHAND];  //Player

void playGame(card deck[NUMOFCARDS], card p1hand[SIZEOFHAND], card p2hand[SIZEOFHAND], const char *suit[NUMOFSUITS], const char *face[NUMOFCARDS]);
void dealHand(card wDeck[NUMOFCARDS], const char *wFace[], const char *wSuit[], card p1hand[SIZEOFHAND], card p2hand[SIZEOFHAND]);
void getPlayerName(char playername[][100]);
void resetDeck(card deck[NUMOFCARDS]);
void resetHand(int hand[NUMOFPLAYERS][SIZEOFHAND]);
void dealHand(card wDeck[NUMOFCARDS], const char *wFace[], const char *wSuit[], card p1hand[SIZEOFHAND], card p2hand[SIZEOFHAND]);
void shuffleDeck(card wDeck[NUMOFCARDS]);
int evaluate(card aHand[SIZEOFHAND], int PlayerIndex);
int getArrayLocation(card localHand[SIZEOFHAND]);
int getFreeCardLocation(card deck[NUMOFCARDS]);
int getHighestCardValue(card aHand[SIZEOFHAND]);
int getCountofValue(card aHand[SIZEOFHAND], int Value);
int ComputerTurn(card aHand[SIZEOFHAND], card deck[NUMOFCARDS]);
void doPlayerTurn(card aHand[SIZEOFHAND], card deck[NUMOFCARDS]);
void declareWinner(card hand1[SIZEOFHAND], card hand2[SIZEOFHAND]);
void writeHandCombination(int combo);

void displayCards(card p1hand[SIZEOFHAND], card p2hand[SIZEOFHAND], int hideCompHand); /*computer hand hidden - if '1' hidden*/
void printCardBack();
void printCardTopBottom();
void printCardValue(int aColor, char CardValue, int TopOrBottom);
void printCardFiller(int aColor, int suit, int lineNumber);

#endif
