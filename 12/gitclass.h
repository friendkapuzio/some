class gitclass
{protected:
    int x=0;
public:
    virtual int show()const{return x;}
};


class gitclass2 : public gitclass
{
public:
    int show()const{return x+1;}
};

