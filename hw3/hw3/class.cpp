#include <string>

using namespace std;


class Player{
    private:
        string name;

    public:
        Player* point;

        int blackVal = 0;
        int redVal = 0;

        void enqueue();
        void dequeue();
        void moveToBack();
};