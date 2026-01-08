
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

// Defining structures
typedef enum 
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
}suits;

typedef struct 
{
    char car;
    int val;
    suits Suit;
}cards;


cards deck[52]={};

//select suit then card


void decker()
{
    int k = 0;
    for (int i=0; i <= 3; i++)
    {
        cards card;
        char s[20];
        char cards2[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
        switch(i)
        {
            case 0:
            {
                card.Suit=Hearts;
                strcpy(s,"Hearts");
                break;
            }
            case 1:
            {
                card.Suit=Diamonds;
                strcpy(s,"Diamonds");
                break;
            }
            case 2:
            {
                card.Suit=Clubs;
                strcpy(s,"Clubs");
                break;
            }
            case 3:
            {
                card.Suit=Spades;
                strcpy(s,"Spades");
                break;
            }
        }
        for( int j = 1; j <= 13; j++)
        {
            if(j<10)
                card.val = j;
            else
                card.val = 10;
            //s[strlen(s)] = cards2[i];
            //strcpy(card.car,s);
            card.car = cards2[j-1];
            deck[k] = card;
            k++;
        }
        
    }
}

/*int main()
{
    decker();
    for( int i = 0; i <= 51; i++)
    {
        char n[15];
        switch(deck[i].Suit)
        {
            case 0:
            {
                strcpy(n,"Hearts");
                break;
            }
            case 1:
            {
                strcpy(n,"Diamonds");
                break;
            }
            case 2:
            {
                strcpy(n,"Clubs");
                break;
            }
            case 3:
            {
                strcpy(n,"Spades");
                break;
            }
        }
        printf("Suit : %s Card : %c Value : %d ",n, deck[i].car, deck[i].val);
        printf("\n");
    }
    return 0;
}*/

int len = 52; //length of cards array
int playerCount = 0;
int dealerCount = 0;

int drawCard(){
    int r = (rand() % (len-0)+0);
    return(r);
}

void deleteElement(int card){
    int del = card;
    deck[del] = deck[len-1];
    len -= 1;
}

void initialDraw(){
    int i = 0, j = 0;
    //player
    for(i=0;i<2;i++){
        int drawn = drawCard();
        int card = deck[drawn].val;
        printf("Player Card drawn: %d\n",card);
        if (card == 1 && playerCount < 11)
            playerCount += 11;
        else
            playerCount += card;
        deleteElement(drawn);
    }
    //dealer
    for(j=0;j<2;j++){
        int drawn = drawCard();
        int card = deck[drawn].val;
        printf("Dealer Card drawn: %d\n",card);
        if (card == 1 && dealerCount < 11)
            dealerCount += 11;
        else
            dealerCount += card;
        deleteElement(drawn);
    }
    printf("Player's Hand: %d\nDealer's Hand: %d\n",playerCount, dealerCount);
    fflush(stdout);

}

void hit(){
    int drawn = drawCard();
    int card = deck[drawn].val;
    printf("Player Card drawn: %d\n",card);
    if (card == 1 && playerCount < 11)
        playerCount += 11;
    else
        playerCount += card;
    deleteElement(drawn);
    printf("Player count: %d\n",playerCount);
}

void stand(){
    while (dealerCount < 17){
        int drawn = drawCard();
        int card = deck[drawn].val;
        printf("Dealer Card drawn: %d\n",card);
        if (card == 1 && dealerCount < 11)
            dealerCount += 11;
        else
            dealerCount += card;
        deleteElement(drawn);
        printf("Dealer count: %d\n",dealerCount);
        if (dealerCount > 21){
            printf("Dealer busted! Player wins!\n");
            break;
        }
    }
}

int main(){
    srand(time(0));
    decker();
    initialDraw();
    char choice = ' ';

    if (playerCount == 21){
        printf("Blackjack! Dealer's turn now\n");
        choice = 's'; //player isnt supposed to play 
    }
    else{

        while (playerCount < 21){
            printf("Hit or stand(h/s)?\n"); scanf(" %c",&choice);

            if (choice == 'h')
                hit();
            else if (choice == 's')
                break;
        }
    }
    if (playerCount > 21)
        printf("Player busted! Dealer wins!\n");
    else{
        printf("Dealer's turn: \n");
        stand();

        if (dealerCount <= 21){
            if (dealerCount < playerCount)
                printf("Player wins!\n");
            else if (dealerCount > playerCount)
                printf("Dealer wins!\n");
            else
                printf("It's a tie!\n");
        }
        else
            printf("Dealer busted! Player wins!\n");
    }
    return 0;
}