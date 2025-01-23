// names: Samuel Oseguera, Jose Arellano, Michael_Santos, arnold rocha
// date: 1/21/25
// assignment: Reviewing Procedural Programming


// Libraries
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// declared namespace
using namespace std;

// Constants and Global variables
// Suits
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
int DECK[52];
int currentCardIndex = 0;
// game state bool
bool play = true;
// wins
int wins = 0;
// ties
int ties = 0;
// losses
int loses = 0;
string response = "";

// initializes the deck with integers between (0-51) for the cards
void initializeDeck() {
    for (int i = 0; i < 52; i++) {
        DECK[i] = i;
    }
}

// shuffles the deck of 52 cards by swapping each card against another
// utilizes srand operator as the random num gen for card selection
void shuffleDeck() {
    srand(time(0));
    for (int i = 0; i < 52; i++) {
        int index = rand() % 52;
        int temp = DECK[i];
        DECK[i] = DECK[index];
        DECK[index] = temp;
    }
}

// deals a card according to its value (0-12) and uses modulus 13 on the index
// increments currentCardIndex to move throughout the deck
int dealCard() {
    return DECK[currentCardIndex++] % 13;
}

// returns a value for card based on its rank
// cards (0-8) return values (0-8) using (+ 2)
// cards (9-12) all return a value of 10
int cardValue(int card) {
    return card < 9 ? card + 2 : 10;
}

// deals the two initial cards for the player and calculates the values
// outputs to the player a message containing their cards' rank and suit
int dealInitialPlayerCards() {
    int card1 = dealCard();
    int card2 = dealCard();
    cout << "Your cards: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] << " and " << RANKS[card2 % 13] << " of " << SUITS[card2 / 13] << endl;
    return cardValue(card1) + cardValue(card2);
}

// deals the initial card for the dealer and calculates it's value
// outputs a message containing the dealer's card's ran and suit
int dealInitialDealerCards() {
    int card1 = dealCard();
    cout << "Dealer's card: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] << endl;
    return cardValue(card1);
}

// runs the player's turn in blackjack, prompting for "hit" or "stand".
// draws a card and updates the total on "hit", ends the loop on "stand" or if total > 21.
// returns the updated total.
int playerTurn(int playerTotal) {
    while (true) {
        cout << "Your total is " << playerTotal << ". Do you want to hit or stand?" << endl;
        string action;
        getline(cin, action);
        if (action == "hit") {
            int newCard = dealCard();
            playerTotal += cardValue(newCard);
            cout << "You drew a " << RANKS[newCard % 13] << " of " << SUITS[newCard / 13] << endl;
            if (playerTotal > 21) {
                break;
            }
        } else if (action == "stand") {
            break;
        } else {
            cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
        }
    }
    return playerTotal;
}

// runs the dealers turn in blackjack and draws cards for the dealer
// ends the loop once dealerTotal >= 17 and outputs dealer's total
int dealerTurn(int dealerTotal) {
    while (dealerTotal < 17) {
        int newCard = dealCard();
        dealerTotal += cardValue(newCard);
    }
    cout << "Dealer's total is " << dealerTotal << endl;
    return dealerTotal;
}


//this void function determines the winner
//if the dealer totals is less than 21 the player wins and after it outputs you win it counts up the total of wins
//else if, they are the same total it is a tie and it counts up the total of ties
// else if players card value is more than 21 the dealer wins
void determineWinner(int playerTotal, int dealerTotal) {
    if (dealerTotal > 21 || playerTotal > dealerTotal) {
        cout << "You win!" << endl;
        wins++;
    } else if (dealerTotal == playerTotal) {
        cout << "It's a tie!" << endl;
        ties++;
    } else {
        cout << "Dealer wins!" << endl;
        loses++;
    }
}


// while true the game plays and it starts by initializing the deck and shuffles the deck from the top of the code
//will deal the player and dealer cards
//then a if statement occurs
//if playertotal is more than 21 the players loses and then it counts up the losses
//else it will ask if you would like to play again
// getline response after words
int main() {

    while (play == true){
        initializeDeck();
        shuffleDeck();
        int playerTotal = dealInitialPlayerCards();
        int dealerTotal = dealInitialDealerCards();
        playerTotal = playerTurn(playerTotal);
        if (playerTotal > 21) {
        cout << "You busted! Dealer wins." << endl;
        loses++;
        }
        else{
        dealerTotal = dealerTurn(dealerTotal);
        determineWinner(playerTotal, dealerTotal);
        }
        cout << "Play again? \n";


        getline(cin, response);
        
        //will ask if you would like to play
        if (response == "No" ){
            play = false;
        }
        else if (response == "Yes" ){
            play = true;
        }
        else if (response == "yes" ){
            play = true;
        
        }
        else if (response == "no" ){
            play = false;
        }
        else {
            cout<<"Invalid input";
        }
        cout << "Wins: " << wins << " \n" << "Loses: " << loses <<" \n" << "Ties: " << ties << "\n";
    }
    return 0;
}
