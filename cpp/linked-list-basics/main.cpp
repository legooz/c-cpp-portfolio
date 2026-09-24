#include "IntNode.cpp"

int main() {
    IntNode *p = new IntNode(10);
    p->next = new IntNode(8);

    std::cout << "First Node: " << p->info << std::endl;
    std::cout << "Second Node: " << p->next->info << std::endl;
    delete p->next;
    delete p;
    return 0;
}
