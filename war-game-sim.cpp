
#include <iostream>
#include <cstring>
using namespace std;


const int MAX_ROWS = 20;
const int MAX_COLS = 30;
const int MAX_NUM_WARRIORS = 26; 
const char CHAR_EMPTY = '.';
const char CHAR_END_INPUT = '!';
const int MAX_DIRECTION_TEXT_LENGTH = 10 + 1; 
const int MAX_ACTION_TEXT_LENGTH = 10 + 1;    

enum DirectionType
{
    DIRECTION_ERROR = 0,
    DIRECTION_EAST,
    DIRECTION_SOUTH,
    DIRECTION_WEST,
    DIRECTION_NORTH,
    DIRECTION_NORTH_EAST,
    DIRECTION_SOUTH_EAST,
    DIRECTION_SOUTH_WEST,
    DIRECTION_NORTH_WEST
};

enum ActionType
{
    ACTION_ERROR = 0,
    ACTION_MOVE,
    ACTION_FIGHT,
    ACTION_SHOOT
};
enum StatusMoveAction
{
    STATUS_ACTION_MOVE_NOT_IMPLMENTED = 0,
    STATUS_ACTION_MOVE_SUCCESS,
    STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY,
    STATUS_ACTION_MOVE_HIT_ANOTHER_ALONG_PATH
};
enum StatusFightAction
{
    STATUS_ACTION_FIGHT_NOT_IMPLEMENTED = 0,
    STATUS_ACTION_FIGHT_SUCCESS,
    STATUS_ACTION_FIGHT_FAIL
};
enum StatusShootAction
{
    STATUS_ACTION_SHOOT_NOT_IMPLEMENTED = 0,
    STATUS_ACTION_SHOOT_SUCCESS,
    STATUS_ACTION_SHOOT_FAIL
};

const char DIRECTION_TEXT_ERROR[] = "wrong direction";
const char DIRECTION_TEXT_EAST[] = "east";
const char DIRECTION_TEXT_WEST[] = "west";
const char DIRECTION_TEXT_SOUTH[] = "south";
const char DIRECTION_TEXT_NORTH[] = "north";
const char DIRECTION_TEXT_NORTHEAST[] = "northeast";
const char DIRECTION_TEXT_NORTHWEST[] = "northwest";
const char DIRECTION_TEXT_SOUTHEAST[] = "southeast";
const char DIRECTION_TEXT_SOUTHWEST[] = "southwest";

const char ACTION_MOVE_TEXT[] = "moves";
const char ACTION_FIGHT_TEXT[] = "fights";
const char ACTION_SHOOT_TEXT[] = "shoots";

int letterToArrayIndex(char letter)
{
    return int(letter - 'A');
}

char indexToLetter(int index)
{
    return char(index + 'A');
}

ActionType convertToActionType(const char actionText[MAX_ACTION_TEXT_LENGTH])
{

  
    if (strcmp(actionText, ACTION_MOVE_TEXT) == 0)
    {
        return ACTION_MOVE;
    }
    else if (strcmp(actionText, ACTION_FIGHT_TEXT) == 0)
    {
        return ACTION_FIGHT;
    }
    else if (strcmp(actionText, ACTION_SHOOT_TEXT) == 0)
    {
        return ACTION_SHOOT;
    }
    return ACTION_ERROR;
}

DirectionType convertDirectionText(const char text[MAX_DIRECTION_TEXT_LENGTH])
{
    if (strcmp(text, DIRECTION_TEXT_EAST) == 0)
    {
        return DIRECTION_EAST;
    }
    if (strcmp(text, DIRECTION_TEXT_SOUTH) == 0)
    {
        return DIRECTION_SOUTH;
    }
    if (strcmp(text, DIRECTION_TEXT_WEST) == 0)
    {
        return DIRECTION_WEST;
    }
    if (strcmp(text, DIRECTION_TEXT_NORTH) == 0)
    {
        return DIRECTION_NORTH;
    }
    if (strcmp(text, DIRECTION_TEXT_NORTHEAST) == 0)
    {
        return DIRECTION_NORTH_EAST;
    }
    if (strcmp(text, DIRECTION_TEXT_NORTHWEST) == 0)
    {
        return DIRECTION_NORTH_WEST;
    }
    if (strcmp(text, DIRECTION_TEXT_SOUTHEAST) == 0)
    {
        return DIRECTION_SOUTH_EAST;
    }
    if (strcmp(text, DIRECTION_TEXT_SOUTHWEST) == 0)
    {
        return DIRECTION_SOUTH_WEST;
    }
    return DIRECTION_ERROR;
}

const char *convertDirectionText(DirectionType direction)
{
    if (direction == DIRECTION_EAST)
        return DIRECTION_TEXT_EAST;
    if (direction == DIRECTION_SOUTH)
        return DIRECTION_TEXT_SOUTH;
    if (direction == DIRECTION_WEST)
        return DIRECTION_TEXT_WEST;
    if (direction == DIRECTION_NORTH)
        return DIRECTION_TEXT_NORTH;
    if (direction == DIRECTION_NORTH_EAST)
        return DIRECTION_TEXT_NORTHEAST;
    if (direction == DIRECTION_NORTH_WEST)
        return DIRECTION_TEXT_NORTHWEST;
    if (direction == DIRECTION_SOUTH_EAST)
        return DIRECTION_TEXT_SOUTHEAST;
    if (direction == DIRECTION_SOUTH_WEST)
        return DIRECTION_TEXT_SOUTHWEST;
    return DIRECTION_TEXT_ERROR;
}

bool isValidMoveDirection(DirectionType d)
{
    return d == DIRECTION_EAST || d == DIRECTION_WEST || d == DIRECTION_SOUTH || d == DIRECTION_NORTH;
}
bool isValidFightDirection(DirectionType d)
{
    return d == DIRECTION_EAST || d == DIRECTION_WEST || d == DIRECTION_SOUTH || d == DIRECTION_NORTH;
}

bool isValidShootDirection(DirectionType d)
{
    return d == DIRECTION_EAST || d == DIRECTION_WEST || d == DIRECTION_SOUTH || d == DIRECTION_NORTH || d == DIRECTION_NORTH_EAST || d == DIRECTION_NORTH_WEST || d == DIRECTION_SOUTH_EAST || d == DIRECTION_SOUTH_WEST;
}

void initializeMap(char map[MAX_ROWS][MAX_COLS], int numRows, int numCols)
{
    int r, c;
    for (r = 0; r < numRows; r++)
        for (c = 0; c < numCols; c++)
            map[r][c] = CHAR_EMPTY;
}

void initializePoints(int healthPoints[MAX_NUM_WARRIORS], int fightPoints[MAX_NUM_WARRIORS], int shootPoints[MAX_NUM_WARRIORS])
{
    for (int i = 0; i < MAX_NUM_WARRIORS; i++)
        healthPoints[i] = fightPoints[i] = shootPoints[i] = 0;
}

void readInputPoints(int healthPoints[MAX_NUM_WARRIORS], int fightPoints[MAX_NUM_WARRIORS], int shootPoints[MAX_NUM_WARRIORS])
{
    int num, hp, fp, sp, i, index;
    char letter;
    initializePoints(healthPoints, fightPoints, shootPoints);
    // Read letters and health points
    cin >> num;
    for (i = 0; i < num; i++)
    {
        cin >> letter >> hp >> fp >> sp;
        index = letterToArrayIndex(letter);
        healthPoints[index] = hp;
        fightPoints[index] = fp;
        shootPoints[index] = sp;
    }
}

void readInputMap(char map[MAX_ROWS][MAX_COLS], int &mapRows, int &mapCols)
{
    int r, c;
    char line[MAX_COLS + 1]; 

    
    cin >> mapRows >> mapCols;
    initializeMap(map, mapRows, mapCols);

    cin.ignore();
    for (r = 0; r < mapRows; r++)
    {
        cin.getline(line, MAX_COLS + 1);
        for (c = 0; c < mapCols; c++)
            map[r][c] = line[c];
    }
}

void displayMap(const char map[MAX_ROWS][MAX_COLS], int mapRows, int mapCols)
{
    int r, c;
    for (r = 0; r < mapRows; r++)
    {
        for (c = 0; c < mapCols; c++)
            cout << map[r][c] << " ";
        cout << endl;
    }
}

void displayPoints(const int healthPoints[MAX_NUM_WARRIORS],
                   const int fightPoints[MAX_NUM_WARRIORS],
                   const int shootPoints[MAX_NUM_WARRIORS])
{
    int i, hp, fp, sp;
    cout << "== Warrior Letter (HP,FP,SP) ==" << endl;
    for (i = 0; i < MAX_NUM_WARRIORS; i++)
    {
        hp = healthPoints[i];
        if (hp > 0)
        {
            fp = fightPoints[i];
            sp = shootPoints[i];
            cout << indexToLetter(i) << "(" << hp << "," << fp << "," << sp << ")" << endl;
        }
    }
}

StatusMoveAction updateMapForMoveAction(char map[MAX_ROWS][MAX_COLS], int mapRows, int mapCols,
                                        char letter, DirectionType direction, int moveSteps)
{
   int rowWarrior,colWarrior;
   bool Warrior_found=false;
    for(int r=0;r<mapRows;r++) 
    {
        for(int c=0;c<mapCols;c++) 
        {
            if(map[r][c]==letter)
            {
                rowWarrior=r;
                colWarrior=c;
                Warrior_found=true;
                break;
            }
        } 
        if (Warrior_found) break;
    }
    int rowNew=rowWarrior;
    int colNew=colWarrior;
    switch (direction)
    {
        case DIRECTION_EAST:
            colNew+=moveSteps;
            break;
        case DIRECTION_SOUTH:
            rowNew+=moveSteps;
            break;
        case DIRECTION_WEST:
            colNew-=moveSteps;
            break;
        case DIRECTION_NORTH:
            rowNew-=moveSteps;
            break;
        default:
            return STATUS_ACTION_MOVE_NOT_IMPLMENTED;
        
    }
    
    
    for (int i = 1; i <= moveSteps; i++) {
        int row_checking = rowWarrior;
        int col_checking = colWarrior;

        if (direction == DIRECTION_EAST) {
            col_checking = col_checking + i;    
        } 
        else if (direction == DIRECTION_SOUTH) {
            row_checking = row_checking + i;
        }
        else if (direction == DIRECTION_WEST) {
            col_checking = col_checking - i; 
        }
        else if (direction == DIRECTION_NORTH) {
            row_checking = row_checking - i;
        }

        if (rowNew < 0 || rowNew >= mapRows || colNew < 0 || colNew >= mapCols) {
            return STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY;
        }

        if (map[row_checking][col_checking] != CHAR_EMPTY) {
            return STATUS_ACTION_MOVE_HIT_ANOTHER_ALONG_PATH;
        }

    }

   

    
    if (map[rowNew][colNew]!=CHAR_EMPTY){
        return STATUS_ACTION_MOVE_HIT_ANOTHER_ALONG_PATH;
    }

        map[rowNew][colNew]=letter;
        map[rowWarrior][colWarrior]=CHAR_EMPTY;
        return STATUS_ACTION_MOVE_SUCCESS;
    
}

StatusFightAction updateMapAndHealthPointsForFightAction(int healthPoints[MAX_NUM_WARRIORS],
                                                         char map[MAX_ROWS][MAX_COLS],
                                                         int mapRows, int mapCols,
                                                         const int fightPoints[MAX_NUM_WARRIORS],
                                                         char letter,
                                                         DirectionType direction,
                                                         char &targetLetter,
                                                         int &targetOriginalHealthPoint,
                                                         int &targetUpdatedHealthPoint)
{
    int rowFighter,colFighter;
    bool fighterFound=false;

        for (int r=0;r<mapRows;r++)
        {
        for (int c=0;c<mapCols;c++) 
        {
            if (map[r][c]==letter)
             {
                rowFighter=r;
                colFighter=c;
                fighterFound=true;
                break;
            }
        }
        if (fighterFound) break;
    }
    
    

    int targetRow=rowFighter;
    int targetCol=colFighter;

    if (direction==DIRECTION_EAST) 
    {
        targetCol++;
    } 
    else if (direction==DIRECTION_SOUTH) 
    {
        targetRow++;
    } else if (direction==DIRECTION_WEST)
    {
        targetCol--;
    } 
    else if (direction==DIRECTION_NORTH) 
    {
        targetRow--;
    } 
    else 
    {
    return STATUS_ACTION_FIGHT_NOT_IMPLEMENTED; 
    }

    if (targetRow<0||targetRow>=mapRows||targetCol<0||targetCol>=mapCols)
        {
        return STATUS_ACTION_FIGHT_FAIL; 
        }
    targetLetter=map[targetRow][targetCol];
    if (targetLetter==CHAR_EMPTY) 
    {
        return STATUS_ACTION_FIGHT_FAIL; 
    }

    int indexOps=letterToArrayIndex(targetLetter);
    int indexFighter=letterToArrayIndex(letter);
    
    targetOriginalHealthPoint=healthPoints[indexOps];
    int opsFightPoints =fightPoints[indexFighter];

   targetUpdatedHealthPoint=targetOriginalHealthPoint-opsFightPoints;
    if (targetUpdatedHealthPoint<=0)
    {
       targetUpdatedHealthPoint=0;
        healthPoints[indexOps]=0;
        map[targetRow][targetCol]=letter;
        map[rowFighter][colFighter]=CHAR_EMPTY;
        return STATUS_ACTION_FIGHT_SUCCESS;
    }
    healthPoints[indexOps]=targetUpdatedHealthPoint;
    return STATUS_ACTION_FIGHT_SUCCESS;

    }
    

StatusShootAction updateMapAndHealthPointsForShootAction(int healthPoints[MAX_NUM_WARRIORS],
                                                         char map[MAX_ROWS][MAX_COLS],
                                                         int mapRows, int mapCols,
                                                         const int shootPoints[MAX_NUM_WARRIORS],
                                                         char letter,
                                                         DirectionType direction,
                                                         char &targetLetter,
                                                         int &targetOriginalHealthPoint,
                                                         int &targetUpdatedHealthPoint)
{
    int shooterRow,shooterCol;
    bool foundShooter=false;

    for(int r=0;r<mapRows;r++)
    {
        for(int c=0;c<mapCols;c++)
        {
            if (map[r][c] == letter)
            {
                shooterRow=r;
                shooterCol=c;
                foundShooter=true;
                break;
            }
        }
        if (foundShooter) 
        break;
    }

    int opRow=shooterRow;
    int opCol=shooterCol;

    switch (direction)
    {
        case DIRECTION_EAST:
        opCol+=2;
        break;
        case DIRECTION_SOUTH:
        opRow+=2;
        break;
        case DIRECTION_WEST:
        opCol-=2;
        break;
        case DIRECTION_NORTH:
        opRow-=2;
        break;
        case DIRECTION_NORTH_EAST:
        opRow--;
        opCol++;
        break;
        case DIRECTION_NORTH_WEST:
        opRow--;
        opCol--;
        break;
        case DIRECTION_SOUTH_EAST:
        opRow++;
        opCol++;
        break;
        case DIRECTION_SOUTH_WEST:
        opRow++;
        opCol--;
        break;
        default:return STATUS_ACTION_SHOOT_NOT_IMPLEMENTED;
    }

    if (opRow<0||opRow>=mapRows||opCol<0||opCol>=mapCols)
    {
        return STATUS_ACTION_SHOOT_FAIL; 
    }

    targetLetter=map[opRow][opCol];
    if (targetLetter==CHAR_EMPTY)
    {
        return STATUS_ACTION_SHOOT_FAIL; 
    }


    int indexOp=letterToArrayIndex(targetLetter);
    targetOriginalHealthPoint = healthPoints[indexOp];

    int shooterIndex =letterToArrayIndex(letter);
    targetUpdatedHealthPoint = targetOriginalHealthPoint-shootPoints[shooterIndex];
    if (targetUpdatedHealthPoint<=0)
    {
       targetUpdatedHealthPoint=0;
        healthPoints[indexOp]=0;
        map[opRow][opCol]=CHAR_EMPTY;
        return STATUS_ACTION_SHOOT_SUCCESS;
    }
    healthPoints[indexOp]=targetUpdatedHealthPoint;
    return STATUS_ACTION_SHOOT_SUCCESS;

    }

int main()
{
   
    char map[MAX_ROWS][MAX_COLS];
    char actionText[MAX_ACTION_TEXT_LENGTH];
    char directionText[MAX_DIRECTION_TEXT_LENGTH];
    int healthPoints[MAX_NUM_WARRIORS];
    int fightPoints[MAX_NUM_WARRIORS];
    int shootPoints[MAX_NUM_WARRIORS];

    
    int mapRows, mapCols, moveSteps;
    char letter;
    ActionType action;
    DirectionType direction;
    StatusMoveAction statusMove;
    StatusFightAction statusFight;
    StatusShootAction statusShoot;

    char targetLetter;
    int targetOriginalHealthPoint;
    int targetUpdatedHealthPoint;

    
    readInputPoints(healthPoints, fightPoints, shootPoints);
    readInputMap(map, mapRows, mapCols);

    cout << "The initial game information:" << endl;
    displayPoints(healthPoints, fightPoints, shootPoints);
    displayMap(map, mapRows, mapCols);

    

    while (true)
    {
        cin >> letter;
        if (letter == CHAR_END_INPUT)
            break; 

        cin >> actionText >> directionText;
        action = convertToActionType(actionText);
        direction = convertDirectionText(directionText);

        if (action == ACTION_MOVE)
        {
            
            cin >> moveSteps;
            if (isValidMoveDirection(direction))
            {
                statusMove = updateMapForMoveAction(map, mapRows, mapCols, letter, direction, moveSteps);
                if (statusMove == STATUS_ACTION_MOVE_NOT_IMPLMENTED)
                {
                    cout << "Error: The move action is not implemented yet" << endl;
                }
                else if (statusMove == STATUS_ACTION_MOVE_SUCCESS)
                {
                    cout << "Success: "
                         << "Warrior " << letter << " moves along the direction " << convertDirectionText(direction) << " by " << moveSteps << " step(s)" << endl;
                    displayMap(map, mapRows, mapCols);
                }
                else if (statusMove == STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY)
                {
                    cout << "Fail: "
                         << "If " << letter << " moves along the direction " << convertDirectionText(direction) << " by " << moveSteps << " step(s)"
                         << ", it will move outside a boundary. The position remains unchanged" << endl;
                    displayMap(map, mapRows, mapCols);
                }
                else if (statusMove == STATUS_ACTION_MOVE_HIT_ANOTHER_ALONG_PATH)
                {
                    cout << "Fail: "
                         << "If " << letter << " moves along the direction " << convertDirectionText(direction) << " by " << moveSteps << " step(s)"
                         << ", it will hit another along the path. The position remains unchanged" << endl;
                    displayMap(map, mapRows, mapCols);
                }
            }
            else
            {
                cout << "Error: The direction " << convertDirectionText(direction) << " is invalid for the move action" << endl;
            }
        }
        else if (action == ACTION_FIGHT)
        {
            if (isValidFightDirection(direction))
            {
                statusFight = updateMapAndHealthPointsForFightAction(healthPoints, map, mapRows, mapCols, fightPoints, letter, direction, targetLetter,
                                                                     targetOriginalHealthPoint, targetUpdatedHealthPoint);
                if (statusFight == STATUS_ACTION_FIGHT_NOT_IMPLEMENTED)
                {
                    cout << "Error: The fight action is not implemented yet" << endl;
                }
                else if (statusFight == STATUS_ACTION_FIGHT_SUCCESS)
                {

                    cout << "Success: "
                         << "Warrior " << letter << " fights " << targetLetter << endl;
                    cout << "Warrior " << targetLetter << " health point is reduced from " << targetOriginalHealthPoint << " to " << targetUpdatedHealthPoint << endl;
                    if (targetUpdatedHealthPoint == 0)
                    {
                        cout << "Warrior " << targetLetter << " is being killed by " << letter << endl;
                        displayMap(map, mapRows, mapCols);
                    }

                    displayPoints(healthPoints, fightPoints, shootPoints);
                }
                else if (statusFight == STATUS_ACTION_FIGHT_FAIL)
                {

                    cout << "Fail: "
                         << "Warrior " << letter << " cannot fight any target" << endl;

                    displayPoints(healthPoints, fightPoints, shootPoints);
                }
            }
            else
            {
                cout << "Error: The direction " << convertDirectionText(direction) << " is invalid for the fight action" << endl;
            }
        }
        else if (action == ACTION_SHOOT)
        {
            if (isValidShootDirection(direction))
            {
                statusShoot = updateMapAndHealthPointsForShootAction(healthPoints, map, mapRows, mapCols, shootPoints, letter, direction, targetLetter,
                                                                     targetOriginalHealthPoint, targetUpdatedHealthPoint);
                if (statusShoot == STATUS_ACTION_SHOOT_NOT_IMPLEMENTED)
                {
                    cout << "Error: The shoot action is not implemented yet" << endl;
                }
                else if (statusShoot == STATUS_ACTION_SHOOT_SUCCESS)
                {

                    cout << "Success: "
                         << "Warrior " << letter << " shoots " << targetLetter << endl;
                    cout << "Warrior " << targetLetter << " health point is reduced from " << targetOriginalHealthPoint << " to " << targetUpdatedHealthPoint << endl;
                    if (targetUpdatedHealthPoint == 0)
                    {
                        cout << "Warrior " << targetLetter << " is being killed by " << letter << endl;
                        displayMap(map, mapRows, mapCols);
                    }

                    displayPoints(healthPoints, fightPoints, shootPoints);
                }
                else if (statusShoot == STATUS_ACTION_SHOOT_FAIL)
                {

                    cout << "Fail: "
                         << "Warrior " << letter << " cannot shoot any target" << endl;

                    displayPoints(healthPoints, fightPoints, shootPoints);
                }
            }
            else
            {
                cout << "Error: The direction " << convertDirectionText(direction) << " is invalid for the shoot action" << endl;
            }
        }
    }

    return 0;
}