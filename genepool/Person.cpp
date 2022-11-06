#include "Person.h"

std::set<Person*> Person::setUn(std::set<Person*> set1, std::set<Person*> set2) {
    std::set<Person*> output = set1;
    output.insert(set2.begin(), set2.end());
    return output;
}

Person::ParentTree* Person::findInd(Person* spouse) {
    for (auto it = cTrees.begin(); it != cTrees.end(); ++it) {
        if (_gender == Gender::MALE) {
            if ((*it)->mom == spouse) return *it;
        }
        else {
            if ((*it)->dad == spouse) return *it;
        }
    }
    return nullptr;
}

std::set<Person*> Person::removeGender(std::set<Person*> input, Gender gen) {
    std::set<Person*> output = input;
    auto it = output.begin();

    while (it != output.end()) {
        if ((*it)->gender() == Gender::FEMALE) it = output.erase(it);
        else ++it;
    }

    return output;
}

// Person Member Functions
void Person::cPop(Person* spouse) {
    for (auto it = cTrees.begin(); it != cTrees.end(); ++it) {
        if (_gender == Gender::MALE) {
            if ((*it)->mom == spouse) {
                cTrees.erase(it);
                return;
            }
        }
        else {
            if ((*it)->dad == spouse) {
                cTrees.erase(it);
                return;
            }
        }
    }
}


Person::Person(std::string nameInp, std::string genderInp, Person* motherInp, Person* fatherInp) {
    _name = nameInp;
    _gender = (genderInp == "male" ? Gender::MALE : Gender::FEMALE);
    _mother = motherInp;
    _father = fatherInp;
}

Person::~Person() {
    if (_gender == Gender::MALE) {
        for (auto it = cTrees.begin(); it != cTrees.end(); ++it) {
            if ((*it)->mom) (*it)->mom->cPop(this);
            delete* it;
        }
    }
    else {
        for (auto it = cTrees.begin(); it != cTrees.end(); ++it) {
            if ((*it)->dad) (*it)->dad->cPop(this);
            delete* it;
        }
    }
    
}

const std::string& Person::name()   const   { return _name; }
Gender  Person::gender() const              { return _gender; }
Person* Person::mother()                    { return _mother; }
Person* Person::father()                    { return _father; }

Person::ParentTree* Person::addChild(Person* child) {
    if (_gender == Gender::MALE) {
        for (auto it = cTrees.begin(); it != cTrees.end(); ++it) {
            if (child->mother() == (*it)->mom) {
                (*it)->children.insert(child);
                return nullptr;
            }
        }
    }
    else {
        for (auto it = cTrees.begin(); it != cTrees.end(); ++it) {
            if (child->father() == (*it)->dad) {
                (*it)->children.insert(child);
                return nullptr;
            }
        }
    }

    Person::ParentTree* newTree = new ParentTree;

    newTree->mom = child->mother();
    newTree->dad = child->father();
    newTree->children.insert(child);

    cTrees.push_back(newTree);

    return newTree;


}

void Person::pushTree(Person::ParentTree* tree) { cTrees.push_back(tree); }


// Old people

// Ancestors
std::set<Person*> Person::ancestors(PMod pmod) {
    if (pmod == PMod::ANY) {
        std::set<Person*> output;
        std::set<Person*> mAnc;
        std::set<Person*> pAnc;
        if (_mother) {
            mAnc = _mother->ancestors();
            output.insert(_mother);
        }
        if (_father) {
            pAnc = _father->ancestors();
            output.insert(_father);
        }
        
        return setUn(setUn(mAnc,pAnc),output);
    }
    else if (pmod == PMod::PATERNAL) {
        if (_father) {
            std::set<Person*> output;
            output.insert(_father);
            return setUn(_father->ancestors(), output);
        }
        else return std::set<Person*>();
    }
    else {
        if (_mother) {
            std::set<Person*> output;
            output.insert(_mother);
            return setUn(_mother->ancestors(), output);
        }
        else return std::set<Person*>();
    }
}

// Parents

std::set<Person*> Person::parents(PMod pmod) {
    std::set<Person*> output;
    if (_father && pmod != PMod::MATERNAL) output.insert(_father);
    if (_mother && pmod != PMod::PATERNAL) output.insert(_mother);
    return output;
}

// Aunt/Uncle

std::set<Person*> Person::parsib(PMod pmod, SMod smod) {
    std::set<Person*> pParsib;
    std::set<Person*> mParsib;
    if (_father && pmod != PMod::MATERNAL) pParsib = _father->siblings(pmod, smod);
    if (_mother && pmod != PMod::PATERNAL) mParsib = _mother->siblings(pmod, smod);

    return setUn(pParsib, mParsib);
}


std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    return removeGender(parsib(pmod, smod), Gender::FEMALE);
}
std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    return removeGender(parsib(pmod, smod), Gender::MALE);
}

// Grandparents

std::set<Person*> Person::grandparents(PMod pmod) {
    std::set<Person*> par = parents(pmod);
    std::set<Person*> output;
    for (auto it = par.begin(); it != par.end(); ++it) {
        output = setUn((*it)->parents(), output);
    }
    return output;
}

std::set<Person*> Person::grandfathers(PMod pmod) {
    return removeGender(grandparents(pmod), Gender::FEMALE);
}

std::set<Person*> Person::grandmothers(PMod pmod) {
    return removeGender(grandparents(pmod), Gender::MALE);
}

// Young people

// Children

std::set<Person*> Person::children() {
    std::set<Person*> output;
    for (auto it = cTrees.begin(); it != cTrees.end(); ++it) {
        output = setUn((*it)->children, output);
    }
    return output;
}


std::set<Person*> Person::children(ParentTree* exclude) {
    std::set<Person*> output;
    for (auto it = cTrees.begin(); it != cTrees.end(); ++it) {
        if (*it != exclude) output = setUn((*it)->children, output);
    }
    return output;
}

std::set<Person*> Person::sons() {
    return removeGender(children(), Gender::FEMALE);
}

std::set<Person*> Person::daughters() {
    return removeGender(children(), Gender::MALE);
}

std::set<Person*> Person::descendants() {
    std::set<Person*> childs = children();
    std::set<Person*> output = childs;
    for (auto it = childs.begin(); it != childs.end(); ++it) {
        output = setUn((*it)->descendants(), output);
    }

    return output;
}

// Grandchildren

std::set<Person*> Person::grandchildren() {
    std::set<Person*> childs = children();
    std::set<Person*> output;
    for (auto it = childs.begin(); it != childs.end(); ++it) {
        output = setUn((*it)->children(), output);
    }
    return output;
}

std::set<Person*> Person::granddaughters() {
    return removeGender(grandchildren(), Gender::FEMALE);
}
std::set<Person*> Person::grandsons() {
    return removeGender(grandchildren(), Gender::MALE);
}


// Siblings

std::set<Person*> Person::siblings(PMod pmod, SMod smod) {

    std::set<Person*> output;

    if (smod == SMod::FULL) {
        if (!_mother || !_father) return std::set<Person*>();
        output = _father->findInd(_mother)->children;
    }
    else if (smod == SMod::HALF) {
        std::set<Person*> mChild;
        std::set<Person*> pChild;

        if (_father && pmod != PMod::MATERNAL) {
            ParentTree* exclude = (_mother) ? _mother->findInd(_father) : nullptr;
            pChild = _father->children(exclude);
        }
        if (_mother && pmod != PMod::PATERNAL) {
            ParentTree* exclude = (_father) ? _father->findInd(_mother) : nullptr;
            mChild = _mother->children(exclude);
        }

        output = setUn(mChild, pChild);
    }
    else {
        std::set<Person*> mChild;
        std::set<Person*> pChild;

        if (_father && pmod != PMod::MATERNAL) pChild = _father->children();
        if (_mother && pmod != PMod::PATERNAL) mChild = _mother->children();

        output = setUn(mChild, pChild);
    }

    output.erase(this);
    return output;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    return removeGender(siblings(pmod, smod), Gender::FEMALE);
}
std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    return removeGender(siblings(pmod, smod), Gender::MALE);
}


// Cousins
std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    std::set<Person*> parsibs = parsib(pmod, smod);
    std::set<Person*> output;
    for (auto it = parsibs.begin(); it != parsibs.end(); ++it) {
        output = setUn((*it)->children(), output);
    }
    return output;
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    return removeGender(cousins(pmod, smod), Gender::FEMALE);
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    return removeGender(cousins(pmod, smod), Gender::MALE);
}


