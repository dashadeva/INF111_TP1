/**
 * Le jeu consiste a trouver une equation qui resout le probleme donne. A l'aide de 
 * la liste de six nombres donnee par le programme et d'un nombre d'operations determine, 
 * l'utilisateur doit trouver comment arriver a la solution demandee. 
 * 
 * @ authors Ryad Malik Meftahi, Darya Nurshina
 * @ version Hiver2019
 */


import javax.swing.JOptionPane;

public class MainTP1 {

	public static void main(String[] args) {

		//Le tableau vide pour 6 nombres est genere et on suppose que le joueur veut jouer au moins
		//une fois
		Nombre[] nombres = new Nombre[6]; 
		boolean quitter = false;
		char[] expression = new char[100];
		int nombreOperation; 
		int cible;
		char rejouer;

		//On initialise le jeu, affiche les regles et on le continue en boucle tant que l'utilisateur ne
		//choisisse pas de quitter
		afficherEntete();

		while (quitter==false) {

			genererNombres(nombres);
			nombreOperation = UtilitaireFonctionsMath.alea(1, 5);
			initExpression(expression);

			//On affiche les nombres choisis, la cible a atteindre et le nombre d'operations
			//permises

			cible = genererValeurCible(nombres, nombreOperation, expression);
			System.out.println("Cible : "+cible);

			rejouer = effectuerTour(nombres, nombreOperation, cible, expression );

			//Tant que l'utilisateur choisit de rejouer, on relance la boucle. Sinon, le jeu
			//s'arrete
			if(rejouer == 'o') {
				quitter = false;
			} else if (rejouer == 'n') {
				quitter = true;
			}

		}

	}

	/**
	 * La fonction sert a prendre les saisies de l'utilisateur pour les nombres et les operations.
	 * Elle effectue le calcul mathematique des operations rentrees.
	 * Pour terminer la fonction lors des saisies, l'utilisateur doit rentrer -1 pour un chiffre ou un '='
	 * pour l'operation.
	 * 
	 * @param nombres: les nombres contenus dans le tableau Nombre
	 * @param compteurOperation: variable qui compte le nombre des operations effectuees
	 * @param nombreOperation: le nombre d'operations permises pour la partie
	 * @return resultat: le resultat de l'operation efectuee
	 */
	public static int obtenirResultatValide(Nombre[] nombres, int compteurOperation, int nombreOperation) {

		//Les booleens du tableau de nombres sont mis a faux 
		int resultat;
		int nombre2;
		char operateur;

		initBoolean(nombres);

		//Le nombre saisi doit etre valide, existant dans la table Nombres et non utilise auparavant.
		//Il est garde dans la variable resultat
		resultat = nombreValideClavier(nombres);

		//Si le resultat n'est pas egal a -1, son booleen est ajuste a vrai pour marquer que le nombre
		//a ete choisi
		if(resultat!=-1) {
			ajusterNombreChoisi(resultat, nombres);
		}

		//Tant que le resultat n'est pas -1 et que le nombre d'operations permises n'est pas depasse,
		//on saisit un operateur.
		while (resultat != -1 && compteurOperation < nombreOperation) {
			operateur = operateurValideClavier();

			//Si l'opérateur n'est pas un '=', on saisit un deuxième nombre. L'opération mathématique entre 
			//les deux nombres s'effectue et se garde dans la variable resultat. Le compteur des opérations est
			//incrementé.			
			if(operateur != '=') {
				nombre2 = nombreValideClavier(nombres);
				if(nombre2 != -1) {
					ajusterNombreChoisi(nombre2, nombres);

					resultat = resultatOperation(resultat, operateur, nombre2);
					compteurOperation++;
					System.out.println("le resultat de l'operation : "+resultat);
					//Dans le cas d'irrespect des consignes, le resultat est assigné une valeur de -1 et la boucle 
					//s'arrête.
				} else {
					resultat = -1;
				}
			} else {
				resultat = -1;
			}
		}
		System.out.println("Resultat retourne: "+resultat);
		return resultat;
	}


	/**
	 * La fonction qui met le jeu à derouler. Affiche les règles et les conditions du jeu;
	 * le messages correspondant au résultat obtenu ainsi que le résultat de l'opération
	 * @param nombres: les nombres contenus dans le tableau Nombre
	 * @param nombreOperation: le nombre d'opérations permises pour la partie
	 * @param cible: le resultat à atteindre
	 * @param expression: solution de l'équation
	 * @return rejouer: contient le choix de rejouer ou pas
	 */
	public static char effectuerTour(Nombre[] nombres, int nombreOperation, 
			int cible, char[] expression) {
		int resultat;
		int compteurOperation = 0;
		char rejouer;

		//On affiche les nombres, le nombre d'opérations permises et la cible
		//Le résultat des opérations est affiché
		do {
			afficherNombres(nombres, nombreOperation, cible);
			resultat = obtenirResultatValide(nombres, compteurOperation, nombreOperation );
			System.out.println(resultat);

			//Si le résultat est égal à la cible, on affiche les félicitations
			//Sinon, on affiche que ce n'est pas le bon résultat
			if (resultat == cible) {
				afficherMessage("BRAVO!!!!!!!!!!!!");
			} else if (resultat != -1) {
				afficherMessage("Ce n'est pas le bon resultat.");
				resultat = -1;
			}

		} 

		//On affiche une solution et demande à l'utilisateur s'il veut rejouer		
		while ( resultat != -1 && resultat != cible );
		afficherExpression(expression);
		rejouer = veutRejouer();
		return rejouer;

	}


	/**
	 * 	Fonction que effectue le fonctionnement du jeu. Genere un resultat avec les nombres entres
	 * en respectant le nombre d'operations permises et les regles du jeu.  
	 * Possede un code retour dans le cas d'une operation pas permise. Si le code est retourné, 
	 * la fonction choisit une autre operation.
	 * 
	 * @param nombres: les nombres contenus dans le tableau Nombre
	 * @param nombreOperation: le nombre d'operations permises pour la partie
	 * @param expression: solution de l'equation
	 * @return cible: le resultat de l'operation
	 */
	public static int genererValeurCible(Nombre[] nombres, int nombreOperation, char[] expression) {


		int cible;
		int nombre2;
		int compteurOperation=0;
		int resultatOperation;
		int nouvelleTaille = 0;

		//Deux nombres pas déjà choisis sont choisis et leurs boolééns sontajustés à vrai
		cible = nombreChoisiHasard(nombres);
		ajusterNombreChoisi(cible, nombres);

		nombre2 = nombrePasDejaChoisi(nombres);
		ajusterNombreChoisi(nombre2, nombres);

		//Tant que le nombre déterminé d'opérations n'a pas été atteint, on demande une
		//prochaine opération et effectue le calcul
		while(compteurOperation < nombreOperation) {

			char operateur = operateurHasard();
			resultatOperation = resultatOperation(cible, operateur, nombre2);

			//Si le résultat est différent de -1, les nouveaux éléments sont ajoutés dans l'équation
			if (resultatOperation!=-1) {

				nouvelleTaille = creerExpression(expression, nouvelleTaille, cible, operateur, nombre2, resultatOperation);
				cible = resultatOperation;

				//S'il reste des opérations à effectuer, on choisi un autre nombre pas déjà choisi 
				//et on ajuste son booléén. Le compteur des opérations est incrementé.
				if (compteurOperation <= nombreOperation) {
					nombre2 = nombrePasDejaChoisi(nombres);
					ajusterNombreChoisi(nombre2, nombres);

				}
				compteurOperation++;
			}
		}

		return cible;




	}


	/**
	 * Methode qui initialise le tableau Nombre avec des nombres aléatoires entre
	 * 1 et 10 et met les booleens accordants a faux.
	 * 
	 * @param nombres: les nombres contenus dans le tableau Nombre
	 */
	public static void genererNombres(Nombre[] nombres) {

		for (int i = 0; i < nombres.length; i++) {
			nombres[i] = new Nombre(); 
			nombres[i].nombre=UtilitaireFonctionsMath.alea(1, 10);
			nombres[i].choisi = false;
		}
	}

	/**
	 * Methode qui initialise le tableau des caracteres de l'expression avec une
	 * valeur par defaut vide
	 * 
	 * @param tabChar: longueur du tableau de caracteres
	 */
	public static void initExpression(char[] tabChar) {

		for (int i = 0; i < tabChar.length; i++) {
			tabChar[i] = ' ';
		}
	}

	/**
	 * Methode qui reinitialise les booleens du tableau nombres a faux.
	 * @param nombres
	 */
	public static void initBoolean(Nombre[] nombres) {

		for (int i = 0; i < nombres.length; i++) {
			nombres[i].choisi = false;
		}
	}

	/**
	 * Methode qui retourne un operateur hasard en charactère parmi {+, -, /, *}.
	 * 
	 * @return operateur: operateur en char
	 */
	public static char operateurHasard() {

		//On choisit un nombre aléatoire entre 0 et 3
		int aleatoire = UtilitaireFonctionsMath.alea(0, 3);
		char operateur = 'z';

		//L'operateur devient celui qui correspond au nombre aléatoire
		if (aleatoire == 0) {
			operateur = '+';
		} else if (aleatoire == 1) {
			operateur = '-';
		} else if (aleatoire == 2) {
			operateur = '/';
		} else if (aleatoire == 3) {
			operateur = '*';
		}

		return operateur;
	}

	/**
	 * Methode qui choisit un nombre faisant partie du tableau Nombre
	 * 
	 * @param nombres: les nombres contenus dans le tableau Nombre
	 * @return nombres[indexAleatoire].nombre: le nombre choisi
	 */
	public static int nombreChoisiHasard(Nombre[] nombres) {

		//On choisit un nombre aleatoire entre 0 et 5 et il devient l'index du nombre
		//a choisir dans le tableau de nombres
		int indexAleatoire = UtilitaireFonctionsMath.alea(0, 5);
		return nombres[indexAleatoire].nombre;
	}

	/**
	 * Methode qui cherche si le nombre choisi fait partie du tableau et s'il
	 * n'a pas encore ete choisi.
	 * 
	 * @param nombre: le nombre choisi
	 * @param nombres: les nombres contenus dans le tableau Nombre
	 * @return existe: booleen qui determine si le nombre choisi respecte les consignes
	 */
	public static boolean nombreExiste(int nombre, Nombre[] nombres) {

		//La variable existe est false par defaut
		boolean existe = false;

		//On verifie dans tous les elements du tableau si le nombre choisi en fait partie,
		//qu'il n'a pas encore été choisi et si c'est le cas, variable existe devient vrai.
		for (int i = 0; i < nombres.length; i++) {
			if(nombres[i].nombre == nombre && nombres[i].choisi == false) {
				existe = true;
			}
		}
		return existe;
	}

	/**
	 * Methode qui retourne le resultat de l'operation demandee.
	 * 
	 * @param nombre1: premier nombre choisi pour l'operation
	 * @param operateur: l'operateur de l'operation
	 * @param nombre2: prochain nombre choisi pour l'operation
	 * @return resultat: le resultat de l'expression
	 */
	public static int resultatOperation(int nombre1, char operateur, int nombre2) {
		int resultat = 0;

		//On effectue l'operation selon l'operateur qui entre
		if (operateur == '*') {
			resultat = nombre1*nombre2;
		} else if (operateur == '+') {
			resultat = nombre1 + nombre2;
		} else if (operateur == '/') {

			//On verifie que l'operation n'a pas de reste, et si oui, le resultat devient -1
			if ((nombre1 % nombre2)==0) {
				resultat = nombre1/nombre2;
			} else {
				resultat = -1;
			}

		} else if (operateur == '-') {
			resultat = nombre1 - nombre2;
		}

		return resultat;
	}

	/**
	 * Methode qui recherche le nombre choisi correspondant dans le tableau Nombre et
	 * met son booleen a vrai pour signaler qu'il a ete choisi.
	 * 
	 * @param nombre: le nombre choisi
	 * @param nombres: les nombres contenus dans le tableau Nombre
	 */
	public static void ajusterNombreChoisi(int nombre, Nombre[] nombres) {
		boolean trouve = false;
		int index = 0;

		//Tant que le nombre n'a pas ete trouve et que la liste n'a pas ete parcourue au complet
		//on cherche le nombre choisi 
		while (trouve == false && index < nombres.length) {
			if (nombres[index].nombre == nombre && nombres[index].choisi == false) {
				trouve = true;
				nombres[index].choisi = true;
			}
			index++;
		}
	}

	/**
	 * Methode qui retourne un nombre du tableau qui n'a pas ete encore choisi
	 * 
	 * @param nombres: les nombres contenus dans le tableau Nombre
	 * @return nombres[index].nombre: un nombre du tableau qui n'a pas encore ete choisi
	 */
	public static int nombrePasDejaChoisi(Nombre[] nombres) {
		boolean trouve = false;
		int index = 0;

		//On parcours les nombres tant qu'on trouve pas un pas deja choisi. 
		while (trouve == false && index < nombres.length-1) {

			//Si le nombre actuel n'a pas ete choisi auparavant, la variable trouve devient vraie.
			if (nombres[index].choisi == false) {
				trouve = true;

				//Autrement, on incremente l'index.
			} else {
				index++;
			}
		}

		return nombres[index].nombre;
	}

	/**
	 * Methode qui ajoute la chaine de caracteres a la suite dans le tableau de caracteres.
	 * 	
	 * @param tabChar: tableau de caracteres
	 * @param tailleInitiale: la taille initiale du tableau
	 * @param nouvelleChaine:la nouvelle chaine ajoutee
	 * @return tailleInitiale+nouvelleChaine.length(): nouvelle taille du tableau de caracteres
	 */
	public static int concatenerNombre(char[] tabChar, int tailleInitiale, String nouvelleChaine) {
		char nouveauChar='z';

		//Pour la longueur de la nouvelle chaine, on insere les caracteres un par un dans le tableau
		//des caracteres en additionnant l'indice courant a la taille initiale du tableau
		for (int i = 0; i < nouvelleChaine.length(); i++) {

			nouveauChar = nouvelleChaine.charAt(i);

			tabChar[i+tailleInitiale] = nouveauChar;
		}

		return tailleInitiale+nouvelleChaine.length();
	}


	/**
	 * Methode qui fait la concatenation des valeurs recues pour donner une nouvelle expression
	 * 
	 * @param expression: le contenu du tableau de caracteres
	 * @param taille: la taille de l'expression
	 * @param operande1: premier element de l'operation
	 * @param operateur: l'operation a effectuer
	 * @param operande2: deuxieme element de l'operation
	 * @param resultat: le resultat de l'operation
	 * @return taille+toAdd.length(): la nouvelle taille du tableau de caracteres
	 */
	public static int creerExpression(char[] expression, int taille, int operande1, char operateur, int operande2, int resultat) {

		//La chaine de caracteres a rajouter au tableau de caracteres
		String toAdd = "\n"+operande1+operateur+operande2+"="+resultat;

		concatenerNombre(expression, taille, toAdd);

		return taille+toAdd.length();
	}

	/**
	 * Methode  qui affiche la fenetre initiale du jeu avec les nombres choisis, le nombre d'operations
	 * oermises et la cible a atteindre
	 * 
	 * @param nombres: les nombres contenus dans le tableau Nombre
	 * @param nbOperation: nombre d'operations permises
	 * @param cible: la cible a atteindre
	 */
	public static void afficherNombres(Nombre[] nombres, int nbOperation, int cible) {

		String nombreDisplay = tabToString(nombres);

		String messageTest 	= "*********************************************\n"
				+ "               Liste des nombres \n"
				+ "*********************************************\n"
				+ 					nombreDisplay+"\n"
				+ "Nombre d'opérations obligatoires: "+nbOperation+"\n"
				+ "La cible est: "+cible+"\n";

		JOptionPane.showMessageDialog(null, messageTest);

	}

	/**
	 * Methode qui transforme le tableau Nombre en une chaine de caracteres
	 * 
	 * @param nombres: les nombres contenus dans le tableau Nombre
	 * @return nombreDisplay: la chaine de caracteres des nombres
	 */
	public static String tabToString(Nombre[] nombres) {

		String nombreDisplay ="";

		//On transforme les elements de Nombre un par un, en caracteres avec des espaces entre eux
		for (int i = 0; i < nombres.length; i++) {
			nombreDisplay+="        "+nombres[i].nombre;
		}

		return nombreDisplay;

	}

	/**
	 * Methode qui affiche les elements du tableau Nombre qui n'ont pas deja ete choisis
	 * 
	 * @param nombres: les nombres contenus dans le tableau Nombre
	 * @return nombreDisplay: les nombres qui n'ont pas deja ete choisis
	 */
	public static String tabToStringPasChoisi(Nombre[] nombres) {

		String nombreDisplay ="";

		//Pour tous les elements de Nombre, on cherche ceux qui n'ont pas ete choisis et on les ajoute
		//dans la chaine de caracteres
		for (int i = 0; i < nombres.length; i++) {

			if(!nombres[i].choisi) {
				nombreDisplay+=" "+nombres[i].nombre;
			}
		}

		return nombreDisplay;

	}

	/**
	 * Methode qui demande un nombre valide qui se trouve dans la liste et qui n'a pas ete choisi,
	 * tant et aussi longtemps que l'entree ne soit pas correcte.
	 * 
	 * @param nombres
	 * @return
	 */
	public static int nombreValideClavier(Nombre[] nombres) {
		int nombreChoisi = 0;

		//On affiche la liste de nombres disponibles et demande d'en choisir un 
		String message = "Entrez un nombre existant dans la liste et non déjà utilisé ou -1 pour annuler. ("
				+tabToStringPasChoisi(nombres)+" )";
		String reponse = "Rien";
		boolean valide = false;

		//L'utilisateur entre un nombre
		do {
			try 
			{ 
				reponse = JOptionPane.showInputDialog(null, message);
				nombreChoisi = Integer.parseInt(reponse); 
			}  
			//Si on fait une entree pas valide, on affiche un message d'erreur
			catch (NumberFormatException e)  
			{ 
				afficherMessage("\""+reponse+"\" n'est pas un nombre valide");
			} 

			//Si le nombre choisi n'est pas egal a -1 et qu'il fait partie de Nombre, 
			//on le considere valide
			if((nombreExiste(nombreChoisi, nombres) ) || ( nombreChoisi == -1)) {

				valide = true;
			}
		} while(valide == false);

		return nombreChoisi;
	}

	/**
	 * Methode qui affiche la fenetre d'input de l'utilisateur et qui valide l'operateur entre.
	 * 
	 * @return operateur: l'operateur choisi et valide
	 */
	public static char operateurValideClavier() {

		char operateur = 'z';
		String message = "Entrez un operateur (+,-,*,/ ou = pour annuler)";
		String reponse;

		//On demande d'entrer un operateur
		//Tant que l'operateur ne fait partie des operateurs permis ou que la longueur entree depasse 1 caractere
		//on redemande d'entrer un operateur valide
		do {
			reponse = JOptionPane.showInputDialog(null, message);
		} while(reponse.length()!=1 || (!reponse.equals("+") && !reponse.equals("-") && !reponse.equals("/") 
				&& !reponse.equals("*") && !reponse.equals("=")) );
		operateur = reponse.charAt(0);

		return operateur;
	}

	/**
	 * Methode qui affiche les regles du jeu.
	 */
	public static void afficherEntete() {

		String message 	= 
				"Le jeu consiste à trouver une valeur cible en utilisant un nombre d'opérations fixé à"
						+ "-l'avance et une liste de nombres fournie. \n\n\n"
						+ "-Un nombre peut se répéter dans la liste fournie +\n"
						+ "-Les seules opérations permises sont : +, -, * et /\n"
						+ "-Un nombre de la liste ne peut être utilisé qu'une fois dans la solution\n"
						+ "-En tout temps la valeur -1 annule l'opération en cours";

		JOptionPane.showMessageDialog(null, message);

	}

	/**
	 * Methode qui affiche l'expression de la solution.
	 * 
	 * @param expression: l'expression de la solution
	 */
	public static void afficherExpression(char[] expression) {

		String message 	= 
				"Une solution: \n"
						+ new String(expression);

		JOptionPane.showMessageDialog(null, message);


	}

	/**
	 * Methode qui demande a l'utilisateur s'il veut rejouer.
	 * 
	 * @return reponseChar: la reponse si l'utilisateur veut rejouer
	 */
	public static char veutRejouer() {

		char reponseChar = 'z';
		String message = "Voulez-vous rejouer une partie (o/n)";
		String reponse;

		//On demande a l'utilisateur s'il veut rejouer. La boucle continue tant que la longueur des caracteres 
		//rentres depasse 1 et qu'elle ne soie pas egale a 'o' ou 'n'.

		do {
			reponse = JOptionPane.showInputDialog(null, message);
		} while(reponse.length()!=1 || (!reponse.equals("o") && !reponse.equals("n")) );
		reponseChar = reponse.charAt(0);

		return reponseChar;
	}

	/**
	 * Methode qui affiche une fenetre avec un message.
	 * 
	 * @param message: le message a afficher
	 */
	public static void afficherMessage(String message) {

		JOptionPane.showMessageDialog(null, message);
	}


}
