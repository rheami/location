template<class K, class V>
class Mapwrap : public std::map<K,V>
{
    Mapwrap();


public:
    bool vide() const { return *this->empty(); }

    iterator debut() { return iterator( *this->begin()); }

    iterateur fin() { return iterateur( *this->end());}
};

Mapwrap::Mapwrap() : std::map<K, V>() {}