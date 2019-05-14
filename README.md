# Wolf3d
This project is a 3D representation of a maze inspired by Wolfenstein 3D video game, using ray-casting.

# Running
To compile the executable, use Make. Then run it with one of the test files in the "maps" directory from the root of this repository.
```
Usage: ./wolf3d maps/map_name
```
# Map format
'P' represents the player position, 0 is an empty space and other numbers from 1 to 6 - texture to display.

```
0 0 1 0 1
0 0 0 0 0
1 1 P 1 1
0 0 1 0 0
```

# Controls:
- Use arrows to navigate;
- Space to change textures layout (different wall textures for every compass point the wall is facing (North, South, East, West)
to standart textures scheme);
- Use enter to change from classic Wolf 3D textures to high-resolution ones.
