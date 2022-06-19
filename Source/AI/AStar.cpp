/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Description
*/

#include "AStar.hpp"

#define RANGE(a) a.begin(), a.end()

void reverseQueue(std::queue<coordinates_t> &Queue)
{
    std::stack<coordinates_t> Stack;
    while (!Queue.empty()) {
        Stack.push(Queue.front());
        Queue.pop();
    }
    while (!Stack.empty()) {
        Queue.push(Stack.top());
        Stack.pop();
    }
}

std::deque<coordinates_t> returnPath(Node currentNode, std::vector<std::vector<gfx_tile_t>> map, std::vector<int> _blockingTiles)
{
    std::deque<coordinates_t> path;

    while (true) {
        if (currentNode.parent == nullptr)
            break;
        if (currentNode == *currentNode.parent)
            break;
        path.push_front(currentNode.position);
        currentNode = *currentNode.parent;
    }
    
    if(!path.empty()) {
        coordinates_t end = {path.back().first, path.back().second};
        for (int blockingTile : _blockingTiles)
            if (map[end.first][end.second].tile == blockingTile)
                path.pop_back();
    }

    return path;
}

std::deque<coordinates_t> calculateAStar(coordinates_t start, coordinates_t end,
    std::vector<std::vector<gfx_tile_t>> map, std::vector<int> _blockingTiles)
{
    end = {end.second, end.first};
    start = {start.second, start.first};

    // Start / End
    Node startNode = Node(nullptr, start);
    Node endNode = Node(nullptr, end);

    // Possible relative pos
    // Used to initiate neighbours
    std::deque<std::pair<int, int>> possiblePos;

    // Init lists
    std::deque<Node> openList;
    std::deque<Node> closedList;

    // Add start node to the list
    openList.push_back(startNode);

    size_t totalIterations = 0;
    size_t max_iterations = map[0].size() * map.size();

    // Initialize neighbour list
    possiblePos.push_front({0, -1});
    possiblePos.push_front({0, 1});
    possiblePos.push_front({-1, 0});
    possiblePos.push_front({1, 0});

    while (!openList.empty()) {
        // Inc total Iteration
        totalIterations += 1;

        // Get the current node
        Node currNode = openList.front();

        // Remove from openList
        openList.pop_front();
        // ... and add to closed list
        closedList.push_back(currNode);

        // Timeour check
        if (totalIterations > max_iterations)
            return {};

        // Check if at target
        if (currNode == endNode)
            return returnPath(currNode, map, _blockingTiles);

        // Generate neighbours
        std::deque<Node> neighbours;

        // Instantiate neighbour nodes
        // Note : f, g, and h are all instatiated to 0
        for (std::pair<int, int> posOffset: possiblePos) {
            // Get node position
            coordinates_t nodePosition = {
                currNode.position.first + posOffset.first,
                currNode.position.second + posOffset.second
            };

            // Make sure within range
            if (nodePosition.first >= map.size() || nodePosition.second >= map[0].size())
                continue;

            // Make sure walkable terrain
            int isBlocked = 0;
            for (int blockingTile: _blockingTiles)
                if ((nodePosition.first != end.first || nodePosition.second != end.second) &&
                    map[nodePosition.first][nodePosition.second].tile == blockingTile)
                    isBlocked = 1;
            if (isBlocked)
                continue;

            // Create new node
            Node newNode = Node(&closedList.back(), nodePosition);

            neighbours.push_back(newNode);
        }

        // Actual loop
        for (Node child: neighbours) {
            // Search closed list if child exist
            if (std::find(RANGE(closedList), child) != closedList.end())
                continue;

            // Calc G
            child.g = currNode.g + 1;
            // Calc H
            child.h = std::abs((int) child.position.first - (int) endNode.position.first) +
                      std::abs((int) child.position.second - (int) endNode.position.second);
            // Sum F = G + H
            child.f = child.g + child.h;

            // If node with same coords is in open list
            // AND openNode.f < child.f, skip child
            int inOpenList = 0;
            for (auto openNode: openList)
                if (child == openNode && openNode.f < child.f)
                    inOpenList = 1;
            if (inOpenList)
                continue;

            // Add child to open list
            openList.push_back(child);
        }
    }
    return {};
}

std::deque<coordinates_t> avoidBomb(coordinates_t start, coordinates_t bombPos, int bombRadius,
    std::vector<std::vector<gfx_tile_t>> map, std::vector<int> _blockingTiles)
{
    start = {start.second, start.first};
    bombPos = {bombPos.second, bombPos.first};

    if ((start.first != bombPos.first && start.second != bombPos.second)
        || std::abs(int(start.first - bombPos.first)) >= bombRadius || std::abs(int(start.second - bombPos.second)) >= bombRadius)
        return {};

    // Start
    Node startNode = Node(nullptr, start);

    // Possible relative pos
    // Used to initiate neighbours
    std::deque<std::pair<int, int>> possiblePos;

    // Init lists
    std::deque<Node> openList;
    std::deque<Node> closedList;

    // Add start node to the list
    openList.push_back(startNode);

    size_t totalIterations = 0;
    size_t max_iterations = map[0].size() * map.size();

    // Initialize neighbour list
    possiblePos.push_front({0, -1});
    possiblePos.push_front({0, 1});
    possiblePos.push_front({-1, 0});
    possiblePos.push_front({1, 0});

    while (!openList.empty()) {
        // Inc total Iteration
        totalIterations += 1;

        // Get the current node
        Node currNode = openList.front();

        // Remove from openList
        openList.pop_front();
        // ... and add to closed list
        closedList.push_back(currNode);

        // Timeour check
        if (totalIterations > max_iterations)
            return {};

        // Check if at target
        if ((currNode.position.first != bombPos.first && currNode.position.second != bombPos.second)
            || std::abs(int(currNode.position.first - bombPos.first)) >= bombRadius || std::abs(int(currNode.position.second - bombPos.second)) >= bombRadius) // if behind corner/ 3-6 pos away from start pos
            return returnPath(currNode, map, _blockingTiles);

        // Instantiate neighbour nodes
        // Note : f, g, and h are all instatiated to 0
        for (std::pair<int, int> posOffset: possiblePos) {
            // Get node position
            coordinates_t nodePosition = {
                currNode.position.first + posOffset.first,
                currNode.position.second + posOffset.second
            };

            // Make sure within range
            if (nodePosition.first >= map.size() || nodePosition.second >= map[0].size())
                continue;

            // Make sure walkable terrain
            int isBlocked = 0;
            for (int blockingTile: _blockingTiles)
                if (map[nodePosition.first][nodePosition.second].tile == blockingTile)
                    isBlocked = 1;
            if (isBlocked)
                continue;

            // Create new node
            Node newNode = Node(&closedList.back(), nodePosition);
            openList.push_back(newNode);
        }
    }
    return {};
}

Node::Node(Node *parent, coordinates_t position)
{
    this->position = position;
    this->parent = parent;
    this->g = 0;
    this->f = 0;
    this->h = 0;
}

bool operator==(Node first, Node other)
{
    return (first.position.first == other.position.first) && (first.position.second == other.position.second);
}
