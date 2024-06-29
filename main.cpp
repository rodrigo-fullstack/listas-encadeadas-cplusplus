#include <iostream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class LinkedList {
    
    private:
        Node* header;
        Node* tail;
        int size;    
        const string emptyList = "Lista Vazia!";
        const string indexError = "Posição Inválida";
        const int NOT_FOUND = -1;
    
    
    public:
        LinkedList() : header(nullptr), tail(nullptr), size(0) {}
    
    public:

        int addStart(int value){
            if(verifyEmpty()){
                return add(value);
            }

            Node* newNode = new Node();
            newNode -> data = value;
            newNode -> next = header;
            header = newNode;
            return value;
        }

        int add(int value){
            /*
            Alocando memória para o objeto node
            Se não fizer isso dá erro de segmentation fault
            */
            Node* node = new Node();
            /*Atribuição aos estados do nó
            É feito por meio de setas ->
            */ 
            node -> data = value;
            node -> next = nullptr;
            
            /*Se for vazio o início header recebe o nó*/ 
            if(verifyEmpty()) header = node; 

            /*Se não, o próximo do último elemento recebe o nó*/
            else tail -> next = node;

            /*O último recebe a célula independentes dos casos*/ 
            tail = node;
            
            /*Tamanho aumenta em 1*/
            size++;
            return value;
        }

        int add(int value, int position){
            try{
                if(verifyExistIndex(position)){
                    throw indexError;
                }
                
            } catch (const char* message){
                cerr << message << endl;
            }

            if(position == 0){
                return addStart(value);
            }

            if(position == size - 1){
                return add(value);
            }

            Node* newNode = new Node();
            
            Node* nodePosition = searchNodeWithIndex(position - 1);

            newNode -> data = value;
            newNode -> next = nodePosition ->next;
            nodePosition = newNode;
            return value;
        }
    public:
        void clean(void){
            Node* current = header;
            for(int i = 0; i < size; i++){
                Node* next = current -> next;
                /*Desalocando da memória*/
                delete current;
                current = next; 
            } 
            header = nullptr;
            tail = nullptr;
            size = 0;
        }

    private:
        bool verifyExistIndex(int index){
            return !(index >= 0 && index <= size);
        }

    private:
        Node* searchNodeWithIndex(int index){
            /*Try-Catch:
            Tenta executar um conjunto de instruções (try), se gerar um erro redireciona o fluxo para o catch (capturar). Isso pode ser direcionado usando o throw
            */
            try{
                if(verifyEmpty())
                    throw emptyList;

                if(verifyExistIndex(index))
                    throw indexError;
                
                /*Mensagem é um ponteiro de conjunto de caracteres recebendo o valor do throw*/ 
            } catch(const char* message){
                //Cerr é o comando da classe ostream que serve para exibir erros
                cerr << message << endl;
            }
            if(index == 0){
                return header;
            }
            
            if(index == size - 1){
                return tail;
            }

            Node* iterator = header;
            int pos = 0;

            while(iterator -> next != nullptr){
                if(pos == index) 
                    return iterator;

                iterator = iterator -> next;
                pos++;
            }
            return nullptr;
        }

    public:
        int searchWithIndex(int index){
            return searchNodeWithIndex(index) -> data;
        }

    private:
        int searchFirstElementPosition(int element){
            try{
                if(verifyEmpty()){
                    throw emptyList;
                }
            } catch(const char* message){
                cerr << message << endl;
            }
        
            if(header -> data == element) return 0;

            if(tail -> data == element) return (size - 1);

            Node* iterator = header;
            for(int i = 0; i < size; i++){
                if(iterator -> data == element) return i;
                
                iterator = iterator -> next;
            }
            return NOT_FOUND;
        }

    public:
        bool contains(int element){
            try{
                if(verifyEmpty()){
                    throw emptyList;
                }
            } catch(const char* message){
                cerr << message << endl;
            }
        
            if(header -> data == element) return true;

            if(tail -> data == element) return true;

            Node* iterator = header;
            for(int i = 0; i < size; i++){
                if(iterator -> data == element) return true;
                
                iterator = iterator -> next;
            }
            return false;
        }
        
        int contains(int element, bool returnPositionOfElement){
            if(returnPositionOfElement){
                return searchFirstElementPosition(element);
            }
            return NOT_FOUND;
        }

    public: 
        Node* getHeader(){
            return header;
        }

    public: 
        Node* getTail(){
            return tail;
        }

    public: 
        bool verifyEmpty(){
            return (size == 0);
        }

    public:         
        bool isNotNull(Node* current){
            return (current != nullptr);
        }
        
    public: 
        bool hasNext(Node* node){
            return (node -> next) != nullptr;
        }

    public: 
        void showHeaderAndTail(){
            std::cout << 
            "Início = " + std::to_string(header -> data) +
            "\nÚltimo = " + std::to_string(tail -> data)
            << endl;
        }

    public: 
        string toStringList(void){
            if(verifyEmpty()){
                return "[]";
            }
            
            string sb = "[";
            Node* current = header;
            while(isNotNull(current)){
                sb += std::to_string(current -> data);
                if(!hasNext(current)){
                    sb += "]";
                    return sb;
                }
                sb += ", ";
                current = current -> next;
            }
            return sb;
        }
    public: 
        void printList(){
            std::cout << toStringList() << endl;
        }
};



int main(){
    LinkedList lista;
    std::cout << lista.toStringList() << std::endl;

    lista.add(1);
    lista.showHeaderAndTail();

    lista.add(2);
    lista.showHeaderAndTail();
    lista.printList();

    lista.add(3);
    lista.printList();

    lista.clean();

    lista.printList();

    lista.add(3);
    lista.add(2);
    lista.add(1);

    /*Buscando por posição*/

    // lista.searchWithIndex(-1);
    // lista.searchWithIndex(100);

    //Último elemento;
    cout << "Elemento posição 2: "+ std::to_string(lista.searchWithIndex(2)) << endl;
    
    cout << "Elemento posição 1: " + std::to_string(lista.searchWithIndex(1)) << endl;

    cout << "Elemento posição 0: " + std::to_string(lista.searchWithIndex(0)) << endl;

    /*Buscando posição do primeiro elemento escolhido*/

    cout << "Elemento 0 na posição: " + std::to_string(lista.contains(0, true)) << endl;

    cout << "Elemento 1 na posição: " + std::to_string(lista.contains(1, true)) << endl;

    cout << "Elemento 2 existe: " + std::to_string(lista.contains(2)) << endl;

    cout << "Elemenoto 3 na posição: " + std::to_string(lista.contains(3, true)) << endl;

    cout << "Elemento adicionado no começo: " + std::to_string(lista.addStart(10)) << endl;

    cout << lista.toStringList() << endl;

    lista.clean();

    cout << "Elemento adicionado no começo: " + std::to_string(lista.addStart(20)) << endl;

    cout << lista.toStringList() << endl;

    lista.add(30);
    lista.addStart(40);

    cout << lista.toStringList() << endl;   

    cout << "Adicionando elemento: " + std::to_string(lista.add(15, 1)) + " na posição 1" << endl;

    cout << lista.toStringList() << endl;

    return 0;

}