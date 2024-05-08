#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

/* Structure for the forest */
typedef struct
{
    int map[MAX_SIZE][MAX_SIZE]; /* 2D array representing the forest map */
    int width;                   /* Width of the forest */
    int height;                  /* Height of the forest */
} Forest;

/* Structure for the botanist */
typedef struct
{
    int Coord_X;           /* X coordinate of the botanist */
    int Coord_Y;           /* Y coordinate of the botanist */
    int Water_Bottle_Size; /* Size of the water bottle carried by the botanist */
} Botanist;

/* Function to initialize the game */
void init_game(Forest *forest, Botanist *botanist)
{
    int i, j;
    char semicolumn;
    char c;
    FILE *file = fopen("init.txt", "r");

    /* Read forest dimensions and botanist information */
    fscanf(file, "%d,%d", &forest->height, &forest->width);
    fscanf(file, "%d,%d,%d", &botanist->Coord_X, &botanist->Coord_Y, &botanist->Water_Bottle_Size);

    /* Read forest map */
    for (i = 0; i < forest->height; i++)
    {
        for (j = 0; j < forest->width; j++)
        {
            fscanf(file, "%c", &c); /* Scan character */
            if (c == ',')
            {
                fscanf(file, "%c", &c); /* If character is ',' scan again */
            }
            else if (c == '\n')
            {
                fscanf(file, "%c", &c); /* If character is newline scan again */
            }

            if (c == 'T')
            {
                forest->map[i][j] = 1; /* If character is Tree place it on the map */
            }
            else if (c == 'B')
            {
                forest->map[i][j] = 2; /* If character is Botanist place it on the map */
                botanist->Coord_X = i; /* Taking the botanist starting locations */
                botanist->Coord_Y = j;
            }
            else if (c == 'X')
            {
                forest->map[i][j] = 3; /* If character is Flower place it on the map */
            }
            else if (c == ' ')
            {
                forest->map[i][j] = 0; /* If character is Road place it on the map */
            }

            if (j == 9) /* To avoid newlines */
            {
                fscanf(file, "%c", &c);
            }
        }
    }

    fclose(file);
}

/* Function to display the forest */

void display_forest(Forest *forest, Botanist *botanist)
{
    int i, j;
    printf("Botanist Coordinates: (%d, %d)\n", botanist->Coord_X, botanist->Coord_Y); /* Printing botanist coordinates */
    printf("Water Bottle Size: %d\n", botanist->Water_Bottle_Size);                   /* Printing current bottle size */
    printf("Forest Map:\n");                                                          /* Now its time to print forest map */

    for (i = 0; i < forest->height; i++)
    {
        for (j = 0; j < forest->width; j++)
        {
            if (i == botanist->Coord_X && j == botanist->Coord_Y) /* If botanist's coordinates matches print B representing botanist */
            {
                printf("B");
            }

            else if (forest->map[i][j] == 3) /* If map arrays index is 3 then print X representing flower */
            {
                printf("X");
            }

            else if (forest->map[i][j] == 1) /* If map arrays index is 1 then print T representing tree */
            {
                printf("T");
            }

            else if (forest->map[i][j] == 0) /* If map arrays index is 0 then print space representing gap/road */
            {
                printf(" ");
            }

            if (j != 9)
            {
                printf(",");
            }
        }
        printf("\n"); /* Newline */
    }
}

/* Core game function. It calls itself recursively when needed */
void search(Forest *forest, Botanist *botanist, char direction, int endflag)
{
    if (endflag == 0) /* If player enters q in this recursive function, endflag will be 0 and i will not go into this case */
    {
        switch (direction) /* Switch case for moving */
        {
        case 'u':                                                             /* Case u for going up */
            botanist->Coord_X--;                                              /* Lowering botanists row */
            if (botanist->Coord_X < 0 || botanist->Coord_X >= forest->height) /* Checking if botanist leaves the board or not */
            {
                botanist->Coord_X++;                                                                                     /* Botanist is leaving board. Increase x to take him/her back */
                printf("You are not allowed to go out of garden!\n");                                                    /* Printing error message */
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): "); /* Asking for input */
                scanf(" %c", &direction);                                                                                /* Scanning input */
                search(forest, botanist, direction, endflag);                                                            /* Calling the function recursively with the new direction */
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 1) /* Checking if the location player wants to move is a tree */
            {
                botanist->Coord_X++;                                                                                     /* Botanist is moving towards to a tree. Increase x to take him/her back */
                printf("You can not move in that direction. There is a tree over there!\n");                             /* Printing error message */
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): "); /* Asking for input */
                scanf(" %c", &direction);                                                                                /* Scanning input */
                search(forest, botanist, direction, endflag);                                                            /* Calling the function recursively with the new direction */
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 0) /* Checking if botanist is moving to empty block/gap/road */
            {
                forest->map[botanist->Coord_X + 1][botanist->Coord_Y] = 0;                                               /* Updating previous location of botanist as empty block */
                display_forest(forest, botanist);                                                                        /* Displaying current board map */
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): "); /* Asking for input */
                scanf(" %c", &direction);                                                                                /* Scanning input */
                search(forest, botanist, direction, endflag);                                                            /* Calling the function recursively with the new direction */
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 3) /* Checking if botanist is moving to flower */
            {
                printf("I've found it!\n");                                                                              /* Botanist has found the flower! */
                botanist->Water_Bottle_Size--;                                                                           /* Decreasing bottle size */
                forest->map[botanist->Coord_X][botanist->Coord_Y] = 0;                                                   /* The location that holds the flower is becoming 0 which represents gap/road/empty place */
                display_forest(forest, botanist);                                                                        /* Displaying current board map */
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): "); /* Asking for input */
                scanf(" %c", &direction);                                                                                /* Scanning input */
                search(forest, botanist, direction, endflag);                                                            /* Calling the function recursively with the new direction */
            }
            break;

        case 'd': /* Same rules for other directions */
            botanist->Coord_X++;
            if (botanist->Coord_X < 0 || botanist->Coord_X >= forest->height)
            {
                botanist->Coord_X--;
                printf("You are not allowed to go out of garden!\n");
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 1)
            {
                botanist->Coord_X--;
                printf("You can not move in that direction. There is a tree over there!\n");
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 0)
            {
                forest->map[botanist->Coord_X - 1][botanist->Coord_Y] = 0;
                display_forest(forest, botanist);
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 3)
            {
                printf("I've found it!\n");
                botanist->Water_Bottle_Size--;
                forest->map[botanist->Coord_X][botanist->Coord_Y] = 0;
                display_forest(forest, botanist);
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            break;

        case 'l':
            botanist->Coord_Y--;
            if (botanist->Coord_Y < 0 || botanist->Coord_Y >= forest->width)
            {
                botanist->Coord_Y++;
                printf("You are not allowed to go out of garden!\n");
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 1)
            {
                botanist->Coord_Y++;
                printf("You can not move in that direction. There is a tree over there!\n");
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 0)
            {
                forest->map[botanist->Coord_X][botanist->Coord_Y + 1] = 0;
                display_forest(forest, botanist);
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 3)
            {
                printf("I've found it!\n");
                botanist->Water_Bottle_Size--;
                forest->map[botanist->Coord_X][botanist->Coord_Y] = 0;
                display_forest(forest, botanist);
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            break;

        case 'r':
            botanist->Coord_Y++;
            if (botanist->Coord_Y < 0 || botanist->Coord_Y >= forest->width)
            {
                botanist->Coord_Y--;
                printf("You are not allowed to go out of garden!\n");
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 1)
            {
                botanist->Coord_Y--;
                printf("You can not move in that direction. There is a tree over there!\n");
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 0)
            {
                forest->map[botanist->Coord_X][botanist->Coord_Y - 1] = 0;
                display_forest(forest, botanist);
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            else if (forest->map[botanist->Coord_X][botanist->Coord_Y] == 3)
            {
                printf("I've found it!\n");
                botanist->Water_Bottle_Size--;
                forest->map[botanist->Coord_X][botanist->Coord_Y] = 0;
                display_forest(forest, botanist);
                printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): ");
                scanf(" %c", &direction);
                search(forest, botanist, direction, endflag);
            }
            break;

        case 'q':        /* Case for exit */
            endflag = 1; /* The function is void so i cant return a value, i am calling the function with updated endflag */
            search(forest, botanist, direction, endflag);
            break;

        default:                                                                                                     /* Default case for invalid inputs */
            printf("Invalid direction.\n");                                                                          /* Printing error message */
            printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): "); /* Asking for input */
            scanf(" %c", &direction);                                                                                /* Scanning input */
            search(forest, botanist, direction, endflag);                                                            /* Calling the function recursively */
            break;
        }
    }
    else if (endflag == 1) /* Case for exit */
    {
        printf("Exitted the game.");
    }
}
int main()
{
    Forest forest;
    Botanist botanist;
    char direction;  /* Variable to store move */
    int i, j;        /* Variable to use in loops */
    int endflag = 0; /* Flag to check if the game is over or not */

    /* Initialize the game */
    init_game(&forest, &botanist);

    /* Display forest */
    display_forest(&forest, &botanist);

    printf("Please enter a direction to move(u for up, r for right, d for down, l for left, q for quit): "); /* Printing */
    scanf(" %c", &direction);                                                                                /* Taking user input for direction */
    search(&forest, &botanist, direction, endflag);                                                          /* Calling the core game function */

    FILE *file = fopen("last.txt", "w");                                                   /* Opening new txt file named last.txt to print the last state of the game */
    fprintf(file, "Botanist Coordinates: (%d, %d)\n", botanist.Coord_X, botanist.Coord_Y); /* Printing botanist coordinates */
    fprintf(file, "Water Bottle Size: %d\n", botanist.Water_Bottle_Size);                  /* Printing bottle size */
    fprintf(file, "Forest Map:\n");                                                        /* Printing map */
    for (i = 0; i < forest.height; i++)
    {
        for (j = 0; j < forest.width; j++)
        {
            if (i == botanist.Coord_X && j == botanist.Coord_Y) /* If botanist's coordinates matches print B representing botanist */
            {
                fprintf(file, "B");
            }

            else if (forest.map[i][j] == 3) /* If map arrays index is 3 then print X representing flower */
            {
                fprintf(file, "X");
            }

            else if (forest.map[i][j] == 1) /* If map arrays index is 1 then print T representing tree */
            {
                fprintf(file, "T");
            }

            else if (forest.map[i][j] == 0) /* If map arrays index is 0 then print space representing gap/road */
            {
                fprintf(file, " ");
            }

            if (j != 9)
            {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n"); /* Newline */
    }

    return 0;
}