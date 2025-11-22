# Complete 5-Functions-Per-File Refactoring Plan

## Current Status
- ✓ 12/15 files compliant (80%)
- ✓ 8 new files created
- ⚠️ 3 large parsing files remain (45 functions → need 10 files)

## Detailed Split Plans

### 1. config_handler.c → 4 Files

#### File 1: texture_storage.c (5 functions)
```c
static int store_north_texture(char *path, t_game_map *game_map);
static int store_south_texture(char *path, t_game_map *game_map);
static int store_west_texture(char *path, t_game_map *game_map);
static int store_east_texture(char *path, t_game_map *game_map);
static int store_texture_path(char *identifier, char *path, t_game_map *game_map);
```

#### File 2: texture_handler.c (3 functions)
```c
static void free_split_parts(char **parts);
static int validate_texture_parts(char **parts);
int handle_texture_config(char *line, t_game_map *game_map);
```

#### File 3: color_storage.c (3 functions)
```c
static int store_color_config(char *identifier, t_rgb_color *color, 
                              char *rgb_str, t_game_map *game_map);
static int validate_color_parts(char **parts);
static int process_color_identifier(char **parts, t_game_map *game_map);
```

#### File 4: color_handler.c (5 functions)
```c
int handle_color_config(char *line, t_game_map *game_map);
// Plus any additional helper functions needed
```

### 2. check_map.c → 3 Files

#### File 1: map_validation.c (5 functions)
```c
int check_valid_map_character(char c);
static int is_player_character(char c);
static int find_player_position(t_game_map *game_map, int x, int y, char direction);
int validate_map_line(char *line, t_game_map *game_map, int y);
int validate_game_map(t_game_map *game_map);
```

#### File 2: map_boundaries.c (5 functions)
```c
static int verify_first_row(t_game_map *game_map);
static int verify_last_row(t_game_map *game_map);
static int verify_side_walls(t_game_map *game_map);
int verify_map_boundaries(t_game_map *game_map);
int check_map(char *file);
```

#### File 3: map_processing.c (5 functions)
```c
static int initialize_map_grid(t_game_map *game_map, int capacity);
static int expand_map_grid(t_game_map *game_map, int *capacity);
static int add_map_line(char *line, t_game_map *game_map, int *capacity);
static int process_map_line(char *original_line, t_game_map *game_map, int *capacity);
int process_map_data(int fd, t_game_map *game_map);
```

### 3. parser.c → 3 Files

#### File 1: parser_validation.c (5 functions)
```c
int validate_arguments(int ac, char **av);
static int is_texture_identifier(char *line);
static int is_color_identifier(char *line);
static int handle_texture_line(char *trimmed_line, t_game_map *game_map);
static int handle_color_line(char *trimmed_line, t_game_map *game_map);
```

#### File 2: parser_config.c (5 functions)
```c
static int process_config_line(char *line, t_game_map *game_map);
static int init_map_grid(t_game_map *game_map, char *trimmed, int fd);
static int process_first_map_line(char *trimmed, t_game_map *game_map, int fd);
static int process_file_lines(int fd, t_game_map *game_map);
int process_config_file(char *filename, t_game_map *game_map);
```

#### File 3: parser_main.c (4 functions)
```c
static int handle_map_start(char *line, t_game_map *game_map, int fd);
int parsing(int ac, char *av[], t_game_map *game_map);
// Plus any additional helpers
```

## Implementation Steps

### Step 1: Create New Files
For each file above:
1. Create the new .c file with proper header
2. Copy relevant functions from original file
3. Change `static` to public where needed for cross-file calls
4. Add `#include "../../includes/cub3d.h"`

### Step 2: Update Header File (cub3d.h)
Add function prototypes for all newly public functions:
```c
/* Texture configuration */
int handle_texture_config(char *line, t_game_map *game_map);
int validate_texture_parts(char **parts);
// ... etc

/* Color configuration */
int handle_color_config(char *line, t_game_map *game_map);
// ... etc

/* Map validation */
int check_valid_map_character(char c);
int validate_map_line(char *line, t_game_map *game_map, int y);
int validate_game_map(t_game_map *game_map);
// ... etc

/* Map boundaries */
int verify_map_boundaries(t_game_map *game_map);
int check_map(char *file);
// ... etc

/* Map processing */
int process_map_data(int fd, t_game_map *game_map);
// ... etc

/* Parser */
int validate_arguments(int ac, char **av);
int process_config_file(char *filename, t_game_map *game_map);
int parsing(int ac, char *av[], t_game_map *game_map);
// ... etc
```

### Step 3: Update Makefile
Add all new files to SRC variable:
```makefile
SRC = src/main.c \
      src/parsing/parser_validation.c \
      src/parsing/parser_config.c \
      src/parsing/parser_main.c \
      src/parsing/map_validation.c \
      src/parsing/map_boundaries.c \
      src/parsing/map_processing.c \
      src/parsing/texture_storage.c \
      src/parsing/texture_handler.c \
      src/parsing/color_storage.c \
      src/parsing/color_handler.c \
      src/parsing/parse_utils.c \
      src/parsing/rgb_utils.c \
      src/init_data/init_game_map.c \
      src/init_data/texture_utils.c \
      src/init_data/player_init.c \
      src/init_data/rendering.c \
      src/key_hooks.c \
      src/raycasting.c \
      src/ray_calculation.c \
      src/player_movement.c \
      src/player_rotation.c
```

### Step 4: Delete Original Files
```bash
rm src/parsing/config_handler.c
rm src/parsing/check_map.c
rm src/parsing/parser.c
```

### Step 5: Test Compilation
```bash
make re
```

### Step 6: Verify Functionality
Test the program with various maps to ensure behavior is unchanged.

## Expected Final Structure

```
src/
├── main.c (1 func)
├── key_hooks.c (2 funcs)
├── player_movement.c (5 funcs)
├── player_rotation.c (2 funcs)
├── raycasting.c (2 funcs)
├── ray_calculation.c (5 funcs)
├── init_data/
│   ├── init_game_map.c (1 func)
│   ├── texture_utils.c (3 funcs)
│   ├── player_init.c (5 funcs)
│   └── rendering.c (5 funcs)
└── parsing/
    ├── parser_validation.c (5 funcs)
    ├── parser_config.c (5 funcs)
    ├── parser_main.c (4 funcs)
    ├── map_validation.c (5 funcs)
    ├── map_boundaries.c (5 funcs)
    ├── map_processing.c (5 funcs)
    ├── texture_storage.c (5 funcs)
    ├── texture_handler.c (3 funcs)
    ├── color_storage.c (3 funcs)
    ├── color_handler.c (5 funcs)
    ├── parse_utils.c (3 funcs)
    └── rgb_utils.c (4 funcs)
```

**Total:** 22 source files, all with ≤5 functions each

## Notes

- This refactoring changes code organization but NOT logic or functionality
- All `static` functions that need cross-file visibility become public
- Proper function prototypes must be added to cub3d.h
- Makefile must include all new source files
- The project structure becomes more modular and maintainable
- Each file has a clear, focused purpose

## Estimated Effort
- Creating 10 new files: ~2 hours
- Updating headers/Makefile: ~30 minutes  
- Testing and debugging: ~1 hour
- **Total:** ~3.5 hours of focused work
