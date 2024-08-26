#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "util.hpp"

#define BOARDLIMITMAX 8
#define BOARDLIMITMIN -1
#define EMPTYCELL nullptr

using namespace std;

enum class PiecePoints{
    Queen = 9, Rook = 5, Knight = 3, Bishop = 3, Pawn = 1, King = 0
    //king's point must be 0, because of updatescores() function.
};
enum class Team{
    White = 0, Black = 1
};
enum class PieceType{
    King = 'K',
    Queen = 'Q',
    Rook = 'R',
    Knight = 'N',
    Bishop = 'B',
    Pawn = 'P'
};

Game::Game(const int wScore,const int bScore): whiteScore(wScore), blackScore(bScore){/*intentionally left blank*/}

const int Game::getScore(Team team) const{
    switch (team){
    case Team::White:
        return whiteScore;
    case Team::Black:
        return blackScore;
    }
}

void Game::printTurn(const Team turn) const{

    cout << "[White's Score : " << whiteScore << " | " << "Black's Score : " << blackScore << ']'<< endl;

    string message = (turn == Team::White) ? "[White's turn]\n": "[Black's turn]\n" ;
    cout << message;
}


void Game::updateScores(const Board& currBoard){

    whiteScore = 0;
    blackScore = 0;
    Piece* p = EMPTYCELL;

    for (int r = 0; r < BOARDLIMITMAX; r++){
        for (int f = 0; f < BOARDLIMITMAX; f++){
            p = currBoard.allPieces[r][f];
            if (p != EMPTYCELL){
                (p->team == Team::White) ? whiteScore += (int)(p->point) : blackScore += (int)(p->point) ;
                
                if(p->isSafe() == false){
                    (p->team == Team::White) ? whiteScore -= 0.50 : blackScore -= 0.50 ;
                }
                
            }
        }
    }
}

bool Game::invalidInput(const string input,const Board& currentBoard,const Team turn) const{

    if (input.size() == 4){

        bool condt1 = input[0] >= 'a' && input[0] <= 'h';
        bool condt2 = input[1] >= '1' && input[1] <= '8';
        bool condt3 = input[2] >= 'a' && input[2] <= 'h';
        bool condt4 = input[3] >= '1' && input[3] <= '8';

        // input format is now being checked if its a valid input and a valid move
        if (condt1 && condt2 && condt3 && condt4){
            //the indexes correnspond to the coordinates
            int pFile = input[0] - 'a' ; //pieceFile
            int pRank = 7 - (input[1] - '1') ; 
            int mFile = input[2] - 'a' ; //moveFile
            int mRank = 7 - (input[3] - '1') ;

            if (currentBoard.allPieces[pRank][pFile] != EMPTYCELL){ //check if its not a nullptr(AKA emptycell)
                Piece currPiece = *(currentBoard.allPieces[pRank][pFile]);

                if (currPiece.team != turn) return true; // white player can move white pieces of course
                
                if (! currPiece.LegalMoves.empty()){
                    for(const vector<int>& move : currPiece.LegalMoves){
                        if (move[0] == mRank && move[1] == mFile){

                            
                            

                            return false; //after all that checks, its decided to be not a invalid move
                        }
                    }
                }
            }
        }
    }
    return true;
}

const string Game::getInput(const Board& currentBoard,const Team turn) const{

    string input;
    bool invalidinput;
    
    do{
        cout << "Enter Your Move: ";
        getline(cin, input, '\n');
        

        if (input == "suggest"){
            cout << "Suggestion is : " ;
            cout << getSuggest(currentBoard,turn) << endl;
            invalidinput = true;
        }else {
            invalidinput = invalidInput(input, currentBoard,turn);

            if(invalidinput){
            cout << "Invalid Input or Move!!! Try Again ('a2a3', 'suggest')\n" ;
            }

        }
    } while (invalidinput);
    
    return input;
}

const string Game::getSuggest(const Board& currentBoard,const Team turn) const{

    Board tempBoard;
    Game tempGame;
    Piece * p = EMPTYCELL;
    string tempsuggest;
    string suggest = "aaaa" ;
    double bestDiff = (turn == Team::White) ? this->whiteScore - this->blackScore : this->blackScore - this->whiteScore ;

    for (int r = 0; r < BOARDLIMITMAX; r++){
        for (int f = 0; f < BOARDLIMITMAX; f++){
            
            p = currentBoard.allPieces[r][f];
            if (p != EMPTYCELL && p->team == turn && ! p->LegalMoves.empty()){
                
                for (const vector<int>& move : p->LegalMoves){
                    tempGame = *this;
                    tempBoard = currentBoard;
                    //convert coordinates to the notation to use updateboard
                    tempsuggest = "aaaa";
                    tempsuggest[0] = (char)((int)(p->coordinates[1]) + 'a') ;
                    tempsuggest[1] = (char)(7- p->coordinates[0] + '1') ;
                    tempsuggest[2] = (char)((int)(move[1]) + 'a');
                    tempsuggest[3] = (char)(7 -move[0] + '1') ;
                    
                    tempBoard.updateLegalMoves();
                    tempBoard.updateBoard(tempsuggest);
                    tempBoard.resetSafeties();
                    tempBoard.updateLegalMoves(); // updates safety properties
                    tempGame.updateScores(tempBoard);
                    
                    if (tempGame.isGameOver(tempBoard,turn)){
                        return tempsuggest;
                    }
                    

                    for (int tR = 0; tR < BOARDLIMITMAX; tR++){
                        for (int tF = 0; tF < BOARDLIMITMAX; tF++){
                            if (tempBoard.allPieces[tR][tF] != EMPTYCELL && tempBoard.allPieces[tR][tF]->type == PieceType::King){
                                if (tempBoard.allPieces[tR][tF]->team != turn && !tempBoard.allPieces[tR][tF]->isSafe()){
                                    tempGame.CheckAlert(turn);
                                }
                            }   
                        } 
                    }
                    double tempDiff = (turn == Team::White) ? tempGame.whiteScore - tempGame.blackScore : tempGame.blackScore - tempGame.whiteScore ;
                    double score = (turn == Team::White) ? tempGame.whiteScore : tempGame.blackScore ;
                    if (score + tempDiff >= bestDiff){
                        bestDiff = tempDiff;
                        suggest = tempsuggest;
                    }
                    
                }
            }
        }
    }
    return suggest;
}

bool Game::isGameOver(const Board& currBoard,const Team turn)const{
    //son oynayanin takim geliyor buraya turn olarak
    const Piece* p = EMPTYCELL;

    for (int r = 0; r < BOARDLIMITMAX; r++){
        for (int f = 0; f < BOARDLIMITMAX; f++){
            p = currBoard.allPieces[r][f];
            if (p != EMPTYCELL && p->type == PieceType::King && p->team != turn){ 
                if (p->LegalMoves.empty() && p->isSafe() == false){
                    // if the oppenent king is under attack and also has no valid move
                    // its needed to check if the attackers can be beaten.
                    if (!currBoard.checkBeatAttacker(turn)){
                        return true;
                    }
                }   
            }
        }   
    }
    return false;
}

void Game::CheckAlert(const Team turn){ //dont use this function, if you are not me!
    (turn == Team::White) ? blackScore = -100 : whiteScore = -100;
}

Board::Board(){
    //empty boxes will be nullptr
    allPieces.resize(8, vector<Piece*>(8, EMPTYCELL));
}

Board::~Board(){
    for(vector<Piece*>& PiecesInARank : allPieces){
        for(Piece* piece : PiecesInARank){
            if (piece != EMPTYCELL){
                delete piece;
            }
        }
    }
}

void Board::operator =(const Board& other){
    //replacing emptycells(nullptrs) into the pieces if there is one
    Piece * p = EMPTYCELL;

    for (int r = 0; r < BOARDLIMITMAX; r++){
        for (int f = 0; f < BOARDLIMITMAX; f++){
            if (other.allPieces[r][f] != EMPTYCELL){
                p = other.allPieces[r][f];
                this->allPieces[r][f] = new Piece(p->team, p->type, p->coordinates, p->point, p->isSafe(), p->symbol);
            }else {
                this->allPieces[r][f] = EMPTYCELL;//not really necessary because default constructor assigns all cell empty
            }
        }
    }
}

void Board::initilize(){

    //for pawns
    for (int i = 0; i < BOARDLIMITMAX; i++){ 
        // for black pieces 
        allPieces[1][i] =
        new Piece(Team::Black,PieceType::Pawn,{1,i},PiecePoints::Pawn,true,'p'); 
        
        // for white pieces
        allPieces[6][i] =
        new Piece(Team::White,PieceType::Pawn,{6,i},PiecePoints::Pawn,true,'P');
    }

    //for some test purposes. spawning a piece at some place on the board
    
    //delete allPieces[4][4];
    //allPieces[4][4] = new Piece(Team::Black,PieceType::Bishop,{4,4},PiecePoints::Bishop,true,'b');
    //allPieces[1][0] = EMPTYCELL;

    allPieces[0][0] = new Piece(Team::Black,PieceType::Rook,{0,0},PiecePoints::Rook,true,'r');
    allPieces[0][1] = new Piece(Team::Black,PieceType::Knight,{0,1},PiecePoints::Knight,true,'n');
    allPieces[0][2] = new Piece(Team::Black,PieceType::Bishop,{0,2},PiecePoints::Bishop,true,'b');
    allPieces[0][3] = new Piece(Team::Black,PieceType::Queen,{0,3},PiecePoints::Queen,true,'q'); 
    allPieces[0][4] = new Piece(Team::Black,PieceType::King,{0,4},PiecePoints::King,true,'k'); 
    allPieces[0][5] = new Piece(Team::Black,PieceType::Bishop,{0,5},PiecePoints::Bishop,true,'b'); 
    allPieces[0][6] = new Piece(Team::Black,PieceType::Knight,{0,6},PiecePoints::Knight,true,'n');
    allPieces[0][7] = new Piece(Team::Black,PieceType::Rook,{0,7},PiecePoints::Rook,true,'r');

    allPieces[7][0] = new Piece(Team::White,PieceType::Rook,{7,0},PiecePoints::Rook,true,'R');
    allPieces[7][1] = new Piece(Team::White,PieceType::Knight,{7,1},PiecePoints::Knight,true,'N');
    allPieces[7][2] = new Piece(Team::White,PieceType::Bishop,{7,2},PiecePoints::Bishop,true,'B');
    allPieces[7][3] = new Piece(Team::White,PieceType::Queen,{7,3},PiecePoints::Queen,true,'Q'); 
    allPieces[7][4] = new Piece(Team::White,PieceType::King,{7,4},PiecePoints::King,true,'K'); 
    allPieces[7][5] = new Piece(Team::White,PieceType::Bishop,{7,5},PiecePoints::Bishop,true,'B'); 
    allPieces[7][6] = new Piece(Team::White,PieceType::Knight,{7,6},PiecePoints::Knight,true,'N');
    allPieces[7][7] = new Piece(Team::White,PieceType::Rook,{7,7},PiecePoints::Rook,true,'R');
}

void Board::fileSave(const string move,const Team team)const{

    ofstream ofile;
    ofile.open("saves.txt", ios::app);

    if (!(ofile.is_open())){
        cout << "file cant open!!\n" ;
        return;
    }

    char symbol;
    for (int rank = 0; rank < BOARDLIMITMAX; rank++){
        ofile << (8 - rank) << " | " ;
        for (int file = 0; file < BOARDLIMITMAX; file++){
                symbol = (allPieces[rank][file] == EMPTYCELL) ? '.': allPieces[rank][file]->symbol;
                ofile << symbol << ' ';
            }
        ofile << endl;
        }
    ofile << "  - - - - - - - - -\n" << "    a b c d e f g h \n" ;

    string turn = (team == Team::White) ? "White Move: ": "Blak Move: " ;

    ofile << turn << move << "\n\n\n\n";

    ofile.close();

}

void Board::printBoard()const{
    char symbol;
    cout << "\n\n\n\n" ;
    for (int rank = 0; rank < BOARDLIMITMAX; rank++){
        cout << (8 - rank) << " | " ;
        for (int file = 0; file < BOARDLIMITMAX; file++){
                symbol = (this->allPieces[rank][file] == EMPTYCELL) ? '.': this->allPieces[rank][file]->symbol;
                cout << symbol << ' ';
            }
        cout << endl;
        }
    cout << "  - - - - - - - - -\n" << "    a b c d e f g h \n" ;
}

void Board::updateLegalMoves()const{

    int king1R = -1,king1F,king2R,king2F;
    Team king1Team,king2Team;
    for (int r = 0; r < BOARDLIMITMAX; r++){
        for (int f = 0; f < BOARDLIMITMAX; f++){
            if (allPieces[r][f] != EMPTYCELL){
                //cout << (char)allPieces[r][f]->type << '\n';
                if (!allPieces[r][f]->LegalMoves.empty())
                {
                    allPieces[r][f]->LegalMoves.clear();
                }
                switch (allPieces[r][f]->type)
                {
                case PieceType::King:
                    if (king1R == -1){
                        king1R = r;
                        king1F = f;
                        king1Team = allPieces[r][f]->team;
                    }else{
                        king2R = r;
                        king2F = f;
                        king2Team = allPieces[r][f]->team;
                    }
                    kingLegalMove(allPieces[r][f]); //done
                    break;
                
                case PieceType::Queen:
                    queenLegalMove(allPieces[r][f]); //done
                    break;
                
                case PieceType::Rook:
                    rookLegalMove(allPieces[r][f]); //done
                    break;
                
                case PieceType::Knight:
                    knightLegalMove(allPieces[r][f]); //done
                    break;
                
                case PieceType::Bishop:
                    bishopLegalMove(allPieces[r][f]); //done
                    break;
                
                case PieceType::Pawn:
                    pawnLegalMove(allPieces[r][f]); //done
                    break;
                default:
                    cout << "something wrong with updatelogalmoves function!!\n" ;
                    break;
                }
            }
        }
    }
    // we need to keep the kings from suicide :D
    Piece * p = nullptr;
    Piece * king1 = allPieces[king1R][king1F];
    Piece * king2 = allPieces[king2R][king2F];
    for (int r = 0; r < BOARDLIMITMAX; r++){
        for (int f = 0; f < BOARDLIMITMAX; f++){
            if (allPieces[r][f] != EMPTYCELL){

                p = allPieces[r][f];
                if (! king1->LegalMoves.empty() && p->team != king1Team && ! p->LegalMoves.empty()){

                    for (const vector<int> moves : p->LegalMoves){
                        int index = 0;
                        for (const vector<int> kingMoves : king1->LegalMoves){
                            if (kingMoves == moves){
                                king1->LegalMoves.erase(king1->LegalMoves.begin() + index);
                            }  
                            index++; 
                        }
                    }
                }else if(! king2->LegalMoves.empty() && p->team != king2Team && ! p->LegalMoves.empty()){
                    
                    for (const vector<int> moves : p->LegalMoves){
                        int index = 0;
                        for (const vector<int> kingMoves : king2->LegalMoves){
                            if (kingMoves == moves){
                                king2->LegalMoves.erase(king2->LegalMoves.begin() + index);
                            }   
                            index++;
                        }
                    }
                }
            }
        }
    }
}

void Board::kingLegalMove(Piece* p)const{

    int r,f;
    for (int i = -1; i <=1 ; i++){
        r = p->coordinates[0] + i;
        if (r > BOARDLIMITMIN && r < BOARDLIMITMAX){
            for (int x = -1; x <= 1; x++){
                f = p->coordinates[1] + x;
                if (f > BOARDLIMITMIN && f < BOARDLIMITMAX){
                    if (allPieces[r][f] == EMPTYCELL){
                        p->LegalMoves.push_back(vector<int> {r,f});
                    }else if(allPieces[r][f]->team != p->team){
                        p->LegalMoves.push_back(vector<int> {r,f});
                        allPieces[r][f]->updateIsSafe(false);
                    }
                }
            }
        }
    }
}

void Board::queenLegalMove(Piece* p)const{
    rookLegalMove(p);
    bishopLegalMove(p);
}

void Board::rookLegalMove(Piece* p)const{
    const int rank = p->coordinates[0];
    const int file = p->coordinates[1];

    bool stopper;
    for (int i = 1, stopper = true; i < 8 && stopper; i++){ //downwards
        if (isAValidCell(rank + i,file)){
            if (isEmptyCell(rank +i,file)){
                p->LegalMoves.push_back(vector<int> {rank + i,file});
            }else if(allPieces[rank +i ][file]->team != p->team ){
                p->LegalMoves.push_back(vector<int> {rank + i,file});
                allPieces[rank +i][file]->updateIsSafe(false);
                stopper = false;
            }else{
                stopper = false;
            }
        }else{
            stopper = false;
        }
    }
    for (int i = -1, stopper = true; i > -8 && stopper; i--){ //upwards
        if (isAValidCell(rank + i,file)){
            if (isEmptyCell(rank +i,file)){
                p->LegalMoves.push_back(vector<int> {rank + i,file});
            }else if(allPieces[rank +i ][file]->team != p->team  ){
                p->LegalMoves.push_back(vector<int> {rank + i,file});
                allPieces[rank +i][file]->updateIsSafe(false);
                stopper = false;
            }else{
                stopper = false;
            }
        }else{
            stopper = false;
        }
    }
    for (int i = 1, stopper = true; i < 8 && stopper; i++){ //to the right
        if (isAValidCell(rank,file+i)){
            if (isEmptyCell(rank,file+i)){
                p->LegalMoves.push_back(vector<int> {rank,file +i });
            }else if(allPieces[rank][file + i]->team != p->team  ){
                p->LegalMoves.push_back(vector<int> {rank,file +i });
                allPieces[rank][file + i]->updateIsSafe(false);
                stopper = false;
            }else{
                stopper = false;
            }
        }else{
            stopper = false;
        }
    }
    for (int i = -1, stopper = true; i > -8 && stopper; i--){ //to the left
        if (isAValidCell(rank,file+i)){
            if (isEmptyCell(rank,file+i)){
                p->LegalMoves.push_back(vector<int> {rank,file +i });
            }else if(allPieces[rank][file + i]->team != p->team  ){
                p->LegalMoves.push_back(vector<int> {rank,file +i });
                allPieces[rank][file + i]->updateIsSafe(false);
                stopper = false;
            }else{
                stopper = false;
            }
        }else{
            stopper = false;
        }
    }

}

void Board::knightLegalMove(Piece* p)const{
    const int rank = p->coordinates[0];
    const int file = p->coordinates[1];

    if (isAValidCell(rank-2,file-1)){
        if (isEmptyCell(rank-2,file-1)){
            p->LegalMoves.push_back(vector<int> {rank-2,file -1});
        }else if(allPieces[rank-2][file-1]->team != p->team){
            p->LegalMoves.push_back(vector<int> {rank-2,file -1});
            allPieces[rank-2][file-1]->updateIsSafe(false);
        }
    }
    if (isAValidCell(rank-2,file+1)){
        if (isEmptyCell(rank-2,file+1)){
            p->LegalMoves.push_back(vector<int> {rank-2,file+1});
        }else if (allPieces[rank-2][file+1]->team != p->team){
            p->LegalMoves.push_back(vector<int> {rank-2,file +1});
            allPieces[rank-2][file+1]->updateIsSafe(false);
        }
    }
    if (isAValidCell(rank+2,file-1)){
        if (isEmptyCell(rank+2,file-1)){
            p->LegalMoves.push_back(vector<int> {rank+2,file -1});
        }else if (allPieces[rank+2][file-1]->team != p->team){
            p->LegalMoves.push_back(vector<int> {rank+2,file -1});
            allPieces[rank+2][file-1]->updateIsSafe(false);
        }
    }
    if (isAValidCell(rank+2,file+1)){
        if (isEmptyCell(rank+2,file+1)){
            p->LegalMoves.push_back(vector<int> {rank+2,file +1});
        }else if (allPieces[rank+2][file+1]->team != p->team){
            p->LegalMoves.push_back(vector<int> {rank+2,file +1});
            allPieces[rank+2][file+1]->updateIsSafe(false);
        }
    }
    
    if (isAValidCell(rank-1,file-2)){
        if (isEmptyCell(rank-1,file-2)){
            p->LegalMoves.push_back(vector<int> {rank-1,file -2});
        }else if (allPieces[rank-1][file-2]->team != p->team){
            p->LegalMoves.push_back(vector<int> {rank-1,file -2});
            allPieces[rank-1][file-2]->updateIsSafe(false);
        }
    }
    if (isAValidCell(rank-1,file+2)){
        if (isEmptyCell(rank-1,file+2)){
            p->LegalMoves.push_back(vector<int> {rank-1,file +2});
        }else if (allPieces[rank-1][file+2]->team != p->team){
            p->LegalMoves.push_back(vector<int> {rank-1,file +2});
            allPieces[rank-1][file+2]->updateIsSafe(false);
        }
    }
    if (isAValidCell(rank+1,file-2)){
        if (isEmptyCell(rank+1,file-2)){
            p->LegalMoves.push_back(vector<int> {rank+1,file -2});
        }else if (allPieces[rank+1][file-2]->team != p->team){
            p->LegalMoves.push_back(vector<int> {rank+1,file -2});
            allPieces[rank+1][file-2]->updateIsSafe(false);
        }
    }
    if (isAValidCell(rank+1,file+2)){
        if (isEmptyCell(rank+1,file+2)){
            p->LegalMoves.push_back(vector<int> {rank+1,file +2});
        }else if (allPieces[rank+1][file+2]->team != p->team){
            p->LegalMoves.push_back(vector<int> {rank+1,file +2});
            allPieces[rank+1][file+2]->updateIsSafe(false);
        }
    }
}

void Board::bishopLegalMove(Piece* p)const{
    const int rank = p->coordinates[0];
    const int file = p->coordinates[1];
    bool stopper;

    for (int i = 1, stopper=true; i < 8 && stopper; i++){ //to the north-west
        if (isAValidCell(rank - i,file -i)){
            if (isEmptyCell(rank - i,file -i)){
                p->LegalMoves.push_back(vector<int> {rank-i,file-i});
            }else if(allPieces[rank -i][file - i]->team != p->team){
                p->LegalMoves.push_back(vector<int> {rank - i,file -i});
                allPieces[rank -i][file -i]->updateIsSafe(false);
                stopper = false;
            }else {
                stopper = false;
            }
        }else{
            stopper = false;
        }
    }
    for (int i = 1, stopper=true; i < 8 && stopper; i++){ //to the north-east
        if (isAValidCell(rank - i,file +i)){
            if (isEmptyCell(rank - i,file +i)){
                p->LegalMoves.push_back(vector<int> {rank-i,file+i});
            }else if(allPieces[rank -i][file + i]->team != p->team){
                p->LegalMoves.push_back(vector<int> {rank - i,file +i});
                allPieces[rank -i][file +i]->updateIsSafe(false);
                stopper = false;
            }else {
                stopper = false;
            }
        }else{
            stopper = false;
        }
    }
    for (int i = 1, stopper=true; i < 8 && stopper; i++){ //to the south-west
        if (isAValidCell(rank + i,file -i)){
            if (isEmptyCell(rank + i,file -i)){
                p->LegalMoves.push_back(vector<int> {rank+i,file-i});
            }else if(allPieces[rank +i][file - i]->team != p->team){
                p->LegalMoves.push_back(vector<int> {rank + i,file -i});
                allPieces[rank +i][file -i]->updateIsSafe(false);
                stopper = false;
            }else {
                stopper = false;
            }
        }else{
            stopper = false;
        }
    }
    for (int i = 1, stopper=true; i < 8 && stopper; i++){ //to the south-west
        if (isAValidCell(rank + i,file +i)){
            if (isEmptyCell(rank + i,file +i)){
                p->LegalMoves.push_back(vector<int> {rank + i,file + i});
            }else if(allPieces[rank +i][file + i]->team != p->team){
                p->LegalMoves.push_back(vector<int> {rank + i,file + i});
                allPieces[rank +i][file + i]->updateIsSafe(false);
                stopper = false;
            }else {
                stopper = false;
            }
        }else{
            stopper = false;
        }
    }
    
}

void Board::pawnLegalMove(Piece* p)const{

    int rank = p->coordinates[0];
    int file = p->coordinates[1];
    if(p->team == Team::Black){
        //valid for all black pawns
        if(isAValidCell(rank +1)){
            if(isEmptyCell(rank+1,file)){
                p->LegalMoves.push_back(vector<int> {rank +1, file});
            }
            //attacks on an oppenent piece
            if (isAValidCell(rank,file -1) &&(!isEmptyCell(rank+1,file-1) && allPieces[rank +1][file -1 ]->team == Team::White)){
                p->LegalMoves.push_back(vector<int> {rank +1 , file -1});
                allPieces[rank+1][file-1]->updateIsSafe(false);
            }
            if (isAValidCell(rank,file +1)&& (!isEmptyCell(rank+1,file+1) && allPieces[rank + 1][file + 1 ]->team == Team::White)){
                p->LegalMoves.push_back(vector<int> {rank +1 , file +1});
                allPieces[rank+1][file+1]->updateIsSafe(false);
            }
        }
        //the first move of the pawn
        if (rank == 1 && isEmptyCell(3,file) && isEmptyCell(2,file)){ 
            p->LegalMoves.push_back(vector<int> {3,file});
        }
        
    }else { //white pawn
        //valid for all white pawns
        if(isAValidCell(rank -1)){
            if(isEmptyCell(rank -1,file)){
                p->LegalMoves.push_back(vector<int> {rank -1, file});
            }
            //attack on an black piece
            if (isAValidCell(rank,file -1) && (!isEmptyCell(rank -1,file-1) && allPieces[rank -1][file -1 ]->team == Team::Black)){
                p->LegalMoves.push_back(vector<int> {rank -1 , file -1});
                allPieces[rank-1][file-1]->updateIsSafe(false);
            }
            if (isAValidCell(rank,file + 1) && (!isEmptyCell(rank -1,file+1) && allPieces[rank - 1][file + 1 ]->team == Team::Black)){
                p->LegalMoves.push_back(vector<int> {rank -1 , file +1});
                allPieces[rank-1][file+1]->updateIsSafe(false);
            }
        }
        //the first move of the pawn
        if (rank == 6 && isEmptyCell(4,file) && isEmptyCell(5,file)){ 
                    p->LegalMoves.push_back(vector<int> {4,file});
        }   
    }
}

void Board::legalMovesPrinterTest()const{

    for (int r = 0; r < BOARDLIMITMAX; r++){
        for (int f = 0; f < BOARDLIMITMAX; f++){

            if(allPieces[r][f] != EMPTYCELL){

                cout << (char)allPieces[r][f]->type << " "<< (char)('a' +(int)(allPieces[r][f]->coordinates[1])) 
                << 8- (int)allPieces[r][f]->coordinates[0] << ' ' <<allPieces[r][f]->isSafe() << " : " ;

                if (! allPieces[r][f]->LegalMoves.empty()){
                    for (const vector<int> moves : allPieces[r][f]->LegalMoves){
                        cout <<(char)('a' + moves[1]) << 8 - moves[0]<< " / " ;
                    }
                    cout << "\n";
                }else{
                    cout << "nolegalmovesyet" << endl;
                }
            }else{
                cout << "empty cell!!\n";
            }
        }   
    }
}

bool Board::isAValidCell(const int r,const int f)const{
    if (r <= BOARDLIMITMIN || r >= BOARDLIMITMAX) return false;
    if (f <= BOARDLIMITMIN || f >= BOARDLIMITMAX) return false;

    return true;
}

bool Board::isEmptyCell(const int r,const int f)const{
    return (allPieces[r][f] == EMPTYCELL);
}

void Board::updateBoard(const string& input){
    
    int pFile = input[0] - 'a' ; //pieceFile
    int pRank = 7 - (input[1] - '1'); 
    int mFile = input[2] - 'a' ; //moveFile
    int mRank = 7 - (input[3] - '1');

    //cout << pRank << pFile << mRank << mFile << '\n' ;
    Piece *p = allPieces[pRank][pFile];
    if (allPieces[mRank][mFile] == EMPTYCELL){
        
        allPieces[mRank][mFile] = new Piece(p->team,p->type,{mRank,mFile},p->point,p->safety,p->symbol);
        delete allPieces[pRank][pFile];
        allPieces[pRank][pFile] = EMPTYCELL;

    }else {
        delete allPieces[mRank][mFile];
        allPieces[mRank][mFile] = new Piece(p->team,p->type,{mRank,mFile},p->point,p->safety,p->symbol);
        delete allPieces[pRank][pFile];
        allPieces[pRank][pFile] = EMPTYCELL;
    }
    
}

void Board::resetSafeties()const{
    for (int r = 0; r < BOARDLIMITMAX; r++){
        for (int f = 0; f < BOARDLIMITMAX; f++){
            if(allPieces[r][f] != EMPTYCELL){
                allPieces[r][f]->updateIsSafe(true);
            }
        }
    }
}

bool Board::checkBeatAttacker(const Team turn)const{
    //son oynayanin takimi turn olarak geliyor
    //iterata all pieces and their all legalmoves
    //simulate the game with a legalmove
    //if there is at least one move which defends the king return true

    Board tempBoard;
    
    //tempBoard.printBoard(); //for test purposes. assignment overload works !!
    Piece * p = EMPTYCELL;
    string tempInput;
    
    for (int r = 0; r < BOARDLIMITMAX; r++){
        for (int f = 0; f < BOARDLIMITMAX; f++){
            
            p = allPieces[r][f];
            if (p != EMPTYCELL && p->team != turn && ! p->LegalMoves.empty()){
                
                for (const vector<int>& move : p->LegalMoves){

                    tempBoard = (*this);
                    //convert coordinates to the notation to use updateboard
                    tempInput = "aaaa";
                    tempInput[0] = (char)((int)(p->coordinates[1]) + 'a') ;
                    tempInput[1] = (char)(7- p->coordinates[0] + '1') ;
                    tempInput[2] = (char)((int)(move[1]) + 'a');
                    tempInput[3] = (char)(7 -move[0] + '1') ;
                    
                    tempBoard.updateLegalMoves();
                    tempBoard.updateBoard(tempInput);
                    tempBoard.resetSafeties();
                    tempBoard.updateLegalMoves(); // updates safety properties
                    //tempBoard.printBoard();
                    
                    //move simulated and next legal moves calculated
                    //checking if the opponent king is still underattack
                    //if not so return true. that means attacker can be beaten
                    for (int tR = 0; tR < BOARDLIMITMAX; tR++){
                        for (int tF = 0; tF < BOARDLIMITMAX; tF++){
                            if (tempBoard.allPieces[tR][tF] != EMPTYCELL && tempBoard.allPieces[tR][tF]->type == PieceType::King){
                                if (tempBoard.allPieces[tR][tF]->team != turn && tempBoard.allPieces[tR][tF]->isSafe()){
                                    return true;
                                }
                            }   
                        } 
                    }
                }
            }
        }
    }
    return false;
}



Piece::Piece(Team _team,PieceType _type,vector<int> _coordinates,PiecePoints _point,bool _isSafe,char _symbol):
    team(_team), type(_type), point(_point), safety(_isSafe), symbol(_symbol){
        coordinates.push_back(_coordinates[0]);
        coordinates.push_back(_coordinates[1]);     
}

bool Piece::isSafe() const {return safety;}

void Piece::updateIsSafe(const bool issafe){
    this->safety = issafe;
}

void Piece::updateCoordinates(const int newR,const int newF){
    this->coordinates[0] = newR;
    this->coordinates[1] = newF;
}


