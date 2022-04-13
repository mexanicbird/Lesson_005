#include <iostream>
#include <vector>
#include <ctime>
#define FULLSTACK 21
using namespace std;

/* task 001 */
template<class T>
class Pair1 {
protected:
    T pairVarFirst;
    T pairVarSecond;
public:
    Pair1 (T _pairVarFirst, T _pairVarSecond ) : pairVarFirst(_pairVarFirst), pairVarSecond(_pairVarSecond){
    }
    T first () const {
        return pairVarFirst;
    }
    T second () const {
        return pairVarSecond;
    }
};



/* task 002 */
template<class T1, class T2>
class Pair {
protected:
    T1 pairVarFirst;
    T2 pairVarSecond;
public:
    Pair (T1 _pairVarFirst, T2 _pairVarSecond ) : pairVarFirst(_pairVarFirst), pairVarSecond(_pairVarSecond){
    }
    T1 first () const {
        return pairVarFirst;
    }
    T2 second () const {
        return pairVarSecond;
    }
};



/* task 003 */
template <typename T3>
class StringValuePair : public Pair<std::string, T3> {
protected:
public:
    StringValuePair (const std::string stringValue, const T3 randomValue) :
    Pair<std::string, T3> (stringValue, randomValue){};
};



/* task 004 */
enum ECardSuit { SPADES, CLUBS, DIAMONDS, HEARTS };
enum ECardValue {
    ACE   = 1,
    TWO   = 2,
    THREE = 3,
    FOUR  = 4,
    FIVE  = 5,
    SIX   = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE  = 9,
    TEN   = 10,
    JACK  = 10,
    QUEEN = 10,
    KING  = 10
};

class Card {
    ECardSuit suit;
    ECardValue value;
    bool isCoverUp;
public:
    Card(ECardSuit _suit, ECardValue _value) : suit(_suit), value(_value) {
        isCoverUp = true;
    }

    void flip() {
        isCoverUp =! isCoverUp;
    }
    ECardValue getValue() const {
        return value;
    }
};

class Hand {
protected:
    std::vector<Card*> m_cards;
public:
    void Add(Card* newCard) {
        m_cards.push_back(newCard);
    };

    void Clear() {
        auto iter = m_cards.begin();
        for (iter = m_cards.begin(); iter != m_cards.end(); ++iter) {
            delete *iter;
            *iter = 0; }
        m_cards.clear();
    };

    int getTotal() const {
        if (m_cards.empty()) {
            return 0; }

        if (m_cards[0]->getValue() == 0)
        {
            return 0; }

        int total = 0;
        vector<Card*>::const_iterator iter;
        for (iter = m_cards.begin(); iter != m_cards.end(); ++iter) {
            total += (*iter)->getValue(); }

        bool containsAce = false;
        for (iter = m_cards.begin(); iter != m_cards.end(); ++iter) {
            if ((*iter)->getValue() == ACE) {
                containsAce = true; }
        }

        if (containsAce && total <= 11) {
            total += 10;
        }
        return total;
    }
};

class GenericPlayer : public Hand {
protected:
    std::string name;
public:
    GenericPlayer(std::string _name) : name(_name) {
    }

    virtual ~GenericPlayer() {
    Clear();}

    virtual bool IsHitting() {
        // мне кажется эта функция должна быть переопределена
        // отдельно для игрока и отдельно для компьютера
        return 0;
    }

    bool IsBoosted() {
        return (getTotal() >= FULLSTACK);
    }

    void Bust() {
        std::cout << "У игрока - " << name << " перебор!" <<std::endl;
    }
};



int main(int argc, const char** argv) {
    /* execution time control */
    double start_time =  clock();

    std::cout << "Lesson 004" << std::endl;
    std::cout << "Task 1" << std::endl;
    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
    std::cout << "\n";

    std::cout << "Task 2" << std::endl;
    Pair<int, double> p3(6, 7.8);
    cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';
    const Pair<double, int> p4(3.4, 5);
    cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';
    std::cout << "\n";

    std::cout << "Task 3" << std::endl;
    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
    std::cout << "\n";

    std::cout << "Task 4" << std::endl;
    GenericPlayer a1("Алексей");
    a1.getTotal();
    std::cout << (a1.IsBoosted()) << std::endl;
    a1.Bust();
    std::cout << "\n";

    /* execution time control */
    double end_time = clock();
    double search_time = (end_time - start_time)/1000;
    std::cout << "Program execution time = " << search_time << " sec"<< std::endl;
    return 0;
}
