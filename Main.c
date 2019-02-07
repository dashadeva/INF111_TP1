/**
 * Le jeu consiste à trouver une équation qui résout le problème donné. À l'aide de 
 * la liste de six nombres donnée par le programme et d'un nombre d'opérations déterminé, 
 * l'utilisateur doit trouver comment arriver à la solution demandée. 
 * 
 * @ authors Ryad Malik Meftahi, Darya Nurshina
 * @ version Hiver2019
 */


import javax.swing.JOptionPane;

public class MainTP1 {

	public static void main(String[] args) {
		
//Le tableau vide pour 6 nombres est généré et on suppose que le joueur veut jouer au moins
//une fois
		Nombre[] nombres = new Nombre[6]; 
		boolean quitter = false;
		char[] expression = new char[100];
		int nombreOperation; 
		int cible;
		char rejouer;

//On initialise le jeu, affiche les règles et on le continue en boucle tant que l'utilisateur ne
//choisisse pas de quitter
		afficherEntete();

		while (quitter==false) {

			genererNombres(nombres);
			nombreOperation = UtilitaireFonctionsMath.alea(1, 5);
			initExpression(expression);

//On affiche les nombres choisis, la cible à atteindre et le nombre d'opérations
//permises

			cible = genererValeurCible(nombres, nombreOperation, expression);
			System.out.println("Cible : "+cible);

			rejouer = effectuerTour(nombres, nombreOperation, cible, expression );

//Tant que l'utilisateur choisit de rejouer, on relance la boucle. Sinon, le jeu
//s'arrête
			if(rejouer == 'o') {
				quitter = false;
			} else if (rejouer == 'n') {
				quitter = true;
			}

		}

	}

/**
 * La fonction sert à prendre les saisies de l'utilisateur pour les nombres et les opérations.
 * Elle effectue le calcul mathématique des opérations rentrées.
 * Pour terminer la fonction lors des saisies, l'utilisateur doit rentrer -1 pour un chiffre ou un '='
 * pour l'opération.
 * 
 * @param nombres: les nombres contenus dans le tableau Nombre
 * @param compteurOperation: variable qui compte le nombre des opérations effectuées
 * @param nombreOperation: le nombre d'opérations permises pour la partie
 * @return resultat: le resultat de l'operation efectuée
 */
	public static int obtenirResultatValide(Nombre[] nombres, int compteurOperation, int nombreOperation) {

//Les boolééns du tableau de nombres sont mis à faux 
		int resultat;
		int nombre2;
		char operateur;

		initBoolean(nombres);

//Le nombre saisi doit être valide, existant dans la table Nombres et non utilisé auparavant.
//Il est gardé dans la variable resultat
		resultat = nombreValideClavier(nombres);

//Si le résultat n'est pas égal à -1, son booléén est ajusté à vrai pour marquer que le nombre
//a été choisi
		if(resultat!=-1) {
			ajusterNombreChoisi(resultat, nombres);
		}

//Tant que le résultat n'est pas -1 et que le nombre d'opérations permises n'est pas dépassé,
//on saisit un opérateur.
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
 * 	Fonction que effectue le fonctionnement du jeu. Génère un résultat avec les nombres entrés
 * en respectant le nombre d'opérations permises et les règles du jeu.  
 * 
 * @param nombres
 * @param nombreOperation
 * @param expression
 * @return
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
 * 
 * @param nombres
 */
	public static void genererNombres(Nombre[] nombres) {

		for (int i = 0; i < nombres.length; i++) {
			nombres[i] = new Nombre(); 
			nombres[i].nombre=UtilitaireFonctionsMath.alea(1, 10);
			nombres[i].choisi = false;
		}
	}

/**
 * 
 * @param tabChar
 */
	public static void initExpression(char[] tabChar) {

		for (int i = 0; i < tabChar.length; i++) {
			tabChar[i] = ' ';
		}
	}

/**
 * 
 * @param nombres
 */
	public static void initBoolean(Nombre[] nombres) {

		for (int i = 0; i < nombres.length; i++) {
			nombres[i].choisi = false;
		}
	}

/**
 * 
 * @return
 */
	public static char operateurHasard() {

		int aleatoire = UtilitaireFonctionsMath.alea(0, 3);
		char operateur = 'z';

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
 * 
 * @param nombres
 * @return
 */
	public static int nombreChoisiHasard(Nombre[] nombres) {

		int indexAleatoire = UtilitaireFonctionsMath.alea(0, 5);
		return nombres[indexAleatoire].nombre;
	}

/**
 * 
 * @param nombre
 * @param nombres
 * @return
 */
	public static boolean nombreExiste(int nombre, Nombre[] nombres) {

		boolean existe = false;
		for (int i = 0; i < nombres.length; i++) {
			if(nombres[i].nombre == nombre && nombres[i].choisi == false) {
				existe = true;
			}
		}
		return existe;
	}

/**
 * 
 * @param nombre1
 * @param operateur
 * @param nombre2
 * @return
 */
	public static int resultatOperation(int nombre1, char operateur, int nombre2) {
		int resultat = 0;

		if (operateur == '*') {
			resultat = nombre1*nombre2;
		} else if (operateur == '+') {
			resultat = nombre1 + nombre2;
		} else if (operateur == '/') {
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
 * 
 * @param nombre
 * @param nombres
 */
	public static void ajusterNombreChoisi(int nombre, Nombre[] nombres) {
		boolean trouve = false;
		int index = 0;
		while (trouve == false && index < nombres.length) {
			if (nombres[index].nombre == nombre && nombres[index].choisi == false) {
				trouve = true;
				nombres[index].choisi = true;
			}
			index++;
		}
	}

/**
 * 
 * @param nombres
 * @return
 */
	public static int nombrePasDejaChoisi(Nombre[] nombres) {
		boolean trouve = false;
		int index = 0;

		while (trouve == false && index < nombres.length-1) {
			if (nombres[index].choisi == false) {
				trouve = true;
			} else {
				index++;
			}
		}

		return nombres[index].nombre;
	}

/**
 * 	
 * @param tabChar
 * @param tailleInitiale
 * @param nouvelleChaine
 * @return
 */
	public static int concatenerNombre(char[] tabChar, int tailleInitiale, String nouvelleChaine) {

		char nouveauChar='z';
		for (int i = 0; i < nouvelleChaine.length(); i++) {
			//System.out.print(nouveauChar);
			nouveauChar = nouvelleChaine.charAt(i);
			//System.out.print(nouveauChar);
			tabChar[i+tailleInitiale] = nouveauChar;
		}

		return tailleInitiale+nouvelleChaine.length();
	}

/**
 * 
 * @param expression
 * @param taille
 * @param operande1
 * @param operateur
 * @param operande2
 * @param resultat
 * @return
 */
	public static int creerExpression(char[] expression, int taille, int operande1, char operateur, int operande2, int resultat) {

		String toAdd = "\n"+operande1+operateur+operande2+"="+resultat;

		concatenerNombre(expression, taille, toAdd);

		return taille+toAdd.length();
	}

	/**
	 * 
	 * @param nombres
	 * @param nbOperation
	 * @param cible
	 */
	public static void afficherNombres(Nombre[] nombres, int nbOperation, int cible) {

		String nombreDisplay = tabToString(nombres);

		String messageTest 	= "*********************************************\n"
				+ "               Liste des nombres \n"
				+ "*********************************************\n"
				+ 					nombreDisplay+"\n"
				+ "Nombre d'op�rations obligatoires: "+nbOperation+"\n"
				+ "La cible est: "+cible+"\n";

		JOptionPane.showMessageDialog(null, messageTest);

	}

	/**
	 * 
	 * @param nombres
	 * @return
	 */
	public static String tabToString(Nombre[] nombres) {

		String nombreDisplay ="";
		for (int i = 0; i < nombres.length; i++) {
			nombreDisplay+="        "+nombres[i].nombre;
		}

		return nombreDisplay;

	}

	/**
	 * 
	 * @param nombres
	 * @return
	 */
	public static String tabToStringPasChoisi(Nombre[] nombres) {

		String nombreDisplay ="";
		for (int i = 0; i < nombres.length; i++) {
			if(!nombres[i].choisi) {
				nombreDisplay+=" "+nombres[i].nombre;
			}
		}

		return nombreDisplay;

	}

	/**
	 * 
	 * @param nombres
	 * @return
	 */
	public static int nombreValideClavier(Nombre[] nombres) {

		int nombreChoisi = 0;
		String message = "Entrez un nombre existant dans la liste et non d�j� utilis� ou -1 pour annuler. ("
				+tabToStringPasChoisi(nombres)+" )";
		String reponse = "Rien";
		boolean valide = false;

		do {
			try 
			{ 
				reponse = JOptionPane.showInputDialog(null, message);
				nombreChoisi = Integer.parseInt(reponse); 
			}  
			catch (NumberFormatException e)  
			{ 
				afficherMessage("\""+reponse+"\" n'est pas un nombre valide");
			} 

			if((nombreExiste(nombreChoisi, nombres) ) || ( nombreChoisi == -1)) {
				//ajusterNombreChoisi(nombreChoisi, nombres);
				valide = true;
			}
		} while(valide == false);

		return nombreChoisi;
	}

	/**
	 * 
	 * @return
	 */
	public static char operateurValideClavier() {

		char operateur = 'z';
		String message = "Entrez un op�rateur (+,-,*,/ ou = pour annuler)";
		String reponse;

		do {
			reponse = JOptionPane.showInputDialog(null, message);
		} while(reponse.length()!=1 || (!reponse.equals("+") && !reponse.equals("-") && !reponse.equals("/") 
				&& !reponse.equals("*") && !reponse.equals("=")) );
		operateur = reponse.charAt(0);

		return operateur;
	}

	/**
	 * 
	 */
	public static void afficherEntete() {

		String message 	= 
				"Le jeu consiste � trouver une valeur cible en utilisant un nombre d'op�rations fix� �"
						+ "-l'avance et une liste de nombres fournie. \n\n\n"
						+ "-Un nombre peut se r�p�ter dans la liste fournie +\n"
						+ "-Les seules op�rations permises sont : +, -, * et /\n"
						+ "-Un nombre de la liste ne peut �tre utilis� qu'une fois dans la solution\n"
						+ "-En tout temps la valeur -1 annule l'op�ration en cours";

		JOptionPane.showMessageDialog(null, message);

	}

	/**
	 * 
	 * @param expression
	 */
	public static void afficherExpression(char[] expression) {

		String message 	= 
				"Une solution: \n"
						+ new String(expression);

		JOptionPane.showMessageDialog(null, message);


	}

	/**
	 * 
	 * @return
	 */
	public static char veutRejouer() {

		char reponseChar = 'z';
		String message = "Voulez-vous rejouer une partie (o/n)";
		String reponse;

		do {
			reponse = JOptionPane.showInputDialog(null, message);
		} while(reponse.length()!=1 || (!reponse.equals("o") && !reponse.equals("n")) );
		reponseChar = reponse.charAt(0);

		return reponseChar;
	}

	/**
	 * 
	 * @param message
	 */
	public static void afficherMessage(String message) {

		JOptionPane.showMessageDialog(null, message);
	}


}
