#include <iostream>
#include "ECS/ECS.hpp"
#include "ECS/EntityManager.hpp"
#include "ECS/EntityViewer.hpp"
#include "ECS/ComponentPool.hpp"

struct Pos {
    int x;
    int y;
};
struct Score {
    std::size_t score;
};

int main() {
    EntityManager em;

    EntityID player = em.CreateNewEntity();
    Pos *playerPos = em.Assign<Pos>((EntityID) player, Pos{2, 3});
    Score *playerScore = em.Assign<Score>(player, Score{3});
    std::cout << "player id: " << GetEntityIndex(player) << ", pos: " << playerPos->x << "|" << playerPos->y << ", score: " << playerScore->score << std::endl;

    EntityID player1 = em.CreateNewEntity();
    Pos *playerPos1 = em.Assign<Pos>((EntityID) player1, Pos{7, 8});
    Score *playerScore1 = em.Assign<Score>(player1, Score{10});
    std::cout << "player id: " << GetEntityIndex(player1) << ", pos: " << playerPos1->x << "|" << playerPos1->y << ", score: " << playerScore1->score << std::endl;

    std::cout << "em entity size: " << em.getEntities().size() << ", component pools size: " << em.getComponentPools().size() << std::endl << std::endl;
    for (EntityID ent : EntityViewer<>(em))
    {
        Pos* playerPos2 = em.Get<Pos>(ent);
        Score* playerScore2 = em.Get<Score>(ent);

        std::cout << "iterate over em: " << std::endl;
        std::cout << "Player Pos: " << playerPos2->x << "|" << playerPos2->y << std::endl;
        std::cout << "Player Score: " << playerScore2->score << std::endl;
    }
    return 0;
}
