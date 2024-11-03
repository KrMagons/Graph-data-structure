#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
class ListElement{

    private:

        T element; //element
        ListElement* next_element; //pointer to next element

    public:

        //constructor
        ListElement(T element){
            this->element = element;
            this->next_element = nullptr;
        }

        //method that sets a pointer to next element
        void set_next_element(ListElement* next_element){
            this->next_element = next_element;
        }

        //method that returns a pointer to next element
        ListElement* get_next_element(){
            return this->next_element;
        }

        //method that returns element
        T get_element(){
            return this->element;
        }

        //method that returns a reference to element
        T& get_reference(){
            return this->element;
        }
};


template <typename T>
class List{

    private:

        ListElement<T>* start; //pointer to list start
        ListElement<T>* end; //pointer to list end
        int size; //list size

        //method that splits list in half and returns a pointer to list middle
        ListElement<T>* split(ListElement<T>* start){
            ListElement<T>* fast = start;
            ListElement<T>* slow = start;

            while (fast->get_next_element() != nullptr && fast->get_next_element()->get_next_element() != nullptr) {
                fast = fast->get_next_element()->get_next_element();
                slow = slow->get_next_element();
            }
            ListElement<T>* temporary = slow->get_next_element();
            slow->set_next_element(nullptr);
            return temporary;
        }

        //recursive method that merges two sorted lists together
        ListElement<T>* merge(ListElement<T>* first, ListElement<T>* second){
            if (first == nullptr) {
                return second;
            }

            if (second == nullptr) {
                return first;
            }

            ListElement<T>* merged = nullptr;

            if (first->get_element() <= second->get_element()) {
                merged = first;
                merged->set_next_element(merge(first->get_next_element(), second));
            } else {
                merged = second;
                merged->set_next_element(merge(first, second->get_next_element()));
            }
            return merged;
        }

        //recursive method that uses split and merge to sort list
        void merge_sort(ListElement<T>* start){
            if (this->start == nullptr || this->start->get_next_element() == nullptr) {
                return;
            }

            ListElement<T>* second = split(this->start);
            merge_sort(this->start);
            merge_sort(second);
            this->start = merge(this->start, second);

            ListElement<T>* current = this->start;
            while (current->get_next_element() != nullptr) {
                current = current->get_next_element();
            }
            this->end = current;
        }

    public:

        //constructor
        List(){
            this->start = nullptr;
            this->end = nullptr;
            this->size = 0;
        }

        //destructor
        ~List(){
            this->clear();
        }

        //method that returns list size
        int get_size(){
            return this->size;
        }

        //method that checks if list is empty
        bool is_empty(){
            if(this->size == 0){
                return true;
            }else{
                return false;
            }
        }

        //method that adds an element to list end
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

        //method that adds an element to list start
        void add_front(T element){
            ListElement<T>* new_element = new ListElement<T>(element);
            if(this->is_empty()){
                this->end = new_element;
            }else{
                new_element->set_next_element(this->start);
            }
            this->start = new_element;
            this->size++;
        }

        //method that sorts an element in list and adds it (list must be sorted already)
        void add_sorted(T element){
            if (this->is_empty() || element >= this->end->get_element()) {
                this->add_back(element);
                return;
            }

            if (element <= this->start->get_element()) {
                this->add_front(element);
                return;
            }

            ListElement<T>* new_element = new ListElement<T>(element);
            ListElement<T>* current = this->start;

            while (current->get_next_element() != nullptr && current->get_next_element()->get_element() < element) {
                current = current->get_next_element();
            }
            new_element->set_next_element(current->get_next_element());
            current->set_next_element(new_element);
            this->size++;
        }

        //method that removes an element from list end
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

        //method that removes an element from list start
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

        //method that removes an element from list by index
        void remove(int id){
            if(id < 0 || id >= this->get_size() || this->is_empty()){
                throw out_of_range("Index out of bounds");
            }
            
            ListElement<T>* current = this->start;

            if (id == 0) {
                this->start = current->get_next_element();
                delete current;
                this->size--;
                return;
            }

            ListElement<T>* previous_element = nullptr;    
            for (int i = 0; i < id; i++) {
                previous_element = current;
                current = current->get_next_element();
            }

            previous_element->set_next_element(current->get_next_element());
            delete current;
            this->size--;
        }

        //method that returns the element of list start
        T get_front(){
            if(this->is_empty()){
                throw out_of_range("List is empty");
            }else{
                return this->start->get_element();
            }
        }

        //method that returns the element of list end
        T get_back(){
            if(this->is_empty()){
                throw out_of_range("List is empty");
            }else{
                return this->end->get_element();
            }
        }

        //method that returns an element from list by index 
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

        //method that returns a reference to an element from list by index
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

        //method that sorts list
        void sort(){
            this->merge_sort(this->start);
        }

        //method that clears list
        void clear(){
            int size = this->get_size();
            if(!this->is_empty()){
                for(int i = 0; i < size; i++){
                    this->remove_back();
                }
            }
        }

        //method that prints list
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


template <typename T>
class PriorityQueue{

    private:

        List<T> priority_queue;

    public:

        PriorityQueue(){
            this->priority_queue.sort();
        }

        int get_size(){
            return this->priority_queue.get_size();
        }

        bool is_empty(){
            return this->priority_queue.is_empty();
        }

        void push(T element){
            this->priority_queue.add_sorted(element);
        }

        T pop(){
            if (this->is_empty()){
                throw out_of_range("Priority queue is empty");
            }

            T element = this->priority_queue.get_front();
            this->priority_queue.remove_front();
            return element;
        }

        T get_element(int id){
            return this->priority_queue.get(id);
        }

        void print(){
            while (!this->is_empty()) {
                cout << this->pop() << " ";
            }
        }
};


template <typename T1, typename T2>
class Pair{

    private:

        T1 first;
        T2 second;

    public:

        Pair(){}

        Pair(T1 first, T2 second){
            this->first = first;
            this->second = second;
        }

        T1 get_first(){
            return this->first;
        }

        T2 get_second(){
            return this->second;
        }

        void set_first(T1 first){
            this->first = first;
        }

        void set_second(T2 second){
            this->second = second;
        }

        void print(){
            cout << this->get_first() << " " << this->get_second();
        }

};


template<typename K, typename V>
class Map{

    private:

        List<Pair<K, V>> map;

    public:

        Map(){}

        int get_size(){
            return this->map.get_size();
        }

        bool is_empty(){
            return this->map.is_empty();
        }

        void insert(K key, V value){
            if (this->exists(key)) {
                throw runtime_error("Key already exists");
            }
            
            Pair<K, V> pair(key, value);
            map.add_back(pair);
        }

        void remove(K key){
            if (!this->exists(key)) {
                throw runtime_error("Key not found");
            }

            for (int i = 0; i < this->get_size(); i++) {
                if (this->map.get(i).get_first() == key) {
                    this->map.remove(i);
                    break;
                }
            }
        }

        void clear(){
            this->map.clear();
        }

        bool exists(K key){
            if (this->map.is_empty()) {
                return false;
            }

            for (int i = 0; i < this->get_size(); i++){
                if (this->map.get(i).get_first() == key) {
                    return true;
                }
            }
            return false;
        }

        void update_value(K key, V value){
            if (this->is_empty()){
                throw runtime_error("Map is empty");
            }

            for (int i = 0; i < this->get_size(); i++){
                if (this->map.get(i).get_first() == key) {
                    this->map.get(i).get_second() = value;
                }
            }
            throw runtime_error("Key not found");
        }

        V get_value(K key){
            if (this->is_empty()) {
                throw runtime_error("Map is empty");
            }

            for (int i = 0; i < this->get_size(); i++) {
                if (this->map.get(i).get_first() == key) {
                    return this->map.get(i).get_second();
                }
            }
            throw runtime_error("No value found for this key");
        }

        K get_key(V value){
            if (this->is_empty()) {
                throw runtime_error("Map is empty");
            }

            for (int i = 0; i < this->get_size(); i++) {
                if (this->map.get(i).get_second() == value) {
                    return this->map.get(i).get_first();
                }
            }
            throw runtime_error("No key found for this value");
        }

};


class Edge{

    private:

        int from;
        int to;
        int cost; //always 1

    public:

        Edge(){}

        Edge(int from, int to){
            this->from = from;
            this->to = to;
            this->cost = 1;
        }

        int get_from(){
            return this->from;
        }

        int get_to(){
            return this->to;
        }

        int get_cost(){
            return this->cost;
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

        int get_size(){
            return this->graph.get_size();
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
            while (!queue.is_empty()) {
                int visited = queue.get_front();
                queue.remove();
                cout << visited << " ";
                for (int i = 0; i < this->graph.get_reference(visited).get_neighbours().get_size(); i++) {
                    int neighbour = this->graph.get_reference(visited).get_neighbours().get(i).get_to();
                    if (!visited_vertices[neighbour]) {
                        queue.add(neighbour);
                        visited_vertices[neighbour] = true;
                    }
                }
                
            }
        }


        //method that calculates heuristic (steps to goal vertex) for each vertex
        Map<int, int> calculate_heuristic(int start_vertex_id){
            Map<int, int> heuristic_map;
            heuristic_map.insert(start_vertex_id, 0); //cost from start -> start is 0

            Queue<int> queue;
            queue.add(start_vertex_id);
            while (!queue.is_empty()) {
                int visited = queue.get_front();
                queue.remove();
                int cost = heuristic_map.get_value(visited);
                //get neighbours for current vertex
                for (int i = 0; i < this->graph.get_reference(visited).get_neighbours().get_size(); i++) {
                    int neighbour = this->graph.get_reference(visited).get_neighbours().get(i).get_to();
                    int neighbour_cost = this->graph.get_reference(visited).get_neighbours().get(i).get_cost();
                    int new_cost = cost + neighbour_cost;
                //if this path to neighbour vertex is new or shorter than a different one, update the new heuristic for this neighbour vertex
                if (!heuristic_map.exists(neighbour) || heuristic_map.get_value(neighbour) > new_cost) {
                    heuristic_map.insert(neighbour, new_cost);
                    queue.add(neighbour);
                }
                }

            }
            return heuristic_map;
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
cout<< "Graph with 3 rooms: " << "\n";
graph.print();

cout<< "\n";

cout << "BFS Graph from state 4: " << "\n";
graph.print_bfs(4);

cout<< "\n";
cout<< "\n";

Map<int, int> heuristic_values = graph.calculate_heuristic(4);
for (int i = 0; i < graph.get_size(); i++) {
    if (heuristic_values.exists(i)) {
        cout << "4" << " -> " << i << " is " << heuristic_values.get_value(i) << " steps " << "\n";
    }
}

}
