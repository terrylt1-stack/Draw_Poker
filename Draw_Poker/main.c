/*Terry Tschaekofkse
Draw_Poker.c*/

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

int const FALSE = 0;
int const TRUE = 1;

void printGreeting();
int getBet();
char getSuit();
char getRank();
void getFirstHand(int cardRank[], int cardSuit[]);
void getFinalHand(int cardRank[], int cardSuit[], int finalRank[], int finalSuit[], int ranksinHand[], int suitsinHand[]);
int analyzeHand(int ranksinHand[], int suitsinHand[]);

char keep_window_open();

int main()
{
    int bet;
    int bank = 100;
    int i;
    int cardRank[5];     // Will be one of 13 values (Ace through King)
    int cardSuit[5];     // Will be one of 4 values, (Clubs,Diamonds, Hearts, Spades)
    int finalRank[5];
    int finalSuit[5];
    int ranksinHand[13]; // Used for evaluating the final hand
    int suitsinHand[4];  // Used for evaluating the final hand
    int winnings;
    time_t t;
    char suit = ' ', rank = ' ', stillPlay = ' ';

    printGreeting();

    // Loop runs each time the user plays a hand of draw poker

    do
    {
         bet = getBet();
         srand(time(&t));
         getFirstHand(cardRank, cardSuit);
         puts("Your five cards");
         for (i = 0; i < 5; i++)
         {
              suit = getSuit(cardSuit[i]);
              rank = getRank(cardRank[i]);
              printf("Card #%d: %c%c\n", i+1, rank, suit);
         }
         /* These two arrays are used to figure out the value of
         the player's hand. However, they must be zeroed out
         in case the user plays multiple hands*/

         for (i = 0; i < 4; i++)
         {
              suitsinHand[i] = 0;
         }

         for (i = 0; i < 13; i++)
         {
              ranksinHand[i] = 0;
         }

         getFinalHand(cardRank, cardSuit, finalRank, finalSuit, ranksinHand, suitsinHand);

         puts("Your five final cards: ");

         for (i = 0; i < 5; i++)
         {
              suit = getSuit(finalSuit[i]);
              rank = getRank(finalRank[i]);
              printf("Card #%d: %c%c\n", i+1, rank, suit);
         }
         winnings = analyzeHand(ranksinHand, suitsinHand);
         printf("You won %d!\n", bet * winnings);
         bank = bank - bet + (bet * winnings);
         printf("Your bank is now %d.\n", bank);
         printf("Do you want to play again? ");
         scanf(" %c", &stillPlay);
    }while (toupper(stillPlay) == 'Y');

    keep_window_open(); // Use only if needed

    return 0;
}
char keep_window_open()
{
     char ch;
     scanf("%c", ch);
}

void printGreeting()
{
     puts("\t\tWELCOME TO THE CASINO");
     puts("\t\tHOME OF TEXT DRAW POKER\n");

     puts("Here are the rules: ");
     puts("You start with 100 credits, and you make a bet from 1 to 5 credits");
     puts("You are dealt 5 cards, and then you choose which cards to keep or discard");
     puts("You want to make the best possible hand");
     puts("Here is the table for winnings, assuming a bet of 1 credit");
     puts("Pair\t\t\t\t1 credit");
     puts("Two Pairs\t\t\t2 credits");
     puts("Three Pairs\t\t\t3 credits");
     puts("Straight\t\t\t4 credits");
     puts("Flush\t\t\t\t5 credits");
     puts("Full House\t\t\t8 credits");
     puts("Four of a Kind\t\t\t10 credits");
     puts("Straight Flush\t\t\t20 credits\n");
     puts("Have Fun!\n");
}

// Function to deal the first five cards

void getFirstHand(int cardRank[], int cardSuit[])
{
     int i, j;
     int cardDup;

     for (i = 0; i < 5; i++)
          {
               cardDup = 0;
               do
          {
               cardRank[i] = (rand() % 13);  // Card rank is one of 13
               cardSuit[i] = (rand() % 4);   // Card suit is one of 4

               // Loop to ensure each card is unique

               for (j = 0; j < i; j++)
               {
                    if ((cardRank[i] == cardRank[j]) && (cardSuit[i] == cardSuit[j]))
                    {
                    cardDup = 1;
                    }
               }
          }while (cardDup == 1);
     }
}
// Function that changes the suit integer value to a character representing the suit

char getSuit(int suit)
{
     switch (suit)
     {
     case 0:
          return('c');
     case 1:
          return('d');
     case 2:
          return('h');
     case 3:
          return('s');
     }
}

// Function that changes the rank integer value to a character representing the rank

char getRank(int rank)
{
     switch (rank)
     {
     case 0:
          return('A');
     case 1:
          return('2');
     case 2:
          return('3');
     case 3:
          return('4');
     case 4:
          return('5');
     case 5:
          return('6');
     case 6:
          return('7');
     case 7:
          return('8');
     case 8:
          return('9');
     case 9:
          return('T');
     case 10:
          return('J');
     case 11:
          return('Q');
     case 12:
          return('K');
     }
}

// Function to get the user's bet between 1 and 5

int getBet()
{
     int bet;

     do        // Will keep running until the user enters 0-5
     {
          puts("How much do you want to bet?");
          puts("Enter a number between 1 and 5, or 0 to quit the game: ");
          scanf("%d", &bet);

          if (bet >= 1 && bet <= 5)
          {
               return (bet);
          }
          else if (bet == 0)
          {
               exit (1);
          }
          else
          {
               puts("Please enter a bet from 1 through 5 or 0 to quit the game: ");
          }
     }while ((bet <0) || (bet > 5));
}

// Function reviews the final hand and determines the value of the hand

int analyzeHand(int ranksinHand[], int suitsinHand[])
{
     int num_consec = 0;
     int i, rank, suit;
     int straight = FALSE;
     int flush = FALSE;
     int four = FALSE;
     int three = FALSE;
     int pairs = 0;

     for (suit = 0; suit < 4; suit++)

          if (suitsinHand[suit] == 5)

               flush = TRUE;

          rank = 0;

          while (ranksinHand[rank] == 0)
              rank++;

               for (; rank < 13 && ranksinHand[rank]; rank++)
                    num_consec++;

               if (num_consec == 5)
               {
                    straight =TRUE;
               }
               for (rank = 0; rank < 13; rank++)
               {
                    if (ranksinHand[rank] == 4)
                       four = TRUE;
                    if (ranksinHand[rank] == 3)
                       three = TRUE;
                    if (ranksinHand[rank] == 2)
                        pairs++;
               }

               if (straight && flush)
               {
                    puts("Straight Flush\n");
                    return (20);
               }
               else if (four)
               {
                    puts("Four of a Kind\n");
                    return (10);
               }
               else if (three && pairs == 1)
               {
                    puts("Full House\n");
                    return (8);
               }
               else if (flush)
               {
                    puts("Flush\n");
                    return (5);
               }
               else if (straight)
               {
                    puts("Straight\n");
                    return (4);
               }
               else if (three)
               {
                    puts("Three of a Kind\n");
                    return (3);
               }
               else if (pairs == 2)
               {
                    puts("Two pairs\n");
                    return (2);
               }
               else if (pairs == 1)
               {
                    puts("Pair\n");
                    return (1);
               }
               else
               {
                    puts("High Card\n");
                    return (0);
               }
}

/* Function to look through each of the five cards in the first hand and asks
the user if they want to keep the card. If they say no they get a replacement card */

getFinalHand(int cardRank[], int cardSuit[], int finalRank[], int finalSuit[], int ranksinHand[], int suitsinHand[])
{
     int i, j, cardDup;
     char suit, rank, ans;

     for (i = 0; i < 5; i++)
     {
          suit = getSuit(cardSuit[i]);
          rank = getRank(cardRank[i]);
          printf("Do you want to keep card #%d: %c%c?\n", i+1, rank, suit);
          puts("Please answer Y for yes or N for no: ");
          scanf(" %c", &ans);
          if (toupper(ans) == 'Y')
          {
               finalRank[i] = cardRank[i];
               finalSuit[i] = cardSuit[i];
               ranksinHand[finalRank[i]]++;
               suitsinHand[finalSuit[i]]++;
               continue;
          }
          else if (toupper(ans) == 'N')
          {
               cardDup = 0;
               do
               {
                    cardDup = 0;
                    finalRank[i] = (rand() % 13);
                    finalSuit[i] = (rand() % 4);

                    /* First check new card against the 5 original
                    cards to avoid duplication*/

                    for (j = 0; j < 5; j++)
                    {
                         if ((finalRank[i] == cardRank[j]) && (finalSuit[i] == cardSuit[j]))
                         {
                              cardDup = 1;
                         }
                    }

                    /* Next check the new card against any newly drawn
                    cards to avoid duplication*/

                    for (j = 0; j < i; j++)
                    {
                         if ((finalRank[i] == finalRank[j]) && (finalSuit[i] == finalSuit[j]))
                         {
                              cardDup = 1;
                         }
                    }
               }while (cardDup == 1);
               ranksinHand[finalRank[i]]++;
               suitsinHand[finalSuit[i]]++;
          }
     }
}





