#include <vector>

struct Game
{
    int id;
    char ans;
};


class GameManager{
private:
    std::vector<Game> game_list;
public:
    GameManager();
    ~GameManager();
    
    bool createGame();
    int submitGuess(int id, int guess);
    void deleteGame(int id);
    int getAns(int id);
};