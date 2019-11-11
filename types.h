#include "constants.h"


struct gamestate {
    int player_x;
    int player_y;

    player player_data;

    region current_region; 
};

struct region {
    int region_index; // array of map data somewhere
    tile region_tiles[MAX_REGION_ROWS][MAX_REGION_COLS];
}

struct tile {
    sprite tile_sprite;
    int collisions;
    char* (*tile_interact)(gamestate* current_stat); // might output a message, or do nothing if background
};

// TODO add character sprite structures

struct sprite {
    int sprite_index; // this, or just a bit array / image?
};

struct trainer_sprite {
    int sprite_index; // this, or just a bit array / image?
};

struct player {
    pokedex* pokedex_data;
    trainer trainer_data;
    items* player_bag;
    badges badge_data;
};

struct trainer { // includes npcs
    pokemon party_data[MAX_POKEMON_PARTY];
    trainer_sprite sprite_data;
    // possibly dialogue for npcs?
};

struct items {
    item item_bag[MAX_ITEMS];
    int current_item_index;
};

struct item {
    char* item_name;

    void (*item_effect)(gamestate* current_state);
};

struct badges {
    badge player_badges[NUM_BADGES];
};

struct badge {
    char* badge_name;
    int badge_won;
};

struct pokemon {
    pokemon_phenotype pkmn;
    moveset pkmn_moves;
    pokemon_implicit_stats pkmn_hidden_stats; // IVS and such
    pokemon_stats pkmn_stats; // hp, atk def etc
};

struct moveset {
    move movelist[MAX_MOVES];
    int move_pp[MAX_MOVES];
};

struct move {
    char* move_name;
    pokemon_type move_type;
    int is_hm;
    int damage;
    int accuracy;

    void (*move_effect)(pokemon* attacked_pkmn);
}

struct pokemon_implicit_stats {
    int iv;
};

struct pokemon_impl_statrange {
    pokemon_implicit_stats lower_bound;
    pokemon_implicit_stats upper_bound;
};

struct pokemon_stats {
    int hp;
    int pkmn_atk;
    int pkmn_def;
    int pkmn_spdef;
    int pkmn_spatk;
    int status_condition;
};

struct pokemon_phenotype {
    char* pkmn_name;
    pokemon_type pkmn_primary_type;
    pokemon_type pkmn_secondary_type;
    pokemon_impl_statrange pkmn_statrange;
};

struct pokedex {
    pokedex_entry pokemon_list[NUM_POKEMON];
    int current_pkmn_index;
};

struct pokedex_entry {
    pokemon_phenotype pkmn;
    int caught;
};

enum pokemon_type {
    NORMAL, FIRE, WATER, ELECTRIC, GRASS, ICE, FIGHTING, POISON, GROUND, FLYING, PSYCHIC, BUG, ROCK, GHOST, DRAGON
};