#include"PokemonData.h"
#include<iostream>
#include<climits>


DataCon::DataCon(){
	pokemon.reserve(1092);
	moves.reserve(844);
	pokemon_moves.reserve(528238);
	pokemon_species.reserve(898);
	experience.reserve(601);
	type_names.reserve(19);
	pokemon_stats.reserve(6552);
	stats.reserve(8);
	pokemon_types.reserve(1675);
}



std::ostream &operator<<(std::ostream &o,  const Pokemon &s){
	o << "Pokemon{\n"; 
	o << '\t' << "id: " << (s.id() == INT_MAX ? " " : std::to_string(s.id())) << '\n';
	o << '\t' << "identifier: " << s.identifier() << '\n';
	o << '\t' << "species_id: " << (s.species_id() == INT_MAX ? " " : std::to_string(s.species_id())) << '\n';
	o << '\t' << "height: " << (s.height() == INT_MAX ? " " : std::to_string(s.height())) << '\n';
	o << '\t' << "weight: " << (s.weight() == INT_MAX ? " " : std::to_string(s.weight())) << '\n';
	o << '\t' << "base_experience: " << (s.base_experience() == INT_MAX ? " " : std::to_string(s.base_experience())) << '\n';
	o << '\t' << "order: " << (s.order() == INT_MAX ? " " : std::to_string(s.order())) << '\n';
	o << '\t' << "is_default: " << (s.is_default() == INT_MAX ? " " : std::to_string(s.is_default())) << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Move &s){
	o << "Move{\n"; 
	o << '\t' << "id: " << (s.id() == INT_MAX ? " " : std::to_string(s.id())) << '\n';
	o << '\t' << "identifier: " << s.identifier() << '\n';
	o << '\t' << "generation_id: " << (s.generation_id() == INT_MAX ? " " : std::to_string(s.generation_id())) << '\n';
	o << '\t' << "type_id: " << (s.type_id() == INT_MAX ? " " : std::to_string(s.type_id())) << '\n';
	o << '\t' << "power: " << (s.power() == INT_MAX ? " " : std::to_string(s.power())) << '\n';
	o << '\t' << "pp: " << (s.pp() == INT_MAX ? " " : std::to_string(s.pp())) << '\n';
	o << '\t' << "accuracy: " << (s.accuracy() == INT_MAX ? " " : std::to_string(s.accuracy())) << '\n';
	o << '\t' << "priority: " << (s.priority() == INT_MAX ? " " : std::to_string(s.priority())) << '\n';
	o << '\t' << "target_id: " << (s.target_id() == INT_MAX ? " " : std::to_string(s.target_id())) << '\n';
	o << '\t' << "damage_class_id: " << (s.damage_class_id() == INT_MAX ? " " : std::to_string(s.damage_class_id())) << '\n';
	o << '\t' << "effect_id: " << (s.effect_id() == INT_MAX ? " " : std::to_string(s.effect_id())) << '\n';
	o << '\t' << "effect_chance: " << (s.effect_chance() == INT_MAX ? " " : std::to_string(s.effect_chance())) << '\n';
	o << '\t' << "contest_type_id: " << (s.contest_type_id() == INT_MAX ? " " : std::to_string(s.contest_type_id())) << '\n';
	o << '\t' << "contest_effect_id: " << (s.contest_effect_id() == INT_MAX ? " " : std::to_string(s.contest_effect_id())) << '\n';
	o << '\t' << "super_contest_effect_id: " << (s.super_contest_effect_id() == INT_MAX ? " " : std::to_string(s.super_contest_effect_id())) << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Pokemon_Move &s){
	o << "Pokemon_Move{\n"; 
	o << '\t' << "pokemon_id: " << (s.pokemon_id() == INT_MAX ? " " : std::to_string(s.pokemon_id())) << '\n';
	o << '\t' << "version_group_id: " << (s.version_group_id() == INT_MAX ? " " : std::to_string(s.version_group_id())) << '\n';
	o << '\t' << "move_id: " << (s.move_id() == INT_MAX ? " " : std::to_string(s.move_id())) << '\n';
	o << '\t' << "pokemon_move_method_id: " << (s.pokemon_move_method_id() == INT_MAX ? " " : std::to_string(s.pokemon_move_method_id())) << '\n';
	o << '\t' << "level: " << (s.level() == INT_MAX ? " " : std::to_string(s.level())) << '\n';
	o << '\t' << "order: " << (s.order() == INT_MAX ? " " : std::to_string(s.order())) << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Pokemon_Species &s){
	o << "Pokemon_Species{\n"; 
	o << '\t' << "id: " << (s.id() == INT_MAX ? " " : std::to_string(s.id())) << '\n';
	o << '\t' << "identifier: " << s.identifier() << '\n';
	o << '\t' << "generation_id: " << (s.generation_id() == INT_MAX ? " " : std::to_string(s.generation_id())) << '\n';
	o << '\t' << "evolves_from_species_id: " << (s.evolves_from_species_id() == INT_MAX ? " " : std::to_string(s.evolves_from_species_id())) << '\n';
	o << '\t' << "evolution_chain_id: " << (s.evolution_chain_id() == INT_MAX ? " " : std::to_string(s.evolution_chain_id())) << '\n';
	o << '\t' << "color_id: " << (s.color_id() == INT_MAX ? " " : std::to_string(s.color_id())) << '\n';
	o << '\t' << "shape_id: " << (s.shape_id() == INT_MAX ? " " : std::to_string(s.shape_id())) << '\n';
	o << '\t' << "habitat_id: " << (s.habitat_id() == INT_MAX ? " " : std::to_string(s.habitat_id())) << '\n';
	o << '\t' << "gender_rate: " << (s.gender_rate() == INT_MAX ? " " : std::to_string(s.gender_rate())) << '\n';
	o << '\t' << "capture_rate: " << (s.capture_rate() == INT_MAX ? " " : std::to_string(s.capture_rate())) << '\n';
	o << '\t' << "base_happiness: " << (s.base_happiness() == INT_MAX ? " " : std::to_string(s.base_happiness())) << '\n';
	o << '\t' << "is_baby: " << (s.is_baby() == INT_MAX ? " " : std::to_string(s.is_baby())) << '\n';
	o << '\t' << "hatch_counter: " << (s.hatch_counter() == INT_MAX ? " " : std::to_string(s.hatch_counter())) << '\n';
	o << '\t' << "has_gender_differences: " << (s.has_gender_differences() == INT_MAX ? " " : std::to_string(s.has_gender_differences())) << '\n';
	o << '\t' << "growth_rate_id: " << (s.growth_rate_id() == INT_MAX ? " " : std::to_string(s.growth_rate_id())) << '\n';
	o << '\t' << "forms_switchable: " << (s.forms_switchable() == INT_MAX ? " " : std::to_string(s.forms_switchable())) << '\n';
	o << '\t' << "is_legendary: " << (s.is_legendary() == INT_MAX ? " " : std::to_string(s.is_legendary())) << '\n';
	o << '\t' << "is_mythical: " << (s.is_mythical() == INT_MAX ? " " : std::to_string(s.is_mythical())) << '\n';
	o << '\t' << "order: " << (s.order() == INT_MAX ? " " : std::to_string(s.order())) << '\n';
	o << '\t' << "conquest_order: " << (s.conquest_order() == INT_MAX ? " " : std::to_string(s.conquest_order())) << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Experience &s){
	o << "Experience{\n"; 
	o << '\t' << "growth_rate_id: " << (s.growth_rate_id() == INT_MAX ? " " : std::to_string(s.growth_rate_id())) << '\n';
	o << '\t' << "level: " << (s.level() == INT_MAX ? " " : std::to_string(s.level())) << '\n';
	o << '\t' << "experience: " << (s.experience() == INT_MAX ? " " : std::to_string(s.experience())) << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Type_Name &s){
	o << "Type_Name{\n"; 
	o << '\t' << "type_id: " << (s.type_id() == INT_MAX ? " " : std::to_string(s.type_id())) << '\n';
	o << '\t' << "local_language_id: " << (s.local_language_id() == INT_MAX ? " " : std::to_string(s.local_language_id())) << '\n';
	o << '\t' << "name: " << s.name() << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Pokemon_Stat &s){
	o << "Pokemon_Stat{\n"; 
	o << '\t' << "pokemon_id: " << (s.pokemon_id() == INT_MAX ? " " : std::to_string(s.pokemon_id())) << '\n';
	o << '\t' << "stat_id: " << (s.stat_id() == INT_MAX ? " " : std::to_string(s.stat_id())) << '\n';
	o << '\t' << "base_stat: " << (s.base_stat() == INT_MAX ? " " : std::to_string(s.base_stat())) << '\n';
	o << '\t' << "effort: " << (s.effort() == INT_MAX ? " " : std::to_string(s.effort())) << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Stat &s){
	o << "Stat{\n"; 
	o << '\t' << "id: " << (s.id() == INT_MAX ? " " : std::to_string(s.id())) << '\n';
	o << '\t' << "damage_class_id: " << (s.damage_class_id() == INT_MAX ? " " : std::to_string(s.damage_class_id())) << '\n';
	o << '\t' << "identifier: " << s.identifier() << '\n';
	o << '\t' << "is_battle_only: " << (s.is_battle_only() == INT_MAX ? " " : std::to_string(s.is_battle_only())) << '\n';
	o << '\t' << "game_index: " << (s.game_index() == INT_MAX ? " " : std::to_string(s.game_index())) << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Pokemon_Type &s){
	o << "Pokemon_Type{\n"; 
	o << '\t' << "pokemon_id: " << (s.pokemon_id() == INT_MAX ? " " : std::to_string(s.pokemon_id())) << '\n';
	o << '\t' << "type_id: " << (s.type_id() == INT_MAX ? " " : std::to_string(s.type_id())) << '\n';
	o << '\t' << "slot: " << (s.slot() == INT_MAX ? " " : std::to_string(s.slot())) << '\n';
	o << "}";
	return o;
}










