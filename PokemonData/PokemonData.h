#ifndef POKEDATA_H
#define POKEDATA_H



#include<string>
#include<vector>
#include<iostream>


class Pokemon_Info{
	private:
		int id_;
		std::string identifier_;
		int species_id_;
		int height_;
		int weight_;
		int base_experience_;
		int order_;
		int is_default_;
	public:
		Pokemon_Info(int id, std::string identifier, int species_id, int height, int weight, int base_experience, int order, int is_default) : id_(id), identifier_(identifier), species_id_(species_id), height_(height), weight_(weight), base_experience_(base_experience), order_(order), is_default_(is_default){}
		int id() const {return id_;}
		std::string identifier() const {return identifier_;}
		int species_id() const {return species_id_;}
		int height() const {return height_;}
		int weight() const {return weight_;}
		int base_experience() const {return base_experience_;}
		int order() const {return order_;}
		int is_default() const {return is_default_;}
};

class Move{
	private:
		int id_;
		std::string identifier_;
		int generation_id_;
		int type_id_;
		int power_;
		int pp_;
		int accuracy_;
		int priority_;
		int target_id_;
		int damage_class_id_;
		int effect_id_;
		int effect_chance_;
		int contest_type_id_;
		int contest_effect_id_;
		int super_contest_effect_id_;
	public:
		Move(int id, std::string identifier, int generation_id, int type_id, int power, int pp, int accuracy, int priority, int target_id, int damage_class_id, int effect_id, int effect_chance, int contest_type_id, int contest_effect_id, int super_contest_effect_id) : id_(id), identifier_(identifier), generation_id_(generation_id), type_id_(type_id), power_(power), pp_(pp), accuracy_(accuracy), priority_(priority), target_id_(target_id), damage_class_id_(damage_class_id), effect_id_(effect_id), effect_chance_(effect_chance), contest_type_id_(contest_type_id), contest_effect_id_(contest_effect_id), super_contest_effect_id_(super_contest_effect_id) {}
		int id() const {return id_;}
		std::string identifier() const {return identifier_;}
		int generation_id() const {return generation_id_;}
		int type_id() const {return type_id_;}
		int power() const {return power_;}
		int pp() const {return pp_;}
		int accuracy() const {return accuracy_;}
		int priority() const {return priority_;}
		int target_id() const {return target_id_;}
		int damage_class_id() const {return damage_class_id_;}
		int effect_id() const {return effect_id_;}
		int effect_chance() const {return effect_chance_;}
		int contest_type_id() const {return contest_type_id_;}
		int contest_effect_id() const {return contest_effect_id_;}
		int super_contest_effect_id() const {return super_contest_effect_id_;}
};

class Pokemon_Move{
	private:
		int pokemon_id_;
		int version_group_id_;
		int move_id_;
		int pokemon_move_method_id_;
		int level_;
		int order_;
	public:
		Pokemon_Move(int pokemon_id, int version_group_id, int move_id, int pokemon_move_method_id, int level, int order) : pokemon_id_(pokemon_id), version_group_id_(version_group_id), move_id_(move_id), pokemon_move_method_id_(pokemon_move_method_id), level_(level), order_(order){}
		int pokemon_id() const {return pokemon_id_;}
		int version_group_id() const {return version_group_id_;}
		int move_id() const {return move_id_;}
		int pokemon_move_method_id() const {return pokemon_move_method_id_;}
		int level() const {return level_;}
		int order() const {return order_;}
};

class Pokemon_Species{
	private:
		int id_;
		std::string identifier_;
		int generation_id_;
		int evolves_from_species_id_;
		int evolution_chain_id_;
		int color_id_;
		int shape_id_;
		int habitat_id_;
		int gender_rate_;
		int capture_rate_;
		int base_happiness_;
		int is_baby_;
		int hatch_counter_;
		int has_gender_differences_;
		int growth_rate_id_;
		int forms_switchable_;
		int is_legendary_;
		int is_mythical_;
		int order_;
		int conquest_order_;
	public:
		Pokemon_Species(int id, std::string identifier, int generation_id, int evolves_from_species_id, int evolution_chain_id, int color_id, int shape_id, int habitat_id, int gender_rate, int capture_rate, int base_happiness, int is_baby, int hatch_counter, int has_gender_differences, int growth_rate_id, int forms_switchable, int is_legendary, int is_mythical, int order, int conquest_order) : id_(id), identifier_(identifier), generation_id_(generation_id), evolves_from_species_id_(evolves_from_species_id), evolution_chain_id_(evolution_chain_id), color_id_(color_id), shape_id_(shape_id), habitat_id_(habitat_id), gender_rate_(gender_rate), capture_rate_(capture_rate), base_happiness_(base_happiness), is_baby_(is_baby), hatch_counter_(hatch_counter), has_gender_differences_(has_gender_differences), growth_rate_id_(growth_rate_id), forms_switchable_(forms_switchable), is_legendary_(is_legendary), is_mythical_(is_mythical), order_(order), conquest_order_(conquest_order){}
		int id() const {return id_;}
		std::string identifier() const {return identifier_;}
		int generation_id() const {return generation_id_;}
		int evolves_from_species_id() const {return evolves_from_species_id_;}
		int evolution_chain_id() const {return evolution_chain_id_;}
		int color_id() const {return color_id_;}
		int shape_id() const {return shape_id_;}
		int habitat_id() const {return habitat_id_;}
		int gender_rate() const {return gender_rate_;}
		int capture_rate() const {return capture_rate_;}
		int base_happiness() const {return base_happiness_;}
		int is_baby() const {return is_baby_;}
		int hatch_counter() const {return hatch_counter_;}
		int has_gender_differences() const {return has_gender_differences_;}
		int growth_rate_id() const {return growth_rate_id_;}
		int forms_switchable() const {return forms_switchable_;}
		int is_legendary() const {return is_legendary_;}
		int is_mythical() const {return is_mythical_;}
		int order() const {return order_;}
		int conquest_order() const {return conquest_order_;}
};

class Experience{
	private:
		int growth_rate_id_;
		int level_;
		int experience_;
	public:
		Experience(int growth_rate_id, int level, int experience) : growth_rate_id_(growth_rate_id), level_(level), experience_(experience){}
		int growth_rate_id() const {return growth_rate_id_;}
		int level() const {return level_;}
		int experience() const {return experience_;}
};

class Type_Name{
	private:
		int type_id_;
		int local_language_id_;
		std::string name_;
	public:
		Type_Name(int type_id, int local_language_id, std::string name) : type_id_(type_id), local_language_id_(local_language_id), name_(name){}
		int type_id() const {return type_id_;}
		int local_language_id() const {return local_language_id_;}
		std::string name() const {return name_;}
};

class Pokemon_Stat{
	private:
		int pokemon_id_;
		int stat_id_;
		int base_stat_;
		int effort_;
	public:
		Pokemon_Stat(int pokemon_id, int stat_id, int base_stat, int effort) : pokemon_id_(pokemon_id), stat_id_(stat_id), base_stat_(base_stat), effort_(effort){}
		int pokemon_id() const {return pokemon_id_;}
		int stat_id() const {return stat_id_;}
		int base_stat() const {return base_stat_;}
		int effort() const {return effort_;}
};

class Stat{
	private:
		int id_;
		int damage_class_id_;
		std::string identifier_;
		int is_battle_only_;
		int game_index_;
	public:
		Stat(int id, int damage_class_id, std::string identifier, int is_battle_only, int game_index) : id_(id), damage_class_id_(damage_class_id), identifier_(identifier), is_battle_only_(is_battle_only), game_index_(game_index){}
		int id() const {return id_;}
		int damage_class_id() const {return damage_class_id_;}
		std::string identifier() const {return identifier_;}
		int is_battle_only() const {return is_battle_only_;}
		int game_index() const {return game_index_;}
};

class Pokemon_Type{
	private:
		int pokemon_id_;
		int type_id_;
		int slot_;
	public:
		Pokemon_Type(int pokemon_id, int type_id, int slot) : pokemon_id_(pokemon_id), type_id_(type_id), slot_(slot){}
		int pokemon_id() const {return pokemon_id_;}
		int type_id() const {return type_id_;}
		int slot() const {return slot_;}
};

class DataCon{
	public:
		std::vector<Pokemon_Info> pokemon;
		std::vector<Move> moves;
		std::vector<Pokemon_Move> pokemon_moves;
		std::vector<Pokemon_Species> pokemon_species;
		std::vector<Experience> experience;
		std::vector<Type_Name> type_names;
		std::vector<Pokemon_Stat> pokemon_stats;
		std::vector<Stat> stats;
		std::vector<Pokemon_Type> pokemon_types;
		std::vector<Type_Name> otherLangues;
		float typeModGraph[18][18];


		/**
		 * @brief Construct a new DataCon object. Includes reserving the needed space in all of the vectors
		 * 
		 */
		DataCon();
};

/**
 * @brief The container for the data parsed from the files
 * 
 */
extern DataCon* pokeData;

/**
* @brief Prints a formated Pokemon object to the provided ostream
* 
* @param o The stream to print the class to
* @param s The Pokemon to print
* @return The stream with the class added
*/
std::ostream &operator<<(std::ostream &o,  const Pokemon_Info &s);
/**
* @brief Prints a formated Move object to the provided ostream
* 
* @param o The stream to print the class to
* @param s The Move to print
* @return The stream with the class added
*/
std::ostream &operator<<(std::ostream &o,  const Move &s);
/**
* @brief Prints a formated Pokemon_Move object to the provided ostream
* 
* @param o The stream to print the class to
* @param s The Pokemon_Move to print
* @return The stream with the class added
*/
std::ostream &operator<<(std::ostream &o,  const Pokemon_Move &s);
/**
* @brief Prints a formated Pokemon_Species object to the provided ostream
* 
* @param o The stream to print the class to
* @param s The Pokemon_Species to print
* @return The stream with the class added
*/
std::ostream &operator<<(std::ostream &o,  const Pokemon_Species &s);
/**
* @brief Prints a formated Experience object to the provided ostream
* 
* @param o The stream to print the class to
* @param s The Experience to print
* @return The stream with the class added
*/
std::ostream &operator<<(std::ostream &o,  const Experience &s);
/**
* @brief Prints a formated Type_Name object to the provided ostream
* 
* @param o The stream to print the class to
* @param s The Type_Name to print
* @return The stream with the class added
*/
std::ostream &operator<<(std::ostream &o,  const Type_Name &s);
/**
* @brief Prints a formated Pokemon_Stat object to the provided ostream
* 
* @param o The stream to print the class to
* @param s The Pokemon_Stat to print
* @return The stream with the class added
*/
std::ostream &operator<<(std::ostream &o,  const Pokemon_Stat &s);
/**
* @brief Prints a formated Stat object to the provided ostream
* 
* @param o The stream to print the class to
* @param s The Stat to print
* @return The stream with the class added
*/
std::ostream &operator<<(std::ostream &o,  const Stat &s);
/**
* @brief Prints a formated Pokemon_Type object to the provided ostream
* 
* @param o The stream to print the class to
* @param s The Pokemon_Type to print
* @return The stream with the class added
*/
std::ostream &operator<<(std::ostream &o,  const Pokemon_Type &s);


#endif