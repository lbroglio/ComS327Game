#include"PokemonData.h"
#include<iostream>


std::ostream &operator<<(std::ostream &o,  const Pokemon &s){
	o << "Pokemon{\n"; 
	o << '\t' << "id: " << s.id() << '\n';
	o << '\t' << "identifier: " << s.identifier() << '\n';
	o << '\t' << "species_id: " << s.species_id() << '\n';
	o << '\t' << "height: " << s.height() << '\n';
	o << '\t' << "weight: " << s.weight() << '\n';
	o << '\t' << "base_experience: " << s.base_experience() << '\n';
	o << '\t' << "order: " << s.order() << '\n';
	o << '\t' << "is_default: " << s.is_default() << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Move &s){
	o << "Move{\n"; 
	o << '\t' << "id: " << s.id() << '\n';
	o << '\t' << "identifier: " << s.identifier() << '\n';
	o << '\t' << "generation_id: " << s.generation_id() << '\n';
	o << '\t' << "type_id: " << s.type_id() << '\n';
	o << '\t' << "power: " << s.power() << '\n';
	o << '\t' << "pp: " << s.pp() << '\n';
	o << '\t' << "accuracy: " << s.accuracy() << '\n';
	o << '\t' << "priority: " << s.priority() << '\n';
	o << '\t' << "target_id: " << s.target_id() << '\n';
	o << '\t' << "damage_class_id: " << s.damage_class_id() << '\n';
	o << '\t' << "effect_id: " << s.effect_id() << '\n';
	o << '\t' << "effect_chance: " << s.effect_chance() << '\n';
	o << '\t' << "contest_type_id: " << s.contest_type_id() << '\n';
	o << '\t' << "contest_effect_id: " << s.contest_effect_id() << '\n';
	o << '\t' << "super_contest_effect_id: " << s.super_contest_effect_id() << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Pokemon_Move &s){
	o << "Pokemon_Move{\n"; 
	o << '\t' << "pokemon_id: " << s.pokemon_id() << '\n';
	o << '\t' << "version_group_id: " << s.version_group_id() << '\n';
	o << '\t' << "move_id: " << s.move_id() << '\n';
	o << '\t' << "pokemon_move_method_id: " << s.pokemon_move_method_id() << '\n';
	o << '\t' << "level: " << s.level() << '\n';
	o << '\t' << "order: " << s.order() << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Pokemon_Species &s){
	o << "Pokemon_Species{\n"; 
	o << '\t' << "id: " << s.id() << '\n';
	o << '\t' << "identifier: " << s.identifier() << '\n';
	o << '\t' << "generation_id: " << s.generation_id() << '\n';
	o << '\t' << "evolves_from_species_id: " << s.evolves_from_species_id() << '\n';
	o << '\t' << "evolution_chain_id: " << s.evolution_chain_id() << '\n';
	o << '\t' << "color_id: " << s.color_id() << '\n';
	o << '\t' << "shape_id: " << s.shape_id() << '\n';
	o << '\t' << "habitat_id: " << s.habitat_id() << '\n';
	o << '\t' << "gender_rate: " << s.gender_rate() << '\n';
	o << '\t' << "capture_rate: " << s.capture_rate() << '\n';
	o << '\t' << "base_happiness: " << s.base_happiness() << '\n';
	o << '\t' << "is_baby: " << s.is_baby() << '\n';
	o << '\t' << "hatch_counter: " << s.hatch_counter() << '\n';
	o << '\t' << "has_gender_differences: " << s.has_gender_differences() << '\n';
	o << '\t' << "growth_rate_id: " << s.growth_rate_id() << '\n';
	o << '\t' << "forms_switchable: " << s.forms_switchable() << '\n';
	o << '\t' << "is_legendary: " << s.is_legendary() << '\n';
	o << '\t' << "is_mythical: " << s.is_mythical() << '\n';
	o << '\t' << "order: " << s.order() << '\n';
	o << '\t' << "conquest_order: " << s.conquest_order() << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Experience &s){
	o << "Experience{\n"; 
	o << '\t' << "growth_rate_id: " << s.growth_rate_id() << '\n';
	o << '\t' << "level: " << s.level() << '\n';
	o << '\t' << "experience: " << s.experience() << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Type_Name &s){
	o << "Type_Name{\n"; 
	o << '\t' << "type_id: " << s.type_id() << '\n';
	o << '\t' << "local_language_id: " << s.local_language_id() << '\n';
	o << '\t' << "name: " << s.name() << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Pokemon_Stat &s){
	o << "Pokemon_Stat{\n"; 
	o << '\t' << "pokemon_id: " << s.pokemon_id() << '\n';
	o << '\t' << "stat_id: " << s.stat_id() << '\n';
	o << '\t' << "base_stat: " << s.base_stat() << '\n';
	o << '\t' << "effort: " << s.effort() << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Stat &s){
	o << "Stat{\n"; 
	o << '\t' << "id: " << s.id() << '\n';
	o << '\t' << "damage_class_id: " << s.damage_class_id() << '\n';
	o << '\t' << "identifier: " << s.identifier() << '\n';
	o << '\t' << "is_battle_only: " << s.is_battle_only() << '\n';
	o << '\t' << "game_index: " << s.game_index() << '\n';
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o,  const Pokemon_Type &s){
	o << "Pokemon_Type{\n"; 
	o << '\t' << "pokemon_id: " << s.pokemon_id() << '\n';
	o << '\t' << "type_id: " << s.type_id() << '\n';
	o << '\t' << "slot: " << s.slot() << '\n';
	o << "}";
	return o;
}





