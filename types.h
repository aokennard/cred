#include "constants.h"


struct gamestate {
    int player_x;
    int player_y;

    player player_data;
};

struct player {
    pokedex* pokedex_data;
    pokemon party_data[MAX_POKEMON_PARTY];
    items* player_bag;
    badges badge_data;
};

struct items {
    item item_bag[MAX_ITEMS];
    int current_item_index;
};

struct item {
    char* item_name;
    // function pointer that modifies the gamestate
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
    // probably a function pointer taking in a pokemon and outputting another pokemon
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