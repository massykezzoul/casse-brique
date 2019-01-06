#include <iostream>
#include <string>
#include "option.h"

using namespace std;

// La Classe Option

// Constructeurs
	Option::Option(){}
	
	Option::Option(Id id,const std::string& nom,char rac,Arg arg,const std::string& description)
		:identifiant(id),nom(nom),racourci(rac),argument(arg),description(description) {}

	Option::Option(Option const &copy) {
		identifiant = copy.get_identifiant();
		nom = (copy.get_nom());
		racourci = (copy.get_racourci());
		argument = (copy.get_argument());
		description = (copy.get_description());
	}


// les Getteurs
	Option::Id Option::get_identifiant() const {
		return identifiant;
	}
	std::string Option::get_nom() const {
		return nom;
	}
	char Option::get_racourci() const {
		return racourci;
	}
	Option::Arg Option::get_argument() const {
		return argument;
	}
	std::string Option::get_description() const {
		return description;
	}

	void Option::print() const {
		std::cout << "Identifiant : " << identifiant << std::endl
			<< "Nom : " << nom << std::endl
			<< "Racourci : " << racourci << std::endl
			<< "Type d'argumment : "<< argument << std::endl
			<< "Description : "<< description << std::endl;
	}

// Les setteurs

	void Option::set_identifiant(Option::Id id) {
		identifiant = id;
	}
	void Option::set_nom(const std::string& n) {
		nom = n;
	}
	void Option::set_racourci(char rac) {
		racourci = rac;
	}
	void Option::set_argument(Option::Arg arg) {
		argument = arg;
	}
	void Option::set_description(const std::string& des) {
		description = des;
	}

// La surchage de l'operator

	Option Option::operator=(Option const& copy) {
		if (this != &copy) {
			identifiant = copy.get_identifiant();
			nom = (copy.get_nom());
			racourci = (copy.get_racourci());
			argument = (copy.get_argument());
			description = (copy.get_description());
		}

		return *this;
	}



/* -------------------------------------------------------------------------- */
// La Classe Option_tab
// Ici se fait toute la gestion des paramètres
// Le Constructeur
Option_tab::Option_tab():nb(0){
	// Définition des options disponible
	Option opt1(Option::HELP,"help",'h',Option::NOPE,
		"Affiche les aides du programme");
	
	Option opt2(Option::VERSION,"version",'v',Option::NOPE,
		"Affiche la version du programme"); 

	Option opt3(Option::CONFIG,"config",'c',Option::STR,
		"Donne le fichier de configuration");

    Option opt4(Option::AUTEUR,"auteur",'a',Option::NOPE,
        "Donne le nom des auteur");
	/* 
	Pour l'ajout d'une option : 
	Option opt*i*(Option::Id*,"nom de l'option**",'raccourci**',Option::type_argument,
		"courte description");

		* L'identifiant de l'option (voir 'option.h' ligne:6)
		** Doivent ếtre Unique
	*/

	// Ajout des option définit dans un tableau d'option
	add(opt1);
	add(opt2);
	add(opt3);
	add(opt4);
}

// Les methodes 
void Option_tab::add(const Option &opt){
	// Vérifit si l'option n'existe pas déja dans le tableau
	if (get_option(opt.get_identifiant()) == -1) {	
		tab[nb] = opt;
		nb++;
	}
	else 
		std::cerr << "Identifiant déjà existant dans le tableau." <<std::endl<< std::endl;
}
void Option_tab::print() const{
	for (int i = 0; i < nb; ++i){
		tab[i].print();
		std::cout << std::endl;
	}
}
Option::Id Option_tab::cherche(const std::string &nom) const{
	for (int i = 0; i < nb; ++i) {
		if (tab[i].get_nom() == nom)
			return tab[i].get_identifiant();
	}
	return Option::NB_ID;
}
Option::Id Option_tab::cherche(const char rac) const{
	for (int i = 0; i < nb; ++i) {
		if (tab[i].get_racourci() == rac)
			return tab[i].get_identifiant();
	}
	return Option::NB_ID;
}

bool Option_tab::is_nom(std::string arg) const {
	if ((arg[0] == '-') && (arg[1] == '-') && (cherche(&arg[2]) != Option::NB_ID) )
		return true;
	else 
		return false;
}

bool Option_tab::is_raccourci(std::string arg) const {
	if ((arg[0] == '-') && (cherche(arg[1]) != Option::NB_ID) )
		return true;
	else 
		return false;
}

Option::Arg Option_tab::get_argument(const std::string &nom) const{
	for (int i = 0; i < nb; ++i) {
		if (tab[i].get_nom() == nom)
			return tab[i].get_argument();
	}
	return Option::NB_ARG;
}
Option::Arg Option_tab::get_argument(const Option::Id  id) const{
	for (int i = 0; i < nb; ++i) {
		if (tab[i].get_identifiant() == id)
			return tab[i].get_argument();
	}
	return Option::NB_ARG;
}
int Option_tab::get_option(const Option::Id id){
	int i = 0;
	while (i < nb) {
		if (tab[i].get_identifiant() == id)
			return i;
	++i;
	}
	if (i == nb)
		return -1;
}
Option const &Option_tab::get_option(int index) {
	if ((index >= 0) && (index < nb))
		return tab[index];
	else 
		std::cerr << "L'option n'a pas été trouvé" << std::endl;
}

void Option_tab::gere_parametre(int argc,char const *argv[],string& config_file) {
	int i = 1;
	int j = -1;
	int vitesse = -1;
	string config = "";
	Option::Id id = Option::NB_ID;

	while (i < argc) {
		j = -1;
		id = Option::NB_ID;
		if (is_nom(argv[i])) {
			// Est une option avec son nom long spécifié
			j = get_option(cherche(&argv[i][2]));
		} else if (is_raccourci(argv[i])){
			// Est une option avec son raccourci spécifié
			j = get_option(cherche(argv[i][1]));
		}

		/* j étant l'id de l'option */
		switch (j) {
			case 0:
				/* help */
				cout << "Utilisation du programme : " << endl
					<< "\t./casse-brique [OPTION] [ARGUMENTS]" << endl
					<< "Les Arguments disponible sont : " << endl
					<< "\t-h, --help    : Affiche cette aide puis quitte le programme" << endl
					<< "\t-v, --version : Affiche la version du programme et quitte" << endl
					<< "\t-a, --auteur  : Affiche les auteurs du programme et quitte" << endl
					<< "\t-c, --config [ARGUMENT] : Changer le fichier de configuration" << endl;


				exit(0);
				break;
			case 1:
				/* version */
				cout << "Casse-brique 1.0.0" << endl;
				
				exit(0);
				break;
			case 2:
				/* config */
				if ((i + 1 < argc)  &&  (argv[i+1][0] != '-')) {
					++i; // passe à l'argument de l'option
					config = argv[i]; // recupere la chaine
					cout << "Fichier de configuration : '" << config <<"'." << endl;
					getchar();
				} else {
					cerr << "Argument manquant pour '" << argv[i] <<"'"
						<< endl;
					exit(1);
				}	
				break;
			case 3:
				/* Auteur */
				cout << "Les auteurs de ce programme sont : " << endl
					<< "\tKezzoul massili -> Massili.kezzoul@etu.umontpellier.fr"<< endl
					<< "\tBoyan" << endl 
					<< "\tRomain" << endl
					<< "\tYann" << endl;
				exit(0);
				break;
			default:
				cerr << "L'option \"" << argv[i] 
					<< "\" n'existe pas" << endl;
				
				cout << "Utilisation du programme : " << endl
					<< "\t./casse-brique [OPTION] [ARGUMENTS]" << endl
					<< "Les Arguments disponible sont : " << endl
					<< "\t-h, --help    : Affiche l'aide d'utilisation puis quitte le programme" << endl
					<< "\t-v, --version : Affiche la version du programme et quitte" << endl
					<< "\t-a, --auteur  : Affiche les auteurs du programme et quitte" << endl
					<< "\t-c, --config [ARGUMENT] : Changer le fichier de configuration" << endl;
				exit(1);
				break;
			}
			++i;
	}
	if (config != "" ) config_file = config;
}
