import java.util.Random;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		//Nombre[] nombres = new Nombre[6];
		
		char[] testChar = new char[100];
		testChar[0] = 'a';
		testChar[1] = 'b';
		System.out.println("" + new String(testChar));
		System.out.println(concatenerNombre(testChar, 2, "nouvelleChaine"));
		//concatenerNombre(testChar, 2, "nouvelleChaine");
		System.out.println("\n"+ new String(testChar));
		
		
		
		//genererNombres(nombres);

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
			resultat = nombre1/nombre2;
		} else if (operateur == '-') {
			resultat = nombre1 - nombre2;
		}
		
		return resultat;
	}
	
	public static void ajusterNombreChoisi(int nombre, Nombre[] nombres) {
		boolean trouve = false;
		int index = 0;
		while (trouve == false) {
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
		
		while (trouve == false) {
			if (nombres[index].choisi == false) {
				trouve = true;
			}
			index++;
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
		return 0;
	}

}
