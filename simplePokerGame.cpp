#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
int DECK[52];
int currentCardIndex = 0;

void initializeDeck() {
    for (int i = 0; i < 52; i++) {
        DECK[i] = i;
    }
}

void shuffleDeck() {
    srand(time(0));
    for (int i = 0; i < 52; i++) {
        int index = rand() % 52;
        int temp = DECK[i];
        DECK[i] = DECK[index];
        DECK[index] = temp;
    }
}

int dealCard() {
    return DECK[currentCardIndex++] % 13;
}

int cardValue(int card) {
    return card < 9 ? card + 2 : 10;
}

int dealInitialPlayerCards() {
    int card1 = dealCard();
    int card2 = dealCard();
    cout << "Your cards: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] << " and " << RANKS[card2 % 13] << " of " << SUITS[card2 / 13] << endl;
    return cardValue(card1) + cardValue(card2);
}

int dealInitialDealerCards() {
    int card1 = dealCard();
    cout << "Dealer's card: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] << endl;
    return cardValue(card1);
}

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

int dealerTurn(int dealerTotal) {
    while (dealerTotal < 17) {
        int newCard = dealCard();
        dealerTotal += cardValue(newCard);
    }
    cout << "Dealer's total is " << dealerTotal << endl;
    return dealerTotal;
}

void determineWinner(int playerTotal, int dealerTotal) {
    if (dealerTotal > 21 || playerTotal > dealerTotal) {
        cout << "You win!" << endl;
    } else if (dealerTotal == playerTotal) {
        cout << "It's a tie!" << endl;
    } else {
        cout << "Dealer wins!" << endl;
    }
}

int main() {
    initializeDeck();
    shuffleDeck();
  
    int playerTotal = dealInitialPlayerCards();
    int dealerTotal = dealInitialDealerCards();
  
    playerTotal = playerTurn(playerTotal);
    if (playerTotal > 21) {
      cout << "You busted! Dealer wins." << endl;
      return 0;
    }
    dealerTotal = dealerTurn(dealerTotal);
    determineWinner(playerTotal, dealerTotal);
  
    return 0;
}
