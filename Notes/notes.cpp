#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// COMMANDES
// Créer un étudiant : create [name]
// Ajouter une note à un étudiant : add [name] [note]
// Afficher les notes d'un étudiant : notes [name] 
// Afficher la  moyenne d'un étudiant : average [name]
// Afficher la liste des étudiant : list

class Etudiant {
    public:
        Etudiant(const std::string & nom, const std::vector<double> & notes)
            : nom(nom), notes(notes) {}

        void ajouterNote(double note) {
            notes.push_back(note);
        }

        void afficherNotes(){
            std::cout << "Notes : ";
            for(int note : notes){
                std::cout << note << " ";
            }
            std::cout << " \n";
        }

        void afficherNom(){
            std::cout << nom << " \n";
        }

        void getNom(std::string& n) const{
            n = nom;
        }

        double getAverage() const{
            if (notes.empty()){
                std::cout << "Aucune notes à calculer. \n";
                return 0.0;
            }
            double somme = 0.0;
            for(double note : notes){
                somme += note;
            }
            return somme / notes.size();
        }
    
    private:
        std::string nom;
        std::vector<double> notes;
        
};
 
void ajouterEtudiant(std::vector<Etudiant>& liste ,const std::string & nom){
    liste.emplace_back(Etudiant(nom, std::vector<double>{}));
}

Etudiant* rechercherEtudiant(std::vector<Etudiant> & liste, const std::string & nom){
    for (Etudiant& etudiant : liste){
        std::string n;
        etudiant.getNom(n);
        if(n == nom){
            return &etudiant;
        }
    }
    return nullptr;
}
    
int main(){
    
    std::vector<Etudiant> liste;
   
    while (true) {
        std::string line;
        std::string command;
        std::string arg1;
        double arg2 =  0.0;
 
        std::cout << "Commands : [create, list, add, notes, average, quit]: ";
        std::getline(std::cin, line);
        std::istringstream stream(line);
        stream >> command;

        if (command == "quit"){
            break;
        }

        if(command == "create"){
            if (stream >> arg1){
                ajouterEtudiant(liste, arg1);
                std::cout << arg1 << " est ajouté à la liste des étudiants. \n";
            } else {
                std::cout << "Erreur : Veuillez entrer un nom. \n";
            }
        }
        
        if(command == "list"){
            for(Etudiant e : liste){
                e.afficherNom();
            }
        }

        if(command == "notes"){
            if (stream >> arg1){
                Etudiant* etudiant = rechercherEtudiant(liste, arg1);
                if( etudiant != nullptr){
                    etudiant->afficherNotes();
                } else {
                    std::cout << "Etudiant " << arg1 << " non trouvé. \n";
                }
            } else {
                std::cout << "Erreur : Veuillez entrer un nom. \n";
            }            
        }

        if(command == "average"){
            if (stream >> arg1){
                Etudiant* etudiant = rechercherEtudiant(liste, arg1);
                if( etudiant != nullptr){
                    double average = etudiant->getAverage();
                    std::cout << "La moyenne de " << arg1 << " est " << average << " \n";
                } else {
                    std::cout << "Etudiant " << arg1 << " non trouvé. \n";
                }
            } else {
                std::cout << "Erreur : Veuillez entrer un nom. \n";
            }            
        }


        if(command == "add"){
            if (stream >> arg1){
                Etudiant* etudiant = rechercherEtudiant(liste, arg1);
                if(etudiant != nullptr){
                    if(stream >> arg2){
                        if (arg2 <= 20 && arg2 >= 0){
                            etudiant->ajouterNote(arg2);
                            etudiant->afficherNotes();
                        } else {
                            std::cout << "Erreur : Valeur incorrecte, veuillez entrer une note entre 0 et 20 \n";
                        }
                    } else {
                        std::cout << "Erreur : Veuillez entrer une note entre 0 et 20 \n";
                    }
                } else {
                    std::cout << "Etudiant "<< arg1 <<" non trouvé. \n";
                }       

            } else {
                std::cout << "Erreur: Veuillez entrer un nom. \n";
            }
        }

    }

    return 0;
}
