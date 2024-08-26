#include <iostream>
#include <string>
#include "util.hpp"

using namespace std;

enum class Team{
    White = 0, Black = 1
};

int main(){

    Game GameObject;
    Board ChessBoard;
    Team turn = Team::Black;
    string input;
    
    ChessBoard.initilize();
    ChessBoard.updateLegalMoves();

    do{
        
        turn = (turn == Team::White)? Team::Black : Team::White ;
        
        ChessBoard.printBoard();
        
        GameObject.printTurn(turn);
        
        input = GameObject.getInput(ChessBoard,turn);
        
        ChessBoard.updateBoard(input);
        ChessBoard.fileSave(input, turn);
        ChessBoard.resetSafeties();

        ChessBoard.updateLegalMoves();
        //ChessBoard.legalMovesPrinterTest();
        GameObject.updateScores(ChessBoard);        

    } while (! GameObject.isGameOver(ChessBoard,turn));
    
    ChessBoard.printBoard(); // last position
    string winner = (turn == Team::White) ? "White Won!\n": "Black Won!\n" ;
    cout << winner;


    return 0;
}