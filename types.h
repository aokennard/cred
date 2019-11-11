#include "constants.h"

/* 
    Represents the current state of the game and our player's existence in it
    Should be the struct that is saved / loaded on game save
*/
typedef struct {
    position player_posn; 

    player player_data;

    area current_area; 
} gamestate;


/*
    Stores the chunk of data for a segment of the map
    Includes the index for the overall area struct to get name. Currently includes relevant data for each tile in the area.
    Will only be updating global map data if dirty flag set
    Possibly could use a method which uses a sliding window over this area as well
    TODO: add support for routes, their probabilities and pokemon seen in them
*/
typedef struct {
    int dirty;
    int area_index; // index for map_areas structure
    tile area_tiles[MAX_AREA_ROWS][MAX_AREA_COLS];
} area;

/*
    Stores global map / region data.
    Contains names of each area, as well as each area in the map.
    Should probably be loaded from file initially (preprocessor?) and saved at end if area changes, possibly in chunks
*/
typedef struct { 
    string area_names[MAX_AREAS];
    area areas[MAX_AREAS];
} map_areas;

/*
    Stores a given tile's data in an area.
    This includes whether an entity can bump into it, its sprite, and any interactions with the tile
    Can be encounter tile thats passive or something that you can click on
*/
typedef struct {
    sprite tile_sprite;
    int collisions;
    void (*passive_interact)(gamestate* current_state); // encounter tiles and the like
    dialogue (*tile_interact)(gamestate* current_state); // when clicking on tile: might output a message, or do nothing if background
} tile;

/*
    Stores data about a sprite for some object
    Contains the index into the list of all sprites, the direction it might be in (if relevant), and the data for the sprite
*/
typedef struct {
    int sprite_index; // this, or just a bit array / image?
    int sprite_direction; // up down left right, can be used as an offset from sprite_index to get directional sprite
    sprite_data* sprite_data_ptr; // just update ptr when changing things
} sprite;

/*
    Stores a given sprites color data at the defined resolution
*/
typedef struct {
    color sprite_colors[TILE_X_SIZE][TILE_Y_SIZE];
} sprite_data;

/*
    Stores all the sprites for tiles and characters alike
    Should be loaded in from file, never changes
*/
typedef struct {
    sprite_data game_sprites[MAX_SPRITES];
} sprites;

/*
    Represents the player's data
    Contains what they have for the pokedex, their party data, their items and badges
*/
typedef struct {
    pokedex* pokedex_data;
    trainer trainer_data;
    items* player_bag;
    badges badge_data;
} player;

/*
    Contains data on an NPC
    Stores the id of an npc (could be used to look up name and sprite, etc), dialogue it may have, its sprite, and trainer data if not null
    Possibly store data on items they use in battle or etc later
*/
typedef struct {
    int npc_id;
    position npc_position;
    dialogue npc_text;
    sprite npc_sprite;
    trainer* trainer_npc;
} npc;

/*
    Stores dialogue for a given object (NPC or otherwise), as well as input handler for user interactions
*/
typedef struct {
    string dialogue_text[MAX_DIALOGUE_STRINGS];
    int (*dialogue_react)(string user_input); // index of next dialogue to go to, after input
} dialogue;

typedef struct {
    char* string;
    int strlen;
} string;

typedef struct {
    int x, y;
} position;

typedef struct {
    char red, green, blue;
} color;

/*
    Represents data relevant to a trainer; player or NPC
*/
typedef struct { 
    pokemon party_data[MAX_POKEMON_PARTY];
} trainer;

/*
    Stores items as the player would have in their bag, and the current index of what the bag is at
*/
typedef struct {
    item item_bag[MAX_ITEMS];
    int current_item_index;
} items;

/*
    Stores data on an item - whether it's key, its amount, the name, and its effect
*/
typedef struct {
    string item_name;
    int item_amount;
    int key_item;
    void (*item_effect)(gamestate* current_state);
} item;

/*
    Stores the player's badges
*/
typedef struct {
    badge player_badges[NUM_BADGES];
} badges;

/*
    Stores a badge and if the player has it
*/
typedef struct {
    string badge_name;
    int badge_won;
} badge;

/*
    Stores data on a pokemon (combat, not general) - the specific pokemon that it is, its moves, and relevant stats
*/
typedef struct {
    pokemon_phenotype pkmn;
    moveset pkmn_moves;
    pokemon_implicit_stats pkmn_hidden_stats; // IVS and such
    pokemon_stats pkmn_stats; // hp, atk def etc
} pokemon;

/*
    Stores the moves for a pokemon, and how much pp each has
*/
typedef struct {
    move movelist[MAX_MOVES];
    int move_pp[MAX_MOVES];
} moveset;

/*
    Stores a specific move, the damage type, other stats about it, and the effect it has on a pokemon
*/
typedef struct {
    string move_name;
    pokemon_type move_type;
    int is_hm;
    int damage;
    int accuracy;
    int max_pp;

    void (*move_effect)(pokemon* attacked_pkmn);
} move;

/*
    Stores not seen stats for a pokemon
*/
typedef struct {
    int iv;
} pokemon_implicit_stats;

/*
    Stores the range of stats for a given pokemon - does this include atk and such? can add later
*/
typedef struct {
    pokemon_implicit_stats lower_bound;
    pokemon_implicit_stats upper_bound;
} pokemon_impl_statrange;

/*
    Stores viewable stats on a pokemon like its hp, atk, etc
*/
typedef struct {
    int hp;
    int max_hp;
    int pkmn_atk;
    int pkmn_def;
    int pkmn_spdef;
    int pkmn_spatk;
    int status_condition;
} pokemon_stats;

/*
    Represents a pokemon - its name, types, and stats. Probably more later.
*/
typedef struct {
    string pkmn_name;
    pokemon_type pkmn_primary_type;
    pokemon_type pkmn_secondary_type;
    pokemon_impl_statrange pkmn_statrange;
} pokemon_phenotype;

/*
    Represents the player's pokedex - entries, the current index, and caught/seen pokemon
*/
typedef struct {
    pokedex_entry pokemon_list[NUM_POKEMON];
    int current_pkmn_index;
    int caught_pokemon;
    int seen_pokemon;
} pokedex;

/*
    An entry in the pokedex - the pokemon, whether we've caught it, seen it, where to catch it, and later other misc data
*/
typedef struct {
    pokemon_phenotype pkmn;
    int caught;
    int seen;
    int area_caught; // idx into area_names
} pokedex_entry;

/*
    Current pokemon / move types
*/
enum pokemon_type {
    NORMAL, FIRE, WATER, ELECTRIC, GRASS, ICE, FIGHTING, POISON, GROUND, FLYING, PSYCHIC, BUG, ROCK, GHOST, DRAGON
};