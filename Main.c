import javax.swing.JOptionPane;

public class MainTP1 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		//JOptionPane.showMessageDialog(null, "salut");
		//afficherEntete();
		//operateurValideClavier();
		
		Nombre[] nombres = new Nombre[6]; //On génère le tableau de nombres
		boolean quitter = false;
		char[] expression = new char[100];
		int nombreOperation = UtilitaireFonctionsMath.alea(1, 5);
		int cible;
		char rejouer;
		
		afficherEntete();
		
		while (quitter==false) {
			
			genererNombres(nombres);
			
//			nombres[0].nombre = 5;
//			nombres[1].nombre = 2;
//			nombres[2].nombre = 6;
//			nombres[3].nombre = 7;
//			nombres[4].nombre = 1;
//			nombres[5].nombre = 8;
			
			initExpression(expression);
			//initExpression(expressionHumain);
			
			cible = genererValeurCible(nombres, nombreOperation, expression);
			
//			afficherNombres(nombres, nombreOperation, cible);
//			afficherExpression(expression);
			
			System.out.println(cible);
			
			rejouer = effectuerTour(nombres, nombreOperation, cible, expression );
			
			if(rejouer == 'o') {
				quitter = false;
			} else if (rejouer == 'n') {
				quitter = true;
			}
			
		}
		
		
	}
	
	public static int obtenirResultatValide(Nombre[] nombres, int compteurOperation, int nombreOperation) {
		
		int resultat;
		int nombre2;
		char operateur;
		
		initBoolean(nombres);
		
		resultat = nombreValideClavier(nombres);
		
		if(resultat!=-1) {
			ajusterNombreChoisi(resultat, nombres);
		}
		
		while (resultat != -1 && compteurOperation < nombreOperation) {
			operateur = operateurValideClavier();
			
			if(operateur != '=') {
				nombre2 = nombreValideClavier(nombres);
				if(nombre2 != -1) {
					ajusterNombreChoisi(resultat, nombres);
					
					resultat = resultatOperation(resultat, operateur, nombre2);
					compteurOperation++;
					System.out.println("le resultat de l'opération : "+resultat);
				} else {
					resultat = -1;
				}
			} else {
				resultat = -1;
			}
		}
		System.out.println("Resultat retourné: "+resultat);
		return resultat;
	}
	
	public static char effectuerTour(Nombre[] nombres, int nombreOperation, 
										  int cible, char[] expression) {
		int resultat;
		int compteurOperation = 0;
		char rejouer;
		do {
			afficherNombres(nombres, nombreOperation, cible);
			resultat = obtenirResultatValide(nombres, compteurOperation, nombreOperation );
			System.out.println(resultat);
			//afficherExpression(expression);
			if (resultat == cible) {
				afficherMessage("BRAVO!!!!!!!!!!!!");
			} else if (resultat != -1) {
				afficherMessage("Ce n'est pas le bon résultat.");
				resultat = -1;
			}
			
		} while ( resultat != -1 && resultat != cible );
		afficherExpression(expression);
		rejouer = veutRejouer();
		return rejouer;
		
	}
	
	public static int genererValeurCible(Nombre[] nombres, int nombreOperation, char[] expression) {
	
		
		int cible;
		int nombre2;
		int compteurOperation=0;
		int resultatOperation;
		int nouvelleTaille = 0;
		
		cible = nombreChoisiHasard(nombres);
		ajusterNombreChoisi(cible, nombres);
		
		nombre2 = nombrePasDejaChoisi(nombres);
		ajusterNombreChoisi(nombre2, nombres);
		
		while(compteurOperation < nombreOperation) {
			
			char operateur = operateurHasard();
			resultatOperation = resultatOperation(cible, operateur, nombre2);
			if (resultatOperation!=-1) {
				
				nouvelleTaille = creerExpression(expression, nouvelleTaille, cible, operateur, nombre2, resultatOperation);
				cible = resultatOperation;
				
				if (compteurOperation <= nombreOperation) {
					nombre2 = nombrePasDejaChoisi(nombres);
					ajusterNombreChoisi(nombre2, nombres);
					
				}
				compteurOperation++;
			}
		}
		
//		afficherExpression(expression);
//		afficherNombres(nombres, nombreOperation, cible);
		
		return cible;
		
		
		
		
	}
	
	public static void genererNombres(Nombre[] nombres) {
		
		for (int i = 0; i < nombres.length; i++) {
			nombres[i] = new Nombre(); 
			nombres[i].nombre=UtilitaireFonctionsMath.alea(1, 10);
			nombres[i].choisi = false;
		}
	}
	
	public static void initExpression(char[] tabChar) {
		
		for (int i = 0; i < tabChar.length; i++) {
			tabChar[i] = ' ';
		}
	}
	
	public static void initBoolean(Nombre[] nombres) {
		
		for (int i = 0; i < nombres.length; i++) {
			nombres[i].choisi = false;
		}
	}
	
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
	
	
	public static int nombreChoisiHasard(Nombre[] nombres) {
		
		int indexAleatoire = UtilitaireFonctionsMath.alea(0, 5);
		return nombres[indexAleatoire].nombre;
	}
	
	public static boolean nombreExiste(int nombre, Nombre[] nombres) {
		
		boolean existe = false;
		for (int i = 0; i < nombres.length; i++) {
			if(nombres[i].nombre == nombre && nombres[i].choisi == false) {
				existe = true;
			}
		}
		return existe;
	}
	
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
	
	public static int creerExpression(char[] expression, int taille, int operande1, char operateur, int operande2, int resultat) {
		
		String toAdd = "\n"+operande1+operateur+operande2+"="+resultat;
		
		concatenerNombre(expression, taille, toAdd);
		
		return taille+toAdd.length();
	}
	
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
	
	public static String tabToString(Nombre[] nombres) {
		
		String nombreDisplay ="";
		for (int i = 0; i < nombres.length; i++) {
			nombreDisplay+="        "+nombres[i].nombre;
		}
		
		return nombreDisplay;
		
	}
	
	public static String tabToStringPasChoisi(Nombre[] nombres) {
		
		String nombreDisplay ="";
		for (int i = 0; i < nombres.length; i++) {
			if(!nombres[i].choisi) {
				nombreDisplay+=" "+nombres[i].nombre;
			}
		}
		
		return nombreDisplay;
		
	}
	
	public static int nombreValideClavier(Nombre[] nombres) {
		
		int nombreChoisi = 0;
		String message = "Entrez un nombre existant dans la liste et non déjà utilisé ou -1 pour annuler. ("
							+tabToStringPasChoisi(nombres)+" )";
		String reponse;
		boolean valide = false;
		
		do {
			reponse = JOptionPane.showInputDialog(null, message);
			nombreChoisi = Integer.parseInt(reponse);
			if((nombreExiste(nombreChoisi, nombres) ) || ( nombreChoisi == -1)) {
				valide = true;
			}
		} while(valide == false);
		
		return nombreChoisi;
	}
	
	public static char operateurValideClavier() {
		
		char operateur = 'z';
		String message = "Entrez un opérateur (+,-,*,/ ou = pour annuler)";
		String reponse;
		
		do {
			reponse = JOptionPane.showInputDialog(null, message);
		} while(reponse.length()!=1 || (!reponse.equals("+") && !reponse.equals("-") && !reponse.equals("/") 
										&& !reponse.equals("*") && !reponse.equals("=")) );
		operateur = reponse.charAt(0);
		
		return operateur;
	}
	
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
	
	public static void afficherExpression(char[] expression) {
		
		String message 	= 
				"Une solution: \n"
				+ new String(expression);
		
		JOptionPane.showMessageDialog(null, message);
		
		
	}
	
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
	
	public static void afficherMessage(String message) {
		
		JOptionPane.showMessageDialog(null, message);
	}
	

}
