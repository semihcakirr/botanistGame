This is a game that you control a botanist which is moving in a garden and collecting flowers.
There is trees in garden which acts as a barrier to the player.
Botanist cant leave the board and cant move through trees.
Botanist has a bottle size which acts as an inventory, whenever he/she collects a flower bottle size decreases 1.
If user wants to quit he/she can press q.

There is two structures, first one is forest and second one is botanist.

Forest structure holds the followings:
-Map [Integer][Integer]: This is a 2D array.
-Width [Integer]: This stores number of rows (size of dimension X) the map.
-Height [Integer]: This stores number of columns (size of dimension Y) of the map.

Botanist structures holds the followings:
-Coord_X [Integer]: The X coordinate of the botanist.
-Coord_Y [Integer]: The Y coordinate of the botanist.
-Water_Bottle_Size [Integer]: This is the volume of water bottle size.

The values that this variables holds are taken from a txt file named init.txt

FUNCTIONS

void init_game(Forest forest, Botanist botanist)
-This function reads a file called init.txt and creates both the forest and the botanist. The first line
contains height and width of the forest separated by “,”. The second line contains coordinates of
Botanist and his/her water bottle volume. Starting from the second line, map is defined. Trees, the
botanist and the rare flower is illustrated as T, B and X.

void search(...)
-This is a recursive function that walks (up, down, left and right) on the forest to find the rare flower.
Botanist can move only in whitespaces. Botanist says "I've found it!" whenever he/she finds it. Botanist
has a strong memory so he/she remembers where he/she walked before.

display_forest(…)
-This function shows the collected flower number and not used bottle number and also gives us the
Botanist coordinates. Update the botanist's view as you move through the forest. If the Botanist finds
a Flower replace it with the whitespace.

Notes:
-Taking direction information from the user in the form of r(right),l(left),u(up),d(down).
-You can move in only whitespaces. If the user wants to go on trees, returning a warning.
-Saving the last view of the forest and information in another .txt file before leaving the program.
-Size of the forest and the number of flowers are changeble depending on init.txt file.
