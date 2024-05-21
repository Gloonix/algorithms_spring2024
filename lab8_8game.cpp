#include <iostream>
#include <array>
#include <cassert>
#include <unordered_map>
#include <queue>
#include <algorithm>

const char FieldSize = 9;
const std::array<char, FieldSize> finishField = {1, 2, 3, 4, 5, 6, 7, 8, 0};

class GameState
{
public:
    GameState(const std::array<char, FieldSize> &field)
    : field(field)
    {
        emptyPos = -1;
        for (int i = 0; i < FieldSize; i++)
        {
            if (field[i] == 0)
            {
                emptyPos = i;
            }
        }
        assert(emptyPos != -1);
    }
    
    bool IsComplete() const
    {
        return field == finishField;
    }
    
    bool IsSolvable() const
    {
        return getInvCount() % 2 == 0;
    }
    
    bool CanMoveLeft() const
    {
        return emptyPos % 3 != 2;
    }
    
    bool CanMoveRight() const
    {
        return emptyPos % 3 != 0;
    }
    
    bool CanMoveUp() const
    {
        return emptyPos < 6;
    }
    
    bool CanMoveDown() const
    {
        return emptyPos > 2;
    }
    
    GameState MoveLeft() const
    {
        assert(CanMoveLeft());
        
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos + 1]);
        newState.emptyPos++;
        return newState;
    }
    
    GameState MoveRight() const
    {
        assert(CanMoveRight());
        
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos - 1]);
        newState.emptyPos--;
        return newState;
    }
    
    GameState MoveUp() const
    {
        assert(CanMoveUp());
        
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos + 3]);
        newState.emptyPos += 3;
        return newState;
    }
    
    GameState MoveDown() const
    {
        assert(CanMoveDown());
        
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos - 3]);
        newState.emptyPos -= 3;
        return newState;
    }
    
    bool operator==(const GameState &other) const
    {
        return field == other.field;
    }
    
private:
    size_t getInvCount() const
    {
        size_t inv_count = 0;
        for (int i = 0; i < FieldSize - 1; i++)
        {
            for (int j = i + 1; j < FieldSize; j++)
            {
                if (field[i] > field[j] && field[i] && field[j])
                    inv_count++;
            }
        }
        return inv_count;
    }
    
    std::array<char, FieldSize> field;
    char emptyPos;
    
    friend struct GameStateHasher;
    friend std::ostream& operator<<(std::ostream &out, const GameState &state);
};

struct GameStateHasher
{
public:
    size_t operator()(const GameState &state) const
    {
        size_t hash = 0;
        std::memcpy(&hash, state.field.data(), sizeof(hash));
        return hash;
    }
};

std::ostream& operator<<(std::ostream &out, const GameState &state)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            out << static_cast<int>(state.field[i * 3 + j]) << ' ';
        }
        out << std::endl;
    }
    return out;
}

std::string GetSolution(const std::array<char, FieldSize> &field)
{
    GameState startState(field);
    
    if (!startState.IsSolvable())
        return "-1";
    
    std::unordered_map<GameState, char, GameStateHasher> visited;
    visited[startState] = 'S';
    
    std::queue<GameState> queue;
    queue.push(startState);
    
    while (true)
    {
        GameState state = queue.front();
        queue.pop();
        
        if (state.IsComplete())
            break;
        
        if (state.CanMoveLeft())
        {
            GameState newState = state.MoveLeft();
            if (visited.find(newState) == visited.end())
            {
                visited[newState] = 'L';
                queue.push(newState);
            }
        }
        if (state.CanMoveRight())
        {
            GameState newState = state.MoveRight();
            if (visited.find(newState) == visited.end())
            {
                visited[newState] = 'R';
                queue.push(newState);
            }
        }
        if (state.CanMoveUp())
        {
            GameState newState = state.MoveUp();
            if (visited.find(newState) == visited.end())
            {
                visited[newState] = 'U';
                queue.push(newState);
            }
        }
        if (state.CanMoveDown())
        {
            GameState newState = state.MoveDown();
            if (visited.find(newState) == visited.end())
            {
                visited[newState] = 'D';
                queue.push(newState);
            }
        }
    }
    
    std::string path;
    GameState state(finishField);
    
    std::cout << state << std::endl;
    while (visited[state] != 'S')
    {
        char move = visited[state];
        switch (move)
        {
            case 'L':
            {
                state = state.MoveRight();
                path += 'L';
                break;
            }
            case 'R':
            {
                state = state.MoveLeft();
                path += 'R';
                break;
            }
            case 'D':
            {
                state = state.MoveUp();
                path += 'D';
                break;
            }
            case 'U':
            {
                state = state.MoveDown();
                path += 'U';
                break;
            }
        }
        
        std::cout << state << std::endl;
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

int main(int argc, const char * argv[]) {
    std::array<char, FieldSize> field = {2, 3, 1, 4, 5, 6, 7, 8, 0};
    std::cout << GetSolution(field) << std::endl;
    return 0;
}
