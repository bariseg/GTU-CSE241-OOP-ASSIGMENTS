#ifndef _UTIL_HPP_
#define _UTIL_HPP_
#include <vector>
#include <string>

using namespace std;

class Game;
class Board;
class Piece;
enum class PieceType;
enum class PiecePoints;
enum class Team;

class Game{
public:

    Game(const int wScore = 39, const int bScore = 39);

    const int getScore(Team team) const;
    void updateScores(const Board& currBoard);
    
    const string getInput(const Board& currentBoard,const Team turn)const;
    void printTurn(const Team turn) const;
    bool isGameOver(const Board& currBoard,const Team turn)const;

private:
    double whiteScore,blackScore;

    void CheckAlert(const Team turn);

    bool invalidInput(const string input,const Board& currentBoard,const Team turn) const;
    //suggest if there is a checkmate.If not, suggests if there is a check
    //if not, suggests the best scored move
    const string getSuggest(const Board& currentBoard,const Team turn) const;
};

class Board{

friend Game;
public:
    Board();
    ~Board();

    void operator =(const Board& other);

    void printBoard() const ;
    void initilize();
    void fileSave(const string move,const Team team)const ;

    void updateLegalMoves() const;
    void updateBoard(const string& input);

    void legalMovesPrinterTest()const ;
    void resetSafeties()const;
    bool checkBeatAttacker(const Team turn)const;

private:

    vector< vector< Piece* > > allPieces;

    //those functions work inside the updateLegalMoves() function to help it.
    void kingLegalMove(Piece* p)const;
    void queenLegalMove(Piece* p)const;
    void rookLegalMove(Piece* p)const;
    void knightLegalMove(Piece* p)const;
    void bishopLegalMove(Piece* p)const;
    void pawnLegalMove(Piece* p)const;

    bool isEmptyCell(const int r,const int f)const;
    bool isAValidCell(const int r=0,const int f=0)const;

};


class Piece{

friend Board;
friend Game;
public:
    
    Piece(  Team _team,
            PieceType type, vector<int> coordinates,
            PiecePoints _point,
            bool isSafe,
            char _symbol);

    void updateCoordinates(const int newR,const int newF);
    void updateIsSafe(bool issafe);
    bool isSafe() const ;
    

private:

    const PieceType type;
    const char symbol;
    const Team team;
    vector<int> coordinates;
    const PiecePoints point;
    bool safety;
    vector< vector <int> > LegalMoves;

};



#endif /* _UTIL_HPP_ */