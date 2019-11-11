#include "constants.h"


struct gamestate {
    position player_posn;

    player player_data;

    area current_area; 
};

struct area {
    int area_index; // array of map data somewhere
    tile area_tiles[MAX_AREA_ROWS][MAX_AREA_COLS];
}

struct map_areas { // probably make it so a map area can just be preprocessor included
    string area_names[MAX_AREAS];
    area areas[MAX_AREAS];
}

struct tile {
    sprite tile_sprite;
    int collisions;
    dialogue (*tile_interact)(gamestate* current_stat); // might output a message, or do nothing if background
};

// TODO add character sprite structures

struct sprite {
    int sprite_index; // this, or just a bit array / image?
    int sprite_direction; // up down left right, can be used as an offset from sprite_index to get directional sprite
};

struct sprites {
    sprite game_sprites[MAX_SPRITES];
}

struct player {
    pokedex* pokedex_data;
    trainer trainer_data;
    items* player_bag;
    badges badge_data;
};

struct npc {
    int npc_id;
    int is_trainer;
    position npc_position;

    dialogue npc_text;
    sprite npc_sprite;

    trainer* trainer_npc;
    
};

struct dialogue {
    string dialogue_text[MAX_DIALOGUE_STRINGS];
    int (*dialogue_react)(string user_input); // index of next dialogue to go to, after input
};

struct string {
    char* string;
    int strlen;
};

struct position {
    int x, y;
};

struct trainer { // includes npcs
    pokemon party_data[MAX_POKEMON_PARTY];
};

struct items {
    item item_bag[MAX_ITEMS];
    int current_item_index;
};

struct item {
    string item_name;

    void (*item_effect)(gamestate* current_state);
};

struct badges {
    badge player_badges[NUM_BADGES];
};

struct badge {
    string badge_name;
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
    string move_name;
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
    string pkmn_name;
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