#include "constants.h"

typedef struct position position;
typedef struct string string;
typedef struct color color;
typedef struct gamestate gamestate;
typedef struct area area;
typedef struct map_areas map_areas;
typedef struct tile tile;
typedef struct sprite sprite;
typedef struct sprite_data sprite_data;
typedef struct sprites sprites;
typedef struct player player;
typedef struct npc npc;
typedef struct dialogue dialogue;
typedef struct trainer trainer;
typedef struct items items;
typedef struct item item;
typedef struct badges badges;
typedef struct badge badge;
typedef struct pokemon pokemon;
typedef struct moveset moveset;
typedef struct move move;
typedef struct pokemon_implicit_stats pokemon_implicit_stats;
typedef struct pokemon_impl_statrange pokemon_impl_statrange;
typedef struct pokemon_stats pokemon_stats;
typedef struct pokemon_phenotype pokemon_phenotype;
typedef struct pokedex pokedex;
typedef struct pokedex_entry pokedex_entry;
typedef struct pokemon_move_data pokemon_move_data;
typedef struct route_encounter_rates route_encounter_rates;



/*
    Current pokemon / move types -- make a lookup table for weaknesses
*/

typedef enum {
    NORMAL, FIRE, WATER, ELECTRIC, GRASS, ICE, FIGHTING, POISON, GROUND, FLYING, PSYCHIC, BUG, ROCK, GHOST, DRAGON
} pokemon_type;

struct position {
    int x;
    int y;
};

struct string {
    char* str;
    int strlen;
};

struct color {
    char red;
    char green;
    char blue;
};

/*
    Stores not seen stats for a pokemon
*/
struct pokemon_implicit_stats {
    int iv;
};

/*
    Stores viewable stats on a pokemon like its hp, atk, etc
*/
struct pokemon_stats {
    int hp;
    int max_hp;
    int pkmn_atk;
    int pkmn_def;
    int pkmn_spdef;
    int pkmn_spatk;
    int status_condition;
};

/*

*/
struct route_encounter_rates {
    float biome_encounters[NUM_BIOMES][NUM_POKEMON]; // for a given area, the tile 'biome' for a given pokemon if nonzero is the encounter rate
};

/*
    Stores dialogue for a given object (NPC or otherwise), as well as input handler for user interactions
*/
struct dialogue {
    string dialogue_text[MAX_DIALOGUE_STRINGS]; // TODO VLA?
    int (*dialogue_react)(string user_input); // index of next dialogue to go to, after input
};

/*
    Stores data on an item - whether it's key, its amount, the name, and its effect
*/
struct item {
    string item_name;
    int item_amount;
    int key_item;
    void (*item_effect)(gamestate* current_state);
};

/*
    Stores items as the player would have in their bag, and the current index of what the bag is at
*/
struct items {
    item item_bag[MAX_ITEMS]; // TODO VLA?
    int current_item_index;
};

/*
    Stores the range of stats for a given pokemon - does this include atk and such? can add later
*/
struct pokemon_impl_statrange {
    pokemon_implicit_stats lower_bound;
    pokemon_implicit_stats upper_bound;
};

/*
    Represents a pokemon - its name, types, and stats. Probably more later.
*/
struct pokemon_phenotype {
    string pkmn_name;
    pokemon_type pkmn_primary_type;
    pokemon_type pkmn_secondary_type;
    pokemon_impl_statrange pkmn_statrange;
};

/*
    An entry in the pokedex - the pokemon, whether we've caught it, seen it, where to catch it, and later other misc data
*/
struct pokedex_entry {
    pokemon_phenotype pkmn;
    int caught;
    int seen;
    int area_caught; // idx into area_names
};

/*
    Represents the player's pokedex - entries, the current index, and caught/seen pokemon
*/
struct pokedex {
    pokedex_entry pokemon_list[NUM_POKEMON]; // TODO VLA?
    int current_pkmn_index;
    int caught_pokemon;
    int seen_pokemon;
};


/*
    Stores a specific move, the damage type, other stats about it, and the effect it has on a pokemon
*/
struct move {
    string move_name;
    pokemon_type move_type;
    int is_hm;
    int damage;
    int accuracy;
    int max_pp;

    void (*move_effect)(pokemon* attacked_pkmn);
};

/*
    Stores the moves a pokemon can learn for a given pokemon
*/
struct pokemon_move_data {
    move learnable_moves[MAX_MOVES]; // should be a set -- TODO VLA
    move level_to_moves[MAX_POKEMON_LEVEL]; 
};


/*
    Stores the moves for a pokemon, and how much pp each has
*/
struct moveset {
    move movelist[MAX_MOVES];
    int move_pp[MAX_MOVES];
};

/*
    Stores data on a pokemon (combat, not general) - the specific pokemon that it is, its moves, and relevant stats
*/
struct pokemon {
    pokemon_phenotype pkmn;
    moveset pkmn_moves;
    pokemon_implicit_stats pkmn_hidden_stats; // IVS and such
    pokemon_stats pkmn_stats; // hp, atk def etc
    pokemon_move_data possible_moves;
};

/*
    Represents data relevant to a trainer; player or NPC
*/
struct trainer { 
    pokemon party_data[MAX_POKEMON_PARTY];
};

/*
    Stores a badge and if the player has it
*/
struct badge {
    string badge_name;
    int badge_won;
};

/*
    Stores data about a sprite for some object
    Contains the index into the list of all sprites, the direction it might be in (if relevant), and the data for the sprite
*/
struct sprite {
    int sprite_index; // this, or just a bit array / image?
    int sprite_direction; // up down left right, can be used as an offset from sprite_index to get directional sprite
    sprite_data* sprite_data_ptr; // just update ptr when changing things
};

/*
    Contains data on an NPC
    Stores the id of an npc (could be used to look up name and sprite, etc), dialogue it may have, its sprite, and trainer data if not null
    Possibly store data on items they use in battle or etc later
*/
struct npc {
    int npc_id;
    string npc_name;
    position npc_position;
    dialogue npc_text;
    sprite npc_sprite;
    trainer* trainer_npc;
};

/*
    Stores a given tile's data in an area.
    This includes whether an entity can bump into it, its sprite, and any interactions with the tile
    Can be encounter tile thats passive or something that you can click on
*/
struct tile {
    sprite tile_sprite;
    int collisions;
    void (*passive_interact)(gamestate* current_state); // encounter tiles and the like
    dialogue (*tile_interact)(gamestate* current_state); // when clicking on tile: might output a message, or do nothing if background
    union tile_entities {
        npc person_entity;
        item floor_item;
    } tile_entities;
};

/*
    Stores the player's badges
*/
struct badges {
    badge player_badges[NUM_BADGES]; // TODO VLA
};

/*
    Represents the player's data
    Contains what they have for the pokedex, their party data, their items and badges
*/
struct player {
    string player_name;
    pokedex* pokedex_data;
    trainer trainer_data;
    items* player_bag;
    badges badge_data;
};

/*
    Stores the chunk of data for a segment of the map
    Includes the index for the overall area struct to get name. Currently includes relevant data for each tile in the area.
    Will only be updating global map data if dirty flag set
    Possibly could use a method which uses a sliding window over this area as well
    TODO: add support for routes, their probabilities and pokemon seen in them
*/
struct area {
    int dirty;
    int area_index; // index for map_areas structure
    route_encounter_rates* encounter_probs;
    tile area_tiles[MAX_AREA_ROWS][MAX_AREA_COLS];
};

/*
    Stores global map / region data.
    Contains names of each area, as well as each area in the map.
    Should probably be loaded from file initially (preprocessor?) and saved at end if area changes, possibly in chunks
*/
struct map_areas { 
    string area_names[MAX_AREAS];
    area areas[MAX_AREAS];
};

/* 
    Represents the current state of the game and our player's existence in it
    Should be the struct that is saved / loaded on game save
*/
struct gamestate {
    position player_posn; 
    player player_data;
    area current_area; 
};

/*
    Stores a given sprites color data at the defined resolution
*/
struct sprite_data {
    color sprite_colors[TILE_X_SIZE][TILE_Y_SIZE];
};

/*
    Stores all the sprites for tiles and characters alike
    Should be loaded in from file, never changes
*/
struct sprites {
    sprite_data game_sprites[MAX_SPRITES]; // TODO VLA
};

