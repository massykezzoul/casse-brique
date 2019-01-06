#ifndef OPTION_H
#define OPTION_H

class Option {
public:
	/* L'identifiant de l'option */
	enum Id {
		HELP = 0,
		VERSION,
		CONFIG, /* Spécifier le nom du fichier de configuration */
        AUTEUR, /* Donne le nom des auteurs de ce programme */
		NB_ID
	};

	/* Le type d'argument que prend cette option */
	enum Arg {
		INT = 0,
		FLOAT,
		CHAR,
		STR,
		NOPE,
		NB_ARG
	};

private:
	Id identifiant;			 // l'identifiant de l'option
	std::string nom; 		 // intitulé de l'option
	char racourci; 			 // bah .., le nom est clair je crois
	Arg argument;    		 // Le type eventuelle de son argument 
	std::string description; // Description de ce que fait l'option


public:
	Option(); /* Constructeur par défault (à enlever peut-être car je ne vois pas à quoi il sert :/ ) */
	Option(Id,const std::string&,char,Arg,const std::string&);

	//Constructeur par copie
	Option(Option const &copy);

	// Les getteurs
	Id get_identifiant() const;
	std::string get_nom() const;
	char get_racourci() const;
	Arg get_argument() const;
	std::string get_description() const;

	//	Affiche l'option (Pour le test)
	void print() const;

	//	Les setteurs
	void set_identifiant(Id);
	void set_nom(const std::string&);
	void set_racourci(char);
	void set_argument(Arg);
	void set_description(const std::string&);

	//	Surcharge de l'operateur d'affectation
	Option operator=(Option const&);

};

/* ---------------------------------------------------- */
/* La Classes Option_tab qui est un tableau d'option 	*/

/* Le nombre maximum d'option dans le tableau */
/* 
	TODO : 
		Tableau dynamique (mais j'ai la flemme pour l'instant o:D )
*/
#define OPTION_TAB_MAX 10

class Option_tab {
private:
	size_t nb;
	Option tab[OPTION_TAB_MAX];

public:
	// La définitions des options est prise en charge par le constructeur
	Option_tab();

	//Permet d'ajouter une Option au tableau
	void add(const Option &opt);

	//Afficher les options enregistrées dans le tableau
	void print() const;

	//Renvoie l'identifiant de l'option dont le nom est donné en paramètre
	Option::Id cherche(const std::string &nom) const;

	//Renvoie l'identifiant de l'option dont le racourci est donné en paramètre
	Option::Id cherche(const char rac) const;

	//Renvoie Vrai si la chaine est un nom d'une option
	bool is_nom(std::string) const;

	//Renvoie Vrai si la chaine est un raccourci d'une option
	bool is_raccourci(std::string) const;

	/*
		Etant donné un nom (court ou long) d’option,
		la fonction donne si un argument est requis  et son type le cas échéant. 
	*/  
	Option::Arg get_argument(const std::string &nom) const;

    Option::Arg get_argument(const Option::Id) const;

	// Return l'index de l'option selon son identifiant (retourne -1 si n'existe pas)
	int get_option(const Option::Id id);

	// Prend la position d'une option dans le tableau et retourne cette option
	Option const &get_option(unsigned int index);

	/*
		La méthode qui sera Utilisé par le programme principal
		Donnée 	: argc le nombre d'argument du programme, et argv l'ensembre des arguments du programme principal
		Resultat: Applique les modifications fournit en arguments

		PS : Peut-être que ce n'est pas sa place mais a voir plus tard
	*/
	void gere_parametre(int argc,char const *argv[],std::string& config_file);

};


#endif 