#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
class ListElement{

    private:

        T element;
        ListElement* next_element;

    public:

        ListElement(T element){
            this->element = element;
            this->next_element = nullptr;
        }

        void set_next_element(ListElement* next_element){
            this->next_element = next_element;
        }

        ListElement* get_next_element(){
            return this->next_element;
        }

        T get_element(){
            return this->element;
        }

        T& get_reference(){
            return this->element;
        }
};


template <typename T>
class List{

    private:

        ListElement<T>* start;
        ListElement<T>* end;
        int size;

    public:

        List(){
            this->start = nullptr;
            this->end = nullptr;
            this->size = 0;
        }

        ~List(){
            this->clear();
        }

        int get_size(){
            return this->size;
        }

        bool is_empty(){
            if(this->size == 0){
                return true;
            }else{
                return false;
            }
        }

        void add_back(T element){
            ListElement<T>* new_element = new ListElement<T>(element);
            if(this->is_empty()){
                this->start = new_element;
            }else{
                this->end->set_next_element(new_element);
            }
            this->end = new_element;
            this->size++;
        }

        void add_front(T element){
            ListElement<T>* new_element = new ListElement<T>(element);
            if(this->is_empty()){
                this->end = new_element;
            }else{
                new_element.set_next_element(this->start);
            }
            this->start = new_element;
            this->size++;
        }

        void remove_back(){
            if(this->is_empty()){
                return;
            }
            if(this->start == this->end){
                delete this->end;
                this->start = nullptr;
                this->end = nullptr;
                this->size--;
            }else{
                ListElement<T>* current = this->start;
                while(current->get_next_element() != this->end){
                    current = current->get_next_element();
                }
                delete this->end;
                this->end = current;
                current->set_next_element(nullptr);
                this->size--;
            }
        }

        void remove_front(){
            if(this->is_empty()){
                return;
            }
            if(this->start == this->end){
                delete this->start;
                this->start = nullptr;
                this->end = nullptr;
                this->size--;
            }else{
                ListElement<T>* current = this->start->get_next_element();
                delete this->start;
                this->start = current;
                this->size--;
            }
        }

        T get_front(){
            if(this->is_empty()){
                throw out_of_range("List is empty");
            }else{
                return this->start->get_element();
            }
        }

        T get_back(){
            if(this->is_empty()){
                throw out_of_range("List is empty");
            }else{
                return this->end->get_element();
            }
        }

        T get(int id){
            if(id < 0 || id >= this->get_size() || this->is_empty()){
                throw out_of_range("Index out of bounds");
            }
            ListElement<T>* current = this->start;
            for(int i = 0; i < id; i++){
                current = current->get_next_element();
            }
            return current->get_element();
        }

        T& get_reference(int id){
            if(id < 0 || id >= this->get_size() || this->is_empty()){
                throw out_of_range("Index out of bounds");
            }
            ListElement<T>* current = this->start;
            for(int i = 0; i < id; i++){
                current = current->get_next_element();
            }
            return current->get_reference();
        }

        void clear(){
            int size = this->get_size();
            if(!this->is_empty()){
                for(int i = 0; i < size; i++){
                    this->remove_back();
                }
            }
        }

        void print(){
            ListElement<T>* current = this->start;
            while(current != nullptr){
                cout << current->get_element() << " ";
                current = current->get_next_element();
            }
        }
};


template <typename T>
class Queue{

    private:

        List<T> queue;

    public:

        Queue(){}

        int get_size(){
            return this->queue.get_size();
        }

        bool is_empty(){
            if(this->get_size() == 0){
                return true;
            }else{
                return false;
            }
        }

        T get_front(){
            return this->queue.get_front();
        }

        void add(T element){
            this->queue.add_back(element);
        }

        void remove(){
            this->queue.remove_front();
        }
};


class Edge{

    private:

        int from;
        int to;

    public:

        Edge(){}

        Edge(int from, int to){
            this->from = from;
            this->to = to;
        }

        int get_from(){
            return this->from;
        }

        int get_to(){
            return this->to;
        }
};


class Vertex{

    private:

        int id;
        List<Edge> neighbours;

    public:

        Vertex(){}

        Vertex(int id){
            this->id = id;
        }

        int get_id(){
            return this->id;
        }

        List<Edge>& get_neighbours(){
            return this->neighbours;
        }

        void add_neighbour(Edge edge){
            this->neighbours.add_back(edge);
        }
};


class Graph{

    private:

        List<Vertex> graph;

    public:

        Graph(){}

        void add_vertex(int id){
            Vertex vertex(id);
            this->graph.add_back(vertex);
        }

        void add_edge(int from, int to){
            Edge edge(from, to);
            this->graph.get_reference(from).add_neighbour(edge);
        }

        void print(){
            if(this->graph.is_empty()){
                return;
            }
            for(int i = 0; i < this->graph.get_size(); i++){
                cout << this->graph.get_reference(i).get_id();
                for(int j = 0; j < this->graph.get_reference(i).get_neighbours().get_size(); j++){
                    cout << " -> ";
                    cout << this->graph.get_reference(i).get_neighbours().get(j).get_to();
                }
                cout << "\n";
            }
        }

        void print_bfs(int start_vertex_id){
            int vertex_count = this->graph.get_size();
            bool visited_vertices[vertex_count] = {false};
            Queue<int> queue;

            queue.add(start_vertex_id);
            visited_vertices[start_vertex_id] = true;
            while(!queue.is_empty()){
                int visited = queue.get_front();
                queue.remove();
                cout << visited << " ";
                for(int i = 0; i < this->graph.get_reference(visited).get_neighbours().get_size(); i++){
                    int neighbour = this->graph.get_reference(visited).get_neighbours().get(i).get_to();
                    if(!visited_vertices[neighbour]){
                        queue.add(neighbour);
                        visited_vertices[neighbour] = true;
                    }
                }
                
            }
        }
};


Graph graph_reader(string filename){

    Graph graph;
    fstream file;
    int vertex_count, edge_count;
    int from, to;

    file.open(filename);

    if(!file.is_open()){
        throw runtime_error("Error opening file");
    }

    file >> vertex_count >> edge_count;

    for(int i = 0; i < vertex_count; i++){
        graph.add_vertex(i);
    }

    for(int i = 0; i < edge_count; i++){
        file >> from >> to;
        graph.add_edge(from, to);
    }

    return graph;
}

int main(){

Graph graph = graph_reader("3rooms.txt");

cout << "Graph for 8 rooms: " << endl;
graph.print();

cout << endl;

cout << "BFS from state 0: " << endl;
graph.print_bfs(0);

}