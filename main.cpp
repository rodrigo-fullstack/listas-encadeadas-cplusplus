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
    
    
    public:
        LinkedList() : header(nullptr), tail(nullptr), size(0) {}
    
    public:
        int addLast(int value){
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
        Node* searchNodeWithIndex(int index){
            if(index < 0 )
        }

    public:
        int searchWithIndex(int index){

        }

    public:
        searchElement(int value){

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



int main()
{
    LinkedList lista;
    std::cout << lista.toStringList() << std::endl;

    lista.addLast(1);
    lista.showHeaderAndTail();

    lista.addLast(2);
    lista.showHeaderAndTail();
    lista.printList();

    lista.addLast(3);
    lista.printList();

    lista.clean();

    lista.printList();
    return 0;
}