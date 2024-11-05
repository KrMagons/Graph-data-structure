
                for (int i = 0; i < this->graph.get_reference(visited).get_neighbours().get_size(); i++) {
                    int neighbour = this->graph.get_reference(visited).get_neighbours().get(i).get_to();
                    if (!visited_vertices[neighbour]) {
                        queue.add(neighbour);
                        visited_vertices[neighbour] = true;
                    }
                }
            }
        }
};

int main(){

cout << "Hello world!";

}