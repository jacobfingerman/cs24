#ifndef PERSON_H
#define PERSON_H

#include "Enums.h"

#include <set>
#include <string>
#include <vector>
#include <algorithm>

// This is the Person class you need to implement.
// It has many member functions that perform relationship queries.
// Add any member variables you need to support this.
// Implement the member functions in Person.cpp.


class Person {
public:
    struct ParentTree {
        Person* mom;
        Person* dad;
        std::set<Person*> children;
    };

private:
  // Member Variables
    std::string _name;
    Gender _gender;
    Person* _mother;
    Person* _father;
    std::vector<ParentTree*> cTrees;
  // Helper Functions
    std::set<Person*> setUn(std::set<Person*> set1, std::set<Person*> set2);
    Person::ParentTree* findInd(Person* spouse);
    std::set<Person*> removeGender(std::set<Person*> input, Gender gen);

public:

  // Constructor
  Person(std::string nameInp, std::string genderInp, Person* motherInp, Person* fatherInp);
  // Destructor?
  ~Person();

  // Required Getter Functions
  const std::string& name()   const;
  Gender             gender() const;
  Person*            mother();
  Person*            father();

  // Required Relationship Functions
  std::set<Person*> ancestors(PMod pmod = PMod::ANY);
  std::set<Person*> aunts(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> brothers(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> children(ParentTree* exclude = nullptr);
  std::set<Person*> cousins(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> daughters(ParentTree* exclude = nullptr);
  std::set<Person*> descendants();
  std::set<Person*> grandchildren();
  std::set<Person*> granddaughters();
  std::set<Person*> grandfathers(PMod pmod = PMod::ANY);
  std::set<Person*> grandmothers(PMod pmod = PMod::ANY);
  std::set<Person*> grandparents(PMod pmod = PMod::ANY);
  std::set<Person*> grandsons();
  std::set<Person*> nephews(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> nieces(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> parents(PMod pmod = PMod::ANY);
  std::set<Person*> siblings(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> sisters(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> sons(ParentTree* exclude = nullptr);
  std::set<Person*> uncles(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);

  // Other Member Functions
  void cPop(Person* spouse);
  ParentTree* addChild(Person* child);
  void pushTree(Person::ParentTree* tree);
  std::set<Person*> parsib(PMod pmod, SMod smod);
};

#endif
